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



#include "gmtexture.h"


namespace GMlib {

namespace GL {

  GLuintCMap Texture::_ids;

  Texture::Texture(GLenum target) : _name(""), _target(target), _valid(true) {

    _id = OGL::createTex();

    _ids[_id] = 1;
  }

  Texture::Texture(const std::string name) : _name(name) {

    _valid = OGL::createTex( _name, GL_TEXTURE_2D );

    _target = OGL::getTexTarget( _name );
    _id     = OGL::getTexId( _name );

    _ids[_id] = 1;
  }

  Texture::Texture(const std::string name, GLenum target) : _name(name), _target(target) {

    _valid = OGL::createBo( _name, _target );
    _id = OGL::getBoId( _name );

    _ids[_id] = 1;
  }

  Texture::Texture(const Texture &copy) {

    _name   = copy._name;
    _id     = copy._id;
    _target = copy._target;

    _valid  = copy._valid;

    _ids[_id]++;
  }

  Texture::~Texture() {

    _ids[_id]--;
    if( _ids.count(_id) <= 0 )
      OGL::deleteTex(_id);
  }

  GLuint Texture::getId() const {

    return _id;
  }

  std::string Texture::getName() const {

    return _name;
  }

  GLenum Texture::getTarget() const {

    return _target;
  }

  bool Texture::isValid() const {

    return _valid;
  }

  void Texture::safeBind() const {

    glGetIntegerv( _target, &_safe_id );
    bind();
  }

  void Texture::safeUnbind() const {

    glBindFramebuffer( _target, _safe_id );
  }

  void Texture::setParameterf(GLenum pname, GLfloat param) {

    safeBind();
    glTexParameterf( _target, pname, param );
    safeUnbind();
  }

  void Texture::setParameteri( GLenum pname, GLint param) {

    safeBind();
    glTexParameteri( _target, pname, param );
    safeUnbind();
  }

  void Texture::setTarget(GLenum target) const {

    _target = target;
    OGL::setTexTarget( _name, _target );
  }


} // END namesapce GL

} // END namespace GMlib

