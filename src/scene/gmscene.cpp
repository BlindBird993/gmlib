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



/*! \file gmscene.cpp
 *
 *  Implementation of the Scene class.
 */


#include "gmscene.h"

#include "gmsceneobject.h"
#include "light/gmlight.h"
#include "camera/gmcamera.h"
#include "event/gmeventmanager.h"
#include "render/gmrendermanager.h"


namespace GMlib {



  /*! Scene::Scene()
   *  \brief Pending Documentation
   *
   *  Default constructor
   */
  Scene::Scene() :
    _scene(),
    _matrix_stack(32),
    _event_manager(0) {

    _timer_active   = true;
    _timer_time_scale    = 1;
    _timer_time_elapsed  = 0;
    _timer_fixed_dt_enabled = false;
    _timer_fixed_dt = 0.25;
    _matrix_stack    += HqMatrix<float,3>();
  }


  /*! Scene::Scene( SceneObject* obj )
   *  \brief Pending Documentation
   *
   *  Standar constructor
   */
  Scene::Scene( SceneObject* obj ) :
    _scene(),
    _matrix_stack(32),
    _event_manager(0) {

    _scene += obj;
    _timer_active = true;
    _timer_time_scale = 1;
    _timer_time_elapsed  = 0;
    _timer_fixed_dt_enabled = false;
    _timer_fixed_dt = 0.25;
    _matrix_stack += HqMatrix<float,3>();
  }


  /*! Scene::Scene( const Scene&  s )
   *  \brief Pending Documentation
   *
   *  Copy constructor
   */
  Scene::Scene( const Scene&  s ) :
    _scene(s._scene),
    _matrix_stack(s._matrix_stack),
    _event_manager(0) {

    _timer_active   = true;
    _timer_time_scale    = 1;
    _timer_time_elapsed  = 0;
    _timer_fixed_dt_enabled = false;
    _timer_fixed_dt = 0.25;
  }


  /*! Scene::~Scene()
   *  \brief Pending Documentation
   *
   *  Destructor
   */
  Scene::~Scene() {

    for( int i=0; i < _scene.getSize(); i++ )
      if( _scene[i] != 0x0 )
        delete _scene[i];
  }


  /*! SceneObject* Scene::find(unsigned int name)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  SceneObject* Scene::find(unsigned int name) {
    SceneObject* obj;

    for(int i=0; i < _scene.getSize(); i++)
      if( (obj = _scene[i]->find(name)) ) return obj;
    return 0;
  }

  RenderManager *Scene::getRenderManager() const {  return 0x0; }

  void Scene::getDisplayableObjects(Array<DisplayObject *> &disp_objs, const Camera *cam)  const {

    const Frustum &frustum = cam->getFrustum();
    const bool is_culling = cam->isCulling();

    if(is_culling)
      for( int i = 0; i < _scene.getSize(); ++i )
        _scene(i)->culling( disp_objs, frustum );
    else
      for( int i = 0; i < _scene.getSize(); ++i )
        _scene(i)->fillObj( disp_objs );
  }


  /*! int Scene::getSize()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  int Scene::getSize() {

    return _scene.getSize();
  }


  /*! Sphere<float,3>	Scene::getSphere()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  Sphere<float,3>	Scene::getSphere() {

    Sphere<float,3> sp;
    for(int i=0; i< _scene.getSize(); i++)
      sp += _scene[i]->getSurroundingSphere();
    return sp;
  }


  /*! Sphere<float,3>	Scene::getSphereClean() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  Sphere<float,3>	Scene::getSphereClean() const {

    Sphere<float,3> sp;
    for(int i=0; i< _scene.getSize(); i++)
      sp += _scene(i)->getSurroundingSphereClean();
    return sp;
  }

  void Scene::updateSelection(SceneObject *obj) {

    if( obj->isSelected() )
      _sel_objs.insert(obj);
    else
      _sel_objs.remove(obj);
  }


  /*! void Scene::insert(SceneObject* obj)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void Scene::insert(SceneObject* obj) {

    if(!obj)
      return;

    _scene.insert(obj);
    obj->setParent(0);
  }


  /*! void Scene::prepare()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void Scene::prepare() {

    int no_disp_obj = 0;
    _lights.resetSize();

    for(int i=0; i < _scene.getSize(); i++)
      no_disp_obj += _scene[i]->prepare( _lights, _matrix_stack, this );

    updateMaxObjects(no_disp_obj);
  }


  /*! void Scene::remove( SceneObject* obj )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void Scene::remove( SceneObject* obj ) {

    if(obj) _scene.remove(obj);
  }

  /*! SceneObject* Scene::operator[]( int i )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  SceneObject* Scene::operator[]( int i ) {

    return _scene[i];
  }


  /*! Scene& Scene::operator=(const Scene& sc)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  Scene& Scene::operator=(const Scene& sc) {

    _timer_active	        = false;
    _timer_time_elapsed   = sc._timer_time_elapsed;
    _timer_time_scale	    = sc._timer_time_scale;

    _scene		            = sc._scene;

    _event_manager        = sc._event_manager;

    return *this;
  }

  bool Scene::isSelected(SceneObject *obj) const {

    return _sel_objs.exist( obj );
  }

  void
  Scene::setEventManager(EventManager *mgr) {
    _event_manager = mgr;
  }

  void Scene::enabledFixedDt() {

    _timer_fixed_dt_enabled = true;
  }

  void Scene::disableFixedDt() {

    _timer_fixed_dt_enabled = false;
  }

  void Scene::setFixedDt(double dt) {

    _timer_fixed_dt = dt;
  }

  void Scene::removeSelections() {

    // make a copy of the array instead of a reference as
    // SceneObject->setSelected(...) updates the selected objects array.
    Array<SceneObject*> sel_objs = getSelectedObjects();

    for( int i = 0; i < sel_objs.getSize(); i++ )
        sel_objs[i]->setSelected( false );
  }

  /*! void Scene::simulate()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  NB!!! ONLY USED BY gmWindow    // Subject to change
   */
  void Scene::simulate() {

    if( !_timer_active ) return;

    if( _timer_time_elapsed == 0 )	prepare();

    double dt, timer_dt;
    timer_dt = _timer.getSec(true);
    if( _timer_fixed_dt_enabled ) dt = _timer_fixed_dt;
    else                          dt = _timer_time_scale * timer_dt;

    if(dt) {

      _timer_time_elapsed  += dt;
      if ( _event_manager ) _event_manager->processEvents(dt);
      for( int i=0; i< _scene.getSize(); i++ )
        _scene[i]->simulate(dt);
    }
  }

  void Scene::updateMaxObjects(int /*no_objects*/) {}


} // END namespace GMlib







