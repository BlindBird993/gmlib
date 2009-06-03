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



/*! \file gmDPERBSCurve.c
 *
 *  Implementation of the DPERBSCurve template class.
 *
 *  \date   2008-10-30
 */

#include "gmDPBezierCurve.h"
#include "gmDPArc.h"

namespace GMlib {



  template <typename T>
  inline
  DPERBSCurve<T>::DPERBSCurve() {

    init();
  }


  template <typename T>
  inline
  DPERBSCurve<T>::DPERBSCurve( DCurve<T>* g, int no_locals ) {

    init();

    _closed = g->isClosed();

    _c.setDim(no_locals);

    generateKnotVector( g );

    for( int i = 0; i < no_locals-1; i++ ) {
      _c[i] = new DPArc<T>( g->evaluateParent( _t[i+1], 2 ), _t[i], _t[i+1], _t[i+2] );
      insertPatch( _c[i] );
    }


    // Handle Open/Closed
    int i = no_locals-1;
    if( _closed )
      _c[i] = _c[0];
    else {
      _c[i] = new DPArc<T>( g->evaluateParent( _t[i+1], 2 ), _t[i], _t[i+1], _t[i+2] );
      insertPatch( _c[i] );
    }
  }


  template <typename T>
  inline
  DPERBSCurve<T>::DPERBSCurve( DCurve<T>* g, int no_locals, int d ) {

    init();

    _closed = g->isClosed();

    _c.setDim(no_locals);


//    cout << "ERBSCurve:  It is " << ( _closed ? "closed" : "not closed" ) << endl;
    generateKnotVector( g );


//    _tmp.setDim( no_locals );
    for( int i = 0; i < no_locals - 1; i++ ) {

      _c[i] = new DPBezierCurve<T>( g->evaluateParent( _t[i+1], d ), _t[i], _t[i+1], _t[i+2] );
      insertPatch( _c[i] );
    }

    int i = no_locals-1;
    if( _closed )
      _c[i] = _c[0];
    else {
      _c[i] = new DPBezierCurve<T>( g->evaluateParent( _t[i+1], d ), _t[i], _t[i+1], _t[i+2] );
      insertPatch( _c[i] );
    }
  }


  template <typename T>
  inline
  DPERBSCurve<T>::DPERBSCurve( const DPERBSCurve<T>& copy ) : DCurve<T>( copy ) {

    init();
  }


//  template <typename T>
//  inline
//  DPERBSCurve<T>::DPERBSCurve( const PERBSCurve<T,3>& copy ) : DCurve<T>( copy ) {
//
//    init();
//  }
//
//
//  template <typename T>
//  inline
//  DPERBSCurve<T>::DPERBSCurve( PERBSCurve<T,3>* copy ) : DCurve<T>() {
//
//    _l_ref = copy;
//  }


  template <typename T>
  DPERBSCurve<T>::~DPERBSCurve() {}


  template <typename T>
  inline
  void DPERBSCurve<T>::edit( SceneObject *obj ) {

    int i;
    for( i = 0; i < _c.getDim(); i++ )
      if( _c[i] == obj )
        goto edit_loop_break;

    edit_loop_break:

    // If Bezier Patch
    DPBezierCurve<T> *bezier = dynamic_cast<DPBezierCurve<T>*>(_c[i]);
    if( bezier )
      bezier->updateCoeffs( _c[i]->getPos() - _c[i]->evaluate( 0.5, 0 )[0] );

    DCurve<T>::replot(0);
  }


  template <typename T>
  inline
  string DPERBSCurve<T>::getIdentity() const {

    return "DPERBSCurve";
  }


//  template <typename T>
//  inline
//  PERBSCurve<T,3>* DPERBSCurve<T>::getPERBSCurve() {
//
//    return _l_ref;
//  }


  template <typename T>
  inline
  void DPERBSCurve<T>::hideLocalPatches() {

    for( int i = 0; i < _c.getDim(); i++ )
      _c[i]->setVisible( false, -1 );
//
//    if( !_p_visible )
//      return;
//
//    for( int i = 0; i < _p.getDim(); i++ )
//      SceneObject::remove( _p[i] );
//
//    _p.clear();
//
//    _p_visible = false;
  }


  template <typename T>
  void DPERBSCurve<T>::init() {

//    _l_ref = dynamic_cast<PERBSCurve<T,3>*>( this->_p_ref );
//    _patches_visible = false;

    /////////////////////////
    _evaluator = new EvaluatorERBS<T>();
    _resamp_mode = GM_RESAMPLE_PREEVAL;
    _pre_eval = true;
    /////////////////////////
  }


  template <typename T>
  inline
  void DPERBSCurve<T>::insertPatch( DCurve<T>* patch ) {

    patch->replot( 10 );
    patch->setVisible( false );
    patch->setCollapsed( true );
    insert( patch );
  }


  template <typename T>
  inline
  bool DPERBSCurve<T>::isLocalPatchesVisible() const {

    for( int i = 0; i < _c.getDim(); i++ )
      if( _c(i)->isVisible() )
        return true;

    return false;//_p_visible;
  }


  template <typename T>
  inline
  void DPERBSCurve<T>::localDisplay() {

    DCurve<T>::localDisplay();
  }


  template <typename T>
  inline
  void DPERBSCurve<T>::showLocalPatches() {

    for( int i = 0; i < _c.getDim(); i++ )
      _c[i]->setVisible( true, -1 );
//
//    if( _p_visible )
//      return;
//
//    DVector< PCurve<T,3>* > &p = getPERBSCurve()->getLocalPatches();
//
//    int no_curves;
//    if( getPERBSCurve()->isClosed() )
//      no_curves = p.getDim() - 1;
//    else
//      no_curves = p.getDim();
//
//    _p.setDim( no_curves );
//
//    for( int i = 0; i < no_curves; i++ ) {
//
//      visualizeLocalPatch(p[i], i, no_curves, collapsed );
//    }
//
//    _p_visible = true;
  }


  template <typename T>
  inline
  void DPERBSCurve<T>::visualizeLocalPatch( PCurve<T,3>* p, int i, int m, bool collapsed ) {
//
//    // Arc
//    PArc<T,3> *arcObj = dynamic_cast<PArc<T,3>*>( p );
//    if( arcObj ) {
//
//      _p[i] = new DPArc<T>( arcObj );
//      visualizeLocalPatchInit( i, m, collapsed );
//      return;
//    }
//
//    // Bezier Curve
//    PBezierCurve<T,3> *bcObj = dynamic_cast<PBezierCurve<T, 3>* >( p );
//    if( bcObj ) {
//
//      _p[i] = new DPBezierCurve<T>( bcObj );
//      visualizeLocalPatchInit( i, m, collapsed );
//      return;
//    }
  }


  template <typename T>
  inline
  void DPERBSCurve<T>::visualizeLocalPatchInit( int i, int m, bool collapsed ) {
//
//    // if-then: Set collapsed
//    if( collapsed )
//      _p[i]->setCollapsed( true );
//
//    // Create Plot
//    _p[i]->replot( 10 );
//
//    // Insert in scene
//    SceneObject::insert( _p[i] );
  }








  //////////////////////// DPERBSCurve !!!!!!!!!!!!!! DPERBSCurve ////////////////////////
  //////////////////////// DPERBSCurve !!!!!!!!!!!!!! DPERBSCurve ////////////////////////
  //////////////////////// DPERBSCurve !!!!!!!!!!!!!! DPERBSCurve ////////////////////////
  //////////////////////// DPERBSCurve !!!!!!!!!!!!!! DPERBSCurve ////////////////////////








  template <typename T>
  inline
  void DPERBSCurve<T>::eval( T t, int d, bool l) {

    int tk;
    for( tk = 1; tk < _t.getDim()-2; tk++ )
      if( t < _t[tk+1] )
        break;

    int c0i, c1i;
    c0i = tk - 1;
    c1i = tk;

    // Evaluating first Local Curve @ k
    DVector< Vector<T,3> > c0 = _c[c0i]->evaluateParent( _c[c0i]->getLocalMapping( t, _t[tk-1], _t[tk], _t[tk+1] ), 2 );


    // If t == _t[tk], meaning that the sample is at the knot, set the sample value to the sampled value of the first local curve.
    if( abs(t - _t[tk]) < 1e-5 ) {
      this->_p = c0;
      return;
    }

    // Evaluating second Local Curve @ k
    DVector< Vector<T,3> > c1 = _c[c1i]->evaluateParent( _c[c1i]->getLocalMapping( t, _t[tk], _t[tk+1], _t[tk+2] ), 2 );

    DVector<T> B;
    getB( B, tk, t, 2 );

    // Calculate pascals triangle numbers and then compute the sample position data
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


  template <typename T>
  inline
  void DPERBSCurve<T>::generateKnotVector( DCurve<T>* g ) {

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


  template <typename T>
  inline
  void DPERBSCurve<T>::getB( DVector<T>& B, int tk, T t, int d ) {

    B.setDim(3);
    _evaluator->set( _t[tk], _t[tk+1] - _t[tk] );
    B[0] = 1 - _evaluator->operator()(t);  // (*_evaluator)(t)
    B[1] = - _evaluator->getDer1();
    B[2] = - _evaluator->getDer2();
  }


  template <typename T>
  inline
  T DPERBSCurve<T>::getEndP() {

    return _t[_t.getDim()-2];
  }


  template <typename T>
  inline
  DVector< DCurve<T>* >& DPERBSCurve<T>::getLocalPatches() {

    return _c;
  }


  template <typename T>
  inline
  T DPERBSCurve<T>::getStartP() {

    return _t[1];
  }


  template <typename T>
  inline
  bool DPERBSCurve<T>::isClosed() const {

    return _closed;
  }


  template <typename T>
  inline
  void DPERBSCurve<T>::resample( DVector< DVector< Vector<T,3> > >& p, int m, int d, T start, T end ) {

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




  template <typename T>
  inline
  void DPERBSCurve<T>::resampleInline( DVector< DVector< Vector<T,3> > >& p, int m, T dt ) {

    for( int i = 0; i < m; i++ ) {

      T t = _t[1] + T(i) * dt;

      eval( t );
      p[i] = this->_p;
    }
  }


  template <typename T>
  inline
  void DPERBSCurve<T>::resamplePreEval( DVector< DVector< Vector<T,3> > >& p, int m, T dt ) {

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
    DVector< Vector<T,3> > c0, c1;
    for( int i = 0; i < m; i++ ) {

      // T-value of ERBS
      t = getStartP() + T(i) * dt;

      // Indices
      const int tk = _tk[i];
      const int c0i = tk-1;
      const int c1i = tk;

      // Evaluate First Local Curve
      c0 = _c[c0i]->evaluateParent( _c[c0i]->getLocalMapping( t, _t[tk-1], _t[tk], _t[tk+1] ), 2 );

      // Use c0 only if it is at the interpolation point
      if( abs(t - _t[tk]) < 1e-5 )
        p[i] = c0;
      else {

        // Evaluate Second Local Curve
        c1 = _c[c1i]->evaluateParent( _c[c1i]->getLocalMapping( t, _t[tk], _t[tk+1], _t[tk+2] ), 2 );


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


  template <typename T>
  inline
  void DPERBSCurve<T>::setResampleMode( GM_RESAMPLE_MODE mode ) {

    _resamp_mode = mode;
  }

}


