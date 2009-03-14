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



/*! \file gmDPPlane.h
 *
 *  Interface for the gmDPPlane class.
 *
 *  \date   2008-09-04
 */

#ifndef __gmDPPLANE_H__
#define __gmDPPLANE_H__



#include <string>

#include "gmDSurf.h"
#include "gmPPlane.h"


namespace GMlib {

  template <typename T>
  class DPPlane : public DSurf<T> {
  public:
    DPPlane( const Point<T,3>& p, const Vector<T,3>& u, const Vector<T,3>& v );
    DPPlane( const DPPlane<T>& pplane );
    DPPlane( const PPlane<T,3>& pplane );
    virtual ~DPPlane();

    virtual const UnitVector<T,3>&    getNormal();
    virtual PPlane<T,3>*              getPPlane();


  protected:
    PPlane<T,3>                       *_l_ref;

    std::string                       getIdentity() const;
    virtual void                      init();
  };


} // END namespace GMlib

// Include DPPlane class function implementations
#include "gmDPPlane.c"



#endif // __gmDPPLANE_H__
