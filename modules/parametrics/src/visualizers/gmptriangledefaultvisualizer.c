
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



/*! \file gmptriangledefaultvisualizer.c
 *
 *  Implementation of the PTriangleDefaultVisualizer template class.
 */

#include "gmptriangledefaultvisualizer.h"

// gmlib
#include <scene/camera/gmcamera.h>

namespace GMlib {


  template <typename T, int n>
  PTriangleDefaultVisualizer<T,n>::PTriangleDefaultVisualizer()
    : _no_elements(0) {

    _prog.acquire("phong");
    _geometry_prog.acquire("color");

    _vbo.create();
    _ibo.create();
  }

  template <typename T, int n>
  inline
  void PTriangleDefaultVisualizer<T,n>::render(const SceneObject *obj, const DefaultRenderer* renderer) const {

    const Camera* cam = renderer->getCamera();

    const HqMatrix<float,3> &mvmat = obj->getModelViewMatrix(cam);
    const HqMatrix<float,3> &pmat = obj->getProjectionMatrix(cam);

    this->glSetDisplayMode();

    _prog.bind(); {

      // Model view and projection matrices
      _prog.setUniform( "u_mvmat", mvmat );
      _prog.setUniform( "u_mvpmat", pmat * mvmat );

      // Lights
      _prog.setUniformBlockBinding( "Lights", renderer->getLightUBO(), 0 );

      // Get Material Data
      const Material &m = obj->getMaterial();
      _prog.setUniform( "u_mat_amb", m.getAmb() );
      _prog.setUniform( "u_mat_dif", m.getDif() );
      _prog.setUniform( "u_mat_spc", m.getSpc() );
      _prog.setUniform( "u_mat_shin", m.getShininess() );

      GL::AttributeLocation vert_loc = _prog.getAttributeLocation( "in_vertex" );
      GL::AttributeLocation normal_loc = _prog.getAttributeLocation( "in_normal" );

      _vbo.bind();
      _vbo.enable( vert_loc, 3, GL_FLOAT, GL_FALSE,  sizeof(GL::GLVertexNormal), reinterpret_cast<const GLvoid*>(0x0) );
      _vbo.enable( normal_loc, 3, GL_FLOAT, GL_TRUE, sizeof(GL::GLVertexNormal), reinterpret_cast<const GLvoid*>(sizeof(GL::GLVertex) ) );

      draw();

      _vbo.disable( vert_loc );
      _vbo.disable( normal_loc );
      _vbo.unbind();

    } _prog.unbind();
  }

  template <typename T, int n>
  inline
  void PTriangleDefaultVisualizer<T,n>::replot( const DVector< DVector< Vector<T,3> > >& p, int m ) {

    _no_elements = PTriangleVisualizer<T,n>::getNoTriangles( m )*3;

    // Fill VBO
    PTriangleVisualizer<T,n>::fillStandardVBO( _vbo, p );

    // Fill IBO
    PTriangleVisualizer<T,n>::fillTriangleIBO( _ibo, m );
  }

  template <typename T, int n>
  inline
  void PTriangleDefaultVisualizer<T,n>::renderGeometry( const SceneObject* obj, const Renderer* renderer, const Color& color ) const {

    _geometry_prog.bind(); {

      _geometry_prog.setUniform( "u_color", color );
      _geometry_prog.setUniform( "u_mvpmat", obj->getModelViewProjectionMatrix(renderer->getCamera()) );
      GL::AttributeLocation vertice_loc = _geometry_prog.getAttributeLocation( "in_vertex" );

      _vbo.bind();
      _vbo.enable( vertice_loc, 3, GL_FLOAT, GL_FALSE, sizeof(GL::GLVertexNormal), reinterpret_cast<const GLvoid*>(0x0) );

      draw();

      _vbo.disable( vertice_loc );
      _vbo.unbind();

    } _geometry_prog.unbind();
  }

  template <typename T, int n>
  inline
  void PTriangleDefaultVisualizer<T,n>::draw() const {

    _ibo.bind();
    _ibo.drawElements( GL_TRIANGLES, _no_elements, GL_UNSIGNED_INT, reinterpret_cast<const GLvoid*>(0x0) );
    _ibo.unbind();
  }

} // END namespace GMlib
