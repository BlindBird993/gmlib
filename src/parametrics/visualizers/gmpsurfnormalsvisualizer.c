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



/*! \file gmpsurfnormalsvisualizer.c
 *
 *  Implementation of the PSurfNormalsVisualizer template class.
 */


#include <opengl/gmopengl.h>
#include <opengl/glsl/gmglprogram.h>
#include <opengl/glsl/gmglshadermanager.h>


namespace GMlib {

  template <typename T, int n>
  PSurfNormalsVisualizer<T,n>::PSurfNormalsVisualizer() {

    this->setRenderProgram( GL::GLProgram("color") );

    _color = GMcolor::Black;
    _size = 1.0;

    _no_elements = 0;
  }

  template <typename T, int n>
  PSurfNormalsVisualizer<T,n>::~PSurfNormalsVisualizer() {}

  template <typename T, int n>
  inline
  void PSurfNormalsVisualizer<T,n>::display() {

    const GL::GLProgram &prog = this->getRenderProgram();
    prog.setUniform( "u_color", _color );


    GLuint vert_loc = prog.getAttributeLocation( "in_vertex" );

    _vbo.bind();
    _vbo.enable( vert_loc, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0x0 );

    // Draw
    glDrawArrays( GL_LINES, 0, _no_elements );

    _vbo.disable( vert_loc );
    _vbo.unbind();
  }

  template <typename T, int n>
  const Color& PSurfNormalsVisualizer<T,n>::getColor() const {

    return _color;
  }

  /*! GM_SURF_NORMALSVISUALIZER_MODE PSurfNormalsVisualizer<T,n>::getMode() const
   *
   *  Returns the displaymode of the visualizer.
   *  All       - Shows all normals.
   *  Boundary  - Shows only the normals on the boundary.
   *  Interior  - Shows only the interior normals.
   *
   *  \return Visualizer normals mode.
   */
  template <typename T, int n>
  GM_SURF_NORMALSVISUALIZER_MODE PSurfNormalsVisualizer<T,n>::getMode() const {

    return _mode;
  }

  template <typename T, int n>
  double PSurfNormalsVisualizer<T,n>::getSize() const {

    return _size;
  }

  /*! void PSurfNormalsVisualizer<T,n>::makePlotAll( DMatrix< DMatrix< Vector<T, 3> > >& p, DMatrix< Vector<T, 3> >& normals )
   *
   *  Generates the plot data for all normals.
   *
   *  \param[in]  p         Evaluated position data.
   *  \param[in]  normals   Evaluated Normal data.
   */
  template <typename T, int n>
  void PSurfNormalsVisualizer<T,n>::makePlotAll( DMatrix< DMatrix< Vector<T, 3> > >& p, DMatrix< Vector<T, 3> >& normals ) {

    int no_normals = p.getDim1() * p.getDim2();
    _no_elements = no_normals * 2;

    _vbo.bind();
    _vbo.createBufferData( no_normals * 2 * sizeof(GL::GLVertex), 0x0, GL_STATIC_DRAW );

    GL::GLVertex *ptr = _vbo.mapBuffer<GL::GLVertex>();
    if( ptr ) {

      for( int i = 0; i < p.getDim1(); i++ ) {
        for( int j = 0; j < p.getDim2(); j++ ) {

          (*ptr).x = p[i][j][0][0][0];
          (*ptr).y = p[i][j][0][0][1];
          (*ptr).z = p[i][j][0][0][2];
          ptr++;

          const Vector<T,3> N = normals[i][j].getNormalized() * _size;
          (*ptr).x = p[i][j][0][0][0] + N(0);
          (*ptr).y = p[i][j][0][0][1] + N(1);
          (*ptr).z = p[i][j][0][0][2] + N(2);
          ptr++;
        }
      }
    }

    _vbo.unmapBuffer();
    _vbo.unbind();
  }

  /*! void PSurfNormalsVisualizer<T,n>::makePlotInterior( DMatrix< DMatrix< Vector<T, 3> > >& p, DMatrix< Vector<T, 3> >& normals )
   *
   *  Generates the plot data for all interior normals.
   *
   *  \param[in]  p         Evaluated position data.
   *  \param[in]  normals   Evaluated Normal data.
   */
  template <typename T, int n>
  void PSurfNormalsVisualizer<T,n>::makePlotInterior( DMatrix< DMatrix< Vector<T, 3> > >& p, DMatrix< Vector<T, 3> >& normals ) {

    int no_normals = ( p.getDim1() - 2 ) * ( p.getDim2() - 2 );
    _no_elements = no_normals * 2;

    _vbo.bind();
    _vbo.createBufferData( no_normals * 2 * sizeof(GL::GLVertex), 0x0, GL_STATIC_DRAW );

    GL::GLVertex *ptr = _vbo.mapBuffer<GL::GLVertex>();
    if( ptr ) {

      for( int i = 1; i < p.getDim1()-1; i++ ) {
        for( int j = 1; j < p.getDim2()-1; j++ ) {

          (*ptr).x = p[i][j][0][0][0];
          (*ptr).y = p[i][j][0][0][1];
          (*ptr).z = p[i][j][0][0][2];
          ptr++;

          const Vector<T,3> N = normals[i][j].getNormalized() * _size;
          (*ptr).x = p[i][j][0][0][0] + N(0);
          (*ptr).y = p[i][j][0][0][1] + N(1);
          (*ptr).z = p[i][j][0][0][2] + N(2);
          ptr++;
        }
      }
    }

    _vbo.unmapBuffer();
    _vbo.unbind();
  }

  /*! void PSurfNormalsVisualizer<T,n>::makePlotBoundary( DMatrix< DMatrix< Vector<T, 3> > >& p, DMatrix< Vector<T, 3> >& normals )
   *
   *  Generates the plot data for all boundary normals.
   *
   *  \param[in]  p         Evaluated position data.
   *  \param[in]  normals   Evaluated Normal data.
   */
  template <typename T, int n>
  void PSurfNormalsVisualizer<T,n>::makePlotBoundary( DMatrix< DMatrix< Vector<T, 3> > >& p, DMatrix< Vector<T, 3> >& normals ) {

    int no_normals = ( p.getDim1() + p.getDim2() ) * 2 - 4;
    _no_elements = no_normals * 2;

    _vbo.bind();
    _vbo.createBufferData( no_normals * 2 * sizeof(GL::GLVertex), 0x0, GL_STATIC_DRAW );

    GL::GLVertex *ptr = _vbo.mapBuffer<GL::GLVertex>();
    if( ptr ) {

      for( int i = 0, j; i < p.getDim1(); i++ ) {

        // j = 0
        j = 0;

        (*ptr).x = p[i][j][0][0][0];
        (*ptr).y = p[i][j][0][0][1];
        (*ptr).z = p[i][j][0][0][2];
        ptr++;

        const Vector<T,3> N1 = normals[i][j].getNormalized() * _size;
        (*ptr).x = p[i][j][0][0][0] + N1(0);
        (*ptr).y = p[i][j][0][0][1] + N1(1);
        (*ptr).z = p[i][j][0][0][2] + N1(2);
        ptr++;

        // j = p.getDim2() -1
        j = p.getDim2() - 1;

        (*ptr).x = p[i][j][0][0][0];
        (*ptr).y = p[i][j][0][0][1];
        (*ptr).z = p[i][j][0][0][2];
        ptr++;

        const Vector<T,3> N2 = normals[i][j].getNormalized() * _size;
        (*ptr).x = p[i][j][0][0][0] + N2(0);
        (*ptr).y = p[i][j][0][0][1] + N2(1);
        (*ptr).z = p[i][j][0][0][2] + N2(2);
        ptr++;
      }

      for( int i, j = 1; j < p.getDim2()-1; j++ ) {

        // i = 0
        i = 0;

        (*ptr).x = p[i][j][0][0][0];
        (*ptr).y = p[i][j][0][0][1];
        (*ptr).z = p[i][j][0][0][2];
        ptr++;

        const Vector<T,3> N1 = normals[i][j].getNormalized() * _size;
        (*ptr).x = p[i][j][0][0][0] + N1(0);
        (*ptr).y = p[i][j][0][0][1] + N1(1);
        (*ptr).z = p[i][j][0][0][2] + N1(2);
        ptr++;

        // j = p.getDim1() -1
        i = p.getDim1() - 1;
        (*ptr).x = p[i][j][0][0][0];
        (*ptr).y = p[i][j][0][0][1];
        (*ptr).z = p[i][j][0][0][2];
        ptr++;

        const Vector<T,3> N2 = normals[i][j].getNormalized() * _size;
        (*ptr).x = p[i][j][0][0][0] + N2(0);
        (*ptr).y = p[i][j][0][0][1] + N2(1);
        (*ptr).z = p[i][j][0][0][2] + N2(2);
        ptr++;
      }
    }

    glUnmapBuffer( GL_ARRAY_BUFFER );
    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );
  }

  template <typename T, int n>
  void PSurfNormalsVisualizer<T,n>::replot(
    DMatrix< DMatrix< Vector<T, n> > >& p,
    DMatrix< Vector<T, n> >& normals,
    int /*m1*/, int /*m2*/, int /*d1*/, int /*d2*/,
    bool /*closed_u*/, bool /*closed_v*/
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

  template <typename T, int n>
  void PSurfNormalsVisualizer<T,n>::setColor( const Color& color ) {

    _color = color;
  }

  /*! void PSurfNormalsVisualizer<T,n>::setMode( GM_SURF_NORMALSVISUALIZER_MODE mode )
   *
   *  Sets the normals mode for the visualizer.
   *
   *  All       - Shows all normals.
   *  Boundary  - Shows only the normals on the boundary.
   *  Interior  - Shows only the interior normals.
   *
   *  \param[in]  mode  The normals mode.
   *
   *  \see PSurfNormalsVisualizer<T,n>::GM_SURF_NORMALSVISUALIZER_MODE
   */
  template <typename T, int n>
  void PSurfNormalsVisualizer<T,n>::setMode( GM_SURF_NORMALSVISUALIZER_MODE mode ) {

    _mode = mode;
  }

  template <typename T, int n>
  void PSurfNormalsVisualizer<T,n>::setSize( double size ) {

    _size = size;
  }



} // END namespace GMlib
