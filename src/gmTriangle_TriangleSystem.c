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



/*! \file gmTriangle_TriangleSystem.c
 *  \brief TriangleSystem class function implementations
 *
 *  \date   2008-10-22
 */

namespace GMlib {






  template <typename T>
  inline
  void TriangleSystem<T>::adjust( Triangle<T> *t, bool wider )	{

    _tv->_adjustTriangle(t,wider);
  }


  template <typename T>
  inline
  Vertex<T>* TriangleSystem<T>::find( const Point<T,3>& p) const {

    return _tv->_find(p);
  }


  template <typename T>
  inline
  Edge<T>* TriangleSystem<T>::find( const Point<T,3>& p1,const Point<T,3>& p2){

    return _tv->_find(p1,p2);
  }


  //template <typename T>
  //inline
  //int TriangleSystem<T>::getStreamMode() {
  //
  //  return _tv->getStreamMode();
  //}


  template <typename T>
  inline
  void TriangleSystem<T>::insert( Edge<T> *e ) {

    (_tv->_getEdges()) += e;
  }


  template <typename T>
  inline
  void TriangleSystem<T>::insert( Triangle<T> *t) {

    _tv->_insertTriangle(t);
  }


  template <typename T>
  inline
  void TriangleSystem<T>::remove( Edge<T> *e) {

    (_tv->_getEdges()).remove(e);
  }


  template <typename T>
  inline
  void TriangleSystem<T>::remove( Triangle<T> *t) {

    _tv->_removeTriangle(t);
  }


  template <typename T>
  inline
  void TriangleSystem<T>::set( TriangleFacets<T>& ts ) {

    _tv = &ts;
  }

}

