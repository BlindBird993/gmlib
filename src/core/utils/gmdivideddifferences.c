
// include for syntaxhighlighting in editors
#include "gmdivideddifferences.h"

// gmlib
#include "gmutils.h"

// stl
#include <cassert>


template <typename T, int n>
void GMlib::DD::compute1D( GMlib::DVector<GMlib::DVector<GMlib::Vector<T, n> > >& p, T dt, bool closed, int d, int d_start ) {

  assert( d_start > 0 );

  T dt2 = 2*dt;
  int k = p.getDim()-1;

  for(int j = d_start; j <= d_start+d; j++) {

    int j1 = j-1;

    for(int i = 1; i < k; i++) // ordinary divided differences
      p[i][j] = (p[i+1][j1] - p[i-1][j1])/dt2;

    if(closed) // biting its own tail
    {
      p[0][j] = (p[1][j1] - p[k][j1]  )/dt2;
      p[k][j] = (p[0][j1] - p[k-1][j1])/dt2;
    }
    else // second degree endpoints divided differences
    {
      p[0][j] = ( 4*p[1][j1]   - 3*p[0][j1] - p[2][j1]  )/dt2;
      p[k][j] = (-4*p[k-1][j1] + 3*p[k][j1] + p[k-2][j1])/dt2;
    }
  }
}



template <typename T, int n>
void GMlib::DD::compute2D( GMlib::DMatrix< GMlib::DMatrix < GMlib::Vector<T,n> > >& a,
                           T du, T dv, bool closed_u, bool closed_v,
                           int d1, int d2, int d1_start, int d2_start ) {
  GM_UNUSED(d1_start) GM_UNUSED(d2_start)


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




    if( closed_u ) {

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

      if( closed_v ) {

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
