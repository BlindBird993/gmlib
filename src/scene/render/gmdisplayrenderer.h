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
#include "../visualizers/gmstdrepvisualizer.h"
#include "../visualizers/gmcoordsysrepvisualizer.h"
//#include "../window/gmviewset.h"
//#include "../window/gmwindow.h"
#include "gmrendertarget.h"

// gmlib
#include <opengl/gmframebufferobject.h>
#include <opengl/gmrenderbufferobject.h>
#include <opengl/gmtexture.h>
#include <opengl/bufferobjects/gmvertexbufferobject.h>


namespace GMlib {


  class DisplayRenderer : public Renderer {
  public:
    explicit DisplayRenderer();
    ~DisplayRenderer();

    const GL::Texture&      getRenderTexture() const;
    const GL::Texture&      getSelectTexture() const;

    /* virtual from Renderer */
    void                    reshape(int x,int y, int w, int h);




  private:
    /* Object rendering */
    GL::Program             _render_prog;
    GL::FramebufferObject   _fbo;
    GL::Texture             _rbo_color;
    GL::Texture             _rbo_depth;

    /* Selection rendering */
    GL::Program             _render_select_prog;
    GL::FramebufferObject   _fbo_select;
    GL::Texture             _rbo_select;

    GL::FramebufferObject   _fbo_select_depth;
    GL::Texture             _rbo_select_depth;

    /* other suff */
    HqMatrix<float,3>       _ortho_mat;
    int                     _x, _y;
    int                     _w, _h;

    GL::VertexBufferObject  _quad_vbo;

    void                    render(const DisplayObject *obj, const Camera *cam) const;
    void                    renderSelectedGeometry(const DisplayObject *obj, const Camera *cam) const;
    void                    renderCoordSys(const Camera *cam ) const;


    CoordSysRepVisualizer   *_coord_sys_visu;

    void                    initRenderProgram();
    void                    initRenderSelectProgram();


    /* virtual from Renderer */
    void                    renderObjects(Array<DisplayObject*>& objs, Camera* cam);
    void                    renderToTarget();


  }; // END class DisplayRenderer










  inline
  const GL::Texture& DisplayRenderer::getRenderTexture() const {

    return _rbo_color;
  }

  inline
  const GL::Texture& DisplayRenderer::getSelectTexture() const {

    return _rbo_select;
  }

  inline
  void DisplayRenderer::render( const DisplayObject* obj, const Camera* cam ) const {

    if( obj != cam ) {

      if(obj->isCollapsed()) {

        VisualizerStdRep::getInstance()->render(obj,cam);
      }
      else {

        const Array<Visualizer*>& visus = obj->getVisualizers();
        for( int i = 0; i < visus.getSize(); ++i ) {

          visus(i)->render(obj,cam);
        }

        obj->localDisplay(cam);
      }
    }
  }

  inline
  void DisplayRenderer::renderSelectedGeometry( const DisplayObject* obj, const Camera* cam ) const {

    if( obj != cam && obj->isSelected()  ) {

      _render_select_prog.bind(); {

        _render_select_prog.setUniform( "u_color", Color( obj->getVirtualName()) );

        if(obj->isCollapsed()) {

          VisualizerStdRep::getInstance()->renderGeometry(_render_select_prog,obj,cam);
        }
        else {

          const Array<Visualizer*>& visus = obj->getVisualizers();
          for( int i = 0; i < visus.getSize(); ++i )
            visus(i)->renderGeometry(_render_select_prog,obj,cam);

          obj->localSelect(_render_select_prog,cam);
        }

      } _render_select_prog.unbind();
    }
  }

  inline
  void DisplayRenderer::renderCoordSys(const Camera *cam) const {

    _coord_sys_visu->render(cam,cam);
  }



  inline
  void DisplayRenderer::renderToTarget() {


//    GL_CHECK(::glViewport( _x, _y, _w, _h ));

    GL_CHECK(::glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ));
    GL_CHECK(::glDisable(GL_DEPTH_TEST));


    // Draw scene composition
    {
      _render_prog.bind();

      _render_prog.setUniform( "u_mvpmat", _ortho_mat );
      _render_prog.setUniform( "u_tex", getRenderTexture(), (GLenum)GL_TEXTURE0, 0 );
      _render_prog.setUniform( "u_tex_selected", getSelectTexture(), (GLenum)GL_TEXTURE1, 1 );
      _render_prog.setUniform( "u_buf_w", float(_w) );
      _render_prog.setUniform( "u_buf_h", float(_h) );
  //    _render_prog.setUniform( "u_select_color", _select_color );
      _render_prog.setUniform( "u_select_color", GMlib::GMcolor::Beige );

      GL::AttributeLocation vert_loc = _render_prog.getAttributeLocation( "in_vertex" );
      GL::AttributeLocation tex_coord_loc = _render_prog.getAttributeLocation( "in_tex_coord" );

      _quad_vbo.bind();

      _quad_vbo.enable( vert_loc,      3, GL_FLOAT, GL_FALSE, sizeof(GL::GLVertexTex2D), reinterpret_cast<const GLvoid*>(0x0) );
      _quad_vbo.enable( tex_coord_loc, 2, GL_FLOAT, GL_FALSE, sizeof(GL::GLVertexTex2D), reinterpret_cast<const GLvoid*>(3*sizeof(GLfloat)) );

      GL_CHECK(::glDrawArrays( GL_QUADS, 0, 4 ));

      _quad_vbo.disable(tex_coord_loc);
      _quad_vbo.disable(vert_loc);

      _quad_vbo.unbind();


      _render_prog.unbind();
    }

    GL_CHECK(::glEnable(GL_DEPTH_TEST));
  }

  inline
  void DisplayRenderer::renderObjects(Array<DisplayObject*>& objs, Camera* cam) {

    // Clear render buffers
    _fbo.clearColorBuffer( getClearColor() );
    _fbo.clear( GL_DEPTH_BUFFER_BIT );

    _fbo_select.clearColorBuffer( GMcolor::Black );
    _fbo_select_depth.clear( GL_DEPTH_BUFFER_BIT );


//      cam->updateLightUBO( window );


    // Object rendering
    _fbo.bind(); {

      // Render coordinate-system visualization
      renderCoordSys( cam );

      // Render the scene objects
      for( int j = 0; j < objs.getSize(); ++j )
        render( objs[j], cam);

    } _fbo.unbind();

    // Selection rendering - render to depth buffer
    _fbo_select_depth.bind(); {

      GL_CHECK(::glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ));

      for( int j = 0; j < objs.getSize(); ++j )
        renderSelectedGeometry( objs[j], cam);

    } _fbo_select_depth.unbind();

    // Selection rendering - render
    _fbo_select.bind(); {

      GLint depth_mask, depth_func;
      GL_CHECK(::glGetIntegerv( GL_DEPTH_WRITEMASK, &depth_mask ));
      GL_CHECK(::glGetIntegerv( GL_DEPTH_FUNC, &depth_func));

      GL_CHECK(::glDepthFunc( GL_LEQUAL ));
      GL_CHECK(::glDepthMask( GL_TRUE ));

      GL_CHECK(::glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ));

      for( int j = 0; j < objs.getSize(); ++j )
        renderSelectedGeometry( objs[j], cam );

      GL_CHECK(::glDepthFunc( depth_func ));
      GL_CHECK(::glDepthMask( depth_mask ));

    } _fbo_select.unbind();

  }



} // END namespace GMlib

#endif // __gmDISPLAYRENDERER_H__
