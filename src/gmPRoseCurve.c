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



/*! \file gmPRoseCurve.c
 *
 *  Implementation of the PRoseCurve template class.
 *
 *  \date   2008-12-02
 */


namespace GMlib {


  template <typename T, int n>
  inline
  PRoseCurve<T, n>::PRoseCurve ( T radius ) {


    this->_dm = GM_DERIVATION_EXPLICIT;
    _r = radius;
  }


  template <typename T, int n>
  inline
  PRoseCurve<T, n>::PRoseCurve ( const PRoseCurve& copy ) : PCurve<T,n>( copy ) {}


  template <typename T, int n>
  inline
  void PRoseCurve<T, n>::eval( T t, int d, bool l ) {

    this->_p.setDim( d + 1 );

    this->_p[0][0] = _r * cos( T(1.75) * t) * cos(t);
    this->_p[0][1] = _r * sin( t )*cos( T(1.75) * t );
    this->_p[0][2] = T(0);

    if( this->_dm == GM_DERIVATION_EXPLICIT ) {

      if(d > 0)
      {
        this->_p[1][0] = _r * -1.75*sin(1.75*t)*cos(t)-sin(t)*cos(1.75*t);
        this->_p[1][1] = _r * -1.75*sin(t)*sin(1.75*t)+cos(1.75*t)*cos(t);
        this->_p[1][2] = 0.0;
      }
      if(d > 1)
      {
        this->_p[2][0]= _r * 3.5*sin(t)*sin(1.75*t)-4.0625*cos(1.75*t)*cos(t);
        this->_p[2][1]= _r * -3.5*sin(1.75*t)*cos(t)-4.0625*sin(t)*cos(1.75*t);
        this->_p[2][2]= 0.0;
      }
    }
  }


  template <typename T, int n>
  inline
  T PRoseCurve<T, n>::getEndP() {

    return T( 8 * M_PI );
  }


  template <typename T, int n>
  std::string PRoseCurve<T,n>::getIdentity() const {

    return "PRoseCurve";
  }


  template <typename T, int n>
  inline
  T PRoseCurve<T, n>::getStartP() {

    return T(0);
  }


  template <typename T, int n>
  inline
  bool PRoseCurve<T, n>::isClosed() const {

    return true;
  }

}

