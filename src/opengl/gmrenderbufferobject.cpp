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


namespace GMlib {

namespace GL {

  GLuintCMap RenderbufferObject::_ids;

  RenderbufferObject::RenderbufferObject() : _name("") {

    _id = OGL::createRbo();
    _valid = true;

    _ids[_id] = 1;
  }

  RenderbufferObject::RenderbufferObject(const std::string name) : _name(name) {

    _valid = OGL::createRbo( name );
    _id = OGL::getRboId( name );

    _ids[_id] = 1;
  }

  RenderbufferObject::RenderbufferObject(const RenderbufferObject &copy) {

    _name = copy._name;
    _id = copy._id;

    _ids[_id]++;
  }

  RenderbufferObject::~RenderbufferObject() {

    _ids[_id]--;
    if( _ids.count(_id) <= 0 )
      OGL::deleteRbo( _id );
  }


  void RenderbufferObject::createStorage(GLenum internal_format, GLsizei width, GLsizei height) const {

    GLuint id = safeBind();
    GL_CHECK(glRenderbufferStorage( GL_RENDERBUFFER, internal_format, width, height ));
    safeUnbind(id);
  }

  GLuint RenderbufferObject::getId() const {

    return _id;
  }

  std::string RenderbufferObject::getName() const {

    return _name;
  }

  bool RenderbufferObject::isValid() const {

    return _valid;
  }

  GLint RenderbufferObject::safeBind() const {

    GLint id;
    GL_CHECK(glGetIntegerv( GL_RENDERBUFFER_BINDING, &id ));
    bind();

    return id;
  }

  void RenderbufferObject::safeUnbind( GLint id ) const {

    GL_CHECK(glBindRenderbuffer( GL_RENDERBUFFER, id ));
  }


} // END namespace GL

} // END namespace GMlib
