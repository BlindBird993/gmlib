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




#ifndef GM_PARAMETRICS_SURFACE_PSUBSURF_H
#define GM_PARAMETRICS_SURFACE_PSUBSURF_H


// GMlib includes+
#include "../gmpsurf.h"


namespace GMlib {


  template <typename T>
  class PSubSurf : public PSurf<T,3> {
    GM_SCENEOBJECT(PSubSurf)
  public:
    PSubSurf( PSurf<T,3>* s, T su, T eu, T sv, T ev);
    PSubSurf( PSurf<T,3>* s, T su, T eu, T u, T sv, T ev, T v);
    PSubSurf( PSurf<T,3>* s, const Point<T,2>& p1, const Point<T,2>& p2,
                             const Point<T,2>& p3, const Point<T,2>& p4);
    PSubSurf( PSurf<T,3>* s, const Point<T,2>& p1, const Point<T,2>& p2,
                             const Point<T,2>& p3, const Point<T,2>& p4,
                             const Point<T,2>& p);
    PSubSurf( const PSubSurf<T>& copy );

    virtual ~PSubSurf();

    // virtual functions from PSurf
    bool              isClosedU() const;
    bool              isClosedV() const;

    // Local functions

  protected:

    PSurf<T,3>*       _s;
    Vector<float,3>   _trans; // (x,y,z)
    Vector<T,2>       _q;     // (u,v)
    Vector<T,2>       _p1;
    Vector<T,2>       _a;
    Vector<T,2>       _b;
    Vector<T,2>       _c;

    // virtual functions from PSurf
    void              eval( T u, T v, int d1, int d2, bool lu=true, bool lv=true);

    T                 getEndPU();
    T                 getEndPV();
    T                 getStartPU();
    T                 getStartPV();

  private:

    // Local help functions
    void set(PSurf<T,3>* s, T su, T eu, T u, T sv, T ev, T v);
    void set(PSurf<T,3>* s, const Point<T,2>& p1, const Point<T,2>& p2,
                            const Point<T,2>& p3, const Point<T,2>& p4,
                            const Point<T,2>& p);

    Vector<T,2>  S(T u, T v);
    Vector<T,2>  Su(T u, T v);
    Vector<T,2>  Sv(T u, T v);
    Vector<T,2>& Suv(T u, T v);

  }; // END class PSubSurf

} // END namepace GMlib


// Include PSubSurf class function implementations
#include "gmpsubsurf.c"


#endif // GM_PARAMETRICS_SURFACE_PSUBSURF_H

