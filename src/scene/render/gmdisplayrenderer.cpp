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

//stl
#include <cassert>



namespace GMlib {




  DisplayRenderer::DisplayRenderer(Scene *scene) : MultiObjectRenderer(scene), _fbo("DefaultRenderBufferObject"), _fbo_select("DefaultRenderSelectBufferObject"), _rbo_color(GL_TEXTURE_2D), _rbo_select(GL_TEXTURE_2D), _rbo_depth() {


    // Color rbo texture parameters
    _rbo_color.setParameteri( GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    _rbo_color.setParameteri( GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    _rbo_color.setParameterf( GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    _rbo_color.setParameterf( GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Select rbo texture parameters
    _rbo_select.setParameteri( GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    _rbo_select.setParameteri( GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    _rbo_select.setParameterf( GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    _rbo_select.setParameterf( GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


    // Bind renderbuffers to framebuffer.
    _fbo.attachRenderbuffer( _rbo_depth, GL_DEPTH_ATTACHMENT );
    _fbo.attachTexture2D( _rbo_color,  GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 );

    // Bind select renderbuffer to select framebuffer
    _fbo_select.attachRenderbuffer( _rbo_select_depth, GL_DEPTH_ATTACHMENT );
    _fbo_select.attachTexture2D( _rbo_select, GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 );

    // Bind depth buffer ot depthbuffer framebuffer
    _fbo_select_depth.attachRenderbuffer( _rbo_select_depth, GL_DEPTH_ATTACHMENT );

  }

  void DisplayRenderer::resize(int w, int h) {

    Renderer::resize(w,h);

    _rbo_depth.createStorage( GL_DEPTH_COMPONENT32, w, h );
    _rbo_color.texImage2D( 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0x0 );

    _rbo_select_depth.createStorage( GL_DEPTH_COMPONENT32, w, h );
    _rbo_select.texImage2D( 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0x0 );
  }




} // END namespace GMlib
