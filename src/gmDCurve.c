/**********************************************************************************
**
** Copyright (C) 1994 Narvik University College
** Contact: GMlib Online Portal at http://episteme.hin.no
**
** This file is part of the Geometric Modeling Library, GMlib.
**
** GMlib is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** GMlib is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with GMlib.  If not, see <http://www.gnu.org/licenses/>.
**
**********************************************************************************/



/*! \file gmDCurve.c
 *
 *  Implementation of the gmDCurve template class.
 *
 *  \date   2008-09-09
 */


//#include "gmOpenGL.h"

#include "gmPCurve.h"


namespace GMlib {


  template <typename T>
  inline
  DCurve<T>::DCurve( int s ) {

//    _p_ref = 0;
    _init();


    /////////////// PCURVE //////////////////
    _sam		            = s;
    _d		              = -1;
    _tr			            = T(0);
    _sc			            = T(1);
    setEval(0);
  }


  template <typename T>
  inline
  DCurve<T>::DCurve( const DCurve<T>& copy ) : DParametrics<T,1>( copy ) {

//    _p_ref        = copy._p_ref;
    _line_width   = copy._line_width;
    _no_der       = copy._no_der;
    _no_samp      = copy._no_samp;


    /////////////// PCURVE //////////////////
    _sam                = copy._sam;
    _p                  = copy._p;
    _t			            = copy._t;
    _d			            = copy._d;
    _tr			            = copy._tr;
    _sc			            = copy._sc;
    setEval(0);
  }


  template <typename T>
  inline
  DCurve<T>::DCurve( const PCurve<T,3>& copy ) : DParametrics<T,1>( copy ) { //, _p_ref( copy ) {

    _init();
  }


  template <typename T>
  inline
  DCurve<T>::DCurve( PCurve<T,3>* copy ) : DParametrics<T,1>( copy ) {

//    _p_ref = copy;

    _init();
  }


  template <typename T>
  void DCurve<T>::_init() {

    this->_lighted = false;
    _line_width = 1.0;
    _no_der = 0;
    _no_samp = 0;

    this->_default_visualizer.set( this );
  }

  template <typename T>
  inline
  float DCurve<T>::getLineWidth() const {

    return _line_width;
  }


  template <typename T>
  inline
  int DCurve<T>::getNoDer() const {

    return _no_der;
  }


  template <typename T>
  inline
  int DCurve<T>::getNoSamp() const {

    return _no_samp;
  }


//  template <typename T>
//  inline
//  PCurve<T,3>* DCurve<T>::getPCurve() {
//
//    return _p_ref;
//  }


  template <typename T>
  inline
  void  DCurve<T>::localDisplay() {

    glPushAttrib( GL_LIGHTING_BIT | GL_LINE_BIT ); {

      // Set Properties
      glDisable( GL_LIGHTING );
      glLineWidth( _line_width );

      for( int i = 0; i < this->_visualizers.getSize(); i++ )
        this->_visualizers[i]->display();

    } glPopAttrib();
  }


  template <typename T>
  inline
  void DCurve<T>::localSelect() {

    glPushAttrib( GL_LINE_BIT ); {

      glLineWidth( 2 * _line_width );

      if( this->_dynamic ) {

        glVertexPointer( 3, GL_FLOAT, 2*3*sizeof(float), this->_vertices_n1[0].getPtr() );
        glDrawArrays( GL_LINE_STRIP, 0, this->_vertices_n1.getDim() );
      }
      else
        glCallList( this->_dlist );

    } glPopAttrib();

    for( int i = 0; i < this->_visualizers.getSize(); i++ )
      this->_visualizers[i]->select();
  }


//  template <typename T>
//  void DCurve<T>::replot( int m, bool dynamic, int d ) {
//
//    // Check wheather or not PCurve is valid
//    if( !_p_ref )
//      return;
//
//
//    // Correct sample domain
//    if( m < 2 )
//      m = _p_ref->_sam;
//    else
//      _p_ref->_sam = m;
//
//
//    // Set Properties
//    this->_dynamic = dynamic;
//    _no_samp = m;
//    _no_der = d;
//
//
//    // Resample
//    DVector< DVector< Vector<T, 3> > > p;
//    _p_ref->resample( p, m, 1, _p_ref->getStartP(), _p_ref->getEndP() );
//
//
//    // Set The Surrounding Sphere
//    setSurroundingSphere( p );
//
//
//    // Clean up Display Lists
//    if( this->_dlist ) {
//
//      glDeleteLists( this->_dlist, 1 );
//      this->_dlist = 0;
//    }
//
//
//    // Create Display lists or input data into vertex arrays...
//    // Dependent on wheather or not the Curve is dynamic
//    if(dynamic) {
//
//      glEnableClientState( GL_VERTEX_ARRAY );
//      this->_vertices_n1.setDim( p.getDim() );
//
//      for( int i = 0; i < p.getDim(); i++ )
//        this->_vertices_n1[i] = p[i][0].toFloat();
//    }
//    else {
//
//      this->_dlist = glGenLists(1);
//
//      // Make displaylist for display of lined curve and select
//      glNewList( this->_dlist, GL_COMPILE ); {
//        glBegin(GL_LINE_STRIP); {
//
//          for( int i = 0; i < p.getDim(); i++ )
//            glPoint( Point<float, 3>( p[i][0].toFloat() ) );
//
//        }glEnd();
//      } glEndList();
//    }
//
//
//    // Replot Visaulizers
//    for( int i = 0; i < this->_visualizers.getSize(); i++ )
//      this->_visualizers[i]->replot( p, m, d );
//  }


  template <typename T>
  void DCurve<T>::replot( int m, int d, bool dynamic ) {

    // Check wheather or not PCurve is valid
//    if( !_p_ref )
//      return;


    // Correct sample domain
    if( m < 2 )
      m = _sam;
    else
      _sam = m;


    // Set Properties
    this->_dynamic = dynamic;
    _no_samp = m;
    _no_der = d;


    // Resample
//    cout << "Sample data of: " << getIdentity() << endl;
    DVector< DVector< Vector<T, 3> > > p;
    resample( p, m, 1, getStartP(), getEndP() );

//    for( int i = 0; i < p.getDim(); i++ ) {
//
//      cout << "samp: " << i << endl;
//      for( int j = 0; j < p[i].getDim(); j++ ) {
//        cout << " der: " << j << endl;
//        for( int k = 0; k < 3; k++ )
//          cout << "  " << p[i][j][k];
//        cout << endl;
//      }
//      cout << endl;
//    }
//    cout << endl << endl;

    // Set The Surrounding Sphere
    setSurroundingSphere( p );


    // Clean up Display Lists
    if( this->_dlist ) {

      glDeleteLists( this->_dlist, 2 );
      this->_dlist = 0;
    }


    // Create Display lists or input data into vertex arrays...
    // Dependent on wheather or not the Curve is dynamic
    if(dynamic) {

      glEnableClientState( GL_VERTEX_ARRAY );
      this->_vertices_n1.setDim( p.getDim() );

      for( int i = 0; i < p.getDim(); i++ )
        this->_vertices_n1[i] = p[i][0].toFloat();
    }
    else {

      this->_dlist = glGenLists(2);

      // Make displaylist for display of lined curve
      glNewList( this->_dlist, GL_COMPILE ); {
        glBegin(GL_LINE_STRIP); {

          for( int i = 0; i < p.getDim(); i++ )
            glPoint( Point<float, 3>( p[i][0].toFloat() ) );

        }glEnd();
      } glEndList();

      // Make displaylist for selection of lined curve
      glNewList( this->_dlist + 1, GL_COMPILE ); {
        glBegin(GL_LINE_STRIP); {

          for( int i = 0; i < p.getDim(); i++ )
            glPoint( Point<float, 3>( p[i][0].toFloat() ) );

        }glEnd();
      } glEndList();
    }


    // Replot Visaulizers
    for( int i = 0; i < this->_visualizers.getSize(); i++ )
      this->_visualizers[i]->replot( p, m, d );
  }


  template <typename T>
  inline
  void DCurve<T>::setLineWidth( float width ) {

    _line_width = width;
  }


//  template <typename T>
//  inline
//  void DCurve<T>::setPCurve( PCurve<T,3>* pcurve ) {
//
//    _p_ref = pcurve;
//    DParametrics<T,1>::setParametrics( _p_ref );
//  }


  template <typename T>
  inline
  void DCurve<T>::setSurroundingSphere( const DVector< DVector< Vector<T, 3> > >& p ) {

    Sphere<float,3>  s;
    s.resetPos( Point<float,3>( p(0)(0) ) );
    s += Point<float,3>( p(p.getDim() - 1)(0) );
    for( int i = p.getDim() - 2; i > 0; i-- )
      s += Point<float,3>( p(i)(0) );
    DParametrics<T,1>::setSurroundingSphere(s);
  }



  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // PCURVE !!!!!!!!!!!!!!!! PCURVE !!!!!!!!!!!!!!!!!!!! PCURVE !!!!!!!!!!!!!!
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  template <typename T>
  inline
  void	DCurve<T>::_eval( T t, int d ) {

    if( !(d <=_d &&  t ==_t) ) {

      _t = t; _d = d;
      eval( shift(t), d );
    }
  }


  template <typename T>
  inline
  void DCurve<T>::_evalDerDD( DVector< DVector< Vector<T, 3> > > & p, int d, T du ) const {



    T one_over_du = T(1) / du;
    T one_over_2du = T(1) / ( T(2) * du );

    int u, i, k;

    for( u = 1; u < d; u++ ) {
      for( i = 1; i < p.getDim() - 1; i++ ) {
        for( k = 0; k < 3; k++ )
          p[i][u][k] = p[i+1][u-1][k] - p[i-1][u-1][k];

        p[i][u] *= one_over_2du;
      }
    }

    if( isClosed() ) {
      for( u = 1; u < d; u++ ) {
        for( k = 0; k < 3; k++ )
          p[0][u][k] = p[p.getDim()-1][u][k] = p[1][u-1][k] - p[p.getDim() - 2][u-1][k];

        p[0][u] = p[p.getDim()-1][u] *= one_over_2du;
      }
    }
    else {
      for( u = 1; u < d; u++ ) {
        for( k = 0; k < 3; k++ ) {
          p[0][u][k] = p[1][u-1][k] - p[0][u-1][k];
          p[p.getDim()-1][u][k] = p[p.getDim()-1][u-1][k] - p[p.getDim()-2][u-1][k];

        }

        p[0][u] *= one_over_du;
        p[p.getDim()-1][u] *= one_over_du;
      }
    }
  }


  template <typename T>
  DVector<Vector<T,3> >& DCurve<T>::evaluate( T t, int d ) {

    static DVector< Vector<T,3> > p;
    p.setDim(d+1);
    _eval(t,d);

    p[0] = this->_present*((Point<T,3>)_p[0]);

    for( int i = 1; i <= d; i++ )
      p[i] = this->_present * (Vector<T,3>)_p[i];

    return p;
  }


  template <typename T>
  DVector<Vector<T,3> >& DCurve<T>::evaluateLocal( T t, int d ) {

    _eval(t,d);
    return _p;
  }


  template <typename T>
  DVector<Vector<T,3> >& DCurve<T>::evaluateParent( T t, int d ) {

    static DVector< Vector<T,3> > p;
    p.setDim(d+1);
    _eval(t,d);

    p[0] = this->_matrix*((Point<T,3>)_p[0]);

    for( int i = 1; i <= d; i++ )
      p[i] = this->_matrix * (Vector<T,3>)_p[i];

    return p;
  }


  template <typename T>
  inline
  T DCurve<T>::getCurvature( T t ) {

    _eval( t, 2 );
    Vector<T,3> d1 = _p[1];
    T a1= d1.getLength();

    if( a1 < T(1.0e-5) )
      return T(0);

    d1 /= a1;

    Vector<T,3> d2 = ( _p[2] - ( d1 * _p[2] ) * d1 ) / ( a1 * a1 );

    return d2.getLength();
  }


  template <typename T>
  inline
  T DCurve<T>::getCurveLength( T a , T b ) {

    if(b<a)	{

      a = getParStart();
      b = getParEnd();
    }

    return _integral( a, b, 1e-10 );
  }


  template <typename T>
  inline
  Vector<T,3> DCurve<T>::getDer1( T t ) {

    eval( t, 1 );
    return _p[1];
  }


  template <typename T>
  inline
  Vector<T,3> DCurve<T>::getDer2( T t ) {

    _eval(t,2);
    return _p[2];
  }


  template <typename T>
  inline
  std::string DCurve<T>::getIdentity() const {

    return "PCurve";
  }


  template <typename T>
  inline
  T DCurve<T>::getLocalMapping( T t, T /*ts*/, T /*ti*/, T /*te*/ ) {

    return t;
  }


  template <typename T>
  inline
  T DCurve<T>::getParDelta()	{

    return _sc*( getEndP() - getStartP() );
  }


  template <typename T>
  inline
  T DCurve<T>::getParEnd() {

    return getParStart() + getParDelta();
  }


  //template <typename T>
  //inline
  //T DCurve<T>::getRadius( T t ) {
  //
  //  return 1.0/getCurvature(t);
  //}
  //
  //template <typename T>
  //inline
  //T DCurve<T>::getSpeed( T t )		{
  //
  //  return getDer1(t).getLength();
  //}


  template <typename T>
  inline
  T DCurve<T>::getParStart()	{

    return getStartP() + _tr;
  }


  template <typename T>
  inline
  void DCurve<T>::resample( Array< Point<T, 3> >& a, T eps ) {

    _sam = 0; _s_sam = 0; _e_sam = 1;
    T t, ddt, dp5 = getParDelta()/5;
    bool go_on=true;

    for( t = getParStart(); go_on; t += ddt ) {

      eval( t, 2 );
      a += _p[0];
      if ( a.getSize() > 7000 )
        break;

      T _r = _p[1] * _p[1];
      Vector<T,3> r = _p[2]-( (_p[2] * _p[1] ) / _r) * _p[1];
      _r = sqrt(double(_r));
      ddt = 2 * _r / _p[1].getLength() * acos( ( _r - eps ) / _r);

      if( ddt > dp5)
        ddt = dp5;

      if( ddt > getParEnd() - t ) {

        T oddt = ddt;
        ddt = getParEnd() - t;
        go_on = false;

        if( ddt < oddt / 5 )
          a.removeIndex( a.getSize() - 1 );
      }
    }
    eval( t, 0 );
    a += _p[0];
  }


  template <typename T>
  inline
  void DCurve<T>::resample( Array<Point<T,3> >& a, int m ) {

    _sam = m; _s_sam = 0; _e_sam = 1;
    T du = getParDelta() / ( m - 1 );
    a.setSize( m );

    for( int i = 0; i < m; i++ ) {

      eval( getParStart() + i * du, 0 );
      a[i] = _p[0];
    }

  }


  template <typename T>
  inline
  void DCurve<T>::resample( Array<Point<T,3> >& a, int m, T start, T end ) {

    _sam = m; _s_sam = start; _e_sam = end;
    T du = getParDelta();
    T st = getParStart() + start * du;
    T et = getParStart() + end * du;
    du = ( et - st ) / ( m - 1 );
    a.setSize( m );

    for(int i=0; i<m; i++) {

      eval( st + i * du, 0 );
      a[i] = _p[0];
    }
  }


  template <typename T>
  inline
  void DCurve<T>::resample( DVector< DVector< Vector<T, 3> > >& p, int m, int d, T start, T end ) {

    T du = (end-start)/(m-1);
    p.setDim(m);

    for( int i = 0; i < m - 1; i++ ) {

      eval( start + i * du, d, true);
      p[i] = _p;
    }
    eval( end, d, true );
    p[m-1] = _p;


    switch( this->_dm ) {
      case GM_DERIVATION_EXPLICIT:
        // Do nothing, evaluator algorithms for explicite calculation of derivatives
        // should be defined in the eval( ... ) function enclosed by
        // if( this->_derivation_method == this->EXPLICIT ) { ... eval algorithms for derivatives ... }
        break;

      case GM_DERIVATION_DD:
      default:
        _evalDerDD( p, d, du );
        break;
    };
  }


  template <typename T>
  inline
  void DCurve<T>::setDomain(T start, T end) {

    _sc = ( end - start );
    _tr= getStartP() + start;
  }


  template <typename T>
  inline
  void DCurve<T>::setDomainScale( T sc ) {

    _sc = sc;
  }


  template <typename T>
  inline
  void DCurve<T>::setDomainTrans( T tr ) {

    _tr = tr;
  }


  template <typename T>
  inline
  void DCurve<T>::setEval( int d ) {

    _defalt_d = d;
  }


  template <typename T>
  inline
  T DCurve<T>::shift( T t ) {

    return _tr + _sc * ( t - getStartP() );
  }


  template <typename T>
  inline
  Point<T,3> DCurve<T>::operator()( T t )	{

    eval( t, _defalt_d );
    return ( Point<T,3> ) _p[0];
  }
}
