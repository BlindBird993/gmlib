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



/*! \file gmselectorgrid.c
 *  \brief Pending Description
 *
 *  Detailed File Description
 */



namespace GMlib {




  /*! SelectorGrid::SelectorGrid( Point<T,n>& mp, SceneObject* parent, const Color& c )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  add a new line
   */
  template <typename T, int n>
  SelectorGrid<T,n>::SelectorGrid( APoint<T,n>& mp, SceneObject* parent, const Color& c )
    : Selector<T,n>( mp, -1, parent ),
    _prog( "color" )
  {

    this->_type_id	= GM_SO_TYPE_SELECTOR_GRID;
    this->_default	= c;
    this->_marked	= c.getInverse();
    this->_root		= NULL;
//    this->_scale.reset();
    this->translate( -mp.toFloat());

    Sphere<float,3> ts(Point<float,3>(float(0)),0.866);
    this->setSurroundingSphere(ts);

    glGenBuffers( 1, &_vbo );
    glGenBuffers( 1, &_ibo );
    _selectors = 0x0;
  }

  template <typename T, int n>
  SelectorGrid<T,n>::~SelectorGrid() {

    glDeleteBuffers( 1, &_ibo );
    glDeleteBuffers( 1, &_vbo );
  }

  template <typename T, int n>
  void SelectorGrid<T,n>::_updateIBO() {


    const int m1 = _selectors->getDim1()-1;
    const int m2 = _selectors->getDim2()-1;

    int no_grid_indices = m1*m2*4;
    GLushort grid[no_grid_indices];
    for( int i = 0; i < m1; i++ ) {

      for( int j = 0; j < m2; j++ ) {

        // common idx
        const GLushort c_idx = i * m2 + j;

        // i idx
        const GLushort i_idx = (i+1) * m2 + j;

        // j idx
        const GLushort j_idx = i * m2 + j + 1;

        grid[c_idx]   = c_idx;
        grid[c_idx+1] = i_idx;
        grid[c_idx+2] = c_idx;
        grid[c_idx+3] = j_idx;
      }
    }

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _ibo );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, no_grid_indices * sizeof(GLushort), grid, GL_STATIC_DRAW );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0x0 );
  }

  template <typename T, int n>
  void SelectorGrid<T,n>::_updateVBO() {

    int no_grid_floats = _selectors->getDim1() * _selectors->getDim2() * 3;
    GLfloat grid[4*4*3];//no_grid_floats];
    GLfloat test[10];

    for( int i = 0; i < _selectors->getDim1(); i++ ) {
      for( int j = 0; j < _selectors->getDim2(); j++ ) {

        const int idx = (i * _selectors->getDim1() + j) * 3;
        grid[idx]   = (*_selectors)[i][j][0];
        grid[idx+1] = (*_selectors)[i][j][1];
        grid[idx+2] = (*_selectors)[i][j][2];
      }
    }

    glBindBuffer( GL_ARRAY_BUFFER, _vbo );
    glBufferData( GL_ARRAY_BUFFER, no_grid_floats * sizeof(GLfloat), grid, GL_DYNAMIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );
  }

  /*! void SelectorGrid::add(APoint<T,n>& p1, APoint<T,n>& p2)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  add a new line
   */
  template <typename T, int n>
  inline
  void SelectorGrid<T,n>::add(APoint<T,n>& p1, APoint<T,n>& p2) {

    _c += &p1;
    _c += &p2;
  }

  /*! void SelectorGrid::localDisplay()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  add a new line
   */
  template <typename T, int n>
  void SelectorGrid<T,n>::localDisplay() {

    if( !_selectors )
      return;

    _prog.bind();

    _prog.setUniform( "u_color", GMcolor::Green );
    _prog.setUniform( "u_selected", false );

    GLuint vert_loc = _prog.getAttributeLocation( "in_vertex" );

    glBindBuffer( GL_ARRAY_BUFFER, _vbo );
    glVertexAttribPointer( vert_loc, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0x0 );
    glEnableVertexAttribArray( vert_loc );

    glPointSize( 10.0f );
    glDrawArrays( GL_POINTS, 0, _selectors->getDim1() * _selectors->getDim2() );

//    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _ibo );
//    glDrawElements( GL_LINES, (_selectors->getDim1()-1)*(_selectors->getDim2()-1)*4, GL_UNSIGNED_SHORT, 0x0 );
//    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0x0 );


    glDisableVertexAttribArray( vert_loc );

    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );

    _prog.unbind();
  }


  /*! void SelectorGrid::localSelect()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void SelectorGrid<T,n>::localSelect() {}

  template <typename T, int n>
  void SelectorGrid<T,n>::setSelectors( DMatrix< Vector<T,n> >& selectors ) {

    int dim1, dim2;

    if( _selectors ) {
      dim1 = _selectors->getDim1();
      dim2 = _selectors->getDim2();
    }
    else {

      dim1 = dim2 = 0;
    }

    _selectors = &selectors;
    if( dim1 != _selectors->getDim1() || dim2 != _selectors->getDim2() ) {
//      _allocateBOs();
      _updateVBO();
      _updateIBO();
    }
  }
}
