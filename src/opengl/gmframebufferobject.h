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


#ifndef __gmFRAMEBUFFEROBJECT_H__
#define __gmFRAMEBUFFEROBJECT_H__


#include "gmopengl.h"
#include "gmrenderbufferobject.h"
#include "gmtexture.h"


namespace GMlib {

namespace GL {

  class FramebufferObject {
  public:
    explicit FramebufferObject();
    explicit FramebufferObject( const std::string name );
    FramebufferObject( const FramebufferObject& copy );
    ~FramebufferObject();

    GLuint                  getId() const;
    std::string             getName() const;

    bool                    isValid() const;

    void                    bind() const;
    void                    unbind() const;

    void                    bindRead() const;
    void                    unbindRead() const;

    void                    bindDraw() const;
    void                    unbindDraw() const;

    void                    clear(GLbitfield mask) const;
    void                    clearColorBuffer(const Color& c) const;

    void                    attachRenderbuffer( const RenderbufferObject& rbo,  GLenum attachment );

    void                    attachTexture1D(const Texture& tex, GLenum target, GLenum attachment, GLenum textarget = GL_TEXTURE_1D, GLint level = 0);
    void                    attachTexture2D(const Texture& tex, GLenum target, GLenum attachment, GLenum textarget = GL_TEXTURE_2D, GLint level = 0);
    void                    attachTexture3D(const Texture& tex, GLenum target, GLenum attachment, GLenum textarget = GL_TEXTURE_3D, GLint level = 0, GLint layer = 0 );

    void                    blitTo( GLuint dest_id,
                                    GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1,
                                    GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1,
                                    GLbitfield mask, GLenum filter ) const;

  protected:
    bool                    _valid;

    /* variables "managed" by the backend */
    mutable std::string     _name;
    mutable GLuint          _id;



  private:
    explicit FramebufferObject( GLuint id );
    static GLuintCMap       _ids;

    void                    bind( GLenum target ) const;
    void                    unbind( GLenum target ) const;

    GLint                   safeBind() const;
    void                    safeUnbind(GLint id) const;


  }; // END class FramebufferObject

  inline
  void FramebufferObject::bind( GLenum target ) const {

    GL_CHECK(glBindFramebuffer( target, _id ));
  }

  inline
  void FramebufferObject::unbind( GLenum target ) const {

    GL_CHECK(glBindFramebuffer( target, 0x0 ));
  }

  inline
  void FramebufferObject::bind() const {

    bind( GL_FRAMEBUFFER );
  }

  inline
  void FramebufferObject::unbind() const {

    unbind( GL_FRAMEBUFFER );
  }

  inline
  void FramebufferObject::bindRead() const {

    bind( GL_READ_FRAMEBUFFER );
  }

  inline
  void FramebufferObject::unbindRead() const {

    unbind( GL_READ_FRAMEBUFFER );
  }

  inline
  void FramebufferObject::bindDraw() const {

    bind( GL_DRAW_FRAMEBUFFER );
  }

  inline
  void FramebufferObject::unbindDraw() const {

    unbind( GL_DRAW_FRAMEBUFFER );
  }

  inline
  void FramebufferObject::clear(GLbitfield mask) const {

    GLint id = safeBind();
    GL_CHECK(::glClear( mask ));
    safeUnbind(id);
  }

  inline
  void FramebufferObject::clearColorBuffer(const Color &c ) const {

    static float cc[4];
    GL_CHECK(::glGetFloatv( GL_COLOR_CLEAR_VALUE, cc ));
    GL_CHECK(glClearColor( c ));

    GLint id = safeBind();
    GL_CHECK(::glClear( GL_COLOR_BUFFER_BIT ));
    safeUnbind(id);

    GL_CHECK(::glClearColor( GLclampf(cc[0]), GLclampf(cc[1]), GLclampf(cc[2]), GLclampf(cc[3]) ));
  }


} // END namespace GL

} // END namespace GMlib


#endif // __gmFRAMEBUFFEROBJECT_H__
