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



/*! \file   gmDPTCurve.h
 *
 *  Interface for the DPTCurve class.
 *
 *  \date   2008-11-26
 */

#ifndef __gmDPTCURVE_H__
#define __gmDPTCURVE_H__


#include "gmDCurve.h"
#include "gmPTCurve.h"


namespace GMlib {


  template <typename T>
  class DPTCurve : public DCurve<T> {
  public:
    DPTCurve( PCurve<T, 3>* pcA, PCurve<T, 3>* pcB );

    void  setPA( PCurve<T, 3>* pcA );
    void  setPB( PCurve<T, 3>* pcB );


  protected:
    void  localSimulate( double dt );


  private:
    PTCurve<T, 3> *_ptc;


  }; // END class DPTCurve

} // END namespace GMlib


// Include DPTCurve class function implementations
#include "gmDPTCurve.c"

#endif // __gmDPTCURVE_H__


