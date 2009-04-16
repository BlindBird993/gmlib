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



/*! \file gmDPERBSSurf.h
 *
 *  Interface for the gmDPERBSSurf class.
 *
 *  \date   2008-10-28
 */

#ifndef __gmDPERBSSURF_H__
#define __gmDPERBSSURF_H__


// GMlib includes+
#include "gmDSurf.h"
#include "gmPERBSSurf.h"


namespace GMlib {


  template <typename T>
  class DPERBSSurf : public DSurf<T> {
  public:
    DPERBSSurf( DSurf<T>* g, int no_locals_u, int no_locals_v, int d1, int d2 );
    DPERBSSurf( const DMatrix< DPBezierSurf<T>* >& c, DVector<T> u, DVector<T> v, bool closed_u, bool closed_v );
    DPERBSSurf( const DPERBSSurf<T>& copy );
//    DPERBSSurf( const PERBSSurf<T,3>& copy );
//    DPERBSSurf( PERBSSurf<T,3>* copy );
    virtual ~DPERBSSurf();


    void                      edit( SceneObject *obj );
    string                    getIdentity() const;
//    virtual PERBSSurf<T,3>*   getPERBSSurf();
    virtual void              hideLocalPatches();
    bool                      isLocalPatchesVisible() const;
    virtual void              showLocalPatches( bool collapsed = true );

  protected:
//    PERBSSurf<T,3>            *_l_ref;
//    DMatrix< DSurf<T>* >      _patches;
//    bool                      _patches_visible;

    virtual void              init();
    void                      insertPatch( DSurf<T> *patch );
    void                      localDisplay();
    virtual void              visualizeLocalPatch( PSurf<T,3>* p, int i, int j, int n, int m, bool collapsed );
    virtual void              visualizeLocalPatchInit( int i, int j, int n, int m, bool collapsed );



  //////////////////////// PERBSSurf !!!!!!!!!!!!!! PERBSSurf ////////////////////////
  //////////////////////// PERBSSurf !!!!!!!!!!!!!! PERBSSurf ////////////////////////
  //////////////////////// PERBSSurf !!!!!!!!!!!!!! PERBSSurf ////////////////////////
  //////////////////////// PERBSSurf !!!!!!!!!!!!!! PERBSSurf ////////////////////////

  public:
    void                      generateKnotVector( DSurf<T>* g );
    DVector<T>&               getKnotsU();
    DVector<T>&               getKnotsV();
    DMatrix<DSurf<T>* >&      getLocalPatches();
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
    DMatrix< DMatrix< Vector<T,3> > >     _c0;
    DMatrix< DMatrix< Vector<T,3> > >     _c1;



    DMatrix< int >            _uk;
    DMatrix< int >            _vk;
    DVector<T>                _u;
    DVector<T>                _v;
//
    GM_RESAMPLE_MODE          _resamp_mode;
    bool                      _pre_eval;

    DMatrix< DSurf<T>* >      _c;


    void	                    eval( T u, T v, int d1 = 0, int d2 = 0, bool lu = false, bool lv = false );
    void                      generateKnotVector( DVector<T>& kv, const T s, const T d, int kvd, bool closed );
    void                      getB( DVector<T>& B, const DVector<T>& kv, int tk, T t, int d );
    DMatrix< Vector<T,3> >    getC( T u, T v, int uk, int vk, T du, T dv );
    DMatrix< Vector<T,3> >    getCPre( T u, T v, int uk, int vk, T du, T dv, int i, int j );
    T                         getEndPU();
    T                         getEndPV();
    T                         getStartPU();
    T                         getStartPV();
    void                      resample( DMatrix<DMatrix <Vector<T,3> > >& p, int m1, int m2, int d1, int d2, T s_u, T s_v, T e_u, T e_v );
    void                      resampleInline( DMatrix<DMatrix <Vector<T,3> > >& p, int m1, int m2, T du, T dv );
    void                      resamplePreEval( DMatrix<DMatrix <Vector<T,3> > >& p, int m1, int m2, T du, T dv );
  };




} // END namepace GMlib

// Include DPERBSSurf class function implementations
#include "gmDPERBSSurf.c"


#endif // __gmDPERBSSURF_H__



