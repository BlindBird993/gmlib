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



/*! \file gmVCoordinateSystem.h
 *
 *  Interface for the VCoordinateSystem class.
 *
 *  \date   2009-08-25
 */

#ifndef __gmVCOORIDINATESYSTEM_H__
#define __gmVCOORIDINATESYSTEM_H__


#include "gmGLColor.h"
#include "gmVisualizer.h"


namespace GMlib {


  enum GM_VISUALIZER_COORDSYS {
    GM_VISUALIZER_COORDSYS_LOCAL,
    GM_VISUALIZER_COORDSYS_GLOBAL,
    GM_VISUALIZER_COORDSYS_PARENT
  };

  template <typename T, int n>
  class VCoordinateSystem : public Visualizer<T,n> {
  public:
    VCoordinateSystem();
    VCoordinateSystem( const VCoordinateSystem<T,n>& copy );
    ~VCoordinateSystem();

    void                      display();
    GM_VISUALIZER_COORDSYS    getCoordinateSystem() const;
    std::string               getIdentity() const;
    void                      replot(
      DVector< DVector< Vector<T, 3> > >& p,
      int m, int d
    );
    void                      replot(
      DMatrix< DMatrix< Vector<T, 3> > >& p,
      DMatrix< Vector<T, 3> >& normals,
      int m1, int m2, int d1, int d2
    );
    void                      setCoordinateSystem( GM_VISUALIZER_COORDSYS coordsys );

  protected:
    unsigned int              _dlist;
    GM_VISUALIZER_COORDSYS    _cs;

    void                      genDList();
    void                      init();


  };

} // END namespace GMlib

// Include VCoordinateSystem class function implementations
#include "gmVCoordinateSystem.c"


#endif // __gmVCOORIDINATESYSTEM_H__





