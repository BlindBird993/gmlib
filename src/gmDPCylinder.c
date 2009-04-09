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



/*! \file gmDPApple.c
 *
 *  Implementation of the gmDPApple template class.
 *
 *  \date   2008-09-07
 */


namespace GMlib {


//  template <typename T>
//  inline
//  DPCylinder<T>::DPCylinder( T rx, T ry, T h ) : DSurf<T>( new PCylinder<T,3>( rx, ry, h ) ) {
//
//    init();
//  }


  template <typename T>
  inline
  DPCylinder<T>::DPCylinder( T rx, T ry, T h ) {

    init();

    setConstants( rx, ry, h );
    this->_dm = GM_DERIVATION_EXPLICIT;
  }


  template <typename T>
  inline
  DPCylinder<T>::DPCylinder( const DPCylinder<T>& copy ) : DCurve<T>(copy) {

    init();

    _rx = copy._rx;
    _ry = copy._ry;
    _h  = copy._h;
    this->_dm = GM_DERIVATION_EXPLICIT;
  }


//  template <typename T>
//  inline
//  DPCylinder<T>::DPCylinder( const PCylinder<T,3>& pcylinder ) : DCurve<T>(pcylinder) {
//
//    init();
//  }
//
//
//  template <typename T>
//  inline
//  DPCylinder<T>::DPCylinder( PCylinder<T,3> *copy ) : DSurf<T>( copy ){
//
//    _l_ref = copy;
//  }


  template <typename T>
  inline
  DPCylinder<T>::~DPCylinder() {}


  template <typename T>
  inline
  std::string DPCylinder<T>::getIdentity() const {

    return "DPCylinder";
  }


//  template <typename T>
//  inline
//  PCylinder<T,3>* DPCylinder<T>::getPCylinder() {
//
//    return _l_ref;
//  }


//  template <typename T>
//  inline
//  const PCylinder<T,3>* const DPCylinder<T>::getPCylinder() const {
//
//    return _l_ref;
//  }


  template <typename T>
  inline
  void DPCylinder<T>::init() {

//    _l_ref = dynamic_cast<PCylinder<T,3>*>( this->_p_ref );
  }




  //////////////////////// PCylinder !!!!!!!!!!!!!! PCylinder ////////////////////////
  //////////////////////// PCylinder !!!!!!!!!!!!!! PCylinder ////////////////////////
  //////////////////////// PCylinder !!!!!!!!!!!!!! PCylinder ////////////////////////
  //////////////////////// PCylinder !!!!!!!!!!!!!! PCylinder ////////////////////////


  template <typename T>
  inline
  T DPCylinder<T>::getEndPU() {

    return T( -0.5 );
  }


  template <typename T>
  inline
  T DPCylinder<T>::getEndPV() {

    return T( -0.5 * M_PI );
  }


  template <typename T>
  inline
  T DPCylinder<T>::getHeight() const {

    return _h;
  }


  template <typename T>
  inline
  T DPCylinder<T>::getRadiusX() const {

    return _rx;
  }


  template <typename T>
  inline
  T DPCylinder<T>::getRadiusY() const {

    return _ry;
  }


  template <typename T>
  inline
  void DPCylinder<T>::eval( T u, T v, int d1, int d2, bool lu, bool lv ) {

    this->_p[0][0][0] =		_rx * sin( v );
    this->_p[0][0][1] =		_ry * cos( v );
    this->_p[0][0][2] =		_h * u;

    if( this->_dm == GM_DERIVATION_EXPLICIT ) {

      if(d1) //u
      {
        this->_p[1][0][0] =	T(0);
        this->_p[1][0][1] =	T(0);
        this->_p[1][0][2] =	_h;
      }
      if(d1>1)//uu
      {
        this->_p[2][0][0] =	T(0);
        this->_p[2][0][1] =	T(0);
        this->_p[2][0][2] =	T(0);
      }
      if(d2) //v
      {
        this->_p[0][1][0] = _ry * cos(v);
        this->_p[0][1][1] = -_rx *sin(v);
        this->_p[0][1][2] =	T(0);
      }
      if(d2>1) //vv
      {
        this->_p[0][2][0] = -_ry * sin(v);
        this->_p[0][2][1] =	-_rx * cos(v);
        this->_p[0][2][2] =	T(0);
      }
      if(d1 && d2) //uv
      {
        this->_p[1][1][0] =	T(0);
        this->_p[1][1][1] =	T(0);
        this->_p[1][1][2] =	T(0);
      }
      if(d1>1 && d2)//uuv
      {
        this->_p[2][1][0] = T(0);
        this->_p[2][1][1] = T(0);
        this->_p[2][1][2] = T(0);
      }
      if(d1 && d2>1) //uvv
      {
        this->_p[1][2][0] =	T(0);
        this->_p[1][2][1] =	T(0);
        this->_p[1][2][2] =	T(0);
      }
      if(d1>1 && d2>1) //uuvv
      {
        this->_p[2][2][0] =	T(0);
        this->_p[2][2][1] =	T(0);
        this->_p[2][2][2] =	T(0);
      }
    }
  }


  template <typename T>
  inline
  T DPCylinder<T>::getStartPU() {

    return T( 0.5 );
  }


  template <typename T>
  inline
  T DPCylinder<T>::getStartPV() {

    return T( 1.5 * M_PI );
  }


  template <typename T>
  inline
  bool DPCylinder<T>::isClosedU() const {

    return false;
  }


  template <typename T>
  inline
  bool DPCylinder<T>::isClosedV() const {

    return true;
  }


  template <typename T>
  inline
  void DPCylinder<T>::setConstants( T rx, T ry, T h ) {

    _rx = rx;
    _ry = ry;
    _h = h;
  }
}

