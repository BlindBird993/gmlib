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



/*! \file gmPBezierSurf.h
 *
 *  Interface for the PBezierSurf class.
 *
 *  \date   2008-11-20
 */

#ifndef __gmPBEZIERSURF_H__
#define __gmPBEZIERSURF_H__

// STL
#include <iostream>

// GMlib includes
#include "gmPSurf.h"


namespace GMlib {


  template <typename T, int n>
  class PBezierSurf : public PSurf<T, n> {
  public:

    PBezierSurf( const DMatrix< Vector<T, n> >& c );
    PBezierSurf( const DMatrix< Vector<T, n> >& c, T us, T u, T ue, T vs, T v, T ve );
    PBezierSurf( const PBezierSurf<T, n>& pbc );

    DMatrix< Vector<T,n> >&   getControlPoints();
    int                       getDegreeU() const;
    int                       getDegreeV() const;
    std::string               getIdentity() const;
    T                         getLocalMapping( T t, T ts, T tt, T te );
    bool                      isClosedU() const;
    bool                      isClosedV() const;
    void                      setClosed( bool closed_u, bool closed_v );
    void                      setControlPoints( const DMatrix< Vector<T, n> >& cp );
    void                      setResampleMode( GM_RESAMPLE_MODE mode );
    void                      setScale( T du, T dv );


  protected:
    DMatrix< Vector<T, n> >   _c;
    T                         _su;
    T                         _sv;
    DMatrix< DMatrix< T > >   _u;
    DMatrix< DMatrix< T > >   _v;
    bool                      _cu;
    bool                      _cv;

    GM_RESAMPLE_MODE          _resamp_mode;
    bool                      _pre_eval;

    void	                    eval( T u, T v, int d1 = 0, int d2 = 0, bool lu = false, bool lv = false );
    T                         getEndPU();
    T                         getEndPV();
    T                         getStartPU();
    T                         getStartPV();

    void                      resample(DMatrix<DMatrix <Vector<T,n> > >& a, int m1, int m2, int d1, int d2, T s_u = T(0), T s_v = T(0), T e_u = T(0), T e_v = T(0));
    void                      resampleInline( DMatrix< DMatrix< Vector<T, n> > >& p, int m1, int m2, T du, T dv );
    void                      resamplePreEval( DMatrix< DMatrix< Vector<T, n> > >& p, int m1, int m2, T du, T dv );

  };




} // END namespace GMlib

// Include PBezierSurf class function implementation
#include "gmPBezierSurf.c"

#endif // __gmPBEZIERSURF_H__

