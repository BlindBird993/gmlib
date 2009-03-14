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



/*! \file gmParametrics.h
 *
 *  Interface for the Parametrics class.
 *
 *  \date   2008-11-24
 */

#ifndef __gmPARAMETRICS_H__
#define __gmPARAMETRICS_H__

// STL
#include <iostream>

// GMlib
#include "gmAffineSpace.h"

namespace GMlib {



  enum GM_RESAMPLE_MODE {
    GM_RESAMPLE_INLINE,
    GM_RESAMPLE_PREEVAL
  };

  enum GM_DERIVATION_METHOD {
    GM_DERIVATION_EXPLICIT,
    GM_DERIVATION_DD
  };




  template <typename T, int n>
  class Parametrics : public AffineSpace<T,n> {
  public:
    Parametrics();
    Parametrics( const Parametrics<T,n>& copy );

    std::string             getIdentity() const;
    void                    setDerivationMethod( GM_DERIVATION_METHOD method );

  protected:
    GM_DERIVATION_METHOD    _dm;
  };

}

// Include Function Implementations
#include "gmParametrics.c"

#endif // __gmPARAMETRICS_H__

