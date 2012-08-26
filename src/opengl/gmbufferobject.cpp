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

  GLuintCMap BufferObject::_ids;

  BufferObject::BufferObject( GLenum target ) {

    _name = "";
    _id = OGL::createBo();
    _target = target;
    _valid = true;

    _ids[_id] = 1;
  }

  BufferObject::BufferObject( const std::string name ) {

    _name = name;

    _valid = OGL::createBo( _name, GL_ARRAY_BUFFER );

    _target = OGL::getBoTarget( _name );
    _id = OGL::getBoId( _name );

    _ids[_id] = 1;
  }

  BufferObject::BufferObject( const std::string name, GLenum target ) {

    _name = name;
    _target = target;

    _valid = OGL::createBo( _name, _target );
    _id = OGL::getBoId( _name );

    _ids[_id] = 1;
  }

  BufferObject::BufferObject( const BufferObject& copy ) {

    _name = copy._name;
    _id   = copy._id;
    _target = copy._target;
    _valid = copy._valid;

    _ids[_id]++;
  }

  BufferObject::~BufferObject() {

    _ids[_id]--;
    if( _ids.count(_id) <= 0 )
      OGL::deleteBo(_id);
  }

  void BufferObject::createBufferData(GLsizeiptr size, const GLvoid *data, GLenum usage) {

    glBufferData( _target, size, data, usage );
  }

  void BufferObject::disableVertexArrayPointer( GLuint vert_loc ) {

    glDisableVertexAttribArray( vert_loc );
  //  release();
  }

  void BufferObject::enableVertexArrayPointer( GLuint vert_loc, int size, GLenum type, bool normalized, GLsizei stride, const void* offset ) {

  //  bind();
    glVertexAttribPointer( vert_loc, size, type, normalized, stride, offset );
    glEnableVertexAttribArray( vert_loc );

  }

  GLuint BufferObject::getId() const {

    return _id;
  }

  GLenum BufferObject::getTarget() const {

    return _target;
  }

  std::string BufferObject::getName() const {

    return _name;
  }

  bool BufferObject::isValid() const {

    return _valid;
  }

  void BufferObject::setTarget( GLenum target ) {

    _target = target;
    OGL::setBoTarget( _name, _target );
  }

  void BufferObject::unmapBuffer() const {

    glUnmapBuffer( _target );
  }


} // END namespace GMlib
