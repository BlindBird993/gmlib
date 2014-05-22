
// include for syntaxhighlighting in editors
#include "gmdivideddifferences.h"

// gmlib
#include "gmutils.h"
#include "../containers/gmdvector.h"
#include "../containers/gmdmatrix.h"

// stl
#include <cassert>

namespace GMlib {
  namespace DD {
    namespace Private {




      // ln : loop
      // en : end/execute
      // n  : dim













      template <int ln, int en, int n>
      class Static_For_Der_ {
      public:

        template <typename G>
        static void compute( G& assign, G& prev , G& next, const Vector<double,n>& dt, const Vector<int,n>& d, const Vector<int,n>& ed) {

          const int s = 0;
          const int e = d(ln-1);
          for( int i = s; i <= e; ++i )
            Static_For_Der_<ln+1,en,n>::compute( assign[i], prev[i], next[i], dt, d, ed );
        }
      };

      template <int en, int n>
      class Static_For_Der_<en,en,n> {
      public:

        template <typename G>
        static void compute( G& assign, G& prev , G& next, const Vector<double,n>& dt, const Vector<int,n>& d, const Vector<int,n>& ed ) {

          const int s = 1;
          const int e = d(en-1);
          for( int i = s; i <= e; ++i )
            assign[i] = (next[i-1] - prev[i-1]) / dt(en-1);
        }
      };








      template <int ln, int en, int n>
      class Static_For_Data_ {
      public:

        template <typename G>
        static void compute( G& assign, G& prev , G& next, const Vector<int,n>& k, const Vector<double,n>& dt, const Vector<int,n>& d, const Vector<int,n>& ed ) {

  //        std::cout << "  Data ln: " << ln;
          const int s = (ln == en ) ? 1 : 0;
          const int e = (ln == en ) ? k(ln-1) : k(ln-1)+1;
          const int o = (ln == en ) ? 1 : 0;    // offset
  //        std::cout << ", s: " << s <<", e: " << e << ", o: " << o;
  //        std::cout << std::endl;
          for( int i = s; i < e; ++i )
            Static_For_Data_<ln+1,en,n>::compute( assign[i], prev[i-o], next[i+o], k, dt, d, ed );
        }
      };

      template <int en, int n>
      class Static_For_Data_<n,en,n> {
      public:

        template <typename G>
        static void compute( G& assign, G& prev , G& next, const Vector<int,n>& k, const Vector<double,n>& dt, const Vector<int,n>& d, const Vector<int,n>& ed ) {

  //        std::cout << "  Data Base case";
          const int s = (n == en ) ? 1 : 0;
          const int e = (n == en ) ? k(n-1) : k(n-1)+1;
          const int o = (n == en ) ? 1 : 0;    // offset
  //        std::cout << ", s: " << s <<", e: " << e << ", o: " << o;
  //        std::cout << std::endl;
          for( int i = s; i < e; ++i )
            Static_For_Der_<1,en,n>::compute( assign[i],prev[i-o],next[i+o], dt, d, ed );
        }
      };



      template <int ln, int en, int n>
      class Static_For_Data_Boundary_Closed_ {
      public:

        template <typename G>
        static void compute( G& assign, G& prev , G& next, const Vector<int,n>& k, const Vector<double,n>& dt, const Vector<int,n>& d, const Vector<int,n>& ed ) {


          if( ln == en ) {
            Static_For_Data_Boundary_Closed_<ln+1,en,n>::compute( assign[0],       prev[k(ln-1)-1], next[1], k, dt, d, ed );
            Static_For_Data_Boundary_Closed_<ln+1,en,n>::compute( assign[k(ln-1)], prev[k(ln-1)-1], next[1], k, dt, d, ed );
          }
          else
            for( int i = 0; i < k(ln-1)+1; ++i ) Static_For_Data_Boundary_Closed_<ln+1,en,n>::compute( assign[i], prev[i], next[i], k, dt, d, ed );
        }
      };

      template <int en, int n>
      class Static_For_Data_Boundary_Closed_<n,en,n> {
      public:

        template <typename G>
        static void compute( G& assign, G& prev , G& next, const Vector<int,n>& k, const Vector<double,n>& dt, const Vector<int,n>& d, const Vector<int,n>& ed ) {

          if( n == en ) {
            Static_For_Der_<1,en,n>::compute( assign[0],      prev[k(n-1)-1], next[1], dt, d, ed );
            Static_For_Der_<1,en,n>::compute( assign[k(n-1)], prev[k(n-1)-1], next[1], dt, d, ed );
          }
          else
            for( int i = 0; i < k(n-1)+1; ++i ) Static_For_Der_<1,en,n>::compute( assign[i],prev[i],next[i], dt, d, ed );

        }
      };


















      template <int ln, int en, int n>
      class Static_For_Der_Boundary_Open_2nd_ {
      public:

        template <typename G>
        static void compute( G& assign, G& curr , G& next, G& next2, const Vector<double,n>& dt, const Vector<int,n>& d, const Vector<int,n>& ed, bool l ) {

          const int s = 0;
          const int e = d(ln-1);
          for( int i = s; i <= e; ++i )
            Static_For_Der_Boundary_Open_2nd_<ln+1,en,n>::compute( assign[i], curr[i], next[i], next2[i], dt, d, ed, l );
        }
      };

      template <int en, int n>
      class Static_For_Der_Boundary_Open_2nd_<en,en,n> {
      public:

        template <typename G>
        static void compute( G& assign, G& curr , G& next, G& next2, const Vector<double,n>& dt, const Vector<int,n>& d, const Vector<int,n>& ed, bool l ) {

          const int s = 1;
          const int e = d(en-1);
          const int sign = l ? 1 : -1;
          for( int i = s; i <= e; ++i )
            assign[i] = (sign*4*next[i-1] - sign*3*curr[i-1] - sign*3*next2[i-1]) / dt(en-1);


        }
      };









      template <int ln, int en, int n>
      class Static_For_Data_Boundary_Open_ {
      public:

        template <typename G>
        static void compute( G& assign, G& curr , G& next, G& next2, const Vector<int,n>& k, const Vector<double,n>& dt, const Vector<int,n>& d, const Vector<int,n>& ed, bool l = true ) {


          if( ln == en ) {
            Static_For_Data_Boundary_Open_<ln+1,en,n>::compute( assign[0],       curr[0],       next[1],         next[2],         k, dt, d, ed, true ); // left
            Static_For_Data_Boundary_Open_<ln+1,en,n>::compute( assign[k(ln-1)], curr[k(ln-1)], next[k(ln-1)-1], next[k(ln-1)-2], k, dt, d, ed, false ); // right
          }
          else {
            for( int i = 0; i < k(ln-1)+1; ++i )
              Static_For_Data_Boundary_Open_<ln+1,en,n>::compute( assign[i], curr[i], next[i], next2[i], k, dt, d, ed, l );
          }
        }
      };

      template <int en, int n>
      class Static_For_Data_Boundary_Open_<n,en,n> {
      public:

        template <typename G>
        static void compute( G& assign, G& curr , G& next, G& next2, const Vector<int,n>& k, const Vector<double,n>& dt, const Vector<int,n>& d, const Vector<int,n>& ed, bool l = true ) {

          if( n == en ) {
            Static_For_Der_Boundary_Open_2nd_<1,en,n>::compute( assign[0],      curr[0],      next[1],        next2[2],        dt, d, ed, true ); // left
            Static_For_Der_Boundary_Open_2nd_<1,en,n>::compute( assign[k(n-1)], curr[k(n-1)], next[k(n-1)-1], next2[k(n-1)-1], dt, d, ed, false ); // right
          }
          else {
            for( int i = 0; i < k(n-1)+1; ++i )
              Static_For_Der_Boundary_Open_2nd_<1,en,n>::compute( assign[i],curr[i],next[i], next2[i], dt, d, ed, l );
          }
        }
      };


















      template <int ln, int n>
      class Static_For_Dim_ {
      public:

        template <typename T>
        static void compute( T& p, const Vector<int,n>& k, const Vector<double,n>& dt, const Vector<bool,n>& closed, const Vector<int,n>& d, const Vector<int,n>& ed ) {

  //        std::cout << "Dim ln: " << ln << std::endl;
          Static_For_Data_<1,ln,n>::compute( p, p, p, k, dt, d, ed );

          if( closed(n-1) )
            Static_For_Data_Boundary_Closed_<1,ln,n>::compute( p, p, p, k, dt, d, ed );
          else
//            Static_For_Data_Boundary_Open_<1,ln,n>::compute( p, p, p, p, k, dt, d, ed )
                ;

          // Move on to next dimension pass
          Static_For_Dim_<ln+1,n>::compute( p, k, dt, closed, d, ed );
        }
      };


      template <int n>
      class Static_For_Dim_<n,n> {
      public:

        template <typename T>
        static void compute( T& p, const Vector<int,n>& k, const Vector<double,n>& dt, const Vector<bool,n>& closed, const Vector<int,n>& d, const Vector<int,n>& ed ) {

  //        std::cout << "Dim Base case " << std::endl;
          Static_For_Data_<1,n,n>::compute( p, p, p, k, dt, d, ed );

          if( closed(n-1) )
            Static_For_Data_Boundary_Closed_<1,n,n>::compute( p, p, p, k, dt, d, ed );
          else
//            Static_For_Data_Boundary_Open_<1,n,n>::compute( p, p, p, p, k, dt, d, ed )
            ;
        }
      };
    }

  }
}

template< typename T>
inline
void GMlib::DD::compute1D( T& p, double dt, bool closed, int d, int ed ) {

  assert( ed >= 0 );

  double dt2 = 2*dt;
  int k = p.getDim()-1;

  for(int i = 1+ed; i <= ed+d; i++) {

    int i1 = i-1;

    for(int l = 1; l < k; l++) // ordinary diviedd differences
      p[l][i] = (p[l+1][i1] - p[l-1][i1])/dt2;

    if(closed) // biting its own tail
    {
      p[0][i] = (p[1][i1] - p[k-1][i1])/dt2;
      p[k][i] = p[0][i];
    }
    else // second edgree endpoints diviedd differences
    {
      p[0][i] = ( 4*p[1][i1]   - 3*p[0][i1] - p[2][i1]  )/dt2;
      p[k][i] = (-4*p[k-1][i1] + 3*p[k][i1] + p[k-2][i1])/dt2;
    }
  }
}


template <typename T>
inline
void GMlib::DD::compute2D( T& p, double du, double dv, bool closed_u, bool closed_v,
                int d1, int d2, int ed1, int ed2 ) {

  assert( ed1 >= 0 );
  assert( ed2 >= 0 );

//  DD::compute(p, Vector<int,2>( p.getDim1(), p.getDim2() ),
//              Vector<double,2>(du,dv), Vector<bool,2>(closed_u,closed_v),
//              Vector<int,2>(d1,d2), Vector<int,2>(ed1,ed2) );


  double du2 = 2*du;
  double dv2 = 2*dv;
  int ku = p.getDim1()-1;
  int kv = p.getDim2()-1;


  // Compute U derivatives

  for(int i = 1+ed1; i <= ed1+d1; ++i) { // edr in u
    // j = 0

    int i1 = i-1;

    // ordinary divided differences
    for(int k = 1; k < ku; ++k)     // data points u
      for(int l = 0; l < kv+1; ++l) // data points v
        p[k][l][i][0] = (p[k+1][l][i1][0] - p[k-1][l][i1][0]) / du2;

    if(closed_u) { // biting its own tail

      for(int l = 0; l < kv+1; ++l) { // data points u
        p[0 ][l][i][0] = (p[1][l][i1][0] - p[ku-1][l][i1][0]) / du2;
        p[ku][l][i][0] = p[0][l][i][0];
      }
    }
    else { // second edgree endpoints divided differences

      for(int l = 0; l < kv+1; ++l) { // data points u
        p[0 ][l][i][0] = ( 4*p[1   ][l][i1][0] - 3*p[0 ][l][i1][0] - p[2   ][l][i1][0] ) / du2;
        p[ku][l][i][0] = (-4*p[ku-1][l][i1][0] + 3*p[ku][l][i1][0] + p[ku-2][l][i1][0] ) / du2;
      }
    }
  }






  // Compute ALL V derivatives

  for( int i = 0; i <= ed1+d1; ++i ) {
    for(int j = 1+ed2; j <= ed2+d2; ++j) { // edr in u

      int j1 = j-1;

      // ordinary divided differences
      for(int k = 0; k < ku+1; ++k)   // data points u
        for(int l = 1; l < kv; ++l)   // data points v
          p[k][l][i][j] = (p[k][l+1][i][j1] - p[k][l-1][i][j1]) / dv2;

      if(closed_v) { // biting its own tail

        for(int k = 0; k < ku+1; ++k) { // data points v
          p[k][0 ][i][j] = (p[k][1][i][j1] - p[k][kv-1][i][j1]) / dv2;
          p[k][kv][i][j] = p[k][0][i][j];
        }
      }
      else { // second edgree endpoints divided differences

        for(int k = 0; k < ku+1; ++k) { // data points v
          p[k][0 ][i][j] = ( 4*p[k][1   ][i][j1] - 3*p[k][0 ][i][j1] - p[k][2   ][i][j1] ) / dv2;
          p[k][kv][i][j] = (-4*p[k][kv-1][i][j1] + 3*p[k][kv][i][j1] + p[k][kv-2][i][j1] ) / dv2;
        }
      }
    }
  }

}


template <typename T, int n>
void GMlib::DD::compute( T& p, const Vector<int,n>& p_dims, const Vector<double,n>& dt, const Vector<bool,n>& closed, const Vector<int,n>& d, const Vector<int,n>& ed = Vector<int,n>(0) ) {

  const Vector<int,n> k = p_dims - Vector<int,n>(1);
  const Vector<double,n> dt2 = dt * 2;

  Private::Static_For_Dim_<1,n>::compute(p,k,dt2,closed,d,ed);
}
