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



/*! \file gmselectorgridvisualizer.h
 */


#ifndef __gmSELECTORGRIDVISUALIZER_H__
#define __gmSELECTORGRIDVISUALIZER_H__


#include "../gmvisualizer.h"

// gmlib
#include <core/containers/gmdmatrix.h>
#include <opengl/gmprogram.h>
#include <opengl/bufferobjects/gmvertexbufferobject.h>
#include <opengl/bufferobjects/gmindexbufferobject.h>


namespace GMlib {

  template <typename T, int n>
  class Selector;

  template <typename T>
  class SelectorGridVisualizer : public Visualizer {
    GM_VISUALIZER(SelectorGridVisualizer)
  public:
    SelectorGridVisualizer();

    void                          render(const DisplayObject *obj, const Camera *cam) const;
    void                          reset();
    void                          setLineWidth( float line_width = 1.0f );
    void                          setSelectors( DVector< Vector<T,3> >& c, int tp=0 );
    void                          setSelectors( DMatrix< Vector<T,3> >& c );
    void                          update();

  protected:
    int                           _no_indices;
    float                         _line_width;
    DVector< Vector<T,3>* >       _c;

    GL::Program                   _prog;

    GL::VertexBufferObject        _vbo;
    GL::IndexBufferObject         _ibo;

  private:
    void                          _fillVBO();

    void                          _makeLines();
    void                          _makeTriangs();

  }; // END class SelectorGridVisualizer

} // END namespace GMlib

// Implementations
#include "gmselectorgridvisualizer.c"


#endif // __gmSELECTORGRIDVISUALIZER_H__