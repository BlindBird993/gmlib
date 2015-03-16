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

#ifndef __gmPLINE_H__
#define __gmPLINE_H__


#include "../gmpcurve.h"


namespace GMlib {


  template <typename T>
  class PLine : public PCurve<T,3> {
    GM_SCENEOBJECT(PLine)
  public:
    explicit PLine( const Point<T,3>& p, const Vector<T,3>& v );
    explicit PLine( const Point<T,3>& p1, const Point<T,3>& p2 );
    PLine( const PLine<T>& copy );
    virtual ~PLine();

    bool            isClosed() const;

  protected:
    Point<T,3>      _pt;
    Vector<T,3>     _v;

    void            eval(T t, int d, bool l);
    T               getEndP();
    T               getStartP();

  }; // END class PLine

} // END namepace GMlib

// Include PLine class function implementations
#include "gmpline.c"


#endif // __gmPLINE_H__
