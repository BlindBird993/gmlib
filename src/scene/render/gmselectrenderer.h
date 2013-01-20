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



/*! \file gmselectrender.h
 *  \brief Pending Documentation
 *
 *  Pending Documentation
 */

#ifndef __gmSELECTRENDERER_H__
#define __gmSELECTRENDERER_H__


#include "gmrenderer.h"

// local
#include "../camera/gmcamera.h"

// gmlib
#include <opengl/gmframebufferobject.h>
#include <opengl/gmrenderbufferobject.h>
#include <opengl/glsl/gmglprogram.h>


namespace GMlib {

  class SelectRenderer : public MultiObjectRenderer {
  public:
    SelectRenderer( Scene* scene );

    SceneObject*                findObject( int x, int y );
    Array<SceneObject*>         findObjects(int xmin, int ymin, int xmax, int ymax );

    void                        select(Array<SceneObject*>& objs, Camera* cam, int type_id );

    /* virtual from Renderer */
    void                        resize(int w, int h);

    /* virtual from MultiObjectRenderer */
    void                        prepare(Array<SceneObject*>& objs, Camera *cam);

  private:

    GL::FramebufferObject       _fbo;
    GL::RenderbufferObject      _rbo_color;
    GL::RenderbufferObject      _rbo_depth;
  };





  inline
  void SelectRenderer::select(Array<SceneObject*>& objs, Camera *cam, int type_id) {


    prepare( objs, cam );

    _fbo.clear( GL_DEPTH_BUFFER_BIT );
    _fbo.clearColorBuffer( GMcolor::Black );


    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    _fbo.bind();

    GLboolean depth_test_state;
    glGetBooleanv( GL_DEPTH_TEST, &depth_test_state );
    glEnable( GL_DEPTH_TEST );
    {

      const GL::GLProgram select_prog("select");

      select_prog.bind();

      for( int i=0; i < objs.getSize(); i++ )
        objs[i]->select( type_id, cam );

      select_prog.unbind();

    }
    if( !depth_test_state )
      glDisable( GL_DEPTH_TEST );

    _fbo.unbind();

  }


} // END namespace GMlib

#endif // __gmSELECTRENDERER_H__
