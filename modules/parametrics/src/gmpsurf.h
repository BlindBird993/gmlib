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



/*! \file gmpsurf.h
 *
 *  Interface for the PSurf class.
 */

#ifndef __gmDSURF_H__
#define __gmDSURF_H__


#include "gmparametrics.h"

// gmlib
#include <core/containers/gmarray.h>
#include <core/containers/gmdvector.h>
#include <core/containers/gmdmatrix.h>

// stl
#include <fstream>


namespace GMlib {

  template <typename T, int n>
  class PSurfVisualizer;

  template <typename T, int n>
  class PSurfDefaultVisualizer;

  template <typename T,int n>
  class PSurf : public Parametrics<T,2,n> {
  public:

    PSurf( int s1 = 20, int s2 = 20 );
    PSurf( const PSurf<T,n>& copy );
    virtual ~PSurf();

    //virtual void                  estimateClpPar( const Point<T,n>& p, T& u, T& v );
    DMatrix<Vector<T,n> >&        evaluate( const APoint<T,2>& p, const APoint<int,2>& d );
    DMatrix<Vector<T,n> >&        evaluate( T u, T v, int d1, int d2 );
    DVector<Vector<T,n> >         evaluateD( const APoint<T,2>& p, const APoint<int,2>& d );
    DVector<Vector<T,n> >         evaluateD( T u, T v, int d1, int d2 );
    DMatrix<Vector<T,n> >&        evaluateGlobal( const APoint<T,2>& p, const APoint<int,2>& d );
    DMatrix<Vector<T,n> >&        evaluateGlobal( T u, T v, int d1, int d2 );
    DMatrix<Vector<T,n> >&        evaluateParent( const APoint<T,2>& p, const APoint<int,2>& d );
    DMatrix<Vector<T,n> >&        evaluateParent( T u, T v, int d1, int d2 );
    virtual T                     getCurvatureGauss( T u, T v );
    virtual T                     getCurvatureMean( T u, T v );
    virtual T                     getCurvaturePrincipalMax( T u, T v );
    virtual T                     getCurvaturePrincipalMin( T u, T v );
    int                           getDerivativesU() const;
    int                           getDerivativesV() const;
    Vector<T,n>&                  getDerU( T u, T v );
    Vector<T,n>&                  getDerV( T u, T v );
    Vector<T,n>&                  getDerUU( T u, T v );
    Vector<T,n>&                  getDerVV( T u, T v );
    Vector<T,n>&                  getDerUV( T u, T v );
    Vector<T,n>&                  getNormal();
    T                             getParDeltaU();
    T                             getParDeltaV();
    T                             getParStartU();
    T                             getParStartV();
    T                             getParEndU();
    T                             getParEndV();
    Vector<T,n>&                  getPosition( T u, T v );
    int                           getSamPU( int i = 0 ) const;
    int                           getSamPV( int i = 0 ) const;
    int                           getSamplesU() const;
    int                           getSamplesV() const;
    virtual bool                  isClosedU() const;
    virtual bool                  isClosedV() const;
    virtual bool                  getClosestPoint( const Point<T,n>& q, T& u, T& v );
    bool                          getClosestPoint( const Point<T,n>& q, Point<T,2>& uv );
    virtual void                  preSample( int m1, int m2, int d1, int d2, T s_u = T(0), T s_v = T(0), T e_u = T(0), T e_v = T(0) );
    virtual void                  replot( int m1 = 0, int m2 = 0, int d1 = 0, int d2 = 0 );
    void                          resample(DMatrix<DMatrix <DMatrix <Vector<T,n> > > >	& a, int m1, int m2, int d1, int d2 );
    virtual void                  resample(DMatrix<DMatrix <Vector<T,n> > >& a, int m1, int m2, int d1, int d2, T s_u = T(0), T s_v = T(0), T e_u = T(0), T e_v = T(0));
    virtual void                  resampleNormals( const DMatrix<DMatrix<Vector<T,n> > > &sample, DMatrix<Vector<T,3> > &normals ) const;
    void                          setDomainU( T start, T end );
    void                          setDomainUScale( T sc );
    void                          setDomainUTrans( T tr );
    void                          setDomainV( T start, T end );
    void                          setDomainVScale( T sc );
    void                          setDomainVTrans( T tr );
    void                          setNoDer( int d );
    virtual void                  setSurroundingSphere( const DMatrix< DMatrix< Vector<T,n> > >& p );
    virtual Parametrics<T,2,n>*   split( T t, int uv );

    void                          enableDefaultVisualizer( bool enable = true );
    PSurfVisualizer<T,n>*         getDefaultVisualizer() const;
    void                          toggleDefaultVisualizer();
    void                          insertVisualizer( Visualizer *visualizer );
    void                          removeVisualizer( Visualizer *visualizer );

    const Point<T,n>&             operator () ( T u, T v );

  protected:
    Array< PSurfVisualizer<T,n>* >  _psurf_visualizers;
    PSurfVisualizer<T,n>          *_default_visualizer;

    int                           _no_sam_u;    // Number of samples u for single sampling
    int                           _no_sam_v;    // Number of samples v for single sampling

    int                           _no_der_u;    // Number of derivatives u
    int                           _no_der_v;    // Number of derivatives u

    DVector< Vector<T,2> >        _sam_p_u;     // Sample partition u (start/stop)
    DVector< Vector<T,2> >        _sam_p_v;     // Sample partition v (start/stop)

    DVector< int >                _no_sam_p_u;  // Number of samples for each sampling partition in u
    DVector< int >                _no_sam_p_v;  // Number of samples for each sampling partition in v


    // Used by operator() for number of derivative to evaluate.
    int                           _default_d;


    // The result of the previous evaluation
    DMatrix< Vector<T,n> >        _p;           // Position and belonging partial derivatives
    Vector<T,n>                   _n;           // Surface normal, for display in 3D
    T                             _u;           // The parameter value in u-direction used for last evaluation
    T                             _v;           // The parameter value in v-direction used for last evaluation
    int                           _d1;          // Number of derivatives in u-direction computed last time
    int                           _d2;          // Number of derivatives in v-direction computed last time
    bool                          _diagonal;    // True if only upper left half of matrix is evaluated.

    // Shift of parameter
    T                             _tr_u;        // Translate u-parametre
    T                             _sc_u;        // Scale u-parametre

    T                             _tr_v;        // Translate v-parametre
    T                             _sc_v;        // Scale v-parametre


    /*! virtual void PSurf<T,3>::eval( T u, T v, int d1, int d2, bool lu , bool lv ) = 0
     *  Surface evaluator. (Requires implementation in PSurf sub-classes.)
     *  \param[in]  u   Evaluation parameter in u-direction.
     *  \param[in]  v   Evaluation parameter in v-direction.
     *  \param[in]  d1  Number of derivatives to be computed for u.
     *  \param[in]  d2  Number of derivatives to be computed for v.
     *  \param[in]  lu  Whether to evaluate from left in u.
     *  \param[in]  lv  Whether to evaluate from left in v.
     */
    virtual void                  eval( T u, T v, int d1, int d2, bool lu = true, bool lv = true ) = 0;

    /*! virtual T PSurf<T,3>::getEndPU() = 0
     *  Returns the parametric end value in u-direction. (Requires implementation in PSurf sub-classes.)
     *  \return Parametric end value in u.
     */
    virtual T                     getEndPU() = 0;

    /*! virtual T PSurf<T,3>::getEndPV() = 0
     *  Returns the parametric end value in v-direction. (Requires implementation in PSurf sub-classes.)
     *  \return Parametric end value in v.
     */
    virtual T                     getEndPV() = 0;

    /*! virtual T PSurf<T,3>::getStartPU() = 0
     *  Returns the parametric start value in u-direction. (Requires implementation in PSurf sub-classes.)
     *  \return Parametric start value in u.
     */
    virtual T                     getStartPU() = 0;


    /*! virtual T PSurf<T,3>::getStartPV() = 0
     *  Returns the parametric start value in v-direction. (Requires implementation in PSurf sub-classes.)
     *  \return Parametric start value in v.
     */
    virtual T                     getStartPV() = 0;

    T                             shiftU(T u);
    T                             shiftV(T v);

  private:
    void                          _eval( T u, T v, int d1, int d2 );
    void                          _evalNormal();
//    void                          _setSam( int m1, int m2 );
    int                           _sum( int i, int j );


  }; // END class PSurf

} // END namespace GMlib

// Include PSurf class function implementations
#include "gmpsurf.c"


#endif  //__gmDSURF_H__