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



/*! \file gmPCurve.h
 *
 *  Interface for the gmPCurve class.
 *
 *  \date   2008-09-09
 */

#ifndef __gmPCURVE_H__
#define __gmPCURVE_H__


#include "gmArray.h"
#include "gmParametrics.h"



namespace GMlib {


  template <typename T>
  class PCurve : public Parametrics<T,1> {
  public:
    PCurve( int s = 20 );
    PCurve( const PCurve<T>& copy );

    DVector<Vector<T,3> >&    evaluate( T t, int d );
    DVector<Vector<T,3> >&    evaluateLocal( T t, int d );
    DVector<Vector<T,3> >&    evaluateParent( T t, int d );
    T                         getCurvature( T t );
    T                         getCurveLength( T a = 0, T b = -1 );
    Vector<T,3>               getDer1( T t );
    Vector<T,3>               getDer2( T t );
    std::string               getIdentity() const;
    float                     getLineWidth() const;
    virtual T                 getLocalMapping( T t, T ts, T ti, T te );
    int                       getNoDer() const;
    int                       getNoSamp() const;
    T                         getParDelta();
    T                         getParEnd();
    T                         getParStart();
    T                         getRadius( T t );
    T                         getSpeed( T t );
    virtual bool              isClosed() const;
    virtual void              preSample( int m, int d, T s = T(0), T e = T(0) );
    virtual void              replot( int m = 0, int d = 2 );
    void                      setDomain( T start, T end );
    void                      setDomainScale( T sc );
    void                      setDomainTrans( T tr );
    void                      setEval( int d );
    void                      setLineWidth( float width = 1.0 );
    virtual void              setSurroundingSphere( const DVector< DVector< Vector<T, 3> > >& p );

    Point<T,3>                operator()( T t );

  protected:
    int                       _no_der;
    int                       _no_samp;
    float                     _line_width;


    // Shift of parameter.
    T					                _tr;			// translate
    T					                _sc;			// scale

    T							            _s_sam;		// Først sampling value usually startPar()
    T							            _e_sam;		// Last sampling value usually endtPar()
    int							          _sam;			// Samplings-number
    int							          _defalt_d;		// used by operator() for number of derivative to evaluate.


    //************************************************************
    // xxxxx     The result of the previous evaluation!!!   xxxxxx
    //************************************************************
    DVector<Vector<T,3> >     _p;		// Position and belonging derivatives
    T						              _t;		// The parameter value used for last evaluation
    int						            _d;		// Number of derivatives computed last time


    //*********************************************************************
    //********   Virtual functions nessesary for inheritance !!!   ********
    //*  This functions must be implemented in the real parametric Curve  *
    //*********************************************************************
    virtual void	            eval(T t, int d, bool l = true ) = 0;
    virtual T		              getStartP() {return T(0);}
    virtual T		              getEndP() {return T(0);}

    //**************************************************************
    //********   Virtual functions already implemented !!!   *******
    //**  Must only be implemented if you want something special  **
    //**************************************************************
    virtual void              resample( Array<Point<T,3> >& a, T eps );	// Always smooth, requires derivatives
    virtual void              resample( Array<Point<T,3> >& a, int m );					// Given sampling rate
    virtual void              resample( Array<Point<T,3> >& a, int m, T start, T end );	// Given sampling rate
    virtual void              resample( DVector< DVector< Vector<T, 3> > >& p, int m, int d, T start, T end );


    T					                shift( T t );


  private:
    void	                    _eval( T t, int d );
    void                      _evalDerDD( DVector< DVector< Vector<T, 3> > > & p, int d, T du ) const;
    void                      _init();
    T		                      _integral(T a, T b, double eps);

  }; // END class PCurve

} // END namespace GMlib

// Include PCurve class function implementations
#include "gmPCurve.c"


#endif  // __gmPCURVE_H__

