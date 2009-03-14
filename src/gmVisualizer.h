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



/*! \file gmVisualizer.h
 *
 *  Interface for the Visualizer class.
 *
 *  \date   2008-09-10
 */

#ifndef __gmVISUALIZER_H__
#define __gmVISUALIZER_H__


// STL includes
#include <string>

// GMlib includes
#include "gmDMatrix.h"
#include "gmOpenGL.h"


namespace GMlib {


  class DisplayObject;

  template <typename T, int n>
  class DParametrics;

  template <typename T>
  class DCurve;

  template <typename T>
  class DSurf;

  template <typename T, int n>
  class Visualizer {
  public:
    Visualizer();
    Visualizer( const Visualizer& v );
    virtual ~Visualizer();

    virtual void          display() = 0;
    virtual std::string   getIdentity() const;

    // Curve
    virtual void          replot(
      DVector< DVector< Vector<T, 3> > >& p,
      int m, int d
    );

    // Surface
    virtual void          replot(
      DMatrix< DMatrix< Vector<T, 3> > >& p,
      DMatrix< Vector<T, 3> >& normals,
      int m1, int m2, int d1, int d2
    );

    virtual void          select();
    void                  set( DParametrics<T,n>* obj );

    virtual bool          operator == ( const Visualizer* v ) const;


  protected:
    DParametrics<T,n>     *_ref;
    DCurve<T>             *_ref_n1;
    DSurf<T>              *_ref_n2;


  private:
    void                  _init();
  };



} // END namespace GMlib

// Include Visualizer class function implementations
#include "gmVisualizer.c"


#endif // __gmVISUALIZER_H__
