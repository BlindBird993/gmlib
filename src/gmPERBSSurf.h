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



/*! \file gmPERBSSurf.h
 *
 *  Interface for the PERBSSurf class.
 *
 *  \date   2008-11-20
 */

#ifndef __gmPERBSSURF_H__
#define __gmPERBSSURF_H__

// STL
#include <iostream>

// GMlib includes
#include "gmPSurf.h"
//#include "gmDPERBSSurf.h"
#include "gmPBezierSurf.h"
#include "gmEvaluatorERBS.h"


namespace GMlib {


  template <typename T, int n>
  class PERBSSurf : public PSurf<T, n> {
  public:
    PERBSSurf();  // Dummy
    PERBSSurf( const DMatrix< PBezierSurf<T,n>* >& c, DVector<T> u, DVector<T> v, bool closed_u, bool closed_v );
    PERBSSurf( PSurf<T,n>* g, int no_locals_u, int no_locals_v, int d1, int d2 );
    ~PERBSSurf();


    void                      generateKnotVector( PSurf<T,n>* g );
    std::string               getIdentity() const;
    DVector< T>&              getKnotsU();
    DVector< T>&              getKnotsV();
    DMatrix< PSurf<T,n>* >&   getLocalPatches();
    bool                      isClosedU() const;
    bool                      isClosedV() const;
    void                      setResampleMode( GM_RESAMPLE_MODE mode );
//    void                      setScale( T d );

  protected:
    bool                      _closed_u;
    bool                      _closed_v;

    EvaluatorERBS<T>          *_evaluator;


    DMatrix< DVector<T> >     _Bu;
    DMatrix< DVector<T> >     _Bv;
    DVector< DVector<T> >     _Bc;
    DMatrix< DMatrix< Vector<T,n> > >     _c0;
    DMatrix< DMatrix< Vector<T,n> > >     _c1;



    DMatrix< int >            _uk;
    DMatrix< int >            _vk;
    DVector<T>                _u;
    DVector<T>                _v;
//
    GM_RESAMPLE_MODE          _resamp_mode;
    bool                      _pre_eval;

    DMatrix< PSurf<T,n>* >    _c;


    void	                    eval( T u, T v, int d1 = 0, int d2 = 0, bool lu = false, bool lv = false );
    void                      generateKnotVector( DVector<T>& kv, const T s, const T d, int kvd, bool closed );
    void                      getB( DVector<T>& B, const DVector<T>& kv, int tk, T t, int d );
    DMatrix< Vector<T,n> >    getC( T u, T v, int uk, int vk, T du, T dv );
    DMatrix< Vector<T,n> >    getCPre( T u, T v, int uk, int vk, T du, T dv, int i, int j );
    T                         getEndPU();
    T                         getEndPV();
    T                         getStartPU();
    T                         getStartPV();
    void                      init();
    void                      resample( DMatrix<DMatrix <Vector<T,n> > >& p, int m1, int m2, int d1, int d2, T s_u, T s_v, T e_u, T e_v );
    void                      resampleInline( DMatrix<DMatrix <Vector<T,n> > >& p, int m1, int m2, T du, T dv );
    void                      resamplePreEval( DMatrix<DMatrix <Vector<T,n> > >& p, int m1, int m2, T du, T dv );

  };




} // END namespace GMlib

// Include PERBSSurf class function implementation
#include "gmPERBSSurf.c"

#endif // __gmPERBSSURF_H__



