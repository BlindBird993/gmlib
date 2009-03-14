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



/*! \file gmPBezierCurve.h
 *
 *  Interface for the PBezierCurve class.
 *
 *  \date   2008-10-27
 */

#ifndef __gmPBEZIERCURVE_H__
#define __gmPBEZIERCURVE_H__

// STL
#include <iostream>

// GMlib includes
#include "gmPCurve.h"


namespace GMlib {


  template <typename T, int n>
  class PBezierCurve : public PCurve<T, n> {
  public:
    PBezierCurve( const DVector< Vector<T, n> >& cp );
    PBezierCurve( const DVector< Vector<T, n> >& cp, T s, T t, T e );
    PBezierCurve( const PBezierCurve<T, n>& pbc );

    DVector< Vector<T,n> >&   getControlPoints();
    int                       getDegree() const;
    std::string               getIdentity() const;
    T                         getLocalMapping( T t, T ts, T ti, T te );
    bool                      isClosed() const;
    void                      setClosed( bool state );
    void                      setControlPoints( const DVector< Vector<T, n> >& cv );
    void                      setResampleMode( GM_RESAMPLE_MODE mode );
    void                      setScale( T d );


  protected:
    DVector< Vector<T, n> >   _c;
    T                         _scale;
    DVector< DMatrix< T > >   _t;
    bool                      _closed;

    GM_RESAMPLE_MODE          _resamp_mode;
    bool                      _pre_eval;


    void	                    eval( T t, int d = 0, bool l = false );
    T                         getEndP();
    T                         getStartP();

    void                      resample( DVector< DVector< Vector<T, n> > >& p, int m, int d, T start, T end );
    void                      resampleInline( DVector< DVector< Vector<T, n> > >& p, int m, T dt );
    void                      resamplePreEval( DVector< DVector< Vector<T, n> > >& p, int m, T dt );
  };




} // END namespace GMlib

// Include PBezierCurve class function implementation
#include "gmPBezierCurve.c"

#endif // __gmPBEZIERCURVE_H__

