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

//#include "gmGLSL.h"
#include "gmScene.h"
#include "gmSceneObject.h"
#include "gmLight.h"
#include "gmCamera.h"


namespace GMlib {



  /*! Scene::Scene()
   *  \brief Pending Documentation
   *
   *  Default constructor
   */
  Scene::Scene() : _scene(), _disp_objs(128), _matrix_stack(32) {

    _timer_active   = true;
    _timer_time_scale    = 1;
    _timer_time_elapsed  = 0;
    _matrix_stack    += HqMatrix<float,3>();
  }


  /*! Scene::Scene( SceneObject* obj )
   *  \brief Pending Documentation
   *
   *  Standar constructor
   */
  Scene::Scene( SceneObject* obj ) : _scene(), _disp_objs(128), _matrix_stack(32) {
    _scene += obj;
    _timer_active = true;
    _timer_time_scale = 1;
    _timer_time_elapsed  = 0;
    _matrix_stack += HqMatrix<float,3>();
  }


  /*! Scene::Scene( const Scene&  s )
   *  \brief Pending Documentation
   *
   *  Copy constructor
   */
  Scene::Scene( const Scene&  s ) : _scene(s._scene),_disp_objs(s._disp_objs),_matrix_stack(s._matrix_stack) {

    _timer_active   = true;
    _timer_time_scale    = 1;
    _timer_time_elapsed  = 0;
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


  /*! int Scene::getSize()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  int Scene::getSize() {

    return _scene.getSize();
  }


  /*! int Scene::getSizeTotal()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  int Scene::getSizeTotal() {

    return _disp_objs.getSize();
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
      no_disp_obj += _scene[i]->_prepare( _lights, _matrix_stack, this );

    if( _disp_objs.getMaxSize() < no_disp_obj )
      _disp_objs.setMaxSize( no_disp_obj );
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


  /*! SceneObject* Scene::operator()(int i)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  SceneObject* Scene::operator()(int i) {

    return _disp_objs[i];
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

    return *this;
  }

  bool Scene::isSelected(SceneObject *obj) const {

    return _sel_objs.exist( obj );
  }

  void Scene::removeSelections() {

    int no_objs = _sel_objs.getSize();

    // Remove Selections
    for( int i = 0; i < no_objs; i++ )
        _sel_objs[i]->setSelected( false );

    // Pop all array elements
//    _sel_objs.setSize(0);
    for( int i = 0; i < no_objs; i++ )
      _sel_objs.pop();
  }

  void Scene::setSelection( SceneObject* obj, bool selected ) {

    obj->setSelected( selected );
    if( selected )
      _sel_objs.insert( obj );
    else
      _sel_objs.remove( obj );
  }

  void Scene::setSingleSelection( SceneObject* obj ) {

    removeSelections();
    setSelection( obj, true );
  }

  void Scene::toggleSelection( SceneObject *obj ) {

    setSelection( obj, !isSelected(obj) );
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

    double dt = _timer_time_scale * _timer.getSec(true);

    if(dt) {

      _timer_time_elapsed  += dt;
      for( int i=0; i< _scene.getSize(); i++ )
        _scene[i]->simulate(dt);
    }
  }


  /*! bool Scene::isVisible( SceneObject* obj )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  bool Scene::isVisible( SceneObject* obj ) {

    return _disp_objs.exist( obj );
  }





  /*! void Scene::_lighting()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void Scene::_lighting() {

    for( int i=0; i < _lights.getSize(); i++ )
      _lights[i]->lighting();
  }


  /*! void Scene::_display()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void Scene::_display( bool blend_sorted, Camera* cam ) {

    for( int i = 0; i < _disp_objs.getSize(); i++ )
      _disp_objs[i]->_display( cam );

//    glDisable( GL_BLEND );

//    if( !blend_sorted ) {

//      for( int i = 0; i < _disp_objs.getSize(); i++ )
//        _disp_objs[i]->_display( cam );
//    }
//    else {

//      for( int i = 0; i < _disp_opaque.getSize(); i++ )
//        _disp_opaque[i].getObject()->_display( cam );

//      glEnable( GL_BLEND );
//      for( int i = 0; i < _disp_translucent.getSize(); i++ ) {
//        _disp_translucent[i].getObject()->_display( cam );
//      }
//    }
  }

  /*! void Scene::_select( int type_id, Camera* cam )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void Scene::_select( int type_id, Camera* cam ) {

    for( int i=0; i < _disp_objs.getSize(); i++ )
      _disp_objs[i]->_select( type_id, cam );
  }


  /*! void Scene::_culling( const Frustum& f )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  Culling of light is now possible
   */
  void Scene::_culling( const Frustum& f, bool on ) {

    int i;
    _disp_objs.resetSize();

    if( on )
      for( i = 0; i < _scene.getSize(); i++ )
        _scene[i]->culling( _disp_objs, f );
    else
      for( i = 0; i < _scene.getSize(); i++ )
        _scene[i]->_fillObj( _disp_objs );
  }


  void Scene::_blending( Camera *cam ) {

    _disp_opaque.resetSize();
    _disp_translucent.resetSize();

    for( int i = 0; i < _disp_objs.getSize(); i++ ) {

      const double dto = cam->getDistanceToObject( _disp_objs[i]);
      if( _disp_objs[i]->isOpaque() )
        _disp_opaque += SortObject<SceneObject*,float>(_disp_objs[i], dto );
      else
        _disp_translucent += SortObject<SceneObject*,float>(_disp_objs[i], dto );
    }

    // Sort opaque objects front to back
    _disp_opaque.sort();

    // Sort translucent objects back to front
    _disp_translucent.sort();
    _disp_translucent.reverse();
  }


} // END namespace GMlib






