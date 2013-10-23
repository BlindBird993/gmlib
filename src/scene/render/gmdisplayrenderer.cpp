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

/*! \file gmdisplayrender.cpp
 *  \brief Pending Documentation
 *
 *  Pending Documentation
 */


#include "gmdisplayrenderer.h"

// local
#include "../camera/gmcamera.h"
#include "rendertargets/gmnativerendertarget.h"

//stl
#include <cassert>



namespace GMlib {




  DisplayRenderer::DisplayRenderer(Scene *scene)
    : MultiObjectRenderer(scene), _w(0), _h(0)
  {


    // Acquire programs
    _render_prog.acquire("render");
    _render_select_prog.acquire("render_select");
    _border_prog.acquire("color");


    // Create buffers
    _fbo.create();

    _rbo_color.create(GL_TEXTURE_2D);
    _rbo_depth.create( GL_TEXTURE_2D);

    _fbo_select.create();
    _fbo_select_depth.create();

    _rbo_select.create(GL_TEXTURE_2D);
    _rbo_select_depth.create(GL_TEXTURE_2D);

    // Color rbo texture
    _rbo_color.texParameteri( GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    _rbo_color.texParameteri( GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    _rbo_color.texParameterf( GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    _rbo_color.texParameterf( GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Depth rbo texture
    _rbo_depth.texParameteri( GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    _rbo_depth.texParameteri( GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    _rbo_depth.texParameterf( GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    _rbo_depth.texParameterf( GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Select rbo texture
    _rbo_select.texParameteri( GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    _rbo_select.texParameteri( GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    _rbo_select.texParameterf( GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    _rbo_select.texParameterf( GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Select depth rbo texture
    _rbo_select_depth.texParameteri( GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    _rbo_select_depth.texParameteri( GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    _rbo_select_depth.texParameterf( GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    _rbo_select_depth.texParameterf( GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


    // Bind renderbuffers to framebuffer.
    _fbo.attachTexture2D( _rbo_color,  GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 );
    _fbo.attachTexture2D( _rbo_depth, GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT );

    // Bind select renderbuffer to select framebuffer
    _fbo_select.attachTexture2D( _rbo_select, GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 );
    _fbo_select.attachTexture2D( _rbo_select_depth, GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT );

    // Bind depth buffer to depthbuffer framebuffer
    _fbo_select_depth.attachTexture2D( _rbo_select_depth, GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT );


    _coord_sys_visu = new CoordSysRepVisualizer;



    // Render quad

    DVector< GL::GLVertexTex2D > data(4);
    data[0].x = 0.0f; data[0].y = 0.0f; data[0].z = 0.0f;
    data[0].s = 0.0f; data[0].t = 0.0f;

    data[1].x = 0.0f; data[1].y = 1.0f; data[1].z = 0.0f;
    data[1].s = 0.0f; data[1].t = 1.0f;

    data[2].x = 1.0f; data[2].y = 1.0f; data[2].z = 0.0f;
    data[2].s = 1.0f; data[2].t = 1.0f;

    data[3].x = 1.0f; data[3].y = 0.0f; data[3].z = 0.0f;
    data[3].s = 1.0f; data[3].t = 0.0f;

    _quad_vbo.create();
    _quad_vbo.bufferData( 4 * sizeof(GL::GLVertexTex2D),
                          data.getPtr(), GL_STATIC_DRAW );



    // Set a native render target
    _rt = new NativeRenderTarget;

    // Build an orthogonal matrix
    float near_plane = -1.0f;
    float far_plane = 1.0f;

    float l, r, b, t, n, f;
    l = 0.0f;
    r = 1.0f;
    b = 0.0f;
    t = 1.0f;
    n = near_plane;
    f = far_plane;

    float A, B, C;
    A = - ( r + l ) / ( r - l );
    B = - ( t + b ) / ( t - b );
    C = - ( f + n ) / ( f - n );

    _ortho_mat[0][0] = 2 / (r - l);
    _ortho_mat[0][1] = 0.0f;
    _ortho_mat[0][2] = 0.0f;
    _ortho_mat[0][3] = A;

    _ortho_mat[1][0] = 0.0f;
    _ortho_mat[1][1] = 2 / ( t - b );
    _ortho_mat[1][2] = 0.0f;
    _ortho_mat[1][3] = B;

    _ortho_mat[2][0] = 0.0f;
    _ortho_mat[2][1] = 0.0f;
    _ortho_mat[2][2] = - 2.0f / (f-n);
    _ortho_mat[2][3] = C;

    _ortho_mat[3][0] = 0.0f;
    _ortho_mat[3][1] = 0.0f;
    _ortho_mat[3][2] = 0.0f;
    _ortho_mat[3][3] = 1.0f;
  }

  void DisplayRenderer::resize(int w, int h) {

    _w = w;
    _h = h;

    Renderer::resize(w,h);

    _rbo_color.texImage2D( 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0x0 );
    _rbo_depth.texImage2D( 0, GL_DEPTH_COMPONENT, w, h, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0x0 );

    _rbo_select.texImage2D( 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0x0 );
    _rbo_select_depth.texImage2D( 0, GL_DEPTH_COMPONENT, w, h, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0x0 );

    _rt->resize( Vector<float,2>(_w,_h) );
  }

  void DisplayRenderer::setRenderTarget(RenderTarget *rt) {

    assert( rt );
    delete _rt;
    _rt = rt;
  }




} // END namespace GMlib
