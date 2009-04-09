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
//  DPApple<T>::DPApple( T radius ) : DSurf<T>( new PApple<T,3>( radius ) ) {
//
//    init();
//  }

  template <typename T>
  inline
  DPApple<T>::DPApple( T radius ) {

    init();

    _r = radius;
  }


  template <typename T>
  inline
  DPApple<T>::DPApple( const DPApple<T>& copy ) : DSurf<T>( copy ) {

    init();
    _r = copy._r;
  }


//  template <typename T>
//  inline
//  DPApple<T>::DPApple( const PApple<T,3>& papple ) : DSurf<T>( papple ) {
//
//    init();
//  }


  template <typename T>
  DPApple<T>::~DPApple() {}


  template <typename T>
  inline
  string DPApple<T>::getIdentity() const {

    return "DPApple";
  }


//  template <typename T>
//  inline
//  PApple<T,3>* DPApple<T>::getPApple() {
//
//    return _l_ref;
//  }


  template <typename T>
  void DPApple<T>::init() {

//    _l_ref = dynamic_cast<PApple<T,3>*>( this->_p_ref );
  }









  //////////////////////// PApple !!!!!!!!!!!!!! PApple ////////////////////////
  //////////////////////// PApple !!!!!!!!!!!!!! PApple ////////////////////////
  //////////////////////// PApple !!!!!!!!!!!!!! PApple ////////////////////////
  //////////////////////// PApple !!!!!!!!!!!!!! PApple ////////////////////////



  template <typename T>
  inline
  T DPApple<T>::getEndPU() {

  //  return T(M_PI_2);
    return T(2 * M_PI);
  }


  template <typename T>
  inline
  T DPApple<T>::getEndPV() {

  //  return T(M_PI);
    return T(M_PI);
  }


  template <typename T>
  inline
  bool DPApple<T>::isClosedU() const {

    return true;
  }


  template <typename T>
  inline
  bool DPApple<T>::isClosedV() const {

    return false;
  }


  template <typename T>
  void DPApple<T>::eval(T u, T v, int d1, int d2, bool lu, bool lv ) {

    this->_p.setDim( d1+1, d2+1 );

    this->_p[0][0][0] =	 cos(u) * ( 4 + 3.8 * cos(v) );
    this->_p[0][0][1] =	 sin(u) * ( 4 + 3.8 * cos(v) );
    this->_p[0][0][2] =	 ( cos(v) + sin(v) - 1 ) * ( 1 + sin(v) ) * log( 1 - M_PI * v / 10 ) + 7.5 * sin( v );
  }


  template <typename T>
  inline
  T DPApple<T>::getStartPU() {

  //  return -T(M_PI_2);
    return T(0);
  }


  template <typename T>
  inline
  T DPApple<T>::getStartPV() {

  //  return -T(M_PI);
    return -T(M_PI);
  }
}
