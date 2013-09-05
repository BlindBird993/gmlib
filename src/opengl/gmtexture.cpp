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

  Texture::Texture(GLenum target) :  _valid(true), _name(""), _target(target) {

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

    _valid = OGL::createTex( _name, _target );

    _target = OGL::getTexTarget( _name );
    _id     = OGL::getTexId( _name );

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

  void Texture::texImage1D(GLint level, GLint internal_format, GLsizei width, GLint border, GLenum format, GLenum type, GLvoid *data) {

    GLint id = safeBind();
    GL_CHECK(glTexImage1D( _target, level, internal_format, width, border, format, type, data ));
    safeUnbind(id);
  }

  void Texture::texImage2D(GLint level, GLint internal_format, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, GLvoid *data) {

    GLint id = safeBind();
    GL_CHECK(glTexImage2D( _target, level, internal_format, width, height, border, format, type, data ));
    safeUnbind(id);
  }

  void Texture::texImage3D(GLint level, GLint internal_format, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, GLvoid *data) {

    GLint id = safeBind();
    GL_CHECK(glTexImage3D( _target, level, internal_format, width, height, depth, border, format, type, data ));
    safeUnbind(id);
  }

  void Texture::getTexImage(GLint level, GLenum format, GLenum type, GLvoid* pixels) {

    GLint id = safeBind();
    GL_CHECK(::glGetTexImage( _target, level, format, type, pixels ));
    safeUnbind(id);
  }

  GLint Texture::safeBind() const {

    GLint id;
    GL_CHECK(glGetIntegerv( _target, &id ));
    bind();

    return id;
  }

  void Texture::safeUnbind( GLint id ) const {

    GL_CHECK(glBindTexture( _target, id ));
  }

  void Texture::setParameterf(GLenum pname, GLfloat param) {

    GLint id = safeBind();
    GL_CHECK(glTexParameterf( _target, pname, param ));
    safeUnbind(id);
  }

  void Texture::setParameteri( GLenum pname, GLint param) {

    GLint id = safeBind();
    GL_CHECK(glTexParameteri( _target, pname, param ));
    safeUnbind(id);
  }

  void Texture::setTarget(GLenum target) const {

    _target = target;
    OGL::setTexTarget( _name, _target );
  }


} // END namesapce GL

} // END namespace GMlib

