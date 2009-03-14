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



/*! \file gmDPBSplineCurve.c
 *
 *  Implementation of the DPBSplineCurve template class.
 *
 *  \date   2008-10-28
 */


namespace GMlib {


  template <typename T>
  inline
  DPBSplineCurve<T>::DPBSplineCurve( const DVector< Vector<T, 3> >& cv,  int d  ) : DCurve<T>( new PBSplineCurve<T, 3>( cv, d ) ) {

    init();
  }


  template <typename T>
  inline
  DPBSplineCurve<T>::DPBSplineCurve( const DPBSplineCurve<T>& copy ) : DCurve<T>( copy ) {

    init();
  }


  template <typename T>
  inline
  DPBSplineCurve<T>::DPBSplineCurve( const PBSplineCurve<T,3>& copy ) : DCurve<T>( copy ) {

    init();
  }


  template <typename T>
  inline
  DPBSplineCurve<T>::DPBSplineCurve( PBSplineCurve<T,3>* copy ) : DCurve<T>( copy ) {

    _l_ref = copy;
  }


  template <typename T>
  DPBSplineCurve<T>::~DPBSplineCurve() {}


  template <typename T>
  inline
  string DPBSplineCurve<T>::getIdentity() const {

    return "DPBSplineCurve";
  }


  template <typename T>
  inline
  PBSplineCurve<T,3>* DPBSplineCurve<T>::getPBSplineCurve() {

    return _l_ref;
  }


  template <typename T>
  void DPBSplineCurve<T>::init() {

    _l_ref = dynamic_cast<PBSplineCurve<T,3>*>( this->_p_ref );
  }
}


