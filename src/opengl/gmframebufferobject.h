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

    void                    attachTexture1D(const Texture& tex, GLenum target, GLenum attachment, GLenum textarget = GL_TEXTURE_1D, GLint level = 0);
    void                    attachTexture2D(const Texture& tex, GLenum target, GLenum attachment, GLenum textarget = GL_TEXTURE_2D, GLint level = 0);
    void                    attachTexture3D(const Texture& tex, GLenum target, GLenum attachment, GLenum textarget = GL_TEXTURE_3D, GLint level = 0, GLint layer = 0 );

  protected:
    bool                    _valid;

    /* variables "managed" by the backend */
    mutable std::string     _name;
    mutable GLuint          _id;



  private:
    static GLuintCMap       _ids;

    /* safe-bind */
    mutable GLint           _safe_id;

    void                    safeBind() const;
    void                    safeUnbind() const;


  }; // END class FramebufferObject


  inline
  void FramebufferObject::bind() const {

    glBindFramebuffer( GL_FRAMEBUFFER, _id );
  }

  inline
  void FramebufferObject::unbind() const {

    glBindFramebuffer( GL_FRAMEBUFFER, 0x0 );
  }


} // END namespace GL

} // END namespace GMlib


#endif // __gmFRAMEBUFFEROBJECT_H__
