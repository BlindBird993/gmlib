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

    init();
  }

  template <typename T>
  void
  Dwt<T>::init() {

    CL::OpenCL *cli =  CL::OpenCL::getInstance();

    cl::Program::Sources sources;

    const std::string dwt1_nd_src (
      "__kernel void \n"
      "dwt_nd( __global const float* src, __global float* dst, unsigned int src_offset, unsigned int dst_offset, float2 filter, unsigned int r, unsigned int p ) \n"
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
    sources.push_back( std::make_pair( dwt1_nd_src.c_str(), dwt1_nd_src.length() - 1 ) );

    const std::string idwt1_nd_src = std::string(
      "__kernel void \n"
      "idwt_nd( __global const float* src, __global float* dst, unsigned int src_offset, unsigned int dst_offset, unsigned int src_h_offset, float2 lp, float2 hp, unsigned int r, unsigned int p ) \n"
      "{ \n"        "  const int idx = get_global_id(0); \n"
      "  const int a = pow( (float)(r/2), (float)(p-1) ); \n"
      "  const int i0 = idx + (int)( idx / a ) * a; \n"
      "  const int i1 = i0 + a; \n"
      "\n"
      "  dst[dst_offset+i0] = lp.s0 * src[src_offset+idx] + hp.s1 * src[src_offset+src_h_offset+idx]; \n"
      "  dst[dst_offset+i1] = lp.s1 * src[src_offset+idx] + hp.s0 * src[src_offset+src_h_offset+idx]; \n"
      "} \n"
      "\n"
      );
    sources.push_back( std::make_pair(idwt1_nd_src.c_str(),idwt1_nd_src.length()) );

    std::cout << "Building dwt cl kernels: " << std::endl;
    _program = CL::Program( sources );
    _program.build( cli->getDevices() ) ;


  }

  template <typename T>
  void
  Dwt<T>::swapBuffers() {


  }

  template <typename T>
  void
  Dwt<T>::load(const CL::Buffer &signal, int resolution) {

//    _queue.en
  }

} // END namespace Wavelet
} // END namespace GMlib
