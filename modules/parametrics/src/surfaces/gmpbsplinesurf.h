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




#ifndef GM_PARAMETRICS_SURFACE_PBSPLINESURF_H
#define GM_PARAMETRICS_SURFACE_PBSPLINESURF_H


#include "../gmpsurf.h"


namespace GMlib {

  template <typename T, int n>
  class Selector;

  template <typename T>
  class SelectorGridVisualizer;


  template <typename T>
  class PBSplineSurf : public PSurf<T,3> {
    GM_SCENEOBJECT(PBSplineSurf)

  public:
    PBSplineSurf( const DMatrix< Vector<T,3> >& c, const DVector<T>& u,  const DVector<T>& v);
    PBSplineSurf( const PBSplineSurf<T>& dpbs );
    virtual ~PBSplineSurf();

    virtual void                  edit( int selector ) override;
    DMatrix< Vector<T,3> >&       getControlPoints();
    int                           getDegreeU() const;
    int                           getDegreeV() const;
    virtual void                  hideSelectors();
    bool                          isClosedU() const override;
    bool                          isClosedV() const override;
    bool                          isSelectorsVisible() const;
    void                          preSample( int m1, int m2, int d1, int d2, T s_u = T(0), T s_v = T(0), T e_u = T(0), T e_v = T(0) ) override;
    void                          setClosed( bool closed_u, bool closed_v );
    void                          setControlPoints( const DMatrix< Vector<T,3> >& cp );
    void                          setResampleMode( GM_RESAMPLE_MODE mode );
    void                          setScale( T du, T dv );
    virtual void                  showSelectors( bool grid = false, const Color& _selector_color = GMcolor::darkBlue(), const Color& grid_color = GMcolor::lightGreen() );
    void                          updateCoeffs( const Vector<T,3>& d );


  protected:
    DMatrix< Vector<T,3> >        _c;  // controll polygon
    DVector<T>                    _u;  // knot vector u-direction
    DVector<T>                    _v;  // knot vector v-direction
    int                           _du; // degree in u-direction
    int                           _dv; // degree in v-direction
    int                           _ku; // order in u-direction
    int                           _kv; // order in v-direction

    T                             _su;
    T                             _sv;
    DMatrix< DMatrix< T > >       _ru;
    DMatrix< DMatrix< T > >       _rv;
    bool                          _cu;
    bool                          _cv;

    GM_RESAMPLE_MODE              _resamp_mode;
    bool                          _pre_eval;

    bool                          _selectors;
    SelectorGridVisualizer<T>    *_sgv;
    DMatrix< Selector<T,3>* >     _s;
    bool                          _c_moved;

    void                          eval( T u, T v, int d1 = 0, int d2 = 0, bool lu = false, bool lv = false ) override;
    void                          evalPre( T u, T v, int d1 = 0, int d2 = 0, bool lu = false, bool lv = false );
    void                          findIndex( T u, T v, int& iu, int& iv );
    T                             getEndPU() override;
    T                             getEndPV() override;
    T                             getStartPU() override;
    T                             getStartPV() override;
    virtual void                  init();

  }; // END class PBSplineSurf




} // END namepace GMlib

// Include PBSplineSurf class function implementations
#include "gmpbsplinesurf.c"


#endif // GM_PARAMETRICS_SURFACE_PBSPLINESURF_H


