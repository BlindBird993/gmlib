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



/*! \file gmglprogram.cpp
 *
 *  Pending Documentation
 */


#include "gmglprogram.h"

// gmlib
#include "gmglshadermanager.h"

namespace GMlib {

namespace GL {


  GLProgram::GLProgram( const std::string& name ) {

    if( !GLShaderManager::isInitialized() )
      return;

    _name = name;

    GLShaderManager::createProgram( name );

    _id = GLShaderManager::getProgramID( _name );
  }

  GLProgram::GLProgram( const GLProgram &copy ) {

    if( !GLShaderManager::isInitialized() )
      return;

    _name = copy._name;
    _id = copy._id;
  }

  GLProgram::~GLProgram() {}

  bool GLProgram::addShader( const std::string& name, const std::string& source, GLenum type, bool compile ) const {


    if( !GLShaderManager::createShader( name, type ) )
      return false;

    bool ret = true;

    if( !GLShaderManager::setShaderSource( name, source) )
      ret = false;

    if( !GLShaderManager::addShaderToProgram( _name, name ) )
      ret = false;

    if( compile )
      if( !GLShaderManager::compileShader( name ) )
        ret = false;

    return ret;
  }

  bool GLProgram::addShader( const GLShader& shader ) const {

    return GLShaderManager::addShaderToProgram( _name, shader.getName() );
  }

  void GLProgram::bind() const {

    GL_CHECK(glUseProgram( _id ));
  }

  void GLProgram::disableAttributeArray( const std::string& name ) const {

    disableAttributeArray( getAttributeLocation(name) );
  }

  void GLProgram::disableAttributeArray( GLuint loc ) const {

    GL_CHECK(glDisableVertexAttribArray( loc ));
  }

  void GLProgram::enableAttributeArray( const std::string& name ) const {

    enableAttributeArray( getAttributeLocation( name ) );
  }

  void GLProgram::enableAttributeArray( GLuint loc ) const {

    GL_CHECK(glEnableVertexAttribArray( loc ));
  }

  GLuint GLProgram::getAttributeLocation(const std::string& name) const {

    GLuint loc;
    GL_CHECK(loc = glGetAttribLocation( _id, name.c_str() ));
    return loc;
  }

  GLuint GLProgram::getId() const {

    return _id;
  }

  std::string GLProgram::getInfoLog() const {

  //      return _info_log;
    return std::string();
  }

  const std::string& GLProgram::getName() const {

    return _name;
  }

  std::set<std::string> GLProgram::getShaders() const {


    return GLShaderManager::getProgramShaders( _name );
  }

  GLuint GLProgram::getUniformBlockIndex(const std::string &name) const {

    GLuint block_index;
    GL_CHECK(block_index = glGetUniformBlockIndex( _id, name.c_str() ));
    return block_index;
  }

  GLuint GLProgram::getUniformLocation(const std::string& name) const {

    GLuint uniform_loc;
    GL_CHECK(uniform_loc = glGetUniformLocation( _id, name.c_str() ));
    return uniform_loc;
  }

  bool GLProgram::link() const {

    return GLShaderManager::linkProgram( _name );
  }

  bool GLProgram::removeShader(const std::string &name) const {

    return GLShaderManager::removeShaderFromProgram( _name, name );
  }

  bool GLProgram::removeShader( GLShader* shader ) const {

    return GLShaderManager::removeShaderFromProgram( _name, shader->getName() );
  }

  void GLProgram::setUniform(const std::string &name, bool b) const {

    GL_CHECK(glUniform1i( getUniformLocation(name), b ));
  }

  void GLProgram::setUniform(const std::string& name, const Color &c) const {

    GL_CHECK(glUniform4f(
        getUniformLocation( name ),
        c.getRedC(), c.getGreenC(), c.getBlueC(), c.getAlphaC()
        ));
  }

  void GLProgram::setUniform(const std::string& name, const HqMatrix<float, 3> &matrix, int count, bool transpose) const {

    GL_CHECK(glUniformMatrix4fv(
        getUniformLocation( name ),
        count, transpose, matrix.getPtr()
        ));
  }

  void GLProgram::setUniform(const std::string &name, const Point<float, 3> &p) const {

    GL_CHECK(glUniform3fv(
        getUniformLocation(name),
        3 * sizeof(float), p.getPtr()
        ));
  }

  void GLProgram::setUniform(const std::string &name, GLuint tex_id, GLenum tex_unit, GLuint tex_nr ) const {

    GL_CHECK(glActiveTexture( tex_unit ));
    GL_CHECK(glBindTexture( GL_TEXTURE_2D, tex_id ));
    GL_CHECK(glUniform1i( getUniformLocation( name ), tex_nr ));
  }

  void GLProgram::setUniform(const std::string &name, float f) const {

    GL_CHECK(glUniform1f( getUniformLocation( name ), f ));
  }

  void GLProgram::setUniform( const std::string& name, int i ) const {

    GL_CHECK(glUniform1i( getUniformLocation( name ), i ));
  }

  void GLProgram::unbind() const {

    GL_CHECK(glUseProgram( 0 ));
  }

  GLProgram& GLProgram::operator = ( const GLProgram& copy ) {

    _name = copy._name;
    _id = copy._id;

    return *this;
  }

} // END namespace GL

} // END namespace GMlib
