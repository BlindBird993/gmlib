
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



/*! \file gmPHeart.c
 *
 *  Implementation of the PHeart template class.
 *
 *  \date   2010-09-30
 */


namespace GMlib {


  template <typename T>
  inline
  PHeart<T>::PHeart() {

    init();
  }


  template <typename T>
  inline
  PHeart<T>::PHeart( const PHeart<T>& copy ) : PSurf<T>( copy ) {

    init();
  }



  template <typename T>
  PHeart<T>::~PHeart() {}


  template <typename T>
  void PHeart<T>::eval(T u, T v, int d1, int d2, bool /*lu*/, bool /*lv*/ ) {

    this->_p.setDim( d1+1, d2+1 );


    this->_p[0][0][0] =	(T(4)*sqrt((T)(T(1) - u*u))*pow( (T)sin((T)abs(v)) , (T)abs(v)))*sin(v);
    this->_p[0][0][1] =	(T(4)*sqrt((T)(T(1) - u*u))*pow( (T)sin((T)abs(v)) , (T)abs(v)))*cos(v);
    this->_p[0][0][2] =	u;


    if( this->_dm == GM_DERIVATION_EXPLICIT ) {

      if(d1) //u
      {
        this->_p[1][0][0] =	-T(4)*pow(sin(abs(v)),abs(v))*sin(v)*u/(sqrt(T(1)-u*u));
        this->_p[1][0][1] =	 -T(4)*pow(sin(abs(v)),abs(v))*cos(v)*u/(sqrt(T(1)-u*u));
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
        this->_p[0][1][0] =	T(4)*sqrt(T(1)-u*u)*pow(sin(abs(v)),abs(v))*(/*abs(1,v)*/log(sin(abs(v)))+abs(v)*cos(abs(v))
                /*abs(1,v)*//sin(abs(v)))*sin(v)+T(4)*sqrt(T(1)-u*u)*pow(sin(abs(v)),abs(v))*cos(v);
        this->_p[0][1][1] =	T(4)*sqrt(T(1)-u*u)*pow(sin(abs(v)),abs(v))*(/*abs(1,v)*/log(sin(abs(v)))+abs(v)*cos(abs(v))
                /*abs(1,v)*//(abs(v)))*cos(v)-T(4)*sqrt(T(1)-u*u)*pow(sin(abs(v)),abs(v))*sin(v);
        this->_p[0][1][2] =	T(0);
      }
      if(d2>1) //vv
      {
        this->_p[0][2][0] =	T(0);
        this->_p[0][2][1] =	T(0);
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
        this->_p[2][1][0] =	T(0);
        this->_p[2][1][1] =	T(0);
        this->_p[2][1][2] =	T(0);
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


  template <typename T>
  inline
  T PHeart<T>::getEndPU() {

    return T(0.98);
  }


  template <typename T>
  inline
  T PHeart<T>::getEndPV() {

    return T(M_PI-0.0001);
  }


  template <typename T>
  inline
  T PHeart<T>::getStartPU() {

    return -T(0.98);
  }


  template <typename T>
  inline
  T PHeart<T>::getStartPV() {

    return -T(M_PI+0.0001);
  }


  template <typename T>
  inline
  std::string PHeart<T>::getIdentity() const {

    return "PHeart";
  }


  template <typename T>
  void PHeart<T>::init() {

    this->_dm = GM_DERIVATION_EXPLICIT;
  }


  template <typename T>
  inline
  bool PHeart<T>::isClosedU() const {

    return false;
  }


  template <typename T>
  inline
  bool PHeart<T>::isClosedV() const {

    return false;
  }

} // END namespace GMlib
