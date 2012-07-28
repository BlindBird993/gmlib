

#include "gmselector.h"

namespace GMlib {


  template <typename T>
  SelectorGridVisualizer<T>::SelectorGridVisualizer() : _prog( "color" ) {

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
    const int no_dp = _c.getDim();
    GLfloat dp[no_dp*3];
    float *dptr = dp;
    for( int i = 0; i < no_dp; i++ ) {

      *dptr++ = (*_c[i])(0);
      *dptr++ = (*_c[i])(1);
      *dptr++ = (*_c[i])(2);
    }

    glBindBuffer( GL_ARRAY_BUFFER, _vbo );
    glBufferData( GL_ARRAY_BUFFER, no_dp * 3 * sizeof(GLfloat), dp, GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );
  }

  template <typename T>
  inline
  void SelectorGridVisualizer<T>::display( Camera* cam ) {

    _prog.bind();

    GMlib::HqMatrix<float,3> mvpmat;
    mvpmat = cam->getProjectionMatrix();
    mvpmat = this->_obj->getModelViewProjectionMatrix(cam);

    _prog.setUniform( "u_mvpmat", mvpmat, 1, true );

    _prog.setUniform( "u_color", GMcolor::LightGreen );
    _prog.setUniform( "u_selected", false );


    GLuint vert_loc = _prog.getAttributeLocation( "in_vertex" );
    glBindBuffer( GL_ARRAY_BUFFER, _vbo );
    glVertexAttribPointer( vert_loc, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0x0 );
    glEnableVertexAttribArray( vert_loc );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _ibo );
    glDrawElements( GL_LINES, _no_indices, GL_UNSIGNED_SHORT, (const GLvoid*)0x0 );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0x0 );

    glDisableVertexAttribArray( vert_loc );
    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );


    _prog.unbind();
  }

  template <typename T>
  void SelectorGridVisualizer<T>::reset() {

    _no_indices = 0x0;
  }

  template <typename T>
  void SelectorGridVisualizer<T>::setSelectors( DVector< Vector<T,3> >& c ) {

    // Order the selectors in the local Dvector structure
    _c.setDim( c.getDim() );
    for( int i = 0; i < c.getDim(); i++ )
      _c[i] = &c[i];

    // Fill VBO
    _fillVBO();

    // Fill IBO
    _no_indices = (c.getDim()-1) * 2;
    GLushort indices[_no_indices];

    // Define grid lines
    GLushort *iptr = indices;
    for( int i = 0; i < c.getDim(); i++ ) {

      *iptr++ = i;
      *iptr++ = i + 1;
    }

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _ibo );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, _no_indices * sizeof(GLushort), indices, GL_STATIC_DRAW );
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

    // Create the indice buffer
    _no_indices = (c.getDim1() * (c.getDim2()-1) + (c.getDim1()-1) * c.getDim2()) * 2;
    GLushort indices[_no_indices];
    GLushort *iptr = indices;

    // "Lines" in i dir
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
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, _no_indices * sizeof(GLushort), indices, GL_STATIC_DRAW );
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
