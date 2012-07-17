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



/*! \file gmSphere3D.h
 *
 *  A graphical implementation of the Sphere class
 *
 *  \date   2009-03-06
 */

#ifndef __gmSPHERE3D_H__
#define __gmSPHERE3D_H__


#include "gmPoint.h"
#include "gmArray.h"
#include "gmOpenGL.h"
#include "gmGLProgram.h"



namespace GMlib {


  /*! \class Sphere3D
   *  \brief Pending Documentation
   *
   *  3D Sphere
   */
  class Sphere3D : public Sphere<float,3> {
  public:
    Sphere3D(float r=1.0, int m1=7, int m2=5);
    Sphere3D(const Sphere<float,3>& s, int m1=7, int m2=5);
    Sphere3D( const Sphere3D& copy );
    ~Sphere3D();

    void        display( const HqMatrix<float,3>& mvpmat, bool selected = false );
    void        display( const HqMatrix<float,3>& mvmat, const HqMatrix<float,3>& mvpmat, bool selected = false );
    void        replot(int m1, int m2);
    void        select( const HqMatrix<float,3>& mvpmat, const Color& color );

  private:
    GLProgram   _prog_light;
    GLProgram   _prog_color;
    GLProgram   _prog_select;

    int         _top_bot_verts;
    int         _mid_strips;
    int         _mid_strips_verts;
    GLuint      _vbo_v;
    GLuint      _vbo_n;

    int         _m1;
    int         _m2;

  }; // END class Sphere3D

} // END namespace GMlib


// Include Sphere3D class inline function implementations
#include "gmSphere3D.c"


#endif // __gmSPHERE3D_H__
