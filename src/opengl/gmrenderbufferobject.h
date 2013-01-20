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


#ifndef __gmRENDERBUFFEROBJECT_H__
#define __gmRENDERBUFFEROBJECT_H__


#include "gmopengl.h"
#include "gmtexture.h"


namespace GMlib {

namespace GL {

  class RenderbufferObject {
  public:
    explicit RenderbufferObject();
    explicit RenderbufferObject( const std::string name );
    RenderbufferObject( const RenderbufferObject& copy );
    ~RenderbufferObject();

    GLuint                  getId() const;
    std::string             getName() const;

    bool                    isValid() const;

    void                    bind() const;
    void                    unbind() const;

    void                    createStorage( GLenum internal_format, GLsizei width, GLsizei height ) const;

  protected:
    bool                    _valid;

    /* variables "managed" by the backend */
    mutable std::string     _name;
    mutable GLuint          _id;



  private:
    static GLuintCMap       _ids;

    /* safe-bind */
    GLint                   safeBind() const;
    void                    safeUnbind(GLint id) const;


  }; // END class RenderbufferObject


  inline
  void RenderbufferObject::bind() const {

    glBindRenderbuffer( GL_RENDERBUFFER, _id );
  }

  inline
  void RenderbufferObject::unbind() const {

    glBindFramebuffer( GL_RENDERBUFFER, 0x0 );
  }


} // END namespace GL

} // END namespace GMlib


#endif // __gmRENDERBUFFEROBJECT_H__
