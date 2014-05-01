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



/*! \file gmwindow.cpp
 *  \brief Pending Description
 */


#include "gmwindow.h"

// gmlib
#include <core/containers/gmdvector.h>
#include <opengl/gmopenglmanager.h>

// stl
#include <cstdio>
#include <iostream>


namespace GMlib {




  /*! GMWindow::GMWindow()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  GMWindow::GMWindow(bool init_default_cam) {

    // create buffers
    _std_rep_cube.acquire("std_rep_cube");
    _std_rep_cube_indices.acquire("std_rep_cube_indices");
    _std_rep_frame_indices.acquire("std_rep_frame_indices");


    _stereo     = false;
    _running    = false;
    _isbig      = false;
    _target     = NULL;
    _sun        = NULL;
    _move       = 0.0;
    _active_cam = 0;
    stop();

    if( init_default_cam ) {

      Point<float,3> init_cam_pos(  0.0f, 0.0f, 0.0f );
      Vector<float,3> init_cam_dir( 0.0f, 1.0f, 0.0f );
      Vector<float,3> init_cam_up(  0.0f, 0.0f, 1.0f );

      Camera *cam = new Camera( init_cam_pos, init_cam_dir, init_cam_up );
      insertCamera( cam );
      addViewSet( getCameraIndex(cam) );
    }

    _rm = new RenderManager(this);
  }


  /*! GMWindow::GMWindow(const GMWindow&)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  GMWindow::GMWindow( const GMWindow& gw ) : Scene() {

    (*this) = gw;
  }


  /*! GMWindow::~GMWindow()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  GMWindow::~GMWindow() {

    int i;
    if(_sun) delete _sun;
    for(i=0; i<_cameras.getSize(); i++)
    {
      remove(_cameras[i]);
      delete _cameras[i];
    }
    Light * light;
    for(i=_lights.getSize()-1; i>=0; i=_lights.getSize()-1)
    {
      light = _lights.back();
      removeLight(light);
      delete light;
    }
  }


  void GMWindow::addViewSet( int cam_idx ) {

    if( cam_idx < 1 || cam_idx >= _cameras.getSize() )
      return;

    _view_set_stack += ViewSet(_cameras[cam_idx]);
  }


  /*! void GMWindow::setViewSet(int new_c, int old_c, bool split_vertically, double d)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void GMWindow::addToViewSet(int cam_idx, int split_cam_idx, bool split_vertically, double d) {

    if(cam_idx<1 || cam_idx>=_cameras.getSize() || split_cam_idx <1 || split_cam_idx>=_cameras.getSize() || d<=0 || d>=1) {

      return;
    }

    _view_set_stack.back().insertCamera(_cameras[split_cam_idx],_cameras[cam_idx], split_vertically,d);

    _view_set_stack.back().prepare(_w,_h);
  }


  void GMWindow::clearScene() {

    if( _running )
      Scene::stop();

    for(int i = 0; i < _sel_objs.getSize(); i++)
      _sel_objs[i]->setSelected( false );
    _sel_objs.clear();

    Array<SceneObject*> rmobjs;
    for( int i = 0; i < getSize(); i++ )
      rmobjs += operator[](i);

    for( int i = 0; i < rmobjs.getSize(); i++ ) {

      Camera* cam   = dynamic_cast<Camera*>( rmobjs[i] );
      Light* light  = dynamic_cast<Light*>( rmobjs[i] );

      if( cam )
        continue;
//        removeCamera( cam );
      else if( light )
        continue;
//        removeLight( light );
      else
        remove( rmobjs[i] );

      delete rmobjs[i];
    }

    if( _running )
      Scene::start();
  }

  void GMWindow::clearViewSetConfiguration() {

    if( _running )
      Scene::stop();

    for(int i = 0; i < _sel_objs.getSize(); i++)
      _sel_objs[i]->setSelected( false );
    _sel_objs.clear();

    Array<SceneObject*> rmobjs;
    for( int i = 0; i < getSize(); i++ )
      rmobjs += operator[](i);

    for( int i = 0; i < rmobjs.getSize(); i++ ) {

      Camera* cam   = dynamic_cast<Camera*>( rmobjs[i] );
      if( cam ) {
        removeCamera( cam );
        delete rmobjs[i];
      }
    }

    if( _running )
      Scene::start();
  }

  RenderManager* GMWindow::getRenderManager() const {

    return _rm;
  }

  const Color& GMWindow::getSelectColor() const {

    return getRenderManager()->getSelectColor();
  }

  /*! void GMWindow::insertCamera(Camera* cam, bool insert_in_scene)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void GMWindow::insertCamera(Camera* cam, bool insert_in_scene) {

    cam->setScene(this);
    _cameras += cam;
    if(insert_in_scene)  insert(cam);
  }


  /*! void GMWindow::insertLight(Light* light, bool insert_in_scene)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void GMWindow::insertLight(Light* light, bool insert_in_scene) {

    _lights += light;

    SceneObject* obj = dynamic_cast<SceneObject*>(light);

    if(insert_in_scene && obj)
      insert(obj);
  }


  /*! void GMWindow::popViewSet(int i)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void GMWindow::popView(int cam_idx) {

    _view_set_stack.back().removeCamera(cam_idx);
  }


  void GMWindow::popViewSet() {

    if( getViewSetStackSize() > 2 )
      _view_set_stack.pop();
  }


  /*! bool GMWindow::removeCamera(Camera *)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  bool GMWindow::removeCamera(Camera * cam) {

    if(_cameras.getSize() < 2)
      return false;

    int i = _cameras.getIndex(cam);
    if(i>0)
    {
      for(int j=1; j<_view_set_stack.getSize(); j++)
        _view_set_stack[j].removeCamera(_cameras[_active_cam]);

      remove(cam);
      _cameras.removeIndex(i);
      return true;
    }
    return false;
  }


  /*! bool GMWindow::removeLight(Light* light)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  bool GMWindow::removeLight(Light* light) {

    int i = _lights.getIndex(light);
    if(i>=0)
    {
      SceneObject* obj = dynamic_cast<SceneObject*>(light);

      if(obj)
        remove(obj);

      _lights.removeIndex(i);

      return true;
    }
    return false;
  }

  const Array<Light*>&GMWindow::getInsertedLights() const {

    return _lights;
  }


  /*! void GMWindow::scaleDayLight(double)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void GMWindow::scaleDayLight(double d) {

    _sun->scaleDayLight(d);
  }

  void GMWindow::setClearColor(const Color &color) {

    getRenderManager()->setClearColor(color);
  }

  void GMWindow::setSelectColor( const Color& color ) {

    getRenderManager()->setSelectColor(color);
  }

  void GMWindow::setRenderTarget(RenderTarget *rt) {

    _rm->setRenderTarget( rt );
  }


  /*! bool GMWindow::toggleStereo()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  bool GMWindow::toggleStereo() {

    _stereo = !_stereo;
    return _stereo;
  }

  void GMWindow::initStdGeometry() {

    // std radius of inscribed circle
    float ir = 0.07;

    // Vertices
    GLfloat cube[] = {

    /* 0 */     -ir,    -ir,    -ir,      // Back/Left/Down
    /* 1 */      ir,    -ir,    -ir,
    /* 2 */      ir,     ir,    -ir,
    /* 3 */     -ir,     ir,    -ir,
    /* 4 */     -ir,    -ir,     ir,      // Front/Left/Down
    /* 5 */      ir,    -ir,     ir,
    /* 6 */      ir,     ir,     ir,
    /* 7 */     -ir,     ir,     ir
    };

    // Indice Coords
    GLushort cube_indices[] = {

      4,  5,  6,  7,    // Front
      1,  2,  6,  5,    // Right
      0,  1,  5,  4,    // Bottom
      0,  3,  2,  1,    // Back
      0,  4,  7,  3,    // Left
      2,  3,  7,  6     // Top
    };

    // Frame indice coords
    GLushort frame_indices [] = {

      0,  1,    // x-axis
      0,  3,    // y-axis
      0,  4,    // z-axis

      // Remaining frame
      2,  3,
      2,  1,
      2,  6,

      7,  6,
      7,  4,
      7,  3,

      5,  4,
      5,  6,
      5,  1

    };

    _std_rep_cube.bufferData( 24 * sizeof(GLfloat), cube, GL_STATIC_DRAW );
    _std_rep_cube_indices.bufferData( 24 * sizeof(GLushort), cube_indices, GL_STATIC_DRAW );
    _std_rep_frame_indices.bufferData( 24 * sizeof(GLushort), frame_indices, GL_STATIC_DRAW );
  }

  SceneObject *GMWindow::findSelectObject(Camera *cam, const Vector<int,2> &pos, int type_id) const {

    return findSelectObject( cam, pos(0), pos(1), type_id );
  }

  SceneObject *GMWindow::findSelectObject(Camera *cam, int x, int y, int type_id) const {

    RenderManager *rm = getRenderManager();
    rm->select( cam, type_id );
    return rm->findObject( x, y );
  }


  /*! GMWindow& GMWindow::operator=(const GMWindow& gw)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  GMWindow& GMWindow::operator=(const GMWindow& gw) {

    Scene::operator=(gw);
    _cameras  = gw._cameras;
    _lights  = gw._lights;
    _sun  = gw._sun;
    for(int i=0; i<_cameras.getSize(); i++)
      _cameras[i]->setScene(this);

    _stereo  = false;
    _running = false;
    _isbig   = false;
    _sel_objs.clear();
    _view_set_stack = gw._view_set_stack;        // Active camera set
    reshape(_w,_h);
    return *this;
  }



  #ifndef GL_MULTISAMPLE
  #define GL_MULTISAMPLE  0x809D
  #endif
  /*! void GMWindow::init()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void GMWindow::init() {

//    cout << "GMWindow::init()" << endl;

    initStdGeometry();

    if(_sun)
      _sun->scaleDayLight(1.0);
    insertCamera(new Camera(Point<float,3>(10,10,5),Point<float,3>(-10,-10,-5),Vector<float,3>(0,0,-1)));
    _view_set_stack += ViewSet(_cameras[0]);
    _view_set_stack.back().prepare(_w,_h);
//    int numberoflights;
//    glGetIntegerv(GL_MAX_LIGHTS,&numberoflights);
//    char s[32];
//    std::sprintf( s, "Max number of lights %d\n", numberoflights );
//    message(s);
    //char *extensions = NULL;
      //extensions = (char *)glGetString(GL_EXTENSIONS);
      //_message(extensions);
  }


  /*! bool GMWindow::toggleRun()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  bool GMWindow::toggleRun() {

    if( ( _running = !_running ) )
      start();
    else
      stop();

    return _running;
  }

} // END namespace GMlib
