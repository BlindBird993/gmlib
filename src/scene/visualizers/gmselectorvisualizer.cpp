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


#include "gmselectorvisualizer.h"

#include "../gmdisplayobject.h"

// gmlib
#include <opengl/gmopengl.h>


namespace GMlib {


  SelectorVisualizer *SelectorVisualizer::_s_instance = 0x0;


  SelectorVisualizer::SelectorVisualizer( float r, Material mat )
    : _vbo(), _ibo(), _lights_ubo("lights_ubo"),
      _top_bot_verts(0), _mid_strips(0), _mid_strips_verts(0),
      _mat(mat) {

    setRenderProgram( GL::GLProgram( "phong" ) );
    makeGeometry( r, 10, 10 );
  }

  SelectorVisualizer::SelectorVisualizer(int m1, int m2, float r, Material mat)
    : _vbo(), _ibo(),
      _top_bot_verts(0), _mid_strips(0), _mid_strips_verts(0),
      _mat(mat) {

    setRenderProgram( GL::GLProgram( "phong" ) );
    makeGeometry( r, m1, m2 );
  }

  SelectorVisualizer::~SelectorVisualizer() {}

  void SelectorVisualizer::render(const DisplayObject* obj, const Camera *cam) const {

    const HqMatrix<float,3> &mvmat = obj->getModelViewMatrix(cam);
    const HqMatrix<float,3> &pmat = obj->getProjectionMatrix(cam);

    const GL::GLProgram &prog = this->getRenderProgram();
    prog.bind(); {

      // Model view and projection matrices
      prog.setUniform( "u_mvmat", mvmat );
      prog.setUniform( "u_mvpmat", pmat * mvmat );

      // Lights
      prog.setUniformBlockBinding( "Lights", _lights_ubo, 0 );

      // Material data
      prog.setUniform( "u_mat_amb", _mat.getAmb() );
      prog.setUniform( "u_mat_dif", _mat.getDif() );
      prog.setUniform( "u_mat_spc", _mat.getSpc() );
      prog.setUniform( "u_mat_shi", _mat.getShininess() );

      // Shader attribute locations
      GL::AttributeLocation vert_loc = prog.getAttributeLocation( "in_vertex" );
      GL::AttributeLocation normal_loc = prog.getAttributeLocation( "in_normal" );

      // Bind and draw
      _vbo.bind();
      _vbo.enable( vert_loc, 3, GL_FLOAT, GL_FALSE, sizeof(GL::GLVertexNormal), reinterpret_cast<const GLvoid *>(0x0) );
      _vbo.enable( normal_loc, 3, GL_FLOAT, GL_FALSE, sizeof(GL::GLVertexNormal), reinterpret_cast<const GLvoid *>(sizeof(GL::GLNormal)) );

      // Draw top and bottom caps
      for( int i = 0; i < 2; i++ )
        glDrawArrays( GL_TRIANGLE_FAN, i * _top_bot_verts, _top_bot_verts );

      // Draw body strips
      for( int i = 0; i < _mid_strips; i++ )
        glDrawArrays( GL_TRIANGLE_STRIP, _top_bot_verts*2 + i*_mid_strips_verts, _mid_strips_verts );

      _vbo.disable( normal_loc );
      _vbo.disable( vert_loc );
      _vbo.unbind();

    } prog.unbind();
  }

  SelectorVisualizer *SelectorVisualizer::getInstance() {

    if( !_s_instance )
      _s_instance = new SelectorVisualizer;

    return _s_instance;
  }

  void SelectorVisualizer::makeGeometry(float r, int m1, int m2) {

    _top_bot_verts = m2+2;
    _mid_strips = m1-2;
    _mid_strips_verts = (m2+1) * 2;

    const unsigned int verts = _top_bot_verts * 2 + _mid_strips * _mid_strips_verts;


    DVector<GL::GLVertexNormal> v(verts);
    GL::GLVertexNormal *v_ptr = v.getPtr();

    // Compute stride in the spheres u and v parametric direction.
    const float du = M_PI / m1;
    const float dv = M_2PI / m2;


    // Compute top and bottom triangle fans for the sphere
    {
      float u;
      float su, cu, ru;

      const Arrow<float,3> top = Arrow<float,3>(Point<float,3>(0,0,r), Vector<float,3>(0,0,1));
      v_ptr->x = top.getPos()(0);
      v_ptr->y = top.getPos()(1);
      v_ptr->z = top.getPos()(2);
      v_ptr->nx = top.getDir()(0);
      v_ptr->ny = top.getDir()(1);
      v_ptr->nz = top.getDir()(2);
      v_ptr++;

      u = M_PI_2 - du;

      su = sin(u);
      cu = cos(u);
      ru = r * cu;

      float v = 0;
      for( int i = 0; i < m2+1; i++, v += dv ) {

        const float sv = sin(v);
        const float cv = cos(v);

        v_ptr->x  = ru*cv;
        v_ptr->y  = ru*sv;
        v_ptr->z  = r*su;
        v_ptr->nx = cu*cv;
        v_ptr->ny = cu*sv;
        v_ptr->nz = su;
        v_ptr++;
      }


      const Arrow<float,3> bottom = Arrow<float,3>(Point<float,3>(0,0,-r),Vector<float,3>(0,0,-1));
      v_ptr->x  = bottom.getPos()(0);
      v_ptr->y  = bottom.getPos()(1);
      v_ptr->z  = bottom.getPos()(2);
      v_ptr->nx = bottom.getDir()(0);
      v_ptr->ny = bottom.getDir()(1);
      v_ptr->nz = bottom.getDir()(2);
      v_ptr++;

      u = M_PI_2 - du * (m1-1);
      su = sin(u);
      cu = cos(u);
      ru = r * cu;

      v = 0;
      for( int i = m2; i >= 0; i--, v += dv ) {

        const float sv = sin(v);
        const float cv = cos(v);

        v_ptr->x = ru*cv;
        v_ptr->y = ru*sv;
        v_ptr->z = r*su;
        v_ptr->nx = cu*cv;
        v_ptr->ny = cu*sv;
        v_ptr->nz = su;
        v_ptr++;
      }
    }


    // Compute body triangle strips on the sphere
    for( int i = 0; i < m1-2; i++ ) {

      const float u1 = M_PI_2 - du * (i+1);
      const float u2 = M_PI_2 - du * (i+2);

      const float su1 = sin(u1);
      const float cu1 = cos(u1);
      const float ru1 = r * cu1;

      const float su2 = sin(u2);
      const float cu2 = cos(u2);
      const float ru2 = r * cu2;

      for( int j = 0; j < m2+1; j++ ) {

        const float v = j * dv;
        const float sv = sin(v);
        const float cv = cos(v);

        v_ptr->x = ru1*cv;
        v_ptr->y = ru1*sv;
        v_ptr->z = r*su1;
        v_ptr->nx = cu1*cv;
        v_ptr->ny = cu1*sv;
        v_ptr->nz = su1;
        v_ptr++;

        v_ptr->x = ru2*cv;
        v_ptr->y = ru2*sv;
        v_ptr->z = r*su2;
        v_ptr->nx = cu2*cv;
        v_ptr->ny = cu2*sv;
        v_ptr->nz = su2;
        v_ptr++;
      }
    }

    _vbo.createBufferData( v.getDim() * sizeof(GL::GLVertexNormal), v.getPtr(), GL_STATIC_DRAW );

  }

  void SelectorVisualizer::renderGeometry(const GL::AttributeLocation &vert_loc) const {

    _vbo.bind();
    _vbo.enable( vert_loc, 3, GL_FLOAT, GL_FALSE, sizeof(GL::GLVertexNormal), reinterpret_cast<const GLvoid *>(0x0) );

    // Draw top and bottom caps
    for( int i = 0; i < 2; i++ )
      glDrawArrays( GL_TRIANGLE_FAN, i * _top_bot_verts, _top_bot_verts );

    // Draw body strips
    for( int i = 0; i < _mid_strips; i++ )
      glDrawArrays( GL_TRIANGLE_STRIP, _top_bot_verts*2 + i*_mid_strips_verts, _mid_strips_verts );

    _vbo.disable( vert_loc );
    _vbo.unbind();
  }


} // END namespace GMlib
