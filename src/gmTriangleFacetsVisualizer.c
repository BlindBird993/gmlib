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



/*! \file gmTriangleFacetsVisualizer.h
 *
 *  TriangleFacetsVisualizer implementations
 *
 *  \date   2011-02-07
 */

namespace GMlib {

  template <typename T>
  TriangleFacetsVisualizer<T>::TriangleFacetsVisualizer() {

    _tf = 0x0;
  }

  template <typename T>
  TriangleFacetsVisualizer<T>::~TriangleFacetsVisualizer() {}

  template <typename T>
  std::string TriangleFacetsVisualizer<T>::getIdentity() const {

    return "TriangleFacets Visualizer";
  }

  template <typename T>
  inline
  void TriangleFacetsVisualizer<T>::replot() {}

  template <typename T>
  void TriangleFacetsVisualizer<T>::set( SceneObject* obj ) {

    Visualizer::set( obj );

    _tf = dynamic_cast<TriangleFacets<T>*>( obj );
  }



} // END namespace GMlib
