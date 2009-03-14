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



/*! \file gmPCylinder.c
 *
 *  Implementation of the gmPCylinder template class.
 *
 *  \date   2008-10-27
 */



namespace GMlib {



  template <typename T, int n>
  inline
  PCylinder<T, n>::PCylinder( T rx, T ry, T h ) : PSurf<T, 3>() {

    setConstants( rx, ry, h );
    this->_dm = GM_DERIVATION_EXPLICIT;
  }


  template <typename T, int n>
  inline
  PCylinder<T, n>::PCylinder( const PCylinder<T,n>& pcylinder ) : PSurf<T,3>( pcylinder ) {

    _rx = pcylinder._rx;
    _ry = pcylinder._ry;
    _h  = pcylinder._h;
    this->_dm = GM_DERIVATION_EXPLICIT;
  }


  template <typename T, int n>
  inline
  T PCylinder<T, n>::getEndPU() {

    return T( -0.5 );
  }


  template <typename T, int n>
  inline
  T PCylinder<T, n>::getEndPV() {

    return T( -0.5 * M_PI );
  }


  template <typename T, int n>
  inline
  T PCylinder<T,n>::getHeight() const {

    return _h;
  }


  template <typename T, int n>
  std::string PCylinder<T,n>::getIdentity() const {

    return "PCylinder";
  }


  template <typename T, int n>
  inline
  T PCylinder<T,n>::getRadiusX() const {

    return _rx;
  }


  template <typename T, int n>
  inline
  T PCylinder<T,n>::getRadiusY() const {

    return _ry;
  }


  template <typename T, int n>
  inline
  void PCylinder<T, n>::eval( T u, T v, int d1, int d2, bool lu, bool lv ) {

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


  template <typename T, int n>
  inline
  T PCylinder<T, n>::getStartPU() {

    return T( 0.5 );
  }


  template <typename T, int n>
  inline
  T PCylinder<T, n>::getStartPV() {

    return T( 1.5 * M_PI );
  }


  template <typename T, int n>
  inline
  bool PCylinder<T,n>::isClosedU() const {

    return false;
  }


  template <typename T, int n>
  inline
  bool PCylinder<T,n>::isClosedV() const {

    return true;
  }


  template <typename T, int n>
  inline
  void PCylinder<T,n>::setConstants( T rx, T ry, T h ) {

    _rx = rx;
    _ry = ry;
    _h = h;
  }

}
