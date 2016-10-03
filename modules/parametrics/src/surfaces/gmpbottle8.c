
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
  PBottle8<T>::PBottle8( T radius ) {

    init();

    _r = radius;
  }


  template <typename T>
  inline
  PBottle8<T>::PBottle8( const PBottle8<T>& copy ) : PSurf<T,3>( copy ) {

    init();

    _r = copy._r;
  }



  template <typename T>
  PBottle8<T>::~PBottle8() {}


  template <typename T>
  void PBottle8<T>::eval(T u, T v, int d1, int d2, bool /*lu*/, bool /*lv*/ ) {

    this->_p.setDim( d1+1, d2+1 );


    this->_p[0][0][0] =	(_r+cos(T(.5)*u)*sin(v)-sin(T(.5)*u)*sin(T(2)*v))*cos(u);
    this->_p[0][0][1] =	(_r+cos(T(.5)*u)*sin(v)-sin(T(.5)*u)*sin(T(2)*v))*sin(u);
    this->_p[0][0][2] =	sin(T(.5)*u)*sin(v)+cos(T(.5)*u)*sin(T(2)*v);


    if( this->_dm == GM_DERIVATION_EXPLICIT ) {

      if(d1) //u
      {
        this->_p[1][0][0] =	-cos(u)*sin(T(.5)*u)*T(.5)*sin(v)-cos(u)*cos(T(.5)*u)*T(.5)*sin(T(2)*v)
                -sin(u)*_r-sin(u)*cos(T(.5)*u)*sin(v)+sin(u)*sin(T(.5)*u)*sin(T(2)*v);
        this->_p[1][0][1] =	-sin(u)*sin(T(.5)*u)*T(.5)*sin(v)-sin(u)*cos(T(.5)*u)*T(.5)*sin(T(2)*v)
                +cos(u)*_r+cos(u)*cos(T(.5)*u)*sin(v)-cos(u)*sin(T(.5)*u)*sin(T(2)*v);
        this->_p[1][0][2] =	-T(.5)*(-cos(T(.5)*u)*sin(v)+sin(T(.5)*u)*sin(T(2)*v));
      }
      if(d1>1)//uu
      {
        this->_p[2][0][0] =	-cos(u)*cos(T(.5)*u)*T(.25)*sin(v)+cos(u)*sin(T(.5)*u)*T(.25)*sin(T(2)*v)
                +2.0*sin(u)*sin(T(.5)*u)*T(.5)*sin(v)+2.0*sin(u)*cos(T(.5)*u)*T(.5)*sin(T(2)*v)
                -cos(u)*_r-cos(u)*cos(T(.5)*u)*sin(v)+cos(u)*sin(T(.5)*u)*sin(T(2)*v);
        this->_p[2][0][1] =	-sin(u)*cos(T(.5)*u)*T(.25)*sin(v)+sin(u)*sin(T(.5)*u)*T(.25)*sin(T(2)*v)
                -2.0*cos(u)*sin(T(.5)*u)*T(.5)*sin(v)-2.0*cos(u)*cos(T(.5)*u)*T(.5)*sin(T(2)*v)
                -sin(u)*_r-sin(u)*cos(T(.5)*u)*sin(v)+sin(u)*sin(T(.5)*u)*sin(T(2)*v);
        this->_p[2][0][2] =	-T(.25)*(sin(T(.5)*u)*sin(v)+cos(T(.5)*u)*sin(T(2)*v));
      }
      if(d2) //v
      {
        this->_p[0][1][0] =	-(-cos(T(.5)*u)*cos(v)+sin(T(.5)*u)*cos(T(2)*v)*T(2))*cos(u);
        this->_p[0][1][1] =	-(-cos(T(.5)*u)*cos(v)+sin(T(.5)*u)*cos(T(2)*v)*T(2))*sin(u);
        this->_p[0][1][2] =	sin(T(.5)*u)*cos(v)+cos(T(.5)*u)*cos(T(2)*v)*T(2);
      }
      if(d2>1) //vv
      {
        this->_p[0][2][0] =	(-cos(T(.5)*u)*sin(v)+sin(T(.5)*u)*sin(T(2)*v)*T(4))*cos(u);
        this->_p[0][2][1] =	(-cos(T(.5)*u)*sin(v)+sin(T(.5)*u)*sin(T(2)*v)*T(4))*sin(u);
        this->_p[0][2][2] =	-sin(T(.5)*u)*sin(v)-cos(T(.5)*u)*sin(T(2)*v)*T(4);
      }
      if(d1 && d2) //uv
      {
        this->_p[1][1][0] =  -cos(u)*sin(T(.5)*u)*T(.5)*cos(v)-cos(u)*cos(T(.5)*u)*T(.5)*cos(T(2)*v)*T(2)
                -sin(u)*cos(T(.5)*u)*cos(v)+sin(u)*sin(T(.5)*u)*cos(T(2)*v)*T(2);
        this->_p[1][1][1] =	-sin(u)*sin(T(.5)*u)*T(.5)*cos(v)-sin(u)*cos(T(.5)*u)*T(.5)*cos(T(2)*v)*T(2)
                +cos(u)*cos(T(.5)*u)*cos(v)-cos(u)*sin(T(.5)*u)*cos(T(2)*v)*T(2);
        this->_p[1][1][2] =	-T(.5)*(-cos(T(.5)*u)*cos(v)+sin(T(.5)*u)*cos(T(2)*v)*T(2));
      }
      if(d1>1 && d2)//uuv
      {
        this->_p[2][1][0] =	-cos(u)*cos(T(.5)*u)*T(.25)*cos(v)+cos(u)*sin(T(.5)*u)*T(.25)*cos(T(2)*v)*T(2)
                +2.0*sin(u)*sin(T(.5)*u)*T(.5)*cos(v)+2.0*sin(u)*cos(T(.5)*u)*T(.5)*cos(T(2)*v)*T(2)
                -cos(u)*cos(T(.5)*u)*cos(v)+cos(u)*sin(T(.5)*u)*cos(T(2)*v)*T(2);
        this->_p[2][1][1] =	-sin(u)*cos(T(.5)*u)*T(.25)*cos(v)+sin(u)*sin(T(.5)*u)*T(.25)*cos(T(2)*v)*T(2)
                -2.0*cos(u)*sin(T(.5)*u)*T(.5)*cos(v)-2.0*cos(u)*cos(T(.5)*u)*T(.5)*cos(T(2)*v)*T(2)
                -sin(u)*cos(T(.5)*u)*cos(v)+sin(u)*sin(T(.5)*u)*cos(T(2)*v)*T(2);
        this->_p[2][1][2] =	-T(.25)*(sin(T(.5)*u)*cos(v)+cos(T(.5)*u)*cos(T(2)*v)*T(2));
      }
      if(d1 && d2>1) //uvv
      {
        this->_p[1][2][0] =	cos(u)*sin(T(.5)*u)*T(.5)*sin(v)+cos(u)*cos(T(.5)*u)*T(.5)*sin(T(2)*v)*T(4)
                +sin(u)*cos(T(.5)*u)*sin(v)-sin(u)*sin(T(.5)*u)*sin(T(2)*v)*T(4);
        this->_p[1][2][1] =	sin(u)*sin(T(.5)*u)*T(.5)*sin(v)+sin(u)*cos(T(.5)*u)*T(.5)*sin(T(2)*v)*T(4)
                -cos(u)*cos(T(.5)*u)*sin(v)+cos(u)*sin(T(.5)*u)*sin(T(2)*v)*T(4);
        this->_p[1][2][2] =	T(.5)*(-cos(T(.5)*u)*sin(v)+sin(T(.5)*u)*sin(T(2)*v)*T(4));
      }
      if(d1>1 && d2>1) //uuvv
      {
        this->_p[2][2][0] =	cos(u)*cos(T(.5)*u)*T(.25)*sin(v)-cos(u)*sin(T(.5)*u)*T(.25)*sin(T(2)*v)*T(4)
                -2.0*sin(u)*sin(T(.5)*u)*T(.5)*sin(v)-2.0*sin(u)*cos(T(.5)*u)*T(.5)*sin(T(2)*v)*T(4)
                +cos(u)*cos(T(.5)*u)*sin(v)-cos(u)*sin(T(.5)*u)*sin(T(2)*v)*T(4);
        this->_p[2][2][1] =	sin(u)*cos(T(.5)*u)*T(.25)*sin(v)-sin(u)*sin(T(.5)*u)*T(.25)*sin(T(2)*v)*T(4)
                +2.0*cos(u)*sin(T(.5)*u)*T(.5)*sin(v)+2.0*cos(u)*cos(T(.5)*u)*T(.5)*sin(T(2)*v)*T(4)
                +sin(u)*cos(T(.5)*u)*sin(v)-sin(u)*sin(T(.5)*u)*sin(T(2)*v)*T(4);
        this->_p[2][2][2] =	T(.25)*(sin(T(.5)*u)*sin(v)+cos(T(.5)*u)*sin(T(2)*v)*T(4));
      }
    }
  }


  template <typename T>
  inline
  T PBottle8<T>::getEndPU() {

    return T(M_2PI);
  }


  template <typename T>
  inline
  T PBottle8<T>::getEndPV() {

    return T(M_2PI);
  }


  template <typename T>
  inline
  T PBottle8<T>::getStartPU() {

    return T(0);
  }


  template <typename T>
  inline
  T PBottle8<T>::getStartPV() {

    return T(0);
  }


  template <typename T>
  void PBottle8<T>::init() {

    this->_dm = GM_DERIVATION_EXPLICIT;
  }


  template <typename T>
  inline
  bool PBottle8<T>::isClosedU() const {

    return false;
  }


  template <typename T>
  inline
  bool PBottle8<T>::isClosedV() const {

    return false;
  }

} // END namespace GMlib
