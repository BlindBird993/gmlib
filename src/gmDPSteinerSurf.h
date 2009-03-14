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



/*! \file gmDPSteinerSurf.h
 *  \brief Interface for the DPSteinerSurf class.
 *
 *  \date   2008-09-22
 */

#ifndef __gmDPSTEINERSURF_H__
#define __gmDPSTEINERSURF_H__



#include <string>

#include "gmDSurf.h"
#include "gmPSteinerSurf.h"


namespace GMlib {

  template <typename T>
  class DPSteinerSurf : public DSurf<T> {
  public:
    DPSteinerSurf( T radius = T(20) );
    DPSteinerSurf( const DPSteinerSurf<T>& dpss );
    DPSteinerSurf( const PSteinerSurf<T,3>& dpss );
    virtual ~DPSteinerSurf();

    virtual PSteinerSurf<T,3>*    getPSteinerSurf();

  protected:
    PSteinerSurf<T,3>             *_l_ref;

    std::string                   getIdentity() const;
    virtual void                  init();
  };


} // END namespace GMlib

// Include DPSteinerSurf class function implementations
#include "gmDPSteinerSurf.c"



#endif // __gmDPSTEINERSURF_H__


