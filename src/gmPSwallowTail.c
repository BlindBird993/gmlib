
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



/*! \file gmPSwallowTail.c
 *
 *  Implementation of the PSwallowTail template class.
 *
 *  \date   2010-09-30
 */


namespace GMlib {


  template <typename T>
  inline
  PSwallowTail<T>::PSwallowTail() {

    init();
  }

  template <typename T>
  inline
  PSwallowTail<T>::PSwallowTail( const PSwallowTail<T>& copy ) : PSurf<T>( copy ) {

    init();
  }

  template <typename T>
  PSwallowTail<T>::~PSwallowTail() {}

  template <typename T>
  void PSwallowTail<T>::eval(T u, T v, int d1, int d2, bool /*lu*/, bool /*lv*/ ) {

    this->_p.setDim( d1+1, d2+1 );


    this->_p[0][0][0] =	u*v*v + T(3)*v*v*v*v;
    this->_p[0][0][1] =	-T(2)*u*v - T(4)*v*v*v;
    this->_p[0][0][2] =	u;


    if( this->_dm == GM_DERIVATION_EXPLICIT ) {

      if(d1) //u
      {
        this->_p[1][0][0] =	v*v;
        this->_p[1][0][1] =	-T(2)*v;
        this->_p[1][0][2] =	T(1);
      }
      if(d1>1)//uu
      {
        this->_p[2][0][0] =	T(0);
        this->_p[2][0][1] =	T(0);
        this->_p[2][0][2] =	T(0);
      }
      if(d2) //v
      {
        this->_p[0][1][0] =	2*u*v+12*v*v*v;
        this->_p[0][1][1] =	-2*u-12*v*v;
        this->_p[0][1][2] =	T(0);
      }
      if(d2>1) //vv
      {
        this->_p[0][2][0] =	T(2)*u+T(36)*v*v;
        this->_p[0][2][1] =	-T(24)*v;
        this->_p[0][2][2] =	T(0);
      }
      if(d1 && d2) //uv
      {
        this->_p[1][1][0] =	T(2)*v;
        this->_p[1][1][1] =	-T(2);
        this->_p[1][1][2] =	T(0);
      }
      if(d1>1 && d2)//uuv
      {
        this->_p[2][1][0] =	T(0);
        this->_p[2][1][1] =	T(0);
        this->_p[2][1][2] =	T(0);
      }
      if(d1 && d2>1) //uvv
      {
        this->_p[1][2][0] =	T(2);
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
  T PSwallowTail<T>::getEndPU() {

    return T(2);
  }


  template <typename T>
  inline
  T PSwallowTail<T>::getEndPV() {

    return T(0.8);
  }


  template <typename T>
  inline
  T PSwallowTail<T>::getStartPU() {

    return -T(2);
  }


  template <typename T>
  inline
  T PSwallowTail<T>::getStartPV() {

    return -T(0.8);
  }


  template <typename T>
  inline
  std::string PSwallowTail<T>::getIdentity() const {

    return "PSwallowTail";
  }


  template <typename T>
  void PSwallowTail<T>::init() {

    this->_dm = GM_DERIVATION_EXPLICIT;
  }


  template <typename T>
  inline
  bool PSwallowTail<T>::isClosedU() const {

    return false;
  }


  template <typename T>
  inline
  bool PSwallowTail<T>::isClosedV() const {

    return false;
  }

} // END namespace GMlib
