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



/*! \file gmpsurfvisualizer.h
 *
 *  Interface for the PSurfVisualizer class.
 */


#ifndef __GMPSURFVISUALIZER_H__
#define __GMPSURFVISUALIZER_H__


// gmlib::core
#include <core/types/gmpoint.h>
#include <core/containers/gmdmatrix.h>

// gmlib::opengl
#include <opengl/gmopengl.h>

// gmlib::scenegraph
#include <scenegraph/visualizer/gmvisualizer.h>


namespace GMlib {

  template <typename T>
  class PSurf;

  template <typename T>
  class PSurfVisualizer : public Visualizer {
  public:
    PSurfVisualizer();
    ~PSurfVisualizer();


    std::string   getIdentity() const;
    virtual void  replot(
      DMatrix< DMatrix< Vector<T, 3> > >& p,
      DMatrix< Vector<T, 3> >& normals,
      int m1, int m2, int d1, int d2
    );
    void          set( SceneObject* obj );


    static void   fillStandardIBO( GLuint vbo_id, int m1, int m2 );
//    static void   fillStandardTBO( GLuint tbo_id, GLuint tex_id, DMatrix< DMatrix< Vector<T, 3> > >& p, int d1 = 0, int d2 = 0 );
    static void   fillStandardVBO(GLVertexBufferObject<GLVertexNormalTex2D> &vbo,
                                  unsigned int &no_vertices,
                                  const DMatrix< DMatrix< Vector<T, 3> > >& p );
    static void   fillTriangleStripIBO( GLuint ibo_id, int m1, int m2 );
    static void   fillTriangleStripTexVBO( GLuint vbo_id, int m1, int m2 );
    static void   fillTriangleStripNormalVBO( GLuint vbo_id, DMatrix< Vector<T, 3> >& normals );
    static void   fillTriangleStripVBO( GLuint vbo_id, DMatrix< DMatrix< Vector<T, 3> > >& p, int d1 = 0, int d2 = 0 );
    static int    getNoIndicesPerTriangleStrip( int m1, int m2 );
    static int    getNoTriangleStrips( int m1, int m2 );
    static void   getTriangleStripDataInfo( const DMatrix< DMatrix< Vector<T, 3> > >& p, int& no_dp, int& no_strips, int& no_verts_per_strips );


  protected:
    PSurf<T>      *_surf;

  }; // END class PSurfVisualizer

} // END namespace GMlib

// Include PSurfVisualizer class function implementations
#include "gmpsurfvisualizer.c"



#endif // __GMPSURFVISUALIZER_H__
