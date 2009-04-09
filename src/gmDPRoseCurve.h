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



/*! \file gmDPRoseCurve.h
 *
 *  Interface for the gmDPRoseCurve class.
 *
 *  \date   2008-12-02
 */

#ifndef __gmDPROSECURVE_H__
#define __gmDPROSECURVE_H__


// GMlib includes+
#include "gmDCurve.h"
#include "gmPRoseCurve.h"


namespace GMlib {


  template <typename T>
  class DPRoseCurve : public DCurve<T> {
  public:
    DPRoseCurve( T radius = T(5) );
    DPRoseCurve( const DPRoseCurve<T>& copy );
//    DPRoseCurve( const PRoseCurve<T,3>& copy );
//    DPRoseCurve( PRoseCurve<T,3>* copy );
    virtual ~DPRoseCurve();

//    virtual PRoseCurve<T,3>*    getPRoseCurve();

  protected:
//    PRoseCurve<T,3>*            _l_ref;

    string                      getIdentity() const;
    virtual void                init();


  //////////////////////// PRoseCurve !!!!!!!!!!!!!! PRoseCurve ////////////////////////
  //////////////////////// PRoseCurve !!!!!!!!!!!!!! PRoseCurve ////////////////////////
  //////////////////////// PRoseCurve !!!!!!!!!!!!!! PRoseCurve ////////////////////////

  public:
    bool          isClosed() const;


  protected:
    T             _r;

    void	        eval(T t, int d, bool l);
    T             getEndP();
    T             getStartP();
  };




} // END namepace GMlib

// Include DPRoseCurve class function implementations
#include "gmDPRoseCurve.c"


#endif // __gmDPROSECURVE_H__


