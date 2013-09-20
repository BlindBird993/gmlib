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



#include "gmrenderbufferobject.h"

using namespace GMlib::GL;


GM_GLOBJECT_CPP(RenderbufferObject)




RenderbufferObject::RenderbufferObject( bool generate ) : Object() {

  if( generate ) create();
}

RenderbufferObject::RenderbufferObject(const std::string name) : Object(name) {

  createManaged();
}

RenderbufferObject::RenderbufferObject(const RenderbufferObject &copy) {

  makeCopy(copy);
}

RenderbufferObject::~RenderbufferObject() {

  destroy();
}






void RenderbufferObject::createStorage(GLenum internal_format, GLsizei width, GLsizei height) const {

  GLuint id = safeBind();
  GL_CHECK(::glRenderbufferStorage( GL_RENDERBUFFER, internal_format, width, height ));
  safeUnbind(id);
}

GLuint RenderbufferObject::getCurrentBoundId() const {

  GLint id;
  GL_CHECK(glGetIntegerv( GL_RENDERBUFFER_BINDING, &id ));
  return id;
}

void RenderbufferObject::doBind(GLuint id) const {

  GL_CHECK(::glBindRenderbuffer( GL_RENDERBUFFER, id ));
}

GLuint RenderbufferObject::doCreate() const {

  return OGL::createRbo();
}

GLuint RenderbufferObject::doCreateManaged() const {

  OGL::createRbo(getName());
  return OGL::getRboId(getName());
}

void RenderbufferObject::doDestroy() const {

  OGL::deleteRbo(getId());
}
