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

    void    enable(const GL::AttributeLocation& location, GLint size, GLenum type, bool normalize, GLsizei stride, const GLvoid* offset ) const;
    void    disable(const GL::AttributeLocation& location) const;

  }; // END class VertexBufferObject


  inline
  void VertexBufferObject::enable(const GL::AttributeLocation& location, GLint size, GLenum type,
                                  bool normalize, GLsizei stride, const GLvoid *offset) const {

    this->enableVertexArrayPointer( location, size, type, normalize, stride, offset );
  }

  inline
  void VertexBufferObject::disable(const GL::AttributeLocation& location) const {

    this->disableVertexArrayPointer( location );
  }

} // END namespace GL

} // END namespace GMlib


#endif // __gmVERTEXBUFFEROBJECT_H__
