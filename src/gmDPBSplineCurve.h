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



/*! \file gmDPBSplineCurve.h
 *
 *  Interface for the gmDPBSplineCurve class.
 *
 *  \date   2008-10-28
 */

#ifndef __gmDPBSPLINECURVE_H__
#define __gmDPBSPLINECURVE_H__


// GMlib includes+
#include "gmDCurve.h"
#include "gmPBSplineCurve.h"


namespace GMlib {


  template <typename T>
  class DPBSplineCurve : public DCurve<T> {
  public:
    DPBSplineCurve( const DVector< Vector<T, 3> >& cv, int d  );
    DPBSplineCurve( const DPBSplineCurve<T>& dpbsc );
    DPBSplineCurve( const PBSplineCurve<T,3>& pbsc );
    DPBSplineCurve( PBSplineCurve<T,3>* pbsc );
    virtual ~DPBSplineCurve();

    virtual PBSplineCurve<T,3>*   getPBSplineCurve();

  protected:
    PBSplineCurve<T,3>            *_l_ref;

    string                        getIdentity() const;
    virtual void                  init();
  };




} // END namepace GMlib

// Include DPBSplineCurve class function implementations
#include "gmDPBSplineCurve.c"


#endif // __gmDPBSPLINECURVE_H__


