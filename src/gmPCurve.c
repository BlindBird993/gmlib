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



/*! \file gmCurve.c
 *
 *  Implementation of the gmCurve template class.
 *
 *  \date   2008-09-08
 */


#include "gmArray.h"


namespace GMlib {



  template <class T, int n>
  inline
  PCurve<T,n>::PCurve( int s ) {

    _sam		            = s;
    _d		              = -1;
    _tr			            = T(0);
    _sc			            = T(1);
    setEval(0);
  }

  template <class T, int n>
  inline
  PCurve<T,n>::PCurve( const PCurve<T,n>& pcurve ) : Parametrics<T,n> ( pcurve ) {

    _sam                = pcurve._sam;
    _p                  = pcurve._p;
    _t			            = pcurve._t;
    _d			            = pcurve._d;
    _tr			            = pcurve._tr;
    _sc			            = pcurve._sc;
    setEval(0);
  }


  template <typename T, int n>
  inline
  PCurve<T,n>::~PCurve() {}


  template <typename T, int n>
  inline
  void	PCurve<T,n>::_eval( T t, int d ) {

    if( !(d <=_d &&  t ==_t) ) {

      _t = t; _d = d;
      eval( shift(t), d );
    }
  }


  template <typename T, int n>
  inline
  void PCurve<T,n>::_evalDerDD( DVector< DVector< Vector<T, n> > > & p, int d, T du ) const {



    T one_over_du = T(1) / du;
    T one_over_2du = T(1) / ( T(2) * du );

    int u, i, k;

    for( u = 1; u < d; u++ ) {
      for( i = 1; i < p.getDim() - 1; i++ ) {
        for( k = 0; k < n; k++ )
          p[i][u][k] = p[i+1][u-1][k] - p[i-1][u-1][k];

        p[i][u] *= one_over_2du;
      }
    }

    if( isClosed() ) {
      for( u = 1; u < d; u++ ) {
        for( k = 0; k < n; k++ )
          p[0][u][k] = p[p.getDim()-1][u][k] = p[1][u-1][k] - p[p.getDim() - 2][u-1][k];

        p[0][u] = p[p.getDim()-1][u] *= one_over_2du;
      }
    }
    else {
      for( u = 1; u < d; u++ ) {
        for( k = 0; k < n; k++ ) {
          p[0][u][k] = p[1][u-1][k] - p[0][u-1][k];
          p[p.getDim()-1][u][k] = p[p.getDim()-1][u-1][k] - p[p.getDim()-2][u-1][k];

        }

        p[0][u] *= one_over_du;
        p[p.getDim()-1][u] *= one_over_du;
      }
    }
  }


  template <typename T, int n>
  DVector<Vector<T,n> >& PCurve<T,n>::evaluate( T t, int d ) {

    static DVector< Vector<T,n> > p(d+1);

    _eval(t,d);
    Vector<float,n> tmp= this->_matrix*((Point<T,n>)_p[0]).toFloat();
    for( int i = 0; i < 3; i++ )
      p[0][i] = tmp[i];

    for( int i = 1; i <= d; i++ ) {
      tmp = this->_matrix * (_p[i]).toFloat();
      for( int j = 0; j < 3; j++ )
        p[i][j] = tmp[j];
    }
    return p;
  }


  template <typename T, int n>
  DVector<Vector<T,n> >& PCurve<T,n>::evaluateLocal( T t, int d ) {

    _eval(t,d);
    return _p;
  }


  template <typename T, int n>
  inline
  T PCurve<T,n>::getCurvature( T t ) {

    _eval( t, 2 );
    Vector<T,3> d1 = _p[1];
    T a1= d1.getLength();

    if( a1 < T(1.0e-5) )
      return T(0);

    d1 /= a1;

    Vector<T,3> d2 = ( _p[2] - ( d1 * _p[2] ) * d1 ) / ( a1 * a1 );

    return d2.getLength();
  }


  template <typename T, int n>
  inline
  T PCurve<T, n>::getCurveLength( T a , T b ) {

    if(b<a)	{

      a = getParStart();
      b = getParEnd();
    }

    return _integral( a, b, 1e-10 );
  }


  template <typename T, int n>
  inline
  Vector<T,n> PCurve<T, n>::getDer1( T t ) {

    eval( t, 1 );
    return _p[1];
  }


  template <typename T, int n>
  inline
  Vector<T,n> PCurve<T, n>::getDer2( T t ) {

    _eval(t,2);
    return _p[2];
  }


  template <typename T, int n>
  inline
  std::string PCurve<T,n>::getIdentity() const {

    return "PCurve";
  }


  template <typename T, int n>
  inline
  T PCurve<T,n>::getLocalMapping( T t, T ts, T ti, T te ) {

    return t;
  }


  template <typename T, int n>
  inline
  T PCurve<T,n>::getParDelta()	{

    return _sc*( getEndP() - getStartP() );
  }


  template <typename T, int n>
  inline
  T PCurve<T,n>::getParEnd() {

    return getParStart() + getParDelta();
  }


  //template <typename T, int n>
  //inline
  //T PCurve<T, n>::getRadius( T t ) {
  //
  //  return 1.0/getCurvature(t);
  //}
  //
  //template <typename T, int n>
  //inline
  //T PCurve<T, n>::getSpeed( T t )		{
  //
  //  return getDer1(t).getLength();
  //}


  template <typename T, int n>
  inline
  T PCurve<T,n>::getParStart()	{

    return getStartP() + _tr;
  }


  template <typename T, int n>
  inline
  void PCurve<T, n>::resample( Array< Point<T, n> >& a, T eps ) {

    _sam = 0; _s_sam = 0; _e_sam = 1;
    T t, ddt, dp5 = getParDelta()/5;
    bool go_on=true;

    for( t = getParStart(); go_on; t += ddt ) {

      eval( t, 2 );
      a += _p[0];
      if ( a.getSize() > 7000 )
        break;

      T _r = _p[1] * _p[1];
      Vector<T,n> r = _p[2]-( (_p[2] * _p[1] ) / _r) * _p[1];
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


  template <typename T, int n>
  inline
  void PCurve<T, n>::resample( Array<Point<T,n> >& a, int m ) {

    _sam = m; _s_sam = 0; _e_sam = 1;
    T du = getParDelta() / ( m - 1 );
    a.setSize( m );

    for( int i = 0; i < m; i++ ) {

      eval( getParStart() + i * du, 0 );
      a[i] = _p[0];
    }

  }


  template <typename T, int n>
  inline
  void PCurve<T,n>::resample( Array<Point<T,n> >& a, int m, T start, T end ) {

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


  template <typename T, int n>
  inline
  void PCurve<T,n>::resample( DVector< DVector< Vector<T, n> > >& p, int m, int d, T start, T end ) {

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


  template <typename T, int n>
  inline
  void PCurve<T,n>::setDomain(T start, T end) {

    _sc = ( end - start );
    _tr= getStartP() + start;
  }


  template <typename T, int n>
  inline
  void PCurve<T,n>::setDomainScale( T sc ) {

    _sc = sc;
  }


  template <typename T, int n>
  inline
  void PCurve<T,n>::setDomainTrans( T tr ) {

    _tr = tr;
  }


  template <typename T, int n>
  inline
  void PCurve<T, n>::setEval( int d ) {

    _defalt_d = d;
  }


  template <typename T, int n>
  inline
  T PCurve<T,n>::shift( T t ) {

    return _tr + _sc * ( t - getStartP() );
  }


  template <typename T, int n>
  inline
  Point<T,n> PCurve<T,n>::operator()( T t )	{

    eval( t, _defalt_d );
    return ( Point<T,n> ) _p[0];
  }

}
