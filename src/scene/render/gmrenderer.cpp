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

// local
#include "scene/gmfrustum.h"
#include "scene/camera/gmcamera.h"

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










  DisplayRenderer::DisplayRenderer(Scene *scene) : MultiObjectRenderer(scene) {

    OGL::createRenderBuffer();
  }

  void DisplayRenderer::beginRendering() {

    OGL::bindRenderBuffer();
  }

  void DisplayRenderer::endRendering() {

    OGL::unbindRenderBuffer();
  }

  void DisplayRenderer::prepareRendering() {

    OGL::clearRenderBuffer();
  }

  void DisplayRenderer::prepare(Array<SceneObject*>& objs, Camera *cam) {

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

  void DisplayRenderer::render(Array<SceneObject*>& objs, const Array<Camera *> &cameras) {

    // Prepare renderer for rendering
    prepareRendering();

    // Tell renderer that rendering is begining
    beginRendering(); {

      for( int i = 0; i < cameras.getSize(); ++i ) {


        Camera *cam = cameras(i);
        cam->markAsActive();

        prepare( objs, cam );

        for( int i = 0; i < objs.getSize(); i++ )
          objs[i]->display( cam );

        cam->markAsInactive();
      }
    // Tell renderer that rendering is ending
    } endRendering();
  }

  void DisplayRenderer::renderSelect(Array<SceneObject*>& objs, const Array<Camera *> &cameras) {

    // Prepare renderer for rendering
    prepareRendering();

    // Tell renderer that rendering is begining
    beginRendering(); {

      for( int i = 0; i < cameras.getSize(); ++i ) {

        Camera *cam = cameras(i);
        cam->markAsActive();

        prepare( objs, cam);

        for( int i = 0; i < objs.getSize(); ++i )
          objs[i]->displaySelection( cam );

        cam->markAsInactive();
      }
    // Tell renderer that rendering is ending
    } endRendering();
  }

  void DisplayRenderer::resize(int w, int h) {

    setBufferSize( w, h );
    OGL::setRenderBufferSize(w,h);
  }








  SelectRenderer::SelectRenderer(Scene *scene) : MultiObjectRenderer( scene ) {

    OGL::createSelectBuffer();
  }

  SceneObject *SelectRenderer::findObject(int x, int y) {

    Color c;
    OGL::bindSelectBuffer();
    glReadPixels(x,y,1,1,GL_RGB,GL_UNSIGNED_BYTE,(GLubyte*)(&c));
    OGL::unbindSelectBuffer();

    SceneObject *obj = _scene->find(c.get());
    if( obj )
      obj->setSelected(true);

    return obj;
  }

  Array<SceneObject*> SelectRenderer::findObjects(int xmin, int ymin, int xmax, int ymax) {

    Array<SceneObject* > sel;
    int dx=(xmax-xmin)+1;
    int dy=(ymax-ymin)+1;


    Color* pixels = new Color[dx*dy];
    OGL::bindSelectBuffer();
    glReadPixels(xmin,ymin,dx-1,dy-1,GL_RGBA,GL_UNSIGNED_BYTE,(GLubyte*)pixels);
    OGL::unbindSelectBuffer();


    int ct = 0;
    Color c;
    for(int i = ymin; i < ymax; ++i) {
      for(int j = xmin; j < xmax; ++j) {
        c = pixels[ct++];
        SceneObject *tmp = _scene->find(c.get());
        if(tmp)
          if(!tmp->getSelected()) { sel.insertAlways(tmp); tmp->setSelected(true); }
      }
    }
    delete [] pixels;

    return sel;
  }



  void SelectRenderer::prepareRendering() {

    OGL::clearSelectBuffer();
  }

  void SelectRenderer::beginRendering() {

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    OGL::bindSelectBuffer();

//    GLboolean depth_test_state;
//    glGetBooleanv( GL_DEPTH_TEST, &depth_test_state );
    glEnable( GL_DEPTH_TEST );

  }

  void SelectRenderer::endRendering() {

//    if( !depth_test_state )
      glDisable( GL_DEPTH_TEST );

    OGL::unbindSelectBuffer();
  }

  void SelectRenderer::prepare(Array<SceneObject *> &objs, Camera *cam){


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

  void SelectRenderer::select(Array<SceneObject*>& objs, Camera *cam, int type_id) {

    // Prepare for select rendering
    prepareRendering();

    prepare( objs, cam );

    beginRendering(); {

      // Compute frustum/frustum-matrix, set glViewport
      cam->setupDisplay();

      const GLProgram select_prog("select");

      select_prog.bind();

      for( int i=0; i < objs.getSize(); i++ )
        objs[i]->select( type_id, cam );

      select_prog.unbind();


    } endRendering();

  }

  void SelectRenderer::resize(int w, int h) {

    OGL::setSelectBufferSize( w, h );
  }

  SingleObjectRenderer::SingleObjectRenderer(Scene *scene) : Renderer(scene) {

  }

  MultiObjectRenderer::MultiObjectRenderer(Scene *scene) : Renderer(scene) {
  }


} // END namespace GMlib
