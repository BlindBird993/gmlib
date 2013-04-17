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
#include "../visualizers/gmvisualizerstdrep.h"

// gmlib
#include <opengl/gmframebufferobject.h>
#include <opengl/gmrenderbufferobject.h>
#include <opengl/glsl/gmglprogram.h>


namespace GMlib {

  class SelectRenderer : public MultiObjectRenderer {
  public:
    SelectRenderer( Scene* scene );

    DisplayObject*              findObject( int x, int y ) const;
    Array<DisplayObject*>       findObjects(int xmin, int ymin, int xmax, int ymax ) const;

    void                        select(Array<DisplayObject*>& objs, Camera* cam, int type_id ) const;

    /* virtual from Renderer */
    void                        resize(int w, int h);

    /* virtual from MultiObjectRenderer */
    void                        prepare(Array<DisplayObject*>& objs, Camera *cam) const;

  protected:
    void                        select(DisplayObject* obj, Camera* cam, int what) const;

  private:

    GL::FramebufferObject       _fbo;
    GL::RenderbufferObject      _rbo_color;
    GL::RenderbufferObject      _rbo_depth;
  };








  inline
  void SelectRenderer::select( DisplayObject* obj, Camera* cam, int what ) const {

    if( obj != cam && ( what == 0 || what == obj->getTypeId() || ( what < 0 && what + obj->getTypeId() != 0 ) ) ) {

      const GL::GLProgram &select_prog = obj->getSelectProgram();
      select_prog.setUniform( "u_mvpmat", obj->getModelViewProjectionMatrix(cam), 1, true );
      select_prog.setUniform( "u_color", Color(obj->getVirtualName()) );

      if( obj->isCollapsed() ) {

        VisualizerStdRep *std_rep_visu = VisualizerStdRep::getInstance();
        std_rep_visu->set(obj);
        std_rep_visu->select();
      }
      else {

        const Array<Visualizer*>& visus = obj->getVisualizers();
        for( int i = 0; i < visus.getSize(); ++i )
          visus(i)->select();

        obj->localSelect();
      }
    }
  }


  inline
  void SelectRenderer::select(Array<DisplayObject*>& objs, Camera *cam, int type_id) const {

    // Clear buffers
    _fbo.clear( GL_DEPTH_BUFFER_BIT );
    _fbo.clearColorBuffer( GMcolor::Black );

    // Prepare camera
    prepare( objs, cam );


    // Render selection
    GLboolean depth_test_state;
    glGetBooleanv( GL_DEPTH_TEST, &depth_test_state );
    glEnable( GL_DEPTH_TEST );

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    _fbo.bind(); {

      const GL::GLProgram select_prog("select");

      select_prog.bind();

      for( int i=0; i < objs.getSize(); ++i )
        select( objs[i], cam, type_id );

      select_prog.unbind();

    }  _fbo.unbind();

    if( !depth_test_state )
      glDisable( GL_DEPTH_TEST );

  }


} // END namespace GMlib

#endif // __gmSELECTRENDERER_H__
