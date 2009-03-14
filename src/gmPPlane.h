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



/*! \file gmPPlane.h
 *
 *  Interface for the gmPPlane class.
 *
 *  \date   2008-09-06
 */

#ifndef __gmPPLANE_H__
#define __gmPPLANE_H__

// STL
#include <iostream>

// GMlib includes
#include "gmPoint.h"
#include "gmPSurf.h"


namespace GMlib{


  template <class T, int n>
  class PPlane: public PSurf<T,n> {
  public:
    PPlane( const Point<T,n>& p, const Vector<T,n>& u, const Vector<T,n>& v );
    PPlane( const PPlane<T,n>& pl);

    std::string               getIdentity() const;
    const UnitVector<T,n>&    getNormal() const;

    bool                      isClosedU() const;
    bool                      isClosedV() const;


  protected:
    Point<T,n>		            _pt;
    Vector<T,n>		            _u;
    Vector<T,n>               _v;
    UnitVector<T,n>           _n;

    void                      eval(T u, T v, int d1, int d2, bool lu = true, bool lv = true );
    T                         getEndPU();
    T                         getEndPV();
    T                         getStartPU();
    T                         getStartPV();

  };


} // END namespace GMlib


// Include PPlane class function implementations
#include "gmPPlane.c"


#endif // __gmPPLANE_H__
