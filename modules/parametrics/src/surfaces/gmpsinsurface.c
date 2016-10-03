
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





namespace GMlib {


  template <typename T>
  inline
  PSinSurface<T>::PSinSurface( T radius ) {

    init();

    _r = radius;
  }


  template <typename T>
  inline
  PSinSurface<T>::PSinSurface( const PSinSurface<T>& copy ) : PSurf<T,3>( copy ) {

    init();

    _r = copy._r;
  }



  template <typename T>
  PSinSurface<T>::~PSinSurface() {}


  template <typename T>
  void PSinSurface<T>::eval(T u, T v, int d1, int d2, bool /*lu*/, bool /*lv*/ ) {

    this->_p.setDim( d1+1, d2+1 );


    //	S(u,v)
    this->_p[0][0][0] =	_r*sin(u);
    this->_p[0][0][1] =	_r*sin(v);
    this->_p[0][0][2] =	_r*sin(v+u);


    if( this->_dm == GM_DERIVATION_EXPLICIT ) {

      if(d1) //u
      {
        this->_p[1][0][0] =	_r*cos(u);
        this->_p[1][0][1] =	0.0;
        this->_p[1][0][2] =	_r*cos(v+u);
      }
      if(d1>1) //uu
      {
        this->_p[2][0][0] =	-_r*sin(u);
        this->_p[2][0][1] =	0.0;
        this->_p[2][0][2] =	-_r*sin(v+u);
      }
      if(d2) //v
      {
        this->_p[0][1][0] =	0.0;
        this->_p[0][1][1] =	_r*cos(v);
        this->_p[0][1][2] =	_r*cos(v+u);
      }
      if(d2>1) //vv
      {
        this->_p[0][2][0] =	0.0;
        this->_p[0][2][1] =	-_r*sin(v);
        this->_p[0][2][2] =	-_r*sin(v+u);
      }
      if(d1 && d2) //uv
      {
        this->_p[1][1][0] =	0.0;
        this->_p[1][1][1] =	0.0;
        this->_p[1][1][2] =	-_r*sin(v+u);
      }
      if(d1>1 && d2) //uuv
      {
        this->_p[2][1][0] =	0.0;
        this->_p[2][1][1] =	0.0;
        this->_p[2][1][2] =	-_r*cos(v+u);
      }
      if(d1 && d2>1) //uvv
      {
        this->_p[1][2][0] =	0.0;
        this->_p[1][2][1] =	0.0;
        this->_p[1][2][2] =	-_r*cos(v+u);
      }
      if(d1>1 && d2>1) //uuvv
      {
        this->_p[2][2][0] =	0.0;
        this->_p[2][2][1] =	0.0;
        this->_p[2][2][2] =	_r*sin(v+u);
      }
    }
  }


  template <typename T>
  inline
  T PSinSurface<T>::getEndPU() {

    return T(2 * M_PI);
  }


  template <typename T>
  inline
  T PSinSurface<T>::getEndPV() {

    return T(2 * M_PI);
  }


  template <typename T>
  inline
  T PSinSurface<T>::getStartPU() {

    return T(0);
  }


  template <typename T>
  inline
  T PSinSurface<T>::getStartPV() {

    return T(0);
  }


  template <typename T>
  void PSinSurface<T>::init() {

    this->_dm = GM_DERIVATION_EXPLICIT;
  }


  template <typename T>
  inline
  bool PSinSurface<T>::isClosedU() const {

    return false;
  }


  template <typename T>
  inline
  bool PSinSurface<T>::isClosedV() const {

    return false;
  }

} // END namespace GMlib
