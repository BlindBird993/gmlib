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


#ifndef __gm_OPENGL_TEXTURE_H__
#define __gm_OPENGL_TEXTURE_H__


#include "gmobject.h"


namespace GMlib {

namespace GL {

  class Texture : public Object {
    GM_GLOBJECT
  public:
    explicit Texture();
    explicit Texture( GLenum target, bool generate = true );
    explicit Texture( const std::string name );
    explicit Texture( const std::string name, GLenum target );
    Texture( const Texture& copy );
    ~Texture();

    GLenum                  getTarget() const;

    void                    texImage1D( GLint level, GLint internal_format, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid *data );
    void                    texImage2D( GLint level, GLint internal_format, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *data );
    void                    texImage3D( GLint level, GLint internal_format, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *data );

    void                    texSubImage1D( GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid* data );
    void                    texSubImage2D( GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* data );
    void                    texSubImage3D( GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid* data );

    void                    getTexImage( GLint level, GLenum format, GLenum type, GLvoid* pixels );

    void                    setParameterf(GLenum pname, GLfloat param );
    void                    setParameteri(GLenum pname, GLint param );

    Texture&                operator = ( const Texture& tex );


  private:
    /* variables "managed" by the backend */
    mutable GLenum          _target;

    /* pure-virtual functions from Object */
    virtual GLuint          getCurrentBoundId() const;
    virtual void            doBind( GLuint id ) const;

    virtual GLuint          doCreate() const;
    virtual void            doDestroy() const;

    virtual GLuint          doCreateManaged() const;


  }; // END class Texture

  inline
  GLenum Texture::getTarget() const { return _target; }

  inline
  Texture& Texture::operator = ( const Texture& copy ) {

    Object::operator = ( copy );
    if( isValid() ) _target = copy._target;

    return *this;
  }


} // END namespace GL

} // END namespace GMlib


#endif // __gm_OPENGL_TEXTURE_H__
