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



/*! \file   gmDPTCurve.c
 *
 *  Implementation of the gmDPTCurve template class.
 *
 *  \date   2008-11-26
 */


namespace GMlib {


  template <typename T>
  inline
  DPTCurve<T>::DPTCurve( PCurve<T, 3>* pcA, PCurve<T, 3>* pcB ) : DCurve<T>( new PTCurve<T, 3>( pcA, pcB ) ) {

    _ptc = dynamic_cast<PTCurve<T, 3>*>(this->_p_ref);
  }


  template <typename T>
  inline
  void DPTCurve<T>::localSimulate( double dt ) {

    _ptc->setAngle( dt );
    this->replot( this->_no_samp, this->_dynamic );
  }


  template <typename T>
  inline
  void DPTCurve<T>::setPA( PCurve<T, 3>* pA ) {

    _ptc->setPA( pA );
  }


  template <typename T>
  inline
  void DPTCurve<T>::setPB( PCurve<T, 3>* pB ) {

    _ptc->setPB( pB );
  }
}
