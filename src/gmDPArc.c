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



/*! \file gmDPArc.c
 *
 *  Implementation of the DPArc template class.
 *
 *  \date   2008-11-16
 */


namespace GMlib {


//  template <typename T>
//  inline
//  DPArc<T>::DPArc( T speed, T curvature ) : DCurve<T> ( new PArc<T, 3>( speed, curvature ) ) {
//
//    init();
//  }
//
//
//  template <typename T>
//  inline
//  DPArc<T>::DPArc( T speed, T curvature, T start, T end ) : DCurve<T>( new PArc<T, 3>( speed, curvature, start, end ) ) {
//
//    init();
//  }


  template <typename T>
  inline
  DPArc<T>::DPArc( T speed, T curvature ) {

    _delta = T(1);
    _s = speed;
    _c = curvature;

    _start = T(0);
    _end =  T( M_2PI );

    init();
  }


  template <typename T>
  inline
  DPArc<T>::DPArc( T speed, T curvature, T start, T end ) {

    _delta = T(1);
    _s = speed;
    _c = curvature;

    _start = start;
    _end = end;

    init();
  }


  template <typename T>
  inline
  DPArc<T>::DPArc( DVector< Vector<T,3> >& p, T s, T t, T e ) {

    _s = 1;
    _c = getCurvature( p );
    _delta = p[1].getLength();
    _start = (s-t)*_delta;
    _end = (e-t)*_delta;
//    this->setDomain( s, e );

    DVector< Vector<T,3> > xyz(3);
    xyz[0] = p[1] / _delta;
    xyz[1] = ( p[2] - ( xyz[0] * p[2] ) * xyz[0] ) / (_delta * _delta);

    if( xyz[1].getLength() > 1.0e-5 ) {
      xyz[1] = xyz[1] / xyz[1].getLength();
      xyz[2] = Vector3D<T>(xyz[1]) ^ xyz[0];

      GLMatrix bcmat( _matrix_arc.getTransposed().getPtr() );
      bcmat.basisChange( xyz[0], xyz[1], xyz[2], p[0] );
      for( int i = 0; i < 4; i++ )
        for( int j = 0; j < 4; j++ )
          _matrix_arc[i][j] = bcmat.get(j,i);
//      _matrix.basisChange( xyz[0], xyz[1], xyz[2], p[0] );
    }
    else {
      GLMatrix bcmat( _matrix_arc.getTransposed().getPtr() );
      bcmat.basisChange( xyz[0], Vector3D<T>( 0, 0, 0 ), Vector3D<T>( 0, 0, 0 ), p[0] );
      for( int i = 0; i < 4; i++ )
        for( int j = 0; j < 4; j++ )
          _matrix_arc[i][j] = bcmat.get(j,i);
//      _matrix.basisChange( xyz[0], Vector3D<T>( 0, 0, 0 ), Vector3D<T>( 0, 0, 0 ), p[0] );
    }

  }


  template <typename T>
  inline
  DPArc<T>::DPArc( const DPArc<T>& copy ) : DCurve<T>(copy) {


    _s = copy._s;
    _c = copy._c;

    _start = copy._start;
    _end = copy._end;

    init();
  }


//  template <typename T>
//  inline
//  DPArc<T>::DPArc( const PArc<T,3>& copy ) : DCurve<T>(copy) {
//
//    init();
//  }
//
//
//  template <typename T>
//  inline
//  DPArc<T>::DPArc( PArc<T,3>* copy ) : DCurve<T>(copy) {
//
//    _l_ref = copy;
//  }


  template <typename T>
  inline
  DPArc<T>::~DPArc() {}


//  template <typename T>
//  inline
//  PArc<T,3>* DPArc<T>::getPArc() {
//
//    return _l_ref;
//  }


  template <typename T>
  inline
  string DPArc<T>::getIdentity() const {

    return "DPArc";
  }


  template <typename T>
  void DPArc<T>::init() {

//    _l_ref = dynamic_cast<PArc<T,3>*>( this->_p_ref );
  }















  //////////////////////// PArc !!!!!!!!!!!!!! PArc ////////////////////////
  //////////////////////// PArc !!!!!!!!!!!!!! PArc ////////////////////////
  //////////////////////// PArc !!!!!!!!!!!!!! PArc ////////////////////////
  //////////////////////// PArc !!!!!!!!!!!!!! PArc ////////////////////////




  template <typename T>
  inline
  void DPArc<T>::eval( T t, int d, bool l ) {

    this->_p.setDim( d + 1 );

    if( _c == T(0) ) {

      this->_p[0][0] = _s * t;
      this->_p[0][1] = T(0);
      this->_p[0][2] = T(0);

      if( this->_dm == GM_DERIVATION_EXPLICIT ) {

        if( d > 0 ) {

          this->_p[1][0] = _s;
          this->_p[1][1] = T(0);
          this->_p[1][2] = T(0);
        }

        if( d > 1 ) {

          this->_p[2][0] = T(0);
          this->_p[2][1] = T(0);
          this->_p[2][2] = T(0);
        }
      }
    }
    else {

      const T oot = T(1)/_c;
      const T cst = _c*_s*t;

      this->_p[0][0] = oot * sin(cst);
      this->_p[0][1] = oot * ( 1 - cos(cst) );
      this->_p[0][2] = T(0);

      if( this->_dm == GM_DERIVATION_EXPLICIT ) {

        const T cs = _c*_s;

        if( d > 0 ) {

          this->_p[1][0] = oot * cs * cos(cst);
          this->_p[1][1] = oot * cs * sin(cst);
          this->_p[1][2] = T(0);
        }

        if( d > 1 ) {

          this->_p[2][0] = oot * cs * cs * -sin(cst);
          this->_p[2][1] = oot * cs * cs * cos(cst);
          this->_p[2][2] = T(0);
        }
      }
    }
    this->_p[0] = _matrix_arc * Point<T,3>(this->_p[0]);
    this->_p[1] = _matrix_arc * this->_p[1];
    this->_p[2] = _matrix_arc * this->_p[2];
  }


  template <typename T>
  inline
  T DPArc<T>::getEndP() {

    return _end;
  }


  template <typename T>
  inline
  T DPArc<T>::getCurvature() const {

    return _c;
  }


  template <typename T>
  inline
  T DPArc<T>::getCurvature( DVector< Vector<T,3> >& p ) {

    Vector<T,3> d1 = p[1];
    T a1= d1.getLength();

    if( a1 < T(1.0e-5) )
      return T(0);

    d1 /= a1;

    Vector<T,3> d2 = ( p[2] - ( d1 * p[2] ) * d1 ) / ( a1 * a1 );

    return d2.getLength();
  }


  template <typename T>
  inline
  T DPArc<T>::getLocalMapping( T t, T ts, T ti, T te ) {

    return ( t - ti ) * _delta;
  }


  template <typename T>
  inline
  T DPArc<T>::getSpeed() const {

    return _s;
  }


  template <typename T>
  inline
  T DPArc<T>::getStartP() {

    return _start;
  }


  template <typename T>
  inline
  bool DPArc<T>::isClosed() const {

    return (_end - _start) < 1e-7;
  }


  template <typename T>
  inline
  void DPArc<T>::setCurvature( T curvature ) {

      _c = curvature;
  }


  template <typename T>
  inline
  void DPArc<T>::setEnd( T end ) {

      _end = end;
  }


  template <typename T>
  inline
  void DPArc<T>::setSpeed( T speed ) {

      _s = speed;
  }


  template <typename T>
  inline
  void DPArc<T>::setStart( T start ) {

      _start = start;
  }
}

