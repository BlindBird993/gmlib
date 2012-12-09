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



/*! \file gmpinsideouttorus.h
 *
 *  Interface for the PInsideOutTorus class.
 */

#ifndef __gmPINSIDEOUTTORUS_H__
#define __gmPINSIDEOUTTORUS_H__

#include "../gmpsurf.h"


namespace GMlib {

  template <typename T>
  class PInsideOutTorus : public PSurf<T> {
    GM_SCENEOBJECT(PInsideOutTorus)
  public:
    PInsideOutTorus( T wheelrad=T(3), T tuberad1=T(1), T tuberad2=T(1) );
    PInsideOutTorus( const PInsideOutTorus<T>& copy );
    virtual ~PInsideOutTorus();


  protected:
    T                 _a;		//Wheelradius
    T                 _b;		//Tuberadius1
    T                 _c;		//Tuberadius2

    void              eval(T u, T v, int d1, int d2, bool lu = true, bool lv = true );
    T                 getEndPU();
    T                 getEndPV();
    T                 getStartPU();
    T                 getStartPV();
    virtual void      init();
    bool              isClosedU() const;
    bool              isClosedV() const;

  }; // END class PInsideOutTorus


} // END namespace GMlib

// Include PInsideOutTorus class function implementations
#include "gmpinsideouttorus.c"



#endif // __gmPINSIDEOUTTORUS_H__

