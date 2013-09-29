
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

#include "gmpsurfparamlinesvisualizer.h"

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
PSurfParamLinesVisualizer<T,n>::PSurfParamLinesVisualizer()
  : _vbo(), _ibo(), _lights_ubo("lights_ubo"), _nmap(GL_TEXTURE_2D),
    _ptex_u(GL_TEXTURE_2D), _ptex_v(GL_TEXTURE_2D),
    _no_strips(0), _no_strip_indices(0), _strip_size(0),
    _mat(GMmaterial::BlackRubber) {

  this->setRenderProgram( GL::GLProgram("psurf_phong_nmap_ptex") );
}

template <typename T, int n>
PSurfParamLinesVisualizer<T,n>::PSurfParamLinesVisualizer(const PSurfParamLinesVisualizer<T,n>& copy)
  : _vbo(), _ibo(), _lights_ubo("lights_ubo"), _nmap(GL_TEXTURE_2D),
    _ptex_u(GL_TEXTURE_2D), _ptex_v(GL_TEXTURE_2D),
    _no_strips(0), _no_strip_indices(0), _strip_size(0),
    _mat(copy._mat) {

  this->setRenderProgram( GL::GLProgram("psurf_phong_nmap_ptex") );
}

template <typename T, int n>
void PSurfParamLinesVisualizer<T,n>::render( const DisplayObject* obj, const Camera* cam ) const {

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

    // Base material
    prog.setUniform( "u_mat_amb", obj->getMaterial().getAmb() );
    prog.setUniform( "u_mat_dif", obj->getMaterial().getDif() );
    prog.setUniform( "u_mat_spc", obj->getMaterial().getSpc() );
    prog.setUniform( "u_mat_shi", obj->getMaterial().getShininess() );

    // Line Material
    prog.setUniform( "u_mat_line_amb", _mat.getAmb() );
    prog.setUniform( "u_mat_line_dif", _mat.getDif() );
    prog.setUniform( "u_mat_line_spc", _mat.getSpc() );
    prog.setUniform( "u_mat_line_shi", _mat.getShininess() );

    // Normal map
    prog.setUniform( "u_nmap", _nmap, (GLenum)GL_TEXTURE0, 0 );
    prog.setUniform( "u_ptex_u", _ptex_u, (GLenum)GL_TEXTURE1, 1 );
    prog.setUniform( "u_ptex_v", _ptex_v, (GLenum)GL_TEXTURE2, 2 );

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
void PSurfParamLinesVisualizer<T,n>::draw() const {

  _ibo.bind();
  for( unsigned int i = 0; i < _no_strips; ++i )
    _ibo.drawElements( GL_TRIANGLE_STRIP, _no_strip_indices, GL_UNSIGNED_INT, reinterpret_cast<const GLvoid *>(i * _strip_size) );
  _ibo.unbind();
}


template <typename T, int n>
void PSurfParamLinesVisualizer<T,n>::replot(
  const DMatrix< DMatrix< Vector<T, n> > >& p,
  const DMatrix< Vector<T, 3> >& normals,
  int /*m1*/, int /*m2*/, int /*d1*/, int /*d2*/,
  bool closed_u, bool closed_v
) {

  PSurfVisualizer<T,n>::fillStandardVBO( _vbo, p );
  PSurfVisualizer<T,n>::fillTriangleStripIBO( _ibo, p.getDim1(), p.getDim2(), _no_strips, _no_strip_indices, _strip_size );
  PSurfVisualizer<T,n>::fillNMap( _nmap, normals, closed_u, closed_v );

  generatePTex( 10, 10, 3, 3, closed_u, closed_v );
}

/*!
 *
 *  \param[in] m1 Nuber of U lines
 *  \param[in] m2 Nuber of V lines
 *  \param[in] w1 U line spacing [0,n]
 *  \param[in] w2 V line spacing [0,n]
 *  \param[in] closed_u Closed in U
 *  \param[in] closed_v Closed in V
 */
template <typename T, int n>
void PSurfParamLinesVisualizer<T,n>::generatePTex(int m1, int m2, int s1, int s2, bool closed_u, bool closed_v) {

  DVector<float> tex_data_u, tex_data_v;

  if( m1 < 2 || m2 < 2 || s1 ==0 || s2 == 0 ) {

    tex_data_u = DVector<float>(1,0.0f);
    tex_data_v = DVector<float>(1,0.0f);
  }
  else {

    int m1_t, m2_t;
    m1_t = (m1-1)*(s1+1) + 1;
    m2_t = (m2-1)*(s2+1) + 1;

    tex_data_u = DVector<float>(m1_t,0.0f);
    tex_data_v = DVector<float>(m2_t,0.0f);

    for( int i = 0; i < m1_t; i += (s1+1) )  tex_data_u[i] = 1.0f;
    for( int i = 0; i < m2_t; i += (s2+1) )  tex_data_v[i] = 1.0f;
  }

  // Create U line tex
  _ptex_u.texImage2D( 0, GL_R8, tex_data_u.getDim(), 1, 0, GL_RED, GL_FLOAT, tex_data_u.getPtr() );
  _ptex_u.texParameteri( GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  _ptex_u.texParameteri( GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  if( closed_u )  _ptex_u.texParameterf(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  else            _ptex_u.texParameterf(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  if( closed_v )  _ptex_v.texParameterf(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  else            _ptex_v.texParameterf(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  // Create V line tex
  _ptex_v.texImage2D( 0, GL_R8, 1, tex_data_v.getDim(), 0, GL_RED, GL_FLOAT, tex_data_v.getPtr() );
  _ptex_v.texParameteri( GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  _ptex_v.texParameteri( GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  if( closed_u )  _ptex_u.texParameterf(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  else            _ptex_u.texParameterf(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  if( closed_v )  _ptex_v.texParameterf(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  else            _ptex_v.texParameterf(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

} // END namespace GMlib






