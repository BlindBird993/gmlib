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



/*! \file gmPBezierCurveSurf.h
 *
 *  Interface for the PBezierCurveSurf class.
 *
 *  \date   2011-04-06, ALA
 */

#ifndef GM_PARAMETRICS_SURFACE_PBEZIERCURVESURF_H
#define GM_PARAMETRICS_SURFACE_PBEZIERCURVESURF_H


// GMlib
#include "../gmpsurf.h"
#include "../gmpcurve.h"


namespace GMlib {

  template <typename T>
  class PBezierCurveSurf : public PSurf<T,3> {
    GM_SCENEOBJECT(PBezierCurveSurf)
  public:
    PBezierCurveSurf( Array<PCurve<T,3>*> cu, bool swap_par=false);
    PBezierCurveSurf( PCurve<T,3>* c1, PCurve<T,3>* c2, bool swap_par=false);
    PBezierCurveSurf( const PBezierCurveSurf<T>& su );
    virtual ~PBezierCurveSurf();

    bool          isClosedU() const;
    bool          isClosedV() const;

  protected:

    void          eval(T u, T v, int d1, int d2, bool lu, bool lv );
    T             getEndPU();
    T             getEndPV();
    T             getStartPU();
    T             getStartPV();

    Array<PCurve<T,3>*>   _cu;

    bool                _swap_par;

  }; // END class PBezierCurveSurf

} // END namespace GMlib


// Include PBezierCurveSurf class function implementations
#include "gmpbeziercurvesurf.c"


#endif // GM_PARAMETRICS_SURFACE_PBEZIERCURVESURF_H
