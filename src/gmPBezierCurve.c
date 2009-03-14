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



/*! \file gmPBezierCurve.c
 *
 *  Implementation of the gmPBezierCurve template class.
 *
 *  \date   2008-10-27
 */

#include <iomanip>
using std::setw;

// GMlib includes
#include "gmEvaluatorStatic.h"

namespace GMlib {



  template <typename T, int n>
  inline
  PBezierCurve<T, n>::PBezierCurve ( const DVector< Vector<T, n> >& c ) {

    _closed = false;
    _scale = T(1);
    _pre_eval = true;
    _resamp_mode = GM_RESAMPLE_PREEVAL;

    // Set Control Points
    setControlPoints( c );
  }


  template <typename T, int n>
  inline
  PBezierCurve<T, n>::PBezierCurve( const DVector< Vector<T, n> >& c, T s, T t, T e ) {

    _closed = false;
    _scale = T(1)/(e-s);
    _pre_eval = true;
    _resamp_mode = GM_RESAMPLE_PREEVAL;

//    this->setDomain( s, e );

    // Generate the control points
    DMatrix<T> bhp;
    EvaluatorStatic<T>::evaluateBhp( bhp, c.getDim()-1, (t-s)/(e-s), T(1)/(e-s) );
    bhp.invert();
    _c = bhp * c;

    for( int i = 0; i < c.getDim(); i++ )
      _c[i] -= c(0);
    this->translate( c(0) );
  }


  template <typename T, int n>
  inline
  PBezierCurve<T, n>::PBezierCurve ( const PBezierCurve<T, n>& copy ) : PCurve<T,n>( copy ) {

    _c = copy._c;
    _closed = copy._closed;
    _scale = copy._scale;
    _pre_eval = copy._pre_eval;
    _resamp_mode = copy._resamp_mode;
  }


  template <typename T, int n>
  inline
  DVector< Vector<T,n> >& PBezierCurve<T,n>::getControlPoints() {

    return _c;
  }


  template <typename T, int n>
  inline
  int PBezierCurve<T, n>::getDegree() const {

    return _c.getDim() - 1;
  }

  template <typename T, int n>
  inline
  void PBezierCurve<T, n>::eval( T t, int d, bool l ) {

    // Compute the Bernstein-Hermite Polynomials
    DMatrix< T > bhp;
    EvaluatorStatic<T>::evaluateBhp( bhp, getDegree(), t, _scale );

    this->_p = bhp * _c;
  }


  template <typename T, int n>
  T PBezierCurve<T, n>::getEndP() {

    return T(1);
  }


  template <typename T, int n>
  std::string PBezierCurve<T,n>::getIdentity() const {

    return "PBezierCurve";
  }


  template <typename T, int n>
  inline
  T PBezierCurve<T,n>::getLocalMapping( T t, T ts, T ti, T te ) {

    return (t - ts) / (te-ts);
  }


  template <typename T, int n>
  T PBezierCurve<T, n>::getStartP() {

    return T(0);
  }


  template <typename T, int n>
  inline
  bool PBezierCurve<T, n>::isClosed() const {

    return _closed;
  }


  template <typename T, int n>
  inline
  void PBezierCurve<T, n>::resample( DVector< DVector< Vector<T, n> > >& p, int m, int d, T start, T end ) {

    // dt; sample step value
    const T dt = (end-start) / T(m-1);

    // Set dim of result set
    p.setDim(m);

    switch( _resamp_mode ) {

      case GM_RESAMPLE_INLINE:
        resampleInline( p, m, dt );
        break;

      case GM_RESAMPLE_PREEVAL:
      default:
        resamplePreEval( p, m, dt );
        break;
    }
  }


  template <typename T, int n>
  inline
  void PBezierCurve<T, n>::resampleInline( DVector< DVector< Vector<T, n> > >& p, int m, T dt ) {

    // For each sample point on the uniform curve calculate the Bernstein-Hermite Polynomials
    for( int i = 0; i < m; i++ ) {

      eval( i * dt );
      p[i] = this->_p;
    }
  }


  template <typename T, int n>
  inline
  void PBezierCurve<T, n>::resamplePreEval( DVector< DVector< Vector<T, n> > >& p, int m, T dt ) {

    // Check whether or not to redo the preEvaluation
    if( _pre_eval || m != _t.getDim() ) {

      // Set the dimension of the Bernstein-Hermite Polynomial DVector
      _t.setDim(m);

      // For each sample point on the uniform curve calculate the Bernstein-Hermite Polynomials
      for( int i = 0; i < m; i++ )
        EvaluatorStatic<T>::evaluateBhp( _t[i], getDegree(), i*dt, _scale );

      // Disable the pre-evaluation step
      _pre_eval = false;
    }

    p.setDim( m );
    for( int i = 0; i < m; i++ )
      p[i] = _t[i] * _c;
  }


  template <typename T, int n>
  inline
  void PBezierCurve<T, n>::setClosed( bool state ) {

    _closed = state;
  }

  template <typename T, int n>
  inline
  void PBezierCurve<T, n>::setControlPoints( const DVector< Vector<T, n> >& cp ) {


    if( _c.getDim() == cp.getDim() ) {

      bool no_change = true;
      for( int i = 0; i < cp.getDim(); i++ )
        if( _c[i] != cp(i) )
          no_change = false;

      if( no_change )
        return;
    }
    else {

      _pre_eval = true;
    }

    _c = cp;
  }


  template <typename T, int n>
  inline
  void PBezierCurve<T, n>::setResampleMode( GM_RESAMPLE_MODE mode ) {

    _resamp_mode = mode;
  }


  template <typename T, int n>
  inline
  void PBezierCurve<T, n>::setScale( T d ) {

    if( d == _scale )
      return;

    _scale = d;
    _pre_eval = true;
  }

}

