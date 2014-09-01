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

// local
#include "gmsceneobject.h"
#include "light/gmlight.h"
#include "camera/gmcamera.h"
#include "event/gmeventmanager.h"
#include "light/gmpointlight.h"
#include "light/gmspotlight.h"
#include "light/gmsun.h"


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

    _matrix_stack += HqMatrix<float,3>();

    init();
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
    _matrix_stack += HqMatrix<float,3>();

    init();
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

    init();
  }


  /*! Scene::~Scene()
   *  \brief Pending Documentation
   *
   *  Destructor
   */
  Scene::~Scene() {

    clear();
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

  const SceneObject* Scene::find(unsigned int name) const {
//    SceneObject* obj;

    for(int i=0; i < _scene.getSize(); i++)
      if( const SceneObject* obj = _scene(i)->find(name) ) return obj;
    return 0;
  }

//  RenderManager *Scene::getRenderManager() const {  return 0x0; }

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

  void Scene::clear() {

    if( _running )
      stop();

    // Remove selections
    clearSelection();

    if(_sun) delete _sun;

    int i;
//    for(i=0; i<_cameras.getSize(); i++)
//    {
//      remove(_cameras[i]);
//      delete _cameras[i];
//    }
    Light * light;
    for(i=_lights.getSize()-1; i>=0; i=_lights.getSize()-1)
    {
      light = _lights.back();
      removeLight(light);
      delete light;
    }

    for( int i=0; i < _scene.getSize(); i++ )
      if( _scene[i] != 0x0 )
        delete _scene[i];

    _scene.setSize(0);

    if( _running )
      start();
  }

  void Scene::clearSelection() {

    for(int i = 0; i < _sel_objs.getSize(); i++)
      _sel_objs[i]->setSelected( false );
    _sel_objs.clear();
  }

  void Scene::render() {

    for( int i = 0; i < _cameras.getSize(); ++i ) {
      _cameras[i]->updateLightUBO(this);
      _cameras(i)->render();
    }
  }


  /*! int Scene::getSize()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  int Scene::getSize() {

    return _scene.getSize();
  }


  /*! Sphere<float,3>  Scene::getSphere()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  Sphere<float,3>  Scene::getSphere() {

    Sphere<float,3> sp;
    for(int i=0; i< _scene.getSize(); i++)
      sp += _scene[i]->getSurroundingSphere();
    return sp;
  }


  /*! Sphere<float,3>  Scene::getSphereClean() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  Sphere<float,3>  Scene::getSphereClean() const {

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



  void Scene::insertCamera(Camera* cam) {

    cam->setScene(this);
    _cameras += cam;

    insert(cam);
  }

  bool Scene::removeCamera(Camera* cam) {

    if(_cameras.getSize() < 2)
      return false;

    int i = _cameras.getIndex(cam);
    if(i>0) {

//      for(int j=1; j<_view_set_stack.getSize(); j++)
//        _view_set_stack[j].removeCamera(_cameras[_active_cam]);
      remove(cam);

      _cameras.removeIndex(i);
      return true;
    }
    return false;
  }


  /*! void Scene::prepare()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void Scene::prepare() {

    int no_disp_obj = 0;

    for(int i=0; i < _scene.getSize(); i++)
      no_disp_obj += _scene[i]->prepare( _matrix_stack, this );

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

  void Scene::insertLight(Light* light, bool insert_in_scene ) {

    _lights += light;

    SceneObject *obj = dynamic_cast<SceneObject*>(light);

    if(insert_in_scene && obj)
      insert(obj);

    updateLightUBO();
  }

  bool Scene::removeLight(Light* light) {

    int i = _lights.getIndex(light);
    if(i>=0) {

      SceneObject* obj = dynamic_cast<SceneObject*>(light);

      if(obj)
        remove(obj);

      _lights.removeIndex(i);

      updateLightUBO();

      return true;
    }
    return false;
  }

  void Scene::insertSun() {

    if( _sun ) return;

    _sun = new Sun();
    _sun->scaleDayLight(1.0);

    updateLightUBO();
  }

  void Scene::removeSun() {

    if(!_sun) return;

    delete _sun;
    _sun = 0x0;

    updateLightUBO();
  }

  void Scene::scaleDayLight(double d) {

    _sun->scaleDayLight(d);
  }

  void Scene::setSunDirection(Angle d) {

    if(_sun)
      _sun->rotateGlobal(d, Vector<float,3>(1.0,1.0,0.0));
  }

  bool Scene::isRunning() const {

    return _running;
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
  Scene& Scene::operator=(const Scene& other) {

    _timer_active         = false;
    _timer_time_elapsed   = other._timer_time_elapsed;
    _timer_time_scale     = other._timer_time_scale;

    _scene                = other._scene;
    _event_manager        = other._event_manager;

    _running              = false;

    _lights               = other._lights;
    _sun                  = other._sun;

    _cameras              = other._cameras;
    for(int i=0; i<_cameras.getSize(); i++)
      _cameras[i]->setScene(this);

    clearSelection();

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

    if( _timer_time_elapsed == 0 ) prepare();

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



  void Scene::updateLightUBO() {

    /*
     *  Light types of "sun", "point" and "spot" is supported.
     *  It is assumed that the lights is grouped and sorted in that order
     *  and that the "number of info" is recorded in the header block:
     *  <ul>
     *    <li>Total number of lights.</li>
     *    <li>Number of suns.</li>
     *    <li>Number of point lights.</li>
     *    <li>Number of spot lights.</li>
     *  </ul>
     */

    GL::GLVector<4,GLuint> header;
    std::vector<unsigned int> light_ids;
    std::vector<GL::GLLight> lights;

    Array< SpotLight* > spot_lights;
    Array< PointLight* > point_lights;
    for( int i = 0; i < _lights.size(); ++i ) {


      if( SpotLight* spot_light = dynamic_cast<SpotLight*>( _lights[i] ) ) {

        spot_lights += spot_light;
      }
      else if( PointLight* point_light = dynamic_cast<PointLight*>( _lights[i] ) ) {

        point_lights += point_light;
      }
    }

    // Set header data
//    header.p[1] = _sun ? 1 : 0;
//    header.p[2] = point_lights.size();
//    header.p[3] = spot_lights.size();
//    header.p[0] = header.p[1] + header.p[2] + header.p[3];

    header.p[0] = _sun ? 1.: 0;
    header.p[1] = header.p[0] + point_lights.size();
    header.p[2] = header.p[1] + spot_lights.size();
    header.p[3] = header.p[2];

    if( header.p[0] <= 0 )
      return;

    // Add data to header array
    if( _sun ) {

      GL::GLLight sun;

      sun.amb.p[0] = _sun->getGlobalAmbient().getRedC();
      sun.amb.p[1] = _sun->getGlobalAmbient().getGreenC();
      sun.amb.p[2] = _sun->getGlobalAmbient().getBlueC();
      sun.amb.p[3] = _sun->getGlobalAmbient().getAlphaC();

      sun.dir.p[0] = _sun->getDir()(0);
      sun.dir.p[1] = _sun->getDir()(1);
      sun.dir.p[2] = _sun->getDir()(2);

      lights.push_back(sun);
      light_ids.push_back(_sun->getLightName());
    }

    for( int i = 0; i < point_lights.size(); ++i ) {

      PointLight *light = point_lights[i];

      GL::GLLight pl;
      pl.amb.p[0] = light->getAmbient().getRedC();
      pl.amb.p[1] = light->getAmbient().getGreenC();
      pl.amb.p[2] = light->getAmbient().getBlueC();
      pl.amb.p[3] = light->getAmbient().getAlphaC();

      pl.dif.p[0] = light->getDiffuse().getRedC();
      pl.dif.p[1] = light->getDiffuse().getGreenC();
      pl.dif.p[2] = light->getDiffuse().getBlueC();
      pl.dif.p[3] = light->getDiffuse().getAlphaC();

      pl.spc.p[0] = light->getSpecular().getRedC();
      pl.spc.p[1] = light->getSpecular().getGreenC();
      pl.spc.p[2] = light->getSpecular().getBlueC();
      pl.spc.p[3] = light->getSpecular().getAlphaC();

      pl.pos.p[0] = light->getPos()(0);
      pl.pos.p[1] = light->getPos()(1);
      pl.pos.p[2] = light->getPos()(2);
      pl.pos.p[3] = 1.0f;

      pl.att.p[0] = light->getAttenuation()(0);
      pl.att.p[1] = light->getAttenuation()(1);
      pl.att.p[2] = light->getAttenuation()(2);

      lights.push_back(pl);
      light_ids.push_back(light->getLightName());
    }

    for( int i = 0; i < spot_lights.size(); ++i ) {

      SpotLight *light = spot_lights[i];

      GL::GLLight sl;
      sl.amb.p[0] = light->getAmbient().getRedC();
      sl.amb.p[1] = light->getAmbient().getGreenC();
      sl.amb.p[2] = light->getAmbient().getBlueC();
      sl.amb.p[3] = light->getAmbient().getAlphaC();

      sl.dif.p[0] = light->getDiffuse().getRedC();
      sl.dif.p[1] = light->getDiffuse().getGreenC();
      sl.dif.p[2] = light->getDiffuse().getBlueC();
      sl.dif.p[3] = light->getDiffuse().getAlphaC();

      sl.spc.p[0] = light->getSpecular().getRedC();
      sl.spc.p[1] = light->getSpecular().getGreenC();
      sl.spc.p[2] = light->getSpecular().getBlueC();
      sl.spc.p[3] = light->getSpecular().getAlphaC();

      sl.pos.p[0] = light->getPos()(0);
      sl.pos.p[1] = light->getPos()(1);
      sl.pos.p[2] = light->getPos()(2);
      sl.pos.p[3] = 1.0f;

      sl.dir.p[0] = light->getDir()(0);
      sl.dir.p[1] = light->getDir()(1);
      sl.dir.p[2] = light->getDir()(2);

      sl.spot_cut = light->getCutOff().getDeg();
      sl.spot_exp = light->getExponent();

      lights.push_back(sl);
      light_ids.push_back(light->getLightName());
    }

//    std::reverse( lights.begin(), lights.end() );
//    std::reverse( light_ids.begin(), light_ids.end() );

//    GL::OGL::resetLightBuffer( header, light_ids, lights );

    _lights_ubo.bufferData( sizeof(GL::GLVector<4,GLuint>) + lights.size() * sizeof(GL::GLLight),
                                  0x0, GL_DYNAMIC_DRAW );
    _lights_ubo.bufferSubData( 0, sizeof(GL::GLVector<4,GLuint>), &header );
    _lights_ubo.bufferSubData( sizeof(GL::GLVector<4,GLuint>), sizeof(GL::GLLight) * lights.size(), &lights[0] );

    std::cout << "Updating light UBO!" << std::endl;
    std::cout << "  - Sun(s):             " << header.p[0] << std::endl;
    std::cout << "  - Point Light(s):     " << header.p[1] - header.p[0] << std::endl;
    std::cout << "  - Spot Light(s):      " << header.p[2] - header.p[1] << std::endl;
    std::cout << "  --------------------" << std::endl;
    std::cout << "  - Total nr of Lights: "<< header.p[3] << std::endl;

  }

  void Scene::init() {

    _timer_active   = true;
    _timer_time_scale    = 1;
    _timer_time_elapsed  = 0;
    _timer_fixed_dt_enabled = false;
    _timer_fixed_dt = 0.25;

    _lights_ubo.acquire("lights_ubo");
    _sun = 0x0;

    _running = false;
  }

  const Array<Camera*>& Scene::getCameras() const {

    return _cameras;
  }


} // END namespace GMlib







