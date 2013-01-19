
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



/*! \file gmpsurfdefaultvisualizer.c
 *
 *  Implementation of the PSurfDefaultVisualizer template class.
 */


#include "../gmpsurf.h"

// gmlib
#include <opengl/gmopengl.h>
#include <opengl/glsl/gmglprogram.h>
#include <opengl/glsl/gmglshadermanager.h>
#include <scene/gmscene.h>
#include <scene/camera/gmcamera.h>
#include <scene/light/gmlight.h>
#include <scene/utils/gmmaterial.h>

// stl
#include <set>
#include <string>

namespace GMlib {

  template <typename T>
  PSurfDefaultVisualizer<T>::PSurfDefaultVisualizer() : _vbo(), _ibo(), _no_vertices(0) {

    glGenTextures( 1, &_nmap );
    this->setRenderProgram( GL::GLProgram("psurf_phong_nmap") );
  }

  template <typename T>
  PSurfDefaultVisualizer<T>::~PSurfDefaultVisualizer() {

    glDeleteTextures( 1, &_nmap );
  }

  template <typename T>
  inline
  void PSurfDefaultVisualizer<T>::display() {

    this->glSetDisplayMode();

    const GL::GLProgram &prog = this->getRenderProgram();

    // States
    prog.setUniform( "u_selected", this->_obj->isSelected() );
    prog.setUniform( "u_lighted", this->_obj->isLighted() );

    // Color
    prog.setUniform( "u_color", this->_obj->getColor() );

    // Light data
    GLuint light_u_block_idx =  prog.getUniformBlockIndex( "Lights" );
    glBindBufferBase( GL_UNIFORM_BUFFER, 0, GL::OGL::getLightBuffer() );
    glUniformBlockBinding( prog.getId(), light_u_block_idx, 0 );

    // Material data
    const Material &m = this->_obj->getMaterial();
    prog.setUniform( "u_mat_amb", m.getAmb() );
    prog.setUniform( "u_mat_dif", m.getDif() );
    prog.setUniform( "u_mat_spc", m.getSpc() );
    prog.setUniform( "u_mat_shi", m.getShininess() );

    prog.setUniform( "u_nmap", _nmap, (GLenum)GL_TEXTURE0, 0 );

    GLuint vert_loc = prog.getAttributeLocation( "in_vertex" );
    GLuint tex_loc = prog.getAttributeLocation( "in_tex" );


    _vbo.bind();
    _vbo.enable( vert_loc,    3, GL_FLOAT, GL_FALSE, sizeof(GL::GLVertexTex2D), reinterpret_cast<const GLvoid *>(0x0) );
    _vbo.enable( tex_loc,     2, GL_FLOAT, GL_FALSE, sizeof(GL::GLVertexTex2D), reinterpret_cast<const GLvoid *>(3*sizeof(GLfloat)) );

    draw();

    _vbo.disable( vert_loc );
    _vbo.disable( tex_loc );
    _vbo.unbind();
  }

  template <typename T>
  inline
  void PSurfDefaultVisualizer<T>::draw() {

    _ibo.bind();
    for( int i = 0; i < _no_strips; ++i )
      glDrawElements( GL_TRIANGLE_STRIP, _no_strip_indices, GL_UNSIGNED_INT, reinterpret_cast<const GLvoid *>(i * _strip_size) );
    _ibo.unbind();
  }

  template <typename T>
  inline
  void PSurfDefaultVisualizer<T>::replot(
    DMatrix< DMatrix< Vector<T, 3> > >& p,
    DMatrix< Vector<T, 3> >& normals,
    int /*m1*/, int /*m2*/, int /*d1*/, int /*d2*/,
    bool closed_u, bool closed_v
  ) {

    PSurfVisualizer<T>::fillNMap( _nmap, p, closed_u, closed_v );

    PSurfVisualizer<T>::fillStandardVBO( _vbo, _no_vertices, p );

    PSurfVisualizer<T>::fillTriangleStripIBO( _ibo, p.getDim1(), p.getDim2() );
    PSurfVisualizer<T>::compTriangleStripProperties( p.getDim1(), p.getDim2(), _no_strips, _no_strip_indices, _strip_size );
  }

  template <typename T>
  inline
  void PSurfDefaultVisualizer<T>::select() {

    GLuint vert_loc = this->getSelectProgram().getAttributeLocation( "in_vertex" );

    _vbo.bind();
    _vbo.enable( vert_loc, 3, GL_FLOAT, GL_FALSE, sizeof(GL::GLVertexTex2D), reinterpret_cast<const GLvoid *>(0x0) );

    draw();

    _vbo.disable( vert_loc );
    _vbo.unbind();
  }

} // END namespace GMlib






