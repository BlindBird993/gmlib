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



/*! \file gmsortobject.c
 *
 *  Description
 */


namespace GMlib {


  template <typename T, typename G>
  SortObject<T,G>::SortObject( const T& obj, const G& value ) {

    _obj = obj;
    _value = value;
  }


  template <typename T, typename G>
  const T& SortObject<T,G>::getObject() const {

    return _obj;
  }


  template <typename T, typename G>
  const G& SortObject<T,G>::getValue() const {

    return _value;
  }


  template <typename T, typename G>
  bool SortObject<T,G>::operator < ( const SortObject<T,G>& obj ) const {

    return _value < obj._value;
  }

} // END namespace GMlib