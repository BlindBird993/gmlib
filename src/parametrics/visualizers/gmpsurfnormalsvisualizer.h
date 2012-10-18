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



/*! \file gmpsurfnormalsvisualizer.h
 *
 *  Interface for the PSurfNormalsVisualizer class.
 */


#ifndef __GMPSURFNORMALSVISUALIZER_H__
#define __GMPSURFNORMALSVISUALIZER_H__

#include "gmpsurfvisualizer.h"

// gmlib
#include <core/types/gmpoint.h>
#include <core/containers/gmdvector.h>
#include <core/containers/gmdmatrix.h>
#include <core/utils/gmcolor.h>


namespace GMlib {

  enum GM_SURF_NORMALSVISUALIZER_MODE {
    GM_SURF_NORMALSVISUALIZER_ALL,
    GM_SURF_NORMALSVISUALIZER_INTERIOR,
    GM_SURF_NORMALSVISUALIZER_BOUNDARY
  };

  template <typename T>
  class PSurfNormalsVisualizer : public PSurfVisualizer<T> {
  public:
    PSurfNormalsVisualizer();
    virtual ~PSurfNormalsVisualizer();

    void                              display();
    const Color&                      getColor() const;
    std::string                       getIdentity() const;
    GM_SURF_NORMALSVISUALIZER_MODE    getMode() const;
    double                            getSize() const;
    void                              replot(
      DMatrix< DMatrix< Vector<T, 3> > >& p,
      DMatrix< Vector<T, 3> >& normals,
      int m1, int m2, int d1, int d2
    );
    void                              setColor( const Color& color );
    void                              setMode( GM_SURF_NORMALSVISUALIZER_MODE mode );
    void                              setSize( double size = 1.0 );

  protected:
    GLuint                            _vbo_v;
    int                               _no_elements;

    Color                             _color;
    double                            _size;

    GM_SURF_NORMALSVISUALIZER_MODE    _mode;

    void                              makePlotAll( DMatrix< DMatrix< Vector<T, 3> > >& p, DMatrix< Vector<T, 3> >& normals );
    void                              makePlotInterior( DMatrix< DMatrix< Vector<T, 3> > >& p, DMatrix< Vector<T, 3> >& normals );
    void                              makePlotBoundary( DMatrix< DMatrix< Vector<T, 3> > >& p, DMatrix< Vector<T, 3> >& normals );


  };

} // END namespace GMlib

// Include PSurfNormalsVisualizer class function implementations
#include "gmpsurfnormalsvisualizer.c"





#endif // __GMPSURFNORMALSVISUALIZER_H__
