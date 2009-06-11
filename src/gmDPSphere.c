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



/*! \file gmDPSphere.c
 *
 *  Implementation of the DPSphere template class.
 *
 *  \date   2008-09-04
 */




namespace GMlib {


//  template <typename T>
//  inline
//  DPSphere<T>::DPSphere( T radius ) : DSurf<T>( new PSphere<T, 3>( radius ) ) {
//
//    init();
//  }
//
//
//  template <typename T>
//  inline
//  DPSphere<T>::DPSphere( T radius, int s1, int s2 ) : DSurf<T>( new PSphere<T, 3>( radius, s1, s2 ) ) {
//
//    init();
//  }


  template <typename T>
  inline
  DPSphere<T>::DPSphere( T radius ) {

    init();

    _radius = radius;
    this->_dm = GM_DERIVATION_EXPLICIT;
  }


  template <typename T>
  inline
  DPSphere<T>::DPSphere( T radius, int s1, int s2 ) {

    init();

    _radius = radius;
    this->_dm = GM_DERIVATION_EXPLICIT;
  }


  template <typename T>
  inline
  DPSphere<T>::DPSphere( const DPSphere<T>& copy ) : DSurf<T>( copy ) {

    init();
  }


//  template <typename T>
//  inline
//  DPSphere<T>::DPSphere( const PSphere<T,3>& copy ) : DSurf<T>( copy ) {
//
//    init();
//  }
//
//
//  template <typename T>
//  inline
//  DPSphere<T>::DPSphere( PSphere<T,3>* copy ) : DSurf<T>( copy ) {
//
//    _l_ref = copy;
//  }


  template <typename T>
  DPSphere<T>::~DPSphere() {}


  template <typename T>
  inline
  string DPSphere<T>::getIdentity() const {

    return "DPSphere";
  }


//  template <typename T>
//  inline
//  PSphere<T,3>* DPSphere<T>::getPSphere() {
//
//    return _l_ref;
//  }


//  template <typename T>
//  inline
//  T DPSphere<T>::getRadius() const {
//
//    return _l_ref->getRadius();
//  }
//
//
//  template <typename T>
//  inline
//  void DPSphere<T>::setRadius( T radius ) {
//
//    _l_ref->setRadius( radius );
//  }


//  template <typename T>
//  inline
//  const PSphere<T,3>* const   DPSphere<T>::getPSphere() const {
//
//    return _l_ref;
//  }


  template <typename T>
  inline
  void DPSphere<T>::init() {

//    _l_ref = dynamic_cast<PSphere<T,3>*>( this->_p_ref );
  }










  //////////////////////// PSphere !!!!!!!!!!!!!! PSphere ////////////////////////
  //////////////////////// PSphere !!!!!!!!!!!!!! PSphere ////////////////////////
  //////////////////////// PSphere !!!!!!!!!!!!!! PSphere ////////////////////////
  //////////////////////// PSphere !!!!!!!!!!!!!! PSphere ////////////////////////





  template <typename T>
  inline
  T DPSphere<T>::getEndPU() {

    return T(M_2PI);
  }


  template <typename T>
  inline
  T DPSphere<T>::getEndPV() {

    return T(M_PI_2);
  }


  template <typename T>
  inline
  void DPSphere<T>::eval(T u, T v, int d1, int d2, bool /*lu*/, bool /*lv*/ ) {

    T r = _radius;
    T cos_u = cos(u);
    T cos_v = r * cos(v);
    T sin_u = sin(u);
    T sin_v = r * sin(v);

    this->_p[0][0][0] =  cos_u * cos_v;	// S
    this->_p[0][0][1] =  sin_u * cos_v;
    this->_p[0][0][2] =  sin_v;

    if( this->_dm == GM_DERIVATION_EXPLICIT ) {

      T cu_cv = cos_u * cos_v;
      T cu_sv = cos_u * sin_v;
      T su_cv = sin_u * cos_v;
      T su_sv = sin_u * sin_v;

      if(d1)
      {
        this->_p[1][0][0] = -su_cv;	// S_u
        this->_p[1][0][1] =  cu_cv;
        this->_p[1][0][2] =  T(0);
      }
      if(d2)
      {
        this->_p[0][1][0] = -cu_sv;	// S_v
        this->_p[0][1][1] = -su_sv;
        this->_p[0][1][2] =  cos_v;
      }
      if(d1 && d2)
      {
        this->_p[1][1][0] =  su_sv;	// S_uv
        this->_p[1][1][1] = -cu_sv;
        this->_p[1][1][2] =  T(0);
      }
      if(d1>1)
      {
        this->_p[2][0][0] = -cu_cv;	// S_uu
        this->_p[2][0][1] = -su_cv;
        this->_p[2][0][2] =  T(0);
      }
      if(d2>1)
      {
        this->_p[0][2][0] = -cu_cv;	// S_vv
        this->_p[0][2][1] = -su_cv;
        this->_p[0][2][2] = -sin_v;
      }
      if(d1>1 && d2)
      {
        this->_p[2][1][0] =  cu_sv;	// S_uuv
        this->_p[2][1][1] =  su_sv;
        this->_p[2][1][2] =  T(0);

      }
      if(d1 && d2>1)
      {
        this->_p[1][2][0] =  su_cv;	// S_uvv
        this->_p[1][2][1] = -cu_cv;
        this->_p[1][2][2] =  T(0);

      }
      if(d1>1 && d2>1)
      {
        this->_p[2][2][0] =  cu_cv;	// S_uuvv
        this->_p[2][2][1] =  su_cv;
        this->_p[2][2][2] =  T(0);

      }
      if(d1>2)
      {
        this->_p[3][0][0] =  su_cv;	// S_uuu
        this->_p[3][0][1] = -cu_cv;
        this->_p[3][0][2] =  T(0);
      }
      if(d2>2)
      {
        this->_p[0][3][0] =  cu_sv;	// S_vvv
        this->_p[0][3][1] =  su_sv;
        this->_p[0][3][2] = -cos_v;
      }
      if(d1>2 && d2)
      {
        this->_p[3][1][0] = -su_sv;	// S_uuuv
        this->_p[3][1][1] =  cu_sv;
        this->_p[3][1][2] =  T(0);
      }
      if(d1>2 && d2>1)
      {
        this->_p[3][2][0] = -su_cv;	// S_uuuvv
        this->_p[3][2][1] =  cu_cv;
        this->_p[3][2][2] =  T(0);
      }
      if(d1 && d2>2)
      {
        this->_p[1][3][0] = -su_sv;	// S_uvvv
        this->_p[1][3][1] =  cu_sv;
        this->_p[1][3][2] =  T(0);
      }
      if(d1>1 && d2>2)
      {
        this->_p[2][3][0] = -cu_sv;	// S_uuvvv
        this->_p[2][3][1] = -su_sv;
        this->_p[2][3][2] =  T(0);
      }
      if(d1>2 && d2>2)
      {
        this->_p[3][3][0] =  su_sv;	// S_uuuvvv
        this->_p[3][3][1] = -cu_sv;
        this->_p[3][3][2] =  T(0);
      }
    }
  }


  template <typename T>
  inline
  T DPSphere<T>::getRadius() const {

    return _radius;
  }


  template <typename T>
  inline
  T DPSphere<T>::getStartPU() {

    return T(0);
  }


  template <typename T>
  inline
  T DPSphere<T>::getStartPV() {

    return -T(M_PI_2);
  }


  template <typename T>
  inline
  bool DPSphere<T>::isClosedU() const {

    return true;
  }


  template <typename T>
  inline
  bool DPSphere<T>::isClosedV() const {

    return false;
  }


  template <typename T>
  inline
  void DPSphere<T>::setRadius( T radius ) {

    _radius = radius;
  }
}
