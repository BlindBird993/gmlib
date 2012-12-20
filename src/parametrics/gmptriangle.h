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



/*! \file gmptriangle.h
 *
 *  Interface for the PTriangle class.
 */

#ifndef __gmPTRIANGLE_H__
#define __gmPTRIANGLE_H__


#include "gmparametrics.h"

// gmlib
#include <core/types/gmpoint.h>
#include <core/containers/gmdvector.h>


namespace GMlib {

  template <typename T>
  class PTriangleVisualizer;

  template <typename T>
  class PTriangle : public Parametrics<T,2> {

  public:
    PTriangle( int samples = 20 );
    PTriangle( const PTriangle<T>& copy );

    ~PTriangle();


    const DVector<Vector<T,3> >&      evaluateGlobal( T u, T v, int d);
    const DVector<Vector<T,3> >&      evaluateLocal( T u, T v, int d);
    const DVector<Vector<T,3> >&      evaluateParent( T u, T v, int d);

    const Point<T,3>&                 operator()( T u, T v ); // w = 1-u-v
    const Vector<T,3>&                getDerU( T u, T v );
    const Vector<T,3>&                getDerV( T u, T v );
    const Vector<T,3>&                getDerW( T u, T v );
    const Vector<T,3>&                getDerUU( T u, T v );
    const Vector<T,3>&                getDerUV( T u, T v );
    const Vector<T,3>&                getDerUW( T u, T v );
    const Vector<T,3>&                getDerVV( T u, T v );
    const Vector<T,3>&                getDerVW( T u, T v );
    const Vector<T,3>&                getDerWW( T u, T v );
    const Vector<T,3>&                getNormal( T u, T v );
    UnitVector<T,3>                   getUnitNormal( T u, T v );

    virtual T                         getCurvatureGauss( T u, T v );
    virtual T                         getCurvatureMean( T u, T v );


    const DVector<Vector<T,3> >&      evaluateGlobal(const Point<T,3> & p, int d);
    const DVector<Vector<T,3> >&      evaluateLocal(const Point<T,3> & p, int d);
    const DVector<Vector<T,3> >&      evaluateParent(const Point<T,3> & p, int d);

    const Point<T,3>&                 operator()(const Point<T,3> & p);
    const Vector<T,3>&                getDerU(const Point<T,3> & p);
    const Vector<T,3>&                getDerV(const Point<T,3> & p);
    const Vector<T,3>&                getDerW(const Point<T,3> & p);
    const Vector<T,3>&                getDerUU(const Point<T,3> & p);
    const Vector<T,3>&                getDerUV(const Point<T,3> & p);
    const Vector<T,3>&                getDerUW(const Point<T,3> & p);
    const Vector<T,3>&                getDerVV(const Point<T,3> & p);
    const Vector<T,3>&                getDerVW(const Point<T,3> & p);
    const Vector<T,3>&                getDerWW(const Point<T,3> & p);
    const Vector<T,3>&                getNormal(const Point<T,3> & p);
    UnitVector<T,3>                   getUnitNormal(const Point<T,3> & p);

    T                                 getCurvatureGauss(const Point<T,3> & p);
    T                                 getCurvatureMean(const Point<T,3> & p);

    const Vector<T,3>&                getDer_d(const Point<T,3> & p, const Vector<T,3> & d);


    void                              enableDefaultVisualizer( bool enable = true );
    void                              toggleDefaultVisualizer();
    void                              insertVisualizer( Visualizer *visualizer );
    void                              removeVisualizer( Visualizer *visualizer );

    virtual void                      replot( int m = 0 );
    virtual void                      resample( DVector<DVector<Vector<T, 3> > > &p, int m );


    std::string                       getIdentity() const;

    void                              setEval(int d);
    Parametrics<T,2>*                 split( T t, int uv );

    virtual void                      updateCoeffs( const Vector<T,3>& d );
    virtual bool                      isClosestPoint( const Point<T,3>& p, T& u, T& v );
//    virtual void                      estimateClpPar(const Point<T,n>& p, T& u, T& v) {}
//    virtual void                      setBp( Array<Point<T,n> >bp ) {}

    void                              setTriangNr(bool all = true, int nr = 0);

    virtual Vector<Point<T,3>,3>      getPoints();

  protected:
    Array< PTriangleVisualizer<T>* >  _ptriangle_visualizers;
    PTriangleVisualizer<T>            *_default_visualizer;

    int                               _no_sam;      //  int		__sam;
    DVector< Vector<T,3> >            _p;           //  DMatrix<Vector<T,n> >	__p;
    Vector<T,3>                       _n;           //  Vector<T,3>		__n; // For display in 3D
    T                                 _u;           //  T	__u;
    T                                 _v;           //  T	__v;
    int                               _d;           //  int	__d;
    bool                              _diagonal;    //  bool	__diagonal; // True if only upper left half is evaluated.
    int                               _default_d;   //  int	__defalt_d; // used by operator() for number of derivative to evaluate.

    bool                              _all;
    int                               _t_nr;
    Point<T,3>                        _pt[4];

    virtual void                      eval( T u, T v, T w, int d ) = 0;
    void                              eval( const Point<T,3>& p, int d ) { eval(p(0),p(1),p(2),d); }

    virtual void                      setSurroundingSphere( const DVector<DVector<Vector<T, 3> > > &p );

  private:
    void                              _eval( T u, T v, int d );
    int                               _sum(int i);
    void                              _init();

    void _fuForm( T u, T v, T& E, T& F, T& G, T& e, T& f, T& g);

    void                              resample1( DVector<DVector<Vector<T, 3> > > &p, int m );
    void                              resample2( DVector<DVector<Vector<T, 3> > > &p, int m, int a, int b );
  }; // END class PTriangle





} // END namespace GMlib



// Include PTriangle class function implementations
#include "gmPTriangle.c"

#endif // __gmPTRIANGLE_H__
