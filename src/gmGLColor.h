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



/*! \file gmGLColor.h
 *
 *  An extended GL implementation of the color class
 *
 *  \date   2009-03-06
 */

#ifndef __gmGLCOLOR_H__
#define __gmGLCOLOR_H__


// GMlib includes
#include "gmColor.h"
#include "gmOpenGL.h"


namespace GMlib {




  /*! \class Color
   *  \brief A color class
   *
   *  A color class defining a color object and "color" operations
   */
  class GLColor : public Color {
  public:
    GLColor( unsigned int n = 0 );
    GLColor( unsigned char r, unsigned char g, unsigned char b, unsigned char a=255);
    GLColor( int r, int g, int b, int a=255);
    GLColor( double r, double g, double b, double a=1.0);
    GLColor( const GLColor& copy );
    GLColor( const Color& copy );


    void    glSet() const;
    void    glSetInverse() const;


  }; // END class GLColor


} // END namespace GMlib


// Include inline GLColor function implementations
#include "gmGLColor.c"

#endif // __gmGLCOLOR_H__
