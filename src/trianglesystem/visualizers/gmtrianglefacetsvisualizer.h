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



/*! \file gmtrianglefacetsvisualizer.h
 *
 *  Interface for the TriangleFacetsVisualizer class.
 */


#ifndef __gmTRIANGLEFACETSVISUALIZER_H__
#define __gmTRIANGLEFACETSVISUALIZER_H__


// gmlib::scenegraph
#include <scenegraph/visualizer/gmvisualizer.h>

// gmlib::opengl
#include <opengl/gmopengl.h>


namespace GMlib {

  template <typename T>
  class TriangleFacets;

  template <typename T>
  class TriangleFacetsVisualizer : public Visualizer {
  public:
    TriangleFacetsVisualizer();
    ~TriangleFacetsVisualizer();
    std::string   getIdentity() const;
    virtual void  replot();
    void          set( SceneObject* obj );


    static void   fillStandardVBO(  GLVertexBufferObject& vbo,
                                    unsigned int& no_vertices,
                                    const TriangleFacets<T>* tf );


  protected:
    TriangleFacets<T>      *_tf;

  }; // END class TriangleFacetsVisualizer

} // END namespace GMlib

// Include TriangleFacetsVisualizer class function implementations
#include "gmtrianglefacetsvisualizer.c"



#endif // __gmTRIANGLEFACETSVISUALIZER_H__
