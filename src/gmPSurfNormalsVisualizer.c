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



/*! \file gmPSurfNormalsVisualizer.c
 *
 *  Implementation of the PSurfNormalsVisualizer template class.
 *
 *  \date   2010-04-13
 */


namespace GMlib {

  template <typename T>
  PSurfNormalsVisualizer<T>::PSurfNormalsVisualizer() : _display( "color" ) {

    _color = GMcolor::Black;
    _size = 1.0;

    _no_elements = 0;

    glGenBuffers( 1, &_vbo_v );
  }

  template <typename T>
  PSurfNormalsVisualizer<T>::~PSurfNormalsVisualizer() {

    glDeleteBuffers( 1, &_vbo_v );
  }

  template <typename T>
  inline
  void PSurfNormalsVisualizer<T>::display( Camera* cam ) {

    _display.bind();

    _display.setUniform( "u_mvpmat", cam->getProjectionMatrix() * this->_obj->getModelViewMatrix(cam), 1, true );
    _display.setUniform( "u_color", _color );


    GLuint vert_loc = _display.getAttributeLocation( "in_vertex" );

    glBindBuffer( GL_ARRAY_BUFFER, _vbo_v );
    glVertexAttribPointer( vert_loc, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0x0 );
    glEnableVertexAttribArray( vert_loc );

    // Draw
    glDrawArrays( GL_LINES, 0, _no_elements );

    glDisableVertexAttribArray( vert_loc );

    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );

    _display.unbind();
  }

  template <typename T>
  const Color& PSurfNormalsVisualizer<T>::getColor() const {

    return _color;
  }

  template <typename T>
  std::string PSurfNormalsVisualizer<T>::getIdentity() const {

    return "PSurf Normals Visualizer";
  }

  /*! GM_SURF_NORMALSVISUALIZER_MODE PSurfNormalsVisualizer<T>::getMode() const
   *
   *  Returns the displaymode of the visualizer.
   *  All       - Shows all normals.
   *  Boundary  - Shows only the normals on the boundary.
   *  Interior  - Shows only the interior normals.
   *
   *  \return Visualizer normals mode.
   */
  template <typename T>
  GM_SURF_NORMALSVISUALIZER_MODE PSurfNormalsVisualizer<T>::getMode() const {

    return _mode;
  }

  template <typename T>
  double PSurfNormalsVisualizer<T>::getSize() const {

    return _size;
  }

  /*! void PSurfNormalsVisualizer<T>::makePlotAll( DMatrix< DMatrix< Vector<T, 3> > >& p, DMatrix< Vector<T, 3> >& normals )
   *
   *  Generates the plot data for all normals.
   *
   *  \param[in]  p         Evaluated position data.
   *  \param[in]  normals   Evaluated Normal data.
   */
  template <typename T>
  void PSurfNormalsVisualizer<T>::makePlotAll( DMatrix< DMatrix< Vector<T, 3> > >& p, DMatrix< Vector<T, 3> >& normals ) {

    int no_normals = p.getDim1() * p.getDim2();
    _no_elements = no_normals * 2;

    glBindBuffer( GL_ARRAY_BUFFER, _vbo_v);
    glBufferData( GL_ARRAY_BUFFER, no_normals * 2 * 3 * sizeof(float), 0x0, GL_DYNAMIC_DRAW );

    float *ptr = (float*)glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY );
    if( ptr ) {

      for( int i = 0; i < p.getDim1(); i++ )
        for( int j = 0; j < p.getDim2(); j++ ) {

          for( int k = 0; k < 3; k++ )
            *(ptr++) = p[i][j][0][0][k];

          const GMlib::Vector<T,3> N = normals[i][j].getNormalized() * _size;
          for( int k = 0; k < 3; k++ )
            *(ptr++) = p[i][j][0][0][k] + N(k);
        }
    }

    glUnmapBuffer( GL_ARRAY_BUFFER );
    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );
  }

  /*! void PSurfNormalsVisualizer<T>::makePlotInterior( DMatrix< DMatrix< Vector<T, 3> > >& p, DMatrix< Vector<T, 3> >& normals )
   *
   *  Generates the plot data for all interior normals.
   *
   *  \param[in]  p         Evaluated position data.
   *  \param[in]  normals   Evaluated Normal data.
   */
  template <typename T>
  void PSurfNormalsVisualizer<T>::makePlotInterior( DMatrix< DMatrix< Vector<T, 3> > >& p, DMatrix< Vector<T, 3> >& normals ) {

    int no_normals = ( p.getDim1() - 2 ) * ( p.getDim2() - 2 );
    _no_elements = no_normals * 2;

    glBindBuffer( GL_ARRAY_BUFFER, _vbo_v);
    glBufferData( GL_ARRAY_BUFFER, no_normals * 2 * 3 * sizeof(float), 0x0, GL_DYNAMIC_DRAW );

    float *ptr = (float*)glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY );
    if( ptr ) {

      for( int i = 1; i < p.getDim1()-1; i++ )
        for( int j = 1; j < p.getDim2()-1; j++ ) {

          for( int k = 0; k < 3; k++ )
            *(ptr++) = p[i][j][0][0][k];

          const GMlib::Vector<T,3> N = normals[i][j].getNormalized() * _size;
          for( int k = 0; k < 3; k++ )
            *(ptr++) = p[i][j][0][0][k] + N(k);
        }
    }

    glUnmapBuffer( GL_ARRAY_BUFFER );
    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );
  }

  /*! void PSurfNormalsVisualizer<T>::makePlotBoundary( DMatrix< DMatrix< Vector<T, 3> > >& p, DMatrix< Vector<T, 3> >& normals )
   *
   *  Generates the plot data for all boundary normals.
   *
   *  \param[in]  p         Evaluated position data.
   *  \param[in]  normals   Evaluated Normal data.
   */
  template <typename T>
  void PSurfNormalsVisualizer<T>::makePlotBoundary( DMatrix< DMatrix< Vector<T, 3> > >& p, DMatrix< Vector<T, 3> >& normals ) {

    int no_normals = ( p.getDim1() + p.getDim2() ) * 2 - 4;
    _no_elements = no_normals * 2;

    glBindBuffer( GL_ARRAY_BUFFER, _vbo_v);
    glBufferData( GL_ARRAY_BUFFER, no_normals * 2 * 3 * sizeof(float), 0x0, GL_DYNAMIC_DRAW );

    float *ptr = (float*)glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY );
    if( ptr ) {

      for( int i = 0, j; i < p.getDim1(); i++ ) {


        // j = 0
        j = 0;
        for( int k = 0; k < 3; k++ )
          *(ptr++) = p[i][j][0][0][k];

        const GMlib::Vector<T,3> N1 = normals[i][j].getNormalized() * _size;
        for( int k = 0; k < 3; k++ )
          *(ptr++) = p[i][j][0][0][k] + N1(k);

        // j = p.getDim2() -1
        j = p.getDim2() - 1;
        for( int k = 0; k < 3; k++ )
          *(ptr++) = p[i][j][0][0][k];

        const GMlib::Vector<T,3> N2 = normals[i][j].getNormalized() * _size;
        for( int k = 0; k < 3; k++ )
          *(ptr++) = p[i][j][0][0][k] + N2(k);

      }

      for( int i, j = 1; j < p.getDim2()-1; j++ ) {

        // i = 0
        i = 0;
        for( int k = 0; k < 3; k++ )
          *(ptr++) = p[i][j][0][0][k];

        const GMlib::Vector<T,3> N1 = normals[i][j].getNormalized() * _size;
        for( int k = 0; k < 3; k++ )
          *(ptr++) = p[i][j][0][0][k] + N1(k);

        // j = p.getDim1() -1
        i = p.getDim1() - 1;
        for( int k = 0; k < 3; k++ )
          *(ptr++) = p[i][j][0][0][k];

        const GMlib::Vector<T,3> N2 = normals[i][j].getNormalized() * _size;
        for( int k = 0; k < 3; k++ )
          *(ptr++) = p[i][j][0][0][k] + N2(k);
      }
    }

    glUnmapBuffer( GL_ARRAY_BUFFER );
    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );
  }

  template <typename T>
  void PSurfNormalsVisualizer<T>::replot(
    DMatrix< DMatrix< Vector<T, 3> > >& p,
    DMatrix< Vector<T, 3> >& normals,
    int /*m1*/, int /*m2*/, int /*d1*/, int /*d2*/
  ) {

    switch( _mode ) {

    case GM_SURF_NORMALSVISUALIZER_INTERIOR:
      makePlotInterior( p, normals );
      break;

    case GM_SURF_NORMALSVISUALIZER_BOUNDARY:
      makePlotBoundary( p, normals );
      break;

    case GM_SURF_NORMALSVISUALIZER_ALL:
    default:
      makePlotAll( p, normals );
      break;
    }
  }

  template <typename T>
  void PSurfNormalsVisualizer<T>::setColor( const Color& color ) {

    _color = color;
  }

  /*! void PSurfNormalsVisualizer<T>::setMode( GM_SURF_NORMALSVISUALIZER_MODE mode )
   *
   *  Sets the normals mode for the visualizer.
   *
   *  All       - Shows all normals.
   *  Boundary  - Shows only the normals on the boundary.
   *  Interior  - Shows only the interior normals.
   *
   *  \param[in]  mode  The normals mode.
   *
   *  \see PSurfNormalsVisualizer<T>::GM_SURF_NORMALSVISUALIZER_MODE
   */
  template <typename T>
  void PSurfNormalsVisualizer<T>::setMode( GM_SURF_NORMALSVISUALIZER_MODE mode ) {

    _mode = mode;
  }

  template <typename T>
  void PSurfNormalsVisualizer<T>::setSize( double size ) {

    _size = size;
  }



} // END namespace GMlib
