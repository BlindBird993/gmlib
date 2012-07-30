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


#include "../visualizer/gmvisualizer.h"

// gmlib::core
#include <core/containers/gmdmatrix.h>

namespace GMlib {

  template <typename T, int n>
  class Selector;

  template <typename T>
  class SelectorGridVisualizer : public Visualizer {
  public:
    SelectorGridVisualizer();
    ~SelectorGridVisualizer();

    void                          display( Camera* cam );
    void                          reset();
    void                          setSelectors( DVector< Vector<T,3> >& c );
    void                          setSelectors( DMatrix< Vector<T,3> >& c );
    void                          update();

  protected:
    GLProgram                     _prog;
    GLuint                        _ibo;
    GLuint                        _vbo;
    int                           _no_indices;

    DVector< Vector<T,3>* >       _c;

  private:
    void                          _fillVBO();

  }; // END class SelectorGridVisualizer

} // END namespace GMlib

// Implementations
#include "gmselectorgridvisualizer.c"


#endif // __gmSELECTORGRIDVISUALIZER_H__
