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



#include "gmframebufferobject.h"


namespace GMlib {

namespace GL {

  GLuintCMap FramebufferObject::_ids;

  FramebufferObject::FramebufferObject() {

    _name = "";

    _id = OGL::createFbo();
    _valid = true;

    _ids[_id] = 1;
  }

  FramebufferObject::FramebufferObject(const std::string name) {

    _name = name;

    _valid = OGL::createFbo( name );
    _id = OGL::getFboId( name );

    _ids[_id] = 1;
  }

  FramebufferObject::FramebufferObject(const FramebufferObject &copy) {

    _name = copy._name;
    _id = copy._id;

    _ids[_id]++;
  }

  FramebufferObject::~FramebufferObject() {

    _ids[_id]--;
    if( _ids.count(_id) <= 0 )
      OGL::deleteFbo( _id );
  }

  FramebufferObject::FramebufferObject(GLuint id) {

    _name = "";

    _id = id;
    _valid = true;

    _ids[_id] = 1;

  }

  void FramebufferObject::attachRenderbuffer(const RenderbufferObject &rbo, GLenum attachment) {

    GLint id = safeBind();
    rbo.bind();
    GL_CHECK(glFramebufferRenderbuffer( GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, rbo.getId() ));
    rbo.unbind();
    safeUnbind(id);
  }

  void FramebufferObject::attachTexture1D(const Texture &tex, GLenum target, GLenum attachment, GLenum textarget, GLint level ) {

    GLint id = safeBind();
    GL_CHECK(glFramebufferTexture1D( target, attachment, textarget, tex.getId(), level ));
    safeUnbind(id);
  }

  void FramebufferObject::attachTexture2D(const Texture &tex, GLenum target, GLenum attachment, GLenum textarget, GLint level ) {

    GLint id = safeBind();
    GL_CHECK(glFramebufferTexture2D( target, attachment, textarget, tex.getId(), level ));
    safeUnbind(id);
  }

  void FramebufferObject::attachTexture3D(const Texture &tex, GLenum target, GLenum attachment, GLenum textarget, GLint level, GLint layer ) {

    GLint id = safeBind();
    GL_CHECK(glFramebufferTexture3D( target, attachment, textarget, tex.getId(), level, layer ));
    safeUnbind(id);
  }

  void FramebufferObject::blitTo(GLuint dest_id, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) const {

    FramebufferObject dest_fbo(dest_id);

    bindRead();
    dest_fbo.bindDraw();

    GL_CHECK(::glBlitFramebuffer( srcX0,srcY0,srcX1,srcY1,dstX0,dstY0,dstX1,dstY1,mask,filter ));

    unbindRead();
    dest_fbo.unbindDraw();
  }

  GLuint FramebufferObject::getId() const {

    return _id;
  }

  std::string FramebufferObject::getName() const {

    return _name;
  }

  bool FramebufferObject::isValid() const {

    return _valid;
  }

  GLint FramebufferObject::safeBind() const {

    GLint id;
    GL_CHECK(glGetIntegerv( GL_FRAMEBUFFER_BINDING, &id ));
    bind();

    return id;
  }

  void FramebufferObject::safeUnbind( GLint id ) const {

    GL_CHECK(glBindFramebuffer( GL_FRAMEBUFFER, id ));
  }


} // END namespace GL

} // END namespace GMlib
