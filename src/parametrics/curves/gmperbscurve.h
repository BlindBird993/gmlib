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



/*! \file gmperbscurve.h
 *
 *  Interface for the PERBSCurve class.
 */

#ifndef __gmPERBSCURVE_H__
#define __gmPERBSCURVE_H__


#include "../gmpcurve.h"

#include "../evaluators/gmerbsevaluator.h"


namespace GMlib {


  template <typename T>
  class PERBSCurve : public PCurve<T> {
  public:

    enum CURVE_TYPE {
      SUB_CURVE   = 0,
      ARC_CURVE   = 1,
      BEZIERCURVE = 2
    };

    PERBSCurve(); // Dummy
    PERBSCurve( CURVE_TYPE type, PCurve<T>* g, int n, int d = 2 );
    PERBSCurve( const PERBSCurve<T>& copy );
    virtual ~PERBSCurve();

    void                            edit( SceneObject *obj );
    DVector< PCurve<T>* >&          getLocalPatches();
    int                             getNoLocalPatches() const;
    virtual void                    hideLocalPatches();
    bool                            isLocalPatchesVisible() const;
    virtual void                    showLocalPatches();
    void                            setResampleMode( GM_RESAMPLE_MODE mode );
    virtual void                    toggleLocalCurvesVisible();

    // virual functions from PSurf
    bool                            isClosed() const;
    void                            preSample( int m, int d, T start, T end );

  protected:
    bool                            _closed;
    DVector<T>                      _t;
    DVector<PCurve<T>*>             _c;

    BasisEvaluator<long double>*    _evaluator;

    // Using pre evaulating of GERBS-basis functions
    GM_RESAMPLE_MODE                _resamp_mode;
    bool                            _pre_eval; // To mark that pre eval is done
    DVector< int >                  _tk;       // pre evaluation vector
    DVector< DVector<T> >           _B;        // Storing sample values - GERBS

    // virual functions from PSurf
    void                            eval( T t, int d = 0, bool l = false );
    T                               getEndP();
    T                               getStartP();

    // Local help functions
    int                             findIndex( T t);// const;
    void                            getB( DVector<T>& B, int tk, T t, int d );

  private:
    // Local help functions
    void                            compEval( T t, int d, int k, const DVector<T>& B );
    void                            generateKnotVector( PCurve<T>* g, int n );
    virtual void                    init();
    void                            insertLocal( PCurve<T> *patch );
    PCurve<T>*                      makeLocal( CURVE_TYPE type, PCurve<T>* g, T s, T t, T e, int d=2);

  }; // END class PERBSCurve

} // END namepace GMlib

// Include PERBSCurve class function implementations
#include "gmperbscurve.c"


#endif // __gmDPERBSCURVE_H__


