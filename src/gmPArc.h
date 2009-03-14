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



/*! \file gmPArc.h
 *
 *  Interface for the PArc class.
 *
 *  \date   2008-11-16
 */

#ifndef __gmPARC_H__
#define __gmPARC_H__

// STL
#include <iostream>

// GMlib includes
#include "gmPCurve.h"


namespace GMlib {


  template <typename T, int n>
  class PArc : public PCurve<T, n> {
  public:
    PArc ( T speed, T curvature );
    PArc ( T speed, T curvature, T s, T e );
    PArc ( DVector< Vector<T, n> >& p, T s, T t, T e );
    PArc ( const PArc& ca );

    T         getCurvature() const;
    std::string   getIdentity() const;
    T         getLocalMapping( T t, T ts, T ti, T te );
    T         getSpeed() const;
    bool      isClosed() const;
    void      setCurvature( T curvature );
    void      setEnd( T end );
    void      setSpeed( T speed );
    void      setStart( T start );


  protected:
    T         _delta;   // Speed, but not speed
    T         _s;       // Speed
    T         _c;       // Curvature
    T         _start;   // Start
    T         _end;     // End

    GLMatrix  _matrix;  // Temporary a GLMatrix


    void	    eval(T t, int d, bool l);
    T         getCurvature( DVector< Vector<T, n> >& p );
    T         getEndP();
    T         getStartP();

//    T         _getOmega( T t, T ti, T speed );

  };




} // END namespace GMlib

// Include PArc class function implementation
#include "gmPArc.c"

#endif // __gmPARC_H__
