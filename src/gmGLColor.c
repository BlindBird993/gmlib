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



/*! \file gmGLColor.c
 *  \brief Inline GL Color class implementations
 *
 *  Implementation of inline GL Color class functions.
 *
 *  \date   2009-03-06
 */


// GMlib includes
#include "gmOpenGL.h"


namespace GMlib {


  inline
  GLColor::GLColor( unsigned int n ) : Color( n ){}


  inline
  GLColor::GLColor( unsigned char r, unsigned char g, unsigned char b, unsigned char a ) : Color( r, g, b, a ) {}


  inline
  GLColor::GLColor( int r, int g, int b, int a ) : Color( r, g, b, a ) {}


  inline
  GLColor::GLColor( double r, double g, double b, double a ) : Color( r, g, b, a ) {}


  inline
  GLColor::GLColor( const GLColor& copy ) : Color( copy ) {}


  inline
  GLColor::GLColor( const Color& copy ) : Color( copy ) {}


//
//  /*! void Color::glSet() const
//   *  \brief Pending Documentation
//   *
//   *  Pending Documentation
//   */
  inline
  void GLColor::glSet() const {

    glColor4ubv( _color.rgba );
  }
//
//
//  /*! void Color::glSet() const
//   *  \brief Pending Documentation
//   *
//   *  Pending Documentation
//   */
  inline
  void GLColor::glSetInverse() const {

    ((GLColor)getInverse()).glSet();
  }

}
