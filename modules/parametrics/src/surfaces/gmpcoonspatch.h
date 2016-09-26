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



/*! \file gmPCoonsPatch.h
 *
 *  Interface for the PCoonsPatch class.
 *
 *  \date   2012-04-02, ALA
 */

#ifndef GM_PARAMETRICS_SURFACE_PCOONSPATCH_H
#define GM_PARAMETRICS_SURFACE_PCOONSPATCH_H

// STL
#include <string>

// GMlib
#include "../gmpsurf.h"
#include "../gmpcurve.h"


namespace GMlib {

  template <typename T>
  class PCoonsPatch : public PSurf<T,3> {
    GM_SCENEOBJECT(PCoonsPatch)
  public:
    PCoonsPatch( PSurf<T,3>* s1, PSurf<T,3>* s2, PSurf<T,3>* s3 );
    PCoonsPatch( const PCoonsPatch<T>& su );

    virtual ~PCoonsPatch();

    bool          isClosedU() const;
    bool          isClosedV() const;

  protected:

    void          eval(T u, T v, int d1, int d2, bool lu, bool lv );
    T             getEndPU();
    T             getEndPV();
    T             getStartPU();
    T             getStartPV();

    PSurf<T,3>*    _s1;
    PSurf<T,3>*    _s2;
    PSurf<T,3>*    _s3;

  }; // END class PCoonsPatch

} // END namespace GMlib


// Include PCoonsPatch class function implementations
#include "gmpcoonspatch.c"


#endif // GM_PARAMETRICS_SURFACE_PCOONSPATCH_H
