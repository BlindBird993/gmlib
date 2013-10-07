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
    : MultiObjectRenderer(scene),
      _fbo("DefaultRenderBufferObject"), _rbo_color("rbo_color",GL_TEXTURE_2D), _rbo_depth(),
      _fbo_select("DefaultRenderSelectBufferObject"), _rbo_select(GL_TEXTURE_2D),
      _w(0), _h(0)
  {









    // Color rbo texture parameters
    _rbo_color.texParameteri( GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    _rbo_color.texParameteri( GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    _rbo_color.texParameterf( GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    _rbo_color.texParameterf( GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Select rbo texture parameters
    _rbo_select.texParameteri( GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    _rbo_select.texParameteri( GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    _rbo_select.texParameterf( GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    _rbo_select.texParameterf( GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


    // Bind renderbuffers to framebuffer.
    _fbo.attachRenderbuffer( _rbo_depth, GL_DEPTH_ATTACHMENT );
    _fbo.attachTexture2D( _rbo_color,  GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 );

    // Bind select renderbuffer to select framebuffer
    _fbo_select.attachRenderbuffer( _rbo_select_depth, GL_DEPTH_ATTACHMENT );
    _fbo_select.attachTexture2D( _rbo_select, GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 );

    // Bind depth buffer to depthbuffer framebuffer
    _fbo_select_depth.attachRenderbuffer( _rbo_select_depth, GL_DEPTH_ATTACHMENT );


    _coord_sys_visu = new CoordSysRepVisualizer;




    DVector< GL::GLVertexTex2D > data(4);
    data[0].x = 0.0f; data[0].y = 0.0f; data[0].z = 0.0f;
    data[0].s = 0.0f; data[0].t = 0.0f;

    data[1].x = 0.0f; data[1].y = 1.0f; data[1].z = 0.0f;
    data[1].s = 0.0f; data[1].t = 1.0f;

    data[2].x = 1.0f; data[2].y = 1.0f; data[2].z = 0.0f;
    data[2].s = 1.0f; data[2].t = 1.0f;

    data[3].x = 1.0f; data[3].y = 0.0f; data[3].z = 0.0f;
    data[3].s = 1.0f; data[3].t = 0.0f;

    _quad_vbo.bufferData( 4 * sizeof(GL::GLVertexTex2D),
                          data.getPtr(), GL_STATIC_DRAW );





//    glGenBuffers( 1, &_vbo_quad );
//    glGenBuffers( 1, &_vbo_quad_tex );

//    // Gen quad data (vertex)
//    glBindBuffer( GL_ARRAY_BUFFER, _vbo_quad );

//    DVector< Point<float,3> > data(4);
////    data[0] = Point<float,3>( 0.25f, 0.25f, 0.0f );
////    data[1] = Point<float,3>( 0.25f, 0.75f, 0.0f );
////    data[2] = Point<float,3>( 0.75f, 0.75f, 0.0f );
////    data[3] = Point<float,3>( 0.75f, 0.25f, 0.0f );
//    data[0] = Point<float,3>( 0.0f, 0.0f, 0.0f );
//    data[1] = Point<float,3>( 0.0f, 1.0f, 0.0f );
//    data[2] = Point<float,3>( 1.0f, 1.0f, 0.0f );
//    data[3] = Point<float,3>( 1.0f, 0.0f, 0.0f );

//    glBufferData( GL_ARRAY_BUFFER, 4 * 3 * sizeof(float), data.getPtr(), GL_STATIC_DRAW );
//    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );

//    // Gen quad data (tex)
//    glBindBuffer( GL_ARRAY_BUFFER, _vbo_quad_tex );

//    DVector< Point<float,2> > data_tex(4);
//    data_tex[0] = Point<float,2>( 0.0f, 0.0f );
//    data_tex[1] = Point<float,2>( 0.0f, 1.0f );
//    data_tex[2] = Point<float,2>( 1.0f, 1.0f );
//    data_tex[3] = Point<float,2>( 1.0f, 0.0f );
//  //  data_tex[0] = Point<float,2>( 0.25f, 0.25f );
//  //  data_tex[1] = Point<float,2>( 0.25f, 0.75f );
//  //  data_tex[2] = Point<float,2>( 0.75f, 0.75f );
//  //  data_tex[3] = Point<float,2>( 0.75f, 0.25f );

//    glBufferData( GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), data_tex.getPtr(), GL_STATIC_DRAW );
//    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );

    _rt = new NativeRenderTarget;
  }

  void DisplayRenderer::resize(int w, int h) {

    _w = w;
    _h = h;

    Renderer::resize(w,h);

    _rbo_depth.renderbufferStorage( GL_DEPTH_COMPONENT32, w, h );
    _rbo_color.texImage2D( 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0x0 );

    _rbo_select_depth.renderbufferStorage( GL_DEPTH_COMPONENT32, w, h );
    _rbo_select.texImage2D( 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0x0 );

    _rt->resize( Vector<float,2>(_w,_h) );
  }

  void DisplayRenderer::setRenderTarget(RenderTarget *rt) {

    assert( rt );
    delete _rt;
    _rt = rt;
  }




} // END namespace GMlib
