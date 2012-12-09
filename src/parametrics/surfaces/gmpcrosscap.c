
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
  PCrossCap<T>::PCrossCap( const PCrossCap<T>& copy ) : PSurf<T>( copy ) {

    init();

    _r = copy._r;
  }



  template <typename T>
  PCrossCap<T>::~PCrossCap() {}


  template <typename T>
  void PCrossCap<T>::eval(T u, T v, int d1, int d2, bool /*lu*/, bool /*lv*/ ) {

    this->_p.setDim( d1+1, d2+1 );


    this->_p[0][0][0] =	_r*_r*cos(v)*sin(u)*sin(v);
    this->_p[0][0][1] =	_r*_r*cos(v)*cos(v)*sin(2*u);
    this->_p[0][0][2] =	_r*_r*cos(2*u)*cos(v)*cos(v);


    if( this->_dm == GM_DERIVATION_EXPLICIT ) {

      if(d1) //u
      {
        this->_p[1][0][0] =	_r*_r*cos(v)*cos(u)*sin(v);
        this->_p[1][0][1] =	2.0*_r*_r*cos(v)*cos(v)*cos(2*u);
        this->_p[1][0][2] =	-2.0*_r*_r*cos(v)*cos(v)*sin(2*u);
      }
      if(d1>1)//uu
      {
        this->_p[2][0][0] =	 -_r*_r*cos(v)*sin(u)*sin(v);
        this->_p[2][0][1] =	 -4.0*_r*_r*cos(v)*cos(v)*sin(2.0*u);
        this->_p[2][0][2] =	-4.0*_r*_r*cos(2.0*u)*cos(v)*cos(v);
      }
      if(d2) //v
      {
        this->_p[0][1][0] =	-_r*_r*sin(v)*sin(v)*sin(u)+_r*_r*cos(v)*cos(v)*sin(u);
        this->_p[0][1][1] =	-2.0*_r*_r*cos(v)*sin(2*u)*sin(v);
        this->_p[0][1][2] =	-2.0*_r*_r*cos(v)*cos(2*u)*sin(v);
      }
      if(d2>1) //vv
      {
        this->_p[0][2][0] =	 -4.0*_r*_r*cos(v)*sin(u)*sin(v);
        this->_p[0][2][1] =	2.0*_r*_r*sin(v)*sin(v)*sin(2.0*u)-2.0*_r*_r*cos(v)*cos(v)*sin(2.0*u);
        this->_p[0][2][2] =	2.0*_r*_r*cos(2.0*u)*sin(v)*sin(v)-2.0*_r*_r*cos(2.0*u)*cos(v)*cos(v);
      }
      if(d1 && d2) //uv
      {
        this->_p[1][1][0] =	-_r*_r*sin(v)*sin(v)*cos(u)+_r*_r*cos(v)*cos(v)*cos(u);
        this->_p[1][1][1] =	 -4.0*_r*_r*cos(2.0*u)*cos(v)*sin(v);
        this->_p[1][1][2] =	 4.0*_r*_r*cos(v)*sin(2.0*u)*sin(v);
      }
      if(d1>1 && d2)//uuv
      {
        this->_p[2][1][0] =	 _r*_r*sin(v)*sin(v)*sin(u)-_r*_r*cos(v)*cos(v)*sin(u);
        this->_p[2][1][1] =	  8.0*_r*_r*cos(v)*sin(2.0*u)*sin(v);
        this->_p[2][1][2] =	 8.0*_r*_r*cos(2.0*u)*cos(v)*sin(v);
      }
      if(d1 && d2>1) //uvv
      {
        this->_p[1][2][0] =	-4.0*_r*_r*cos(v)*cos(u)*sin(v);
        this->_p[1][2][1] =	 4.0*_r*_r*cos(2.0*u)*sin(v)*sin(v)-4.0*_r*_r*cos(2.0*u)*cos(v)*cos(v);
        this->_p[1][2][2] =	-4.0*_r*_r*sin(v)*sin(v)*sin(2.0*u)+4.0*_r*_r*cos(v)*cos(v)*sin(2.0*u);
      }
      if(d1>1 && d2>1) //uuvv
      {
        this->_p[2][2][0] =	 4.0*_r*_r*cos(v)*sin(u)*sin(v);
        this->_p[2][2][1] =	 -8.0*_r*_r*sin(v)*sin(v)*sin(2.0*u)+8.0*_r*_r*cos(v)*cos(v)*sin(2.0*u);
        this->_p[2][2][2] =	 -8.0*_r*_r*cos(2.0*u)*sin(v)*sin(v)+8.0*_r*_r*cos(2.0*u)*cos(v)*cos(v);
      }
    }
  }


  template <typename T>
  inline
  T PCrossCap<T>::getEndPU() {

    return T(2 * M_PI);
  }


  template <typename T>
  inline
  T PCrossCap<T>::getEndPV() {

    return T(2 * M_PI);
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
