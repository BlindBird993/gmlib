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



/*! \file gmpsurf.c
 *
 *  Implementation of the PSurf template class.
 */


// gmlib
#include "visualizers/gmpsurfdefaultvisualizer.h"


// stl
#include <sstream>
#include <iomanip>

namespace GMlib {


  template <typename T, int n>
  inline
  PSurf<T,n>::PSurf( int s1, int s2 ) {

    _no_sam_u                       = s1;
    _no_sam_v                       = s2;
    _no_der_u                       = 1;
    _no_der_v                       = 1;
    _d1                             = -1;
    _d2                             = -1;
    _tr_u                           = T(0);
    _sc_u                           = T(1);
    _tr_v                           = T(0);
    _sc_v                           = T(1);

    setNoDer( 2 );
    //_setSam( s1, s2 );

    _default_visualizer = 0x0;
  }


  template <typename T, int n>
  inline
  PSurf<T,n>::PSurf( const PSurf<T,n>& copy ) : Parametrics<T,2,n>( copy ) {

    _p            = copy._p;
    _n            = copy._n;
    _u            = copy._u;
    _v            = copy._v;
    _d1           = copy._d1;
    _d2           = copy._d2;
    _tr_u         = copy._tr_u;
    _sc_u         = copy._sc_u;
    _tr_v         = copy._tr_v;
    _sc_v         = copy._sc_v;
    _sam_p_u      = copy._sam_p_u;
    _sam_p_v      = copy._sam_p_v;
    _no_sam_p_u   = copy._no_sam_p_u;
    _no_sam_p_v   = copy._no_sam_p_v;
    _default_d    = copy._default_d;

    _no_sam_u     = copy._no_sam_u;
    _no_sam_v     = copy._no_sam_v;
    _no_der_u     = copy._no_sam_u;
    _no_der_v     = copy._no_sam_v;

    _default_visualizer = 0x0;
  }

  template <typename T, int n>
  PSurf<T,n>::~PSurf() {

    enableDefaultVisualizer( false );
    if( _default_visualizer )
      delete _default_visualizer;
  }


  template <typename T, int n>
  inline
  void PSurf<T,n>::_eval( T u, T v, int d1, int d2 ) {

    if( !(d1 <= _d1 && d2 <=_d2 && u == _u && v == _v) ) {

      _u  = u;
      _v  = v;
      _d1 = d1;
      _d2 = d2;

      eval( shiftU(u), shiftV(v), d1, d2 );
    }
  }


  template <typename T, int n>
  inline
  void PSurf<T,n>::_evalDerDD( DMatrix<DMatrix <Vector<T,n> > >& a, int d1, int d2, T du, T dv ) const {

    T one_over_du;
    T one_over_dv;



    // Handle all singular patial derivatives in v direction;
    // the case of v == 0
    for( int u = 1, v = 0; u <= d1; u++ ) {

      one_over_du = T(1) / ( pow( T(2) * du, T(u) ) );
  //    T one_over_du = T(1);

      // Handle all partial derivatives in v direction.
      for( int i = 1; i < a.getDim1() - 1; i++ ) {
        for( int j = 0; j < a.getDim2(); j++ ) {

          // Iterate throug each component of the "point"
          for( int k = 0; k < 3; k++ )
            a[i][j][u][v][k] = a[i+1][j][u-1][v][k] - a[i-1][j][u-1][v][k];

          a[i][j][u][v] *= one_over_du;
        }
      }




      if( isClosedU() ) {

        // Handle the edges, for partial derivatives of the dataset; i1 = 0, i2 = a.getDim1()-1
        for( int i1 = 0, i2 = a.getDim1() - 1, j = 0; j < a.getDim2(); j++ ) {

          // Iterate throug each component of the "point"
          for( int k = 0; k < 3; k++ ) {

            a[i1][j][u][v][k] = a[i2][j][u][v][k] = ( a[i1+1][j][u-1][v][k] - a[i2-1][j][u-1][v][k]   );
          }
          a[i1][j][u][v] = a[i2][j][u][v] *= one_over_du;
        }
      }
      else {
        // Handle the edges, for partial derivatives of the dataset; i1 = 0, i2 = a.getDim1()-1
        for( int i1 = 0, i2 = a.getDim1() - 1, j = 0; j < a.getDim2(); j++ ) {

          // Iterate throug each component of the "point"
          for( int k = 0; k < 3; k++ ) {

            a[i1][j][u][v][k] = a[i1+1][j][u-1][v][k] - ( a[i1][j][u-1][v][k] + ( a[i1][j][u-1][v][k] - a[i1+1][j][u-1][v][k] ) );
            a[i2][j][u][v][k] = ( a[i2][j][u-1][v][k] + ( a[i2][j][u-1][v][k] - a[i2-1][j][u-1][v][k] ) ) - a[i2][j][u-1][v][k];
          }
          a[i1][j][u][v] *= one_over_du;
          a[i2][j][u][v] *= one_over_du;
        }
      }
    }




    for( int u = 0; u <= d1; u++ ) {
      for( int v = 1; v <= d2; v++ ) {

        one_over_dv = T(1) / ( pow( T(2) * dv, T(v) ) );
  //      T one_over_dv = T(1);

        // Handle all partial derivatives in v direction.
        for( int i = 0; i < a.getDim1(); i++ ) {
          for( int j = 1; j < a.getDim2() - 1; j++ ) {

            // Iterate throug each component of the "point"
            for( int k = 0; k < 3; k++ )
              a[i][j][u][v][k] = a[i][j+1][u][v-1][k] - a[i][j-1][u][v-1][k];

            a[i][j][u][v] *= one_over_dv;
          }
        }

        if( isClosedV() ) {

          // Handle the edges, for partial derivatives of the dataset; j1 = 0, j2 = a.getDim2()-1
          for( int i = 0, j1 = 0, j2 = a.getDim2() - 1; i < a.getDim1(); i++ ) {

            // Iterate throug each component of the "point"
            for( int k = 0; k < 3; k++ ) {

              a[i][j1][u][v][k] = a[i][j2][u][v][k] = ( a[i][j1+1][u][v-1][k] - a[i][j2-1][u][v-1][k] );
            }
            a[i][j1][u][v] = a[i][j2][u][v] *= one_over_dv;
          }
        }
        else {

          // Handle the edges, for partial derivatives of the dataset; j1 = 0, j2 = a.getDim2()-1
          for( int i = 0, j1 = 0, j2 = a.getDim2() - 1; i < a.getDim1(); i++ ) {

            // Iterate throug each component of the "point"
            for( int k = 0; k < 3; k++ ) {

              a[i][j1][u][v][k] = a[i][j1+1][u][v-1][k] - ( a[i][j1][u][v-1][k] + ( a[i][j1][u][v-1][k] - a[i][j1+1][u][v-1][k] )   );
              a[i][j2][u][v][k] = ( a[i][j2][u][v-1][k] + ( a[i][j2][u][v-1][k] - a[i][j2-1][u][v-1][k] )  ) - a[i][j2-1][u][v-1][k];
            }
            a[i][j1][u][v] *= one_over_dv;
            a[i][j2][u][v] *= one_over_dv;
          }
        }
      }
    }
  }


  template <typename T, int n>
  inline
  void PSurf<T,n>::_evalNormal() {

    _n = _p(1)(0)^_p(0)(1);
  }


//  template <typename T, int n>
//  inline
//  void PSurf<T,n>::estimateClpPar( const Point<T,n>& p, T& u, T& v ) {
//  }

  template <typename T, int n>
  void PSurf<T,n>::enableDefaultVisualizer( bool enable ) {

    if( !enable )
      removeVisualizer( _default_visualizer );
    else {

      if( !_default_visualizer )
        _default_visualizer = new PSurfDefaultVisualizer<T,n>();

      insertVisualizer( _default_visualizer );
    }
  }


  template <typename T, int n>
  inline
  DMatrix<Vector<T,n> >& PSurf<T,n>::evaluate( Point<T,2> p, int d ) {

    return evaluate( p[0], p[1], d, d);
  }


  template <typename T, int n>
  inline
  DMatrix<Vector<T,n> >& PSurf<T,n>::evaluate( T u, T v, int d1, int d2 ) {

    _eval(u, v, d1, d2);
    _evalNormal();
    return _p;
  }


  template <typename T, int n>
  inline
  DVector<Vector<T,n> > PSurf<T,n>::evaluateD( Point<T,2> p, int d ) {

    return evaluateD(p[0], p[1], d, d);
  }


  template <typename T, int n>
  inline
  DVector<Vector<T,n> > PSurf<T,n>::evaluateD( T u, T v, int d1, int d2 ) {

    // Here we are coopying diagonal wise the matrix into an vector
    // One problem is if d1 is not equal d2.
    _eval(u, v, d1, d2);
    DVector<Vector<T,n> > p(_sum(d1, d2));
    int i,j;

    for(i = 0; i <= d1; i++) {
      for(j = 0; j<= std::min<int>(i, d2); j++)  {
        p += _p[i-j][j];
      }
    }

    // Origin --> for(;i <= max(d1, d2); i++)
    for(i = 0; i <= std::max<int>(d1, d2); i++) {
      for(j = i-d1; j <= std::min<int>(i, d2); j++) {
        p += _p[i-j][j];
      }
    }

    return p;
  }


  template <typename T, int n>
  inline
  DMatrix<Vector<T,n> >& PSurf<T,n>::evaluateGlobal( Point<T,2> p, int d ) {

    return evaluateGlobal( p[0], p[1], d, d);
  }


  template <typename T, int n>
  inline
  DMatrix<Vector<T,n> >& PSurf<T,n>::evaluateGlobal( T u, T v, int d1, int d2 ) {

    static DMatrix<Vector<T,n> > p;
    p.setDim( d1+1, d2+1 );

    eval(u,v,d1,d2);

    p[0][0] = this->_present * static_cast< Point<T,n> >(_p[0][0]);

    for( int j = 1; j < p.getDim2(); j++ )
      p[0][j] = this->_present * _p[0][j];

    for( int i = 1; i < p.getDim1(); i++ )
      for( int j = 0; j < p.getDim2(); j++ )
        p[i][j] = this->_present * _p[i][j];

    return p;
  }


  template <typename T, int n>
  inline
  DMatrix<Vector<T,n> >& PSurf<T,n>::evaluateParent( Point<T,2> p, int d ) {

    return evaluateParent( p[0], p[1], d, d );
  }


  template <typename T, int n>
  inline
  DMatrix<Vector<T,n> >& PSurf<T,n>::evaluateParent( T u, T v, int d1, int d2 ) {

    static DMatrix<Vector<T,n> > p;
    p.setDim( d1+1, d2+1 );

    eval(u,v,d1,d2);

    p[0][0] = this->_matrix * static_cast< Point<T,n> >(_p[0][0]);

    for( int j = 1; j < p.getDim2(); j++ )
      p[0][j] = this->_matrix * _p[0][j];

    for( int i = 1; i < p.getDim1(); i++ )
      for( int j = 0; j < p.getDim2(); j++ )
        p[i][j] = this->_matrix * _p[i][j];

    return p;
  }


  template <typename T, int n>
  inline
  T PSurf<T,n>::getCurvatureGauss( T u, T v ) {

    _eval(u, v, 2, 2);
    UnitVector<T,n>   N   = _p[1][0]^_p[0][1];
    Vector<T,n>		  du  = _p[1][0];
    Vector<T,n>		  dv  = _p[0][1];
    Vector<T,n>		  duu = _p[2][0];
    Vector<T,n>		  duv = _p[1][1];
    Vector<T,n>		  dvv = _p[0][2];

    T E = du  * du;
    T F = du  * dv;
    T G = dv  * dv;
    T e = N   * duu;
    T f = N   * duv;
    T g = N   * dvv;

    return (e*g - f*f) / (E*G - F*F);
  }


  template <typename T, int n>
  inline
  T PSurf<T,n>::getCurvatureMean( T u, T v ) {

    _eval(u,v,2,2);
    UnitVector<T,n>   N   = _p[1][0]^_p[0][1];
    Vector<T,n>		  du  = _p[1][0];
    Vector<T,n>		  dv  = _p[0][1];
    Vector<T,n>		  duu = _p[2][0];
    Vector<T,n>		  duv = _p[1][1];
    Vector<T,n>		  dvv = _p[0][2];

    T E = du  * du;
    T F = du  * dv;
    T G = dv  * dv;
    T e = N   * duu;
    T f = N   * duv;
    T g = N   * dvv;

    return 0.5 * (e*G - 2 * (f*F) + g*E) / (E*G - F*F);
  }


  template <typename T, int n>
  inline
  T PSurf<T,n>::getCurvaturePrincipalMax( T u, T v ) {

    T K = getCurvatureGauss( u, v );
    T H = getCurvatureMean( u, v );

    return H + sqrt( H*H - K );
  }


  template <typename T, int n>
  inline
  T PSurf<T,n>::getCurvaturePrincipalMin( T u, T v ) {

    T K = getCurvatureGauss( u, v );
    T H = getCurvatureMean( u, v );

    return H - sqrt( H*H - K );
  }


  template <typename T, int n>
  inline
  int PSurf<T,n>::getDerivativesU() const {

    return _no_der_u;
  }


  template <typename T, int n>
  inline
  int PSurf<T,n>::getDerivativesV() const {

    return _no_der_v;
  }


  template <typename T, int n>
  inline
  Vector<T,n>& PSurf<T,n>::getDerU( T u, T v ) {

    _eval(u, v, 1, 0);
    return _p[1][0];
  }


  template <typename T, int n>
  inline
  Vector<T,n>& PSurf<T,n>::getDerUU( T u, T v ) {

    _eval(u, v, 2, 0);
    return _p[2][0];
  }


  template <typename T, int n>
  inline
  Vector<T,n>& PSurf<T,n>::getDerUV( T u, T v ) {

    _eval(u, v, 2, 2);
    return _p[1][1];
  }


  template <typename T, int n>
  inline
  Vector<T,n>& PSurf<T,n>::getDerV( T u, T v ) {

    _eval(u, v, 0, 1);
    return _p[0][1];
  }


  template <typename T, int n>
  inline
  Vector<T,n>& PSurf<T,n>::getDerVV( T u, T v ) {

    _eval(u, v, 0, 2);
    return _p[0][2];
  }


  template <typename T, int n>
  inline
  T PSurf<T,n>::getLocalMapping( T t, T /*ts*/, T /*tt*/, T /*te*/ ) {

    return t;
  }


  template <typename T, int n>
  inline
  Vector<T,n>& PSurf<T,n>::getNormal() {

    return _n;
  }


  template <typename T, int n>
  inline
  T PSurf<T,n>::getParDeltaU() {

    return _sc_u * (getEndPU() - getStartPU());
  }


  template <typename T, int n>
  inline
  T PSurf<T,n>::getParDeltaV() {

    return _sc_v * (getEndPV() - getStartPV());
  }


  template <typename T, int n>
  inline
  T PSurf<T,n>::getParEndU() {

    return getParStartU() + getParDeltaU();
  }


  template <typename T, int n>
  inline
  T PSurf<T,n>::getParEndV() {

    return getParStartV() + getParDeltaV();
  }


  template <typename T, int n>
  inline
  T PSurf<T,n>::getParStartU() {

    return getStartPU() + _tr_u;
  }


  template <typename T, int n>
  inline
  T PSurf<T,n>::getParStartV() {

    return getStartPV() + _tr_v;
  }

  template <typename T, int n>
  inline
  Vector<T,n>& PSurf<T,n>::getPosition( T u, T v ) {

    _eval(u, v, 0, 0);
    return _p[0][0];
  }

  template <typename T, int n>
  inline
  int PSurf<T,n>::getSamPU( int i ) const {

    return _no_sam_p_u(i);
  }


  template <typename T, int n>
  inline
  int PSurf<T,n>::getSamPV( int i ) const {

    return _no_sam_p_v(i);
  }


  template <typename T, int n>
  inline
  int PSurf<T,n>::getSamplesU() const {

    return _no_sam_u;
  }


  template <typename T, int n>
  inline
  int PSurf<T,n>::getSamplesV() const {

    return _no_sam_v;
  }

  template <typename T, int n>
  inline
  void PSurf<T,n>::insertVisualizer( Visualizer *visualizer ) {

    DisplayObject::insertVisualizer( visualizer );

    PSurfVisualizer<T,n> *visu = dynamic_cast<PSurfVisualizer<T,n>*>( visualizer );
    if( !visu )
      return;

    if( _psurf_visualizers.exist( visu ) )
      return;

    _psurf_visualizers += visu;
  }


  template <typename T, int n>
  bool PSurf<T,n>::isClosedU() const {

    return false;
  }


  template <typename T, int n>
  bool PSurf<T,n>::isClosedV() const {

    return false;
  }


  template <typename T, int n>
  bool PSurf<T,n>::getClosestPoint( const Point<T,n>& q, T& u, T& v ) {

    T a11, a12, a21, a22, b1, b2;
    T du, dv, det;

    /*! \todo fix matrix */
    HqMatrix<T,n> invmat = this->_present;
    invmat.invertOrthoNormal();
    Point<T,n> p = invmat * q;  // Egentlig _present


    for(int i = 0; i < 20; i++ ) {

      DMatrix< Vector<T,n> > &r = evaluate( u, v, 2, 2 );
      Vector<T,n> d = p-r[0][0];

      a11 = d*r[2][0] - r[1][0] * r[1][0];
      a12 = d*r[1][1] - r[1][0] * r[0][1];
      a21 = a12;
      a22 = d*r[0][2] - r[0][1] * r[0][1];

      b1  = -(d*r[1][0]);
      b2  = -(d*r[0][1]);

      det = a11*a22 - a12*a21;
      du  = (b1*a22 - a12*b2) / det;
      dv  = (a11*b2 - b1*a21) / det;
      u   += du;
      v   += dv;

      if(std::fabs(du) < 1e-6 && std::fabs(dv) < 1e-6)
        return true;
    }

    return false;
  }

  template <typename T, int n>
  inline
  bool PSurf<T,n>::getClosestPoint( const Point<T,n>& q, Point<T,2>& uv ) {

    return getClosestPoint(q, uv[0], uv[1]);
  }

  template <typename T, int n>
  inline
  void PSurf<T,n>::preSample(
    int /*m1*/, int /*m2*/, int /*d1*/, int /*d2*/,
    T /*s_u*/, T /*s_v*/, T /*e_u*/, T /*e_v*/
  ) {}


  template <typename T, int n>
  void PSurf<T,n>::replot( int m1, int m2, int d1, int d2 ) {


    // Correct sample domain
    if( m1 < 2 )
      m1 = _no_sam_u;
    else
      _no_sam_u = m1;

    if( m2 < 2 )
      m2 = _no_sam_v;
    else
      _no_sam_v = m2;

    // Correct derivatives
    if( d1 < 1 )
      d1 = _no_der_u;
    else
      _no_der_u = d1;

    if( d2 < 1 )
      d2 = _no_der_v;
    else
      _no_der_v = d2;


    // pre-sampel / pre evaluate data for a given parametric surface, if wanted/needed
    preSample(
      m1, m2, d1, d2,
      getStartPU(),
      getStartPV(),
      getEndPU(),
      getEndPV()
    );


    // Sample Positions and related Derivatives
    DMatrix< DMatrix< Vector<T,n> > > p;
    resample(
      p, m1, m2, d1, d2,
      getStartPU(),
      getStartPV(),
      getEndPU(),
      getEndPV()
    );

    // Sample Normals
    DMatrix< Vector<T,n> > normals;
    resampleNormals( p, normals );

    // Set The Surrounding Sphere
    setSurroundingSphere( p );

    // Replot Visaulizers
    for( int i = 0; i < this->_psurf_visualizers.getSize(); i++ )
      this->_psurf_visualizers[i]->replot( p, normals, m1, m2, d1, d2, isClosedU(), isClosedV() );
  }

  template <typename T, int n>
  inline
  void PSurf<T,n>::removeVisualizer( Visualizer *visualizer ) {

    PSurfVisualizer<T,n> *visu = dynamic_cast<PSurfVisualizer<T,n>*>( visualizer );
    if( visu )
      _psurf_visualizers.remove( visu );

    DisplayObject::removeVisualizer( visu );
  }


  template <typename T, int n>
  void PSurf<T,n>::resample( DMatrix< DMatrix < Vector<T,n> > >& a,
                           int m1, int m2, int d1, int d2,
                           T s_u, T s_v, T e_u, T e_v ) {

    T du = (e_u-s_u)/(m1-1);
    T dv = (e_v-s_v)/(m2-1);

    _p.setDim( d1 + 1, d2 + 1 );
    a.setDim(m1, m2);

    for(int i=0; i<m1-1; i++) {

      T u = s_u + i*du;
      for(int j=0;j<m2-1;j++) {

        eval(u, s_v + j*dv, d1, d2 );
        a[i][j] = _p;
      }

      eval(u, e_v, d1, d2, false, true);
      a[i][m2-1] = _p;
    }

    for(int j=0;j<m2-1;j++) {

      eval(e_u, s_v + j*dv, d1, d2, true, false);
      a[m1-1][j] = _p;
    }

    eval(e_u, e_v, d1, d2, true, true);
    a[m1-1][m2-1] = _p;

    switch( this->_dm ) {
      case GM_DERIVATION_EXPLICIT:
        // Do nothing, evaluator algorithms for explicite calculation of derivatives
        // should be defined in the eval( ... ) function enclosed by
        // if( this->_derivation_method == this->EXPLICIT ) { ... eval algorithms for derivatives ... }
        break;

      case GM_DERIVATION_DD:
      default:
        _evalDerDD( a, d1, d2, du, dv );
        break;
    }
  }


  template <typename T, int n>
  inline
  void PSurf<T,n>::resample( DMatrix<DMatrix <DMatrix <Vector<T,n> > > >& a,
                           int m1, int m2, int d1, int d2 ) {

    resample( a, m1, m2, d1, d2, getStartPU(), getStartPV(), getEndPU(), getEndPV() );
  }


  template <typename T, int n>
  void PSurf<T,n>::resampleNormals( const DMatrix<DMatrix<Vector<T,n> > > &sample, DMatrix<Vector<T,3> > &normals ) const {

    normals.setDim( sample.getDim1(), sample.getDim2() );

    for( int i = 0; i < sample.getDim1(); i++ )
      for( int j = 0; j < sample.getDim2(); j++ )
        normals[i][j] = Vector<T,3>(sample(i)(j)(1)(0))^Vector<T,3>(sample(i)(j)(0)(1));
  }


  template <typename T, int n>
  inline
  void PSurf<T,n>::setDomainU( T start, T end ) {

    _sc_u  = (end - start) / (getEndPU() - getStartPU());
    _tr_u  = start - getStartPU();
  }


  template <typename T, int n>
  inline
  void PSurf<T,n>::setDomainUScale( T sc ) {

    _sc_u = sc;
  }


  template <typename T, int n>
  inline
  void PSurf<T,n>::setDomainUTrans( T tr ) {

    _tr_u = tr;
  }


  template <typename T, int n>
  inline
  void PSurf<T,n>::setDomainV( T start, T end ) {

    _sc_v  = (end - start) / (getEndPV() - getStartPV());
    _tr_v  = start - getStartPV();
  }


  template <typename T, int n>
  inline
  void PSurf<T,n>::setDomainVScale( T sc ) {

    _sc_v = sc;
  }


  template <typename T, int n>
  inline
  void PSurf<T,n>::setDomainVTrans( T tr ) {

    _tr_v = tr;
  }


  template <typename T, int n>
  inline
  void PSurf<T,n>::setNoDer( int d ) {

     _default_d  = d;
  }


  template <typename T, int n>
  void PSurf<T,n>::setSurroundingSphere( const DMatrix< DMatrix< Vector<T,n> > >& p ) {

    Sphere<T,n>  s( p(0)(0)(0)(0) );
    s += Point<T,n>( p( p.getDim1()-1 )( p.getDim2()-1 )(0)(0) );
    s += Point<T,n>( p( p.getDim1()/2 )( p.getDim2()/2 )(0)(0) );
    s += Point<T,n>( p( p.getDim1()-1 )( 0             )(0)(0) );
    s += Point<T,n>( p( 0             )( p.getDim2()-1 )(0)(0) );
    s += Point<T,n>( p( p.getDim1()-1 )( p.getDim2()/2 )(0)(0) );
    s += Point<T,n>( p( p.getDim1()/2 )( p.getDim2()-1 )(0)(0) );
    s += Point<T,n>( p( 0             )( p.getDim2()/2 )(0)(0) );
    s += Point<T,n>( p( p.getDim1()/2 )( 0             )(0)(0) );
    Parametrics<T,2,n>::setSurroundingSphere(s.template toType<float>());
  }


  template <typename T, int n>
  inline
  T PSurf<T,n>::shiftU( T u ) {

    return getStartPU() + _sc_u * ( u - getParStartU() );
  }


  template <typename T, int n>
  inline
  T PSurf<T,n>::shiftV( T v ) {

    return getStartPV() + _sc_v * ( v - getParStartV() );
  }


  template <typename T, int n>
  Parametrics<T,2,n>* PSurf<T,n>::split( T /*t*/, int /*uv*/ ) {

    return 0;
  }

  template <typename T, int n>
  void PSurf<T,n>::toggleDefaultVisualizer() {

    if( !_psurf_visualizers.exist( _default_visualizer ) )
      enableDefaultVisualizer( true );
    else
      enableDefaultVisualizer( false );
  }


  template <typename T, int n>
  inline
  const Point<T,n>& PSurf<T,n>::operator () ( T u, T v ) {

    _eval(u, v, _default_d, _default_d);
    return static_cast<Point<T,n> >(_p[0][0]);
  }


} // END namespace GMlib
