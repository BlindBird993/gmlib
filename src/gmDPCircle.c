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



/*! \file gmDPCircle.c
 *
 *  Implementation of the DPCircle template class.
 *
 *  \date   2008-09-09
 */


namespace GMlib {


  template <typename T>
  inline
  DPCircle<T>::DPCircle( T radius ) : DCurve<T>( new PCircle<T, 3>( radius ) ) {

    init();
  }


  template <typename T>
  inline
  DPCircle<T>::DPCircle( const DPCircle<T>& copy ) : DCurve<T>(copy) {

    init();
  }


  template <typename T>
  inline
  DPCircle<T>::DPCircle( const PCircle<T,3>& copy ) : DCurve<T>(copy) {

    init();
  }


  template <typename T>
  inline
  DPCircle<T>::DPCircle( PCircle<T,3>* copy ) : DCurve<T>(copy) {

    _l_ref = copy;
  }


  template <typename T>
  DPCircle<T>::~DPCircle() {}


  template <typename T>
  inline
  string DPCircle<T>::getIdentity() const {

    return "DPCircle";
  }


  template <typename T>
  inline
  PCircle<T,3>* DPCircle<T>::getPCircle() {

    return _l_ref;
  }


  template <typename T>
  void DPCircle<T>::init() {

    _l_ref = dynamic_cast<PCircle<T,3>*>( this->_p_ref );
  }

}
