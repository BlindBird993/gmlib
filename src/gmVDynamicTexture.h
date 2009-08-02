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



/*! \file gmVDynamicTexture.h
 *
 *  Interface for the VDynamicTexture class.
 *  Visualizes Textures Dynamically on Displayable Curves, Surfaces, etc.
 *
 *  \date   2009-07-31
 */

#ifndef __gmVDYNAMICTEXTURE_H__
#define __gmVDYNAMICTEXTURE_H__


// STL includes
#include <string>

// GMlib includes
#include "gmVDefault.h"


namespace GMlib {

  template <typename T, int n>
  class VDynamicTexture : public VDefault<T,n> {
  public:
    VDynamicTexture();
    VDynamicTexture( const VDynamicTexture<T,n>& copy );

    void                    display();

    std::string             getIdentity() const;

    const HqMatrix<T,3>&    getMatrix() const;

    virtual void            rotate(const Angle& a, const Point<float,3>& p, const UnitVector<float,3>& d );
    virtual void            translate(const Vector<float,3>& trans_vector);

  protected:
    HqMatrix<T,3>           _matrix;


  }; // END class VDynamicTexture

} // END namespace GMlib

// Include VDynamicTexture class function implementations
#include "gmVDynamicTexture.c"


#endif // __gmVDYNAMICTEXTURE_H__

