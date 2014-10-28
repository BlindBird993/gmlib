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



/*! \file gmcamera.h
 *
 *  Interface for the Camera class.
 *  \todo
 *  - Translate the already documented parts into English
 */


#ifndef __gmCAMERA_H__
#define __gmCAMERA_H__

#include "../gmdisplayobject.h"
#include "../gmscene.h"

// gmlib
#include <core/utils/gmstream.h>

// stl
#include <iostream>




namespace GMlib {



  class Renderer;
  class SelectRenderer;



  /*!  \class Camera gmcamera.h <gmCamera>
   *  \brief  The Camera class
   *
   *  Inneholder:
   *    privat;
   *        Et navn for identifikasjon i select funksjonaliteten.
   *        To matriser for lokal transformasjon av objektet.
   *        En Omsluttende kule til objektet som må lages.
   *        En array av pekere til alle sub-objektene til dette objektet
   *    public:
   *        Konstuktør med mulige default verdier og sletter
   *        En display funksjon for displaying av objektet.
   *        En select funksjon for plukking(select) av objektet med mus.
   *        En simulate funksjon for at objektet kan bevege subobjekter.
   *        En find funksjon for å finne en funksjon med et gitt navn.
   *        En rotate, scale og translate funksjon for å
   *           posisjonere objektet relativt i forhold til morsobjektet
   *    protected:
   *        Det er to virtuelle funksjoner localDisplay og localSelect
   *          som alle avledede klasser må ha sin versjon av.
   *        Arbeidsdelingen er slik at display og select foretar
   *          transformasjonen lagret i matrix, og displayer alle
   *          sub-objektene til objektet. Men etter transformasjonen
   *          og før sub-objektene displayes kalles localDisplay
   *          (eventuelt localSelect). I localDisplay kan en så
   *          displaye det som ikke displayes i sub-objektene og/eller
   *          foreta transformasjoner av sub-objekter for
   *          å simulere bevegelser.
   *        Det er også en insert-funksjon som avledede klasser
   *            kan bruke for å lage sub-objekt. Hvis en avledet klasse
   *          trenger tilgang til et objekt for bevegelsessimulering
   *          bør den lage en egen peker for det.
   */
  class Camera : public DisplayObject {
    GM_SCENEOBJECT(Camera)
  public:
    Camera( Scene& s = _default_scene );
    Camera( Scene* s );

    Camera( const Point<float,3>&  pos,
            const Point<float,3>&  look_at_pos);

    Camera( const Point<float,3>&  pos,
            const Vector<float,3>& dir,
            const Vector<float,3>& up,
            float zoom=1);

    virtual ~Camera();

    SceneObject*                findSelectObject(int, int, int type_id=0);
//    SceneObject*                findSelectObject( const Vector<int,2>& pos, int type_id=0);
//    Array<SceneObject* >        findSelectObjects(int xmin, int ymin, int xmax, int ymax, int type_id=0);

    HqMatrix<float,3>&          getMatrix();
    const HqMatrix<float,3>&    getMatrix() const;
    const HqMatrix<float,3>&    getProjectionMatrix() const;
    Arrow<int,2>                getViewport() const;
    void                        getViewport(int& w1, int& w2, int& h1, int& h2) const;
    int                         getViewportW() const;
    int                         getViewportH() const;

//    virtual void                go(bool stereo=false);  // Running the Camera.

    bool                        isCoordSysVisible() const;
    void                        setCoordSysVisible(bool visible=true);


    virtual double              deltaTranslate(DisplayObject * obj);
    double                      getDistanceToObject(int, int);
    double                      getDistanceToObject(SceneObject* obj);
    virtual SceneObject*        lockTargetAtPixel(int,int);

    bool                        isCulling() const;
    void                        enableCulling( bool enable = true );

    void                        decreaseEyeDist(double delta=0.01);
    void                        decreaseFocalDist(double delta=1);
    float                       getRatio() const;
    void                        increaseEyeDist(double delta=0.01);
    void                        increaseFocalDist(double delta=1);
    float                       getNearPlane() const;
    void                        setCuttingPlanes(float near_plane, float far_plane);
    void                        setEyeDist(double eye_dist=0.08);
    float                       getAngleTan() const;
    float                       getFarPlane() const;
    float                       getFocalLength() const;
    void                        setFocalDist(double focal=50.0);

    const Frustum&              getFrustum() const;
    void                        setFrustumVisible(bool visible=true);
    bool                        isFrustumVisible() const;

    void                        setScene(Scene& s);
    void                        setScene(Scene *s);
    virtual void                zoom(float z);


    void                        reset();            // To be used when changing Camera.
    virtual void                reshape(int x1, int y1, int x2, int y2);    // To be used when changing size of window
    void                        updateCameraOrientation();

//  protected:
  public:
    float                       _near_plane;
    float                       _far_plane;
    float                       _ratio;

    Frustum                     _frustum;

    void                        basisChange( const Vector<float,3>& x,
                                             const Vector<float,3>& y,
                                             const Vector<float,3>& z,
                                             const Vector<float,3>& p);

//    virtual void                display();
    virtual  void               drawActiveCam();
    SceneObject*                find(unsigned int name);
    virtual void                makeGraphics();
    void                        resetC(float z = 1);
//    void                        select(int type_id);
    virtual void                setPerspective();

    // *****************
    // Virtual functions
    // from SceneObject
    void                        localDisplay();
    void                        localSelect();


//  private:
    static Scene                _default_scene;
    static unsigned int         _display_list;

    Scene*                      _scene;
    int                         _x,_y,_w,_h;          // Viewport position and size.

    bool                        _coord_sys_visible;
    bool                        _frustum_visible;

    double                      _focal_length;
    double                      _eye_dist;
    double                      _ed_fd;
    float                       _angle_tan;

    bool                        _culling;



  public:
    void    switchToLeftEye() { basisChange( _side, _up, _dir, _pos ); }

    void    switchToRightEye() {

      Point<float,3>         tmp_pos  = _pos  - _eye_dist*_side;
      UnitVector<float,3>    tmp_dir  = _dir  + _ed_fd*_side; //tmp_dir  = _pos + _focus_dist*_dir - tmp_pos;
      UnitVector<float,3>    tmp_side = _side - _ed_fd*_dir;  //tmp_side = _up^tmp_dir;
      basisChange(tmp_side, _up, tmp_dir, tmp_pos);            // Change to right eye
    }

    virtual
    void                        setupDisplay();
    void                        applyViewport() const;

  }; // END class Camera









  /*! void Camera::basisChange(const Vector<float,3>& x, const Vector<float,3>& y, const Vector<float,3>& z, const Vector<float,3>& p)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Camera::basisChange( const Vector<float,3>& x,
                            const Vector<float,3>& y,
                            const Vector<float,3>& z,
                            const Vector<float,3>& p ) {

    static Vector<float,4> nx, ny, nz, nw(0.0f);
    nx = -x;
    ny =  y;
    nz = -z;

    nx[3] = x*p;
    ny[3] = -(y*p);
    nz[3] = z*p;
    nw[3] = 1.0f;

    _matrix.setRow( nx, 0 );
    _matrix.setRow( ny, 1 );
    _matrix.setRow( nz, 2 );
    _matrix.setRow( nw, 3 );
  }


  /*! void Camera::decreaseEyeDist(double delta)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Camera::decreaseEyeDist(double delta) {

    _eye_dist-=delta;
    _ed_fd=_eye_dist/_focal_length;
  }


  /*! void Camera::decreaseFocalDist(double delta)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Camera::decreaseFocalDist(double delta) {

    increaseFocalDist(-delta);
  }


//  /*! void Camera::display()
//   *  \brief Pending Documentation
//   *
//   *  Pending Documentation
//   */
//  inline
//  void Camera::display() {

//    setupDisplay();

//    // Cull the scene using the camera's frustum
//    _scene->culling( _frustum, _culling );

//    // Render scene
//    _scene->display( this );

//    if(_coord_sys_visible)
//      drawActiveCam();
//  }

  inline
  void Camera::setupDisplay() {

    setPerspective();
  }


  /*! void Camera::drawActiveCam()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Camera::drawActiveCam() {

    float hh = -1.5*_near_plane*_angle_tan;
    Point<float,3> cp(_ratio*hh, hh, -_near_plane-1.0);


    /*! \todo check if this is correct and fix if not */
//    cp = _matrix_scene * cp;
//    cp = getMatrix() * cp;

//  //  GLboolean lg;
//  //  glGetBooleanv(GL_LIGHTING,&lg);
//  //  if(lg) glDisable(GL_LIGHTING);
//    glPushAttrib( GL_LIGHTING );
//    glDisable( GL_LIGHTING );
//    glBegin(GL_LINES); // draw Coordsys
//      glColor( GMcolor::Red );  glPoint(cp); glPoint(cp+Vector<float,3>(0.1,0,0));
//      glColor( GMcolor::Green );  glPoint(cp); glPoint(cp+Vector<float,3>(0,0.1,0));
//      glColor( GMcolor::Blue );  glPoint(cp); glPoint(cp+Vector<float,3>(0,0,0.1));
//    glEnd();
//    if(_locked && ! _lock_object)
//    {
//      glPushMatrix();
//      glTranslate(_lock_pos);
//      glCallList(_display_list+8);
//      glPopMatrix();
//    }
//    glPopAttrib();
//  //  if (lg) glEnable(GL_LIGHTING);






    // NEW CODE //



//    HqMatrix<float,3> mat;
//    mat[0][3] = cp[0];
//    mat[1][3] = cp[1];
//    mat[2][3] = cp[2];


//    HqMatrix<float,3> proj_mat = getProjectionMatrix();


//    HqMatrix<float,3> mv_mat = _matrix_scene_inv * _matrix * mat;


//    HqMatrix<float,3> mvpmat = proj_mat * this->SceneObject::getMatrix() * this->_matrix_scene;




//    std::cout << "mat:" << std::endl;
//    for( int i = 0; i < 4; i++ ) {
//      for( int j = 0; j < 4; j++ ) {

//        std::cout << mat[i][j] << "  ";
//      }
//      std::cout << std::endl;
//    }
//    std::cout << std::endl;

//    std::cout << "proj_mat:" << std::endl;
//    for( int i = 0; i < 4; i++ ) {
//      for( int j = 0; j < 4; j++ ) {

//        std::cout << proj_mat[i][j] << "  ";
//      }
//      std::cout << std::endl;
//    }
//    std::cout << std::endl;

//    std::cout << "mv_mat:" << std::endl;
//    for( int i = 0; i < 4; i++ ) {
//      for( int j = 0; j < 4; j++ ) {

//        std::cout << mv_mat[i][j] << "  ";
//      }
//      std::cout << std::endl;
//    }
//    std::cout << std::endl;




//    std::cout << "mvpmat:" << std::endl;
//    for( int i = 0; i < 4; i++ ) {
//      for( int j = 0; j < 4; j++ ) {

//        std::cout << mvpmat[i][j] << "  ";
//      }
//      std::cout << std::endl;
//    }
//    std::cout << std::endl;



//    GL::GLProgram prog( "color" );
//    GLBufferObject bo_qs( "std_rep_qs" );
//    GLBufferObject bo_q( "std_rep_q" );

//    prog.bind();

//    prog.setUniform( "u_mvpmat", mvpmat, 1, true );
//    prog.setUniform( "u_selected", false );


//    GLuint vert_loc = prog.getAttributeLocation( "in_vertex" );

//    prog.setUniform( "u_color", GMcolor::Red );
//    bo_qs.enableVertexArrayPointer( vert_loc, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0x0 );
//      glDrawArrays( GL_QUAD_STRIP, 0, 10 );
//    bo_qs.disableVertexArrayPointer( vert_loc );

//    prog.setUniform( "u_color", GMcolor::Blue );
//    bo_q.enableVertexArrayPointer( vert_loc, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0x0 );
//      glDrawArrays( GL_QUADS, 0, 8 );
//    bo_q.disableVertexArrayPointer( vert_loc );

//    prog.unbind();

//    std::cout << "Info:" << std::endl;
//    std::cout << " - vert_loc: " << vert_loc << std::endl;
//    std::cout << " - bo_qs ID: " << bo_qs.getId() << std::endl;
//    std::cout << " - bo_q  ID: " << bo_q.getId() << std::endl;
  }


  /*! void Camera::enableCulling( bool enable )
   *  \brief Enable or disable culling
   *
   *  Enable or disable Culling for this camera
   */
  inline
  void Camera::enableCulling( bool enable ) {

    _culling = enable;
  }


  /*! SceneObject* Camera::find(unsigned int name
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  SceneObject* Camera::find(unsigned int name) {

    return _scene->find(name);
  }


  /*! float Camera::getAngleTan() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  float Camera::getAngleTan() const {

    return _angle_tan;
  }


  /*! float Camera::getFarPlane() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  float Camera::getFarPlane() const  {

    return _far_plane;
  }

  /*! float Camera::getFocalLength() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  float Camera::getFocalLength() const {

    return _focal_length;
  }

  inline
  const Frustum &Camera::getFrustum() const {

    return _frustum;
  }


  /*! float Camera::getNearPlane() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  float Camera::getNearPlane() const {

    return _near_plane;
  }


  inline
  const HqMatrix<float,3>& Camera::getProjectionMatrix() const {

    return _frustum.getProjectionMatrix();
  }


  /*! float Camera::getRatio() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  float Camera::getRatio() const {

    return _ratio;
  }

  inline
  Arrow<int,2>
  Camera::getViewport() const {

    Arrow<int,2> vp;
    vp.setPos( Point<int,2>(_x,_y) );
    vp.setDir( Vector<int,2>(_w,_h) );
    return vp;
  }

  /*!
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Camera::getViewport(int& w1, int& w2, int& h1, int& h2) const {

    w1 = _x;
    h1 = _y;
    w2 = _x+_w;
    h2 = _y+_h;
  }


  /*! int Camera::getViewPortW() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  int Camera::getViewportW() const {

    return _w;
  }


  /*! int Camera::getViewPortH() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  int Camera::getViewportH() const {

    return _h;
  }


  /*! void Camera::increaseEyeDist(double delta)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Camera::increaseEyeDist(double delta) {

    _eye_dist+=delta;
    _ed_fd=_eye_dist/_focal_length;
  }


  /*! void Camera::increaseFocalDist(double delta)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Camera::increaseFocalDist(double delta) {

    setFocalDist(_focal_length+delta);
  }


  /*! bool Camera::isCoordSysVisible() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  bool Camera::isCoordSysVisible() const {

    return _coord_sys_visible;
  }


  /*! bool Camera::isCulling() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  bool Camera::isCulling() const {

    return _culling;
  }


  /*! bool Camera::isFrustumVisible() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  bool Camera::isFrustumVisible() const {

    return _frustum_visible;
  }


  /*! void Camera::reset()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  To be used when changing Camera.
   */
  inline
  void Camera::reset() {

    int  wp[4];
    glGetIntegerv(GL_VIEWPORT,wp);
    reshape(wp[0],wp[1],wp[2],wp[3]);
  }


  /*! void Camera::setCuttingPlanes(float near_plane, float far_plane)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Camera::setCuttingPlanes(float near_plane, float far_plane) {

    _near_plane = near_plane;
    _far_plane  = far_plane;
    _angle_tan  = 13.0f*_near_plane/_focal_length;
  }


  /*! void Camera::setCoordSysVisible(bool visible)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Camera::setCoordSysVisible(bool visible) {

    _coord_sys_visible=visible;
  }


  /*! void Camera::setEyeDist(double eye_dist)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Camera::setEyeDist(double eye_dist) {

    _eye_dist=eye_dist;
    _ed_fd=_eye_dist/_focal_length;
  }


  /*! void Camera::setFocalDist(double focal)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Camera::setFocalDist(double focal)  {

    _focal_length   = focal;
    _ed_fd      = _eye_dist/_focal_length;
    _angle_tan    = 13.0f*_near_plane/_focal_length;
  }


  /*! void Camera::setFrustumVisible(bool visible=true)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Camera::setFrustumVisible(bool visible) {

    _frustum_visible = visible;
  }


  /*! void Camera::setScene(Scene& s)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Camera::setScene(Scene& s) {

    _scene = &s;
  }


  /*! void Camera::setScene(Scene *s)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Camera::setScene(Scene *s) {

    _scene = s;
  }


  /*! void Camera::updateCameraOrientation()
   *    \brief Pending Documentation
   *
   *    Pending Documentation
   */
  inline
  void Camera::updateCameraOrientation() {

    if( _locked ) {

      updateOrientation( getSceneLockPos() );
      basisChange( _side, _up, _dir, _pos );
    }
  }


} // END namespace GMlib


#endif // __gmCAMERA_H__
