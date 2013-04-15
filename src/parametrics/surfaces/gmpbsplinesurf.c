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



/*! \file gmpbsplinesurf.c
 *
 *  Implementation of the PBSplineSurf template class.
 */


#include "../evaluators/gmevaluatorstatic.h"

// gmlib
#include <core/containers/gmdmatrix.h>
#include <scene/selector/gmselector.h>

namespace GMlib {

  template <typename T>
  inline
  PBSplineSurf<T>::PBSplineSurf( const DMatrix< Vector<T,3> >& c, const DVector<T>& u,  const DVector<T>& v) {

    init();

    // Set Control Points and knot-vectors
    _c = c;
    _u = u;
    _v = v;

     // Set order
    _ku = _u.getDim()-_c.getDim1();
    _kv = _v.getDim()-_c.getDim2();

     // Set degree
    _du = _ku-1;
    _dv = _kv-1;
  }


  template <typename T>
  inline
  PBSplineSurf<T>::PBSplineSurf( const PBSplineSurf<T>& copy ) : PSurf<T,3>( copy ) {

    init();

    _c = copy._c;
    _u = copy._u;
    _v = copy._v;

    _ku = copy._ku;
    _kv = copy._kv;

    _du = copy._du;
    _dv = copy._dv;
  }


  template <typename T>
  inline
  PBSplineSurf<T>::~PBSplineSurf() {

    if(_sgv) delete _sgv;
  }


  template <typename T>
  void PBSplineSurf<T>::edit( int /*selector_id*/ ) {

    _c_moved = true;

    if( this->_parent )
      this->_parent->edit( this );

    _sgv->update();

    _c_moved = false;
  }


  template <typename T>
  inline
  void PBSplineSurf<T>::eval( T u, T v, int du, int dv, bool /*lu*/, bool /*lv*/ ) {

//    // Send the control to the pre-eval evaluator
//    if( _resamp_mode == GM_RESAMPLE_PREEVAL ) {
//
//      evalPre( u, v, d1, d2, lu, lv );
//      return;
//    }

    // Set Dimensions
    this->_p.setDim( _du+1, _dv+1 );

    // Compute the Bernstein-Hermite Polynomials
    DMatrix<T> bu, bv;
    int ii = EvaluatorStatic<T>::evaluateBSp( bu, u, _u, _du);
    int jj = EvaluatorStatic<T>::evaluateBSp( bv, v, _v, _dv);

    DMatrix<Vector<T,3> > c(_du+1,_dv+1);
    for(int i=0; i<_ku; i++)
        for(int j=0; j<_kv; j++)
            c[i][j] = _c[i+ii-_du][j+jj-_dv];

    bv.transpose();
    this->_p = bu * (c^bv);

    // Add "0" derivatives if d1/d2 is bigger
    this->_p.resetDim(du+1,dv+1);
  }


  template <typename T>
  inline
  void PBSplineSurf<T>::evalPre( T u, T v, int d1, int d2, bool /*lu*/, bool /*lv*/ ) {

    // Find the u/v index for the preevaluated data.
    int iu, iv;
    findIndex( u, v, iu, iv );

    // Set Dimensions
    this->_p.setDim( getDegreeU()+1, getDegreeV()+1 );

    DMatrix<T> bu = _ru[iu][iv];
    DMatrix<T> bv = _rv[iu][iv];

    bv.transpose();
    this->_p = bu * (_c^bv);

    // Add "0" derivatives if d1/d2 is bigger
    this->_p.resetDim(d1+1,d2+1);
  }


  template <typename T>
  inline
  void PBSplineSurf<T>::findIndex( T u, T v, int& iu, int& iv ) {

    iu = (this->_no_samp_u-1)*(u-this->getParStartU())/(this->getParDeltaU())+0.1;
    iv = (this->_no_samp_v-1)*(v-this->getParStartV())/(this->getParDeltaV())+0.1;
  }


  template <typename T>
  inline
  DMatrix< Vector<T,3> >& PBSplineSurf<T>::getControlPoints() {

    return _c;
  }

  template <typename T>
  inline
  int PBSplineSurf<T>::getDegreeU() const {

    return _du;
  }


  template <typename T>
  inline
  int PBSplineSurf<T>::getDegreeV() const {

    return _dv;
  }


  template <typename T>
  inline
  T PBSplineSurf<T>::getEndPU() {

    return _u[_c.getDim1()+1];
  }


  template <typename T>
  inline
  T PBSplineSurf<T>::getEndPV() {

    return _v[_c.getDim2()+1];
  }


  template <typename T>
  inline
  T PBSplineSurf<T>::getLocalMapping( T t, T ts, T /*tt*/, T te ) {

    return (t - ts) / (te-ts);
  }


  template <typename T>
  inline
  T PBSplineSurf<T>::getStartPU() {

    return _u[_du];
  }


  template <typename T>
  inline
  T PBSplineSurf<T>::getStartPV() {

    return _v[_dv];
  }


  template <typename T>
  void PBSplineSurf<T>::hideSelectors() {

    if( !_selectors )
      return;

    // Remove Selector Grid Visualizer
    this->removeVisualizer( _sgv );
    _sgv->reset();

    // Remove Selectors
    for( int i = 0; i < _s.getDim1(); i++ ) {
      for( int j = 0; j < _s.getDim2(); j++ ) {
        DisplayObject::remove( _s[i][j] );
        delete _s[i][j];
      }
    }

    _selectors = false;
  }


  template <typename T>
  inline
  void PBSplineSurf<T>::init() {

    this->_type_id = GM_SO_TYPE_SURFACE_BEZIER;

    _selectors = false;
    _c_moved = false;

    _cu = false;
    _cv = false;
    _su = T(1);
    _sv = T(1);
    _pre_eval = true;
    _resamp_mode = GM_RESAMPLE_PREEVAL;

    _sgv = new SelectorGridVisualizer<T>;
  }


  template <typename T>
  inline
  bool PBSplineSurf<T>::isClosedU() const {

    return _cu;
  }


  template <typename T>
  inline
  bool PBSplineSurf<T>::isClosedV() const {

    return _cv;
  }


  template <typename T>
  bool PBSplineSurf<T>::isSelectorsVisible() const {

    return _selectors;
  }

  template <typename T>
  inline
  void PBSplineSurf<T>::preSample( int m1, int m2, int /*d1*/, int /*d2*/,
                                   T s_u, T s_v, T e_u, T e_v ) {

    // break out of the preSample function if no preevalution is to be used
    switch( _resamp_mode ) {
    case GM_RESAMPLE_PREEVAL: break;
    case GM_RESAMPLE_INLINE:
    default:
      return;
    }

    // break out and return if preevaluation isn't necessary.
    if( !_pre_eval && m1 == _ru.getDim1() && m2 == _ru.getDim2() )
      return;

    // compute du and dv (step in parametric u and v direction)
    const T du = ( e_u - s_u ) / T(m1-1);
    const T dv = ( e_v - s_v ) / T(m2-1);

    // Set the dimension of the Bernstein-Hermite Polynomial DVector
    _ru.setDim(m1,m2);
    _rv.setDim(m1,m2);

    // Compute the Bernstein-Hermite Polynomiale, for the Bezier Surface
    for( int i = 0; i < m1; i++ ) {
      for( int j = 0; j < m2; j++ ) {
        EvaluatorStatic<T>::evaluateBhp( _ru[i][j], getDegreeU(), i*du, _su );
        EvaluatorStatic<T>::evaluateBhp( _rv[i][j], getDegreeV(), j*dv, _sv );
      }
    }

    // Disable the pre-evaluation step
    _pre_eval = false;

  }


  template <typename T>
  inline
  void PBSplineSurf<T>::setClosed( bool closed_u, bool closed_v ) {

    _cu = closed_u;
    _cv = closed_v;
  }


  template <typename T>
  inline
  void PBSplineSurf<T>::setControlPoints( const DMatrix< Vector<T,3> >& cp ) {


    if( _c.getDim1() == cp.getDim1() || _c.getDim2() == cp.getDim2() ) {

      bool no_change = true;
      for( int i = 0; i < cp.getDim1(); i++ )
        for( int j = 0; j < cp.getDim2(); j++ )
          if( _c[i][j] != cp(i)(j) )
            no_change = false;

      if( no_change )
        return;
    }
    else {

      _pre_eval = true;
    }

    _c = cp;
  }


  template <typename T>
  inline
  void PBSplineSurf<T>::setResampleMode( GM_RESAMPLE_MODE mode ) {

    _resamp_mode = mode;
  }


  template <typename T>
  inline
  void PBSplineSurf<T>::setScale( T du, T dv ) {

    if( du == _su || dv == _sv )
      return;

    _su = du;
    _sv = dv;
    _pre_eval = true;
  }


  template <typename T>
  void PBSplineSurf<T>::showSelectors( bool grid, const Color& _selector_color, const Color& grid_color ) {

    if( _selectors )
      return;

    _s.setDim( _c.getDim1(), _c.getDim2() );
    for( int i = 0, s_id = 0; i < _c.getDim1(); i++ ) {
      for( int j = 0; j < _c.getDim2(); j++ ) {

        Selector<T,3> *sel = new Selector<T,3>( _c[i][j], s_id++, this, T(1), _selector_color );
        DisplayObject::insert( sel );
        _s[i][j] = sel;
      }
    }

    if( grid ) {

      _sgv->setSelectors( _c );
      this->insertVisualizer( _sgv );
    }

    _selectors = true;
  }


  template <typename T>
  inline
  void PBSplineSurf<T>::updateCoeffs( const Vector<T,3>& d ) {

    if( _c_moved ) {

      HqMatrix<T,3> invmat = this->_matrix;
      invmat.invertOrthoNormal();

      Vector<T,3> diff = invmat*d;
      for( int i = 0; i < _c.getDim1(); i++ ) {
        for( int j = 0; j < _c.getDim2(); j++ ) {

          _c[i][j] += diff;
          _s[i][j]->translate( diff );
        }
      }
      DisplayObject::translate( -d );
      this->replot();
    }
  }

} // END namespace GMlib


