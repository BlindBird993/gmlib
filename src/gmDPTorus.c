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



/*! \file gmDPTorus.c
 *
 *  Implementation of the DPTorus template class.
 *
 *  \date   2008-11-26
 */




namespace GMlib {


  template <typename T>
  inline
  DPTorus<T>::DPTorus( T wheelrad, T tuberad1, T tuberad2 ) : DSurf<T>( new PTorus<T, 3>( wheelrad, tuberad1, tuberad2 ) ) {

    init();
  }


  template <typename T>
  inline
  DPTorus<T>::DPTorus( const DPTorus<T>& copy ) : DSurf<T>( copy ) {

    init();
  }


  template <typename T>
  inline
  DPTorus<T>::DPTorus( const PTorus<T,3>& copy ) : DSurf<T>( copy ) {

    init();
  }


  template <typename T>
  inline
  DPTorus<T>::DPTorus( PTorus<T,3>* copy ) : DSurf<T>( copy ) {

    _l_ref = copy;
  }


  template <typename T>
  DPTorus<T>::~DPTorus() {}


  template <typename T>
  inline
  string DPTorus<T>::getIdentity() const {

    return "DPTorus";
  }


  template <typename T>
  inline
  PTorus<T,3>* DPTorus<T>::getPTorus() {

    return _l_ref;
  }


  template <typename T>
  void DPTorus<T>::init() {

    _l_ref = dynamic_cast<PTorus<T,3>*>( this->_p_ref );
  }

}

