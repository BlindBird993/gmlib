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



/*! \file gmpsubcurve.h
 *
 *  Interface for the PSurfCurve class.
 */

#ifndef __gmPSUBCURVE_H__
#define __gmPSUBCURVE_H__


#include "../gmpcurve.h"


namespace GMlib {


  template <typename T>
  class PSubCurve : public PCurve<T> {
  public:
    PSubCurve( PCurve<T>* c, T s, T e);
    PSubCurve( PCurve<T>* c, T s, T e, T t);
    PSubCurve( const PSubCurve<T>& copy );

    virtual ~PSubCurve();

    // virtual functions from SceneObject
    virtual std::string     getIdentity() const;
    // virtual functions from PSurf
    virtual bool            isClosed() const;
    // Local functions
    void                    togglePlot();

  protected:

    PCurve<T>*          _c;
    T                   _s;
    T                   _t;
    T                   _e;
    Vector<float,3>     _trans;

    // virtual functions from PSurf
    void                eval( T t, int d, bool l = false );
    T                   getEndP();
    T                   getStartP();

  private:

    // Local help functions
    void set(PCurve<T>* c, T s, T e, T t);

  }; // END class PSubCurve

} // END namepace GMlib


// Include PSubCurve class function implementations
#include "gmpsubcurve.c"


#endif // __gmPSUBCURVE_H__

