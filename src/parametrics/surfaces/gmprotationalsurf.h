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



/*! \file gmPRotationalSurf.h
 *
 *  Interface for the PRotationalSurf class.
 *
 *  \date   2013-09-26, ALA
 */

#ifndef __gmPROTATIONALSURF_H__
#define __gmPROTATIONALSURF_H__

// STL
#include <string>

// GMlib
#include "../gmpsurf.h"
#include "../gmpcurve.h"


namespace GMlib {

  template <typename T>
  class PRotationalSurf : public PSurf<T> {
    GM_SCENEOBJECT(PRotationalSurf)
  public:
    PRotationalSurf( PCurve<T>* cu, T start_par, T end_par );
    PRotationalSurf( const PRotationalSurf<T>& su );
    virtual ~PRotationalSurf();

    bool          isClosedU() const;
    bool          isClosedV() const;

  protected:

    void          eval(T u, T v, int d1, int d2, bool lu, bool lv );
    T             getEndPU();
    T             getEndPV();
    T             getStartPU();
    T             getStartPV();


    PCurve<T>*    _cu;
    T             _start_par;
    T             _end_par;

  }; // END class PRotationalSurf

} // END namespace GMlib


// Include PRotationalSurf class function implementations
#include "gmprotationalsurf.c"


#endif // __gmPROTATIONALSURF_H__
