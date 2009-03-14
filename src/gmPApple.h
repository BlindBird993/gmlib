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



/*! \file gmPApple.h
 *
 *  Interface for the gmPApple class.
 *
 *  \date   2008-09-07
 */

#ifndef __gmPAPPLE_H__
#define __gmPAPPLE_H__

// STL
#include <iostream>

// GMlib includes
#include "gmPSurf.h"

namespace GMlib {





  template <class T, int n>
  class PApple: public PSurf<T,n> {
  public:
    PApple( T radius = T(1) );
    PApple( const PApple<T,n>& papple );

    std::string       getIdentity() const;

  protected:
    T                 _r;

    void              eval(T u, T v, int d1, int d2, bool lu = true, bool lv = true );
    T                 getEndPU();
    T                 getEndPV();
    T                 getStartPU();
    T                 getStartPV();
    bool              isClosedU() const;
    bool              isClosedV() const;
  };







} // END namespace GMlib

// Include PApple class function implementations
#include "gmPApple.c"


#endif // __gmPAPPLE_H__
