
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



/*! \file gmpcrosscap.c
 *
 *  Implementation of the PCrossCap template class.
 */


namespace GMlib {


  template <typename T>
  inline
  PCrossCap<T>::PCrossCap( T radius ) {

    init();

    _r = radius;
  }


  template <typename T>
  inline
  PCrossCap<T>::PCrossCap( const PCrossCap<T>& copy ) : PSurf<T,3>( copy ) {

    init();

    _r = copy._r;
  }



  template <typename T>
  PCrossCap<T>::~PCrossCap() {}


  template <typename T>
  void PCrossCap<T>::eval(T u, T v, int d1, int d2, bool /*lu*/, bool /*lv*/ ) {

    this->_p.setDim( d1+1, d2+1 );

    this->_p[0][0][0] =	_r*_r*cos(u)*sin(v)*sin(u);
    this->_p[0][0][1] =	_r*_r*cos(u)*cos(u)*sin(2*v);
    this->_p[0][0][2] =	_r*_r*cos(2*v)*cos(u)*cos(u);

    if( this->_dm == GM_DERIVATION_EXPLICIT ) {

      if(d1) //u
      {
        this->_p[1][0][0] =	-_r*_r*sin(u)*sin(u)*sin(v)+_r*_r*cos(u)*cos(u)*sin(v);
        this->_p[1][0][1] =	-2.0*_r*_r*cos(u)*sin(2*v)*sin(u);
        this->_p[1][0][2] =	-2.0*_r*_r*cos(u)*cos(2*v)*sin(u);
      }
      if(d1>1)//uu
      {
        this->_p[2][0][0] =	 -4.0*_r*_r*cos(u)*sin(v)*sin(u);
        this->_p[2][0][1] =	2.0*_r*_r*sin(u)*sin(u)*sin(2.0*v)-2.0*_r*_r*cos(u)*cos(u)*sin(2.0*v);
        this->_p[2][0][2] =	2.0*_r*_r*cos(2.0*v)*sin(u)*sin(u)-2.0*_r*_r*cos(2.0*v)*cos(u)*cos(u);
      }
      if(d2) //v
      {
        this->_p[0][1][0] =	_r*_r*cos(u)*cos(v)*sin(u);
        this->_p[0][1][1] =	2.0*_r*_r*cos(u)*cos(u)*cos(2*v);
        this->_p[0][1][2] =	-2.0*_r*_r*cos(u)*cos(u)*sin(2*v);
      }
      if(d2>1) //vv
      {
        this->_p[0][2][0] =	 -_r*_r*cos(u)*sin(v)*sin(u);
        this->_p[0][2][1] =	 -4.0*_r*_r*cos(u)*cos(u)*sin(2.0*v);
        this->_p[0][2][2] =	-4.0*_r*_r*cos(2.0*v)*cos(u)*cos(u);
      }
      if(d1 && d2) //uv
      {
        this->_p[1][1][0] =	-_r*_r*sin(u)*sin(u)*cos(v)+_r*_r*cos(u)*cos(u)*cos(v);
        this->_p[1][1][1] =	 -4.0*_r*_r*cos(2.0*v)*cos(u)*sin(u);
        this->_p[1][1][2] =	 4.0*_r*_r*cos(u)*sin(2.0*v)*sin(u);
      }
      if(d1>1 && d2)//uuv
      {
        this->_p[2][1][0] =	-4.0*_r*_r*cos(u)*cos(v)*sin(u);
        this->_p[2][1][1] =	 4.0*_r*_r*cos(2.0*v)*sin(u)*sin(u)-4.0*_r*_r*cos(2.0*v)*cos(u)*cos(u);
        this->_p[2][1][2] =	-4.0*_r*_r*sin(u)*sin(u)*sin(2.0*v)+4.0*_r*_r*cos(u)*cos(u)*sin(2.0*v);
      }
      if(d1 && d2>1) //uvv
      {
        this->_p[1][2][0] =	 _r*_r*sin(u)*sin(u)*sin(v)-_r*_r*cos(u)*cos(u)*sin(v);
        this->_p[1][2][1] =	  8.0*_r*_r*cos(u)*sin(2.0*v)*sin(u);
        this->_p[1][2][2] =	 8.0*_r*_r*cos(2.0*v)*cos(u)*sin(u);
      }
      if(d1>1 && d2>1) //uuvv
      {
        this->_p[2][2][0] =	 4.0*_r*_r*cos(u)*sin(v)*sin(u);
        this->_p[2][2][1] =	 -8.0*_r*_r*sin(u)*sin(u)*sin(2.0*v)+8.0*_r*_r*cos(u)*cos(u)*sin(2.0*v);
        this->_p[2][2][2] =	 -8.0*_r*_r*cos(2.0*v)*sin(u)*sin(u)+8.0*_r*_r*cos(2.0*v)*cos(u)*cos(u);
      }
    }
  }


  template <typename T>
  inline
  T PCrossCap<T>::getEndPU() {

    return T(/*2 */ M_PI);
  }


  template <typename T>
  inline
  T PCrossCap<T>::getEndPV() {

    return T(/*2 */ M_PI);
  }


  template <typename T>
  inline
  T PCrossCap<T>::getStartPU() {

    return T(0);
  }


  template <typename T>
  inline
  T PCrossCap<T>::getStartPV() {

    return T(0);
  }


  template <typename T>
  void PCrossCap<T>::init() {

    this->_dm = GM_DERIVATION_EXPLICIT;
  }


  template <typename T>
  inline
  bool PCrossCap<T>::isClosedU() const {

    return false;
  }


  template <typename T>
  inline
  bool PCrossCap<T>::isClosedV() const {

    return false;
  }

} // END namespace GMlib
