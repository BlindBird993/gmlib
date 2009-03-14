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



/*! \file gmPERBSCurve.c
 *
 *  Implementation of the PERBSCurve template class.
 *
 *  \date   2008-10-28
 */


#include <iomanip>
using std::setw;

#include "gmPArc.h"
#include "gmPBezierCurve.h"



namespace GMlib {

  template <typename T, int n>
  PERBSCurve<T,n>::PERBSCurve() {

    init();
  }


  template <typename T, int n >
  PERBSCurve<T,n>::PERBSCurve( PCurve<T,n>* g, int no_locals ) {

    init();

    _closed = g->isClosed();

    _c.setDim(no_locals);


    cout << "ERBSCurve:  It is " << ( _closed ? "closed" : "not closed" ) << endl;
    generateKnotVector( g );


    for( int i = 0; i < no_locals-1; i++ )
      _c[i] = new PArc<T,n>( g->evaluate( _t[i+1], 2 ), _t[i], _t[i+1], _t[i+2] );


    // Handle Open/Closed
    int i = no_locals-1;
    if( _closed )
      _c[i] = _c[0];
    else
      _c[i] = new PArc<T,n>( g->evaluate( _t[i+1], 2 ), _t[i], _t[i+1], _t[i+2] );
  }


  template <typename T, int n >
  PERBSCurve<T,n>::PERBSCurve( PCurve<T,n>* g, int no_locals, int d ) {

    init();

    _closed = g->isClosed();

    _c.setDim(no_locals);


//    cout << "ERBSCurve:  It is " << ( _closed ? "closed" : "not closed" ) << endl;
    generateKnotVector( g );


//    _tmp.setDim( no_locals );
    for( int i = 0; i < no_locals - 1; i++ )
      _c[i] = new PBezierCurve<T,n>( g->evaluate( _t[i+1], d ), _t[i], _t[i+1], _t[i+2] );

    int i = no_locals-1;
    if( _closed )
      _c[i] = _c[0];
    else
      _c[i] = new PBezierCurve<T,n>( g->evaluate( _t[i+1], d ), _t[i], _t[i+1], _t[i+2] );
  }


  template <typename T, int n>
  PERBSCurve<T,n>::~PERBSCurve() {

    if( _evaluator )
      delete _evaluator;
  }


  template <typename T, int n>
  inline
  void PERBSCurve<T,n>::eval( T t, int d, bool l) {

    int tk;
    for( tk = 1; tk < _t.getDim()-2; tk++ )
      if( t < _t[tk+1] )
        break;

    int c0i, c1i;
    c0i = tk - 1;
    c1i = tk;

    // Evaluating first Local Curve @ k
    DVector< Vector<T,n> > c0 = _c[c0i]->evaluate( _c[c0i]->getLocalMapping( t, _t[tk-1], _t[tk], _t[tk+1] ), 2 );


    // If t == _t[tk], meaning that the sample is at the knot, set the sample value to the sampled value of the first local curve.
    if( abs(t - _t[tk]) < 1e-5 ) {
      this->_p = c0;
      return;
    }

    // Evaluating second Local Curve @ k
    DVector< Vector<T,n> > c1 = _c[c1i]->evaluate( _c[c1i]->getLocalMapping( t, _t[tk], _t[tk+1], _t[tk+2] ), 2 );

    DVector<T> B;
    getB( B, tk, t, 2 );

    // Calculate pascals triangle numbers and the compute the sample position data
    c0 -= c1;

    DVector<T> a(B.getDim());
    for( int i = 0; i < B.getDim(); i++ ) {

      // Compute the pascal triangle numbers
      a[i] = 1;
      for( int j = i-1; j > 0; j-- )
        a[j] += a[j-1];

      // Compute the sample position data
      for( int j = 0; j <= i; j++ )
        c1[i] += ( a[j] * B[j] ) * c0[i-j];

    }
    this->_p = c1;
  }


  template <typename T, int n>
  inline
  void PERBSCurve<T,n>::generateKnotVector( PCurve<T,n>* g ) {

    const T st  = g->getParStart();
    const T dt  = g->getParDelta() / ( _c.getDim()-1 );
    const T kvd = _c.getDim() + 2;

    _t.setDim(kvd);

    for( int i = 0; i < kvd - 2; i++ )
      _t[i+1] = st + i * dt;

    if( isClosed() ) {
      _t[0] = _t[1] - ( _t[kvd-2] - _t[kvd-3]);
      _t[kvd-1] = _t[kvd-2] + ( _t[2] - _t[1] );
    }
    else {
      _t[0] = _t[1];
      _t[kvd-1] = _t[kvd-2];
    }
  }


  template <typename T, int n>
  inline
  void PERBSCurve<T,n>::getB( DVector<T>& B, int tk, T t, int d ) {

    B.setDim(3);
    _evaluator->set( _t[tk], _t[tk+1] - _t[tk] );
    B[0] = 1 - _evaluator->operator()(t);  // (*_evaluator)(t)
    B[1] = - _evaluator->getDer1();
    B[2] = - _evaluator->getDer2();
  }


  template <typename T, int n>
  inline
  T PERBSCurve<T,n>::getEndP() {

    return _t[_t.getDim()-2];
  }


  template <typename T, int n>
  std::string PERBSCurve<T,n>::getIdentity() const {

    return "PERBSCurve";
  }


  template <typename T, int n>
  inline
  DVector< PCurve<T,n>* >& PERBSCurve<T,n>::getLocalPatches() {

    return _c;
  }


  template <typename T, int n>
  inline
  T PERBSCurve<T,n>::getStartP() {

    return _t[1];
  }


  template <typename T, int n>
  inline
  void PERBSCurve<T,n>::init() {

    _evaluator = new EvaluatorERBS<T>();
    _resamp_mode = GM_RESAMPLE_PREEVAL;
    _pre_eval = true;
  }


  template <typename T, int n>
  inline
  bool PERBSCurve<T,n>::isClosed() const {

    return _closed;
  }


  template <typename T, int n>
  inline
  void PERBSCurve<T,n>::resample( DVector< DVector< Vector<T, n> > >& p, int m, int d, T start, T end ) {

    // dt; sample step value
    const T dt = ( getEndP() - getStartP() ) / T(m-1);

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
  void PERBSCurve<T, n>::resampleInline( DVector< DVector< Vector<T, n> > >& p, int m, T dt ) {

    for( int i = 0; i < m; i++ ) {

      T t = _t[1] + T(i) * dt;

      eval( t );
      p[i] = this->_p;
    }
  }


  template <typename T, int n>
  inline
  void PERBSCurve<T, n>::resamplePreEval( DVector< DVector< Vector<T, n> > >& p, int m, T dt ) {

    T t;

    if( _pre_eval || m != _tk.getDim() ) {

      int tk;

      // Init the indice table
      _B.setDim(m);
      _tk.setDim( m );

      tk = 1;
      for( int i = 0; i < m; i++ ) {

        // Compute the "current" t value
        t = getStartP() + T(i) * dt;

        // Calculate index of i
        if( _t[tk+1] <= t )
          tk++;
        _tk[i] = tk;


        // Find the complementary B-Vector coherent with the current index.
        if( !(abs(t - _t[tk]) < 1e-5) )
          getB( _B[i], tk, t, 2 );
      }
      _pre_eval = false;
    }

    // Inline Computations
    DVector< Vector<T, n> > c0, c1;
    for( int i = 0; i < m; i++ ) {

      // T-value of ERBS
      t = getStartP() + T(i) * dt;

      // Indices
      const int tk = _tk[i];
      const int c0i = tk-1;
      const int c1i = tk;

      // Evaluate First Local Curve
      c0 = _c[c0i]->evaluate( _c[c0i]->getLocalMapping( t, _t[tk-1], _t[tk], _t[tk+1] ), 2 );


      // Use c0 only if it is at the interpolation point
      if( abs(t - _t[tk]) < 1e-5 )
        p[i] = c0;
      else {

        // Evaluate Second Local Curve
        c1 = _c[c1i]->evaluate( _c[c1i]->getLocalMapping( t, _t[tk], _t[tk+1], _t[tk+2] ), 2 );


        // Correct c0 with c1
        c0 -= c1;

        // Fetch the preevaluated ERBS Vector
        DVector<T> B = _B[i];

        // Add pascal triangle numbers to the equation and compute the final points with coherant derivatives
        DVector<T> a(B.getDim());
        for( int j = 0; j < B.getDim(); j++ ) {

          // Compute the pascal triangle numbers
          a[j] = 1;
          for( int k = j-1; k > 0; k-- )
            a[k] += a[k-1];

          // Compute the sample position data
          for( int k = 0; k <= j; k++ )
            c1[j] += ( a[k] * B[k] ) * c0[j-k];
        }

        p[i] = c1;
      }
    }
  }


  template <typename T, int n>
  inline
  void PERBSCurve<T, n>::setResampleMode( GM_RESAMPLE_MODE mode ) {

    _resamp_mode = mode;
  }
}
