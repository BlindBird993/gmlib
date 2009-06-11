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



/*! \file gmDPCircle.c
 *
 *  Implementation of the DPCircle template class.
 *
 *  \date   2008-09-09
 */


namespace GMlib {



//  template <typename T>
//  inline
//  DPCircle<T>::DPCircle( T radius ) : DCurve<T>( new PCircle<T, 3>( radius ) ) {
//
//    _r = radius;
//    this->_dm = GM_DERIVATION_EXPLICIT;
//    init();
//  }


  template <typename T>
  inline
  DPCircle<T>::DPCircle( T radius ) {

    _r = radius;
    this->_dm = GM_DERIVATION_EXPLICIT;
    init();
  }


  template <typename T>
  inline
  DPCircle<T>::DPCircle( const DPCircle<T>& copy ) : DCurve<T>(copy) {

    init();
  }


//  template <typename T>
//  inline
//  DPCircle<T>::DPCircle( const PCircle<T,3>& copy ) : DCurve<T>(copy) {
//
//    init();
//  }
//
//
//  template <typename T>
//  inline
//  DPCircle<T>::DPCircle( PCircle<T,3>* copy ) : DCurve<T>(copy) {
//
//    _l_ref = copy;
//  }


  template <typename T>
  DPCircle<T>::~DPCircle() {}


  template <typename T>
  inline
  string DPCircle<T>::getIdentity() const {

    return "DPCircle";
  }


//  template <typename T>
//  inline
//  PCircle<T,3>* DPCircle<T>::getPCircle() {
//
//    return _l_ref;
//  }


  template <typename T>
  void DPCircle<T>::init() {

//    _l_ref = dynamic_cast<PCircle<T,3>*>( this->_p_ref );
  }



  //////////////////////// DPCircle !!!!!!!!!!!!!! DPCircle ////////////////////////
  //////////////////////// DPCircle !!!!!!!!!!!!!! DPCircle ////////////////////////
  //////////////////////// DPCircle !!!!!!!!!!!!!! DPCircle ////////////////////////


  template <typename T>
  inline
  void DPCircle<T>::eval( T t, int d, bool /*l*/ ) {

    this->_p.setDim( d + 1 );

    this->_p[0][0] = _r * cos( t );
    this->_p[0][1] = _r * sin( t );
    this->_p[0][2] = T(0);

    if( this->_dm == GM_DERIVATION_EXPLICIT ) {

      if( d > 0 ) {

        this->_p[1][0] = - _r *  sin( t );
        this->_p[1][1] =   _r *  cos( t );
        this->_p[1][2] =   T(0);
      }

      if( d > 1 ) {

        this->_p[2][0] = - _r *  cos( t );
        this->_p[2][1] = - _r *  sin( t );
        this->_p[2][2] =   T(0);
      }
    }
  }


  template <typename T>
  inline
  T DPCircle<T>::getEndP() {

    return T( M_2PI );
  }


  template <typename T>
  inline
  T DPCircle<T>::getStartP() {

    return T(0);
  }


  template <typename T>
  inline
  T DPCircle<T>::getRadius() {

    return _r;
  }


  template <typename T>
  inline
  bool DPCircle<T>::isClosed() const {

    return true;
  }


  template <typename T>
  inline
  void DPCircle<T>::setRadius( T radius ) {

      _r = radius;
  }
}
