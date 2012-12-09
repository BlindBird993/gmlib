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



/*! \file gmptriangledefaultvisualizer.h
 *
 *  Interface for the PTriangleDefaultVisualizer class.
 */


#ifndef __gmPTRIANGLEDEFAULTVISUALIZER_H__
#define __gmPTRIANGLEDEFAULTVISUALIZER_H__


#include "gmptrianglevisualizer.h"

// gmlib
#include <opengl/gmvertexbufferobject.h>
#include <opengl/gmindexbufferobject.h>


namespace GMlib {

  template <typename T>
  class PTriangleDefaultVisualizer : public PTriangleVisualizer<T> {
  public:
    PTriangleDefaultVisualizer();
    virtual ~PTriangleDefaultVisualizer();
    void            display();
    virtual void    replot(
      const DVector< DMatrix< Vector<T,3> > >& p,int m
    );
    void            select();

  protected:
    VertexBufferObject    _vbo;
    IndexBufferObject     _ibo;

    int             _no_triangles;

  }; // END class PTriangleDefaultVisualizer

} // END namespace GMlib

// Include PTriangleDefaultVisualizer class function implementations
#include "gmptriangledefaultvisualizer.c"



#endif // __gmPTRIANGLEDEFAULTVISUALIZER_H__
