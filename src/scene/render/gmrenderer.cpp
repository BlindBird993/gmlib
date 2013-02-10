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

/*! \file gmrender.cpp
 *  \brief Pending Documentation
 *
 *  Pending Documentation
 */


#include "gmrenderer.h"

// local
#include "../gmfrustum.h"
#include "../camera/gmcamera.h"

// stl
#include <cassert>


namespace GMlib {

  Renderer::Renderer(Scene *scene) {

    _scene = scene;
    _initialized = false;
  }

  Renderer::~Renderer() {}

  bool Renderer::isStereoEnabled() const {

    return _stereo;
  }

  void Renderer::enableStereo(bool enable) {

    _stereo = enable;
  }

  int Renderer::getBufferHeight() const {

    return _buffer_height;
  }

  int Renderer::getBufferWidth() const {

    return _buffer_width;
  }

  bool Renderer::isInitialized() const {

    return _initialized;
  }

  void Renderer::markAsInitialized() {

    _initialized = true;
  }

  void Renderer::resize(int w, int h) {

    _buffer_width = w;
    _buffer_height = h;
  }






  SingleObjectRenderer::SingleObjectRenderer(Scene *scene) : Renderer(scene) {

  }

  MultiObjectRenderer::MultiObjectRenderer(Scene *scene) : Renderer(scene) {
  }

  void MultiObjectRenderer::prepare(Array<DisplayObject *> &objs, Camera *cam) const {

    // Compute frustum/frustum-matrix, set glViewport
    cam->setupDisplay();

    const Frustum &frustum = cam->getFrustum();
    const bool is_culling = cam->isCulling();

    objs.resetSize();

    assert( _scene );

    if(is_culling)
      for( int i = 0; i < _scene->getSize(); ++i )
        (*_scene)[i]->culling( objs, frustum );
    else
      for( int i = 0; i < _scene->getSize(); ++i )
        (*_scene)[i]->fillObj( objs );
  }





} // END namespace GMlib
