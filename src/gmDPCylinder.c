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


  template <typename T>
  inline
  DPCylinder<T>::DPCylinder( T rx, T ry, T h ) : DSurf<T>( new PCylinder<T,3>( rx, ry, h ) ) {

    init();
  }


  template <typename T>
  inline
  DPCylinder<T>::DPCylinder( const DPCylinder<T>& pcylinder ) : DCurve<T>(pcylinder)  {

    init();
  }


  template <typename T>
  inline
  DPCylinder<T>::DPCylinder( const PCylinder<T,3>& pcylinder ) : DCurve<T>(pcylinder) {

    init();
  }


  template <typename T>
  inline
  DPCylinder<T>::DPCylinder( PCylinder<T,3> *copy ) : DSurf<T>( copy ){

    _l_ref = copy;
  }


  template <typename T>
  inline
  DPCylinder<T>::~DPCylinder() {}


  template <typename T>
  inline
  std::string DPCylinder<T>::getIdentity() const {

    return "DPCylinder";
  }


  template <typename T>
  inline
  PCylinder<T,3>* DPCylinder<T>::getPCylinder() {

    return _l_ref;
  }


  template <typename T>
  inline
  const PCylinder<T,3>* const DPCylinder<T>::getPCylinder() const {

    return _l_ref;
  }


  template <typename T>
  inline
  void DPCylinder<T>::init() {

    _l_ref = dynamic_cast<PCylinder<T,3>*>( this->_p_ref );
  }

}

