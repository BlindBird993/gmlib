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



#include "gmshader.h"

using namespace GMlib::GL;


template <>
typename std::list<Private::ShaderInfo> Private::GLObject<Private::ShaderInfo>::_data = std::list<Private::ShaderInfo>();



Shader::Shader() {}

Shader::~Shader() { destroyObject(); }

void Shader::create(GLenum type) {

  Private::ShaderInfo info;
  info.type = type;
  createObject(info);
}

void Shader::create(const std::string &name, GLenum type) {

  Private::ShaderInfo info;
  info.name = name;
  info.type = type;
  createObject(info);
}

bool Shader::compile() {

  GL_CHECK(::glCompileShader( getId() ));

  int param;
  GL_CHECK(::glGetShaderiv( getId(), GL_COMPILE_STATUS, &param ));

  updateCompilerLog();

  return param == GL_TRUE;
}

void Shader::setSource(const std::string& source) const {

  //! \todo check whether this is necessary
  const char* src = source.c_str();
  GL_CHECK(::glShaderSource( getId(), 1, &src, 0x0 ));
}

GLenum Shader::getType() const {

  return getInfoIter()->type;
}

GLuint Shader::getCurrentBoundId() const { return 0; }

void Shader::doBind(GLuint id) const {}

GLuint Shader::doGenerate() const {

  GLuint id;
  GL_CHECK(id = ::glCreateShader( getType() ));
  return id;
}

void Shader::doDelete(GLuint id) const {

  //! \todo must also detach shader from programs

  GL_CHECK(::glDeleteShader( getId() ));
}

void Shader::updateCompilerLog() {

  InfoIter itr = getInfoIter();
  itr->compiler_log.clear();

  //! \todo Check if this can be written directly to the compile log std::string

  int len = 0;
  int written = 0;
  char *log;

  GL_CHECK(::glGetShaderiv( getId(), GL_INFO_LOG_LENGTH, &len ));

  if( len > 0 ) {

    len = len+1;
    log = new char[len];

    GL_CHECK(::glGetShaderInfoLog( getId(), len, &written, log ));

    itr->compiler_log.append( log, len );
    delete log;
  }
}
