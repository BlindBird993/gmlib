
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

//! \file gmeventbase.h


#ifndef __GM_OPENCL_GMEVENTBASE_H__
#define __GM_OPENCL_GMEVENTBASE_H__


// local
#include "gmopencl.h"

// stl
#include <string>

namespace GMlib {

namespace CL {

  template <typename T,OpenCL::EventInfo::TYPE T_type>
  class EventBase : public CLObject<T>, GMutils::DerivedFrom<T,cl::Event> {
  public:
    EventBase();
    EventBase( const std::string& name );

  }; // END class Memory

  template <typename T,OpenCL::EventInfo::TYPE T_type>
  EventBase<T,T_type>::EventBase() {}

  template <typename T,OpenCL::EventInfo::TYPE T_type>
  EventBase<T,T_type>::EventBase( const std::string& name )
    : CLObject<T>(name, OpenCL::getInstance()->getEvent<T,T_type>(name)) {}


} // END namespace CL

} // END namespace GMlib


#endif // __GM_OPENCL_GMEVENTBASE_H__
