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



/*! \file gmDPPlane.c
 *
 *  Implementation of the gmDPPlane template class.
 *
 *  \date   2008-09-06
 */


namespace GMlib {

  template <typename T>
  inline
  DPPlane<T>::DPPlane( const Point<T,3>& p, const Vector<T,3>& u, const Vector<T,3>& v ) : DSurf<T>( new PPlane<T,3>( 0.0, u, v ) ) {

    translate( p.toFloat() );
    init();
  }


  template <typename T>
  inline
  DPPlane<T>::DPPlane( const DPPlane<T>& pplane ) : DSurf<T>( pplane ) {

    init();
  }


  template <typename T>
  inline
  DPPlane<T>::DPPlane( const PPlane<T,3>& pplane ) : DSurf<T>( pplane ) {

    init();
  }


  template <typename T>
  DPPlane<T>::~DPPlane() {}


  template <typename T>
  inline
  const UnitVector<T,3>& DPPlane<T>::getNormal() {

    return getPPlane()->getNormal();
  }

  template <typename T>
  inline
  PPlane<T,3>* DPPlane<T>::getPPlane() {

    return _l_ref;
  }

  template <typename T>
  inline
  std::string DPPlane<T>::getIdentity() const {

    return "DPPlane";
  }


  template <typename T>
  void DPPlane<T>::init() {

    _l_ref = dynamic_cast<PPlane<T,3>*>( this->_p_ref );
  }

}
