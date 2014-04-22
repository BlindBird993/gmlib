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
#include "../visualizers/gmstdrepvisualizer.h"

// gmlib
#include <opengl/gmframebufferobject.h>
#include <opengl/gmtexture.h>
#include <opengl/gmprogram.h>


namespace GMlib {

  class SelectRenderer : public MultiObjectRenderer {
  public:
    SelectRenderer( Scene* scene );

    DisplayObject*              findObject( int x, int y ) const;
    Array<DisplayObject*>       findObjects(int xmin, int ymin, int xmax, int ymax ) const;

    void                        select(Array<DisplayObject*>& objs, const Camera* cam, int type_id ) const;

    /* virtual from Renderer */
    void                        resize(int w, int h);

    /* virtual from MultiObjectRenderer */
    void                        prepare(Array<DisplayObject*>& objs, const Camera* cam) const;

  protected:
    void                        select(DisplayObject* obj, const Camera* cam, int what) const;

  private:
    GL::Program                 _prog;

    GL::FramebufferObject       _fbo;
    GL::Texture                 _rbo_color;
    GL::Texture                 _rbo_depth;


    void                        initSelectProgram();
  };








  inline
  void SelectRenderer::select( DisplayObject* obj, const Camera* cam, int what ) const {

    if( obj != cam && ( what == 0 || what == obj->getTypeId() || ( what < 0 && what + obj->getTypeId() != 0 ) ) ) {

      _prog.bind(); {

        _prog.setUniform( "u_color", Color( obj->getVirtualName()) );

        if(obj->isCollapsed()) {

          VisualizerStdRep::getInstance()->renderGeometry(_prog,obj,cam);
        }
        else {

          const Array<Visualizer*>& visus = obj->getVisualizers();
          for( int i = 0; i < visus.getSize(); ++i )
            visus(i)->renderGeometry(_prog,obj,cam);

          obj->localSelect(_prog,cam);
        }

      } _prog.unbind();
    }
  }


  inline
  void SelectRenderer::select(Array<DisplayObject*>& objs, const Camera *cam, int type_id) const {

    // Clear buffers
    _fbo.clear( GL_DEPTH_BUFFER_BIT );
    _fbo.clearColorBuffer( GMcolor::Black );

    // Prepare camera
    prepare( objs, cam );


    // Render selection
    GLboolean depth_test_state;
    GL_CHECK(::glGetBooleanv( GL_DEPTH_TEST, &depth_test_state ));
    GL_CHECK(::glEnable( GL_DEPTH_TEST ));

    GL_CHECK(::glPolygonMode(GL_FRONT_AND_BACK,GL_FILL));

    _fbo.bind(); {

      for( int i=0; i < objs.getSize(); ++i )
        select( objs[i], cam, type_id );

    }  _fbo.unbind();

    if( !depth_test_state )
      GL_CHECK(::glDisable( GL_DEPTH_TEST ));
  }


} // END namespace GMlib

#endif // __gmSELECTRENDERER_H__
