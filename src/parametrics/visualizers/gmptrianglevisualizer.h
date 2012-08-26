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



/*! \file gmptrianglevisualizer.h
 *
 *  Interface for the PTriangleVisualizer class.
 */


#ifndef __gmPTRIANGLEVISUALIZER_H__
#define __gmPTRIANGLEVISUALIZER_H__


// gmlib
#include <core/types/gmpoint.h>
#include <core/containers/gmdvector.h>
#include <core/containers/gmdmatrix.h>
#include <opengl/gmopengl.h>
#include <scene/visualizer/gmvisualizer.h>



#define PTRIANGLEVERTEX_SIZE 32
#define PTRIANGLEVERTEXATTRIB_SIZE 32

namespace GMlib {

  template <typename T>
  class PTriangle;

  struct PTriangleVertex {
    float x, y, z;
    float nx, ny, nz;
    float padding[2];
  };

  struct PTriangleVertexAttributes {
    float r, g, b, a;
    float padding[4];
  };

  template <typename T>
  class PTriangleVisualizer : public Visualizer {
  public:
    PTriangleVisualizer();
    ~PTriangleVisualizer();

    std::string     getIdentity() const;
    virtual void    replot(
      const DVector< DMatrix< Vector<T,3> > >& p,int m
    );
    void            set( SceneObject* obj );


    static void     fillStandardVBO( GLuint vbo_id, const DVector< DMatrix< Vector<T,3> > >& p );
    static void     fillTriangleIBO( GLuint ibo_id, int m );
    static void     fillTriangleStripIBO( GLuint ibo_id, int m );
    static int      getNoIndicesInTriangleStrip( int strip_idx );
    static int      getNoTriangleStrips( int m );
    static int      getNoTriangles( int m );
    static void     getTriangleStripDrawInfo( int strip_idx, int& offset, int& no_indices );
    static int      getTriangleStripOffset( int strip_idx );

  protected:
    PTriangle<T>    *_triangle;

  }; // END class PTriangleVisualizer

} // END namespace GMlib

// Include PTriangleVisualizer class function implementations
#include "gmptrianglevisualizer.c"



#endif // __gmPTRIANGLEVISUALIZER_H__
