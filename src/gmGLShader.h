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



/*! \file gmGLShader.h
 *
 *  Pending Documentation
 *
 *  \date   2010-11-04
 */

#ifndef __gmGLSHADER_H__
#define __gmGLSHADER_H__


// STL
#include <string>

// GMlib
#include "gmOpenGL.h"


namespace GMlib {

  class GLShader {
  public:
    GLShader( const std::string& name, GLenum type );
    GLShader( const std::string& name, const std::string& source, GLenum type );
    GLShader( const GLShader& copy );
    ~GLShader();

    bool                  compile();
    std::string           getInfoLog() const;
    GLuint                getId() const;
    const std::string&    getName() const;
    GLenum                getType() const;
    bool                  isCompiled() const;
    void                  set( const std::string& source );

  protected:
    std::string           _name;

  }; // END class GLShader

} // END namespace GMlib

#endif // __gmGLSHADER_H__
