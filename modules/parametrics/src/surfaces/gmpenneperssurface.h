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



/*! \file gmpenneperssurface.h
 *
 *  Interface for the PEnnepersSurface class.
 */

#ifndef GM_PARAMETRICS_SURFACE_PENNEPERSURFACE_H
#define GM_PARAMETRICS_SURFACE_PENNEPERSURFACE_H

#include "../gmpsurf.h"


namespace GMlib {

  template <typename T>
  class PEnnepersSurface : public PSurf<T,3> {
    GM_SCENEOBJECT(PEnnepersSurface)
  public:
    PEnnepersSurface();
    PEnnepersSurface( const PEnnepersSurface<T>& copy );
    virtual ~PEnnepersSurface();


  protected:
    void              eval(T u, T v, int d1, int d2, bool lu = true, bool lv = true );
    T                 getEndPU();
    T                 getEndPV();
    T                 getStartPU();
    T                 getStartPV();
    virtual void      init();
    bool              isClosedU() const;
    bool              isClosedV() const;

  }; // END class PEnnepersSurface


} // END namespace GMlib

// Include PEnnepersSurface class function implementations
#include "gmpenneperssurface.c"



#endif // GM_PARAMETRICS_SURFACE_PENNEPERSURFACE_H

