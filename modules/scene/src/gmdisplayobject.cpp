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
  ) : SceneObject(pos,dir,up) {}


  /*! DisplayObject::DisplayObject( const Point<float,3>&  lockPos, const Point<float,3>&  pos, const Vector<float,3>& up )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  DisplayObject::DisplayObject(
    const Point<float,3>&  lock_pos,
    const Point<float,3>&  pos,
    const Vector<float,3>& up
  ) : SceneObject(lock_pos,pos,up) {}

  /*! DisplayObject::DisplayObject( SceneObject* lockObject, const Point<float,3>&  pos, const Vector<float,3>& up )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  DisplayObject::DisplayObject(
    SceneObject* lock_object,
    const Point<float,3>&  pos,
    const Vector<float,3>& up
  ) : SceneObject(lock_object,pos,up) {}


  /*! DisplayObject::DisplayObject( const DisplayObject& s )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  DisplayObject::DisplayObject( const DisplayObject& copy ) : SceneObject(copy) {}


  /*! DisplayObject::~DisplayObject()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  DisplayObject::~DisplayObject() {}


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


} // END namespace GMlib
