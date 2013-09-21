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


#include "gmobject.h"


namespace GMlib {

namespace GL {

  class BufferObject : public Object {
    GM_GLOBJECT
  public:
    explicit BufferObject( GLenum target = GL_ARRAY_BUFFER, GLenum binding = GL_ARRAY_BUFFER_BINDING );
    explicit BufferObject( const std::string name );
    explicit BufferObject(const std::string name, GLenum target , GLenum binding);
    BufferObject( const BufferObject& copy );
    virtual ~BufferObject();

    GLenum                  getBinding() const;
//    void                    setBinding( GLenum binding = GL_ARRAY_BUFFER_BINDING ) const;

    GLenum                  getTarget() const;
//    void                    setTarget( GLenum target = GL_ARRAY_BUFFER ) const;

    void                    createBufferData( GLsizeiptr size, const GLvoid* data, GLenum usage ) const;
    void                    disableVertexArrayPointer( const GL::AttributeLocation& vert_loc ) const;
    void                    enableVertexArrayPointer( const GL::AttributeLocation& vert_loc, int size, GLenum type, bool normalized, GLsizei stride, const void* offset ) const;

    template <typename T>
    T*                      mapBuffer( GLenum access = GL_WRITE_ONLY ) const;
    void                    unmapBuffer() const;

    BufferObject&           operator = ( const BufferObject& obj );

  private:
    /* variables "managed" by the backend */
    mutable GLenum          _target;
    mutable GLenum          _binding;

    /* pure-virtual functions from Object */
    virtual GLuint          getCurrentBoundId() const;
    virtual void            doBind( GLuint id ) const;

    virtual GLuint          doCreate() const;
    virtual void            doDestroy() const;

    virtual GLuint          doCreateManaged() const;

  }; // END class BufferObject





  template <typename T>
  inline
  T* BufferObject::mapBuffer(GLenum access ) const {

    GLint id = safeBind();
    void *ptr;
    GL_CHECK(ptr = glMapBuffer( _target, access ));
    safeUnbind(id);

    return static_cast<T*>(ptr);
  }

  inline
  BufferObject& BufferObject::operator = ( const BufferObject& copy ) {

    Object::operator = (copy);
    if( isValid() ) {
      _target = copy._target;
      _binding = copy._binding;
    }

    return *this;
  }


} // END namespace GL

} // END namespace GMlib

#endif // __gmBUFFEROBJECT_H__
