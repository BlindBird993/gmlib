
// include for syntaxhighlighting in editors
#include "gmdivideddifferences.h"

// gmlib
#include "gmutils.h"

// stl
#include <cassert>


template< typename T>
inline
void GMlib::DD::compute1D( T& p, double dt, bool closed, int d, int de ) {

  assert( de >= 0 );

  double dt2 = 2*dt;
  int k = p.getDim()-1;

  for(int j = 1+de; j <= de+d; j++) {

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


template <typename T>
inline
void GMlib::DD::compute2D( T& p, double du, double dv, bool closed_u, bool closed_v,
                int d1, int d2, int de1, int de2 ) {

  assert( de1 >= 0 );
  assert( de2 >= 0 );


  double du2 = 2*du;
  double dv2 = 2*dv;
  int ku = p.getDim1()-1;
  int kv = p.getDim2()-1;


  // Compute U derivatives

  for(int j = 1+de1; j <= de1+d1; ++j) { // der in u

    int j1 = j-1;

    // ordinary divided differences
    for(int k = 1; k < ku; ++k)     // data points u
      for(int l = 0; l < kv+1; ++l) // data points v
        p[k][l][j][0] = (p[k+1][l][j1][0] - p[k-1][l][j1][0]) / du2;

    if(closed_u) { // biting its own tail

      for(int l = 0; l < kv+1; ++l) { // data points u
        p[0 ][l][j][0] = (p[1][l][j1][0] - p[ku  ][l][j1][0]) / du2;
        p[ku][l][j][0] = (p[0][l][j1][0] - p[ku-1][l][j1][0]) / du2;
      }
    }
    else { // second degree endpoints divided differences

      for(int l = 0; l < kv+1; ++l) { // data points u
        p[0 ][l][j][0] = ( 4*p[1   ][l][j1][0] - 3*p[0 ][l][j1][0] - p[2   ][l][j1][0] ) / du2;
        p[ku][l][j][0] = (-4*p[ku-1][l][j1][0] + 3*p[ku][l][j1][0] - p[ku-2][l][j1][0] ) / du2;
      }
    }
  }






  // Compute ALL V derivatives

  for(int j = 1+de2; j <= de2+d2; ++j) { // der in u
    for( int i = 0; i <= de1+d1; ++i ) {

    int j1 = j-1;

    // ordinary divided differences
    for(int k = 0; k < ku+1; ++k)   // data points u
      for(int l = 1; l < ku; ++l)   // data points v
        p[k][l][i][j] = (p[k][l+1][i][j1] - p[k][l-1][i][j1]) / dv2;

    if(closed_v) { // biting its own tail

      for(int k = 0; k < ku+1; ++k) { // data points v
        p[k][0 ][i][j] = (p[k][1][i][j1] - p[k][kv  ][i][j1]) / dv2;
        p[k][kv][i][j] = (p[k][0][i][j1] - p[k][kv-1][i][j1]) / dv2;
      }
    }
    else { // second degree endpoints divided differences

      for(int k = 0; k < ku+1; ++k) { // data points v
        p[k][0 ][i][j] = ( 4*p[k][1   ][i][j1] - 3*p[k][0 ][i][j1] - p[k][2   ][i][j1] ) / dv2;
        p[k][kv][i][j] = (-4*p[k][kv-1][i][j1] + 3*p[k][kv][i][j1] - p[k][ku-2][i][j1] ) / dv2;
      }
    }
    }
  }

}

