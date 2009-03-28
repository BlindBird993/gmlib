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



/*! \file gmPBezierSurf.c
 *
 *  Implementation of the gmPBezierSurf template class.
 *
 *  \date   2008-11-20
 */


// GMlib
#include "gmEvaluatorStatic.h"

namespace GMlib {



  template <typename T, int n>
  inline
  PBezierSurf<T, n>::PBezierSurf ( const DMatrix< Vector<T, n> >& cp ) {

    _cu = false;
    _cv = false;
    _su = T( 1 );
    _sv = T( 1 );
    _pre_eval = true;
    _resamp_mode = GM_RESAMPLE_PREEVAL;

    // Set Control Points
    setControlPoints( cp );
  }


  template <typename T, int n>
  inline
  PBezierSurf<T, n>::PBezierSurf( const DMatrix< Vector<T, n> >& c, T us, T u, T ue, T vs, T v, T ve ) {

    _cu = false;
    _cv = false;
    _su = T(1)/(ue-us);
    _sv = T(1)/(ve-vs);
    _pre_eval = true;
    _resamp_mode = GM_RESAMPLE_PREEVAL;

    // Generate the control points
    DMatrix<T> bhpu, bhpv;
    EvaluatorStatic<T>::evaluateBhp( bhpu, c.getDim1()-1, ( u - us ) / ( ue - us ), _su );
    EvaluatorStatic<T>::evaluateBhp( bhpv, c.getDim2()-1, ( v - vs ) / ( ve - vs ), _sv );
    bhpu.invert();
    bhpv.invert();
    bhpv.transpose();

    _c = bhpu * (c^bhpv);

    for( int i = 0; i < c.getDim1(); i++ )
      for( int j = 0; j < c.getDim2(); j++ )
        _c[i][j] -= c(0)(0);

    this->translateGlobal( c(0)(0) );
  }


  template <typename T, int n>
  inline
  PBezierSurf<T, n>::PBezierSurf ( const PBezierSurf<T, n>& pbc ) : PSurf<T,n>( pbc ) {

    _c = pbc._c;
    _cu = pbc._cu;
    _cv = pbc._cv;
    _su = pbc._su;
    _sv = pbc._sv;
    _pre_eval = pbc._pre_eval;
    _resamp_mode = pbc._resamp_mode;
  }

  template <typename T, int n>
  inline
  void PBezierSurf<T, n>::eval( T u, T v, int d1, int d2, bool lu, bool lv ) {

    // Set Dimensions
    this->_p.setDim( getDegreeU()+1, getDegreeV()+1 );

    // Compute the Bernstein-Hermite Polynomials
    DMatrix< T > bu, bv;
    EvaluatorStatic<T>::evaluateBhp( bu, this->getDegreeU(), u, T(1) );
    EvaluatorStatic<T>::evaluateBhp( bv, this->getDegreeV(), v, T(1) );
//    bv.transpose();

    for( int i = 0; i < bu.getDim1(); i++ )
      for( int j = 0; j < bu.getDim2(); j++ )
        this->_p[i][j] = bu[i] * ( _c^bv[j] );
  }


  template <typename T, int n>
  inline
  DMatrix< Vector<T, n> >& PBezierSurf<T, n>::getControlPoints() {

    return _c;
  }

  template <typename T, int n>
  inline
  int PBezierSurf<T, n>::getDegreeU() const {

    return _c.getDim1() - 1;
  }


  template <typename T, int n>
  inline
  int PBezierSurf<T, n>::getDegreeV() const {

    return _c.getDim2() - 1;
  }


  template <typename T, int n>
  inline
  T PBezierSurf<T, n>::getEndPU() {

    return T(1);
  }


  template <typename T, int n>
  inline
  T PBezierSurf<T, n>::getEndPV() {

    return T(1);
  }


  template <typename T, int n>
  std::string PBezierSurf<T,n>::getIdentity() const {

    return "PBezierSurf";
  }


  template <typename T, int n>
  inline
  T PBezierSurf<T, n>::getLocalMapping( T t, T ts, T tt, T te ) {

    return (t - ts) / (te-ts);
  }


  template <typename T, int n>
  inline
  T PBezierSurf<T, n>::getStartPU() {

    return T(0);
  }


  template <typename T, int n>
  inline
  T PBezierSurf<T, n>::getStartPV() {

    return T(0);
  }


  template <typename T, int n>
  inline
  bool PBezierSurf<T, n>::isClosedU() const {

    return _cu;
  }


  template <typename T, int n>
  inline
  bool PBezierSurf<T, n>::isClosedV() const {

    return _cv;
  }


  template <typename T, int n>
  inline
  void PBezierSurf<T, n>::resample(
    DMatrix< DMatrix < Vector<T,n> > >& p,
    int m1,
    int m2,
    int d1,
    int d2,
    T s_u,
    T s_v,
    T e_u,
    T e_v
  ) {

    // dt; sample step value
    const T du = (e_u-s_u) / T(m1-1);
    const T dv = (e_v-s_v) / T(m2-1);

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


  template <typename T, int n>
  inline
  void PBezierSurf<T, n>::resampleInline( DMatrix< DMatrix< Vector<T, n> > >& p, int m1, int m2, T du, T dv ) {

    // For each sample point on the uniform curve calculate the Bernstein-Hermite Polynomials
    for( int i = 0; i < m1; i++ ) {
      for( int j = 0; j < m2; j++ ) {

        eval( i * du, j * dv );
        p[i][j] = this->_p;
      }
    }
  }


  template <typename T, int n>
  inline
  void PBezierSurf<T, n>::resamplePreEval( DMatrix< DMatrix < Vector<T,n> > >& p, int m1, int m2, T du, T dv ) {

    // Check whether or not to redo the preEvaluation
    // No point i checking the dimensions of bhps_v as they are the same as their u equivilents
    if( _pre_eval || m1 != _u.getDim1() || m2 != _u.getDim2() ) {

      // Set the dimension of the Bernstein-Hermite Polynomial DVector
      _u.setDim(m1,m2);
      _v.setDim(m1,m2);

      // Compute the Bernstein-Hermite Polynomiale, for the Bezier Surface
      for( int i = 0; i < m1; i++ ) {
        for( int j = 0; j < m2; j++ ) {

          EvaluatorStatic<T>::evaluateBhp( _u[i][j], getDegreeU(), i*du, T(1) );
          EvaluatorStatic<T>::evaluateBhp( _v[i][j], getDegreeV(), j*dv, T(1) );
        }
      }

      // Disable the pre-evaluation step
      _pre_eval = false;
    }

    p.setDim( m1, m2 );
    cout << endl;
    for( int i = 0; i < m1; i++ ) {
      for( int j = 0; j < m2; j++ ) {

        DMatrix<T> &u = _u[i][j];
        DMatrix<T> &v = _v[i][j];
        for( int k = 0; k < u.getDim1(); k++ )
          for( int l = 0; l < v.getDim2(); l++ )
            p[i][j][k][l] = u[k] * (_c^v[l]);
      }
    }
  }


  template <typename T, int n>
  inline
  void PBezierSurf<T, n>::setClosed( bool closed_u, bool closed_v ) {

    _cu = closed_u;
    _cv = closed_v;
  }


  template <typename T, int n>
  inline
  void PBezierSurf<T, n>::setControlPoints( const DMatrix< Vector<T, n> >& cp ) {


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


  template <typename T, int n>
  inline
  void PBezierSurf<T, n>::setResampleMode( GM_RESAMPLE_MODE mode ) {

    _resamp_mode = mode;
  }


  template <typename T, int n>
  inline
  void PBezierSurf<T, n>::setScale( T du, T dv ) {

    if( du == _su || dv == _sv )
      return;

    _su = du;
    _sv = dv;
    _pre_eval = true;
  }

}

