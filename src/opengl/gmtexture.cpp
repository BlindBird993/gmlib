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

using namespace GMlib::GL;



Texture::Texture() : GLObject<TextureInfo>() {}

Texture::Texture(GLenum target) :  GLObject<TextureInfo>() {

  TextureInfo info;
  info.target = target;
  create(info);
}

Texture::Texture(const std::string name) : GLObject<TextureInfo>(name) {}

Texture::Texture(const std::string name, GLenum target) : GLObject<TextureInfo>() {

  TextureInfo info;
  info.name = name;
  info.target = target;
  create(info);
}

Texture::~Texture() { destroy(); }





GLuint Texture::doGenerate() const {

  GLuint id;
  GL_CHECK(::glGenTextures( 1, &id) );

  std::cout << "  - Generating Texture: " << id << std::endl;
  return id;
}

void Texture::doDelete(GLuint id) const {

  std::cout << "  - Deleting Texture: " << id << std::endl;
//  GL_CHECK(::glDeleteTextures( 1, &id ));
}

GLuint Texture::getCurrentBoundId() const {

  GLint id;
  GL_CHECK(::glGetIntegerv( getTarget(), &id ));
  return id;
}

void Texture::doBind(GLuint id) const {

  GL_CHECK(::glBindTexture( getTarget(), id ));
}

void Texture::texImage1D(GLint level, GLint internal_format, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid *data) {

  GLint id = safeBind();
  GL_CHECK(::glTexImage1D( getTarget(), level, internal_format, width, border, format, type, data ));
  safeUnbind(id);
}

void Texture::texImage2D(GLint level, GLint internal_format, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *data) {

  GLint id = safeBind();
  GL_CHECK(::glTexImage2D( getTarget(), level, internal_format, width, height, border, format, type, data ));
  safeUnbind(id);
}

void Texture::texImage3D(GLint level, GLint internal_format, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *data) {

  GLint id = safeBind();
  GL_CHECK(::glTexImage3D( getTarget(), level, internal_format, width, height, depth, border, format, type, data ));
  safeUnbind(id);
}

void Texture::texSubImage1D(GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid* data) {

  GLint id = safeBind();
  GL_CHECK(::glTexSubImage1D(getTarget(), level, xoffset, width, format, type, data));
  safeUnbind(id);
}

void Texture::texSubImage2D(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* data) {

  GLint id = safeBind();
  GL_CHECK(::glTexSubImage2D(getTarget(), level, xoffset, yoffset, width, height, format, type, data));
  safeUnbind(id);
}

void Texture::texSubImage3D(GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid* data) {

  GLint id = safeBind();
  GL_CHECK(::glTexSubImage3D(getTarget(), level, xoffset, yoffset, zoffset, width, height, depth, format, type, data));
  safeUnbind(id);
}

void Texture::getTexImage(GLint level, GLenum format, GLenum type, GLvoid* pixels) {

  GLint id = safeBind();
  GL_CHECK(::glGetTexImage( getTarget(), level, format, type, pixels ));
  safeUnbind(id);
}

void Texture::setParameterf(GLenum pname, GLfloat param) {

  GLint id = safeBind();
  GL_CHECK(::glTexParameterf( getTarget(), pname, param ));
  safeUnbind(id);
}

void Texture::setParameteri( GLenum pname, GLint param) {

  GLint id = safeBind();
  GL_CHECK(::glTexParameteri( getTarget(), pname, param ));
  safeUnbind(id);
}

