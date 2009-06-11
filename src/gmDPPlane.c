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



/*! \file gmDPPlane.c
 *
 *  Implementation of the gmDPPlane template class.
 *
 *  \date   2008-09-06
 */


namespace GMlib {

//  template <typename T>
//  inline
//  DPPlane<T>::DPPlane( const Point<T,3>& p, const Vector<T,3>& u, const Vector<T,3>& v ) : DSurf<T>( new PPlane<T,3>( 0.0, u, v ) ) {
//
//    translate( p.toFloat() );
//    init();
//  }

  template <typename T>
  inline
  DPPlane<T>::DPPlane( const Point<T,3>& p, const Vector<T,3>& u, const Vector<T,3>& v ) {

//    translate( p.toFloat() );
    init();


    /////////////// PPLANE /////////////////

    _pt = p;
    _u = u;
    _v = v;

    _n = Vector3D<T>(u)^v;

    this->_dm = GM_DERIVATION_EXPLICIT;
  }


  template <typename T>
  inline
  DPPlane<T>::DPPlane( const DPPlane<T>& copy ) : DSurf<T>( copy ) {

    init();


    /////////////// PPLANE /////////////////

    _pt   = copy._pt;
    _u    = copy._u;
    _v    = copy._v;
    _n    = copy._n;
  }


//  template <typename T>
//  inline
//  DPPlane<T>::DPPlane( const PPlane<T,3>& pplane ) : DSurf<T>( pplane ) {
//
//    init();
//  }


  template <typename T>
  DPPlane<T>::~DPPlane() {}


//  template <typename T>
//  inline
//  const UnitVector<T,3>& DPPlane<T>::getNormal() {
//
//    return getPPlane()->getNormal();
//  }

//  template <typename T>
//  inline
//  PPlane<T,3>* DPPlane<T>::getPPlane() {
//
//    return _l_ref;
//  }

  template <typename T>
  inline
  std::string DPPlane<T>::getIdentity() const {

    return "DPPlane";
  }


  template <typename T>
  void DPPlane<T>::init() {

//    _l_ref = dynamic_cast<PPlane<T,3>*>( this->_p_ref );
  }










  //////////////////////// PPlane !!!!!!!!!!!!!! PPlane ////////////////////////
  //////////////////////// PPlane !!!!!!!!!!!!!! PPlane ////////////////////////
  //////////////////////// PPlane !!!!!!!!!!!!!! PPlane ////////////////////////
  //////////////////////// PPlane !!!!!!!!!!!!!! PPlane ////////////////////////





  template <typename T>
  inline
  const UnitVector<T,3>& DPPlane<T>::getNormal() const {

    return _n;
  }

  template <typename T>
  void DPPlane<T>::eval(T u, T v, int d1, int d2, bool /*lu*/, bool /*lv*/ ) {

    this->_p[0][0] = _pt + u*_u + v*_v ;

    if( this->_dm == GM_DERIVATION_EXPLICIT ) {

      if(d1) {

        this->_p[1][0] = _u;	// S_u
      }
      if(d2) {

        this->_p[0][1] = _v;	// S_v
      }
      if(d1>1) {

        this->_p[2][0][0] = T(0);	// S_uu
        this->_p[2][0][1] = T(0);
        this->_p[2][0][2] = T(0);
      }
      if(d1>1 && d2>1) {

        this->_p[1][1][0] = T(0);	// S_uv
        this->_p[1][1][1] = T(0);
        this->_p[1][1][2] = T(0);
      }
      if(d2>1) {

        this->_p[0][2][0] = T(0);	// S_vv
        this->_p[0][2][1] = T(0);
        this->_p[0][2][2] = T(0);
      }
      if(d1>2) {

        this->_p[3][0][0] = T(0);	// S_uuu
        this->_p[3][0][1] = T(0);
        this->_p[3][0][2] = T(0);
      }
      if(d1>2 && d2>2) {

        this->_p[1][2][0] = T(0);	// S_uuv
        this->_p[1][2][1] = T(0);
        this->_p[1][2][2] = T(0);
      }
      if(d1>2 && d2>2) {

        this->_p[2][1][0] = T(0);	// S_uvv
        this->_p[2][1][1] = T(0);
        this->_p[2][1][2] = T(0);
      }
      if(d2>2) {

        this->_p[0][3][0] = T(0);	// S_vvv
        this->_p[0][3][1] = T(0);
        this->_p[0][3][2] = T(0);
      }
    }
  }


  template <typename T>
  inline
  T DPPlane<T>::getEndPU()	{

    return T(1);
  }

  template <typename T>
  inline
  T DPPlane<T>::getEndPV()	{

    return T(1);
  }


  template <typename T>
  inline
  T DPPlane<T>::getStartPU() {

    return T(0);
  }


  template <typename T>
  inline
  T DPPlane<T>::getStartPV() {

    return T(0);
  }


  template <typename T>
  inline
  const Vector<T,3>& DPPlane<T>::getU() const {

    return _u;
  }


  template <typename T>
  inline
  const Vector<T,3>& DPPlane<T>::getV() const {

    return _v;
  }


  template <typename T>
  inline
  bool DPPlane<T>::isClosedU() const {

    return false;
  }


  template <typename T>
  inline
  bool DPPlane<T>::isClosedV() const {

    return false;
  }


  template <typename T>
  inline
  void DPPlane<T>::setU( const Vector<T,3>& u ) {

    _u = u;
  }


  template <typename T>
  inline
  void DPPlane<T>::setV( const Vector<T,3>& v ) {

    _v = v;
  }
}
