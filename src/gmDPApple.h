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



/*! \file gmDPApple.h
 *
 *  Interface for the gmDPApple class.
 *
 *  \date   2008-09-07
 */

#ifndef __gmDPAPPLE_H__
#define __gmDPAPPLE_H__



#include <string>
using std::string;

#include "gmDSurf.h"
#include "gmPApple.h"


namespace GMlib {

  template <typename T>
  class DPApple : public DSurf<T> {
  public:
    DPApple( T radius = T(1) );
    DPApple( const DPApple<T>& papple );
    DPApple( const PApple<T,3>& papple );
    virtual ~DPApple();

    virtual PApple<T,3>*    getPApple();


  protected:
    PApple<T,3>             *_l_ref;

    string                  getIdentity() const;
    virtual void            init();
  };


} // END namespace GMlib

// Include DPApple class function implementations
#include "gmDPApple.c"



#endif // __gmDPAPPLE_H__

