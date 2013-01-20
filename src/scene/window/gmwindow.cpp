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
 *	\brief Pending Description
 */


#include "gmwindow.h"

// gmlib
#include <core/containers/gmdvector.h>

// stl
#include <cstdio>
#include <iostream>


namespace GMlib {




  /*! GMWindow::GMWindow()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  GMWindow::GMWindow(bool init_default_cam) {

    _stereo	= false;
    _running = false;
    _isbig	 = false;
    _target  = NULL;
    _sun	 = NULL;
    _move	 = 0.0;
    _active_cam = 0;
    stop();

    if( init_default_cam ) {

      Point3D<float> init_cam_pos(  0.0f, 0.0f, 0.0f );
      Vector3D<float> init_cam_dir( 0.0f, 1.0f, 0.0f );
      Vector3D<float> init_cam_up(  0.0f, 0.0f, 1.0f );

      Camera *cam = new Camera( init_cam_pos, init_cam_dir, init_cam_up );
      insertCamera( cam );
      addViewSet( getCameraIndex(cam) );
    }

    initRenderManager();
  }


  /*! GMWindow::GMWindow(const GMWindow&)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  GMWindow::GMWindow( const GMWindow& gw ) : Scene() {

    (*this) = gw;
  }


  /*! GMWindow::~GMWindow()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
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

    GL::OGL::cleanUp();
  }


  void GMWindow::addViewSet( int cam_idx ) {

    if( cam_idx < 1 || cam_idx >= _cameras.getSize() )
      return;

    _view_set_stack += ViewSet(_cameras[cam_idx]);
  }


  /*! void GMWindow::setViewSet(int new_c, int old_c, bool split_vertically, double d)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
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

    //_rotation_object  = 0x0;
    //_locked_object    = 0x0

    Array<SceneObject*> rmobjs;
    for( int i = 0; i < getSize(); i++ )
      rmobjs += operator[](i);

    for( int i = 0; i < rmobjs.getSize(); i++ ) {

      Camera* cam   = dynamic_cast<Camera*>( rmobjs[i] );
      Light* light  = dynamic_cast<Light*>( rmobjs[i] );

      if( cam )
        removeCamera( cam );
      else if( light )
        removeLight( light );
      else
        remove( rmobjs[i] );

      delete rmobjs[i];
    }

    if( _running )
      Scene::start();
  }

  const Color& GMWindow::getSelectColor() const {

    return getRenderManager()->getSelectColor();
  }

  /*! void GMWindow::insertCamera(Camera* cam, bool insert_in_scene)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void GMWindow::insertCamera(Camera* cam, bool insert_in_scene) {

    cam->setScene(this);
    _cameras += cam;
    if(insert_in_scene)	insert(cam);
  }


  /*! void GMWindow::insertLight(Light* light, bool insert_in_scene)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void GMWindow::insertLight(Light* light, bool insert_in_scene) {

    _lights += light;

    SceneObject* obj = dynamic_cast<SceneObject*>(light);

    if(insert_in_scene && obj)
      insert(obj);

    updateLightUBO();
  }


  /*! void GMWindow::popViewSet(int i)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void GMWindow::popView(int cam_idx) {

    _view_set_stack.back().removeCamera(cam_idx);
  }


  void GMWindow::popViewSet() {

    if( getViewSetStackSize() > 2 )
      _view_set_stack.pop();
  }


  /*! bool GMWindow::removeCamera(Camera *)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
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
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  bool GMWindow::removeLight(Light* light) {

    int i = _lights.getIndex(light);
    if(i>=0)
    {
      SceneObject* obj = dynamic_cast<SceneObject*>(light);

      if(obj)
        remove(obj);

      _lights.removeIndex(i);

      updateLightUBO();

      return true;
    }
    return false;
  }


  /*! void GMWindow::scaleDayLight(double)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
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


  /*! bool GMWindow::toggleStereo()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  bool GMWindow::toggleStereo() {

    _stereo = !_stereo;
    return _stereo;
  }

  void GMWindow::updateLightUBO() {

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
    header.p[1] = _sun ? 1 : 0;
    header.p[2] = point_lights.size();
    header.p[3] = spot_lights.size();
    header.p[0] = header.p[1] + header.p[2] + header.p[3];

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

    GL::OGL::resetLightBuffer( header, light_ids, lights );

    std::cout << "Updating light UBO!" << std::endl;
    std::cout << "  - Sun(s):             " << header.p[1] << std::endl;
    std::cout << "  - Point Light(s):     " << header.p[2] << std::endl;
    std::cout << "  - Spot Light(s):      " << header.p[3] << std::endl;
    std::cout << "  --------------------" << std::endl;
    std::cout << "  - Total nr of Lights: "<< header.p[0] << std::endl;

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
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  GMWindow& GMWindow::operator=(const GMWindow& gw) {

    Scene::operator=(gw);
    _cameras	= gw._cameras;
    _lights	= gw._lights;
    _sun	= gw._sun;
    for(int i=0; i<_cameras.getSize(); i++)
      _cameras[i]->setScene(this);

    _stereo	= false;
    _running = false;
    _isbig	 = false;
    _sel_objs.clear();
    _view_set_stack = gw._view_set_stack;				// Active camera set
    reshape(_w,_h);
    return *this;
  }



  #ifndef GL_MULTISAMPLE
  #define GL_MULTISAMPLE  0x809D
  #endif
  /*! void GMWindow::init()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void GMWindow::init() {

//    cout << "GMWindow::init()" << endl;

    if(_sun)
      _sun->scaleDayLight(1.0);
    insertCamera(new Camera(Point3D<float>(10,10,5),Point3D<float>(-10,-10,-5),Vector3D<float>(0,0,-1)));
    _view_set_stack += ViewSet(_cameras[0]);
    _view_set_stack.back().prepare(_w,_h);
    int numberoflights;
    glGetIntegerv(GL_MAX_LIGHTS,&numberoflights);
    char s[32];
    std::sprintf( s, "Max number of lights %d\n", numberoflights );
    message(s);
    //char *extensions = NULL;
      //extensions = (char *)glGetString(GL_EXTENSIONS);
      //_message(extensions);
  }


  /*! bool GMWindow::toggleRun()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  bool GMWindow::toggleRun() {

    if( ( _running = !_running ) )
      start();
    else
      stop();

    return _running;
  }

} // END namespace GMlib
