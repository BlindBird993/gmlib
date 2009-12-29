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



/*! \file gmVDerivatives.h
 *
 *  Interface for the VDerivatives class.
 *
 *  \date   2009-01-28
 */

#ifndef __gmVDERIVATIVES_H__
#define __gmVDERIVATIVES_H__


// STL includes
#include <string>

// GMlib includes
#include "gmDVector.h"
#include "gmDMatrix.h"
#include "gmVisualizer.h"

namespace GMlib {

  enum GM_VISUALIZER_DERIVATIVES_SIZE {
    GM_VISUALIZER_DERIVATIVES_NORMALIZED,
    GM_VISUALIZER_DERIVATIVES_PERCENT,
    GM_VISUALIZER_DERIVATIVES_VERTEX,
  };

  template <typename T, int n>
  class VDerivatives : public Visualizer<T,n> {
  public:
    VDerivatives();
    VDerivatives( const VDerivatives<T,n>& copy );
    ~VDerivatives();

    void                                display();
    const Color&                        getColor() const;
    std::string                         getIdentity() const;
    int                                 getIdxU() const;
    int                                 getIdxV() const;
    double                              getSize() const;
    GM_VISUALIZER_DERIVATIVES_SIZE      getSizeMode() const;
    void                                replot(
      DVector< DVector< Vector<T, 3> > >& p,
      int m, int d
    );
    void                                replot(
      DMatrix< DMatrix< Vector<T, 3> > >& p,
      DMatrix< Vector<T, 3> >& normals,
      int m1, int m2, int d1, int d2
    );
    void                                setColor( const Color& color );
    void                                setDerivative( int u = 0, int v = 0 );
    void                                setSize( GM_VISUALIZER_DERIVATIVES_SIZE mode, double size = 1.0 );

  protected:
    Color                               _color;
    DVector< Arrow<float,3> >           _n1;
    DMatrix< Arrow<float,3> >           _n2;

    GM_VISUALIZER_DERIVATIVES_SIZE      _size_mode;
    double                              _size;

    int                                 _u;
    int                                 _v;
  };

} // END namespace GMlib

// Include VDerivatives class function implementations
#include "gmVDerivatives.c"


#endif // __gmVDERIVATIVES_H__






