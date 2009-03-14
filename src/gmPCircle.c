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



/*! \file gmPCircle.c
 *
 *  Implementation of the PCircle template class.
 *
 *  \date   2008-09-09
 */


namespace GMlib {



  template <typename T, int n>
  inline
  PCircle<T, n>::PCircle ( T radius ) {

    this->_dm = GM_DERIVATION_EXPLICIT;
    _r = radius;
  }


  template <typename T, int n>
  inline
  PCircle<T, n>::PCircle ( const PCircle& c ) : PCurve<T,n>( c ) {

    _r = c._r;
  }


  template <typename T, int n>
  inline
  void PCircle<T, n>::eval( T t, int d, bool l ) {

    this->_p.setDim( d + 1 );

    this->_p[0][0] = _r * cos( t );
    this->_p[0][1] = _r * sin( t );
    this->_p[0][2] = T(0);

    if( this->_dm == GM_DERIVATION_EXPLICIT ) {

      if( d > 0 ) {

        this->_p[1][0] = - _r *  sin( t );
        this->_p[1][1] =   _r *  cos( t );
        this->_p[1][2] =   T(0);
      }

      if( d > 1 ) {

        this->_p[2][0] = - _r *  cos( t );
        this->_p[2][1] = - _r *  sin( t );
        this->_p[2][2] =   T(0);
      }
    }
  }


  template <typename T, int n>
  inline
  T PCircle<T, n>::getEndP() {

    return T( M_2PI );
  }


  template <typename T, int n>
  std::string PCircle<T,n>::getIdentity() const {

    return "PCircle";
  }


  template <typename T, int n>
  inline
  T PCircle<T, n>::getStartP() {

    return T(0);
  }


  template <typename T, int n>
  inline
  T PCircle<T, n>::getRadius() {

    return _r;
  }


  template <typename T, int n>
  inline
  bool PCircle<T, n>::isClosed() const {

    return true;
  }


  template <typename T, int n>
  inline
  void PCircle<T, n>::setRadius( T radius ) {

      _r = radius;
  }

}
