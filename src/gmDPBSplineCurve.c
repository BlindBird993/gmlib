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



/*! \file gmDPBSplineCurve.c
 *
 *  Implementation of the DPBSplineCurve template class.
 *
 *  \date   2008-10-28
 */


namespace GMlib {


//  template <typename T>
//  inline
//  DPBSplineCurve<T>::DPBSplineCurve( const DVector< Vector<T, 3> >& cv,  int d  ) : DCurve<T>( new PBSplineCurve<T, 3>( cv, d ) ) {
//
//    init();
//  }


  template <typename T>
  inline
  DPBSplineCurve<T>::DPBSplineCurve( const DVector< Vector<T, 3> >& cv,  int d  ) {

    init();
  }


  template <typename T>
  inline
  DPBSplineCurve<T>::DPBSplineCurve( const DPBSplineCurve<T>& copy ) : DCurve<T>( copy ) {

    init();
  }


//  template <typename T>
//  inline
//  DPBSplineCurve<T>::DPBSplineCurve( const PBSplineCurve<T,3>& copy ) : DCurve<T>( copy ) {
//
//    init();
//  }


//  template <typename T>
//  inline
//  DPBSplineCurve<T>::DPBSplineCurve( PBSplineCurve<T,3>* copy ) : DCurve<T>( copy ) {
//
//    _l_ref = copy;
//  }


  template <typename T>
  DPBSplineCurve<T>::~DPBSplineCurve() {}


  template <typename T>
  inline
  string DPBSplineCurve<T>::getIdentity() const {

    return "DPBSplineCurve";
  }


//  template <typename T>
//  inline
//  PBSplineCurve<T,3>* DPBSplineCurve<T>::getPBSplineCurve() {
//
//    return _l_ref;
//  }


  template <typename T>
  void DPBSplineCurve<T>::init() {

//    _l_ref = dynamic_cast<PBSplineCurve<T,3>*>( this->_p_ref );
  }



  //////////////////////// PBSplineCurve !!!!!!!!!!!!!! PBSplineCurve ////////////////////////
  //////////////////////// PBSplineCurve !!!!!!!!!!!!!! PBSplineCurve ////////////////////////
  //////////////////////// PBSplineCurve !!!!!!!!!!!!!! PBSplineCurve ////////////////////////
  //////////////////////// PBSplineCurve !!!!!!!!!!!!!! PBSplineCurve ////////////////////////



  template <typename T>
  inline
  void DPBSplineCurve<T>::eval( T t, int d_not_used, bool l ) {

    const int d = getDegree();
    int idx;
    DMatrix<T> bhp;

    if( _pre_eval ) {

      // Fill the Bernstein Polynomial Matrices
      idx = d;

      // Calculate index
      if( t > _kv[idx+1] )
        idx++;

      // Evaluate the Bernstine Polynomial of sampl i of m
      evalBernsteinHermite( bhp, t, idx );
    }

    // Compute the BSpline using the pre evalued Bernstein Polynomials and the Control Points.
    DVector< Vector<T,3> > c;
    c.setDim( d + 1 );
    for( int j = 0; j <= d; j++ )
      c[j] = _cp[idx-(d-j)];

    this->_p = bhp * c;
  }


  template <typename T>
  inline
  void DPBSplineCurve<T>::evalBernsteinHermite( DMatrix<T>& bhp, T t, int idx ) const {

    const int d = getDegree();
    bhp.setDim( d+1, d+1 );

    // Transformed t value
    DVector<T> w;

    // Compute the Bernztein polynomials 1 -> d.
    // One for each row, starting from the bottom up.
    bhp[d-1][0] = 1 - getW( t, idx, 1 );
    bhp[d-1][1] = getW( t, idx, 1 );

    for( int i = d - 2, d_c = 2; i >= 0; i--, d_c++ ) {

      // Generate w
      w.setDim(d_c);
      for( int j = d_c; j > 0; j-- )
        w[j-1] = getW( t, idx - ( d_c - j ), d_c );

      // Compute the bernstein polynomials
      bhp[i][0] = ( 1 - w[0]) * bhp[i+1][0];
      for( int j = 1; j < d - i; j++ )
        bhp[i][j] = w[j-1] * bhp[i+1][j-1] + (1 - w[j]) * bhp[i+1][j];
      bhp[i][d-i] = w[d_c-1] * bhp[i+1][d-i-1];
    }


    // Compute all the deriatives
    bhp[d][0] = -getWder( t, idx, 1 ) * _scale;
    bhp[d][1] = getWder( t, idx, 1 ) * _scale;

    for( int k = 2; k <= d; k++ ) {
      for( int i = d, d_c = 2; i > d - k; i--, d_c++ ) {

        // Generate w for the derivatives
        w.setDim(d_c);
        for( int j = 1; j <= d_c; j++ )
          w[j-1] = k * getWder( t, idx - ( d_c - j ), d_c ) * _scale;

        // Complete the bernstein polynomials by adding the computation of derivatives
        bhp[i][k] = w[0] * bhp[i][k-1];
        for( int j = k - 1, idx_c = 1; j > 0; j--, idx_c++ )
          bhp[i][j] = w[idx_c] * ( bhp[i][j-1] - bhp[i][j] );
        bhp[i][0] = - w[d_c-1] * bhp[i][0];
      }
    }
  }


  template <typename T>
  inline
  void DPBSplineCurve<T>::generateKnotVector() {

    int order = getDegree() + 1;

    _kv.setDim( _cp.getDim() + order );
    int step_knots = _kv.getDim() - ( order * 2 );

    T knot_value = T(0);
    int i = 0;

    // Set the start knots
    for( ; i < order; i++ )
      _kv[i] = knot_value;

    // Set the "step"-knots
    for( int j = 0; j < step_knots; j++ )
      _kv[i++] = ++knot_value;

    // Set the end knots
    knot_value++;
    for( ; i < _kv.getDim(); i++ )
      _kv[i] = knot_value;
  }


  template <typename T>
  inline
  int DPBSplineCurve<T>::getDegree() const {

    return _degree;
  }


  template <typename T>
  T DPBSplineCurve<T>::getEndP() {

    return _kv[_cp.getDim() + getDegree()];
  }


  template <typename T>
  inline
  int DPBSplineCurve<T>::getIndex( T t, int m ) const {

    return ( t * T(getDegree()) ) / T(m);
  }


  template <typename T>
  T DPBSplineCurve<T>::getStartP() {

    return _kv[0];
  }


  template <typename T>
  inline
  T DPBSplineCurve<T>::getW( T t, int idx, int d ) const {

    return ( t - _kv(idx) ) / ( _kv(idx+d) - _kv(idx) );
  }


  template <typename T>
  inline
  T DPBSplineCurve<T>::getWder( T t, int idx, int d ) const {

    return T(1) / ( _kv(idx+d) - _kv(idx) );
  }


  template <typename T>
  inline
  bool DPBSplineCurve<T>::isClosed() const {

    return false;
  }


  template <typename T>
  inline
  void DPBSplineCurve<T>::resample( DVector< DVector< Vector<T,3> > >& p, int m, int not_used, T start, T end ) {

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
  void DPBSplineCurve<T>::resampleInline( DVector< DVector< Vector<T,3> > >& p, int m, T dt ) {

    // For each sample point on the uniform curve compute the Bernstein-Hermite Polynomials
    for( int i = 0; i < m; i++ ) {

      eval( _kv[0] + T(i) * dt );
      p[i] = this->_p;
    }
  }


  template <typename T>
  inline
  void DPBSplineCurve<T>::resamplePreEval( DVector< DVector< Vector<T,3> > >& p, int m, T dt ) {

    const int d = getDegree();

    if( _pre_eval ) {

      T t;
      int idx;

      // Init the indice table and the Bernstein-Hermite Polynomial DVector used in pre-evaluation
      _bhps.setDim(m);
      _indices.setDim( m );

      // Fill the Bernstein Polynomial Matrices
      idx = d;
      for( int i = 0; i < m; i++ ) {

        // Calculate indices
        t = _kv[0] + T(i) * dt;
        if( t > _kv[idx+1] )
          idx++;
        _indices[i] = idx;

        // Evaluate the Bernstine Polynomial of sampl i of m
        evalBernsteinHermite( _bhps[i], t, idx );
      }
    }

    // Compute the BSpline using the pre evalued Bernstein Polynomials and the Control Points.
    DVector< Vector<T, 3> > c(d+1);
    for( int i = 0; i < m; i++ ) {

      for( int j = 0; j <= d; j++ )
        c[j] = _cp[_indices[i]-(d-j)];

      p[i] = _bhps[i] * c;
    }
  }

  template <typename T>
  inline
  void DPBSplineCurve<T>::setControlPoints( const DVector< Vector<T,3> >& cp, bool gen_kv ) {


    // Check whether or not the curve should be pre_evaluated again at the next evaluation,
    // and if the control points should be updated
    if( _cp.getDim() == cp.getDim() ) {

      bool no_change = true;
      for( int i = 0; i < cp.getDim(); i++ )
        if( _cp[i] != cp(i) )
          no_change = false;

      if( no_change )
        return;
    }
    else {

      _pre_eval = true;
    }

    // Set Degree
    _cp = cp;

    // Adjust degree if to high.
    if( _degree > _cp.getDim() - 1 )
      _degree = _cp.getDim() - 1;

    // Generate knot vector if it's desired
    if( gen_kv )
      generateKnotVector();
  }


  template <typename T>
  inline
  void DPBSplineCurve<T>::setDegree( int d ) {

    if( d >= _cp.getDim() || d == _degree )
      return;

    _degree = d;
    _pre_eval = true;
  }


  template <typename T>
  inline
  void DPBSplineCurve<T>::setKnotVector( const DVector< T >& kv ) {

    if( kv.getDim() != _cp.getDim() + getDegree() + 1 )
      return;

    for( int i = 1; i < kv.getDim(); i++ )
      if( kv(i-1) > kv(i) )
        return;

    _kv = kv;
  }


  template <typename T>
  inline
  void DPBSplineCurve<T>::setResampleMode( GM_RESAMPLE_MODE mode ) {

    _resamp_mode = mode;
  }


  template <typename T>
  inline
  void DPBSplineCurve<T>::setScale( T d ) {

    if( d == _scale )
      return;

    _scale = d;
    _pre_eval = true;
  }
}


