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



/*! \file gmglprogram.h
 *
 *  Pending Documentation
 */

#ifndef __gmGLPROGRAM_H__
#define __gmGLPROGRAM_H__


#include "gmopengl.h"
#include "gmglshader.h"

// gmlib::core
#include <core/types/gmpoint.h>

// stl
#include <string>
#include <set>



namespace GMlib {

  class GLProgram {
  public:
    GLProgram( const std::string& name );
    GLProgram( const GLProgram& copy );
    ~GLProgram();

    bool                      addShader( const std::string& name, const std::string& source, GLenum type, bool compile = false ) const;
    bool                      addShader( const GLShader& shader ) const;
    void                      bind() const;
    void                      disableAttributeArray( const std::string& name ) const;
    void                      disableAttributeArray( GLuint location ) const;
    void                      enableAttributeArray( const std::string& name ) const;
    void                      enableAttributeArray( GLuint ) const;
    GLuint                    getAttributeLocation( const std::string& name ) const;
    GLuint                    getId() const;
    std::string               getInfoLog() const;
    const std::string&        getName() const;
    std::set< std::string>    getShaders() const;
    GLuint                    getUniformLocation( const std::string& name ) const;
    bool                      link() const;
    bool                      removeShader( const std::string& name ) const;
    bool                      removeShader( GLShader* shader ) const;
    void                      setUniform( const std::string& name, bool b ) const;
    void                      setUniform( const std::string& name, const Color& c ) const;
    void                      setUniform( const std::string& name, const HqMatrix<float,3>& matrix, int count, bool transpose ) const;
    void                      setUniform( const std::string& name, const Point<float,3>& p ) const;
    void                      setUniform( const std::string& name, GLuint tex_id, GLenum tex_unit, GLuint tex_nr ) const;
    void                      setUniform( const std::string& name, float f ) const;
    void                      setUniform( const std::string& name, int i ) const;
    void                      unbind() const;

    GLProgram&                operator = ( const GLProgram& copy );

  protected:
    std::string               _name;
    GLuint                    _id;

  }; // END class GLProgram

} // END namespace GMlib


#endif // __gmGLPROGRAM_H__
