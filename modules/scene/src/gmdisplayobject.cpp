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



/*! \file gmdisplayobject.cpp
 *
 *  Implementation of the DisplayObject class.
 */

#include "gmdisplayobject.h"


#include "gmvisualizer.h"
#include "camera/gmcamera.h"


namespace GMlib {

  /*! DisplayObject::DisplayObject( const Point<float,3>&  pos, const Vector<float,3>& dir, const Vector<float,3>& up )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  DisplayObject::DisplayObject(
    const Point<float,3>&  pos,
    const Vector<float,3>& dir,
    const Vector<float,3>& up
  ) : SceneObject() {

    init();
    set( pos, dir, up );
  }


  /*! DisplayObject::DisplayObject( const Point<float,3>&  lockPos, const Point<float,3>&  pos, const Vector<float,3>& up )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  DisplayObject::DisplayObject(
    const Point<float,3>&  lock_pos,
    const Point<float,3>&  pos,
    const Vector<float,3>& up
  ) : SceneObject() {

    init();
    Vector<float,3> dir = up.getLinIndVec();
    set(pos,dir,up);
    _locked	= true;
    _lock_pos    = lock_pos;
  }


  /*! DisplayObject::DisplayObject( SceneObject* lockObject, const Point<float,3>&  pos, const Vector<float,3>& up )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  DisplayObject::DisplayObject(
    SceneObject* lock_object,
    const Point<float,3>&  pos,
    const Vector<float,3>& up
  ) : SceneObject() {

    init();
    Vector<float,3> dir = up.getLinIndVec();
    set( pos, dir, up );
    _locked	= true;
    _lock_object	= lock_object;
  }


  /*! DisplayObject::DisplayObject( const DisplayObject& s )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  DisplayObject::DisplayObject( const DisplayObject& copy )
    : SceneObject(copy)
  {

    set( copy._pos, copy._dir, copy._up );

    _locked       = copy._locked;
    _lock_object  = copy._lock_object;
    _lock_pos     = copy._lock_pos;
    _lighted      = copy._lighted;
    _opaque       = copy._opaque;
    _color        = copy._color;
    _material     = copy._material;
    _collapsed    = copy._collapsed;

  }


  /*! DisplayObject::~DisplayObject()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  DisplayObject::~DisplayObject() {}

  const HqMatrix<float,3>& DisplayObject::getModelViewMatrix( const Camera* cam, bool local_cs ) const {

    static HqMatrix<float,3> mv_mat;

    // Translate to scene coordinates
    mv_mat = cam->DisplayObject::getMatrix() * cam->getMatrixToSceneInverse();

    // Apply local coordinate system
    if( _local_cs && local_cs )
      mv_mat = mv_mat * _present;

    // Scale
    mv_mat = mv_mat * _scale.getMatrix();

    return mv_mat;
  }

  const HqMatrix<float,3>& DisplayObject::getModelViewProjectionMatrix( const Camera* cam, bool local_cs ) const {

    static HqMatrix<float,3> mv_mat;
    mv_mat = cam->getProjectionMatrix() * getModelViewMatrix( cam, local_cs );
    return mv_mat;
  }

  const HqMatrix<float,3>& DisplayObject::getProjectionMatrix( const Camera* cam ) const {

    return cam->getProjectionMatrix();
  }

  const SqMatrix<float,3>& DisplayObject::getNormalMatrix( const Camera* cam ) const {

    static SqMatrix<float,3> nmat;
    nmat = getModelViewMatrix(cam).getRotationMatrix();
    nmat.invertOrthoNormal();
    nmat.transpose();
    return nmat;
  }

  Array<Visualizer*>& DisplayObject::getVisualizers() {

    return _visualizers;
  }

  const Array<Visualizer*>& DisplayObject::getVisualizers() const {

    return _visualizers;
  }

  void DisplayObject::init() {

    _lighted          = true;
    _opaque           = true;
    _material         = GMmaterial::PolishedCopper;
    _color            = GMcolor::Red;
    _collapsed        = false;
  }

  void DisplayObject::insertVisualizer( Visualizer* visualizer ) {

    if( _visualizers.exist( visualizer ) )
      return;

    _visualizers += visualizer;
  }

  void DisplayObject::removeVisualizer( Visualizer* visualizer ) {

    _visualizers.remove( visualizer );
  }

  /*! void DisplayObject::lock(SceneObject* obj)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void DisplayObject::lock(SceneObject* obj) {

    if(obj) {
      updateOrientation(obj->getCenterPos());

      basisChange(_side, _up, _dir, _pos);

      _locked	= true;
      _lock_object = obj;
    }
  }


  /*! void DisplayObject::lock( const Point<float,3>& pos )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  ** must be in scene coordinates **
   */
  void DisplayObject::lock( const Point<float,3>& pos ) {

    _lock_pos	= pos;
    _locked	= true;
    _lock_object = 0;
  }


  /*! void DisplayObject::lock( double d )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  ** must be in scene coordinates **
   */
  void DisplayObject::lock( double d ) {

    _lock_pos	= _matrix_scene * (_pos + d*_dir);
    _locked	= true;
    _lock_object = 0;
  }


  /*! void DisplayObject::move( float d )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  Moveing in shooting direction
   */
  void DisplayObject::move( float d ) {

    _pos += d*_dir;
    basisChange(_side, _up, _dir, _pos);
  }


  /*! void DisplayObject::move( const Vector<float,3>& t )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  Move in direction t.
   */
  void DisplayObject::move( const Vector<float,3>& t ) {

    Point<float,3> lock_pos;

    if( _locked ) {
      lock_pos = getSceneLockPos();
      _pos += t;
      updateOrientation(lock_pos);
    }
    else _pos += t;

    basisChange(_side, _up, _dir, _pos);
  }


  /*! void DisplayObject::move(char,double)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  Track u (up) d (down) l (left) r (right)
   */
  void DisplayObject::move(char c, double d) {

    double dir_length = double();
    Point<float,3> lock_pos;

    if(_locked)
    {
      lock_pos  = getSceneLockPos();
      dir_length = ( lock_pos - _pos ).getLength();
    }

    switch (c) {
    case 'u':
      _pos += d*_up;
      break;
    case 'd':
      _pos -= d*_up;
      break;
    case 'l':
      _pos += d*_side;
      break;
    case 'r':
      _pos -= d*_side;
      break;
    default:
      break;
    }

    if(_locked)
    {
      updateOrientation(lock_pos);
      _pos	= lock_pos - dir_length * _dir;
    }

    basisChange(_side, _up, _dir, _pos);
  }


  /*! void DisplayObject::move(const Vector<float,2>& t)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  Track in direction t.
   */
  void DisplayObject::move(const Vector<float,2>& t) {

    double dir_length;
    Point<float,3> lock_pos;

    if(_locked)
    {
      lock_pos  = getSceneLockPos();
      dir_length = (lock_pos - _pos).getLength();

      _pos += t(0)*_side + t(1)*_up;

      updateOrientation(lock_pos);
      _pos	= lock_pos - dir_length*_dir;
    }
    else {
      _pos += _side*t(0) + _up*t(1);
    }
    basisChange(_side, _up, _dir, _pos);
  }


  /*! void DisplayObject::roll(Angle a)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void DisplayObject::roll(Angle a) {

    HqMatrix<float,3> m( a, _dir );
    _up   = m * _up;
    _side = m * _side;
    basisChange(_side, _up, _dir, _pos);
  }


  /*! void DisplayObject::set ( const Point<float,3>&  pos, const Vector<float,3>& dir, const Vector<float,3>& up )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  ** In scene coordinates **
   */
  void DisplayObject::set (
    const Point<float,3>&  pos,
    const Vector<float,3>& dir,
    const Vector<float,3>& up
  ) {

    _pos	= pos;
    _dir	= dir;
    _up		= up - (up*_dir)*_dir;
    _side	= _up^_dir;
    _locked	= false;
    _lock_object	= 0;

    basisChange(_side, _up, _dir, _pos);
  }


  /*! void DisplayObject::tilt( Angle a )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void DisplayObject::tilt( Angle a ) {

    if(!_locked) {

      HqMatrix<float,3> m( a, _side );
      _up   = m * _up;
      _dir  = m * _dir;
      basisChange(_side, _up, _dir, _pos);
    }
  }


  /*! void DisplayObject::turn(Angle a)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void DisplayObject::turn(Angle a) {

    if(!_locked) {

      HqMatrix<float,3> m( a, _up );
      _dir  = m * _dir;
      _side = m * _side;
      basisChange(_side, _up, _dir, _pos);
    }
  }


  /*! void DisplayObject::unLock()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void DisplayObject::unLock() {

    _locked	= false;
    _lock_object = 0;
  }


  /*! void DisplayObject::rotate(Angle a, const Vector<float,3>& rot_axel)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  Virtual SceneObject function
   *  ** In local coordinates.**
   */
  void DisplayObject::rotate(Angle a, const Vector<float,3>& rot_axel) {

    if(_locked)
    {
      Point<float,3> lock_pos = getSceneLockPos();
      double       dir_length = (lock_pos - _pos).getLength();
      Vector<float,3> t,ra = rot_axel;
      double dd= a.getRad()/M_PI_4;
      while(dd > 1.0)
      {
        t = ra^_dir;
        t.setLength(dir_length);
        move(Vector<float,2>(t*_side,t*_up));
        dd -= 1.0;
      }
      t = ra^_dir;
      t.setLength(tan(dd*M_PI_4)*dir_length);
      move(Vector<float,2>(t*_side,t*_up));
    }
    else
    {
      HqMatrix<float,3> m( a, rot_axel );
      _up   = m * _up;
      _dir  = m * _dir;
      _side = m * _side;
    }
    basisChange(_side, _up, _dir, _pos);
  }


  /*! void DisplayObject::rotate(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  Virtual SceneObject function
   *  ** In local coordinates.**
   */
  void DisplayObject::rotate(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d) {

    HqMatrix<float,3> m( a, d, p );
    _pos  = m * _pos;
    _up   = m * _up;
    _dir  = m * _dir;
    _side = m * _side;

    if(_locked)
    {
      Point<float,3> lock_pos = getSceneLockPos();
      updateOrientation(lock_pos);
    }

    basisChange(_side, _up, _dir, _pos);
  }

  void DisplayObject::rotate(const UnitQuaternion<float>& d) {

    HqMatrix<float,3> m(d);
    _pos  = m * _pos;
    _up   = m * _up;
    _dir  = m * _dir;
    _side = m * _side;

    if(_locked)
    {
      Point<float,3> lock_pos = getSceneLockPos();
      updateOrientation(lock_pos);
    }

    basisChange(_side, _up, _dir, _pos);
  }

  /*! void DisplayObject::rotateGlobal(Angle a, const Vector<float,3>& rot_axel)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  Virtual SceneObject function
   *  ** In Scene Coordinates **
   */
  void DisplayObject::rotateGlobal(Angle a, const Vector<float,3>& rot_axel) {

    rotate( a, _matrix_scene_inv * rot_axel );
  }


  /*! void DisplayObject::rotateGlobal(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  Virtual SceneObject function
   *  ** In Scene Coordinates **
   */
  void DisplayObject::rotateGlobal(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d) {

    rotate( a, _matrix_scene_inv * p, _matrix_scene_inv *d );
  }

  void DisplayObject::rotateGlobal(const UnitQuaternion<float>& d) {

    HqMatrix<float,3> m = _matrix_scene_inv * HqMatrix<float,3>(d);
    _pos  = m * _pos;
    _up   = m * _up;
    _dir  = m * _dir;
    _side = m * _side;

    if(_locked)
    {
      Point<float,3> lock_pos = getSceneLockPos();
      updateOrientation(lock_pos);
    }

    basisChange(_side, _up, _dir, _pos);
  }

  /*! void DisplayObject::translate( const Vector<float,3>& trans_vector )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  Virtual SceneObject function
   *  ** In local coordinates.**
   */
  void DisplayObject::translate( const Vector<float,3>& trans_vector ) {

    move(trans_vector);
  }


  /*! void DisplayObject::translateGlobal(const Vector<float,3>& trans_vector)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  Virtual SceneObject function
   *  ** In Scene Coordinates **
   */
  void DisplayObject::translateGlobal(const Vector<float,3>& trans_vector) {

    move( _matrix_scene_inv * trans_vector );
  }


  /*! void DisplayObject::localSimulate(double dt)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  Virtual SceneObject function
   */
  void DisplayObject::localSimulate( double /*dt*/ ) {

    if(_locked) {

      updateOrientation( getSceneLockPos() );
      basisChange(_side, _up, _dir, _pos);
    }
  }

  const Color& DisplayObject::getColor() const {

    return _color;
  }


  Color& DisplayObject::getColor() {

    return _color;
  }


  const Material& DisplayObject::getMaterial() const {

    return _material;
  }


  Material& DisplayObject::getMaterial() {

    return _material;
  }

  bool DisplayObject::isLighted() const {

    return _lighted;
  }

  void DisplayObject::setColor( const Color& c ) {

    _color = c;
  }

  void DisplayObject::setLighted( bool lighted ) {

    _lighted = lighted;
  }

  void DisplayObject::setMaterial( const Material& m ) {

    _material = m;
  }


} // END namespace GMlib
