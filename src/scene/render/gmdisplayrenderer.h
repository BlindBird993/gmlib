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
#include "../window/gmviewset.h"
#include "../window/gmwindow.h"
#include "gmrendertarget.h"

// gmlib
#include <opengl/gmframebufferobject.h>
#include <opengl/gmrenderbufferobject.h>
#include <opengl/gmtexture.h>
#include <opengl/bufferobjects/gmvertexbufferobject.h>


namespace GMlib {


  class DisplayRenderer : public MultiObjectRenderer {
  public:
    DisplayRenderer( Scene* scene );

    const GL::Texture&      getRenderTexture() const;
    const GL::Texture&      getSelectTexture() const;

    virtual void            render(Array<DisplayObject*>& objs, const Array<Camera*>& cameras ) const;

    void                    render( GMWindow *window );
    void                    renderToTarget( GMWindow *window );

    void                    setRenderTarget( RenderTarget* rt );

    /* virtual from Renderer */
    void                    resize(int w, int h);




  private:
    /* Object rendering */
    GL::FramebufferObject   _fbo;
    GL::Texture             _rbo_color;
    GL::RenderbufferObject  _rbo_depth;

    /* Selection rendering */
    GL::FramebufferObject   _fbo_select;
    GL::Texture             _rbo_select;

    GL::FramebufferObject   _fbo_select_depth;
    GL::RenderbufferObject  _rbo_select_depth;

    int                     _w, _h;

    GLuint                    _vbo_quad;
    GLuint                    _vbo_quad_tex;

    void                    render(const DisplayObject *obj, const Camera *cam) const;
    void                    renderGeometry(const DisplayObject *obj, const Camera *cam) const;
    void                    renderCoordSys(const Camera *cam ) const;
//    void                    renderGeometry(const DisplayObject *obj, const Camera *cam) const;



    CoordSysRepVisualizer   *_coord_sys_visu;
    RenderTarget            *_rt;

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
  void DisplayRenderer::renderGeometry( const DisplayObject* obj, const Camera* cam ) const {

    if( obj != cam && obj->isSelected()  ) {

      const GL::GLProgram prog("render_select");
      prog.bind(); {

        prog.setUniform( "u_color", Color( obj->getVirtualName()) );

        if(obj->isCollapsed()) {

          VisualizerStdRep::getInstance()->renderGeometry(prog,obj,cam);
        }
        else {

          const Array<Visualizer*>& visus = obj->getVisualizers();
          for( int i = 0; i < visus.getSize(); ++i )
            visus(i)->renderGeometry(prog,obj,cam);

          obj->localSelect(cam);
        }

      } prog.unbind();
    }
  }

  inline
  void DisplayRenderer::renderCoordSys(const Camera *cam) const {

    _coord_sys_visu->render(cam,cam);
  }

  inline
  void DisplayRenderer::render( GMWindow *window ) {


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

    HqMatrix<float,3> ortho_mat;

    ortho_mat[0][0] = 2 / (r - l);
    ortho_mat[0][1] = 0.0f;
    ortho_mat[0][2] = 0.0f;
    ortho_mat[0][3] = A;

    ortho_mat[1][0] = 0.0f;
    ortho_mat[1][1] = 2 / ( t - b );
    ortho_mat[1][2] = 0.0f;
    ortho_mat[1][3] = B;

    ortho_mat[2][0] = 0.0f;
    ortho_mat[2][1] = 0.0f;
    ortho_mat[2][2] = - 2.0f / (f-n);
    ortho_mat[2][3] = C;

    ortho_mat[3][0] = 0.0f;
    ortho_mat[3][1] = 0.0f;
    ortho_mat[3][2] = 0.0f;
    ortho_mat[3][3] = 1.0f;






    glViewport( 0, 0, _w, _h );







    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glDisable(GL_DEPTH_TEST);








    GL::GLProgram prog( "render" );

    prog.bind();

    prog.setUniform( "u_mvpmat", ortho_mat );
    prog.setUniform( "u_tex", getRenderTexture(), (GLenum)GL_TEXTURE0, 0 );
    prog.setUniform( "u_tex_selected", getSelectTexture(), (GLenum)GL_TEXTURE1, 1 );
    prog.setUniform( "u_buf_w", float(_w) );
    prog.setUniform( "u_buf_h", float(_h) );
//    prog.setUniform( "u_select_color", _select_color );
    prog.setUniform( "u_select_color", GMlib::GMcolor::Beige );

    GL::AttributeLocation vert_loc = prog.getAttributeLocation( "in_vertex" );
    GL::AttributeLocation tex_coord_loc = prog.getAttributeLocation( "in_tex_coord" );

    glBindBuffer( GL_ARRAY_BUFFER, _vbo_quad );
    glVertexAttribPointer( vert_loc(), 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0x0 );
    glEnableVertexAttribArray( vert_loc() );

    glBindBuffer( GL_ARRAY_BUFFER, _vbo_quad_tex );
    glVertexAttribPointer( tex_coord_loc(), 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0x0 );
    glEnableVertexAttribArray( tex_coord_loc() );

    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );

    glDrawArrays( GL_QUADS, 0, 4 );

    glDisableVertexAttribArray( tex_coord_loc() );
    glDisableVertexAttribArray( vert_loc() );

    prog.unbind();

    {
      const ViewSet &top_view_set = window->getTopViewSet();
      GL::GLProgram color_prog( "color" );
      color_prog.bind();

      color_prog.setUniform( "u_mvpmat", ortho_mat );
      color_prog.setUniform( "u_selected", false );
      color_prog.setUniform( "u_color", top_view_set.getBorderColor() );

      GL::AttributeLocation vert_loc = color_prog.getAttributeLocation( "in_vertex" );
      top_view_set.getBorderVBO().bind();
      glVertexAttribPointer( vert_loc(), 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0x0 );
      glEnableVertexAttribArray( vert_loc() );
      glPointSize( 10.0f );
      glDrawArrays( GL_QUADS, 0, top_view_set.getNoBorders() * 4 );

      glDisableVertexAttribArray( vert_loc() );

      top_view_set.getBorderVBO().unbind();

      color_prog.unbind();
    }

    glEnable(GL_DEPTH_TEST);
  }

  inline
  void DisplayRenderer::renderToTarget(GMWindow* window) {

    _rt->bind();
    render( window );
    _rt->unbind();
  }

  inline
  void DisplayRenderer::render(Array<DisplayObject*>& objs, const Array<Camera *> &cameras) const {

    // Clear render buffers
    _fbo.clear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    _fbo_select.clearColorBuffer( GMcolor::Black );
    _fbo_select_depth.clear( GL_DEPTH_BUFFER_BIT );

    // Render
    for( int i = 0; i < cameras.getSize(); ++i ) {

      Camera *cam = cameras(i);
      cam->markAsActive();

      prepare( objs, cam );

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

        ::glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

        for( int j = 0; j < objs.getSize(); ++j )
          renderGeometry( objs[j], cam);

      } _fbo_select_depth.unbind();

      // Selection rendering - render
      _fbo_select.bind(); {

        GLint depth_mask, depth_func;
        ::glGetIntegerv( GL_DEPTH_WRITEMASK, &depth_mask );
        ::glGetIntegerv( GL_DEPTH_FUNC, &depth_func);

        ::glDepthFunc( GL_LEQUAL );
        ::glDepthMask( GL_TRUE );

        ::glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

        for( int j = 0; j < objs.getSize(); ++j )
          renderGeometry( objs[j], cam );

        ::glDepthFunc( depth_func );
        ::glDepthMask( depth_mask );

      } _fbo_select.unbind();

      cam->markAsInactive();
    }
  }



} // END namespace GMlib

#endif // __gmDISPLAYRENDERER_H__
