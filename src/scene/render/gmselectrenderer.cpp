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

// stl
#include <cassert>


namespace GMlib {


  SelectRenderer::SelectRenderer(Scene *scene) : MultiObjectRenderer( scene ) {

    _fbo.attachRenderbuffer( _rbo_color, GL_COLOR_ATTACHMENT0 );
    _fbo.attachRenderbuffer( _rbo_depth, GL_DEPTH_ATTACHMENT );


    _std_rep_visu = new VisualizerStdRep;
  }

  DisplayObject *SelectRenderer::findObject(int x, int y) const {

    Color c;
    _fbo.bind();
    glReadPixels(x,y,1,1,GL_RGB,GL_UNSIGNED_BYTE,(GLubyte*)(&c));
    _fbo.unbind();

    DisplayObject *obj = dynamic_cast<DisplayObject*>(_scene->find(c.get()));
//    if( obj )
//      obj->setSelected(true);

    return obj;
  }

  Array<DisplayObject*> SelectRenderer::findObjects(int xmin, int ymin, int xmax, int ymax) const {

    Array<DisplayObject* > sel;
    int dx=(xmax-xmin)+1;
    int dy=(ymax-ymin)+1;

    Color* pixels = new Color[dx*dy];
    _fbo.bind();
    glReadPixels(xmin,ymin,dx-1,dy-1,GL_RGBA,GL_UNSIGNED_BYTE,(GLubyte*)pixels);
    _fbo.unbind();

    int ct = 0;
    Color c;
    for(int i = ymin; i < ymax; ++i) {
      for(int j = xmin; j < xmax; ++j) {
        c = pixels[ct++];
        DisplayObject *tmp = dynamic_cast<DisplayObject*>(_scene->find(c.get()));
        if(tmp)
          if(!tmp->isSelected()) { sel.insertAlways(tmp); /*tmp->setSelected(true);*/ }
      }
    }
    delete [] pixels;

    return sel;
  }

  void SelectRenderer::prepare(Array<DisplayObject *> &objs, Camera *cam) const{

    cam->applyViewport();

    assert( _scene );
    objs.resetSize();
    _scene->getDisplayableObjects(objs, cam);
  }

  void SelectRenderer::resize(int w, int h) {

    Renderer::resize(w,h);

    _rbo_color.createStorage( GL_RGB, w, h );
    _rbo_depth.createStorage( GL_DEPTH_COMPONENT32, w, h );
  }


} // END namespace GMlib
