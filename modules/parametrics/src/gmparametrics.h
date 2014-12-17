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



/*! \file gmparametrics.h
 *
 *  Interface for the Parametrics class.
 */

#ifndef __gmPARAMETRICS_H__
#define __gmPARAMETRICS_H__




// gmlib
#include <core/containers/gmarray.h>
#include <scene/gmsceneobject.h>
#include <scene/utils/gmmaterial.h>

// stl
#include <string>




namespace GMlib {


  enum GM_PARAMETRICS {
    GM_POINT = 0,
    GM_CURVE = 1,
    GM_SURFACE = 2,
    GM_VOLUME = 3,
    GM_FLOW = 4
  };

  enum GM_RESAMPLE_MODE {
    GM_RESAMPLE_INLINE,
    GM_RESAMPLE_PREEVAL
  };

  enum GM_DERIVATION_METHOD {
    GM_DERIVATION_EXPLICIT,
    GM_DERIVATION_DD
  };


  /*!
   *
   *  \tparam T Template type parameter
   *  \tparam m Manifold dimension \see GM_PARAMETRICS
   *  \tparam n Manifold embedding dimension
   */
  template <typename T, int m, int n>
  class Parametrics : public SceneObject {
  public:
    Parametrics();
    Parametrics( const Parametrics<T,m,n>& copy );
    ~Parametrics();

    void                                  rotate(Angle a, const Vector<T,n>& rot_axel);
    void                                  rotate(Angle a, const Point<T,n>& p,const UnitVector<T,n>& d);
    void                                  rotateParent(Angle a, const Vector<T,n>& rot_axel);
    void                                  rotateParent(Angle a, const Point<T,n>& p,const UnitVector<T,n>& d);
    void                                  rotateGlobal(Angle a, const Vector<T,n>& rot_axel);
    void                                  rotateGlobal(Angle a, const Point<T,n>& p,const UnitVector<T,n>& d);
    void                                  setDerivationMethod( GM_DERIVATION_METHOD method );
    void                                  translate(const Vector<T,n>& trans_vector);
    void                                  translateParent(const Vector<T,n>& trans_vector);
    void                                  translateGlobal(const Vector<T,n>& trans_vector);

  protected:
    GM_DERIVATION_METHOD                  _dm;

    SqMatrix<T,n>                         _A;   //! Scale, skew and rotate
    Vector<T,n>                           _b;   //! Translate

  private:
    void                                  _initSoType();


  }; // END class Parametrics
}

// Include Paramterics class function implementations
#include "gmparametrics.c"



#endif // __gmPARAMETRICS_H__
