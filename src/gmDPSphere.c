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


  template <typename T>
  inline
  DPSphere<T>::DPSphere( T radius ) : DSurf<T>( new PSphere<T, 3>( radius ) ) {

    init();
  }


  template <typename T>
  inline
  DPSphere<T>::DPSphere( T radius, int s1, int s2 ) : DSurf<T>( new PSphere<T, 3>( radius, s1, s2 ) ) {

    init();
  }


  template <typename T>
  inline
  DPSphere<T>::DPSphere( const DPSphere<T>& copy ) : DSurf<T>( copy ) {

    init();
  }


  template <typename T>
  inline
  DPSphere<T>::DPSphere( const PSphere<T,3>& copy ) : DSurf<T>( copy ) {

    init();
  }


  template <typename T>
  inline
  DPSphere<T>::DPSphere( PSphere<T,3>* copy ) : DSurf<T>( copy ) {

    _l_ref = copy;
  }


  template <typename T>
  DPSphere<T>::~DPSphere() {}


  template <typename T>
  inline
  string DPSphere<T>::getIdentity() const {

    return "DPSphere";
  }


  template <typename T>
  inline
  PSphere<T,3>* DPSphere<T>::getPSphere() {

    return _l_ref;
  }


  template <typename T>
  inline
  T DPSphere<T>::getRadius() const {

    return _l_ref->getRadius();
  }


  template <typename T>
  inline
  void DPSphere<T>::setRadius( T radius ) {

    _l_ref->setRadius( radius );
  }


  template <typename T>
  inline
  const PSphere<T,3>* const   DPSphere<T>::getPSphere() const {

    return _l_ref;
  }


  template <typename T>
  inline
  void DPSphere<T>::init() {

    _l_ref = dynamic_cast<PSphere<T,3>*>( this->_p_ref );
  }

}
