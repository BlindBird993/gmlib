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



} // END namespace GMlib
