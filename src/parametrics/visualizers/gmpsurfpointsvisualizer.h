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



/*! \file gmpsurfpointsvisualizer.h
 *
 *  Interface for the PSurfPointsVisualizer class.
 */


#ifndef __GMPSURFPOINTSVISUALIZER_H__
#define __GMPSURFPOINTSVISUALIZER_H__

#include "gmpsurfvisualizer.h"

// gmlib
#include <core/types/gmpoint.h>
#include <core/containers/gmdvector.h>
#include <core/containers/gmdmatrix.h>
#include <core/utils/gmcolor.h>


namespace GMlib {


  template <typename T>
  class PSurfPointsVisualizer : public PSurfVisualizer<T> {
  public:
    PSurfPointsVisualizer();
    virtual ~PSurfPointsVisualizer();

    void              display();
    const Color&      getColor() const;
    std::string       getIdentity() const;
    float             getSize() const;
    void              replot(
      DMatrix< DMatrix< Vector<T, 3> > >& p,
      DMatrix< Vector<T, 3> >& normals,
      int m1, int m2, int d1, int d2
    );
    void              setColor( const Color& color );
    void              setSize( float size );

  protected:

    float             _size;
    Color             _color;

    GLuint            _vbo_v;
    int               _no_points;
  }; // END class PSurfPointsVisualizer



} // END namespace GMlib

// Include PSurfPointsVisualizer class function implementations
#include "gmpsurfpointsvisualizer.c"


#endif // __GMPSURFPOINTSVISUALIZER_H__
