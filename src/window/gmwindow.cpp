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



namespace GMlib {



  /*! void View::_find(int x, int y, Camera*& cam, Array<ViewBorder*>& borders)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void View::_find(int x, int y, Camera*& cam, Array<ViewBorder*>& borders) {

    if( _border ) _border->_find( x, y, cam, borders );
    else
    {
      int w1, w2, h1, h2;
      _camera->getViewport( w1, w2, h1, h2 );
      if( x >= w1 && x <= w2 && y >= h1 && y <= h2 ) cam=_camera;
    }
  }


  /*! void View::_prepare(int x1, int y1, int x2, int y2, Array<ViewBorder*>& borders)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void View::_prepare(int x1, int y1, int x2, int y2, Array<ViewBorder*>& borders) {

    if( _camera )
      _camera->reshape( x1, y1, x2, y2 );
    else
      _border->_prepare( x1, y1, x2, y2, borders );
  }


  /*! void View::_removeCamera(Camera* cam)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void View::_removeCamera(Camera* cam) {

    if( _border ) {

      View* view = _border->_hasCamera( cam );
      if( view ) {

        ViewBorder* border = _border;
        (*this) = (*view);
        delete border;
      }
      else _border->_removeCamera(cam);
    }
  }


  /*! void View::_splitCamera(Camera* cam_to_split, Camera* new_cam, bool split_vertically, double d)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   *	Recurciv seek to find object to split
   */
  void View::_splitCamera(Camera* cam_to_split, Camera* new_cam, bool split_vertically, double d) {

    if(_camera == cam_to_split)
      _split( new_cam, split_vertically, d );
    else if(_border)
      _border->_splitCamera( cam_to_split, new_cam, split_vertically, d );
  }

  /*! ViewSet::ViewSet(Camera* cam)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  ViewSet::ViewSet(Camera* cam) : _root(cam) {

    if(cam)	_cameras += cam;
    _border_color = GMcolor::White;
  }


  /*! ViewSet::ViewSet(const ViewSet& viewset)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  ViewSet::ViewSet(const ViewSet& viewset) {

    int i;
    _cameras = viewset._cameras;
    _vp_w = viewset._vp_w;
    _vp_h = viewset._vp_h;
    _border_color = viewset._border_color;
    _root = viewset._root;
    for( i = 0; i < viewset._borders.getSize(); i++)
      _borders += new ViewBorder( *( viewset._borders(i)) );
    _root._corr( _borders ,viewset._borders );
    for( i = 0; i < _borders.getSize(); i++ )
      _borders[i]->_corr( _borders, viewset._borders );
    prepare(_vp_w, _vp_h );
  }


  /*! ViewSet::~ViewSet()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  ViewSet::~ViewSet() {

    for(int i=0; i<_borders.getSize(); i++)	delete _borders[i];
  }


  /*! ViewSet& ViewSet::operator=(const ViewSet& viewset)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  ViewSet& ViewSet::operator=(const ViewSet& viewset) {

    int i;
    for(i=0; i<_borders.size(); i++) delete _borders[i];
    _borders.resetSize();
    _cameras = viewset._cameras;
    _vp_w = viewset._vp_w;
    _vp_h = viewset._vp_h;
    _border_color = viewset._border_color;
    _root = viewset._root;
    for(i=0; i<viewset._borders.getSize(); i++)
      _borders += new ViewBorder(*(viewset._borders(i)));
    for(i=0; i<_borders.getSize(); i++)
      _borders[i]->_corr(_borders, viewset._borders);
    _root._corr( _borders, viewset._borders);
    prepare( _vp_w, _vp_h);
    return *this;
  }


  /*! void ViewSet::_drawCamera(bool stereo)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void ViewSet::_drawCamera(bool stereo) {

    _drawBorder();
    for( int i = 0; i < _cameras.getSize(); i++ )
      _cameras[i]->go( stereo );
  }


  /*! bool ViewSet::_find(int x, int y, Camera*& cam)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   *
   *	\param[in] x
   *	\param[in] y
   *	\param[out] cam
   *	\return Status result of the search.
   */
  bool ViewSet::_find(int x, int y, Camera*& cam) {

    cam = 0;
    _selected_borders.resetSize();
    _root._find( x, y, cam, _selected_borders);

    if( _selected_borders.getSize() >0 )
      return false;

    return true;
  }


  /*! int ViewSet::getSize()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  int ViewSet::getSize() {

    return _cameras.getSize();
  }


  /*! void ViewSet::_reset()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void ViewSet::_reset() {

    _selected_borders.resetSize();
  }


  /*! void ViewSet::_setBorderColor(const Color& bc)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void ViewSet::_setBorderColor(const Color& bc) {

    _border_color = bc;
  }


  /*! Camera* ViewSet::operator[](int i)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  Camera* ViewSet::operator[](int i) {

    return _cameras[i];
  }

  /*! GMWindow::GMWindow()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  GMWindow::GMWindow() {

    _stereo	= false;
    _running = false;
    _isbig	 = false;
    _target  = NULL;
    _sun	 = NULL;
    _move	 = 0.0;
    _active_cam = 0;
    stop();
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

    OGL::cleanUp();
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
    light->enable();

    SceneObject* obj = dynamic_cast<SceneObject*>(light);

    if(insert_in_scene && obj)
      insert(obj);
  }


  /*! void GMWindow::popViewSet(int i)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void GMWindow::popViewSet(int i) {

    _view_set_stack.back()._removeCamera(i);
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
      light->disable();

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


  /*! void GMWindow::setViewSet(int new_c, int old_c, bool split_vertically, double d)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void GMWindow::setViewSet(int new_c, int old_c, bool split_vertically, double d) {

    if(new_c<1 || new_c>=_cameras.getSize() || old_c <1 || old_c>=_cameras.getSize() || d<=0 || d>=1) {

      return;
    }
    if(_default_only) {

      _view_set_stack += ViewSet(_cameras[new_c]);
      _default_only = false;
    }
    else
      _view_set_stack.back()._insertCamera(_cameras[old_c],_cameras[new_c], split_vertically,d);

    _view_set_stack.back().prepare(_w,_h);
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
    _default_only = true;
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
