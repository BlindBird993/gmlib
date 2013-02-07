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

#include "gmdwt.h"

// local
#include "gmfilter.h"

// gmlib
#include <opencl/gmopencl.h>

// stl
#include <string>

namespace GMlib {
namespace Wavelet {

  template <typename T>
  Dwt<T>::Dwt() : _resolution(0) {

//    _filters.setDim(dim);
    init();
  }

//  template<typename T>
//  void
//  Dwt<T>::setFilter(int dim, Filter<T> *filter) {
//    _filters[dim] = filter;
//  }

  template <typename T>
  void
  Dwt<T>::init() {
    const std::string dwt1_nd_src (
      "__kernel void \n"
      "dwt1_nd( __global float* src, __global float* dst, unsigned int src_offset, unsigned int dst_offset, float2 filter, unsigned int r, unsigned int p ) \n"
      "{ \n"
      "  const int idx = get_global_id(0); \n"
      "  const int a = pow( (float)(r/2), (float)(p-1) ); \n"
      "  const int i0 = idx + (int)( idx / a ) * a; \n"
      "  const int i1 = i0 + a; \n"
      "\n"
      "  dst[dst_offset + idx] = filter.s1 * src[src_offset+i1] + filter.s0 * src[src_offset+i0]; \n"
      "} \n"
      "\n"
      );
    cl::Program::Sources source( 1, std::make_pair( dwt1_nd_src.c_str(), dwt1_nd_src.length() - 1 ) );


    OpenCL* cl_instance = OpenCL::getInstance();


  }

  template <typename T>
  void
  Dwt<T>::swapBuffers() {


  }

  template <typename T>
  void
  Dwt::load(const CL::Buffer &signal, int resolution) {

    _queue.en
  }

} // END namespace Wavelet
} // END namespace GMlib
