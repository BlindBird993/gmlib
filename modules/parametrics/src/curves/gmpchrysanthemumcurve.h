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




#ifndef GM_PARAMETRICS_CURVE_PCHRYSANTHEMUMCURVE_H
#define GM_PARAMETRICS_CURVE_PCHRYSANTHEMUMCURVE_H


#include "../gmpcurve.h"


namespace GMlib {

  template <typename T>
  class PChrysanthemumCurve : public PCurve<T,3> {
    GM_SCENEOBJECT(PChrysanthemumCurve)
  public:
    PChrysanthemumCurve( T radius = T(1) );
    PChrysanthemumCurve( const PChrysanthemumCurve<T>& copy );

  protected:
    T             _r;

    void          eval( T t, int d, bool l );
    T             getEndP();
    T             getStartP();
    bool          isClosed() const;

  }; // END class PChrysanthemumCurve

} // END namespace GMlib


// Include PChrysanthemumCurve class function implementations
#include "gmpchrysanthemumcurve.c"

#endif // GM_PARAMETRICS_CURVE_PCHRYSANTHEMUMCURVE_H
