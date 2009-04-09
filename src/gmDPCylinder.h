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



/*! \file gmDPCylinder.h
 *
 *  Interface for the gmDPCylinder class.
 *
 *  \date   2008-10-27
 */

#ifndef __gmDPCYLINDER_H__
#define __gmDPCYLINDER_H__



#include <string>

#include "gmDSurf.h"
#include "gmPCylinder.h"


namespace GMlib {

  template <typename T>
  class DPCylinder : public DSurf<T> {
  public:
    DPCylinder( T rx = 4, T ry = 4, T h = 2 );
    DPCylinder( const DPCylinder<T>& copy );
//    DPCylinder( const PCylinder<T,3>& copy );
//    DPCylinder( PCylinder<T,3> *copy );
    virtual ~DPCylinder();

//    virtual PCylinder<T,3>*               getPCylinder();
//    virtual const PCylinder<T,3>* const   getPCylinder() const;

  protected:
//    PCylinder<T,3>                        *_l_ref;

    std::string                           getIdentity() const;
    void                                  init();



  //////////////////////// PCylinder !!!!!!!!!!!!!! PCylinder ////////////////////////
  //////////////////////// PCylinder !!!!!!!!!!!!!! PCylinder ////////////////////////
  //////////////////////// PCylinder !!!!!!!!!!!!!! PCylinder ////////////////////////
  //////////////////////// PCylinder !!!!!!!!!!!!!! PCylinder ////////////////////////

  public:
    T             getHeight() const;
    T             getRadiusX() const;
    T             getRadiusY() const;
    bool          isClosedU() const;
    bool          isClosedV() const;
    void          setConstants( T rx, T ry, T h );

  protected:
    T             _rx;
    T             _ry;
    T             _h;

    void          eval(T u, T v, int d1, int d2, bool lu = true, bool lv = true );
    T             getEndPV();
    T             getEndPU();
    T             getStartPU();
    T             getStartPV();
  };


} // END namespace GMlib

// Include DPCylinder class function implementations
#include "gmDPCylinder.c"



#endif // __gmDPCYLINDER_H__


