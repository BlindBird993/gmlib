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
  Dwt<T>::Dwt() : _resolution(0), _b_in(BUFFER_01), _b_out(BUFFER_02) {

    init();
  }

  template <typename T>
  void Dwt<T>::deCompose(const Filter<T>* filter,
                         unsigned int dim, unsigned int res,
                         int lvls, int s_lvl) {







  }

  template <typename T>
  void Dwt<T>::reConstruct(const Filter<T>* filter,
                           unsigned int dim, unsigned int res,
                           int lvls, int s_lvl) {

  }

  template <typename T>
  void
  Dwt<T>::init() {

    CL::OpenCL *cli =  CL::OpenCL::getInstance();

    cl::Program::Sources sources;

    /*
      __kernel void
      dwt_nd( __global const float* src,
                       __global float* dst,
                       unsigned int src_offset,
                       unsigned int dst_offset,
                       float2 filter, unsigned int r, unsigned int p )
      {
        const int idx = get_global_id(0);
        const int a = pow( (float)(r/2), (float)(p-1) );
        const int i0 = idx + (int)( idx / a ) * a;
        const int i1 = i0 + a;

        dst[dst_offset + idx] = filter.s1 * src[src_offset+i1] + filter.s0 * src[src_offset+i0];
      }
      */
    const std::string dwt1_nd_src (
      "__kernel void \n"
      "dwt_nd( __global const float* src, \n"
      "        __global float* dst, \n"
      "        unsigned int src_offset, \n"
      "        unsigned int dst_offset, \n"
      "        __global const float* hp, __global const float* lp, unsigned int filter_size, \n"
      "        unsigned int res, unsigned int pass ) \n"
      "{ \n"
      "  const int idx = get_global_id(0); \n"
      "\n"
      "} \n"
      "\n"
      );
    sources.push_back( std::make_pair( dwt1_nd_src.c_str(), dwt1_nd_src.length() - 1 ) );










    /*
      __kernel void
      idwt_nd( __global const float* src,
               __global float* dst,
               unsigned int src_offset,
               unsigned int dst_offset,
               unsigned int src_h_offset,
               float2 lp, float2 hp, unsigned int r, unsigned int p )
      {
        const int idx = get_global_id(0);
        const int a = pow( (float)(r/2), (float)(p-1) );
        const int i0 = idx + (int)( idx / a ) * a;
        const int i1 = i0 + a;

        dst[dst_offset+i0] = lp.s0 * src[src_offset+idx] + hp.s1 * src[src_offset+src_h_offset+idx];
        dst[dst_offset+i1] = lp.s1 * src[src_offset+idx] + hp.s0 * src[src_offset+src_h_offset+idx];
      }
      */
    const std::string idwt1_nd_src = std::string(
      "__kernel void \n"
      "idwt_nd( __global const float* src, \n"
      "         __global float* dst, \n"
      "         unsigned int src_offset, \n"
      "         unsigned int dst_offset, \n"
      "         unsigned int src_h_offset, \n"
      "         float2 lp, float2 hp, unsigned int r, unsigned int p ) \n"
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

    cl_int error;
    error = _program.build( cli->getDevices() ) ;
    std::cout << "  Compiling: " << error << std::endl;
    if( error != CL_SUCCESS ) {

      size_t length;
      char buffer[2048];
      clGetProgramBuildInfo( _program()(), cli->getDevices()[0](),CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &length);

      std::cout << "  * Build log [BEGIN]: " << std::endl;
      std::cout << "-------------------------------------" << std::endl;
      std::cout << buffer << std::endl;
      std::cout << "-------------------------------------" << std::endl;
      std::cout << "  * Build log [BEGIN]: " << std::endl;
    }


    _queue = CL::CommandQueue( cli->getDevices()[0] );

  }

  template <typename T>
  void
  Dwt<T>::initBuffers(int length) {


  //TODO: Find "optimal" buffer-size, aka: work size. Tune to "warp-size"


    _buffers[_b_in] = CL::Buffer( CL_MEM_READ_WRITE, length * sizeof(T) );
    _buffers[_b_out] = CL::Buffer( CL_MEM_READ_WRITE, length * sizeof(T) );
  }

  template <typename T>
  void
  Dwt<T>::swapBuffers() {

    BUFFER tmp = _b_out;
    _b_out = _b_in;
    _b_in = tmp;
  }

  template <typename T>
  const CL::Buffer&
  Dwt<T>::getNativeInBuffer() const {

    return _buffers[_b_in];
  }

  template <typename T>
  const CL::Buffer&
  Dwt<T>::getNativeOutBuffer() const {

    return _buffers[_b_out];
  }


  template <typename T>
  void
  Dwt<T>::writeToInBuffer( const T* signal, unsigned long int length ) {

    initBuffers(length);
    CL::Buffer &bi = _buffers[_b_in];
    _queue().enqueueWriteBuffer( bi(), CL_TRUE, 0, length * sizeof(T), signal, 0x0, &_event );
    _event.wait();
  }

  template <typename T>
  void
  Dwt<T>::writeToInBuffer( const DVector<T>& signal ) {

    initBuffers(signal.getDim());
    CL::Buffer &bi = _buffers[_b_in];
    _queue.enqueueWriteBuffer( bi, CL_TRUE, signal, 0x0, &_event );
    _event.wait();
  }

  template <typename T>
  void
  Dwt<T>::writeToInBuffer( const DMatrix<T>& signal ) {

    initBuffers(signal.getDim1()*signal.getDim2());
    CL::Buffer &bi = _buffers[_b_in];
    cl_int error;
    error = _queue.enqueueWriteBuffer( bi, CL_TRUE, signal, 0x0, &_event );
    _event.wait();
  }

  template <typename T>
  void
  Dwt<T>::writeToInBuffer( const CL::Buffer& signal, unsigned long int length ) {

    initBuffers(length);
    CL::Buffer &bi = _buffers[_b_in];
    _queue.enqueueCopyBuffer( signal, bi, 0, 0, length * sizeof(T), 0x0, &_event );
    _event.wait();
  }

  template <typename T>
  void
  Dwt<T>::readFromOutBuffer( T* signal, unsigned long int length ) const {

    CL::Buffer &bo = _buffers[_b_out];
    _queue().enqueueReadBuffer( bo(), CL_TRUE, 0, length * sizeof(T), signal, 0x0, &_event );
    _event.wait();
  }

  template <typename T>
  void
  Dwt<T>::readFromOutBuffer( DVector<T>& signal ) const {


    CL::Buffer &bo = _buffers[_b_out];
    _queue.enqueueReadBuffer( bo, CL_TRUE, signal, 0x0, &_event );
    _event.wait();
  }

  template <typename T>
  void
  Dwt<T>::readFromOutBuffer( DMatrix<T>& signal ) const {

    const CL::Buffer &bo = _buffers[_b_out];
    cl_int error;
    error = _queue.enqueueReadBuffer( bo, CL_TRUE, signal );
    std::cout << "  Reading DMatrix data from buffer: " << error << std::endl;;
  }

  template <typename T>
  void
  Dwt<T>::readFromOutBuffer( CL::Buffer& signal, unsigned long int length) const {

    CL::Buffer &bo = _buffers[_b_out];
    _queue.enqueueCopyBuffer( bo, signal, 0, 0, length * sizeof(T), 0x0, &_event );
    _event.wait();
  }




} // END namespace Wavelet
} // END namespace GMlib
