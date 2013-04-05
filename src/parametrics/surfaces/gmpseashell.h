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



/*! \file gmpseashell.h
 *
 *  Interface for the PSeashell class.
 */

#ifndef __gmPSEASHELL_H__
#define __gmPSEASHELL_H__

#include "../gmpsurf.h"


namespace GMlib {

  template <typename T>
  class PSeashell : public PSurf<T,3> {
    GM_SCENEOBJECT(PSeashell)
  public:
    PSeashell();
    PSeashell( const PSeashell<T>& copy );
    virtual ~PSeashell();


  protected:
    void              eval(T u, T v, int d1, int d2, bool lu = true, bool lv = true );
    T                 getEndPU();
    T                 getEndPV();
    T                 getStartPU();
    T                 getStartPV();
    virtual void      init();
    bool              isClosedU() const;
    bool              isClosedV() const;

  }; // END class PSeashell


} // END namespace GMlib

// Include PSeashell class function implementations
#include "gmpseashell.c"



#endif // __gmPSEASHELL_H__

