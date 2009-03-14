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



/*! \file gmPButterfly.c
 *
 *  Implementation of the PButterfly template class.
 *
 *  \date   2008-09-10
 */


namespace GMlib {


  template <typename T, int n>
  inline
  PButterfly<T, n>::PButterfly ( T size ) {

    _size = size;
    this->_dm = GM_DERIVATION_EXPLICIT;
  }


  template <typename T, int n>
  inline
  PButterfly<T, n>::PButterfly ( const PButterfly& pbutterfly ) {}


  template <typename T, int n>
  inline
  void PButterfly<T, n>::eval( T t, int d, bool l ) {

      this->_p.setDim( d + 1 );

//      this->_p[0][0] = cos(t) * ( exp( cos(t) ) - 2 * cos(4 * t) - pow( sin(t / T(12)), T(5) ) );
//      this->_p[0][1] = sin(t) * ( exp( cos(t) ) - 2 * cos(4 * t) - pow( sin(t / T(12)), T(5) ) );
//      this->_p[0][2] = T(0);

    const T  a  = ( exp( cos(t) ) - 2 * cos(4 * t) - pow( sin(t / T(12)), T(5) ) );
    const T  a1 = ( -exp( cos(t) ) * sin(t) + 8 * sin(4 * t) - (5/12)* pow( sin(t / T(12)), T(4) ) * cos(t/12) );
    const T  a2 = ( exp( cos(t) )*sin(t)*sin(t) - exp( cos(t) ) * cos(t) + 8* 4 *cos(4 * t) - (5/12)*( (1/3)* pow( sin(t / T(12)), T(3) )*pow( cos(t / T(12)), T(2) ) - (1/12)* pow( sin(t / T(12)), T(5) ) ));


    this->_p[0][0] = _size * cos(t) * a;
    this->_p[0][1] = _size * sin(t) * a;
    this->_p[0][2] = T(0);

    if( this->_dm == GM_DERIVATION_EXPLICIT ) {

      if( d > 0 ) {

        this->_p[1][0] = _size * -sin(t) * a + cos(t) * a1;
        this->_p[1][1] = _size * cos(t) * a + sin(t) * a1;
        this->_p[1][2] = T(0);
      }


      if( d > 1 ) {

        this->_p[2][0] = _size * -cos(t) * a - sin(t) * a1 - sin(t) * a1 + cos(t) * a2;
        this->_p[2][1] = _size * -sin(t) * a + cos(t) * a1 + cos(t) * a1 + sin(t) * a2;
        this->_p[2][2] = T(0);
      }
    }
  }


  template <typename T, int n>
  inline
  T PButterfly<T, n>::getEndP() {

    return T( M_PI * 24.0 );
  }


  template <typename T, int n>
  std::string PButterfly<T,n>::getIdentity() const {

    return "PButterfly";
  }


  template <typename T, int n>
  inline
  T PButterfly<T, n>::getStartP() {

    return T(0);
  }


  template <typename T, int n>
  inline
  bool PButterfly<T, n>::isClosed() const {

    return true;
  }

}
