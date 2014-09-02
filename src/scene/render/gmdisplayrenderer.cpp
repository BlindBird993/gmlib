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

// gmlib
#include <opengl/shaders/gmvertexshader.h>
#include <opengl/shaders/gmfragmentshader.h>

//stl
#include <cassert>



namespace GMlib {




  DisplayRenderer::DisplayRenderer() : _w(0), _h(0) {

    setClearColor( GMcolor::Grey );

    // Acquire programs
    initRenderProgram();
    initRenderSelectProgram();


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

  DisplayRenderer::~DisplayRenderer() {

    delete _coord_sys_visu;
  }

  void DisplayRenderer::render()  {

    Scene *scene = getCamera()->getScene();
    assert(scene);

    // Update lights
    getCamera()->updateLightUBO(scene);
    getCamera()->updateCameraOrientation();

    // Prepare
    prepare(getCamera());

    // Render scene
    renderScene(getCamera());

    // Set render to target
    RenderTarget *rt = getRenderTarget();
    rt->clear();
    rt->bind();
    renderToTarget();
    rt->unbind();
  }


  void DisplayRenderer::initRenderProgram() {


    const std::string prog_name    = "render_prog";
    if( _render_prog.acquire(prog_name) ) return;


    std::string vs_src(
          "#version 150 core\n"
          "\n"
          "uniform mat4 u_mvpmat;\n"
          "\n"
          "in vec4 in_vertex;\n"
          "in vec2 in_tex_coord;\n"
          "\n"
          "out vec2 ex_tex_coord;\n"
          "out vec4 gl_Position;\n"
          "\n"
          "void main() {\n"
          "\n"
          "  ex_tex_coord = in_tex_coord;\n"
          "  gl_Position = u_mvpmat * in_vertex;\n"
          "}\n"
          );

    std::string fs_src(
          "#version 150 core\n"
          "\n"
          "uniform sampler2D u_tex;\n"
          "uniform sampler2D u_tex_selected;\n"
          "uniform float u_buf_w;\n"
          "uniform float u_buf_h;\n"
          "uniform vec4 u_select_color;\n"
          "\n"
          "in vec2 ex_tex_coord;\n"
          "\n"
          "out vec4 gl_FragColor;\n"
          "\n"
          "float avg( vec4 v ) {\n"
          "\n"
          "  return ( v.r + v.g + v. b ) / 4.0;\n"
          "}\n"
          "\n"
          "\n"
          "float runFilter( mat3 mask, float w, float h ) {\n"
          "\n"
          "  float result = 0; //vec4( 0.0, 0.0, 0.0, 0.0 );\n"
          "\n"
          "  for( float i = -1.0; i <= 1.0; i = i + 1.0 ) {\n"
          "    for( float j = -1.0; j <= 1.0; j = j + 1.0 ) {\n"
          "\n"
          "      float x = ex_tex_coord.x + ( (i + 0.5) / w );\n"
          "      float y = ex_tex_coord.y + ( (j + 0.5) / h );\n"
          "\n"
          "      float sub_res = avg( texture2D( u_tex_selected, vec2( x, y ) ) );\n"
          "\n"
          "      result += sub_res * avg(\n"
          "        vec4(\n"
          "          mask[int(i+1.0)][int(j+1.0)],\n"
          "          mask[int(i+1.0)][int(j+1.0)],\n"
          "          mask[int(i+1.0)][int(j+1.0)],\n"
          "          mask[int(i+1.0)][int(j+1.0)]\n"
          "        )\n"
          "        );\n"
          "    }\n"
          "  }\n"
          "\n"
          "  return result;\n"
          "}\n"
          "\n"
          "void main() {\n"
          "\n"
          "  // x and y sobel filters\n"
          "  mat3 mask_x = mat3(\n"
          "    -1.0, 0.0, 1.0,\n"
          "    -2.0, 0.0, 2.0,\n"
          "    -1.0, 0.0, 1.0\n"
          "    );\n"
          "\n"
          "  mat3 mask_y =  mat3(\n"
          "     1.0,  2.0,  1.0,\n"
          "     0.0,  0.0,  0.0,\n"
          "    -1.0, -2.0, -1.0\n"
          "    );\n"
          "\n"
          "  // summation vars.\n"
          "  float res_x = runFilter( mask_x, u_buf_w, u_buf_h );\n"
          "  float res_y = runFilter( mask_y, u_buf_w, u_buf_h );\n"
          "  float res = sqrt( res_x * res_x + res_y * res_y );\n"
          "\n"
          "  gl_FragColor = texture( u_tex, ex_tex_coord );\n"
          "\n"
          "  if( res > 0.0 )\n"
          "   gl_FragColor = u_select_color;\n"
          "}\n"
          );

    bool compile_ok, link_ok;

    GL::VertexShader vshader;
    vshader.create("render_vs");
    vshader.setPersistent(true);
    vshader.setSource(vs_src);
    compile_ok = vshader.compile();
    assert(compile_ok);

    GL::FragmentShader fshader;
    fshader.create("render_fs");
    fshader.setPersistent(true);
    fshader.setSource(fs_src);
    compile_ok = fshader.compile();
    assert(compile_ok);

    _render_prog.create(prog_name);
    _render_prog.setPersistent(true);
    _render_prog.attachShader(vshader);
    _render_prog.attachShader(fshader);
    link_ok = _render_prog.link();
    assert(link_ok);
  }

  void DisplayRenderer::initRenderSelectProgram() {

    const std::string prog_name    = "render_select_prog";
    if( _render_select_prog.acquire(prog_name) ) return;


    std::string vs_src(
          "#version 150 compatibility \n"
          "uniform mat4 u_mvpmat; \n"
          "uniform vec4 u_color; \n"
          "\n"
          "in vec4 in_vertex; \n"
          "\n"
          "out vec4 gl_Position; \n"
          "\n"
          "void main() \n"
          "{ \n"
          "  gl_Position = u_mvpmat * in_vertex; \n"
          "}\n"
          );

    std::string fs_src(
          "#version 150 compatibility \n"
          "\n"
          "out vec4 gl_FragColor; \n"
          "\n"
          "void main() \n"
          "{ \n"
          "  gl_FragColor = vec4( 1.0, 1.0, 1.0, 1.0 ); \n"
          "} \n"
          );

    bool compile_ok, link_ok;

    GL::VertexShader vshader;
    vshader.create("render_select_vs");
    vshader.setPersistent(true);
    vshader.setSource(vs_src);
    compile_ok = vshader.compile();
    assert(compile_ok);

    GL::FragmentShader fshader;
    fshader.create("render_select_fs");
    fshader.setPersistent(true);
    fshader.setSource(fs_src);
    compile_ok = fshader.compile();
    assert(compile_ok);

    _render_select_prog.create(prog_name);
    _render_select_prog.setPersistent(true);
    _render_select_prog.attachShader(vshader);
    _render_select_prog.attachShader(fshader);
    link_ok = _render_select_prog.link();
    assert(link_ok);

  }

//  void DisplayRenderer::reshape(int x, int y, int w, int h) {

//    Renderer::setViewport(x,y,w,h);

//    _x = x;
//    _y = y;
//    _w = w;
//    _h = h;

//    _rbo_color.texImage2D( 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0x0 );
//    _rbo_depth.texImage2D( 0, GL_DEPTH_COMPONENT, w, h, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0x0 );

//    _rbo_select.texImage2D( 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0x0 );
//    _rbo_select_depth.texImage2D( 0, GL_DEPTH_COMPONENT, w, h, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0x0 );
//  }


  void DisplayRenderer::prepare(Camera *cam) {

    Scene *scene = cam->getScene();
    assert(scene);

    // Compute frustum/frustum-matrix, set glViewport
    cam->setupDisplay();

    // Get displayable objects
    _objs.resetSize();
    scene->getDisplayableObjects( _objs, cam );
  }


  const GL::Texture& DisplayRenderer::getRenderTexture() const {

    return _rbo_color;
  }

  const GL::Texture& DisplayRenderer::getSelectTexture() const {

    return _rbo_select;
  }

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

  void DisplayRenderer::renderCoordSys(const Camera *cam) const {

    _coord_sys_visu->render(cam,cam);
  }



  void DisplayRenderer::renderToTarget() {



    GL_CHECK(::glViewport(getViewportX(), getViewportY(), getViewportW(), getViewportH()));

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

  void DisplayRenderer::reshape() {

      _rbo_color.texImage2D( 0, GL_RGBA8, getViewportW(), getViewportH(), 0, GL_RGBA, GL_UNSIGNED_BYTE, 0x0 );
      _rbo_depth.texImage2D( 0, GL_DEPTH_COMPONENT, getViewportW(), getViewportH(), 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0x0 );

      _rbo_select.texImage2D( 0, GL_RGBA8, getViewportW(), getViewportH(), 0, GL_RGBA, GL_UNSIGNED_BYTE, 0x0 );
      _rbo_select_depth.texImage2D( 0, GL_DEPTH_COMPONENT, getViewportW(), getViewportH(), 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0x0 );

      Renderer::reshape();
    }


  void DisplayRenderer::renderScene(Camera* cam) {


    // Setup size of viewport viewport to fit size of render target
    GL_CHECK(::glViewport(0, 0, getViewportW(), getViewportH()));

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
      for( int j = 0; j < _objs.getSize(); ++j )
        render( _objs[j], cam);

    } _fbo.unbind();

    // Selection rendering - render to depth buffer
    _fbo_select_depth.bind(); {

      GL_CHECK(::glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ));

      for( int j = 0; j < _objs.getSize(); ++j )
        renderSelectedGeometry( _objs[j], cam);

    } _fbo_select_depth.unbind();

    // Selection rendering - render
    _fbo_select.bind(); {

      GLint depth_mask, depth_func;
      GL_CHECK(::glGetIntegerv( GL_DEPTH_WRITEMASK, &depth_mask ));
      GL_CHECK(::glGetIntegerv( GL_DEPTH_FUNC, &depth_func));

      GL_CHECK(::glDepthFunc( GL_LEQUAL ));
      GL_CHECK(::glDepthMask( GL_TRUE ));

      GL_CHECK(::glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ));

      for( int j = 0; j < _objs.getSize(); ++j )
        renderSelectedGeometry( _objs[j], cam );

      GL_CHECK(::glDepthFunc( depth_func ));
      GL_CHECK(::glDepthMask( depth_mask ));

    } _fbo_select.unbind();

  }

} // END namespace GMlib
