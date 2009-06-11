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



/*! \file gmDPERBSSurf.c
 *
 *  Implementation of the DPERBSSurf template class.
 *
 *  \date   2008-11-22
 */

#include "gmDPBezierSurf.h"

namespace GMlib {


//  template <typename T>
//  inline
//  DPERBSSurf<T>::DPERBSSurf( PSurf<T,3>* g, int no_locals_u, int no_locals_v, int d1, int d2 )
//    : DSurf<T>( new PERBSSurf<T,3>( g,3o_locals_u,3o_locals_v, d1, d2 ) ) {
//
//    init();
//  }


  template <typename T>
  inline
  DPERBSSurf<T>::DPERBSSurf() {

    this->_type_id = GM_SO_TYPE_SURFACE_ERBS;

    init();
  }

  template <typename T>
  inline
  DPERBSSurf<T>::DPERBSSurf( DSurf<T>* g, int no_locals_u, int no_locals_v, int d1, int d2 ) {

    this->_type_id = GM_SO_TYPE_SURFACE_ERBS;

    init();

    _closed_u = g->isClosedU();
    _closed_v = g->isClosedV();

    _c.setDim( no_locals_u, no_locals_v );
    generateKnotVector( g );

    // Create the inner surface patches
    int i, j;
    for( i = 0; i < no_locals_u-1; i++ ) {    // locals should be -1, and then later handle the edges.
      for( j = 0; j < no_locals_v-1; j++ ) {

        _c[i][j] = new DPBezierSurf<T>(
          g->evaluateParent( _u[i+1], _v[j+1], d1, d2 ),
          _u[i], _u[i+1], _u[i+2],
          _v[j], _v[j+1], _v[j+2]
        );
        insertPatch( _c[i][j] );
      }

      if( _closed_v )
        _c[i][j] = _c[i][0];
      else {
        _c[i][j] = new DPBezierSurf<T>(
          g->evaluateParent( _u[i+1], _v[j+1], d1, d2 ),
          _u[i], _u[i+1], _u[i+2],
          _v[j], _v[j+1], _v[j+2]
        );
        insertPatch( _c[i][j] );
      }
    }

    if( _closed_u )
      for( j = 0; j < no_locals_v; j++ )
        _c[i][j] = _c[0][j];
    else{
      for( j = 0; j < no_locals_v; j++ ) {
        _c[i][j] = new DPBezierSurf<T>(
          g->evaluateParent( _u[i+1], _v[j+1], d1, d2 ),
          _u[i], _u[i+1], _u[i+2],
          _v[j], _v[j+1], _v[j+2]
        );
        insertPatch( _c[i][j] );
      }
    }

    for( int i = 0; i < _c.getDim1(); i++ ) {
      for( int j = 0; j < _c.getDim2(); j++ ) {

        _c[i][j]->setLighted( true );
        _c[i][j]->setMaterial( GMmaterial::Ruby );
      }
    }
  }


  template <typename T>
  inline
  DPERBSSurf<T>::DPERBSSurf( const DMatrix< DPBezierSurf<T>* >& c, DVector<T> u, DVector<T> v, bool closed_u, bool closed_v ) : _u(u), _v(v) {

    this->_type_id = GM_SO_TYPE_SURFACE_ERBS;

    init();

    _c.setDim( c.getDim1(), c.getDim2() );
    for( int i = 0; i < c.getDim1(); i++ ) {
      for( int j = 0; j < c.getDim2(); j++ ) {
        _c[i][j] = c(i)(j);
        insertPatch( _c[i][j] );
      }
    }

    _closed_u = closed_u;
    _closed_v = closed_v;
  }


  template <typename T>
  inline
  DPERBSSurf<T>::DPERBSSurf( const DPERBSSurf<T>& copy ) : DSurf<T>( copy ) {

    init();
  }


//  template <typename T>
//  inline
//  DPERBSSurf<T>::DPERBSSurf( const PERBSSurf<T,3>& copy ) : DSurf<T>( copy ) {
//
//    init();
//  }
//
//
//  template <typename T>
//  inline
//  DPERBSSurf<T>::DPERBSSurf( PERBSSurf<T,3>* copy ) : DSurf<T>( copy ) {
//
//    _l_ref = copy;
//  }


  template <typename T>
  inline
  DPERBSSurf<T>::~DPERBSSurf() {

    if( _evaluator )
      delete _evaluator;
  }


  template <typename T>
  inline
  void DPERBSSurf<T>::edit( SceneObject* obj ) {

    int i, j;
    for( i = 0; i < _c.getDim1()-1; i++ )
      for( j = 0; j < _c.getDim2()-1; j++ )
        if( _c[i][j] == obj )
          goto edit_loop_break;

    edit_loop_break:

    DPBezierSurf<T> *bezier = dynamic_cast<DPBezierSurf<T>*>(_c[i][j]);
    if( bezier )
      bezier->updateCoeffs( _c[i][j]->getPos() - _c[i][j]->evaluate( 0.5, 0.5, 0, 0 )[0][0] );

    DSurf<T>::replot(0,0);
  }


  template <typename T>
  inline
  string DPERBSSurf<T>::getIdentity() const {

    return "DPERBSSurf";
  }


//  template <typename T>
//  inline
//  PERBSSurf<T,3>* DPERBSSurf<T>::getPERBSSurf() {
//
//    return _l_ref;
//  }

  template <typename T>
  inline
  void DPERBSSurf<T>::hideLocalPatches() {

    for( int i = 0; i < _c.getDim1(); i++ )
      for( int j = 0; j < _c.getDim2(); j++ )
        _c[i][j]->setVisible( false, -1 );

//    if( !_p_visible )
//      return;
//
//    for( int i = 0; i < _p.getDim1(); i++ ) {
//      for( int j = 0; j < _p.getDim2(); j++ ) {
//        SceneObject::remove( _p[i][j] );
//        delete _p[i][j];
//      }
//    }
//
//    _p_visible = false;
  }


  template <typename T>
  inline
  void DPERBSSurf<T>::init() {

//    _l_ref = dynamic_cast<PERBSSurf<T,3>*>(this->_p_ref);
//    _patches_visible = false;

    /////////////////////// PERBSSurf /////////////////////
    _evaluator = new EvaluatorERBS<T>();
    _resamp_mode = GM_RESAMPLE_PREEVAL;
    _pre_eval = true;
    /////////////////////// PERBSSurf /////////////////////
  }


  template <typename T>
  inline
  void DPERBSSurf<T>::insertPatch( DSurf<T>* patch ) {

    patch->replot( 10, 10 );
    patch->setVisible( false );
    patch->setCollapsed( true );
    insert( patch );
  }


  template <typename T>
  inline
  bool DPERBSSurf<T>::isLocalPatchesVisible() const {

    for( int i = 0; i < _c.getDim1(); i++ )
      for( int j = 0; j < _c.getDim2(); j++ )
        if( _c(i)(j)->isVisible() )
          return true;

    return false; //_patches_visible;
  }


  template <typename T>
  inline
  void DPERBSSurf<T>::localDisplay() {

    DSurf<T>::localDisplay();
  }


  template <typename T>
  inline
  void DPERBSSurf<T>::showLocalPatches() {

    for( int i = 0; i < _c.getDim1(); i++ )
      for( int j = 0; j < _c.getDim2(); j++ )
        _c[i][j]->setVisible( true, -1 );
//
//    if( _p_visible )
//      return;
//
//    DMatrix< PSurf<T,3>* > &p = getPERBSSurf()->getLocalPatches();
//
//    // Number of Surfs U
//    int no_surfs_u;
//    if( getPERBSSurf()->isClosedU() )
//      no_surfs_u = p.getDim1() - 1;
//    else
//      no_surfs_u = p.getDim1();
//
//    // Number of Surfs V
//    int no_surfs_v;
//    if( getPERBSSurf()->isClosedV() )
//      no_surfs_v = p.getDim2() - 1;
//    else
//      no_surfs_v = p.getDim2();
//
//
//
//    _p.setDim( no_surfs_u,3o_surfs_v );
//
//    for( int i = 0; i < no_surfs_u; i++ )
//      for( int j = 0; j < no_surfs_v; j++ )
//        visualizeLocalPatch( p[i][j], i, j,3o_surfs_u,3o_surfs_v, collapsed );
//
//    _p_visible = true;
  }


  template <typename T>
  inline
  void DPERBSSurf<T>::visualizeLocalPatch( PSurf<T,3>* /*p*/, int /*i*/, int /*j*/, int /*k*/, int /*l*/, bool /*collapsed*/ ) {

//
//    // Bezier Curve
//    PBezierSurf<T,3> *bsObj = dynamic_cast<PBezierSurf<T,3>* >( p );
//    if( bsObj ) {
//
//      _p[i][j] =  new DPBezierSurf<T>( bsObj );
//      visualizeLocalPatchInit( i, j,3, l, collapsed );
//      return;
//    }
  }


  template <typename T>
  inline
  void DPERBSSurf<T>::visualizeLocalPatchInit( int /*i*/, int /*j*/, int /*k*/, int /*l*/, bool /*collapsed*/ ) {

//    // if-then: Set collapsed
//    if( collapsed )
//      _p[i][j]->setCollapsed( true );
//
//    // Create Plot
//    _p[i][j]->replot( 10, 10 );
//
//    // Insert in scene
//    SceneObject::insert( _p[i][j] );
  }











  //////////////////////// PERBSSurf !!!!!!!!!!!!!! PERBSSurf ////////////////////////
  //////////////////////// PERBSSurf !!!!!!!!!!!!!! PERBSSurf ////////////////////////
  //////////////////////// PERBSSurf !!!!!!!!!!!!!! PERBSSurf ////////////////////////
  //////////////////////// PERBSSurf !!!!!!!!!!!!!! PERBSSurf ////////////////////////


  template <typename T>
  inline
  void DPERBSSurf<T>::eval( T u, T v, int /*d1*/, int /*d2*/, bool /*lu*/, bool /*lv*/ ) {

    // Find Knot Indices u_k and v_k
    int uk, vk;
    for( uk = 1; uk < _u.getDim()-2; uk++ ) if( u < _u[uk+1] ) break;
    for( vk = 1; vk < _v.getDim()-2; vk++ ) if( v < _v[vk+1] ) break;


    // Get result of inner loop for first patch in v
    DMatrix< Vector<T,3> > s0 = getC( u, v, uk, vk, 2, 2 );

    // If placed on a knot return only first patch result
    if( abs(v - _v[vk]) < 1e-5 ) {
      this->_p = s0;
      return;
    }
    // Blend Patches
    else {

      // Get result of inner loop for second patch in v
      DMatrix< Vector<T,3> > s1 = getC( u, v, uk, vk+1, 2, 2 );

      // Evaluate ERBS-basis in v direction
      DVector<T> B;
      getB( B, _v, vk, v, 2 );

      // Compute "Pascals triangle"-numbers and correct patch matrix
      DVector<T> a( B.getDim() );
      s0 -= s1;
      s0.transpose(); s1.transpose();
      for( int i = 0; i < B.getDim(); i++ ) {

        a[i] = 1;
        for( int j = i-1; j > 0; j-- )
          a[j] += a[j-1];                           // Compute "Pascals triangle"-numbers

        for( int j = 0; j <= i; j++ )
          s1[i] += (a[j]*B[j]) * s0[i-j];       // "column += scalar x column"
      }
      s1.transpose();

      this->_p = s1;
    }
  }


  template <typename T>
  inline
  void DPERBSSurf<T>::generateKnotVector( DVector<T>& kv, const T s, const T d, int kvd, bool closed ) {

    // Set Knot Vector dimension
    kv.setDim( kvd );

    // Compute all interior knot values
    for( int i = 0; i < kvd - 2; i++ )
      kv[i+1] = s + i * d;

    // Handle the edges wheather it is closed or not
    if( closed ) {
      kv[0] = kv[1] - ( kv[kvd-2] - kv[kvd-3]);
      kv[kvd-1] = kv[kvd-2] + ( kv[2] - kv[1] );
    }
    else {
      kv[0] = kv[1];
      kv[kvd-1] = kv[kvd-2];
    }
  }


  template <typename T>
  inline
  void DPERBSSurf<T>::getB( DVector<T>& B, const DVector<T>& kv, int tk, T t, int /*d*/ ) {

    B.setDim(3);

    _evaluator->set( kv(tk), kv(tk+1) - kv(tk) );
    B[0] = 1 - _evaluator->operator()(t);
    B[1] = - _evaluator->getDer1();
    B[2] = - _evaluator->getDer2();
  }


  template <typename T>
  inline
  DMatrix< Vector<T,3> > DPERBSSurf<T>::getC( T u, T v, int uk, int vk, T du, T dv ) {

    // Init Indexes and get local u/v values
    const int cu = uk-1;
    const int cv = vk-1;
    const T lu = _c[cu][cv]->getLocalMapping( u, _u[uk-1], _u[uk], _u[uk+1] );
    const T lv = _c[cu][cv]->getLocalMapping( v, _v[vk-1], _v[vk], _v[vk+1] );

    // Evaluate First local patch
    DMatrix< Vector<T,3> > c0 = _c[cu][cv]->evaluateParent( lu, lv, du, dv );

    // If on a interpolation point return only first patch evaluation
    if( abs(u - _u[uk]) < 1e-5 )
      return c0;


    // Select next local patch in u direction
    uk++;

    // Init Indexes and get local u/v values
    const int cu2 = uk-1;
    const int cv2 = vk-1;
    const T lu2 = _c[cu2][cv2]->getLocalMapping( u, _u[uk-1], _u[uk], _u[uk+1] );
    const T lv2 = _c[cu2][cv2]->getLocalMapping( v, _v[vk-1], _v[vk], _v[vk+1] );

    // Evaluate Second local patch
    DMatrix< Vector<T,3> > c1 = _c[cu2][cv2]->evaluateParent( lu2, lv2, du, dv );

    DVector<T> a(du+1);


      // Evaluate ERBS-basis in u direction
    DVector<T> B;
    getB( B, _u, uk-1, u, du );


      // Compute "Pascals triangle"-numbers and correct patch matrix
    c0 -= c1;
    for( int i = 0; i < B.getDim(); i++ ) {

      a[i] = 1;
      for( int j = i-1; j > 0; j-- )
        a[j] += a[j-1];

      for( int j = 0; j <= i; j++ )
        c1[i] += (a[j] * B[j]) * c0[i-j];
    }
    return c1 ;
  }


  template <typename T>
  inline
  DMatrix< Vector<T,3> > DPERBSSurf<T>::getCPre( T u, T v, int uk, int vk, T du, T dv, int i, int j ) {

    // Init Indexes and get local u/v values
    const int cu = uk-1;
    const int cv = vk-1;
    const T lu = _c[cu][cv]->getLocalMapping( u, _u[uk-1], _u[uk], _u[uk+1] );
    const T lv = _c[cu][cv]->getLocalMapping( v, _v[vk-1], _v[vk], _v[vk+1] );

    // Evaluate First local patch
    DMatrix< Vector<T,3> > c0 = _c[cu][cv]->evaluateParent( lu, lv, du, dv );

    // If on a interpolation point return only first patch evaluation
    if( abs(u - _u[uk]) < 1e-5 )
      return c0;

    // Select next local patch in u direction
    uk++;

    // Init Indexes and get local u/v values
    const int cu2 = uk-1;
    const int cv2 = vk-1;
    const T lu2 = _c[cu2][cv2]->getLocalMapping( u, _u[uk-1], _u[uk], _u[uk+1] );
    const T lv2 = _c[cu2][cv2]->getLocalMapping( v, _v[vk-1], _v[vk], _v[vk+1] );

    // Evaluate Second local patch
    DMatrix< Vector<T,3> > c1 = _c[cu2][cv2]->evaluateParent( lu2, lv2, du, dv );

    DVector<T> a(du+1);

      // Evaluate ERBS-basis in u direction
    const DVector<T> B = _Bu[i][j];

      // Compute "Pascals triangle"-numbers and correct patch matrix
    c0 -= c1;
    for( int i = 0; i < B.getDim(); i++ ) {

      a[i] = 1;
      for( int j = i-1; j > 0; j-- )
        a[j] += a[j-1];

      for( int j = 0; j <= i; j++ )
        c1[i] += (a[j] * B(j)) * c0[i-j];
    }

    return c1 ;
  }


  template <typename T>
  inline
  DVector<T>& DPERBSSurf<T>::getKnotsU() {

    return _u;
  }


  template <typename T>
  inline
  DVector<T>& DPERBSSurf<T>::getKnotsV() {

    return _v;
  }


  template <typename T>
  inline
  DMatrix< DSurf<T>* >& DPERBSSurf<T>::getLocalPatches() {
    return _c;
  }


  template <typename T>
  inline
  int DPERBSSurf<T>::getNoLocalPatchesU() const {

    return _c.getDim1();
  }


  template <typename T>
  inline
  int DPERBSSurf<T>::getNoLocalPatchesV() const {

    return _c.getDim2();
  }


  template <typename T>
  inline
  void DPERBSSurf<T>::generateKnotVector( DSurf<T>* g ) {

    // Knot Vector in U direction
    generateKnotVector(
      _u,
      g->getParStartU(),
      g->getParDeltaU() / ( _c.getDim1()-1 ),
      _c.getDim1() + 2,
      isClosedU()
    );

    // Knot Vector in V direction
    generateKnotVector(
      _v,
      g->getParStartV(),
      g->getParDeltaV() / ( _c.getDim2()-1 ),
      _c.getDim2() + 2,
      isClosedV()
    );
  }


  template <typename T>
  inline
  T DPERBSSurf<T>::getEndPU() {

    return _u[_u.getDim()-2];
  }


  template <typename T>
  inline
  T DPERBSSurf<T>::getEndPV() {

    return _v[_v.getDim()-2];
  }


  template <typename T>
  inline
  T DPERBSSurf<T>::getStartPU() {

    return _u[1];
  }


  template <typename T>
  inline
  T DPERBSSurf<T>::getStartPV() {

    return _v[1];
  }


  template <typename T>
  inline
  bool DPERBSSurf<T>::isClosedU() const {

    return _closed_u;
  }


  template <typename T>
  inline
  bool DPERBSSurf<T>::isClosedV() const {

    return _closed_v;
  }


  template <typename T>
  inline
  void DPERBSSurf<T>::resample(
    DMatrix< DMatrix < Vector<T,3> > >& p,
    int m1,
    int m2,
    int /*d1*/,
    int /*d2*/,
    T s_u,
    T s_v,
    T e_u,
    T e_v
  ) {

    const T du = ( e_u - s_u ) / T(m1-1);
    const T dv = ( e_v - s_v ) / T(m2-1);

    // Set dim of result set
    p.setDim(m1,m2);

    switch( _resamp_mode ) {

      case GM_RESAMPLE_INLINE:
        resampleInline( p, m1, m2, du, dv );
        break;

      case GM_RESAMPLE_PREEVAL:
      default:
        resamplePreEval( p, m1, m2, du, dv );
        break;
    }
  }


  template <typename T>
  inline
  void DPERBSSurf<T>::resampleInline( DMatrix<DMatrix <Vector<T,3> > >& p, int m1, int m2, T du, T dv ) {

    for( int i = 0; i < m1; i++ ) {

      const T u = _u[1] + T(i) * du;
      for( int j = 0; j < m2; j++ ) {

        const T v = _v[1] + T(j) * dv;

        eval( u, v );
        p[i][j] = this->_p;
      }
    }
  }


  template <typename T>
  inline
  void DPERBSSurf<T>::resamplePreEval( DMatrix<DMatrix <Vector<T,3> > >& p, int m1, int m2, T du, T dv ) {



    if( _pre_eval || m1 != _uk.getDim1() || m2 != _uk.getDim2() )
    {

      int uk, vk;
      uk = vk = 1;

      _Bu.setDim( m1, m2 );
      _Bv.setDim( m1, m2 );
      _uk.setDim( m1, m2 );
      _vk.setDim( m1, m2 );

      // Outer loop: u dir
      for( int i = 0; i < m1; i++ ) {

        // Find u
        const T u = getStartPU() + T(i) * du;

        // Inner loop: v dir
        for( int j = 0; j < m2; j++ ) {

          // Find v
          const T v = getStartPV() + T(j) * dv;

          // Find indices for uk and vk
          for( uk = 1; uk < _u.getDim()-2; uk++ ) if( u < _u[uk+1] ) break;
          for( vk = 1; vk < _v.getDim()-2; vk++ ) if( v < _v[vk+1] ) break;

          // Save indices
          _uk[i][j] = uk;
          _vk[i][j] = vk;

          // Evaluate ERBS basis in u direction
          if( !(abs(u - _u[uk]) < 1e-5) )
            getB( _Bu[i][j], _u, uk, u, 2 );

          // Evaluate ERBS basis in v direction
          if( !(abs(v - _v[vk]) < 1e-5) )
            getB( _Bv[i][j], _v, vk, v, 2 );

        }
      }

      _pre_eval = false;
    }


    // Inline Computations
    for( int i = 0; i < m1; i++ ) {

      // Compute u
      const T u = getStartPU() + T(i) * du;

      for( int j = 0; j < m2; j++ ) {

        // Compute v
        const T v = getStartPV() + T(j) * dv;

        // Get Indices
        const int vk = _vk[i][j];
        const int uk = _uk[i][j];


        // Get result of inner loop for first patch in v
        DMatrix< Vector<T,3> > s0 = getCPre( u, v, uk, vk, 2, 2, i, j );

        // If placed on a knot return only first patch result
        if( abs(v-_v[vk]) < 1e-5 ) {
          p[i][j] = s0;
        }
        // Blend Patches
        else {

          // Get result of inner loop for second patch in v
          DMatrix< Vector<T,3> > s1 = getCPre( u, v, uk, vk+1, 2, 2, i, j );

          // Evaluate ERBS-basis in v direction
          const DVector<T> B = _Bv[i][j];

          // Compute "Pascals triangle"-numbers and correct patch matrix
          DVector<T> a( B.getDim() );
          s0 -= s1;
          s0.transpose(); s1.transpose();
          for( int k = 0; k < B.getDim(); k++ ) {

            a[k] = 1;
            for( int l = k-1; l > 0; l-- )
              a[l] += a[l-1];                           // Compute "Pascals triangle"-numbers

            for( int l = 0; l <= k; l++ )
              s1[k] += (a[l]*B(l)) * s0[k-l];       // "column += scalar x column"
          }
          s1.transpose();

          p[i][j] = s1;
        }
      }
    }
  }


  template <typename T>
  inline
  void DPERBSSurf<T>::setResampleMode( GM_RESAMPLE_MODE mode ) {

    _resamp_mode = mode;
  }
}


