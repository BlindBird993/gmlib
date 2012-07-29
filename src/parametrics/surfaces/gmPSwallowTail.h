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



/*! \file gmPSwallowTail.h
 *
 *  Interface for the PSwallowTail class.
 *
 *  \date   2010-09-30
 */

#ifndef __gmPSWALLOWTAIL_H__
#define __gmPSWALLOWTAIL_H__



#include <string>


#include "gmPSurf.h"

namespace GMlib {

  template <typename T>
  class PSwallowTail : public PSurf<T> {
  public:
    PSwallowTail();
    PSwallowTail( const PSwallowTail<T>& copy );
    virtual ~PSwallowTail();


  protected:
    void              eval(T u, T v, int d1, int d2, bool lu = true, bool lv = true );
    T                 getEndPU();
    T                 getEndPV();
    std::string       getIdentity() const;
    T                 getStartPU();
    T                 getStartPV();
    virtual void      init();
    bool              isClosedU() const;
    bool              isClosedV() const;

  }; // END class PSwallowTail


} // END namespace GMlib

// Include PSwallowTail class function implementations
#include "gmPSwallowTail.c"



#endif // __gmPSWALLOWTAIL_H__

