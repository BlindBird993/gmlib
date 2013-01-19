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
#include "gmrenderer.h"
#include "../gmviewset.h"

//gmlib
#include <opengl/gmopengl.h>
#include <scene/camera/gmcamera.h>
#include <scene/gmscene.h>
#include <scene/gmsceneobject.h>



namespace GMlib {

  RenderManager::RenderManager(Scene *scene) {

    _scene = scene;
    _disp = new DisplayRenderer( scene );
    _select = new SelectRenderer( scene );

    init();
  }

  void RenderManager::init() {

    _disp->init();
    _select->init();
  }

  void RenderManager::render(ViewSet& view_set) {

    // Prepare renderer for rendering
    _disp->prepareRendering();

    for( int i = 0; i < view_set.getSize(); ++i ) {

      Camera *cam = view_set[i];
      cam->markAsActive();

      _disp->prepare( cam );

      // Tell renderer that rendering is begining
      _disp->beginRendering(); {

        // Rendering
        _disp->render( cam );
  //      _disp->renderSelect( cam );

      // Tell renderer that rendering is ending
      } _disp->endRendering();

      cam->markAsInactive();
    }
  }

  void RenderManager::select(Camera *cam, int type_id) {

    // Prepare for select rendering
    _select->prepareRendering();

    _select->prepare(cam);

    _select->beginRendering(); {

      _select->select( cam, type_id );

    }_select->endRendering();
  }

  void RenderManager::resize(int w, int h) {

    _disp->resize(w,h);
    _select->resize(w,h);
  }

  SceneObject *RenderManager::findObject(int x, int y) {

    _select->findObject( x, y );

  }



} // END namespace GMlib
