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



/*! \file gmPHermiteSurface.h
 *
 *  Interface for the PHermiteSurface class.
 *
 *  \date   2010-09-08
 */


#ifndef __gmPHERMITESURFACE_H__
#define __gmPHERMITESURFACE_H__



#include <gmArray.h>
#include <gmPCurve.h>
#include <gmPSurf.h>

namespace GMlib {

  
  /*! \class PHermiteSurface gmPHermiteSurface.h <gmPHermiteSurface>
   *  \brief Parametric tensor-product generic Hermite surface
   *
   *  A parametric tensor-product generic Hermite surface class.
   */
  template <typename T>
  class PHermiteSurface : public PSurf<T> {
  public:
    PHermiteSurface( const Array< PCurve<T>* >& c1, const Array<PCurve<T>* >& c2 );
    ~PHermiteSurface();

    bool                    isValidCoonsPatch();
    bool                    isValidHermiteSurface();

  protected:
    Array< PCurve<T>* >     _c1, _c2;
    DMatrix< Point<T,3> >   _b;

    void                    edit( SceneObject* obj );
    void                    eval(T u, T v, int d1, int d2, bool lu, bool lv);
    T                       getEndPU();
    T                       getEndPV();
    T                       getH(  int d, int k, T t );
    T                       getHder( int d, int k, T t );
    T                       getStartPU();
    T                       getStartPV();

    void                    insertPatch( PCurve<T>* patch );

  }; // END class PHermiteSurf


} // END namespace GMlib

// Include PHermiteSurface class function implementations
#include "gmPHermiteSurface.c"


#endif // __gmPHERMITESURFACE_H__