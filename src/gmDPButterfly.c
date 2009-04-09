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



/*! \file gmDPButterfly.c
 *
 *  Implementation of the DPButterfly template class.
 *
 *  \date   2008-09-10
 */


namespace GMlib {

//
//  template <typename T>
//  inline
//  DPButterfly<T>::DPButterfly( T size ) : DCurve<T>( new PButterfly<T, 3>(size) ) {
//
//    _size = size;
//    this->_dm = GM_DERIVATION_EXPLICIT;
//    init();
//  }


  template <typename T>
  inline
  DPButterfly<T>::DPButterfly( T size ) {

    _size = size;
    this->_dm = GM_DERIVATION_EXPLICIT;
    init();
  }


  template <typename T>
  inline
  DPButterfly<T>::DPButterfly( const DPButterfly<T>& copy ) : DCurve<T>( copy ) {

    init();
  }


//  template <typename T>
//  inline
//  DPButterfly<T>::DPButterfly( const PButterfly<T,3>& copy ) : DCurve<T>( copy ) {
//
//    init();
//  }
//
//
//  template <typename T>
//  inline
//  DPButterfly<T>::DPButterfly( PButterfly<T,3>* copy ) : DCurve<T>( copy ) {
//
//    _l_ref = copy;
//  }


  template <typename T>
  DPButterfly<T>::~DPButterfly() {}


  template <typename T>
  inline
  string DPButterfly<T>::getIdentity() const {

    return "DPButterfly";
  }


//  template <typename T>
//  inline
//  PButterfly<T,3>* DPButterfly<T>::getPButterfly() {
//
//    return _l_ref;
//  }


  template <typename T>
  void DPButterfly<T>::init() {

//    _l_ref = dynamic_cast<PButterfly<T,3>*>( this->_p_ref );
  }








  //////////////////////// PButterfly !!!!!!!!!!!!!! PButterfly ////////////////////////
  //////////////////////// PButterfly !!!!!!!!!!!!!! PButterfly ////////////////////////
  //////////////////////// PButterfly !!!!!!!!!!!!!! PButterfly ////////////////////////












  template <typename T>
  inline
  void DPButterfly<T>::eval( T t, int d, bool l ) {

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


  template <typename T>
  inline
  T DPButterfly<T>::getEndP() {

    return T( M_PI * 24.0 );
  }


  template <typename T>
  inline
  T DPButterfly<T>::getStartP() {

    return T(0);
  }


  template <typename T>
  inline
  bool DPButterfly<T>::isClosed() const {

    return true;
  }
}
