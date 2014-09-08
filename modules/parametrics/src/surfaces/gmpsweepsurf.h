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



/*! \file gmPSweepSurf.h
 *
 *  Interface for the PSweepSurf class.
 *
 *  \date   2011-03-26
 */

#ifndef __gmPSWEEPSURF_H__
#define __gmPSWEEPSURF_H__


// GMlib
#include "../gmpsurf.h"
#include "../gmpcurve.h"


namespace GMlib {

  template <typename T>
  class PSweepSurf : public PSurf<T,3> {
  GM_SCENEOBJECT(PSweepSurf)
  public:
    PSweepSurf( PCurve<T,3>* profile, PCurve<T,3>* spine, bool RMF = false);
    PSweepSurf( const PSweepSurf<T>& su );
    virtual ~PSweepSurf();

    bool          isClosedU() const;
    bool          isClosedV() const;

  protected:

    void          eval(T u, T v, int d1, int d2, bool lu, bool lv );
    T             getEndPU();
    T             getEndPV();
    T             getStartPU();
    T             getStartPV();


    PCurve<T,3>*    _profile;
    PCurve<T,3>*    _spine;

    Vector<T,3>   _spv;

    bool          _RMF;
    DVector<T>    _omega;

    void          makeOmega(int n = 100, T omega_0 = T(0));
    T             getOmega(T t);

  }; // END class PSweepSurf

} // END namespace GMlib


// Include PSweepSurf class function implementations
#include "gmpsweepsurf.c"


#endif // __gmPSWEEPSURF_H__
