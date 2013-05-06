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

// gmlib
#include <opengl/gmopengl.h>


namespace GMlib {

  template <typename T>
  TriangleFacetsDefaultVisualizer<T>::TriangleFacetsDefaultVisualizer() :
    _vbo(), _ibo(), _lights_ubo("lights_ubo"), _no_elements(0) {

    this->setRenderProgram( GL::GLProgram("phong") );
  }

  template <typename T>
  TriangleFacetsDefaultVisualizer<T>::~TriangleFacetsDefaultVisualizer() {}

  template <typename T>
  inline
  void TriangleFacetsDefaultVisualizer<T>::render(const DisplayObject *obj, const Camera *cam) const {

    const HqMatrix<float,3> &mvmat = obj->getModelViewMatrix(cam);
    const HqMatrix<float,3> &pmat = obj->getProjectionMatrix(cam);

    this->glSetDisplayMode();

    const GL::GLProgram &prog = this->getRenderProgram();
    prog.bind(); {

      // Model view and projection matrices
      prog.setUniform( "u_mvmat", mvmat );
      prog.setUniform( "u_mvpmat", pmat * mvmat );

      // Lights
      prog.setUniformBlockBinding( "Lights", _lights_ubo, 0 );

      // Get Material Data
      const Material &m = obj->getMaterial();
      prog.setUniform( "u_mat_amb", m.getAmb() );
      prog.setUniform( "u_mat_dif", m.getDif() );
      prog.setUniform( "u_mat_spc", m.getSpc() );
      prog.setUniform( "u_mat_shin", m.getShininess() );

      GL::AttributeLocation vert_loc = prog.getAttributeLocation( "in_vertex" );
      GL::AttributeLocation normal_loc = prog.getAttributeLocation( "in_normal" );

      _vbo.bind();
      _vbo.enable( vert_loc, 3, GL_FLOAT, GL_FALSE,  sizeof(GL::GLVertexNormal), 0x0 );
      _vbo.enable( normal_loc, 3, GL_FLOAT, GL_TRUE, sizeof(GL::GLVertexNormal), reinterpret_cast<const GLvoid*>(sizeof(GL::GLVertex)) );

      draw();

      _vbo.disable( vert_loc );
      _vbo.disable( normal_loc );
      _vbo.unbind();

    } prog.unbind();
  }

  template <typename T>
  inline
  void TriangleFacetsDefaultVisualizer<T>::replot(TriangleFacets<T> *tf) {

    TriangleFacetsVisualizer<T>::fillStandardVBO( _vbo, tf );
    TriangleFacetsVisualizer<T>::fillStandardIBO( _ibo, tf );

    _no_elements = tf->getNoTriangles() * 3;
  }

  template <typename T>
  inline
  void TriangleFacetsDefaultVisualizer<T>::draw() const {

    _ibo.bind();
    _ibo.drawElements( GL_TRIANGLES, _no_elements, GL_UNSIGNED_INT, reinterpret_cast<const GLvoid*>(0x0) );
    _ibo.unbind();
  }

  template <typename T>
  inline
  void TriangleFacetsDefaultVisualizer<T>::renderGeometry(const GL::AttributeLocation &vertice_loc) const {

    _vbo.bind();
    _vbo.enable( vertice_loc, 3, GL_FLOAT, GL_FALSE, sizeof(GL::GLVertexNormal), reinterpret_cast<const GLvoid*>(0x0) );

    draw();

    _ibo.unbind();
    _vbo.disable( vertice_loc );
    _vbo.unbind();
  }



} // END namespace GMlib
