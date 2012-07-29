
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



/*! \file gmpinsideouttorus.c
 *
 *  Implementation of the PInsideOutTorus template class.
 */


namespace GMlib {


  template <typename T>
  inline
  PInsideOutTorus<T>::PInsideOutTorus( T wheelrad, T tuberad1, T tuberad2 ) {

    init();

    _a = wheelrad;
    _b = tuberad1;
    _c = tuberad2;
  }


  template <typename T>
  inline
  PInsideOutTorus<T>::PInsideOutTorus( const PInsideOutTorus<T>& copy ) : PSurf<T>( copy ) {

    init();

    _a = copy._a;
    _b = copy._b;
    _c = copy._c;
  }



  template <typename T>
  PInsideOutTorus<T>::~PInsideOutTorus() {}


  template <typename T>
  void PInsideOutTorus<T>::eval(T u, T v, int d1, int d2, bool /*lu*/, bool /*lv*/ ) {

    this->_p.setDim( d1+1, d2+1 );


    this->_p[0][0][0] =			cos(u)*(_b*cos(v)+_a);
    this->_p[0][0][1] =			sin(u)*(_b*cos(v)+_a);
    this->_p[0][0][2] =			_c*sin(v);


    if( this->_dm == GM_DERIVATION_EXPLICIT ) {

      if(d1) //u
      {
        this->_p[1][0][0] =		-sin(u)*(_b*cos(v)+_a);
        this->_p[1][0][1] =		cos(u)*(_b*cos(v)+_a);
        this->_p[1][0][2] =		0.0;
      }
      if(d1>1)//uu
      {
        this->_p[2][0][0] =		-cos(u)*(_b*cos(v)+_a);
        this->_p[2][0][1] =		-sin(u)*(_b*cos(v)+_a);
        this->_p[2][0][2] =		0.0;
      }
      if(d2) //v
      {
        this->_p[0][1][0] =		-_b*cos(u)*sin(v);
        this->_p[0][1][1] =		-_b*sin(u)*sin(v);
        this->_p[0][1][2] =		_c*cos(v);
      }
      if(d2>1) //vv
      {
        this->_p[0][2][0] =		-_b*cos(u)*cos(v);
        this->_p[0][2][1] =		-_b*sin(u)*cos(v);
        this->_p[0][2][2] =		-_c*sin(v);
      }
      if(d1 && d2) //uv
      {
        this->_p[1][1][0] =		_b*sin(u)*sin(v);
        this->_p[1][1][1] =		-_b*cos(u)*sin(v);
        this->_p[1][1][2] =		0.0;
      }
      if(d1>1 && d2)//uuv
      {
        this->_p[2][1][0] =		_b*cos(u)*sin(v);
        this->_p[2][1][1] =		_b*sin(u)*sin(v);
        this->_p[2][1][2] =		0.0;
      }
      if(d1 && d2>1) //uvv
      {
        this->_p[1][2][0] =		_b*sin(u)*cos(v);
        this->_p[1][2][1] =		-_b*cos(u)*cos(v);
        this->_p[1][2][2] =		0.0;
      }
      if(d1>1 && d2>1) //uuvv
      {
        this->_p[2][2][0] =		_b*cos(u)*cos(v);
        this->_p[2][2][1] =		_b*sin(u)*cos(v);
        this->_p[2][2][2] =		0.0;
      }
    }
  }


  template <typename T>
  inline
  T PInsideOutTorus<T>::getEndPU() {

    return T(2 * M_PI);
  }


  template <typename T>
  inline
  T PInsideOutTorus<T>::getEndPV() {

    return T(2 * M_PI);
  }


  template <typename T>
  inline
  T PInsideOutTorus<T>::getStartPU() {

    return T(0);
  }


  template <typename T>
  inline
  T PInsideOutTorus<T>::getStartPV() {

    return T(0);
  }


  template <typename T>
  inline
  std::string PInsideOutTorus<T>::getIdentity() const {

    return "PInsideOutTorus";
  }


  template <typename T>
  void PInsideOutTorus<T>::init() {

    this->_dm = GM_DERIVATION_EXPLICIT;
  }


  template <typename T>
  inline
  bool PInsideOutTorus<T>::isClosedU() const {

    return false;
  }


  template <typename T>
  inline
  bool PInsideOutTorus<T>::isClosedV() const {

    return false;
  }

} // END namespace GMlib
