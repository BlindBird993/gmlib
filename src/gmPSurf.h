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



/*! \file gmPSurf.h
 *
 *  Interface for the PSurf class.
 *
 *  \date   2008-09-04
 */

#ifndef __gmDSURF_H__
#define __gmDSURF_H__

// STL
#include <fstream>

// Local
#include "gmArray.h"
#include "gmParametrics.h"

namespace GMlib {

  template <typename T>
  class PSurf : public Parametrics<T,2> {
  public:

    PSurf();
    PSurf( const PSurf<T>& copy );

    //virtual void                  estimateClpPar( const Point<T,3>& p, T& u, T& v );
    DMatrix<Vector<T,3> >&	      evaluate( Point<T,2> p, int d );
    DMatrix<Vector<T,3> >&    	  evaluate( T u, T v, int d1, int d2 );
    DVector<Vector<T,3> >	        evaluateD( Point<T,2> p, int d );
    DVector<Vector<T,3> >	        evaluateD( T u, T v, int d1, int d2 );
    DMatrix<Vector<T,3> >&    	  evaluateLocal( Point<T,2> p, int d );
    DMatrix<Vector<T,3> >&    	  evaluateLocal( T u, T v, int d1, int d2 );
    DMatrix<Vector<T,3> >&    	  evaluateParent( Point<T,2> p, int d );
    DMatrix<Vector<T,3> >&    	  evaluateParent( T u, T v, int d1, int d2 );
    virtual T                     getCurvatureGauss( T u, T v );
    virtual T                     getCurvatureMean( T u, T v );
    int                           getDerU();
    Vector<T,3>&                  getDerU( T u, T v );
    int                           getDerV();
    Vector<T,3>&                  getDerV( T u, T v );
    Vector<T,3>&                  getDerUU( T u, T v );
    Vector<T,3>&                  getDerVV( T u, T v );
    Vector<T,3>&                  getDerUV( T u, T v );
    std::string                   getIdentity() const;
    virtual T                     getLocalMapping( T t, T ts, T tt, T te );
    int                           getNoDerU() const;
    int                           getNoDerV() const;
    int                           getNoSampU() const;
    int                           getNoSampV() const;
    Vector<T,3>&                  getNormal();
    T                             getParDeltaU();
    T                             getParDeltaV();
    T                             getParStartU();
    T                             getParStartV();
    T                             getParEndU();
    T                             getParEndV();
    int                           getSamU( int i = 0 );
    int                           getSamV( int i = 0 );
    virtual bool                  isClosedU() const;
    virtual bool                  isClosedV() const;
    virtual bool                  isClosestPoint( const Point<T,3>& q, T& u, T& v );
    void                          replot( int m1 = 0, int m2 = 0, int d1 = 2, int d2 = 2 );
    virtual void                  resample(DMatrix<DMatrix <DMatrix <Vector<T,3> > > >	& a, int m1, int m2, int d1, int d2 );
    virtual void                  resample(DMatrix<DMatrix <Vector<T,3> > >& a, int m1, int m2, int d1, int d2, T s_u = T(0), T s_v = T(0), T e_u = T(0), T e_v = T(0));
    virtual void                  resampleNormals( const DMatrix<DMatrix<Vector<T, 3> > > &sample, DMatrix<Vector<T, 3> > &normals ) const;
    void                          setDomainU( T start, T end );
    void                          setDomainUScale( T sc );
    void                          setDomainUTrans( T tr );
    void                          setDomainV( T start, T end );
    void                          setDomainVScale( T sc );
    void                          setDomainVTrans( T tr );
    void                          setEval( int d );
    virtual void                  setSurroundingSphere( const DMatrix< DMatrix< Vector<T, 3> > >& p );
    virtual Parametrics<T,2>*     split( T t, int uv );

    Point<T,3>&                   operator () ( T u, T v );

  protected:
    int                           _no_der_u;
    int                           _no_der_v;
    int                           _no_samp_u;
    int                           _no_samp_v;



    // ****************************
    // Storing samling informations

    // The sampling partition in u. Default first sampling value is
    // getStartParU() and last sampling value is usually getEndParU().
    DVector<T>			              _sam_p_u;

    // The sampling partition in v. Default first sampling value is
    // getStartParV() and last sampling value is usually getEndParV().
    DVector<T>			              _sam_p_v;

    // Samplings-number u directions for each partition.
    DVector<int>		              _sam1;

    // Samplings-number v directions for each partition.
    // NB! Invariant!! dim of _sam* = dim of _sam_p_* -1.
    DVector<int>		              _sam2;

    // Used by operator() for number of derivative to evaluate.
    int					                  _default_d;


    // *************************************
    // The result of the previous evaluation

    DMatrix< Vector<T,3> >        _p;		      // Position and belonging partial derivatives
    Vector<T,3>				            _n;		      // Surface normal, for display in 3D
    T						                  _u;		      // The parameter value in u-direction used for last evaluation
    T						                  _v;		      // The parameter value in v-direction used for last evaluation
    int						                _d1;		    // Number of derivatives in u-direction computed last time
    int						                _d2;		    // Number of derivatives in v-direction computed last time
    bool					                _diagonal;  // True if only upper left half of matrix is evaluated.


    // ******************
    // Shift of parameter
    T	                            _tr_u;		        // Translate u-parametre
    T	                            _sc_u;		        // Scale u-parametre

    T	                            _tr_v;		        // Translate v-parametre
    T	                            _sc_v;		        // Scale v-parametre


    virtual void                  eval( T u, T v, int d1, int d2, bool lu = true, bool lv = true ) = 0;
    virtual T                     getEndPU() { return T(0); } // = 0;
    virtual T                     getEndPV() { return T(0); } // = 0;
    virtual T                     getStartPU() { return T(0); } //  = 0;
    virtual T                     getStartPV() { return T(0); } // = 0;
    T                             shiftU(T u);
    T	                            shiftV(T v);

  private:
    void                          _eval( T u, T v, int d1, int d2 );
    void                          _evalDerDD( DMatrix< DMatrix< Vector<T,3> > >& a, int d1, int d2, T du, T dv ) const;
    void                          _evalNormal();
    void                          _init();
    void                          _setSam( int m1, int m2 );
    int                           _sum( int i, int j );


  };

}

// Include PSurf class function implementations
#include "gmPSurf.c"


#endif  //__gmDSURF_H__
