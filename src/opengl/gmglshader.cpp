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



/*! \file gmglshader.cpp
 *
 *  Pending Documentation
 */


#include"gmglshader.h"

#include "gmglshadermanager.h"


namespace GMlib {



GLShader::GLShader( const std::string& name, const std::string& source, GLenum type) {

  if( !GLShaderManager::isInitialized() )
    return;

  _name = name;

  GLShaderManager::createShader( name, type );
  GLShaderManager::setShaderSource( name, source );
}

GLShader::GLShader( const std::string& name, GLenum type ) {

  _name = name;

  GLShaderManager::createShader( name, type );
}

GLShader::GLShader(const GLShader &copy) {

  if( !GLShaderManager::isInitialized() )
    return;

  _name = copy._name;
}

GLShader::~GLShader() {}

bool GLShader::compile() {

  return GLShaderManager::compileShader( _name );
}

std::string GLShader::getInfoLog() const {

  return std::string();
}

GLuint GLShader::getId() const {

  return GLShaderManager::getShaderID( _name );
}

const std::string& GLShader::getName() const {

  return _name;
}

GLenum GLShader::getType() const {

  return GLShaderManager::getShaderType( _name );
}

bool GLShader::isCompiled() const {

  return true;
}

void GLShader::set( const std::string& source ) {

  GLShaderManager::setShaderSource( _name, source );
}

}
