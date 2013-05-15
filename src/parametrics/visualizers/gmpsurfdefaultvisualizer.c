
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

  template <typename T, int n>
  PSurfDefaultVisualizer<T,n>::PSurfDefaultVisualizer()
    : _vbo(), _ibo(), _lights_ubo("lights_ubo"), _nmap(),
      _no_strips(0), _no_strip_indices(0), _strip_size(0) {

    this->setRenderProgram( GL::GLProgram("psurf_phong_nmap") );
  }

  template <typename T, int n>
  PSurfDefaultVisualizer<T,n>::PSurfDefaultVisualizer(const PSurfDefaultVisualizer<T,n>& copy)
    : PSurfVisualizer<T,n>(copy),
      _vbo(), _ibo(), _lights_ubo("lights_ubo"), _nmap(),
      _no_strips(0), _no_strip_indices(0), _strip_size(0) {

    this->setRenderProgram( GL::GLProgram("psurf_phong_nmap") );
  }

  template <typename T, int n>
  inline
  void PSurfDefaultVisualizer<T,n>::render( const DisplayObject* obj, const Camera* cam ) const {

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

      // Material
      const Material &m = obj->getMaterial();
      prog.setUniform( "u_mat_amb", m.getAmb() );
      prog.setUniform( "u_mat_dif", m.getDif() );
      prog.setUniform( "u_mat_spc", m.getSpc() );
      prog.setUniform( "u_mat_shi", m.getShininess() );

      // Normal map
      prog.setUniform( "u_nmap", _nmap, (GLenum)GL_TEXTURE0, 0 );

      // Get vertex and texture attrib locations
      GL::AttributeLocation vert_loc = prog.getAttributeLocation( "in_vertex" );
      GL::AttributeLocation tex_loc = prog.getAttributeLocation( "in_tex" );

      // Bind and draw
      _vbo.bind();
      _vbo.enable( vert_loc, 3, GL_FLOAT, GL_FALSE, sizeof(GL::GLVertexTex2D), reinterpret_cast<const GLvoid *>(0x0) );
      _vbo.enable( tex_loc,  2, GL_FLOAT, GL_FALSE, sizeof(GL::GLVertexTex2D), reinterpret_cast<const GLvoid *>(3*sizeof(GLfloat)) );

      draw();

      _vbo.disable( vert_loc );
      _vbo.disable( tex_loc );
      _vbo.unbind();

    } prog.unbind();
  }

  template <typename T, int n>
  inline
  void PSurfDefaultVisualizer<T,n>::draw() const {

    _ibo.bind();
    for( unsigned int i = 0; i < _no_strips; ++i )
      _ibo.drawElements( GL_TRIANGLE_STRIP, _no_strip_indices, GL_UNSIGNED_INT, reinterpret_cast<const GLvoid *>(i * _strip_size) );
    _ibo.unbind();
  }

  template <typename T, int n>
  inline
  void PSurfDefaultVisualizer<T,n>::replot(
    const DMatrix< DMatrix< Vector<T, n> > >& p,
    const DMatrix< Vector<T, 3> >& normals,
    int /*m1*/, int /*m2*/, int /*d1*/, int /*d2*/,
    bool closed_u, bool closed_v
  ) {

    PSurfVisualizer<T,n>::fillStandardVBO( _vbo, p );
    PSurfVisualizer<T,n>::fillTriangleStripIBO( _ibo, p.getDim1(), p.getDim2(), _no_strips, _no_strip_indices, _strip_size );
    PSurfVisualizer<T,n>::fillNMap( _nmap, normals, closed_u, closed_v );
  }

  template <typename T, int n>
  inline
  void PSurfDefaultVisualizer<T,n>::renderGeometry( const GL::AttributeLocation& vert_loc ) const {

    _vbo.bind();
    _vbo.enable( vert_loc, 3, GL_FLOAT, GL_FALSE, sizeof(GL::GLVertexTex2D), reinterpret_cast<const GLvoid *>(0x0) );

    draw();

    _vbo.disable( vert_loc );
    _vbo.unbind();
  }

} // END namespace GMlib






