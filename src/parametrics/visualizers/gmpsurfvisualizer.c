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
#include <opengl/glsl/gmglprogram.h>
#include <opengl/glsl/gmglshadermanager.h>

// stl
#include <set>
#include <string>

namespace GMlib {

  template <typename T>
  PSurfVisualizer<T>::PSurfVisualizer() {

    _surf = 0x0;
  }

  template <typename T>
  PSurfVisualizer<T>::~PSurfVisualizer() {}

  template <typename T>
  inline
  void PSurfVisualizer<T>::fillMap(GLuint map, const DMatrix<DMatrix<Vector<T,3> > > &p, int d1, int d2) {

    DVector< Vector<float,3> > tex_data(p.getDim1() * p.getDim2());
    Vector<float,3> *ptr = tex_data.getPtr();
    for( int j = 0; j < p.getDim2(); ++j ) {
      for( int i = 0; i < p.getDim1(); ++i ) {

        *ptr++ = p(i)(j)(d1)(d2);
      }
    }

    glBindTexture( GL_TEXTURE_2D, map );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB16F, p.getDim2(), p.getDim1(), 0, GL_RGB, GL_FLOAT, tex_data.getPtr()->getPtr() );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture( GL_TEXTURE_2D, map );
  }

  template <typename T>
  inline
  void PSurfVisualizer<T>::fillNMap(GLuint nmap, const DMatrix<DMatrix<Vector<T,3> > >& p, bool closed_u, bool closed_v) {

    int m1 = closed_u ? p.getDim1()-1 : p.getDim1();
    int m2 = closed_v ? p.getDim2()-1 : p.getDim2();

    // Fill data
    DVector< Vector<float,3> > tex_data(m1 * m2);
    Vector<float,3> *ptr = tex_data.getPtr();
    for( int j = 0; j < m1; ++j )
      for( int i = 0; i < m2; ++i ) {
        *ptr++ = (p(i)(j)(1)(0) ^ p(i)(j)(0)(1)).template toType<float>();
      }


    // Create Normal map texture and set texture parameters
    glBindTexture( GL_TEXTURE_2D, nmap );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB16F, m2, m1, 0, GL_RGB, GL_FLOAT, tex_data.getPtr()->getPtr() );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if( closed_u )  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    else            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

    if( closed_v )  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    else            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

    glBindTexture( GL_TEXTURE_2D, 0 );
  }

  template <typename T>
  inline
  void PSurfVisualizer<T>::fillStandardIBO( GLuint ibo_id, int m1, int m2 ) {

    const int no_indices = m1 * m2;

    int index = 0;
    DVector<GLushort> indices(no_indices);
    GLushort* indice_ptr = indices.getPtr();
    for( int i = 0; i < m1; i++ )
      for( int j = 0; j < m2; j++ )
        *indice_ptr++ = index++;

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ibo_id );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, no_indices * sizeof(GLushort), indices.getPtr(), GL_STATIC_DRAW );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0x0 );
  }

  template <typename T>
  inline
  void PSurfVisualizer<T>::fillStandardVBO(GL::VertexBufferObject &vbo,
                                         unsigned int &no_vertices,
                                         const DMatrix<DMatrix<Vector<T,3> > > &p) {

    no_vertices = p.getDim1() * p.getDim2();

    vbo.createBufferData( no_vertices * sizeof(GL::GLVertexTex2D), 0x0, GL_STATIC_DRAW );
    vbo.bind();
    GL::GLVertexTex2D *ptr = vbo.mapBuffer<GL::GLVertexTex2D>();
    for( int i = 0; i < p.getDim1(); i++ ) {
      for( int j = 0; j < p.getDim2(); j++ ) {

        // vertex position
        ptr->x = p(i)(j)(0)(0)(0);
        ptr->y = p(i)(j)(0)(0)(1);
        ptr->z = p(i)(j)(0)(0)(2);

        // tex coords
        ptr->s = i/float(p.getDim1()-1);
        ptr->t = j/float(p.getDim2()-1);

        ptr++;
      }
    }
    vbo.unmapBuffer();

    vbo.unbind();
  }

  template <typename T>
  inline
  void PSurfVisualizer<T>::fillTriangleStripIBO(GL::IndexBufferObject& ibo, int m1, int m2) {


    const int no_indices = (m1-1) * m2 * 2;
    DVector<GLuint> indices(no_indices);

    for( int i = 0; i < m1-1; i++ ) {

      const int idx_i = i * m2 * 2;
      for( int j = 0; j < m2; j++ ) {

        const int idx_j = idx_i + (j*2);
        indices[idx_j]   = i*m2 + j;
        indices[idx_j+1] = (i+1)*m2 + j;
      }
    }

    ibo.bind();
    ibo.createBufferData( no_indices * sizeof(GLuint), indices.getPtr(), GL_STATIC_DRAW );
    ibo.unbind();
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
  void PSurfVisualizer<T>::compTriangleStripProperties(int m1, int m2, GLuint &no_strips, GLuint &no_strip_indices, GLsizei &strip_size) {

    no_strips = m1 - 1;
    no_strip_indices = m2 * 2;
    strip_size = no_strip_indices * sizeof(GLuint);
  }

  template <typename T>
  inline
  void PSurfVisualizer<T>::getTriangleStripDataInfo( const DMatrix< DMatrix< Vector<T, 3> > >& p, int& no_dp, int& no_strips, int& no_verts_per_strips ) {

    no_dp = (p.getDim1()-1) * p.getDim2() * 2;
    no_strips = p.getDim1()-1;
    no_verts_per_strips = p.getDim2()*2;
  }

  template <typename T>
  inline
  void PSurfVisualizer<T>::replot(
    DMatrix< DMatrix< Vector<T, 3> > >& /*p*/,
    DMatrix< Vector<T, 3> >& /*normals*/,
    int /*m1*/, int /*m2*/, int /*d1*/, int /*d2*/,
    bool /*closed_u*/, bool /*closed_v*/
  ) {}

  template <typename T>
  void PSurfVisualizer<T>::set( DisplayObject* obj ) {

    Visualizer::set( obj );

    _surf = dynamic_cast<PSurf<T>*>( obj );
  }



} // END namespace GMlib






