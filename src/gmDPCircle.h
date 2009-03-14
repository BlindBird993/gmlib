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



/*! \file gmDPCircle.h
 *
 *  Interface for the gmDPCircle class.
 *
 *  \date   2008-09-09
 */

#ifndef __gmDPCIRCLE_H__
#define __gmDPCIRCLE_H__


// GMlib includes+
#include "gmDCurve.h"
#include "gmPCircle.h"


namespace GMlib {


  template <typename T>
  class DPCircle : public DCurve<T> {
  public:
    DPCircle( T radius = T(20) );
    DPCircle( const DPCircle<T>& copy );
    DPCircle( const PCircle<T,3>& copy );
    DPCircle( PCircle<T,3>* copy );
    virtual ~DPCircle();

    virtual PCircle<T,3>*   getPCircle();


  protected:
    PCircle<T,3>            *_l_ref;

    string                  getIdentity() const;
    virtual void            init();
  };




} // END namepace GMlib

// Include DPCircle class function implementations
#include "gmDPCircle.c"


#endif // __gmDPCIRCLE_H__
