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



/*! \file gmpkuensurface.h
 *
 *  Interface for the PKuenSurface class.
 */

#ifndef __gmPKUENSURFACE_H__
#define __gmPKUENSURFACE_H__

#include "../gmpsurf.h"


namespace GMlib {

  template <typename T>
  class PKuenSurface : public PSurf<T> {
  public:
    PKuenSurface( T radius = T(1) );
    PKuenSurface( const PKuenSurface<T>& copy );
    virtual ~PKuenSurface();


  protected:
    T                 _r;

    void              eval(T u, T v, int d1, int d2, bool lu = true, bool lv = true );
    T                 getEndPU();
    T                 getEndPV();
    std::string       getIdentity() const;
    T                 getStartPU();
    T                 getStartPV();
    virtual void      init();
    bool              isClosedU() const;
    bool              isClosedV() const;

  }; // END class PKuenSurface


} // END namespace GMlib

// Include PKuenSurface class function implementations
#include "gmpkuensurface.c"



#endif // __gmPKUENSURFACE_H__
