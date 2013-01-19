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



/*! \file gmwindow.h
 *
 *  Interface for the Window and "Camera" View classes.
 */


#ifndef __gmWINDOW_H__
#define __gmWINDOW_H__


// local
#include "gmview.h"
#include "gmviewset.h"

// gmlib
#include <scene/camera/gmcamera.h>
#include <scene/render/gmrendermanager.h>

// gmlib::scene - might be removed as light and is implemented with different mechanisms...
#include <scene/light/gmlight.h>
#include <scene/light/gmsun.h>
#include <scene/light/gmspotlight.h>
#include <scene/light/gmpointlight.h>

// stl
#include <iostream>

namespace GMlib {


  /* \class GMWindow gmWindow.h <gmWindow>
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  class GMWindow : public Scene {
  public:
    GMWindow( bool init_default_cam = true );
    GMWindow(const GMWindow&);

    virtual ~GMWindow();


    void                    addToViewSet( int cam_idx, int split_cam_idx, bool split_vertically=true, double d=0.5 );
    void                    addViewSet( int cam_idx );
    virtual void            clearScene();
    Camera*                 findCamera( int x, int y );
    Camera*                 findCamera( const Vector<int,2>& pos );
    int                     getCameraIndex( Camera* cam ) const;
    const Color&            getClearColor() const;
    const Color&            getSelectColor() const;
    int                     getViewportHeight() const;
    int                     getViewportWidth() const;
    int                     getViewSetStackSize() const;
    void                    insertCamera(Camera* cam, bool insert_in_scene = false);

    void                    insertLight(Light* light, bool insert_in_scene = false);
    void                    insertSun();
    bool                    isRunning() const;
    bool                    isStereoEnabled() const;
    void                    moveBorder(int x, int y);
    void                    popView(int cam_idx);
    void                    popViewSet();
    void                    prepareViewSets();

    bool                    removeCamera(Camera * cam);
    bool                    removeLight(Light* light);
    void                    removeSun();
    void                    reset();

    void                    scaleDayLight(double d);
    void                    setClearColor( const Color& color );
    void                    setSelectColor( const Color& color );
    void                    setSunDirection(Angle d);


    virtual bool            toggleRun();
    bool                    toggleStereo();


    GMWindow&               operator=(const GMWindow& gw);



  protected:

    // Cameras light and sun
    Array<Camera*>	        _cameras;
    Array<Light*>	          _lights;
    Sun*			              _sun;

    // Viewport size
    int				              _w;
    int                     _h;					// GMWindow size in viewport coordinates.


    Array<ViewSet>          _view_set_stack;  /// Active camera set

    // index of active camera, old/previous x and y mouse positions
    int				              _active_cam;

    double					        _move;


    bool                    find(int x, int y, int& index);
    virtual void            message( const std::string& str);
    virtual void            message( SceneObject* d);
    virtual void            message( Point<float,3>& p);

    void                    display();

  public:
    virtual void            init();

  protected:
    void                    reshape(int w, int h);

  private:
    bool			              _stereo;

    SceneObject*	          _target;		/// NB!!!! take a look at this variable not used proper today.....
    bool			              _running;		/// Used to stor the state of simulation while mouse/keboard temporary turn off simulation
    bool			              _isbig;			/// State of one window functionality have been used (see _mouseDoubleClick on right knob)



    void            updateLightUBO();

  public:

    SceneObject*            findSelectObject( Camera* cam, const Vector<int,2>& pos, int type_id ) const;
    SceneObject*            findSelectObject( Camera* cam, int x, int y, int type_id ) const;



  }; // END class GMWindow





















  inline
  Camera* GMWindow::findCamera( int x, int y ) {

    int i;
    find( x, y, i );
    if( i > 0 )
      return _cameras[i];

    return 0x0;
  }

  inline
  Camera* GMWindow::findCamera( const Vector<int,2>& pos ) {

    return findCamera( pos(0), pos(1) );
  }

  inline
  const Color& GMWindow::getClearColor() const {

    return getRenderManager()->getClearColor();
  }

  inline
  int GMWindow::getCameraIndex( Camera* cam ) const {

    if( !_cameras.exist( cam ) )
      return -1;

    return _cameras.index( cam );
  }

  inline
  int GMWindow::getViewportHeight() const {

    return _h;
  }

  inline
  int GMWindow::getViewportWidth() const {

    return _w;
  }

  inline
  int GMWindow::getViewSetStackSize() const {

    return _view_set_stack.getSize();
  }


  /*! void GMWindow::insertSun()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void GMWindow::insertSun() {

    _sun = new Sun();
    updateLightUBO();
  }


  inline
  bool GMWindow::isRunning() const {

    return _running;
  }


  /*! bool GMWindow::isStereoEnabled()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  bool GMWindow::isStereoEnabled() const {

    return _stereo;
  }

  inline
  void GMWindow::prepareViewSets() {

    _view_set_stack.back().prepare( _w, _h );
    _view_set_stack.back().prepareGraphics();
  }

  /*! void GMWindow::removeSun()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void GMWindow::removeSun() {

    if(_sun) {

      delete _sun;
      _sun = NULL;

      updateLightUBO();
    }
  }


  /*! void GMWindow::reset()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void GMWindow::reset() {

    init();
  }


  /*! void GMWindow::setSunDirection(Angle d)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void GMWindow::setSunDirection(Angle d) {

    if(_sun)
      _sun->rotateGlobal(d,Vector3D<float>(1.0,1.0,0.0));
  }

  /*! void GMWindow::display(void)
   *	\brief	Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void GMWindow::display() {

    if( _active_cam > -1 )
      _cameras[_active_cam]->move(_move);

//    simulate();
//    prepare();
//    if(_stereo) {

//      glDrawBuffer(GL_BACK_LEFT);
//      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//      _view_set_stack.back()._drawCamera();
//      swapBuffers();
//      glDrawBuffer(GL_BACK_RIGHT);
//      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//      _view_set_stack.back()._drawCamera(true);
//    }
//    else {

//      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//      GL::OGL::clearRenderBuffer();
//      GL::OGL::bindRenderBuffer();
//      _view_set_stack.back().drawCamera();
//      GL::OGL::unbindRenderBuffer();

    RenderManager *rm = getRenderManager();
    rm->render( _view_set_stack.back().getCameras() );
  }


  /*! void GMWindow::reshape(int w, int h)
   *	\brief	Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void GMWindow::reshape(int w, int h) {

    _w = w; _h = h;
    prepareViewSets();

    getRenderManager()->resize( _w, _h );
  }


  /*! void GMWindow::message( const std::string& str)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void GMWindow::message( const std::string& /* str */ ) {}


  /*! void GMWindow::message( SceneObject* d)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void GMWindow::message( SceneObject* /* obj */ ) {}


  /*! void GMWindow::message( Point<float,3>& p)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void GMWindow::message( Point<float,3>& /* p */ ) {}


  /*! bool GMWindow::find(int x, int y, int& index)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  bool GMWindow::find(int x, int y, int& index) {

    if(x<0 || x>_w || y<0 || y>_h)		// Outside window
    {
      index = 0;
      _view_set_stack.back().reset();
      return false;
    }

    Camera* cam;
    if(_view_set_stack.back().find(x,y,cam))		// Camera found
    {
      index = _cameras.index(cam);
      return true;
    }
    else								// border found
    {
      index = -1;
      return false;
    }
  }


  /*! void GMWindow::moveBorder(int x, int y)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void GMWindow::moveBorder(int x, int y) {

    if(x>0 && x <_w && y>0 && y<_h)
      (_view_set_stack.back()).moveBorder(x,y);
  }

} // END namespace GMlib



#endif // __gmWINDOW_H__
