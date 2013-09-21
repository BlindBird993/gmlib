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



#include "gmbufferobject.h"

using namespace GMlib::GL;

GM_GLOBJECT_CPP(BufferObject)







BufferObject::BufferObject(GLenum target , GLenum binding)
  :  Object(), _target(target), _binding(binding) {

  create();
}

BufferObject::BufferObject( const std::string name ) : Object(name), _binding(GL_ARRAY_BUFFER_BINDING) {

  createManaged();
  _target = OGL::getBoTarget(getName());
}

BufferObject::BufferObject( const std::string name, GLenum target, GLenum binding ) : Object(name), _target(target), _binding(binding) {

  createManaged();
  _target = OGL::getBoTarget(getName());
}

BufferObject::BufferObject( const BufferObject& copy ) {

  makeCopy(copy);
  _target   = copy._target;
  _binding  = copy._binding;
}

BufferObject::~BufferObject() { destroy(); }









void BufferObject::createBufferData(GLsizeiptr size, const GLvoid *data, GLenum usage) const {

  GLint id = safeBind();
  GL_CHECK(::glBufferData( _target, size, data, usage ));
  safeUnbind(id);
}

void BufferObject::disableVertexArrayPointer( const GL::AttributeLocation& vert_loc ) const {

  GL_CHECK(::glDisableVertexAttribArray( vert_loc() ));
}

void BufferObject::doBind(GLuint id) const {

  GL_CHECK(::glBindBuffer( _target, id ));
}

GLuint BufferObject::doCreate() const {

  return OGL::createBo();
}

GLuint BufferObject::doCreateManaged() const {

  OGL::createBo( getName(), _target );
  return OGL::getBoId(getName());
}

void BufferObject::doDestroy() const {

  OGL::deleteBo(getId());
}

void BufferObject::enableVertexArrayPointer( const GL::AttributeLocation& vert_loc, int size, GLenum type, bool normalized, GLsizei stride, const void* offset ) const {

  GL_CHECK(::glVertexAttribPointer( vert_loc(), size, type, normalized, stride, offset ));
  GL_CHECK(::glEnableVertexAttribArray( vert_loc() ));
}

GLuint BufferObject::getCurrentBoundId() const {

  GLint id;
  GL_CHECK(::glGetIntegerv( _binding, &id ));
  return id;
}

GLenum BufferObject::getBinding() const {

  return _binding;
}

GLenum BufferObject::getTarget() const {

  return _target;
}

//void BufferObject::setBinding(GLenum binding) const {

//  _binding = binding;
//}

//void BufferObject::setTarget( GLenum target ) const {

//  _target = target;
//  OGL::setBoTarget( _name, _target );
//}

void BufferObject::unmapBuffer() const {

  GLint id = safeBind();
  GL_CHECK(::glUnmapBuffer( _target ));
  safeUnbind(id);
}
