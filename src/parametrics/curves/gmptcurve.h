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



/*! \file   gmptcurve.h
 *
 *  Interface for the PTCurve class (Parametric Tranformed Curve).
 */

#ifndef __gmPTCURVE_H__
#define __gmPTCURVE_H__

#include "../gmpcurve.h"

// gmlib
#include <core/types/gmangle.h>


namespace GMlib {


  template <typename T>
  class PTCurve : public PCurve<T> {
  public:
    PTCurve( PCurve<T>* pcA, PCurve<T>* pcB );
    PTCurve( const PTCurve<T>& ptc );

    bool                                isClosed() const;
    void                                setAngle( T a );
    void                                setPA( PCurve<T>* pcA );
    void                                setPB( PCurve<T>* pcB );


  protected:
    void                                eval( T t, int d, bool l = true ) {}
    T                                   getStartP() { return T(0); }
    T                                   getEndP() { return T(1); }
    void                                localSimulate( double dt );
    void                                resample( DVector< DVector< Vector<T,3> > >& p, int m, int d, T start, T end );


  private:
    void                                _compute( DVector< DVector< Vector<T,3> > >& p );
    void                                _merge_PA_and_PB( int i );
    void                                _resample( PCurve<T>* obj, DVector<DVector< Vector<T,3> > >& p, int m, int d );
    Point<T,3>                          _rotate_and_project();

    PCurve<T>                           *_pcA;
    PCurve<T>                           *_pcB;

    T                                   _angle;
    DVector<DVector<Vector<T,3> > >     _pA;
    DVector<DVector<Vector<T,3> > >     _pB;
    bool                                _resampleA;
    bool                                _resampleB;
    Point<T,6>                          _tPoints;



  }; // END class PTCurve

} // END namespace GMlib


// Include PTCurve class function implementations
#include "gmptcurve.c"

#endif // __gmPTCURVE_H__

