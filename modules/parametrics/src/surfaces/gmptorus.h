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



/*! \file gmptorus.h
 *
 *  Interface for the PTorus class.
 */

#ifndef __gmPTORUS_H__
#define __gmPTORUS_H__

#include "../gmpsurf.h"


namespace GMlib {

  template <typename T>
  class PTorus : public PSurf<T,3> {
    GM_SCENEOBJECT(PTorus)
  public:
    PTorus( T wheelrad=T(3), T tuberad1=T(1), T tuberad2=T(1) );
    PTorus( const PTorus<T>& pshere );
    virtual ~PTorus();

    const T&      getTubeRadius1() const;
    const T&      getTubeRadius2() const;
    const T&      getWheelRadius() const;
    bool          isClosedU() const override;
    bool          isClosedV() const override;
    void          setTubeRadius1( const T& radius );
    void          setTubeRadius2( const T& radius );
    void          setWheelRadius( const T& radius );

  protected:
    T             _a;		//Wheelradius
    T             _b;		//Tuberadius1
    T             _c;		//Tuberadius2

    void          eval(T u, T v, int d1, int d2, bool lu, bool lv ) override;
    T             getEndPU() override;
    T             getEndPV() override;
    T             getStartPU() override;
    T             getStartPV() override;

  }; // END class PTorus

} // END namespace GMlib


// Include PTorus class function implementations
#include "gmptorus.c"


#endif // __gmPTORUS_H__


