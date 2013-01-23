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



/*! \file gmptrianglevisualizer.c
 *
 *  Implementation of the PTriangleVisualizer template class.
 */

// gmlib
#include "../gmptriangle.h"

namespace GMlib {


  template <typename T>
  PTriangleVisualizer<T>::PTriangleVisualizer() {

    _triangle = 0x0;
  }

  template <typename T>
  PTriangleVisualizer<T>::~PTriangleVisualizer() {}

  template <typename T>
  void  PTriangleVisualizer<T>::fillStandardVBO(GL::VertexBufferObject vbo, const DVector<DVector<Vector<T,3> > > &p) {

    int no_dp = p.getDim();


    Vector<T,3> a, b;
    UnitVector<T,3> n;

    DVector<GL::GLVertexNormal> dp(no_dp);
    for( int i = 0; i < p.getDim(); i++ ) {

//      const UnitVector<float,3> n = Vector3D<float>( p(i)(0)(1) ) ^ p(i)(1)(0);

      a = p(i)(3)-p(i)(1);
      b = p(i)(2)-p(i)(1);
      n = a^b;

      dp[i].x   = p(i)(0)(0);
      dp[i].y   = p(i)(0)(1);
      dp[i].z   = p(i)(0)(2);
      dp[i].nx  = n(0);
      dp[i].ny  = n(1);
      dp[i].nz  = n(2);
    }

    vbo.bind();
    vbo.createBufferData( no_dp * sizeof( GL::GLVertexNormal ), dp.getPtr(), GL_STATIC_DRAW );
    vbo.unbind();
  }

  template <typename T>
  void  PTriangleVisualizer<T>::fillTriangleIBO(GL::IndexBufferObject ibo, int m ) {

    int no_indices = m*m*3;

    DVector<GLuint> indices(no_indices);
    GLuint *iptr = indices.getPtr();
    for( int i = 0; i < m; i++ ) {

      // Index row i and row i+1
      const int o1 = 0.5 *  i    * (i+1);
      const int o2 = 0.5 * (i+1) * (i+2);

      // Upper triangles (pointing down)
      for( int j = 1; j < i+1; j++ ) {

        *iptr++ = o1 + j;
        *iptr++ = o1 + j - 1;
        *iptr++ = o2 + j;
      }

      // Lower triangles (pointing up)
      for( int j = 1; j < i+2; j++ ) {

        *iptr++ = o2 + j - 1;
        *iptr++ = o2 + j;
        *iptr++ = o1 + j - 1;
      }
    }

    ibo.bind();
    ibo.createBufferData( no_indices, indices.getPtr(), GL_STATIC_DRAW );
    ibo.unbind();
  }

  template <typename T>
  void  PTriangleVisualizer<T>::fillTriangleStripIBO( GLuint ibo_id, int m ) {

    m -= 1;

    int no_indices = m*(m+2);

    DVector<GLushort> indices(no_indices);
    for( int i = 0; i < m; i++ ) {

      const int o1 = 0.5 *  i    * (i+1);
      const int o2 = 0.5 * (i+1) * (i+2);
      const int o = i*(i+2);
      const int is = 2 * i + 3;

      for( int j = 0; j < is/2; j++ ) {

        indices[o+j*2]    = o2 +j;
        indices[o+j*2+1]  = o1 +j;
      }

      indices[o+is-1] = o1+is-1;
    }

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ibo_id );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, no_indices * sizeof(GLushort), indices.getPtr(), GL_STATIC_DRAW );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0x0 );
  }

  template <typename T>
  inline
  int PTriangleVisualizer<T>::getNoTriangleStrips( int m ) {

    return m-1;
  }

  template <typename T>
  inline
  int PTriangleVisualizer<T>::getNoTriangles(int m) {

    return m*m;
  }

  template <typename T>
  inline
  int PTriangleVisualizer<T>::getNoIndicesInTriangleStrip( int strip_idx ) {

    return 2*strip_idx+3;
  }

  template <typename T>
  inline
  void PTriangleVisualizer<T>::getTriangleStripDrawInfo( int strip_idx, int& offset, int& no_indices ) {

    offset = strip_idx*(strip_idx+2);
    no_indices = 2*strip_idx+3;
  }

  template <typename T>
  inline
  int PTriangleVisualizer<T>::getTriangleStripOffset( int strip_idx ) {

    return strip_idx*(strip_idx+2);
  }

  template <typename T>
  inline
  void PTriangleVisualizer<T>::replot( const DVector< DVector< Vector<T,3> > >& /*p*/, int /*m*/ ) {}

  template <typename T>
  void PTriangleVisualizer<T>::set( SceneObject* obj ) {

    Visualizer::set( obj );

    _triangle = dynamic_cast<PTriangle<T>*>( obj );
  }





} // END namespace GMlib
