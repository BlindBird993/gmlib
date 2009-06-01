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



/*! \file gmDPERBSCurve.h
 *
 *  Interface for the DPERBSCurve class.
 *
 *  \date   2008-10-31
 */

#ifndef __gmDPERBSCURVE_H__
#define __gmDPERBSCURVE_H__


// GMlib includes+
#include "gmDCurve.h"
#include "gmPERBSCurve.h"


namespace GMlib {


  template <typename T>
  class DPERBSCurve : public DCurve<T> {
  public:
    DPERBSCurve(); // Dummy
    DPERBSCurve( DCurve<T>* g, int no_locals );
    DPERBSCurve( DCurve<T>* g, int no_locals, int d );
    DPERBSCurve( const DPERBSCurve<T>& copy );
//    DPERBSCurve( const PERBSCurve<T,3>& copy );
//    DPERBSCurve( PERBSCurve<T,3>* copy );
    virtual ~DPERBSCurve();

    void                        edit( SceneObject *obj );
    string                      getIdentity() const;
//    virtual PERBSCurve<T,3>*    getPERBSCurve();
    virtual void                hideLocalPatches();
    bool                        isLocalPatchesVisible() const;
    virtual void                showLocalPatches();

  protected:
//    PERBSCurve<T,3>             *_l_ref;
//    DVector< DCurve<T>* >       _patches;
//    bool                        _patches_visible;


    virtual void                init();
    void                        insertPatch( DCurve<T> *patch );
    void                        localDisplay();
    virtual void                visualizeLocalPatch( PCurve<T,3>* p, int i, int m, bool collapsed );
    virtual void                visualizeLocalPatchInit( int i, int m, bool collapsed );






  //////////////////////// DPERBSCurve !!!!!!!!!!!!!! DPERBSCurve ////////////////////////
  //////////////////////// DPERBSCurve !!!!!!!!!!!!!! DPERBSCurve ////////////////////////
  //////////////////////// DPERBSCurve !!!!!!!!!!!!!! DPERBSCurve ////////////////////////
  //////////////////////// DPERBSCurve !!!!!!!!!!!!!! DPERBSCurve ////////////////////////



  public:
    void                        generateKnotVector( DCurve<T>* g );
    DVector< DCurve<T>* >&      getLocalPatches();
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


    DVector< DCurve<T>* >       _c;

    void	                      eval( T t, int d = 0, bool l = false );
    void                        getB( DVector<T>& B, int tk, T t, int d );
    T                           getEndP();
    T                           getStartP();
    void                        resample( DVector< DVector< Vector<T,3> > >& p, int m, int d, T start, T end );
    void                        resampleInline( DVector< DVector< Vector<T,3> > >& p, int m, T dt );
    void                        resamplePreEval( DVector< DVector< Vector<T,3> > >& p, int m, T dt );

  };




} // END namepace GMlib

// Include DPERBSCurve class function implementations
#include "gmDPERBSCurve.c"


#endif // __gmDPERBSCURVE_H__


