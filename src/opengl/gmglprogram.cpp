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
using namespace GMlib;




GLProgram::GLProgram( const std::string& name ) {

  if( !GLShaderManager::isInitialized() )
    return;

  _name = name;

  bool ok = GLShaderManager::createProgram( name );

  _id = GLShaderManager::getProgramID( _name );

//    std::cout << "  " << ( ok ? "Creating" : "Using" ) << " a GLProgram \"" << name << "\" with id: " << _id << std::endl;
}

GLProgram::GLProgram( const GLProgram &copy ) {

  if( !GLShaderManager::isInitialized() )
    return;

  _name = copy._name;
  _id = copy._id;
}

GLProgram::~GLProgram() {}

bool GLProgram::addShader( const std::string& name, const std::string& source, GLenum type, bool compile ) {


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

bool GLProgram::addShader( const GLShader& shader ) {

  return GLShaderManager::addShaderToProgram( _name, shader.getName() );
}

void GLProgram::bind() const {

  glUseProgram( _id );
}

void GLProgram::disableAttributeArray( const std::string& name ) const {

  disableAttributeArray( getAttributeLocation(name) );
}

void GLProgram::disableAttributeArray( GLuint loc ) const {

  glDisableVertexAttribArray( loc );
}

void GLProgram::enableAttributeArray( const std::string& name ) const {

  enableAttributeArray( getAttributeLocation( name ) );
}

void GLProgram::enableAttributeArray( GLuint loc ) const {

  glEnableVertexAttribArray( loc );
}

GLuint GLProgram::getAttributeLocation(const std::string& name) const {

  return glGetAttribLocation( _id, name.c_str() );
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

GLuint GLProgram::getUniformLocation(const std::string& name) const {

  return glGetUniformLocation( _id, name.c_str() );
}

bool GLProgram::link() const {

  return GLShaderManager::linkProgram( _name );
}

bool GLProgram::removeShader(const std::string &name) {

  return GLShaderManager::removeShaderFromProgram( _name, name );
}

bool GLProgram::removeShader( GLShader* shader ) {

  return GLShaderManager::removeShaderFromProgram( _name, shader->getName() );
}

void GLProgram::setUniform(const std::string &name, bool b) {

  glUniform1i( getUniformLocation(name), b );
}

void GLProgram::setUniform(const std::string& name, const Color &c) {

  glUniform4f(
      getUniformLocation( name ),
      c.getRedC(), c.getGreenC(), c.getBlueC(), c.getAlphaC()
      );
}

void GLProgram::setUniform(const std::string& name, const HqMatrix<float, 3> &matrix, int count, bool transpose) {

  glUniformMatrix4fv(
      getUniformLocation( name ),
      count, transpose, matrix.getPtr()
      );
}

void GLProgram::setUniform(const std::string &name, const Point<float, 3> &p) {

  glUniform3fv(
      getUniformLocation(name),
      3 * sizeof(float), p.getPtr()
      );
}

void GLProgram::setUniform(const std::string &name, GLuint tex_id, GLenum tex_unit, GLuint tex_nr ) {

  glActiveTexture( tex_unit );
  glBindTexture( GL_TEXTURE_2D, tex_id );
  glUniform1i( getUniformLocation( name ), tex_nr );
}

void GLProgram::setUniform(const std::string &name, float f) {

  glUniform1f( getUniformLocation( name ), f );
}

void GLProgram::setUniform( const std::string& name, int i ) {

  glUniform1i( getUniformLocation( name ), i );
}

void GLProgram::unbind() const {

  glUseProgram( 0 );
}

GLProgram& GLProgram::operator = ( const GLProgram& copy ) {

  _name = copy._name;
  _id = copy._id;

  return *this;
}

