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
//    DPBSplineCurve( const PBSplineCurve<T,3>& pbsc );
//    DPBSplineCurve( PBSplineCurve<T,3>* pbsc );
    virtual ~DPBSplineCurve();

//    virtual PBSplineCurve<T,3>*   getPBSplineCurve();

  protected:
//    PBSplineCurve<T,3>            *_l_ref;

    string                        getIdentity() const;
    virtual void                  init();


  //////////////////////// PBSplineCurve !!!!!!!!!!!!!! PBSplineCurve ////////////////////////
  //////////////////////// PBSplineCurve !!!!!!!!!!!!!! PBSplineCurve ////////////////////////
  //////////////////////// PBSplineCurve !!!!!!!!!!!!!! PBSplineCurve ////////////////////////
  //////////////////////// PBSplineCurve !!!!!!!!!!!!!! PBSplineCurve ////////////////////////

  public:
    int                       getDegree() const;
    void                      generateKnotVector();
    bool                      isClosed() const;
    void                      setControlPoints( const DVector< Vector<T,3> >& cv, bool gen_kv = true );
    void                      setDegree( int d );
    void                      setKnotVector( const DVector<T>& kv );
    void                      setResampleMode( GM_RESAMPLE_MODE mode );
    void                      setScale( T d );


  protected:
    DVector< Vector<T,3> >   _cp;
    T                         _scale;

    DVector< DMatrix< T > >   _bhps;
    DVector< int >            _indices;
    DVector<T>                _kv;
    int                       _degree;

    GM_RESAMPLE_MODE          _resamp_mode;
    bool                      _pre_eval;


    void	                    eval( T t, int d = 0, bool l = false );
    void                      evalBernsteinHermite( DMatrix<T>& bp_mat, T t, int idx ) const;
    T                         getEndP();
    int                       getIndex( T t, int m ) const;
    T                         getStartP();
    T                         getW( T t, int idx, int d ) const;
    T                         getWder( T t, int idx, int d ) const;
    void                      resample( DVector< DVector< Vector<T,3> > >& p, int m, int d, T start, T end );
    void                      resampleInline( DVector< DVector< Vector<T,3> > >& p, int m, T dt );
    void                      resamplePreEval( DVector< DVector< Vector<T,3> > >& p, int m, T dt );



  };




} // END namepace GMlib

// Include DPBSplineCurve class function implementations
#include "gmDPBSplineCurve.c"


#endif // __gmDPBSPLINECURVE_H__


