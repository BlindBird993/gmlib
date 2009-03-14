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



/*! \file gmDPButterfly.h
 *
 *  Interface for the gmDPButterfly class.
 *
 *  \date   2008-09-10
 */

#ifndef __gmDPBUTTERFLY_H__
#define __gmDPBUTTERFLY_H__


// GMlib includes+
#include "gmDCurve.h"
#include "gmPButterfly.h"


namespace GMlib {


  template <typename T>
  class DPButterfly : public DCurve<T> {
  public:
    DPButterfly( T size = T(5) );
    DPButterfly( const DPButterfly<T>& copy );
    DPButterfly( const PButterfly<T,3>& copy );
    DPButterfly( PButterfly<T,3>* copy );
    virtual ~DPButterfly();

    virtual PButterfly<T,3>*    getPButterfly();

  protected:
    PButterfly<T,3>             *_l_ref;

    string                      getIdentity() const;
    virtual void                init();
  };




} // END namepace GMlib

// Include DPButterfly class function implementations
#include "gmDPButterfly.c"


#endif // __gmDPBUTTERFLY_H__

