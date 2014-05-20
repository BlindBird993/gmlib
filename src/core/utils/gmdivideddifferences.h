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


#ifndef __GM_CORE_UTILS_DIVIDEDDIFFERENCES_H__
#define __GM_CORE_UTILS_DIVIDEDDIFFERENCES_H__

// GMlib
#include "../types/gmpoint.h"
#include "../containers/gmdvector.h"
#include "../containers/gmdmatrix.h"


// Numeric includes
#include <cmath>

// System includes
#include <cstdlib>


namespace GMlib {

  namespace DD {

    template <typename T, int n>
    void compute1D( DVector< DVector< Vector<T, n> > > & p, T dt, bool closed, int d, int d_start = 1 );

    template <typename T, int n>
    void compute2D( DMatrix<DMatrix <Vector<T,n> > >& p,
                    T du, T dv, bool closed_u, bool closed_v,
                    int d1, int d2, int d1_start = 1, int d2_start = 1 );
//  {


//      assert( d1_start > 0 );
//      assert( d2_start > 0 );

//      // DEBUG START reset -- this is for debug
//      for( int i = 0; i < p.getDim1(); ++i )
//        for( int j = 0; j < p.getDim2(); ++j )
//          for( int k = 0; k < p(i)(j).getDim1(); ++k )
//            for( int l = 0; l < p(i)(j).getDim2(); ++l )
//              if(k!=0||l!=0) p[i][j][k][l] = Vector<T,n>(T(0));

//      // DEBUG END

//      std::cout << "################ p[before DD]: " << p << std::endl;




//      std::cout << "$$$$$$$$$$$$$$$$ p[after DD]: " << p << std::endl;

//    }
  }

} // END namespace


// Including template definition file.
#include "gmdivideddifferences.c"

#endif // __GM_CORE_UTILS_DIVIDEDDIFFERENCES_H__
