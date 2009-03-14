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



/*! \file gmDPButterfly.c
 *
 *  Implementation of the DPButterfly template class.
 *
 *  \date   2008-09-10
 */


namespace GMlib {


  template <typename T>
  inline
  DPButterfly<T>::DPButterfly( T size ) : DCurve<T>( new PButterfly<T, 3>(size) ) {

    init();
  }


  template <typename T>
  inline
  DPButterfly<T>::DPButterfly( const DPButterfly<T>& copy ) : DCurve<T>( copy ) {

    init();
  }


  template <typename T>
  inline
  DPButterfly<T>::DPButterfly( const PButterfly<T,3>& copy ) : DCurve<T>( copy ) {

    init();
  }


  template <typename T>
  DPButterfly<T>::~DPButterfly() {}


  template <typename T>
  inline
  DPButterfly<T>::DPButterfly( PButterfly<T,3>* copy ) : DCurve<T>( copy ) {

    _l_ref = copy;
  }


  template <typename T>
  inline
  string DPButterfly<T>::getIdentity() const {

    return "DPButterfly";
  }


  template <typename T>
  inline
  PButterfly<T,3>* DPButterfly<T>::getPButterfly() {

    return _l_ref;
  }


  template <typename T>
  void DPButterfly<T>::init() {

    _l_ref = dynamic_cast<PButterfly<T,3>*>( this->_p_ref );
  }

}
