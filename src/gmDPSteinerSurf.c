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



/*! \file gmDPSteinerSurf.c
 *
 *  Implementation of the gmDPSteinerSurf template class.
 *
 *  \date   2008-09-07
 */


namespace GMlib {


  template <typename T>
  inline
  DPSteinerSurf<T>::DPSteinerSurf( T radius ) : DSurf<T>( new PSteinerSurf<T,3>( radius ) ) {

    init();
  }


  template <typename T>
  inline
  DPSteinerSurf<T>::DPSteinerSurf( const DPSteinerSurf<T>& copy ) : DSurf<T>( copy ) {

    init();
  }


  template <typename T>
  inline
  DPSteinerSurf<T>::DPSteinerSurf( const PSteinerSurf<T,3>& copy ) : DSurf<T>( copy ) {

    init();
  }


  template <typename T>
  DPSteinerSurf<T>::~DPSteinerSurf() {}


  template <typename T>
  inline
  std::string DPSteinerSurf<T>::getIdentity() const {

    return "DPSteinerSurf";
  }


  template <typename T>
  inline
  PSteinerSurf<T,3>* DPSteinerSurf<T>::getPSteinerSurf() {

    return _l_ref;
  }


  template <typename T>
  void DPSteinerSurf<T>::init() {

    _l_ref = dynamic_cast<PSteinerSurf<T,3>*>( this->_p_ref );
  }

}
