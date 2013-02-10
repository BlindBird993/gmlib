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



/*! \file gmptriangle.c
 *
 *  Implementation of the PTriangle template class.
 */

// local
#include "visualizers/gmptriangledefaultvisualizer.h"


namespace GMlib {

  template <typename T>
  PTriangle<T>::PTriangle( int samples ) {

    _d      = -1;
    _no_sam  = samples;
    _init();
    setEval( 0 );

    _default_visualizer = new PTriangleDefaultVisualizer<T>();
    enableDefaultVisualizer( true );
  }

  template <typename T>
  PTriangle<T>::PTriangle( const PTriangle<T>& copy ) {

    _p            = copy._p;
    _n            = copy._n;
    _u            = copy._u;
    _v            = copy._v;
    _d           = copy._d;
    _all          = copy._all;

    for( int i = 0; i < 4; ++i ) _pt[i] = copy._pt[i];

    _default_d    = copy._default_d;

    _default_visualizer = new PTriangleDefaultVisualizer<T>();
    enableDefaultVisualizer( true );
  }

  template <typename T>
  PTriangle<T>::~PTriangle() {

    enableDefaultVisualizer( false );
    delete _default_visualizer;
  }

  template <typename T>
  inline
  void PTriangle<T>::_eval( T u, T v, int d )
  {
      if(!(u == _u && v == _v && d <= _d))
      {
          _u = u;
          _v = v;
          _d = d;
          eval(u, v, 1-u-v, d);
      }
  }


  template <typename T>
  inline
  int PTriangle<T>::_sum( int i ) {

    int r = 0;
    for(; i>0; i--) r += i;
    return r;
  }

  template <typename T>
  void PTriangle<T>::enableDefaultVisualizer( bool enable ) {

    if( !enable )
      removeVisualizer( _default_visualizer );
    else
      insertVisualizer( _default_visualizer );
  }

  template <typename T>
  inline
  const DVector<Vector<T,3> >& PTriangle<T>::evaluateGlobal( T u, T v, int d  )
  {
    static DVector<Vector<T,3> > p;

    _eval(u,v, d);
    p.setDim( _p.getDim() );

    p[0] = this->_present * (Point<T,3>)_p[0];

    for( int j = 1; j < p.getDim(); j++ )
      p[j] = this->_present * _p[j]; //  They are Vector<T,3> as default

    return p;
  }


  template <typename T>
  inline
  const DVector<Vector<T,3> >& PTriangle<T>::evaluateLocal( T u, T v, int d )
  {
    _eval(u, v, d);
    return _p;
  }


  template <typename T>
  inline
  const DVector<Vector<T,3> >& PTriangle<T>::evaluateParent( T u, T v, int d )
  {
    static DVector<Vector<T,3> > p;

    _eval(u, v, d);
    p.setDim( _p.getDim() );

    p[0] = this->_matrix * (Point<T,3>)_p[0];

    for( int j = 1; j < p.getDim(); j++ )
      p[j] = this->_matrix * _p[j]; //  They are Vector<T,3> as default

    return p;
  }


  template <typename T>
  void PTriangle<T>::_fuForm( T u, T v, T& E, T& F, T& G, T& e, T& f, T& g)
  {
    _eval( u, v, 2);
    Vector<T,3>     du = _p[2]-_p[1];
    Vector<T,3>     dv = _p[3]-_p[1];
    UnitVector<T,3> N  = du^dv;

    Vector<T,3>     duu = _p[6] - 2*_p[9] + _p[4];
    Vector<T,3>     duv = getDerUV(u,v);
    Vector<T,3>     dvv = _p[5] - 2*_p[8] + _p[4];

    E = du*du;
    F = du*dv;
    G = dv*dv;
    e = N*duu;
    f = N*duv;
    g = N*dvv;
  }



  template <typename T>
  T PTriangle<T>::getCurvatureGauss( T u, T v )
  {
     T E, F, G, e, f, g;

     _fuForm( u, v, E, F, G, e, f, g);

     return (e*g - f*f)/(E*G-F*F);
  }


  template <typename T>
  T PTriangle<T>::getCurvatureMean( T u, T v )
  {
     T E, F, G, e, f, g;

     _fuForm( u, v, E, F, G, e, f, g);

     return 0.5*(e*G-2*(f*F)+g*E)/(E*G-F*F);
  }


  template <typename T>
  inline
  const Vector<T,3>& PTriangle<T>::getDerU( T u, T v )
  {
    _eval(u,v,1);
    return _p[1];
  }

  template <typename T>
  inline
  const Vector<T,3>& PTriangle<T>::getDerV( T u, T v )
  {
    _eval(u,v,1);
    return _p[2];
  }

  template <typename T>
  inline
  const Vector<T,3>& PTriangle<T>::getDerW( T u, T v )
  {
    _eval(u,v,1);
    return _p[3];
  }


  template <typename T>
  inline
  const Vector<T,3>& PTriangle<T>::getDerUU( T u, T v ) {

    _eval(u,v,2);
    return _p[4];
  }


  template <typename T>
  inline
  const Vector<T,3>& PTriangle<T>::getDerUV( T u, T v ) {

    _eval(u,v,2);
    return _p[5];
  }

  template <typename T>
  inline
  const Vector<T,3>& PTriangle<T>::getDerUW( T u, T v ) {

    _eval(u,v,2);
    return _p[6];
  }


  template <typename T>
  inline
  const Vector<T,3>& PTriangle<T>::getDerVV( T u, T v ) {

    _eval(u,v,2);
    return _p[7];
  }

  template <typename T>
  inline
  const Vector<T,3>& PTriangle<T>::getDerVW( T u, T v ) {

    _eval(u,v,2);
    return _p[8];
  }

  template <typename T>
  inline
  const Vector<T,3>& PTriangle<T>::getDerWW( T u, T v ) {

    _eval(u,v,2);
    return _p[9];
  }



  template <typename T>
  std::string PTriangle<T>::getIdentity() const {

    return "PTriangle";
  }


  template <typename T>
  const Vector<T,3>& PTriangle<T>::getNormal( T u, T v ) {

    _eval(u, v, 1);
    _n = Vector<T,3>(_p[2]-_p[1])^(_p[3]-_p[1]);
    return _n;
  }


  template <typename T>
  UnitVector<T,3> PTriangle<T>::getUnitNormal( T u, T v ) {

    return getNormal( u, v );
  }

  template <typename T>
  inline
  void PTriangle<T>::insertVisualizer( Visualizer *visualizer ) {

    PTriangleVisualizer<T> *visu = dynamic_cast<PTriangleVisualizer<T>*>( visualizer );
    if( !visu )
      return;

    if( _ptriangle_visualizers.exist( visu ) )
      return;

    _ptriangle_visualizers += visu;

    DisplayObject::insertVisualizer( visualizer );
  }

  template <typename T>
  inline
  void PTriangle<T>::removeVisualizer( Visualizer *visualizer ) {

    PTriangleVisualizer<T> *visu = dynamic_cast<PTriangleVisualizer<T>*>( visualizer );
    if( visu )
      _ptriangle_visualizers.remove( visu );

    DisplayObject::removeVisualizer( visualizer );
  }


  template <typename T>
  bool PTriangle<T>::isClosestPoint( const Point<T,3>& q, T& u, T& v ) {

    T a11,a12,a21,a22,b1,b2;
    T du,dv,det;

    HqMatrix<float,3> invmat = this->_present;
    invmat.invertOrthoNormal();
    Point<T,3> p = invmat * q;  // Egentlig _present

    for(int i=0; i<20;i++) {

      _eval( u, v, 1 );

      Vector<T,3> d = p - _p[0];

      a11 = d*(_p[7]-2*_p[5]+_p[4])-(_p[2]-_p[1])*(_p[2]-_p[1]);
      a12 = d*(_p[8]-_p[6]-_p[5]+_p[4])-(_p[2]-_p[1])*(_p[3]-_p[1]);
      a21 = a12;
      a22 = d*(_p[9]-2*_p[6]+_p[4])-(_p[3]-_p[1])*(_p[3]-_p[1]);

      b1  = -(d*(_p[2]-_p[1]));
      b2  = -(d*(_p[3]-_p[1]));

      det = a11*a22-a12*a21;
      du  = (b1*a22-a12*b2)/det;
      dv  = (a11*b2-b1*a21)/det;
      if(fabs(du)< 1e-6 && fabs(dv) < 1e-6) break;
      u += du;
      v += dv;
    }
    return true;
  }

  template <typename T>
  inline
  void PTriangle<T>::replot( int m )
  {
    if( m < 2 )  m = _no_sam;
    else         _no_sam = m;

    // Sample Positions and related Derivatives
    DVector< DVector< Vector<T,3> > > p;
    resample( p, m );

    setSurroundingSphere( p );

    // Replot Visaulizers
    for( int i = 0; i < this->_ptriangle_visualizers.getSize(); i++ )
      this->_ptriangle_visualizers[i]->replot( p, m );
  }


  template <typename T>
  inline
  void PTriangle<T>::setTriangNr(bool all, int nr)
  {
      _all  = all;
      _t_nr = nr;
  }


  template <typename T>
  inline
  void PTriangle<T>::resample( DVector< DVector < Vector<T,3> > >& p, int m )
  {
    if(_all) resample1(p, m);
    else
    {
        if (_t_nr == 1) resample2(p, m, 1, 2);
        if (_t_nr == 2) resample2(p, m, 2, 3);
        if (_t_nr == 3) resample2(p, m, 3, 1);
    }
  }


  template <typename T>
  inline
  void PTriangle<T>::resample1( DVector< DVector < Vector<T,3> > >& p, int m )
  {
    T u,v,du = T(1)/(m-1);
    p.setDim(_sum(m));
    int i,j,k;
    for(k=0,i=0; i<m; i++) {
      for( j=0; j<=i; j++ )
      {
        v = j*du;
        u = (i-j)*du;
        eval(u, v, 1-u-v, 1);
        p[k++] = _p;
      }
    }
  }


  template <typename T>
  inline
  void PTriangle<T>::resample2( DVector< DVector < Vector<T,3> > >& p, int m, int a, int b)
  {
    T u,v,w,du = T(1)/(m-1);
    p.setDim(_sum(m));
    int i,j,k;
    for(k=0,i=0; i<m; i++) {
      for( j=0; j<=i; j++ )
      {
        v = j*du;
        u = i*du;
        w = 1 - u;
        u -= v;
        Point<T,3> pr = u*_pt[0] + v*_pt[a] + w*_pt[b];
        eval(pr, 1);
        p[k++] = _p;
      }
    }
  }


  template <typename T>
  inline
  void PTriangle<T>::_init() {
    T t= 1/3.0;
    _all = true;
    _pt[0] = Point<T,3>(t, t, t);
    _pt[1] = Point<T,3>(T(1), T(0), T(0));
    _pt[2] = Point<T,3>(T(0), T(1), T(0));
    _pt[3] = Point<T,3>(T(0), T(0), T(1));
  }


  template <typename T>
  inline
  void PTriangle<T>::setEval( int d ) {

    _default_d = d;
  }


  template <typename T>
  inline
  void PTriangle<T>::setSurroundingSphere( const DVector<DVector<Vector<T, 3> > >& p ) {

    Sphere<float,3>  s( (p(0)(0)).toFloat() );

    s += Point<float,3>( p( p.getDim()-1)(0) );
    for( int i = 1; i < p.getDim() - 1; i++ )
      s += Point<float,3>( p(i)(0) );

    Parametrics<T,2>::setSurroundingSphere(s);
  }


  template <typename T>
  inline
  Parametrics<T,2>* PTriangle<T>::split( T t, int uv ) {

    return 0x0;
  }

  template <typename T>
  void PTriangle<T>::toggleDefaultVisualizer() {

    if( !_ptriangle_visualizers.exist( _default_visualizer ) )
      enableDefaultVisualizer( true );
    else
      enableDefaultVisualizer( false );
  }

  template <typename T>
  inline
  void PTriangle<T>::updateCoeffs( const Vector<T,3>& /*d*/ ) {}


  template <typename T>
  inline
  const Point<T,3>& PTriangle<T>::operator()( T u, T v ) {

    _eval(u,v);
    return static_cast< Point<T,3> >( _p[0][0] );
  }


  template <typename T>
  inline
  const DVector<Vector<T,3> >&  PTriangle<T>::evaluateGlobal(const Point<T,3> & p, int d)
  {
      return  evaluateGlobal(p(0), p(1), d);
  }

  template <typename T>
  inline
  const DVector<Vector<T,3> >&  PTriangle<T>::evaluateLocal(const Point<T,3> & p, int d)
  {
      return  evaluateLocal(p(0), p(1), d);
  }

  template <typename T>
  inline
  const DVector<Vector<T,3> >&  PTriangle<T>::evaluateParent(const Point<T,3> & p, int d)
  {
      return  evaluateParent(p(0), p(1), d);
  }

  template <typename T>
  inline
  const Point<T,3>&             PTriangle<T>::operator()(const Point<T,3> & p)
  {
      return  operator()(p(0), p(1));
  }

  template <typename T>
  inline
  const Vector<T,3>&            PTriangle<T>::getDerU(const Point<T,3> & p)
  {
      return  getDerU(p(0), p(1));
  }

  template <typename T>
  inline
  const Vector<T,3>&            PTriangle<T>::getDerV(const Point<T,3> & p)
  {
      return  getDerV(p(0), p(1));
  }

  template <typename T>
  inline
  const Vector<T,3>&            PTriangle<T>::getDerW(const Point<T,3> & p)
  {
      return  getDerW(p(0), p(1));
  }

  template <typename T>
  inline
  const Vector<T,3>&            PTriangle<T>::getDerUU(const Point<T,3> & p)
  {
      return  getDerUU(p(0), p(1));
  }

  template <typename T>
  inline
  const Vector<T,3>&            PTriangle<T>::getDerUV(const Point<T,3> & p)
  {
      return  getDerUV(p(0), p(1));
  }

  template <typename T>
  inline
  const Vector<T,3>&            PTriangle<T>::getDerUW(const Point<T,3> & p)
  {
      return  getDerUW(p(0), p(1));
  }

  template <typename T>
  inline
  const Vector<T,3>&            PTriangle<T>::getDerVV(const Point<T,3> & p)
  {
      return  getDerVV(p(0), p(1));
  }

  template <typename T>
  inline
  const Vector<T,3>&            PTriangle<T>::getDerVW(const Point<T,3> & p)
  {
      return  getDerVW(p(0), p(1));
  }

  template <typename T>
  inline
  const Vector<T,3>&            PTriangle<T>::getDerWW(const Point<T,3> & p)
  {
      return  getDerWW(p(0), p(1));
  }

  template <typename T>
  inline
  const Vector<T,3>&            PTriangle<T>::getNormal(const Point<T,3> & p)
  {
      return  getNormal(p(0), p(1));
  }

  template <typename T>
  inline
  UnitVector<T,3>               PTriangle<T>::getUnitNormal(const Point<T,3> & p)
  {
      return  getUnitNormal(p(0), p(1));
  }

  template <typename T>
  inline
  T                             PTriangle<T>::getCurvatureGauss(const Point<T,3> & p)
  {
      return  getCurvatureGauss(p(0), p(1));
  }

  template <typename T>
  inline
  T                             PTriangle<T>::getCurvatureMean(const Point<T,3> & p)
  {
      return  getCurvatureMean(p(0), p(1));
  }


  template <typename T>
  inline
  const Vector<T,3>&            PTriangle<T>::getDer_d(const Point<T,3> & p, const Vector<T,3> & d)
  {
      eval(p, 1);
      return d[0]*_p[1] + d[1]*_p[2] + d[2]*_p[3];
  }


  template <typename T>
  Vector<Point<T,3>,3>          PTriangle<T>::getPoints()
  {
      Vector<Point<T,3>,3> a;

      return a;
  }


} // END namespace GMlib
