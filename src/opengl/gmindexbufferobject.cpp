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



#include "gmindexbufferobject.h"


namespace GMlib {



  IndexBufferObject::IndexBufferObject() : BufferObject( GL_ELEMENT_ARRAY_BUFFER ) {

    _type = GL_UNSIGNED_INT;
    _type_size = sizeof(GLuint);
  }

  IndexBufferObject::IndexBufferObject(const std::string &name) :
    BufferObject( name, GL_ELEMENT_ARRAY_BUFFER ) {
  }

  void IndexBufferObject::createBufferData(unsigned int no_indices, const GLvoid *data, GLenum usage) {

    BufferObject::createBufferData( no_indices * _type_size, data, usage );
  }

  void IndexBufferObject::draw() {}

  const GLenum &IndexBufferObject::getMode() const {

    return _mode;
  }

  const GLenum &IndexBufferObject::getType() const {

    return _type;
  }

  const GLsizei &IndexBufferObject::getTypeSize() const {

    return _type_size;
  }












  TrianglesIBO::TrianglesIBO() : IndexBufferObject() {

    init();
  }

  TrianglesIBO::TrianglesIBO(const std::string &name) :
    IndexBufferObject( name ) {

    init();
  }

  void TrianglesIBO::draw() {

    bind();
    glDrawElements( GL_TRIANGLES, _no_indices, getType(), (const GLvoid*)0x0 );
    unbind();
  }

  void TrianglesIBO::init() {

    _no_indices = 0;
  }
















  TriangleStripIBO::TriangleStripIBO() : IndexBufferObject() {

    init();
  }

  TriangleStripIBO::TriangleStripIBO(const std::string &name) :
    IndexBufferObject(name) {

    init();
  }

  void TriangleStripIBO::draw() {

    bind();
    for( int i = 0; i < _no_strips; ++i )
      glDrawElements( GL_TRIANGLE_STRIP, _no_indices_per_strip, getType(), (const GLvoid*)(i * _strip_size) );
    unbind();
  }

  void TriangleStripIBO::fill( int m1, int m2 ) {

    _no_strips = m1 - 1;
    _no_indices_per_strip = m2 * 2;

    int no_indices = _no_strips * _no_indices_per_strip;

    GLuint indices[no_indices];
    for( int i = 0; i < m1-1; i++ ) {

      const int idx_i = i * m2 * 2;
      for( int j = 0; j < m2; j++ ) {

        const int idx_j = idx_i + (j*2);
        indices[idx_j]   = i*m2 + j;
        indices[idx_j+1] = (i+1)*m2 + j;
      }
    }

    bind();
    createBufferData( no_indices, indices, GL_STATIC_DRAW );
    unbind();

    // Strip size must be set after createBufferData( ... ) is called
    // as the type size is defined by the createBufferData function
    _strip_size = getTypeSize() * _no_indices_per_strip;
  }

  void TriangleStripIBO::init() {

    _no_strips = 0;
    _no_indices_per_strip = 0;
    _strip_size = 0;
  }


} // END namespace GMlib
