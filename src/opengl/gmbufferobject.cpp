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


namespace GMlib {

namespace GL {

  GLuintCMap BufferObject::_ids;

  BufferObject::BufferObject(GLenum target , GLenum binding) : _valid(true), _name(""), _target(target), _binding(binding) {

    _id = OGL::createBo();

    _ids[_id] = 1;
  }

  BufferObject::BufferObject( const std::string name ) : _name(name), _binding(GL_ARRAY_BUFFER_BINDING) {

    _valid = OGL::createBo( _name, GL_ARRAY_BUFFER );

    _target = OGL::getBoTarget( _name );
    _id = OGL::getBoId( _name );

    _ids[_id] = 1;
  }

  BufferObject::BufferObject( const std::string name, GLenum target, GLenum binding ) : _name(name), _target(target) {

    _valid = OGL::createBo( _name, _target );
    _id = OGL::getBoId( _name );

    _ids[_id] = 1;
  }

  BufferObject::BufferObject( const BufferObject& copy )
    : _valid(copy._valid), _name(copy._name), _id(copy._id),
      _target(copy._target), _binding(copy._binding) {

    _ids[_id]++;
  }

  BufferObject::~BufferObject() {

    _ids[_id]--;
    if( _ids.count(_id) <= 0 )
      OGL::deleteBo(_id);
  }

  void BufferObject::createBufferData(GLsizeiptr size, const GLvoid *data, GLenum usage) const {

    GLint id = safeBind();
    GL_CHECK(glBufferData( _target, size, data, usage ));
    safeUnbind(id);
  }

  void BufferObject::disableVertexArrayPointer( GLuint vert_loc ) const {

    GL_CHECK(glDisableVertexAttribArray( vert_loc ));
  }

  void BufferObject::enableVertexArrayPointer( GLuint vert_loc, int size, GLenum type, bool normalized, GLsizei stride, const void* offset ) const {

    GL_CHECK(glVertexAttribPointer( vert_loc, size, type, normalized, stride, offset ));
    GL_CHECK(glEnableVertexAttribArray( vert_loc ));

  }

  GLenum BufferObject::getBinding() const {

    return _binding;
  }

  GLuint BufferObject::getId() const {

    return _id;
  }

  std::string BufferObject::getName() const {

    return _name;
  }

  GLenum BufferObject::getTarget() const {

    return _target;
  }

  bool BufferObject::isValid() const {

    return _valid;
  }

  GLint BufferObject::safeBind() const {

    bind();
    GLint id;
    GL_CHECK(glGetIntegerv( _binding, &id ));
    return id;
  }

  void BufferObject::safeUnbind( GLint id ) const {

    GL_CHECK(glBindBuffer( _target, id ));
  }

  void BufferObject::setBinding(GLenum binding) const {

    _binding = binding;
  }

  void BufferObject::setTarget( GLenum target ) const {

    _target = target;
    OGL::setBoTarget( _name, _target );
  }

  void BufferObject::unmapBuffer() const {

    GLint id = safeBind();
    GL_CHECK(glUnmapBuffer( _target ));
    safeUnbind(id);
  }

} // END namesapce GL

} // END namespace GMlib
