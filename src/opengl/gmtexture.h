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


#include "gmopengl.h"


namespace GMlib {

namespace GL {

  class Texture {
  public:
    explicit Texture();
    explicit Texture( GLenum target );
    explicit Texture( const std::string name );
    explicit Texture( const std::string name, GLenum target );
    Texture( const Texture& copy );
    virtual ~Texture();

    void                    bind() const;
    void                    unbind() const;

    std::string             getName() const;
    GLuint                  getId() const;
    GLenum                  getTarget() const;
    void                    setTarget( GLenum target = GL_TEXTURE_2D ) const;

    bool                    isManaged() const;
    bool                    isValid() const;

    void                    texImage1D( GLint level, GLint internal_format, GLsizei width, GLint border, GLenum format, GLenum type, GLvoid *data );
    void                    texImage2D( GLint level, GLint internal_format, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, GLvoid *data );
    void                    texImage3D( GLint level, GLint internal_format, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, GLvoid *data );

    void                    getTexImage( GLint level, GLenum format, GLenum type, GLvoid* pixels );

    void                    setParameterf(GLenum pname, GLfloat param );
    void                    setParameteri(GLenum pname, GLint param );

    Texture&                operator = ( const Texture& tex );


  protected:
    bool                    _valid;   //! Holds whether the texture is valid
    bool                    _managed; //! Holds whether the texture is managed by the backend or not

    /* variables "managed" by the backend */
    mutable std::string     _name;
    mutable GLuint          _id;
    mutable GLenum          _target;

  private:
    static GLuintCMap       _ids;

    /* safe-bind */
    GLint                   safeBind() const;
    void                    safeUnbind( GLint id ) const;

  }; // END class Texture



  inline
  void Texture::bind() const {

    GL_CHECK(glBindTexture( _target, _id ));
  }

  inline
  void Texture::unbind() const {

    GL_CHECK(glBindTexture( _target, 0x0 ));
  }

  inline
  Texture& Texture::operator = ( const Texture& copy ) {

    _managed  = copy._managed;
    _valid    = copy._valid;

    _name     = copy._name;
    _id       = copy._id;
    _target   = copy._target;

    if( !_managed )
      _ids[_id]++;

    return (*this);
  }


} // END namespace GL

} // END namespace GMlib


#endif // __gm_OPENGL_TEXTURE_H__
