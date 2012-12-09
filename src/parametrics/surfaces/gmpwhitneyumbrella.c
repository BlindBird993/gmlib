
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



/*! \file gmpwhitneyumbrella.c
 *
 *  Implementation of the PWhitneyUmbrella template class.
 */


namespace GMlib {


  template <typename T>
  inline
  PWhitneyUmbrella<T>::PWhitneyUmbrella() {

    init();
  }

  template <typename T>
  inline
  PWhitneyUmbrella<T>::PWhitneyUmbrella( const PWhitneyUmbrella<T>& copy ) : PSurf<T>( copy ) {

    init();
  }

  template <typename T>
  PWhitneyUmbrella<T>::~PWhitneyUmbrella() {}

  template <typename T>
  void PWhitneyUmbrella<T>::eval(T u, T v, int d1, int d2, bool /*lu*/, bool /*lv*/ ) {

    this->_p.setDim( d1+1, d2+1 );

    this->_p[0][0][0] =	v*u;
    this->_p[0][0][1] =	u;
    this->_p[0][0][2] =	v*v;


    if( this->_dm == GM_DERIVATION_EXPLICIT ) {

      if(d1) //u
      {
        this->_p[1][0][0] =	v;
        this->_p[1][0][1] =  T(1);
        this->_p[1][0][2] =	0.0;
      }
      if(d1>1)//uu
      {
        this->_p[2][0][0] =	0.0;
        this->_p[2][0][1] =	0.0;
        this->_p[2][0][2] =	0.0;
      }
      if(d2) //v
      {
        this->_p[0][1][0] =	u;
        this->_p[0][1][1] =	0.0;
        this->_p[0][1][2] =	T(2)*v;
      }
      if(d2>1) //vv
      {
        this->_p[0][2][0] =	0.0;
        this->_p[0][2][1] =	0.0;
        this->_p[0][2][2] =	T(2);
      }
      if(d1 && d2) //uv
      {
        this->_p[1][1][0] =	T(1);
        this->_p[1][1][1] =	0.0;
        this->_p[1][1][2] =	0.0;
      }
      if(d1>1 && d2)//uuv
      {
        this->_p[2][1][0] =	0.0;
        this->_p[2][1][1] =	0.0;
        this->_p[2][1][2] =	0.0;
      }
      if(d1 && d2>1) //uvv
      {
        this->_p[1][2][0] =	0.0;
        this->_p[1][2][1] =	0.0;
        this->_p[1][2][2] =	0.0;
      }
      if(d1>1 && d2>1) //uuvv
      {
        this->_p[2][2][0] =	0.0;
        this->_p[2][2][1] =	0.0;
        this->_p[2][2][2] =	0.0;
      }
    }
  }

  template <typename T>
  inline
  T PWhitneyUmbrella<T>::getEndPU() {

    return T(M_PI);
  }

  template <typename T>
  inline
  T PWhitneyUmbrella<T>::getEndPV() {

    return T(M_PI);
  }

  template <typename T>
  inline
  T PWhitneyUmbrella<T>::getStartPU() {

    return -T(M_PI);
  }

  template <typename T>
  inline
  T PWhitneyUmbrella<T>::getStartPV() {

    return -T(M_PI);
  }

  template <typename T>
  void PWhitneyUmbrella<T>::init() {

    this->_dm = GM_DERIVATION_EXPLICIT;
  }

  template <typename T>
  inline
  bool PWhitneyUmbrella<T>::isClosedU() const {

    return false;
  }

  template <typename T>
  inline
  bool PWhitneyUmbrella<T>::isClosedV() const {

    return false;
  }

} // END namespace GMlib
