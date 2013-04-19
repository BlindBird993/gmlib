/*****************************************************************************
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
*****************************************************************************/



/*! \file gmselectorgridvisualizer.c
 */

#include "../selector/gmselector.h"

namespace GMlib {


  template <typename T>
  SelectorGridVisualizer<T>::SelectorGridVisualizer() {

    setRenderProgram( GL::GLProgram("color") );

    _no_indices = 0;

    glGenBuffers( 1, &_ibo );
    glGenBuffers( 1, &_vbo );
  }

  template <typename T>
  SelectorGridVisualizer<T>::~SelectorGridVisualizer() {

    glDeleteBuffers( 1, &_ibo );
    glDeleteBuffers( 1, &_vbo );
  }

  template <typename T>
  void SelectorGridVisualizer<T>::_fillVBO() {

    // Fill the vertice buffer
    const int no = _c.getDim();
    DVector<Vector<GLfloat,3> > dp(no);
    for( int i = 0; i < no; i++ )
      dp[i] = (*_c[i]).template toType<GLfloat>();

    glBindBuffer( GL_ARRAY_BUFFER, _vbo );
    glBufferData( GL_ARRAY_BUFFER, no * 3 * sizeof(GLfloat), dp[0].getPtr(), GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );
  }

  template <typename T>
  inline
  void SelectorGridVisualizer<T>::display() {

    const GL::GLProgram &prog = this->getRenderProgram();
    prog.setUniform( "u_color", GMcolor::LightGreen );
    prog.setUniform( "u_selected", false );

    GLuint vert_loc = prog.getAttributeLocation( "in_vertex" );
    glBindBuffer( GL_ARRAY_BUFFER, _vbo );
    glVertexAttribPointer( vert_loc, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0x0 );
    glEnableVertexAttribArray( vert_loc );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _ibo );
    glDrawElements( GL_LINES, _no_indices, GL_UNSIGNED_SHORT, (const GLvoid*)0x0 );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0x0 );

    glDisableVertexAttribArray( vert_loc );
    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );
  }

  template <typename T>
  void SelectorGridVisualizer<T>::reset() {

    _no_indices = 0;
  }

  template <typename T>
  void SelectorGridVisualizer<T>::setSelectors( DVector< Vector<T,3> >& c, int tp) {

    // Order the selectors in the local Dvector structure
    _c.setDim( c.getDim() );
    for( int i = 0; i < c.getDim(); i++ )
      _c[i] = &c[i];

    // Fill VBO
    _fillVBO();

    // Define grid lines
    switch(tp){
      case 0: _makeLines();
              break;
      case 1: _makeTriangs();
              break;
      default: ;
    }
  }


  template <typename T>
  inline
  void SelectorGridVisualizer<T>::_makeLines()     // Fill IBO
  {
    // Create the indice buffer
    DVector<GLushort> indices(_no_indices = 2*(_c.getDim()-1));
    for(int i=0, j=0; i < _no_indices; i+=2, j++) {
      indices[i]   = j;
      indices[i+1] = j + 1;
    }

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _ibo );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, _no_indices * sizeof(GLushort), indices.getPtr(), GL_STATIC_DRAW );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0x0 );
  }


  template <typename T>
  inline
  void SelectorGridVisualizer<T>::_makeTriangs()     // Fill IBO
  {
    // Create the indice buffer
    int m = (sqrt(8*_c.getDim()+1)-1)/2;
    DVector<GLushort> indices(_no_indices = 3*(m*(m-1)));
    for( int k=0, i=0; i < m-1; i++) {
      int o1 = (i*(i+1))/2;
      int o2 = ((i+1)*(i+2))/2;
      for( int j = 0, l = o2-o1; j < l; j++ ) {
        indices[k++] = o1+j; indices[k++] = o2+j;
        indices[k++] = o1+j; indices[k++] = o2+j+1;
        indices[k++] = o2+j; indices[k++] = o2+j+1;
      }
    }

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _ibo );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, _no_indices * sizeof(GLushort), indices.getPtr(), GL_STATIC_DRAW );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0x0 );
  }


  template <typename T>
  void SelectorGridVisualizer<T>::setSelectors( DMatrix< Vector<T,3> >& c ) {

    // Order the selectors in a DVector structure
    _c.setDim( c.getDim1() * c.getDim2() );
    for( int i = 0; i < c.getDim1(); i++ )
      for( int j = 0; j < c.getDim2(); j++ )
        _c[i*c.getDim1()+j] = &c[i][j];

    // Fill VBO
    _fillVBO();


    // Fill IBO
    _no_indices = (c.getDim1() * (c.getDim2()-1) + (c.getDim1()-1) * c.getDim2()) * 2;
    DVector<GLushort> indices(_no_indices);     // Create the indice buffer


    // "Lines" in i dir
    GLushort *iptr = indices.getPtr();
    for( int i = 0; i < c.getDim1(); i++ ) {
      for( int j = 0; j < c.getDim2()-1; j++ ) {

        *iptr++ = i * c.getDim2() + j;
        *iptr++ = i * c.getDim2() + j + 1;
      }
    }

    // "Lines" in j dir
    for( int i = 0; i < c.getDim1()-1; i++ ) {
      for( int j = 0; j < c.getDim2(); j++ ) {

        *iptr++ = i * c.getDim2() + j;
        *iptr++ = (i+1) * c.getDim2() + j;
      }
    }

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _ibo );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, _no_indices * sizeof(GLushort), indices.getPtr(), GL_STATIC_DRAW );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0x0 );
  }

  template <typename T>
  inline
  void SelectorGridVisualizer<T>::update() {

    glBindBuffer( GL_ARRAY_BUFFER, _vbo );
    GLfloat* ptr = (GLfloat*)glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY );

    for( int i = 0; i < _c.getDim(); i++ ) {
      for( int k = 0; k < 3; k++ ) {

        const int idx = i * 3 + k;
        if( ptr[idx] != (*_c[i])(k) )
          ptr[idx] = (*_c[i])(k);
      }
    }

    glUnmapBuffer( GL_ARRAY_BUFFER );
    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );
  }

} // END namespace GMlib
