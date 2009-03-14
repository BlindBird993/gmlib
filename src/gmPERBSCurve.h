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



/*! \file gmPERBSCurve.h
 *
 *  Interface for the PERBSCurve class.
 *
 *  \date   2008-10-31
 */

#ifndef __gmPERBSCURVE_H__
#define __gmPERBSCURVE_H__

// STL
#include <iostream>

// GMlib includes
#include "gmPCurve.h"
#include "gmEvaluatorERBS.h"


namespace GMlib {


  template <typename T, int n>
  class PERBSCurve : public PCurve<T, n> {
  public:
    PERBSCurve();
    PERBSCurve( PCurve<T,n>* g, int no_locals, int d );
    PERBSCurve( PCurve<T,n>* g, int no_locals );
    ~PERBSCurve();

    void                        generateKnotVector( PCurve<T,n>* g );
    std::string                 getIdentity() const;
    DVector< PCurve<T,n>* >&    getLocalPatches();
    bool                        isClosed() const;
    void                        setResampleMode( GM_RESAMPLE_MODE mode );

  protected:

    bool                        _closed;

    EvaluatorERBS<T>            *_evaluator;


    DVector< DVector<T> >       _B;
    DVector< int >              _tk;
    DVector<T>                  _t;
//
    GM_RESAMPLE_MODE            _resamp_mode;
    bool                        _pre_eval;


    DVector< PCurve<T,n>* >     _c;

    void	                      eval( T t, int d = 0, bool l = false );
    void                        getB( DVector<T>& B, int tk, T t, int d );
    T                           getEndP();
    T                           getStartP();
    void                        init();
    void                        resample( DVector< DVector< Vector<T, n> > >& p, int m, int d, T start, T end );
    void                        resampleInline( DVector< DVector< Vector<T, n> > >& p, int m, T dt );
    void                        resamplePreEval( DVector< DVector< Vector<T, n> > >& p, int m, T dt );

  };




} // END namespace GMlib

// Include PERBSCurve class function implementation
#include "gmPERBSCurve.c"

#endif // __gmPERBSCURVE_H__


