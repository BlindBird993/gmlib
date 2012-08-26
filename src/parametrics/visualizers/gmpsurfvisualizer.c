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



/*! \file gmpsurfvisualizer.c
 *
 *  Implementation of the PSurfVisualizer template class.
 */


#include "../gmpsurf.h"

// gmlib
#include <scene/gmscene.h>
#include <scene/camera/gmcamera.h>
#include <scene/light/gmlight.h>
#include <scene/utils/gmmaterial.h>
#include <opengl/gmopengl.h>
#include <opengl/gmglprogram.h>
#include <opengl/gmglshadermanager.h>

// stl
#include <set>
#include <string>

namespace GMlib {

  template <typename T>
  PSurfVisualizer<T>::PSurfVisualizer() {

    _surf = 0x0;
    setRenderProgram( GLProgram("default") );
  }

  template <typename T>
  PSurfVisualizer<T>::~PSurfVisualizer() {}

  template <typename T>
  inline
  void PSurfVisualizer<T>::fillStandardIBO( GLuint ibo_id, int m1, int m2 ) {

    const int no_indices = m1 * m2;

    int index = 0;
    GLushort indices[no_indices];
    GLushort* indice_ptr = indices;
    for( int i = 0; i < m1; i++ )
      for( int j = 0; j < m2; j++ )
        *indice_ptr++ = index++;

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ibo_id );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, no_indices * sizeof(GLushort), indices, GL_STATIC_DRAW );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0x0 );
  }

  template <typename T>
  inline
  void PSurfVisualizer<T>::fillStandardVBO(VertexBufferObject &vbo,
                                         unsigned int &no_vertices,
                                         const DMatrix<DMatrix<Vector<T,3> > > &p) {

    no_vertices = p.getDim1() * p.getDim2();

    vbo.bind();
    vbo.createBufferData( no_vertices * sizeof(GLVertexNormalTex2D), 0x0, GL_STATIC_DRAW );
    GLVertexNormalTex2D *ptr = vbo.mapBuffer<GLVertexNormalTex2D>();
//    GLVertexNormalTex2D *ptr = (GLVertexNormalTex2D*)glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY );
    for( int i = 0; i < p.getDim1(); i++ ) {
      for( int j = 0; j < p.getDim2(); j++ ) {

        // vertex position
        ptr->x = p(i)(j)(0)(0)(0);
        ptr->y = p(i)(j)(0)(0)(1);
        ptr->z = p(i)(j)(0)(0)(2);

        // normals
        const Vector<float,3> n = Vector3D<float>( p(i)(j)(1)(0) )^p(i)(j)(0)(1);
        ptr->nx = n(0);
        ptr->ny = n(1);
        ptr->nz = n(2);

        // tex coords
        ptr->s = i/float(p.getDim1()-1);
        ptr->t = j/float(p.getDim2()-1);

        ptr++;
      }
    }
    vbo.unmapBuffer();

    vbo.unbind();
  }

  //  template <typename T>
  //  inline
  //  void PSurfVisualizer<T>::fillStandardTBO( GLuint tbo_id, GLuint tex_id, DMatrix< DMatrix< Vector<T, 3> > >& p, int d1, int d2 ) {

  //    // Bind TBO
  //    glBindBuffer( GL_TEXTURE_BUFFER, tbo_id ); {

  //      // Allocate buffer memory
  //      int dp = p.getDim1() * p.getDim2();
  //      glBufferData( GL_TEXTURE_BUFFER, dp * 4 * sizeof(float), 0x0, GL_STATIC_DRAW );

  //      float *ptr = (float*)glMapBuffer( GL_TEXTURE_BUFFER, GL_WRITE_ONLY );
  //      if( ptr ) {

  //        for( int i = 0; i < p.getDim1(); i++ )
  //          for( int j = 0; j < p.getDim2(); j++ )
  //            for( int k = 0; k < 3; k++ )
  //              ptr[ ( i * p.getDim2() + j ) * 3 + k] = p[i][j][d1][d2][k];
  //      }
  //      glUnmapBuffer( GL_TEXTURE_BUFFER );

  //      glBindTexture( GL_TEXTURE_BUFFER, tex_id );
  //      glTexBuffer( GL_TEXTURE_BUFFER, GL_RGBA32F, tbo_id );
  //      glBindTexture( GL_TEXTURE_BUFFER, 0x0 );

  //    }glBindBuffer( GL_TEXTURE_BUFFER, 0x0 );
  //  }

  template <typename T>
  inline
  void PSurfVisualizer<T>::fillTriangleStripIBO(GLuint ibo_id, int m1, int m2) {

    const int no_indices = (m1-1) * m2 * 2;
    GLushort indices[no_indices];
    for( int i = 0; i < m1-1; i++ ) {

      const int idx_i = i * m2 * 2;
      for( int j = 0; j < m2; j++ ) {

        const int idx_j = idx_i + (j*2);
        indices[idx_j]   = i*m2 + j;
        indices[idx_j+1] = (i+1)*m2 + j;
      }
    }

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ibo_id );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, no_indices * sizeof(GLushort), indices, GL_STATIC_DRAW );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0x0 );
  }

  template <typename T>
  inline
  void PSurfVisualizer<T>::fillTriangleStripNormalVBO( GLuint vbo_id, DMatrix< Vector<T, 3> >& normals ) {

    int no_normals = (normals.getDim1()-1) * normals.getDim2() * 2;

    glBindBuffer( GL_ARRAY_BUFFER, vbo_id );
    glBufferData( GL_ARRAY_BUFFER, no_normals * 3 * sizeof(float), 0x0, GL_DYNAMIC_DRAW );

    float *ptr = (float*)glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY );
    if( ptr ) {

      for( int i = 0; i < normals.getDim1()-1; i++ ) {

        const int idx_i = i * normals.getDim2() * 2;
        for( int j = 0; j < normals.getDim2(); j++ ) {


          // Normals
          const int idx_j = (idx_i + (j*2)) * 3;
          const UnitVector<T,3> n1 = normals[ i   ][j];
          const UnitVector<T,3> n2 = normals[ i+1 ][j];
          for( int k = 0; k < 3; k++ ) {

            const int idx_k = idx_j + k;
            ptr[idx_k]   = n1(k);
            ptr[idx_k+3] = n2(k);
          }
        }
      }
    }

    glUnmapBuffer( GL_ARRAY_BUFFER );
    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );
  }

  template <typename T>
  inline
  void PSurfVisualizer<T>::fillTriangleStripTexVBO( GLuint vbo_id, int m1, int m2 ) {

    int no_tex = (m1-1) * m2 * 2;

    glBindBuffer( GL_ARRAY_BUFFER, vbo_id );
    glBufferData( GL_ARRAY_BUFFER, no_tex * 2 * 2 * sizeof(float), 0x0, GL_STATIC_DRAW );

    float *ptr = (float*)glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY );
    if( ptr ) {

      for( int i = 0; i < m1-1; i++ ) {

        const int idx_i = i * m2 * 2;
        for( int j = 0; j < m2; j++ ) {

          // Texture Coords
          const int idx_k = (idx_i + (j*2)) * 2;
          ptr[idx_k]   = i / float( m1 - 1 ); // s1
          ptr[idx_k+1] = j / float( m2 - 1 ); // t1
          ptr[idx_k+2] = (i+1) / float( m1 - 1 ); // s2
          ptr[idx_k+3] = j / float( m2 - 1 ); // t2
        }
      }
    }

    glUnmapBuffer( GL_ARRAY_BUFFER );
    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );
  }

  template <typename T>
  inline
  void PSurfVisualizer<T>::fillTriangleStripVBO( GLuint vbo_id, DMatrix< DMatrix< Vector<T, 3> > >& p, int d1, int d2 ) {

    int no_dp;
    int no_strips;
    int no_verts_per_strips;
    PSurfVisualizer<T>::getTriangleStripDataInfo( p, no_dp, no_strips, no_verts_per_strips );

    glBindBuffer( GL_ARRAY_BUFFER, vbo_id );
    glBufferData( GL_ARRAY_BUFFER, no_dp * 3 * sizeof(float), 0x0,  GL_DYNAMIC_DRAW );

    float *ptr = (float*)glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY );
    if( ptr ) {

      for( int i = 0; i < p.getDim1()-1; i++ ) {

        const int idx_i = i * p.getDim2() * 2;
        for( int j = 0; j < p.getDim2(); j++ ) {

          // Populate data
          const int idx_j = (idx_i + (j*2)) * 3;
          for( int k = 0; k < 3; k++ ) {

            const int idx_k = idx_j + k;
            ptr[idx_k]   = p[ i   ][j][d1][d2][k];
            ptr[idx_k+3] = p[ i+1 ][j][d1][d2][k];
          }
        }
      }
    }

    glUnmapBuffer( GL_ARRAY_BUFFER );
    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );
  }

  template <typename T>
  inline
  int PSurfVisualizer<T>::getNoIndicesPerTriangleStrip( int /*m1*/, int m2 ) {

    return m2*2;
  }

  template <typename T>
  inline
  int PSurfVisualizer<T>::getNoTriangleStrips( int m1, int /*m2*/ ) {

    return m1-1;
  }

  template <typename T>
  inline
  void PSurfVisualizer<T>::getTriangleStripDataInfo( const DMatrix< DMatrix< Vector<T, 3> > >& p, int& no_dp, int& no_strips, int& no_verts_per_strips ) {

    no_dp = (p.getDim1()-1) * p.getDim2() * 2;
    no_strips = p.getDim1()-1;
    no_verts_per_strips = p.getDim2()*2;
  }

  template <typename T>
  std::string PSurfVisualizer<T>::getIdentity() const {

    return "PSurf Visualizer";
  }

  template <typename T>
  inline
  void PSurfVisualizer<T>::replot(
    DMatrix< DMatrix< Vector<T, 3> > >& /*p*/,
    DMatrix< Vector<T, 3> >& /*normals*/,
    int /*m1*/, int /*m2*/, int /*d1*/, int /*d2*/
  ) {}

  template <typename T>
  void PSurfVisualizer<T>::set( SceneObject* obj ) {

    Visualizer::set( obj );

    _surf = dynamic_cast<PSurf<T>*>( obj );
  }

} // END namespace GMlib






