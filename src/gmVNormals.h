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



/*! \file gmVNormals.h
 *
 *  Interface for the VNormals class.
 *
 *  \date   2009-01-28
 */

#ifndef __gmVNORMALS_H__
#define __gmVNORMALS_H__


// STL includes
#include <string>

// GMlib includes
#include "gmPoint.h"
#include "gmColor.h"
#include "gmDVector.h"
#include "gmDMatrix.h"
#include "gmVisualizer.h"


namespace GMlib {

  template <typename T, int n>
  class VNormals : public Visualizer<T,n> {
  public:
    VNormals();
    VNormals( const VNormals<T,n>& copy );
    ~VNormals();

    void                          display();
    const Color&                  getColor() const;
    std::string                   getIdentity() const;
    double                        getSize() const;
    void                          replot(
      DVector< DVector< Vector<T, 3> > >& p,
      int m, int d
    );
    void                          replot(
      DMatrix< DMatrix< Vector<T, 3> > >& p,
      DMatrix< Vector<T, 3> >& normals,
      int m1, int m2, int d1, int d2
    );
    void                          setColor( const Color& color );
    void                          setSize( double size = 1.0 );

  protected:
    DVector< Vector<float,3> >    _n1;
    DMatrix< Arrow<float,3> >     _n2;

    Color                         _color;
    double                        _size;
  };

} // END namespace GMlib

// Include VNormals class function implementations
#include "gmVNormals.c"


#endif // __gmVNORMALS_H__



