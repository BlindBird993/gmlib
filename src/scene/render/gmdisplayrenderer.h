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



/*! \file gmdisplayrender.h
 *  \brief Pending Documentation
 *
 *  Pending Documentation
 */

#ifndef __gmDISPLAYRENDERER_H__
#define __gmDISPLAYRENDERER_H__


#include "gmrenderer.h"

// local
#include "../camera/gmcamera.h"

// gmlib
#include <opengl/gmframebufferobject.h>
#include <opengl/gmrenderbufferobject.h>
#include <opengl/gmtexture.h>


namespace GMlib {


  class DisplayRenderer : public MultiObjectRenderer {
  public:
    DisplayRenderer( Scene* scene );

    void      render(Array<SceneObject*>& objs, const Array<Camera*>& cameras );

    /* virtual from Renderer */
    void      resize(int w, int h);


//  private:

    /* Rendering */
    GL::FramebufferObject   _fbo;
    GL::Texture             _rbo_color;
    GL::RenderbufferObject  _rbo_depth;

    /* Selection rendering */
    GL::FramebufferObject   _fbo_select;
    GL::Texture             _rbo_select;

    GL::FramebufferObject   _fbo_select_depth;
    GL::RenderbufferObject  _rbo_select_depth;


  }; // END class DisplayRenderer






  inline
  void DisplayRenderer::render(Array<SceneObject*>& objs, const Array<Camera *> &cameras) {

    // Clear render buffers
    _fbo.clear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    _fbo_select.clearColorBuffer( GMcolor::Black );
    _fbo_select_depth.clear( GL_DEPTH_BUFFER_BIT );





    // Object rendering

    _fbo.bind();

    for( int i = 0; i < cameras.getSize(); ++i ) {


      Camera *cam = cameras(i);
      cam->markAsActive();

      prepare( objs, cam );

      for( int i = 0; i < objs.getSize(); i++ )
        objs[i]->display( cam );

      cam->markAsInactive();
    }
    _fbo.unbind();




    // Selection rendering - render to depth buffer


    _fbo_select_depth.bind();


    for( int i = 0; i < cameras.getSize(); ++i ) {


      Camera *cam = cameras(i);
      cam->markAsActive();

      prepare( objs, cam );


      glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
      for( int i = 0; i < objs.getSize(); ++i )
        objs[i]->displayDepth( cam );

      cam->markAsInactive();
    }
    _fbo_select_depth.unbind();


    // Selection rendering - render

    GLint depth_mask, depth_func;

    ::glGetIntegerv( GL_DEPTH_WRITEMASK, &depth_mask );
    ::glGetIntegerv( GL_DEPTH_FUNC, &depth_func);

    ::glDepthFunc( GL_LEQUAL );
    ::glDepthMask( GL_FALSE );

    _fbo_select.bind();

    for( int i = 0; i < cameras.getSize(); ++i ) {


      Camera *cam = cameras(i);
      cam->markAsActive();

      prepare( objs, cam );


      glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
      for( int i = 0; i < objs.getSize(); ++i )
        objs[i]->displaySelection( cam );

      cam->markAsInactive();
    }
      _fbo_select.unbind();

    ::glDepthFunc( depth_func );
    ::glDepthMask( depth_mask );
  }



} // END namespace GMlib

#endif // __gmDISPLAYRENDERER_H__
