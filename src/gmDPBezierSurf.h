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



/*! \file gmDPBezierSurf.h
 *
 *  Interface for the gmDPBezierSurf class.
 *
 *  \date   2008-10-28
 */

#ifndef __gmDPBEZIERSURF_H__
#define __gmDPBEZIERSURF_H__


// GMlib includes+
#include "gmDSurf.h"
#include "gmPBezierSurf.h"
#include "gmSelector.h"
#include "gmSelectorGrid.h"


namespace GMlib {


  template <typename T>
  class DPBezierSurf : public DSurf<T> {
  public:
    DPBezierSurf( const DMatrix< Vector<T,3> >& cp );
    DPBezierSurf( const DMatrix< Vector<T,3> >& cp, T u_s, T u, T u_e, T v_s, T v, T v_e  );
    DPBezierSurf( const DPBezierSurf<T>& dpbs );
//    DPBezierSurf( const PBezierSurf<T,3>& pbs );
//    DPBezierSurf( PBezierSurf<T,3>* pbs );
    virtual ~DPBezierSurf();

    virtual void                edit( int selector );
//    virtual PBezierSurf<T,3>*   getPBezierSurf();
    virtual void                hideSelectors();
    bool                        isSelectorsVisible() const;
    void                        rotate(Angle a, const Vector<float,3>& rot_axel);
    void                        rotate(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d);
    void                        rotateGlobal(Angle a, const Vector<float,3>& rot_axel);
    void                        rotateGlobal(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d);

//    virtual void                setResampleMode( GM_RESAMPLE_MODE mode );
    virtual void                showSelectors( bool grid = false, const GLColor& _selector_color = GMcolor::DarkBlue, const GLColor& grid_color = GMcolor::LightGreen );
    void                        translate(const Vector<float,3>& trans_vector);
    void                        translateGlobal(const Vector<float,3>& trans_vector);

  protected:
    bool                        _selectors;
    SelectorGrid<T,3>*			    _sg;
    DMatrix< Selector<T,3>* >   _s;
//    PBezierSurf<T,3>*           _l_ref;

    string                      getIdentity() const;
    virtual void                init();
    void                        localDisplay();



  //////////////////////// PBezierSurf !!!!!!!!!!!!!! PBezierSurf ////////////////////////
  //////////////////////// PBezierSurf !!!!!!!!!!!!!! PBezierSurf ////////////////////////
  //////////////////////// PBezierSurf !!!!!!!!!!!!!! PBezierSurf ////////////////////////
  //////////////////////// PBezierSurf !!!!!!!!!!!!!! PBezierSurf ////////////////////////

  public:
    DMatrix< Vector<T,3> >&   getControlPoints();
    int                       getDegreeU() const;
    int                       getDegreeV() const;
    T                         getLocalMapping( T t, T ts, T tt, T te );
    bool                      isClosedU() const;
    bool                      isClosedV() const;
    void                      setClosed( bool closed_u, bool closed_v );
    void                      setControlPoints( const DMatrix< Vector<T,3> >& cp );
    void                      setResampleMode( GM_RESAMPLE_MODE mode );
    void                      setScale( T du, T dv );


  protected:
    DMatrix< Vector<T,3> >    _c;
    T                         _su;
    T                         _sv;
    DMatrix< DMatrix< T > >   _u;
    DMatrix< DMatrix< T > >   _v;
    bool                      _cu;
    bool                      _cv;

    GM_RESAMPLE_MODE          _resamp_mode;
    bool                      _pre_eval;

    void	                    eval( T u, T v, int d1 = 0, int d2 = 0, bool lu = false, bool lv = false );
    T                         getEndPU();
    T                         getEndPV();
    T                         getStartPU();
    T                         getStartPV();

    void                      resample( DMatrix<DMatrix <Vector<T,3> > >& a, int m1, int m2, int d1, int d2, T s_u = T(0), T s_v = T(0), T e_u = T(0), T e_v = T(0));
    void                      resampleInline( DMatrix< DMatrix< Vector<T,3> > >& p, int m1, int m2, T du, T dv );
    void                      resamplePreEval( DMatrix< DMatrix< Vector<T,3> > >& p, int m1, int m2, T du, T dv );
  };




} // END namepace GMlib

// Include DPBezierSurf class function implementations
#include "gmDPBezierSurf.c"


#endif // __gmDPBEZIERSURF_H__


