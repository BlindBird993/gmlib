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



/*! \file gmDPArc.c
 *
 *  Implementation of the DPArc template class.
 *
 *  \date   2008-11-16
 */


namespace GMlib {


  template <typename T>
  inline
  DPArc<T>::DPArc( T speed, T curvature ) : DCurve<T> ( new PArc<T, 3>( speed, curvature ) ) {

    init();
  }


  template <typename T>
  inline
  DPArc<T>::DPArc( T speed, T curvature, T start, T end ) : DCurve<T>( new PArc<T, 3>( speed, curvature, start, end ) ) {

    init();
  }


  template <typename T>
  inline
  DPArc<T>::DPArc( const DPArc<T>& copy ) : DCurve<T>(copy) {

    init();
  }


  template <typename T>
  inline
  DPArc<T>::DPArc( const PArc<T,3>& copy ) : DCurve<T>(copy) {

    init();
  }


  template <typename T>
  inline
  DPArc<T>::DPArc( PArc<T,3>* copy ) : DCurve<T>(copy) {

    _l_ref = copy;
  }


  template <typename T>
  inline
  DPArc<T>::~DPArc() {}


  template <typename T>
  inline
  PArc<T,3>* DPArc<T>::getPArc() {

    return _l_ref;
  }


  template <typename T>
  inline
  string DPArc<T>::getIdentity() const {

    return "DPArc";
  }


  template <typename T>
  void DPArc<T>::init() {

    _l_ref = dynamic_cast<PArc<T,3>*>( this->_p_ref );
  }

}

