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
#include "gmrendertarget.h"
#include "rendertargets/gmnativerendertarget.h"

// gmlib
#include <opengl/utils/gmutils.h>

// stl
#include <cassert>


namespace GMlib {

  Renderer::Renderer()
    : _x(0), _y(0), _w(0), _h(0),
      _clear_color(GMcolor::Grey) {

    _rt = new NativeRenderTarget;
  }

  Renderer::~Renderer() {

    delete _rt;
  }

  const Color&Renderer::getClearColor() const {

    return _clear_color;
  }

  void Renderer::setClearColor(const Color& color) {

    _clear_color = color;
  }

  void Renderer::reshape(int x, int y, int w, int h) {

    _x = x;
    _y = y;
    _w = w;
    _h = h;

    _rt->resize( Vector<unsigned int,2>( _w, _h ) );
  }

  void Renderer::setRenderTarget(RenderTarget* rt) {

    assert(rt);
    delete _rt;
    _rt = rt;
  }

  void Renderer::prepare(Array<DisplayObject*>& objs, Camera *cam) {


    Scene *scene = cam->getScene();
    assert(scene);

    // Compute frustum/frustum-matrix, set glViewport
    cam->setupDisplay();

    // Get displayable objects
    objs.resetSize();
    scene->getDisplayableObjects( objs, cam );
  }

  void Renderer::setupViewport( int x, int y, int w, int h ) {

    GL_CHECK(::glViewport(x, y, w, h));
  }

  void Renderer::render( Camera* cam) {

    // Prepare
    prepare( _objs, cam );

    // Set Viewport
    setupViewport(0, 0, _w, _h);

    // Render objects
    renderObjects( _objs, cam);
  }

  void Renderer::renderTo() {

    // Set Viewport
    setupViewport(_x, _y, _w, _h);

    // Render to target
    _rt->clear();
    _rt->bind();
    renderToTarget();
    _rt->unbind();
  }





} // END namespace GMlib
