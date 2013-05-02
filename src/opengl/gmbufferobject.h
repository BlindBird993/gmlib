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


#ifndef __gmBUFFEROBJECT_H__
#define __gmBUFFEROBJECT_H__


#include "gmopengl.h"


namespace GMlib {

namespace GL {

  class BufferObject {
  public:
    explicit BufferObject( GLenum target = GL_ARRAY_BUFFER, GLenum binding = GL_ARRAY_BUFFER_BINDING );
    explicit BufferObject( const std::string name );
    explicit BufferObject(const std::string name, GLenum target , GLenum binding);
    BufferObject( const BufferObject& copy );
    virtual ~BufferObject();

    void                    bind() const;
    void                    unbind() const;

    std::string             getName() const;
    GLuint                  getId() const;

    GLenum                  getBinding() const;
    void                    setBinding( GLenum binding = GL_ARRAY_BUFFER_BINDING ) const;

    GLenum                  getTarget() const;
    void                    setTarget( GLenum target = GL_ARRAY_BUFFER ) const;

    bool                    isValid() const;

    void                    createBufferData( GLsizeiptr size, const GLvoid* data, GLenum usage ) const;
    void                    disableVertexArrayPointer( GLuint vert_loc ) const;
    void                    enableVertexArrayPointer( GLuint vert_loc, int size, GLenum type, bool normalized, GLsizei stride, const void* offset ) const;

    template <typename T>
    T*                      mapBuffer( GLenum access = GL_WRITE_ONLY ) const;
    void                    unmapBuffer() const;

    BufferObject&           operator = ( const BufferObject& obj );

  protected:
    bool                    _valid;

    /* variables "managed" by the backend */
    mutable std::string     _name;
    mutable GLuint          _id;
    mutable GLenum          _target;
    mutable GLenum          _binding;

  private:
    static GLuintCMap       _ids;

    /* safe-bind */
    virtual GLint           safeBind() const;
    void                    safeUnbind( GLint id ) const;

  }; // END class BufferObject



  inline
  void BufferObject::bind() const {

    GL_CHECK(glBindBuffer( _target, _id ));
  }

  template <typename T>
  inline
  T* BufferObject::mapBuffer(GLenum access ) const {

    GLint id = safeBind();
    void *ptr;
    GL_CHECK(ptr = glMapBuffer( _target, access ));
    return static_cast<T*>(ptr);
    safeUnbind(id);
  }

  inline
  void BufferObject::unbind() const {

    GL_CHECK(glBindBuffer( _target, 0x0 ));
  }

  inline
  BufferObject& BufferObject::operator = ( const BufferObject& copy ) {

    _name     = copy._name;
    _id       = copy._id;
    _target   = copy._target;

    _valid    = copy._valid;

    _ids[_id]++;

    return *this;
  }


} // END namespace GL

} // END namespace GMlib

#endif // __gmBUFFEROBJECT_H__
