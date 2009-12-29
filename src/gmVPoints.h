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



/*! \file gmVPoints.h
 *
 *  Interface for the VPoints class.
 *
 *  \date   2009-01-27
 */

#ifndef __gmVPOINTS_H__
#define __gmVPOINTS_H__


// STL includes
#include <string>

// GMlib includes
#include "gmDVector.h"
#include "gmVisualizer.h"

namespace GMlib {


  template <typename T, int n>
  class VPoints : public Visualizer<T,n> {
  public:
    VPoints();
    VPoints( const VPoints<T,n>& v );
    ~VPoints();

    void              display();
    const GLColor&    getColor() const;
    std::string       getIdentity() const;
    float             getSize() const;
    void              replot(
      DVector< DVector< Vector<T, 3> > >& p,
      int m, int d
    );
    void              replot(
      DMatrix< DMatrix< Vector<T, 3> > >& p,
      DMatrix< Vector<T, 3> >& normals,
      int m1, int m2, int d1, int d2
    );
    void              setColor( const GLColor& color );
    void              setSize( float size );

  protected:
    DVector< Point<float,3> >   _n1;
    DMatrix< Point<float,3> >   _n2;
    float             _size;
    GLColor           _color;
  };



} // END namespace GMlib

// Include VPoints class function implementations
#include "gmVPoints.c"


#endif // __gmVPOINTS_H__





