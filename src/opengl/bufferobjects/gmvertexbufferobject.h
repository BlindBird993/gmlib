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


#ifndef __gmVERTEXBUFFEROBJECT_H__
#define __gmVERTEXBUFFEROBJECT_H__


#include "../gmbufferobject.h"


namespace GMlib {

namespace GL {

  class VertexBufferObject : public BufferObject {
  public:
    explicit VertexBufferObject();
    explicit VertexBufferObject( const std::string& name );

    void    enable(GLuint index, GLint size, GLenum type, bool normalize, GLsizei stride, const GLvoid* offset );
    void    disable( GLuint index );

  }; // END class VertexBufferObject


  inline
  void VertexBufferObject::enable(GLuint index, GLint size, GLenum type,
                                  bool normalize, GLsizei stride, const GLvoid *offset) {

    this->enableVertexArrayPointer( index, size, type, normalize, stride, offset );
  }

  inline
  void VertexBufferObject::disable(GLuint index) {

    this->disableVertexArrayPointer( index );
  }

} // END namespace GL

} // END namespace GMlib


#endif // __gmVERTEXBUFFEROBJECT_H__
