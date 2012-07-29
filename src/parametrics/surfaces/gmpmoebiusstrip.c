
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



/*! \file gmpmoebiusstrip.c
 *
 *  Implementation of the PMoebiusStrip template class.
 */


namespace GMlib {


  template <typename T>
  inline
  PMoebiusStrip<T>::PMoebiusStrip( T radius, T width ) {

    init();

    _r = radius;
    _w = width;
  }


  template <typename T>
  inline
  PMoebiusStrip<T>::PMoebiusStrip( const PMoebiusStrip<T>& copy ) : PSurf<T>( copy ) {

    init();

    _r = copy._r;
    _w = copy._w;
  }



  template <typename T>
  PMoebiusStrip<T>::~PMoebiusStrip() {}


  template <typename T>
  void PMoebiusStrip<T>::eval(T u, T v, int d1, int d2, bool /*lu*/, bool /*lv*/ ) {

    this->_p.setDim( d1+1, d2+1 );


    this->_p[0][0][0] =	(_r+_w*u*cos(T(.5)*v))*cos(v);
    this->_p[0][0][1] =	(_r+_w*u*cos(T(.5)*v))*sin(v);
    this->_p[0][0][2] =	_w*u*sin(T(.5)*v);


    if( this->_dm == GM_DERIVATION_EXPLICIT ) {

      if(d1) //u
      {
        this->_p[1][0][0] =		_w*cos(T(.5)*v)*cos(v);
        this->_p[1][0][1] =		_w*cos(T(.5)*v)*sin(v);
        this->_p[1][0][2] =		_w*sin(T(.5)*v);
      }
      if(d1>1)//uu
      {
        this->_p[2][0][0] =	T(0);
        this->_p[2][0][1] =	T(0);
        this->_p[2][0][2] =	T(0);
      }
      if(d2) //v
      {
        this->_p[0][1][0] =	-_w*u*sin(T(.5)*v)*T(.5)*cos(v)-sin(v)*_r-sin(v)*_w*u*cos(T(.5)*v);
        this->_p[0][1][1] =	-_w*u*sin(T(.5)*v)*T(.5)*sin(v)+cos(v)*_r+cos(v)*_w*u*cos(T(.5)*v);
        this->_p[0][1][2] =	_w*u*cos(T(.5)*v)*T(.5);
      }
      if(d2>1) //vv
      {
        this->_p[0][2][0] =	-_w*u*cos(T(.5)*v)*T(.25)*cos(v)
                +2.0*_w*u*sin(T(.5)*v)*T(.5)*sin(v)-cos(v)*_r-cos(v)*_w*u*cos(T(.5)*v);
        this->_p[0][2][1] =	-_w*u*cos(T(.5)*v)*T(.25)*sin(v)
                -2.0*_w*u*sin(T(.5)*v)*T(.5)*cos(v)-sin(v)*_r-sin(v)*_w*u*cos(T(.5)*v);
        this->_p[0][2][2] =	-_w*u*sin(T(.5)*v)*T(.25);
      }
      if(d1 && d2) //uv
      {
        this->_p[1][1][0] =	-_w*(sin(T(.5)*v)*T(.5)*cos(v)+cos(T(.5)*v)*sin(v));
        this->_p[1][1][1] =	-_w*(sin(T(.5)*v)*T(.5)*sin(v)-cos(T(.5)*v)*cos(v));
        this->_p[1][1][2] =	_w*cos(T(.5)*v)*T(.5);
      }
      if(d1>1 && d2)//uuv
      {
        this->_p[2][1][0] =		T(0);
        this->_p[2][1][1] =		T(0);
        this->_p[2][1][2] =		T(0);
      }
      if(d1 && d2>1) //uvv
      {
        this->_p[1][2][0] =	-_w*(cos(T(.5)*v)*T(.25)*cos(v)-2.0*sin(T(.5)*v)*T(.5)*sin(v)+cos(T(.5)*v)*cos(v));
        this->_p[1][2][1] =	-_w*(cos(T(.5)*v)*T(.25)*sin(v)+2.0*sin(T(.5)*v)*T(.5)*cos(v)+cos(T(.5)*v)*sin(v));
        this->_p[1][2][2] =	-_w*sin(T(.5)*v)*T(.25);
      }
      if(d1>1 && d2>1) //uuvv
      {
        this->_p[2][2][0] =		T(0);
        this->_p[2][2][1] =		T(0);
        this->_p[2][2][2] =		T(0);
      }
    }
  }


  template <typename T>
  inline
  T PMoebiusStrip<T>::getEndPU() {

    return T(1);
  }


  template <typename T>
  inline
  T PMoebiusStrip<T>::getEndPV() {

    return T(1.5*M_PI);
  }


  template <typename T>
  inline
  T PMoebiusStrip<T>::getStartPU() {

    return -T(1);
  }


  template <typename T>
  inline
  T PMoebiusStrip<T>::getStartPV() {

    return -T(0.5*M_PI);
  }


  template <typename T>
  inline
  std::string PMoebiusStrip<T>::getIdentity() const {

    return "PMoebiusStrip";
  }


  template <typename T>
  void PMoebiusStrip<T>::init() {

    this->_dm = GM_DERIVATION_EXPLICIT;
  }


  template <typename T>
  inline
  bool PMoebiusStrip<T>::isClosedU() const {

    return false;
  }


  template <typename T>
  inline
  bool PMoebiusStrip<T>::isClosedV() const {

    return false;
  }

} // END namespace GMlib
