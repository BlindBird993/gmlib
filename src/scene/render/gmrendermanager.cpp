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

/*! \file gmrendermanager.h
 *  \brief Pending Documentation
 *
 *  Pending Documentation
 */


#include "gmrendermanager.h"

// local
#include "../camera/gmcamera.h"
#include "../gmscene.h"
#include "../gmsceneobject.h"
#include "../window/gmwindow.h"
#include "gmdisplayrenderer.h"
#include "gmselectrenderer.h"

//gmlib
#include <opengl/gmopengl.h>



namespace GMlib {

  RenderManager::RenderManager(GMWindow *window)
    : _objs(128), _clear_color( 0.5f, 0.5f, 0.5f, 1.0f ),
      _select_color( GMcolor::Pink )
  {

    _window = window;
    _scene = static_cast<Scene*>( window );
    _disp = new DisplayRenderer( window );
    _select = new SelectRenderer( window );
  }

  const Color &RenderManager::getClearColor() const {

    return _clear_color;
  }

  const Color &RenderManager::getSelectColor() const {

    return _select_color;
  }

  DisplayObject *RenderManager::findObject(int x, int y) {

    return _select->findObject( x, y );
  }

  void RenderManager::resize(int w, int h) {

    _disp->resize(w,h);
    _select->resize(w,h);

    _w = w;
    _h = h;
  }

  void RenderManager::render(const Array<Camera*>& cameras ) {


    // Initialize scene
    GL::glClearColor( getClearColor() );
    ::glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    ::glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
    ::glShadeModel(GL_SMOOTH);
    ::glEnable(GL_DEPTH_TEST);
    ::glEnable(GL_LIGHTING);

    // Update camera orientation
    for( int i = 0; i < cameras.getSize(); ++i )
      cameras(i)->updateCameraOrientation();

    // Render
    _disp->render( _objs, cameras );
  }

  void RenderManager::renderTo() {

    _disp->render( _window );
  }

  void RenderManager::select(Camera *cam, int type_id) {

      _select->select( _objs, cam, type_id );
  }

  void RenderManager::setClearColor(const Color &c) {

    _clear_color = c;
  }

  void RenderManager::setSelectColor(const Color &c) {

    _select_color = c;
  }

  void RenderManager::updateMaxObjects(int no_objs) {

    if( _objs.getMaxSize() < no_objs )
      _objs.setMaxSize(no_objs);
  }



} // END namespace GMlib
