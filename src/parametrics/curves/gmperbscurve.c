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



/*! \file gmperbscurve.c
 *
 *  Implementation of the PERBSCurve template class.
 */


#include "gmparc.h"
#include "gmpbeziercurve.h"


namespace GMlib {




  /*! PERBSCurve<T>::PERBSCurve()
   *
   *  Default constructor.
   *  Dummy.
   */
  template <typename T>
  inline
  PERBSCurve<T>::PERBSCurve() {

    this->_type_id = GM_SO_TYPE_CURVE_ERBS;

    init();
  }

  /*! PERBSCurve<T>::PERBSCurve( DVector< DVector< Vector<T,3> > >& c, const DVector<T>& t, bool closed )
   *
   *  Constructs an ERBS curve interpolating the data points of c, according to the knot vector t.
   *
   *  \param c Data set. Each data point consists of { position, 1st derivative, 2nd derivative, ... }.
   *  \param t Knot vector for the data-set c.
   *  \param closed Whether the data of c represents a closed curve.
   */
  template <typename T>
  inline
  PERBSCurve<T>::PERBSCurve( const DVector< DVector< Vector<T,3> > >& c, const DVector<T>& t, bool closed ) : _t(t) {

    this->_type_id = GM_SO_TYPE_CURVE_ERBS;

    init();

    _closed = closed;

    // Set data set dimenstion
    if( _closed ) _c.setDim( c.getDim() + 1 );
    else          _c.setDim( c.getDim() );

    // Pad knot vector
    padKnotVector();

    // Generate local patches (data set)
    for( int i = 0; i < c.getDim(); i++ ) {

      _c[i] = PBezierCurve<T>( c[i], _t[i], _t[i+1], t[i+2] );
      insertPatch( _c[i] );
    }

    if( _closed )
      _c[_c.getDim()-1] = _c[0];

  }

  /*! PERBSCurve<T>::PERBSCurve( DVector< DVector< Vector<T,3> > >& c, T start, T end, bool closed )
   *
   *  Constructs an ERBS curve interpolating the data points of c, according to the knot vector t.
   *
   *  \param c Data set. Each data point consists of { position, 1st derivative, 2nd derivative, ... }.
   *  \param start Start of the knot vector interval.
   *  \param end End of the knot vector interval.
   *  \param closed Whether the data of c represents a closed curve.
   */
  template <typename T>
  inline
  PERBSCurve<T>::PERBSCurve( const DVector< DVector< Vector<T,3> > >& c, T start, T end, bool closed ) {

    this->_type_id = GM_SO_TYPE_CURVE_ERBS;

    init();

    _closed = closed;

    if( _closed ) _c.setDim( c.getDim() + 1 );
    else          _c.setDim( c.getDim() );

    generateKnotVector( start, end );

    for( int i = 0; i < c.getDim(); i++ ) {

      _c[i] = new PBezierCurve<T>( c(i), _t[i], _t[i+1], _t[i+2] );
      insertPatch( _c[i] );
    }

    if( _closed )
      _c[_c.getDim()-1] = _c[0];
  }

  /*! PERBSCurve<T>::PERBSCurve( PCurve<T>* g, int no_locals )
   *
   *  Constructor which creates an ERBS Curve approximating the curve g.
   *  This constructor method uses PArc's as local patches.
   *
   *  \param g The curve to approximate.
   *  \param no_locals Number of local patches to create for the approximation.
   */
  template <typename T>
  inline
  PERBSCurve<T>::PERBSCurve( PCurve<T>* g, int no_locals ) {

    this->_type_id = GM_SO_TYPE_CURVE_ERBS;

    init();

    _closed = g->isClosed();

    if( _closed ) no_locals++;

    _c.setDim(no_locals);

    generateKnotVector( g );

    for( int i = 0; i < no_locals-1; i++ ) {
      _c[i] = new PArc<T>( g->evaluateParent( _t[i+1], 2 ), _t[i], _t[i+1], _t[i+2] );
      insertPatch( _c[i] );
    }

    // Handle Open/Closed
    int i = no_locals-1;
    if( _closed )
      _c[i] = _c[0];
    else {
      _c[i] = new PArc<T>( g->evaluateParent( _t[i+1], 2 ), _t[i], _t[i+1], _t[i+2] );
      insertPatch( _c[i] );
    }
  }

  /*! PERBSCurve<T>::PERBSCurve( PCurve<T>* g, int no_locals, int d )
   *
   *  Constructor which creates an ERBS Curve approximating the curve g.
   *  This constructor method uses PBezierCurves' as local patches.
   *
   *  \param g The curve to approximate.
   *  \param no_locals Number of local patches to create for the approximation.
   *  \param d The degree to use for the local patches, and when evaluating the input curve.
   */
  template <typename T>
  inline
  PERBSCurve<T>::PERBSCurve( PCurve<T>* g, int no_locals, int d ) {

    this->_type_id = GM_SO_TYPE_CURVE_ERBS;

    init();

    _closed = g->isClosed();

    if( _closed ) no_locals++;

    _c.setDim(no_locals);

    generateKnotVector( g );


    for( int i = 0; i < no_locals - 1; i++ ) {

      _c[i] = new PBezierCurve<T>( g->evaluateParent( _t[i+1], d ), _t[i], _t[i+1], _t[i+2] );
      insertPatch( _c[i] );
    }

    int i = no_locals-1;
    if( _closed )
      _c[i] = _c[0];
    else {
      _c[i] = new PBezierCurve<T>( g->evaluateParent( _t[i+1], d ), _t[i], _t[i+1], _t[i+2] );
      insertPatch( _c[i] );
    }
  }

  /*! PERBSCurve::PERBSCurve( const PERBSCurve<T>& copy ) : PCurve<T>( copy )
   *
   *  Copy Constructor
   *
   *  \param copy The curve to copy.
   */
  template <typename T>
  inline
  PERBSCurve<T>::PERBSCurve( const PERBSCurve<T>& copy ) : PCurve<T>( copy ) {

    init();
  }

  /*! PERBSCurve<T>::PERBSCurve( const PERBSCurve<T>& copy ) : PCurve<T>( copy )
   *
   *  Destructor
   */
  template <typename T>
  PERBSCurve<T>::~PERBSCurve() {

    for( int i = 0; i < _c.getDim(); i++ )
      SceneObject::remove( _c[i] );

    if( _evaluator )
      delete _evaluator;
  }


  template <typename T>
  inline
  void PERBSCurve<T>::edit( SceneObject *obj ) {

    int i;
    for( i = 0; i < _c.getDim(); i++ )
      if( _c[i] == obj )
        goto edit_loop_break;

    edit_loop_break:

    // If Bezier Patch
    PBezierCurve<T> *bezier = dynamic_cast<PBezierCurve<T>*>(_c[i]);
    if( bezier )
      bezier->updateCoeffs( _c[i]->getPos() - _c[i]->evaluate( 0.5, 0 )[0] );

    PCurve<T>::replot(0);
  }

  template <typename T>
  inline
  void PERBSCurve<T>::eval( T t, int d, bool l ) {

    // Send the control to the pre-eval evaluator
    if( _resamp_mode == GM_RESAMPLE_PREEVAL ) {

      evalPre( t, d, l );
      return;
    }

    int tk;
    for( tk = 1; tk < _t.getDim()-2; tk++ )
      if( t < _t[tk+1] )
        break;

    int c0i, c1i;
    c0i = tk - 1;
    c1i = tk;

    // Evaluating first Local Curve @ k
    DVector< Vector<T,3> > c0 = _c[c0i]->evaluateParent( _c[c0i]->getLocalMapping( t, _t[tk-1], _t[tk], _t[tk+1] ), d );

    // If t == _t[tk], meaning that the sample is at the knot, set the sample value to the sampled value of the first local curve.
    if( std::fabs(t - _t[tk]) < 1e-5 ) {
      this->_p = c0;
      return;
    }

    // Evaluating second Local Curve @ k
    DVector< Vector<T,3> > c1 = _c[c1i]->evaluateParent( _c[c1i]->getLocalMapping( t, _t[tk], _t[tk+1], _t[tk+2] ), d );
    DVector<T> B;
    getB( B, tk, t, d );

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
  void PERBSCurve<T>::evalPre( T t, int /*d*/, bool /*l*/ ) {

    // Find the u/v index for the preevaluated data.
    int it;
    it = 0;
    findIndex( t, it );

    // Find Knot Indice t_k
    int tk = _tk[it];

    int c0i, c1i;
    c0i = tk - 1;
    c1i = tk;

    // Evaluating first Local Curve @ k
    DVector< Vector<T,3> > c0 = _c[c0i]->evaluateParent( _c[c0i]->getLocalMapping( t, _t[tk-1], _t[tk], _t[tk+1] ), _B.getDim()-1 );

    // If t == _t[tk], meaning that the sample is at the knot, set the sample value to the sampled value of the first local curve.
    if( std::fabs(t - _t[tk]) < 1e-5 ) {
      this->_p = c0;
      return;
    }

    // Evaluating second Local Curve @ k
    DVector< Vector<T,3> > c1 = _c[c1i]->evaluateParent( _c[c1i]->getLocalMapping( t, _t[tk], _t[tk+1], _t[tk+2] ), _B.getDim()-1 );
    const DVector<T> &B = _B[it];

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
        c1[i] += ( a[j] * B(j) ) * c0[i-j];
    }
    this->_p = c1;
  }


  template <typename T>
  inline
  void PERBSCurve<T>::findIndex( T t, int& it ) {

    it = (this->_no_sam-1)*(t-this->getParStart())/(this->getParDelta())+0.1;
  }

  /*! void PERBSCurve<T>::generateKnotVector( PCurve<T>* g )
   *
   *  Generates a knot vector for the parametric interval of the curve g.
   *
   *  \param g The curve to be created a knot vector for.
   */
  template <typename T>
  inline
  void PERBSCurve<T>::generateKnotVector( PCurve<T>* g ) {

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

  /*! void PERBSCurve<T>::generateKnotVector( T start, T end )
   *
   *  Generates a knot vector for the interval start, end.
   *
   *  \param start The start of the knot vector curve interval
   *  \param end The end of the knot vector curve interval
   */
  template <typename T>
  inline
  void PERBSCurve<T>::generateKnotVector( T start, T end ) {

    const T st  = start;
    const T dt  = (end - start) / ( _c.getDim()-1 );
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
  void PERBSCurve<T>::getB( DVector<T>& B, int tk, T t, int d ) {

    B.setDim(d+1);
    _evaluator->set( _t[tk], _t[tk+1] - _t[tk] );
    B[0] = 1 - _evaluator->operator()(t);  // (*_evaluator)(t)
    B[1] = - _evaluator->getDer1();
    B[2] = - _evaluator->getDer2();
  }


  template <typename T>
  inline
  T PERBSCurve<T>::getEndP() {

    return _t[_t.getDim()-2];
  }


  template <typename T>
  inline
  std::string PERBSCurve<T>::getIdentity() const {

    return "PERBSCurve";
  }


  template <typename T>
  inline
  DVector< PCurve<T>* >& PERBSCurve<T>::getLocalPatches() {

    return _c;
  }


  template <typename T>
  inline
  int PERBSCurve<T>::getNoLocalPatches() const {

    return _c.getDim();
  }


  template <typename T>
  inline
  T PERBSCurve<T>::getStartP() {

    return _t[1];
  }


  template <typename T>
  inline
  void PERBSCurve<T>::hideLocalPatches() {

    for( int i = 0; i < _c.getDim(); i++ )
      _c[i]->setVisible( false, -1 );
  }


  template <typename T>
  void PERBSCurve<T>::init() {

    _evaluator = ERBSEvaluator<long double>::getInstance();
    _resamp_mode = GM_RESAMPLE_PREEVAL;
    _pre_eval = true;
  }


  template <typename T>
  inline
  void PERBSCurve<T>::insertPatch( PCurve<T>* patch ) {

    patch->replot( 10 );
    patch->setVisible( false );
    patch->setCollapsed( true );
    this->insert( patch );
  }


  template <typename T>
  inline
  bool PERBSCurve<T>::isClosed() const {

    return _closed;
  }


  template <typename T>
  inline
  bool PERBSCurve<T>::isLocalPatchesVisible() const {

    for( int i = 0; i < _c.getDim(); i++ )
      if( _c(i)->isVisible() )
        return true;

    return false;
  }

  /*! void PERBSCurve<T>::padKnotVector()
   *
   *  Prepends and appends an element to the internal knot vector.
   *  Value of the padded elements depends on the whether the data set is closed.
   */
  template <typename T>
  inline
  void PERBSCurve<T>::padKnotVector() {

    if( _closed ) {

      T d_start, d_end;
      d_start = _t[1] - _t[0];
      d_end = _t[_t.getDim()-1] - _t[_t.getDim()-2];
      _t.prepend( _t[0] - d_end );
      _t.append( _t[_t.getDim()-1] + d_start );
    }
    else {

      _t.prepend( _t[0] );
      _t.append( _t[_t.getDim()-1] );
    }
  }

  template <typename T>
  inline
  void PERBSCurve<T>::preSample( int m, int d, T start, T end ) {

    // break out of the preSample function if no preevalution is to be used
    switch( _resamp_mode ) {
    case GM_RESAMPLE_PREEVAL: break;
    case GM_RESAMPLE_INLINE:
    default:
      return;
    }


    // break out and return if preevaluation isn't necessary.
    if( !_pre_eval && m == _tk.getDim() )
    return;


    int tk;
    tk = 1;

    // dt; sample step value
    const T dt = ( end - start ) / T(m-1);

    // Set dimension for B and index value tables.
    _B.setDim(m);
    _tk.setDim( m );

    for( int i = 0; i < m; i++ ) {

      // Compute the "current" t value
      const T t = getStartP() + T(i) * dt;

      // Calculate index of i
      if( _t[tk+1] <= t )
        tk++;
      _tk[i] = tk;


      // Find the complementary B-Vector coherent with the current index.
      if( !(std::fabs(t - _t[tk]) < 1e-5) )
        getB( _B[i], tk, t, d );
    }

    _pre_eval = false;
  }


  template <typename T>
  inline
  void PERBSCurve<T>::setResampleMode( GM_RESAMPLE_MODE mode ) {

    _resamp_mode = mode;
  }


  template <typename T>
  inline
  void PERBSCurve<T>::showLocalPatches() {

    for( int i = 0; i < _c.getDim(); i++ )
      _c[i]->setVisible( true, -1 );
  }


} // END namespace GMlib


