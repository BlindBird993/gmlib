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

//! \file gmcommandqueue.h


#ifndef __GM_OPENCL_GMCOMMANDQUEUE_H__
#define __GM_OPENCL_GMCOMMANDQUEUE_H__


// local
#include "gmopencl.h"

// stl
#include <string>

namespace GMlib {

namespace CL {


  class CommandQueue : public CLObject<cl::CommandQueue> {
  public:
    CommandQueue();
    CommandQueue( const cl::Device& device,
                  cl_command_queue_properties properties = 0);
    CommandQueue( const std::string& name );
    CommandQueue( const std::string& name, const cl::Device& device,
                  cl_command_queue_properties properties = 0);

  }; // END class CommandQueue



} // END namespace CL

} // END namespace GMlib


#endif // __GM_OPENCL_GMCOMMANDQUEUE_H__
