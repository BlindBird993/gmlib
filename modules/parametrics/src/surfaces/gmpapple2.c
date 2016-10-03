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





namespace GMlib {


  template <typename T>
  inline
  PApple2<T>::PApple2( T radius ) {

    init();

    _r = radius;
  }


  template <typename T>
  inline
  PApple2<T>::PApple2( const PApple2<T>& copy ) : PSurf<T,3>( copy ) {

    init();

    _r = copy._r;
  }



  template <typename T>
  PApple2<T>::~PApple2() {}


  template <typename T>
  void PApple2<T>::eval(T u, T v, int d1, int d2, bool /*lu*/, bool /*lv*/ ) {

    this->_p.setDim( d1+1, d2+1 );


    this->_p[0][0][0] =	 2*_r*cos(u)*(1+cos(v))*sin(v);
    this->_p[0][0][1] =	 2*_r*sin(u)*(1+cos(v))*sin(v);
    this->_p[0][0][2] =	-2*_r*cos(v)*(1+cos(v));


    if( this->_dm == GM_DERIVATION_EXPLICIT ) {

      if(d1) //u
      {
        this->_p[1][0][0] = -2*_r*sin(u)*(1+cos(v))*sin(v);
        this->_p[1][0][1] =  2*_r*cos(u)*(1+cos(v))*sin(v);
        this->_p[1][0][2] =  T(0);
      }
      if(d1>1)//uu
      {
        this->_p[2][0][0] =	-2*_r*cos(u)*(1+cos(v))*sin(v);
        this->_p[2][0][1] =	-2*_r*sin(u)*(1+cos(v))*sin(v);
        this->_p[2][0][2] =	 T(0);
      }
      if(d2) //v
      {
        this->_p[0][1][0] =	 2*_r*cos(u)*(2*cos(v)*(cos(v)+1)-1);
        this->_p[0][1][1] =	 2*_r*sin(u)*(2*cos(v)*(cos(v)+1)-1);
        this->_p[0][1][2] =	 2*_r*sin(v)*(1+2*cos(v));
      }
      if(d2>1) //vv
      {
        this->_p[0][2][0] =	-2*_r*cos(u)*sin(v)*(1+4*cos(v));
        this->_p[0][2][1] =	-2*_r*sin(u)*sin(v)*(1+4*cos(v));
        this->_p[0][2][2] =	 2*_r*(cos(v)+2*(cos(v)*cos(v)-sin(v)*sin(v)));
      }
      if(d1 && d2) //uv
      {
        this->_p[1][1][0] =	-2*_r*sin(u)*(2*cos(v)*(cos(v)+1)-1);
        this->_p[1][1][1] =	 2*_r*cos(u)*(2*cos(v)*(cos(v)+1)-1);
        this->_p[1][1][2] =	 T(0);
      }
      if(d1>1 && d2)//uuv
      {
        this->_p[2][1][0] =	-2*_r*cos(u)*(2*cos(v)*(cos(v)+1)-1);
        this->_p[2][1][1] =	-2*_r*sin(u)*(2*cos(v)*(cos(v)+1)-1);
        this->_p[2][1][2] =	 T(0);
      }
      if(d1 && d2>1) //uvv
      {
        this->_p[1][2][0] =	 2*_r*sin(u)*sin(v)*(4*cos(v)+2);
        this->_p[1][2][1] =	-2*_r*cos(u)*sin(v)*(4*cos(v)+2);
        this->_p[1][2][2] =	 T(0);
      }
      if(d1>1 && d2>1) //uuvv
      {
        this->_p[2][2][0] =	 2*_r*cos(u)*sin(v)*(4*cos(v)+2);
        this->_p[2][2][1] =	 2*_r*sin(u)*sin(v)*(4*cos(v)+2);
        this->_p[2][2][2] =	 T(0);
      }
    }
  }


  template <typename T>
  inline
  T PApple2<T>::getEndPU() {

    return T(0.5 * M_PI);
  }


  template <typename T>
  inline
  T PApple2<T>::getEndPV() {

    return T(M_PI);
  }


  template <typename T>
  inline
  T PApple2<T>::getStartPU() {

    return -T(0.5 * M_PI);
  }


  template <typename T>
  inline
  T PApple2<T>::getStartPV() {

    return -T(M_PI);
  }


  template <typename T>
  void PApple2<T>::init() {

    this->_dm = GM_DERIVATION_EXPLICIT;
  }


  template <typename T>
  inline
  bool PApple2<T>::isClosedU() const {

    return true;
  }


  template <typename T>
  inline
  bool PApple2<T>::isClosedV() const {

    return false;
  }

} // END namespace GMlib
