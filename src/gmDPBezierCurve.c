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



/*! \file gmDPBezierCurve.c
 *
 *  Implementation of the DPBezierCurve template class.
 *
 *  \date   2008-10-28
 */


namespace GMlib {


  template <typename T>
  inline
  DPBezierCurve<T>::DPBezierCurve( const DVector< Vector<T, 3> >& c ) {

    init();

    _closed = false;
    _scale = T(1);
    _pre_eval = true;
    _resamp_mode = GM_RESAMPLE_PREEVAL;

    // Set Control Points
    setControlPoints( c );
  }


  template <typename T>
  inline
  DPBezierCurve<T>::DPBezierCurve( const DVector< Vector<T, 3> >& c, T s, T t, T e ) {

    init();

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


  template <typename T>
  inline
  DPBezierCurve<T>::DPBezierCurve( const DPBezierCurve<T>& copy ) : DCurve<T>( copy ) {

    init();
  }


  template <typename T>
  inline
  DPBezierCurve<T>::DPBezierCurve( const PBezierCurve<T,3>& copy ) : DCurve<T>( copy ) {

    init();
  }


//  template <typename T>
//  inline
//  DPBezierCurve<T>::DPBezierCurve( PBezierCurve<T,3>* copy ) : DCurve<T>( copy ) {
//
//    _l_ref = copy;
//  }


  template <typename T>
  DPBezierCurve<T>::~DPBezierCurve() {}


  template <typename T>
  void DPBezierCurve<T>::edit( int selector ) {

    DCurve<T>::replot(0,false);
    if( this->_parent )
      this->_parent->edit( this );
  }


  template <typename T>
  inline
  string DPBezierCurve<T>::getIdentity() const {

    return "DPBezierCurve";
  }


//  template <typename T>
//  inline
//  PBezierCurve<T,3>* DPBezierCurve<T>::getPBezierCurve() {
//
//    return _l_ref;
//  }


  template <typename T>
  inline
  void DPBezierCurve<T>::hideSelectors() {

    if( !_selectors )
      return;

    // Remove Selector Grid
    DisplayObject::remove( _sg );
    delete _sg;
    _sg = 0;

    // Remove Selectors
    for( int i = 0; i < _s.getDim(); i++ ) {
      DisplayObject::remove( _s[i] );
      delete _s[i];
    }

    _selectors = false;
  }


  template <typename T>
  void DPBezierCurve<T>::init() {

//    _l_ref = dynamic_cast<PBezierCurve<T,3>*>(this->_p_ref);
    _selectors = false;
    _sg = 0;
  }


  template <typename T>
  bool DPBezierCurve<T>::isSelectorsVisible() const {

    return _selectors;
  }


  template <typename T>
  inline
  void DPBezierCurve<T>::localDisplay() {

    DCurve<T>::localDisplay();
  }


  template <typename T>
  inline
  void DPBezierCurve<T>::rotate(Angle a, const Vector<float,3>& rot_axel) {

    DParametrics<T,1>::rotate( a, rot_axel );
    if( this->_parent )
      this->_parent->edit( this );
  }


  template <typename T>
  inline
  void DPBezierCurve<T>::rotate(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d) {

    DParametrics<T,1>::rotate( a, p, d );
    if( this->_parent )
      this->_parent->edit( this );
  }


  template <typename T>
  inline
  void DPBezierCurve<T>::rotateGlobal(Angle a, const Vector<float,3>& rot_axel) {

    DParametrics<T,1>::rotateGlobal( a, rot_axel );
    if( this->_parent )
      this->_parent->edit( this );
  }


  template <typename T>
  inline
  void DPBezierCurve<T>::rotateGlobal(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d) {

    DParametrics<T,1>::rotateGlobal( a, p, d );
    if( this->_parent )
      this->_parent->edit( this );
  }


  template <typename T>
  inline
  void DPBezierCurve<T>::showSelectors( bool grid, const GLColor& _selector_color, const GLColor& grid_color ) {

    if( _selectors )
      return;

//    DVector< Vector<T, 3> > &c = _l_ref->getControlPoints();

    _s.setDim( _c.getDim() );
    for( int i = 0, s_id = 0; i < _c.getDim(); i++ ) {

      Selector<T,3> *sel = new Selector<T,3>( _c[i], s_id++, this, T(1), _selector_color );
      DisplayObject::insert( sel );
      _s[i] = sel;
    }


    if( grid ) {

      _sg = new SelectorGrid<T,3>( _c[0], this, grid_color );

      for( int i = 1; i < _c.getDim(); i++ )
          _sg->add(_c[i-1], _c[i]);  // Lines in grid

      DisplayObject::insert( _sg );
    }

    _selectors = true;
  }


  template <typename T>
  inline
  void DPBezierCurve<T>::translate( const Vector<float,3>& trans_vector ) {


    DParametrics<T,1>::translate( trans_vector );
    if( this->_parent )
      this->_parent->edit( this );
  }


  template <typename T>
  inline
  void DPBezierCurve<T>::translateGlobal( const Vector<float,3>& trans_vector ) {


    DParametrics<T,1>::translateGlobal( trans_vector );
    if( this->_parent )
      this->_parent->edit( this );
  }













  //////////////////////// DPBezierCurve !!!!!!!!!!!!!! DPBezierCurve ////////////////////////
  //////////////////////// DPBezierCurve !!!!!!!!!!!!!! DPBezierCurve ////////////////////////
  //////////////////////// DPBezierCurve !!!!!!!!!!!!!! DPBezierCurve ////////////////////////
  //////////////////////// DPBezierCurve !!!!!!!!!!!!!! DPBezierCurve ////////////////////////





  template <typename T>
  inline
  DVector< Vector<T,3> >& DPBezierCurve<T>::getControlPoints() {

    return _c;
  }


  template <typename T>
  inline
  int DPBezierCurve<T>::getDegree() const {

    return _c.getDim() - 1;
  }

  template <typename T>
  inline
  void DPBezierCurve<T>::eval( T t, int d, bool l ) {

    // Compute the Bernstein-Hermite Polynomials
    DMatrix< T > bhp;
    EvaluatorStatic<T>::evaluateBhp( bhp, getDegree(), t, _scale );

    this->_p = bhp * _c;
  }


  template <typename T>
  T DPBezierCurve<T>::getEndP() {

    return T(1);
  }


  template <typename T>
  inline
  T DPBezierCurve<T>::getLocalMapping( T t, T ts, T ti, T te ) {

    return (t - ts) / (te-ts);
  }


  template <typename T>
  T DPBezierCurve<T>::getStartP() {

    return T(0);
  }


  template <typename T>
  inline
  bool DPBezierCurve<T>::isClosed() const {

    return _closed;
  }


  template <typename T>
  inline
  void DPBezierCurve<T>::resample( DVector< DVector< Vector<T,3> > >& p, int m, int d, T start, T end ) {

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


  template <typename T>
  inline
  void DPBezierCurve<T>::resampleInline( DVector< DVector< Vector<T, 3> > >& p, int m, T dt ) {

    // For each sample point on the uniform curve calculate the Bernstein-Hermite Polynomials
    for( int i = 0; i < m; i++ ) {

      eval( i * dt );
      p[i] = this->_p;
    }
  }


  template <typename T>
  inline
  void DPBezierCurve<T>::resamplePreEval( DVector< DVector< Vector<T, 3> > >& p, int m, T dt ) {

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


  template <typename T>
  inline
  void DPBezierCurve<T>::setClosed( bool state ) {

    _closed = state;
  }

  template <typename T>
  inline
  void DPBezierCurve<T>::setControlPoints( const DVector< Vector<T,3> >& cp ) {


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


  template <typename T>
  inline
  void DPBezierCurve<T>::setResampleMode( GM_RESAMPLE_MODE mode ) {

    _resamp_mode = mode;
  }


  template <typename T>
  inline
  void DPBezierCurve<T>::setScale( T d ) {

    if( d == _scale )
      return;

    _scale = d;
    _pre_eval = true;
  }
}

