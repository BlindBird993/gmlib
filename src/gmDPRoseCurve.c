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



/*! \file gmDPRoseCurve.c
 *
 *  Implementation of the DPRoseCurve template class.
 *
 *  \date   2008-12-02
 */


namespace GMlib {


//  template <typename T>
//  inline
//  DPRoseCurve<T>::DPRoseCurve( T radius ) : DCurve<T>( new PRoseCurve<T, 3>(radius) ) {
//
//    this->_dm = GM_DERIVATION_EXPLICIT;
//    _r = radius;
//    init();
//  }


  template <typename T>
  inline
  DPRoseCurve<T>::DPRoseCurve( T radius ) {

    this->_dm = GM_DERIVATION_EXPLICIT;
    _r = radius;
    init();
  }


  template <typename T>
  inline
  DPRoseCurve<T>::DPRoseCurve( const DPRoseCurve<T>& copy ) : DCurve<T>( copy ) {

    init();
  }


//  template <typename T>
//  inline
//  DPRoseCurve<T>::DPRoseCurve( const PRoseCurve<T,3>& copy ) : DCurve<T>( copy ) {
//
//    init();
//  }
//
//
//  template <typename T>
//  inline
//  DPRoseCurve<T>::DPRoseCurve( PRoseCurve<T,3>* copy ) : DCurve<T>( copy ) {
//
//    _l_ref = copy;
//  }


  template <typename T>
  DPRoseCurve<T>::~DPRoseCurve() {}


  template <typename T>
  inline
  string DPRoseCurve<T>::getIdentity() const {

    return "DPRoseCurve";
  }


//  template <typename T>
//  inline
//  PRoseCurve<T,3>*    DPRoseCurve<T>::getPRoseCurve() {
//
//    return _l_ref;
//  }


  template <typename T>
  void DPRoseCurve<T>::init() {

//    _l_ref  = dynamic_cast<PRoseCurve<T,3>*>( this->_p_ref );
  }











  //////////////////////// PRoseCurve !!!!!!!!!!!!!! PRoseCurve ////////////////////////
  //////////////////////// PRoseCurve !!!!!!!!!!!!!! PRoseCurve ////////////////////////
  //////////////////////// PRoseCurve !!!!!!!!!!!!!! PRoseCurve ////////////////////////














  template <typename T>
  inline
  void DPRoseCurve<T>::eval( T t, int d, bool l ) {

    this->_p.setDim( d + 1 );

    this->_p[0][0] = _r * cos( T(1.75) * t) * cos(t);
    this->_p[0][1] = _r * sin( t )*cos( T(1.75) * t );
    this->_p[0][2] = T(0);

    if( this->_dm == GM_DERIVATION_EXPLICIT ) {

      if(d > 0) {

        this->_p[1][0] = _r * -T(1.75)*sin(T(1.75)*t)*cos(t)-sin(t)*cos(T(1.75)*t);
        this->_p[1][1] = _r * -T(1.75)*sin(t)*sin(T(1.75)*t)+cos(T(1.75)*t)*cos(t);
        this->_p[1][2] = T(0);
      }

      if(d > 1) {

        this->_p[2][0]= _r * T(3.5)*sin(t)*sin(T(1.75)*t)-T(4.0625)*cos(T(1.75)*t)*cos(t);
        this->_p[2][1]= _r * -T(3.5)*sin(T(1.75)*t)*cos(t)-T(4.0625)*sin(t)*cos(T(1.75)*t);
        this->_p[2][2]= T(0);
      }
    }
  }


  template <typename T>
  inline
  T DPRoseCurve<T>::getEndP() {

    return T( 8 * M_PI );
  }


  template <typename T>
  inline
  T DPRoseCurve<T>::getStartP() {

    return T(0);
  }


  template <typename T>
  inline
  bool DPRoseCurve<T>::isClosed() const {

    return true;
  }
}

