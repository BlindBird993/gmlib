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



/*! \file gmtrianglefacetsdefaultvisualizer.h
 *
 *  TriangleFacetsDefaultVisualizer implementations
 */


#include "../gmtrianglesystem.h"


namespace GMlib {

  template <typename T>
  TriangleFacetsDefaultVisualizer<T>::TriangleFacetsDefaultVisualizer() :
    _vbo(), _ibo() {}

  template <typename T>
  TriangleFacetsDefaultVisualizer<T>::~TriangleFacetsDefaultVisualizer() {}

  template <typename T>
  inline
  void TriangleFacetsDefaultVisualizer<T>::display() {

    this->glSetDisplayMode();

    const GL::GLProgram &prog = this->getRenderProgram();

    prog.setUniform( "u_color", this->_obj->getColor() );
    prog.setUniform( "u_selected", this->_obj->isSelected() );
    prog.setUniform( "u_lighted", this->_obj->isLighted() );

    // Light data
    GLuint light_u_block_idx =  prog.getUniformBlockIndex( "Lights" );
    glBindBufferBase( GL_UNIFORM_BUFFER, 0, GL::OGL::getLightBuffer() );
    glUniformBlockBinding( prog.getId(), light_u_block_idx, 0 );

    // Get Material Data
    const Material &m = this->_obj->getMaterial();
    prog.setUniform( "u_mat_amb", m.getAmb() );
    prog.setUniform( "u_mat_dif", m.getDif() );
    prog.setUniform( "u_mat_spc", m.getSpc() );
    prog.setUniform( "u_mat_shin", m.getShininess() );

    GLuint vert_loc = prog.getAttributeLocation( "in_vertex" );
    GLuint normal_loc = prog.getAttributeLocation( "in_normal" );

    _vbo.bind();
    _vbo.enable( vert_loc, 3, GL_FLOAT, GL_FALSE,  sizeof(GL::GLVertexNormal), (const GLvoid*)0x0 );
    _vbo.enable( normal_loc, 3, GL_FLOAT, GL_TRUE, sizeof(GL::GLVertexNormal), (const GLvoid*)sizeof(GL::GLVertex) );
    _ibo.draw();
    _vbo.disable( vert_loc );
    _vbo.disable( normal_loc );
    _vbo.unbind();
  }

  template <typename T>
  inline
  void TriangleFacetsDefaultVisualizer<T>::replot() {

    TriangleFacetsVisualizer<T>::fillStandardVBO( _vbo, this->_tf );
    TriangleFacetsVisualizer<T>::fillStandardIBO( _ibo, this->_tf );
  }

  template <typename T>
  inline
  void TriangleFacetsDefaultVisualizer<T>::select() {

    GLuint vert_loc = this->getSelectProgram().getAttributeLocation( "in_vertex" );

    _vbo.bind();
    _vbo.enable( vert_loc, 3, GL_FLOAT, GL_FALSE, sizeof(GL::GLVertexNormal), (const GLvoid*)0x0 );
    _ibo.draw();
    _vbo.disable( vert_loc );
    _vbo.unbind();
  }



} // END namespace GMlib
