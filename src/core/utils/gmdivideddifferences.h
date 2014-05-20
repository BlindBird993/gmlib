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

    template <typename T>
    void compute1D( T& p, double dt, bool closed, int d, int de = 0 );

    template <typename T>
    void compute2D( T& p, double du, double dv, bool closed_u, bool closed_v, int d1, int d2, int de1 = 0, int de2 = 0 );
  }

} // END namespace


// Including template definition file.
#include "gmdivideddifferences.c"

#endif // __GM_CORE_UTILS_DIVIDEDDIFFERENCES_H__
