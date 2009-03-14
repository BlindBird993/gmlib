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



/*! \file gmPSurf.c
 *
 *  Implementation of the gmPSurf template class.
 *  Tensor Product surface.
 *
 *  \date   2008-07-17
 */


#include <iomanip>
using std::setw;


namespace GMlib {



  /*! PSurf<T,n>::PSurf( int s1, int s2)
   *  \brief  Default Constructor
   *
   *  Default Constructor
   *  the default constructor
   */
  template <typename T, int n>
  inline
  PSurf<T,n>::PSurf( int s1, int s2 ) {

    _d1                             = -1;
    _d2                             = -1;
    _tr_u                           = T(0);
    _sc_u                           = T(1);
    _tr_v                           = T(0);
    _sc_v                           = T(1);
    //_setSam( s1, s2 );
  }


  template <typename T, int n>
  inline
  PSurf<T,n>::PSurf( const PSurf<T,n>& c ) : Parametrics<T,n> ( c ) {

    _p                              = c._p;
    _n                              = c._n;
    _u                              = c._u;
    _v                              = c._v;
    _d1                             = c._d1;
    _d2                             = c._d2;
    _tr_u                           = c._tr_u;
    _sc_u                           = c._sc_u;
    _tr_v                           = c._tr_v;
    _sc_v                           = c._sc_v;
    _sam_p_u                        = c._sam_p_u;
    _sam_p_v                        = c._sam_p_v;
    _sam1                           = c._sam1;
    _sam2                           = c._sam2;
    _default_d                      = c._default_d;
  }


  template <typename T, int n>
  inline
  PSurf<T,n>::~PSurf() {
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
          for( int k = 0; k < n; k++ )
            a[i][j][u][v][k] = a[i+1][j][u-1][v][k] - a[i-1][j][u-1][v][k];

          a[i][j][u][v] *= one_over_du;
        }
      }




      if( isClosedU() ) {

        // Handle the edges, for partial derivatives of the dataset; i1 = 0, i2 = a.getDim1()-1
        for( int i1 = 0, i2 = a.getDim1() - 1, j = 0; j < a.getDim2(); j++ ) {

          // Iterate throug each component of the "point"
          for( int k = 0; k < n; k++ ) {

            a[i1][j][u][v][k] = a[i2][j][u][v][k] = ( a[i1+1][j][u-1][v][k] - a[i2-1][j][u-1][v][k]   );
          }
          a[i1][j][u][v] = a[i2][j][u][v] *= one_over_du;
        }
      }
      else {
        // Handle the edges, for partial derivatives of the dataset; i1 = 0, i2 = a.getDim1()-1
        for( int i1 = 0, i2 = a.getDim1() - 1, j = 0; j < a.getDim2(); j++ ) {

          // Iterate throug each component of the "point"
          for( int k = 0; k < n; k++ ) {

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
            for( int k = 0; k < n; k++ )
              a[i][j][u][v][k] = a[i][j+1][u][v-1][k] - a[i][j-1][u][v-1][k];

            a[i][j][u][v] *= one_over_dv;
          }
        }

        if( isClosedV() ) {

          // Handle the edges, for partial derivatives of the dataset; j1 = 0, j2 = a.getDim2()-1
          for( int i = 0, j1 = 0, j2 = a.getDim2() - 1; i < a.getDim1(); i++ ) {

            // Iterate throug each component of the "point"
            for( int k = 0; k < n; k++ ) {

              a[i][j1][u][v][k] = a[i][j2][u][v][k] = ( a[i][j1+1][u][v-1][k] - a[i][j2-1][u][v-1][k] );
            }
            a[i][j1][u][v] = a[i][j2][u][v] *= one_over_dv;
          }
        }
        else {

          // Handle the edges, for partial derivatives of the dataset; j1 = 0, j2 = a.getDim2()-1
          for( int i = 0, j1 = 0, j2 = a.getDim2() - 1; i < a.getDim1(); i++ ) {

            // Iterate throug each component of the "point"
            for( int k = 0; k < n; k++ ) {

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

    _n = Vector3D<T>( _p(1)(0) ) ^ Vector3D<T>( _p(0)(1) );
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
  int PSurf<T,n>::getSamU( int i ) {

    return _sam1[i];
  }


  template <typename T, int n>
  inline
  int PSurf<T,n>::getSamV( int i ) {

    return _sam2[i];
  }

  template <typename T, int n>
  inline
  int PSurf<T,n>::getDerU() {

    return _d1;
  }


  template <typename T, int n>
  inline
  int PSurf<T,n>::getDerV() {

    return _d2;
  }


  template <typename T, int n>
  inline
  void PSurf<T,n>::setEval( int d ) {

     _default_d  = d;
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
  inline
  Point<T,n>& PSurf<T,n>::operator () ( T u, T v ) {

    _eval(u, v, _default_d, _default_d);
    return static_cast<Point<T,n> >(_p[0][0]);
  }


  template <typename T, int n>
  inline
  Vector<T,n>& PSurf<T,n>::getDerU( T u, T v ) {

    _eval(u, v, 1, 0);
    return _p[1][0];
  }


  template <typename T, int n>
  inline
  Vector<T,n>& PSurf<T,n>::getDerV( T u, T v ) {

    _eval(u, v, 0, 1);
    return _p[0][1];
  }


  template <typename T, int n>
  inline
  Vector<T,n>& PSurf<T,n>::getDerUU( T u, T v ) {

    _eval(u, v, 2, 0);
    return _p[2][0];
  }


  template <typename T, int n>
  inline
  Vector<T,n>& PSurf<T,n>::getDerVV( T u, T v ) {

    _eval(u, v, 0, 2);
    return _p[0][2];
  }


  template <typename T, int n>
  inline
  Vector<T,n>& PSurf<T,n>::getDerUV( T u, T v ) {

    _eval(u, v, 2, 2);
    return _p[1][1];
  }


  template <typename T, int n>
  inline
  std::string PSurf<T,n>::getIdentity() const {

    return "PSurf";
  }


  template <typename T, int n>
  inline
  T PSurf<T,n>::getLocalMapping( T t, T ts, T tt, T te ) {

    return t;
  }


  template <typename T, int n>
  inline
  Vector<T,n>& PSurf<T,n>::getNormal() {

    return _n;
  }


  template <typename T, int n>
  inline
  DMatrix<Vector<T,n> >& PSurf<T,n>::evaluate( T u, T v, int d1, int d2 ) {

    static DMatrix<Vector<T,n> > p( d1+1, d2+1 );

    eval(u,v,d1,d2);
    Vector<float,n> tmp;

    for( int i = 0; i < p.getDim1(); i++ ) {
      for( int j = 0; j < p.getDim2(); j++ ) {

        if( i==0 && j==0 )
          tmp = this->_matrix * (Point<float,n>)_p[0][0].toFloat();
        else
          tmp = this->_matrix * (Vector<float,n>)_p[i][j].toFloat();

        for( int k = 0; k < 3; k++ )
          p[i][j][k] = tmp[k];
      }
    }

    return p;
  }


  template <typename T, int n>
  inline
  DMatrix<Vector<T,n> >& PSurf<T,n>::evaluateLocal( T u, T v, int d1, int d2 ) {

    _eval(u, v, d1, d2);
    _evalNormal();
    return _p;
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
      for(j = 0; j<= min(i, d2); j++)	{
        p += _p[i-j][j];
      }
    }

    // Origin --> for(;i <= max(d1, d2); i++)
    for(i = 0; i <= max(d1, d2); i++) {
      for(j = i-d1; j <= min(i, d2); j++) {
        p += _p[i-j][j];
      }
    }

    return p;
  }


  template <typename T, int n>
  inline
  DMatrix<Vector<T,n> >& PSurf<T,n>::evaluate( Point<T,2> p, int d ) {

    return evaluate( p[0], p[1], d, d);
  }


  template <typename T, int n>
  inline
  DVector<Vector<T,n> > PSurf<T,n>::evaluateD( Point<T,2> p, int d ) {

    return evaluateD(p[0], p[1], d, d);
  }


//  template <typename T, int n>
//  inline
//  T PSurf<T,n>::getCurvatureGauss( T u, T v ) {
//
//    _eval(u, v, 2, 2);
//    UnitVector<T,3> N   = normal(u, v);	    // _p[0][1]^_p[1][0];
//    Vector<T,3>		  du  = getDerU(u, v);	  // _p[0][1];
//    Vector<T,3>		  dv  = getDerV(u, v);	  // _p[1][0];
//    Vector<T,3>		  duu = getDerUU(u, v);	  // _p[0][2];
//    Vector<T,3>		  duv = getDerUV(u, v);	  // _p[1][1];
//    Vector<T,3>		  dvv = getDerVV(u, v);	  // _p[2][0];
//
//    T E = du  * du;
//    T F = du  * dv;
//    T G = dv  * dv;
//    T e = N   * duu;
//    T f = N   * duv;
//    T g = N   * dvv;
//
//    return (e*g - f*f) / (E*G - F*F);
//  }
//
//
//  template <typename T, int n>
//  inline
//  T PSurf<T,n>::getCurvatureMean( T u, T v ) {
//
//    _eval(u,v,2,2);
//    UnitVector<T,3> N   = normal(u, v);
//    Vector<T,3>		  du  = getDerU(u, v);
//    Vector<T,3>		  dv  = getDerV(u, v);
//    Vector<T,3>		  duu = getDerUU(u, v);
//    Vector<T,3>		  duv = getDerUV(u, v);
//    Vector<T,3>		  dvv = getDerVV(u, v);
//
//    T E = du  * du;
//    T F = du  * dv;
//    T G = dv  * dv;
//    T e = N   * duu;
//    T f = N   * duv;
//    T g = N   * dvv;
//
//    return 0.5 * (e*G - 2 * (f*F) + g*E) / (E*G - F*F);
//  }


//  template <typename T, int n>
//  inline
//  void PSurf<T,n>::estimateClpPar( const Point<T,n>& p, T& u, T& v ) {
//  }


  template <typename T, int n>
  inline
  PSurf<T,n>* PSurf<T,n>::split( T t, int uv ) {

    return 0;
  }


  template <typename T, int n>
  inline
  void PSurf<T,n>::resampleNormals( const DMatrix<DMatrix<Vector<T, 3> > > &sample, DMatrix<Vector<T, 3> > &normals ) const {

    normals.setDim( sample.getDim1(), sample.getDim2() );

//    cout << "Generating Normals:" << endl;

    for( int i = 0; i < sample.getDim1(); i++ ) {
      for( int j = 0; j < sample.getDim2(); j++ ) {
        normals[i][j] = Vector3D<T>( sample(i)(j)(1)(0) ) ^ sample(i)(j)(0)(1);
//        normals[i][j] = Vector3D<T>( sample(i)(j)(0)(1) ) ^ sample(i)(j)(1)(0);
  //
  //      cout << "\t[" << i << ", " << j << "] (";
  //      for( int k = 0; k < n; k++ ){
  //
  //        cout << setw(3) << sample(i)(j)(1)(0)(k);
  //        if( k != n-1 )
  //          cout << ", ";
  //      }
  //      cout << ") u'";
  //      cout << endl;
  //
  //      cout << "\t[" << i << ", " << j << "] (";
  //      for( int k = 0; k < n; k++ ){
  //
  //        cout << setw(3) << sample(i)(j)(0)(1)(k);
  //        if( k != n-1 )
  //          cout << ", ";
  //      }
  //      cout << ") v'";
  //      cout << endl;
  //
  //      cout << "\t[" << i << ", " << j << "] (";
  //      for( int k = 0; k < n; k++ ){
  //
  //        cout << setw(3) << normals[i][j][k];
  //        if( k != n-1 )
  //          cout << ", ";
  //      }
  //      cout << ") norm";
  //      cout << endl << endl;
      }
  //      cout << endl;
    }
  }


  template <typename T, int n>
  inline
  void PSurf<T,n>::resample(
    DMatrix< DMatrix < Vector<T,n> > >& a,
    int m1,
    int m2,
    int d1,
    int d2,
    T s_u,
    T s_v,
    T e_u,
    T e_v
  ) {

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
  void PSurf<T,n>::resample(
    DMatrix<DMatrix <DMatrix <Vector<T,n> > > >	& a,
    int m1,
    int m2,
    int d1,
    int d2
  ) {

//    if(m1>0)
//    for(int i=0; i< _sam1.getDim(); i++)
//      _sam1[i]= max(2,int(0.5+(m1*(_sam_p_u[i+1] - _sam_p_u[i]))/(_sam_p_u.back() - _sam_p_u[0])));
//    if(m2>0)
//    for(int i=0; i< _sam2.getDim(); i++)
//      _sam2[i]= max(2,int(0.5+(m2*(_sam_p_v[i+1] - _sam_p_v[i]))/(_sam_p_v.back() - _sam_p_v[0])));
//
//    a.setDim(_sam1.getDim(),_sam2.getDim());
//
//    for(int i = 0; i < a.getDim1(); i++)
//      for(int j = 0; j < a.getDim2(); j++)
//        resample(a[i][j],_sam1[i],_sam2[j], d1, d2, _sam_p_u[i],_sam_p_v[j],_sam_p_u[i+1],_sam_p_v[j+1]);
  }

}
