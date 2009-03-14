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



/*! \file gmAffineSpace.h
 *  AffineSpace class header
 *
 *  Interface for the AffineSpace class.
 *
 *  \date   2008-11-24
 */

#ifndef __gmAFFINESPACE_H__
#define __gmAFFINESPACE_H__

// STL
#include <iostream>

// GMlib
#include "gmOpenGL.h" // Needs to be swapped with the include for the HqMatrix.

namespace GMlib {


  template <typename T, int n>
  class AffineSpace {
  public:
    AffineSpace();
    AffineSpace( const AffineSpace<T,n>& copy );

    Vector<T,n>	          getDir();
    virtual std::string   getIdentity() const;
    GLMatrix&             getMatrix();
    Point<T,n>	          getPos();
    Vector<T,n>	          getSide();
    Vector<T,n>	          getUp();

    virtual void          move(const Vector<T,n>& t);

    virtual void          rotate( Angle a, const Vector<T,n>& rot_axel );
    virtual void          rotateGlobal( Angle a, const Vector<T,n>& rot_axel );
    virtual void          rotate( Angle a, const Point<T,n>& p,const UnitVector<T,n>& d );
    virtual void          rotateGlobal( Angle a, const Point<T,n>& p,const UnitVector<T,n>& d );
    virtual void          translate( const Vector<T,n>& trans_vector );
    virtual void          translateGlobal( const Vector<T,n>& trans_vector );


  protected:
    GLMatrix              _matrix;            // Needs to be swaped with HqMatrix

    Point<T,n>		        _pos;
    UnitVector<T,n>       _dir;
    UnitVector<T,n>	      _side;
    UnitVector<T,n>       _up;

    virtual void          basisChange(
                            const Vector<T,n>& dir,
                            const Vector<T,n>& side,
                            const Vector<T,n>& up,
                            const Vector<T,n>& pos
                          );

  private:
    void                  _init();
  };

}

// Include Function Implementations
#include "gmAffineSpace.c"

#endif // __gmAFFINESPACE_H__
