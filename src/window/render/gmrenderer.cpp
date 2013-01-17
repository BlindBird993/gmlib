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


#include "gmrenderer.h"

// gmlib
#include <scene/gmfrustum.h>
#include <scene/camera/gmcamera.h>


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
  }

  bool Renderer::isInitialized() const {

    return _initialized;
  }

  void Renderer::markAsInitialized() {

    _initialized = true;
  }

  void Renderer::setBufferSize(int w, int h) {

    _buffer_width = w;
    _buffer_height = h;
  }

  void Renderer::prepare(Camera *cam) {

    // Compute frustum/frustum-matrix, set glViewport
    cam->setupDisplay();


    const Frustum &frustum = cam->getFrustum();
    const bool is_culling = cam->isCulling();

    _objs.resetSize();

    if( !_scene )
      return;

    if(is_culling)
      for( int i = 0; i < _scene->getSize(); ++i )
        (*_scene)[i]->culling( _objs, frustum );
    else
      for( int i = 0; i < _scene->getSize(); ++i )
        (*_scene)[i]->fillObj( _objs );
  }











  DisplayRenderer::DisplayRenderer(Scene *scene) : Renderer(scene) {

    init();
  }

  void DisplayRenderer::beginRendering() {

    OGL::bindRenderBuffer();
  }

  void DisplayRenderer::endRendering() {

    OGL::unbindRenderBuffer();
  }

  void DisplayRenderer::prepareRendering() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    OGL::clearRenderBuffer();
  }

  void DisplayRenderer::init() {

    OGL::createRenderBuffer();
  }

  void DisplayRenderer::render( Camera* cam) {

    for( int i = 0; i < _objs.getSize(); i++ )
      _objs[i]->display( cam );
  }

  void DisplayRenderer::resize(int w, int h) {

    setBufferSize( w, h );
    OGL::setRenderBufferSize(w,h);
  }


} // END namespace GMlib
