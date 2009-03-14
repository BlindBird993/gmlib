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



/*! \file gmPApple.c
 *
 *  Implementation of the gmPApple template class.
 *
 *  \date   2008-09-07
 */




namespace GMlib {



  template <typename T, int n>
  inline
  PApple<T, n>::PApple( T radius ) {

    _r = radius;
  }


  template <typename T, int n>
  inline
  PApple<T, n>::PApple( const PApple<T,n>& papple ) {

    _r = papple._r;
  }


  template <typename T, int n>
  inline
  T PApple<T, n>::getEndPU() {

  //  return T(M_PI_2);
    return T(2 * M_PI);
  }


  template <typename T, int n>
  inline
  T PApple<T, n>::getEndPV() {

  //  return T(M_PI);
    return T(M_PI);
  }


  template <typename T, int n>
  std::string PApple<T,n>::getIdentity() const {

    return "PApple";
  }


  template <typename T, int n>
  inline
  bool PApple<T, n>::isClosedU() const {

    return true;
  }


  template <typename T, int n>
  inline
  bool PApple<T, n>::isClosedV() const {

    return false;
  }


  template <typename T, int n>
  void PApple<T, n>::eval(T u, T v, int d1, int d2, bool lu, bool lv ) {

    this->_p.setDim( d1+1, d2+1 );

    this->_p[0][0][0] =	 cos(u) * ( 4 + 3.8 * cos(v) );
    this->_p[0][0][1] =	 sin(u) * ( 4 + 3.8 * cos(v) );
    this->_p[0][0][2] =	 ( cos(v) + sin(v) - 1 ) * ( 1 + sin(v) ) * log( 1 - M_PI * v / 10 ) + 7.5 * sin( v );
  }


  template <typename T, int n>
  inline
  T PApple<T, n>::getStartPU() {

  //  return -T(M_PI_2);
    return T(0);
  }


  template <typename T, int n>
  inline
  T PApple<T, n>::getStartPV() {

  //  return -T(M_PI);
    return -T(M_PI);
  }

}
