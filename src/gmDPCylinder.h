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
    DPCylinder( const PCylinder<T,3>& copy );
    DPCylinder( PCylinder<T,3> *copy );
    virtual ~DPCylinder();

    virtual PCylinder<T,3>*               getPCylinder();
    virtual const PCylinder<T,3>* const   getPCylinder() const;

  protected:
    PCylinder<T,3>                        *_l_ref;

    std::string                           getIdentity() const;
    void                                  init();
  };


} // END namespace GMlib

// Include DPCylinder class function implementations
#include "gmDPCylinder.c"



#endif // __gmDPCYLINDER_H__


