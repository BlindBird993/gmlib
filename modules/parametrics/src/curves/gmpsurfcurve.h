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



/*! \file gmPSurfCurve.h
 *
 *  Interface for the PSurfCurve class.
 *
 *  \date   2011-04-06, ALA
 */

#ifndef GM_PARAMETRICS_CURVE_PSURFCURVE_H
#define GM_PARAMETRICS_CURVE_PSURFCURVE_H


// GMlib includes+
#include "../gmpcurve.h"
#include "../gmpsurf.h"


namespace GMlib {


  template <typename T>
  class PSurfCurve : public PCurve<T,3> {
    GM_SCENEOBJECT(PSurfCurve)
  public:
    PSurfCurve( PSurf<T,3>* s, const Point<T,2>& p1,  const Point<T,2>& p2);
    PSurfCurve( PSurf<T,3>* s, const Point<T,2>& p1,  const Point<T,2>& p2,
                             const Vector<T,2>& v1, const Vector<T,2>& v2);
    PSurfCurve( const PSurfCurve<T>& copy );

    virtual ~PSurfCurve();

    bool                isClosed() const;

    void                togglePlot();

    virtual void        resample( DVector< DVector< Vector<T, 3> > >& p,
                                      int m, int d, T start, T end );

  protected:

    PSurf<T,3>*           _s;
    Point<T,2>          _p1;
    Point<T,2>          _p2;

    bool                _der_curve;
    Vector<T,2>         _v1;
    Vector<T,2>         _v2;

    Vector<T,2>         _dv;

    bool                _plot;

    void	            eval1( T t, int d);
    void	            eval2( T t, int d);

    void	            eval( T t, int d = 0, bool l = false );
    T                   getEndP();
    T                   getStartP();

  }; // END class PSurfCurve

} // END namepace GMlib


// Include PSurfCurve class function implementations
#include "gmpsurfcurve.c"


#endif // GM_PARAMETRICS_CURVE_PSURFCURVE_H

