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

    this->_dm = GM_DERIVATION_EXPLICIT;
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
  void DPApple<T>::eval(T u, T v, int d1, int d2, bool /*lu*/, bool /*lv*/ ) {

    this->_p.setDim( d1+1, d2+1 );

    this->_p[0][0][0] =	 cos(u) * ( 4 + 3.8 * cos(v) );
    this->_p[0][0][1] =	 sin(u) * ( 4 + 3.8 * cos(v) );
    this->_p[0][0][2] =	 ( cos(v) + sin(v) - 1 ) * ( 1 + sin(v) ) * log( 1 - M_PI * v / 10 ) + 7.5 * sin( v );


    if( this->_dm == GM_DERIVATION_EXPLICIT ) {

      // du
      if(d1){
        this->_p[1][0][0] = -sin(u)* (4 + 3.8* cos(v));                                                                                                                                                                      // dx/du
        this->_p[1][0][1] = cos(u) * (4 + 3.8 * cos(v));                                                                                                                                                                   // d y/du
        this->_p[1][0][2] = T(0);                                                                                                                                                                                                          //  dz/du
      }

      //duu
      if(d1>1){
        this->_p[2][0][0] =-cos(u)* (4 + 3.8* cos(v));
        this->_p[2][0][1] =-sin(u) * (4 + 3.8 * cos(v));
        this->_p[2][0][2] =	 T(0);
      }

      //dv
      if(d2){
        this->_p[0][1][0] =- cos(u)* 3.8* sin(v);                                                                                                                                                                                     // dx/dv
        this->_p[0][1][1] =-sin(u) * 3.8 * sin(v);                                                                                                                                                                                     //  dy/dv
        this->_p[0][1][2] =  -(cos(v)* (1/(1 - M_PI * v / 10))*log(M_E)*(M_PI/10)+ sin(v) *log(1 - M_PI * v / 10))
                                +(0.5*(1/(1 - M_PI * v / 10))*log(M_E)*(M_PI/10))
                                +(0.5*(-sin(2*v)*(1/(1 - M_PI * v / 10))*log(M_E)*(M_PI/10)+cos(2*v)*2*log(1 - M_PI * v / 10)))
                                +(0.5*(sin(2*v)*2*log(1 - M_PI * v / 10)+cos(2*v)*(1/(1 - M_PI * v / 10))*log(M_E)*(M_PI/10)))
                                +7.5 * cos(v);
      }

      //dvv
      if(d2>1){
        this->_p[0][2][0] = - cos(u)* 3.8* cos(v);
        this->_p[0][2][1] = -sin(u) * 3.8 * cos(v);
        this->_p[0][2][2] = -(( -sin(v)*(1/(1 - M_PI * v / 10))*log(M_E)*(M_PI/10) + cos(v) * log(M_E)*(M_PI/10) *(M_PI/10) *(1/((1/(1 - M_PI * v / 10))*(1/(1 - M_PI * v / 10))) ) ) + (-sin(v) * (1/(1 - M_PI * v / 10))*log(M_E)*(M_PI/10) +cos(v) *log(1 - M_PI * v / 10) ) )
                      +(0.5*(M_PI / 10)*(1/((1/(1 - M_PI * v / 10))*(1/(1 - M_PI * v / 10))))*log(M_E)*(M_PI/10))
                      + ( 0.5* ( (-2*cos(2*v)*(1/(1 - M_PI * v / 10))*log(M_E)*(M_PI/10) - sin(2*v)*(M_PI/10)*(1/((1/(1 - M_PI * v / 10))*(1/(1 - M_PI * v / 10)))) *log(M_E)*(M_PI/10))+(-sin(2*v)*4*log(1 - M_PI * v / 10) - cos(2*v)*2* (1/(1 - M_PI * v / 10))*log(M_E)*(M_PI/10) )))
                      +( 0.5* (( -sin(2*v)*2*(1/(1 - M_PI * v / 10))*log(M_E)*(M_PI/10) + cos(2*v)*4* log(1 - M_PI * v / 10))+( cos(2*v)*(1/((1/(1 - M_PI * v / 10))*(1/(1 - M_PI * v / 10))) )*log(M_E)*(M_PI/10)*(M_PI/10) - sin(2*v)*2*(1/(1 - M_PI * v / 10))*log(M_E)*(M_PI/10))))
                      -7.5 * sin(v);
      }

      //duv/dvu
      if(d1 && d2){
        this->_p[1][1][0] = sin(u)* 3.8* sin(v);
        this->_p[1][1][1] =-cos(u) * 3.8 * sin(v);
        this->_p[1][1][2] =T(0);
      }

      //duvv
      if(d1 && d2>1){
        this->_p[1][2][0] =sin(u)* 3.8* cos(v);
        this->_p[1][2][1] =-cos(u) * 3.8 * cos(v);
        this->_p[1][2][2] =T(0);
      }

      //duuv
      if(d1>1 && d2){
        this->_p[2][1][0] =cos(u)* 3.8* sin(v);
        this->_p[2][1][1] =sin(u) * 3.8 * sin(v);
        this->_p[2][1][2] = T(0);
      }

      //duuvv
      if(d1>1 && d2>1){
        this->_p[2][2][0] =cos(u)* 3.8* cos(v);
        this->_p[2][2][1] =sin(u) * 3.8 * cos(v);
        this->_p[2][2][2] =T(0);
      }
    }
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
