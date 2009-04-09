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



/*! \file gmDPArc.h
 *
 *  Interface for the gmDPArc class.
 *
 *  \date   2008-11-16
 */

#ifndef __gmDPARC_H__
#define __gmDPARC_H__


// GMlib includes+
#include "gmDCurve.h"
#include "gmPArc.h"


namespace GMlib {


  template <typename T>
  class DPArc : public DCurve<T> {
  public:
    DPArc( T speed, T curvature );
    DPArc( T speed, T curvature, T start, T end );
    DPArc( DVector< Vector<T,3> >& p, T s, T t, T e );
    DPArc( const DPArc<T>& copy );
//    DPArc( const PArc<T,3>& copy );
//    DPArc( PArc<T,3>* copy );
    virtual ~DPArc();


//    virtual PArc<T,3>*    getPArc();

  protected:
//    PArc<T,3>             *_l_ref;

    string                getIdentity() const;
    virtual void          init();





  //////////////////////// PArc !!!!!!!!!!!!!! PArc ////////////////////////
  //////////////////////// PArc !!!!!!!!!!!!!! PArc ////////////////////////
  //////////////////////// PArc !!!!!!!!!!!!!! PArc ////////////////////////
  //////////////////////// PArc !!!!!!!!!!!!!! PArc ////////////////////////


  public:
    T         getCurvature() const;
    T         getLocalMapping( T t, T ts, T ti, T te );
    T         getSpeed() const;
    bool      isClosed() const;
    void      setCurvature( T curvature );
    void      setEnd( T end );
    void      setSpeed( T speed );
    void      setStart( T start );


  protected:
    T         _delta;   // Speed, but not speed
    T         _s;       // Speed
    T         _c;       // Curvature
    T         _start;   // Start
    T         _end;     // End

    HqMatrix<float,3>  _matrix_arc;


    void	    eval(T t, int d, bool l);
    T         getCurvature( DVector< Vector<T,3> >& p );
    T         getEndP();
    T         getStartP();
  };




} // END namepace GMlib

// Include DPArc class function implementations
#include "gmDPArc.c"


#endif // __gmDPARC_H__

