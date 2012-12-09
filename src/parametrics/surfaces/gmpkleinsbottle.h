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



/*! \file gmpkleinsbottle.h
 *
 *  Interface for the PKleinsBottle class.
 */

#ifndef __gmPKLEINSBOTTLE_H__
#define __gmPKLEINSBOTTLE_H__

#include "../gmpsurf.h"


namespace GMlib {

  template <typename T>
  class PKleinsBottle : public PSurf<T> {
    GM_SCENEOBJECT(PKleinsBottle)
  public:
    PKleinsBottle( T scale_x = T(1), T scale_y = T(1.5), T scale_z = T(4) );
    PKleinsBottle( const PKleinsBottle<T>& copy );
    virtual ~PKleinsBottle();


  protected:
    T                 _r;
    T                 _sx;
    T                 _sy;

    void              eval(T u, T v, int d1, int d2, bool lu = true, bool lv = true );
    T                 getEndPU();
    T                 getEndPV();
    T                 getStartPU();
    T                 getStartPV();
    virtual void      init();
    bool              isClosedU() const;
    bool              isClosedV() const;

  }; // END class PKleinsBottle


} // END namespace GMlib

// Include PKleinsBottle class function implementations
#include "gmpkleinsbottle.c"



#endif // __gmPKLEINSBOTTLE_H__

