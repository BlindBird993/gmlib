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



/*! \file gmPHermiteCurveSurf.h
 *
 *  Interface for the PHermiteCurveSurf class.
 *
 *  \date   2011-04-06, ALA
 */

#ifndef __gmPHERMITECURVESURF_H__
#define __gmPHERMITECURVESURF_H__

// STL
#include <string>

// GMlib
#include "../gmpsurf.h"
#include "../gmpcurve.h"
#include "../evaluators/gmHermite4Evaluator.h"


namespace GMlib {

  template <typename T>
  class PHermiteCurveSurf : public PSurf<T> {
    GM_SCENEOBJECT(PHermiteCurveSurf)
  public:
    PHermiteCurveSurf( PCurve<T>* c1, PCurve<T>* c2, PCurve<T>* c3, PCurve<T>* c4, bool swap_par=false);
    PHermiteCurveSurf( Array<PCurve<T>*> cu, bool swap_par=false);
    PHermiteCurveSurf( const PHermiteCurveSurf<T>& su );
    virtual ~PHermiteCurveSurf();

    bool          isClosedU() const;
    bool          isClosedV() const;

    void          makeSample(DMatrix<DMatrix<Vector<T,3> > >& m, int m1, int m2);

  protected:

    void          eval(T u, T v, int d1, int d2, bool lu, bool lv );
    T             getEndPU();
    T             getEndPV();
    T             getStartPU();
    T             getStartPV();

    Hermite4Evaluator<T>*  _H;

    Array<PCurve<T>*> _cu;
    bool              _swap_par;

  public:

    static Hermite4Evaluator<T> HCu; // default blending for preevaluation

  }; // END class PHermiteCurveSurf

} // END namespace GMlib


// Include PHermiteCurveSurf class function implementations
#include "gmphermitecurvesurf.c"


#endif // __gmPHERMITECURVESURF_H__
