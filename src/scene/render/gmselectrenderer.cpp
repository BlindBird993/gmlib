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

/*! \file gmselectrender.cpp
 *  \brief Pending Documentation
 *
 *  Pending Documentation
 */


#include "gmselectrenderer.h"

// local
#include "../gmscene.h"
#include "../camera/gmcamera.h"

// gmlib
#include <opengl/shaders/gmvertexshader.h>
#include <opengl/shaders/gmfragmentshader.h>
#include <opengl/gmprogram.h>

// stl
#include <cassert>


namespace GMlib {


  SelectRenderer::SelectRenderer(Scene *scene)
    : MultiObjectRenderer( scene )
  {

    initSelectProgram();

    _fbo.create();
    _rbo_color.create(GL_TEXTURE_2D);
    _rbo_depth.create(GL_TEXTURE_2D);


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


    _fbo.attachTexture2D( _rbo_color,  GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 );
    _fbo.attachTexture2D( _rbo_depth, GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT );
  }

  DisplayObject *SelectRenderer::findObject(int x, int y) const {

    Color c;
    _fbo.bind();
    GL_CHECK(::glReadPixels(x,y,1,1,GL_RGB,GL_UNSIGNED_BYTE,(GLubyte*)(&c)));
    _fbo.unbind();

    DisplayObject *obj = dynamic_cast<DisplayObject*>(_scene->find(c.get()));

    return obj;
  }

  Array<DisplayObject*> SelectRenderer::findObjects(int xmin, int ymin, int xmax, int ymax) const {

    Array<DisplayObject* > sel;
    int dx=(xmax-xmin)+1;
    int dy=(ymax-ymin)+1;

    Color* pixels = new Color[dx*dy];
    _fbo.bind();
    GL_CHECK(::glReadPixels(xmin,ymin,dx-1,dy-1,GL_RGBA,GL_UNSIGNED_BYTE,(GLubyte*)pixels));
    _fbo.unbind();

    int ct = 0;
    Color c;
    for(int i = ymin; i < ymax; ++i) {
      for(int j = xmin; j < xmax; ++j) {
        c = pixels[ct++];
        DisplayObject *tmp = dynamic_cast<DisplayObject*>(_scene->find(c.get()));
        if(tmp)
          if(!tmp->isSelected()) { sel.insertAlways(tmp); }
      }
    }
    delete [] pixels;

    return sel;
  }

  void SelectRenderer::initSelectProgram() {

    const std::string prog_name    = "select_prog";
    if( _prog.acquire(prog_name) ) return;

    std::string vs_src(
          "#version 150 compatibility \n"
          "uniform mat4 u_mvpmat; \n"
          "uniform vec4 u_color; \n"
          "\n"
          "in vec4 in_vertex; \n"
          "\n"
          "out vec4 ex_color; \n"
          "out vec4 gl_Position; \n"
          "\n"
          "void main() \n"
          "{ \n"
          "  gl_Position = u_mvpmat * in_vertex; \n"
          "  ex_color = u_color; \n"
          "}\n"
          );

    std::string fs_src(
          "#version 150 compatibility \n"
          "\n"
          "in vec4 ex_color; \n"
          "\n"
          "out vec4 gl_FragColor; \n"
          "\n"
          "void main() \n"
          "{ \n"
          "  gl_FragColor = ex_color; \n"
          "} \n"
          );

    GL::VertexShader vshader;
    vshader.create("select_vs");
    vshader.setPersistent(true);
    vshader.setSource(vs_src);
    assert(vshader.compile());

    GL::FragmentShader fshader;
    fshader.create("select_fs");
    fshader.setPersistent(true);
    fshader.setSource(fs_src);
    assert(fshader.compile()) ;

    _prog.create(prog_name);
    _prog.setPersistent(true);
    _prog.attachShader(vshader);
    _prog.attachShader(fshader);
    assert(_prog.link());
  }

  void SelectRenderer::prepare(Array<DisplayObject *> &objs, const Camera *cam) const{

    cam->applyViewport();

    assert( _scene );
    objs.resetSize();
    _scene->getDisplayableObjects(objs, cam);
  }

  void SelectRenderer::resize(int w, int h) {

    Renderer::resize(w,h);

    _rbo_color.texImage2D( 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0x0 );
    _rbo_depth.texImage2D( 0, GL_DEPTH_COMPONENT, w, h, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0x0 );
  }


} // END namespace GMlib
