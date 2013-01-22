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


  class BufferObject {
  public:
    explicit BufferObject( GLenum type = GL_ARRAY_BUFFER );
    explicit BufferObject( const std::string name );
    explicit BufferObject( const std::string name, GLenum type );
    BufferObject( const BufferObject& copy );
    virtual ~BufferObject();

    void                    bind() const;
    void                    createBufferData( GLsizeiptr size, const GLvoid* data, GLenum usage );
    void                    disableVertexArrayPointer( GLuint vert_loc );
    void                    enableVertexArrayPointer( GLuint vert_loc, int size, GLenum type, bool normalized, GLsizei stride, const void* offset );
    GLuint                  getId() const;
    GLenum                  getTarget() const;
    std::string             getName() const;
    bool                    isValid() const;
    template <typename T>
    T*                      mapBuffer( GLenum access = GL_WRITE_ONLY ) const;
    void                    unbind() const;
    void                    unmapBuffer() const;
    void                    setTarget( GLenum target = GL_ARRAY_BUFFER );

    BufferObject&           operator = ( const BufferObject& obj );

  protected:
    std::string             _name;
    GLuint                  _id;
    GLenum                  _target;
    bool                    _valid;

  private:
    static GLuintCMap       _ids;

  }; // END class BufferObject



  inline
  void BufferObject::bind() const {

    glBindBuffer( _target, _id );
  }

  template <typename T>
  inline
  T* BufferObject::mapBuffer(GLenum access ) const {

    return static_cast<T*>(glMapBuffer( _target, access ));
  }

  inline
  void BufferObject::unbind() const {

    glBindBuffer( _target, 0x0 );
  }

  inline
  BufferObject& BufferObject::operator = ( const BufferObject& obj ) {

    _name = obj._name;
    _id = obj._id;
    _target = obj._target;
    _valid = obj._valid;
    _ids[_id]++;
    return *this;
  }



} // END namespace GMlib

#endif // __gmBUFFEROBJECT_H__
