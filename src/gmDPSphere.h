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



/*! \file gmDPSphere.h
 *
 *  Interface for the gmDPSphere class.
 *
 *  \date   2008-09-04
 */

#ifndef __gmDPSPHERE_H__
#define __gmDPSPHERE_H__

// STL
#include <string>

// GMlib
#include "gmDSurf.h"
#include "gmPSphere.h"


namespace GMlib {

  template <typename T>
  class DPSphere : public DSurf<T> {
  public:
    DPSphere( T radius = T(1) );
    DPSphere( T radius, int s1, int s2 );
    DPSphere( const DPSphere<T>& copy );
//    DPSphere( const PSphere<T,3>& copy );
//    DPSphere( PSphere<T,3>* copy );
    virtual ~DPSphere();

//    virtual PSphere<T,3>*               getPSphere();
//    virtual const PSphere<T,3>* const   getPSphere() const;
//
//    T                                   getRadius() const;
//    void                                setRadius( T radius );


  protected:
//    PSphere<T,3>                        *_l_ref;

    std::string                         getIdentity() const;
    void                                init();



  //////////////////////// PSphere !!!!!!!!!!!!!! PSphere ////////////////////////
  //////////////////////// PSphere !!!!!!!!!!!!!! PSphere ////////////////////////
  //////////////////////// PSphere !!!!!!!!!!!!!! PSphere ////////////////////////
  //////////////////////// PSphere !!!!!!!!!!!!!! PSphere ////////////////////////

  public:
    T             getRadius() const;
    void          setRadius( T radius );

  protected:
    T             _radius;

    void          eval(T u, T v, int d1, int d2, bool lu = true, bool lv = true );
    T             getEndPV();
    T             getEndPU();
    T             getStartPU();
    T             getStartPV();
    bool          isClosedU() const;
    bool          isClosedV() const;


  };


} // END namespace GMlib

// Include DPSphere class function implementations
#include "gmDPSphere.c"


#endif // __gmDPSPHERE_H__

