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

//// gmlib
#include <opencl/gmopencl.h>
#include <opencl/gmkernel.h>

// stl
#include <string>
#include <cassert>

namespace GMlib {
namespace Wavelet {

  template <typename T>
  Dwt<T>::Dwt() : _resolution(0), _bA(BUFFER_01), _bB(BUFFER_02) {

    init();
  }

  template <typename T>
  void Dwt<T>::deCompose(const Filter<T>* filter,
                         unsigned int dim, unsigned int res,
                         int lvls, int s_lvl) {

    assert(filter);

    cl_int                  err;

    const unsigned int s_size  = std::pow(res, dim);

    int filter_len[2];
    filter_len[FILTER_LP] = filter->getDecomposeLP().getDim();
    filter_len[FILTER_HP] = filter->getDecomposeHP().getDim();

    CL::Buffer filters[2];
    filters[FILTER_LP] = CL::Buffer( CL_MEM_READ_ONLY, filter_len[FILTER_LP] * sizeof(T) );
    filters[FILTER_HP] = CL::Buffer( CL_MEM_READ_ONLY, filter_len[FILTER_HP] * sizeof(T) );

    err = _queue.enqueueWriteBuffer( filters[FILTER_LP], CL_TRUE, filter->getDecomposeLP(), 0x0, &_event );
    _event.wait();
    std::cout << "Load LP filter status: " << err << std::endl;

    err = _queue.enqueueWriteBuffer( filters[FILTER_HP], CL_TRUE, filter->getDecomposeHP(), 0x0, &_event );
    _event.wait();
    std::cout << "Load HP filter status: " << err << std::endl;

    FILTER f = FILTER_LP;

    ////////////////////
    // Execute kernel(s)

    // tmp vars
    unsigned int tmp_s_size = s_size;


    // levels
    for( unsigned int i = 0; i < lvls; i++ ) {

      // Passes
      for( unsigned int j = 0; j < dim; j++ ) {

        // Filters
        for( int k = 0; k < std::pow( 2, float(j+1) ); k++ ) {



          // Common kernel parameters
          cl_int arg_err;
          arg_err = _dwt_k.setArg(   0, _buffers[_bA] );                // Source signal buffer
          std::cout << "Kernel arg 0 status: " << arg_err << std::endl;

          arg_err = _dwt_k.setArg(   1, _buffers[_bB] );               // Dwt signal buffer
          std::cout << "Kernel arg 1 status: " << arg_err << std::endl;

          arg_err = _dwt_k().setArg( 2, (unsigned int)(int(k/2) * tmp_s_size) );       // Source buffer offset
          std::cout << "Kernel arg 2 status: " << arg_err << std::endl;

          arg_err = _dwt_k().setArg( 3, (unsigned int)(k * tmp_s_size / 2) );          // Dwt signal buffer offset
          std::cout << "Kernel arg 3 status: " << arg_err << std::endl;

          arg_err = _dwt_k.setArg( 4, filters[f] );              // Filter
          std::cout << "Kernel arg 4 status: " << arg_err << std::endl;

          arg_err = _dwt_k().setArg( 5, (unsigned int)(filter_len[f]) );
          std::cout << "Kernel arg 5 status: " << arg_err << std::endl;

          arg_err = _dwt_k().setArg( 6, (unsigned int)(res/std::pow( 2, float(i) ) ) );   // Signal resolution (size)
          std::cout << "Kernel arg 6 status: " << arg_err << std::endl;

          arg_err = _dwt_k().setArg( 7, (unsigned int)(j+1) );                         // Pass dimension (1)
          std::cout << "Kernel arg 7 status: " << arg_err << std::endl;


          // Enqueue kernel for execution
          err = _queue.enqueueNDRangeKernel( _dwt_k,
                                             cl::NullRange,
                                             cl::NDRange(tmp_s_size/2),
                                             cl::NDRange(64),
                                             0x0, &_event );
          _event.wait();   // Wait for kernel

          std::cout << "Running kernel status: " << err << std::endl;

          f = (f == FILTER_LP ? FILTER_HP : FILTER_LP );
//          f = (f+ 1) % 2;
        }

        tmp_s_size /= 2;

        // Swap "working" buffers
        swapBuffers();
      }
    }


    swapBuffers();


  }

  template <typename T>
  void Dwt<T>::reConstruct(const Filter<T>* filter,
                           unsigned int dim, unsigned int res,
                           int lvls, int s_lvl) {

    assert(filter);

    cl_int                  err;

    const unsigned int s_size  = std::pow(res,dim);


    int lp_len, hp_len;
    lp_len = filter->getReconstructLP().getDim();
    hp_len = filter->getReconstructHP().getDim();

    CL::Buffer lp, hp;
    lp = CL::Buffer( CL_MEM_READ_ONLY, lp_len * sizeof(T) );
    err = _queue.enqueueWriteBuffer( lp, CL_TRUE, filter->getReconstructLP(), 0x0, &_event );
    _event.wait();
    std::cout << "Load LP filter status: " << err << std::endl;

    hp = CL::Buffer( CL_MEM_READ_ONLY, hp_len * sizeof(T) );
    err = _queue.enqueueWriteBuffer( hp, CL_TRUE, filter->getReconstructHP(), 0x0, &_event );
    _event.wait();
    std::cout << "Load HP filter status: " << err << std::endl;





    ////////////////////
    // Execute kernel(s)

    // tmp vars
    unsigned int tmp_s_size = s_size / ( 2<<(lvls*dim-2) );

    // levels
    for( int i = lvls-1; i >= 0; i-- ) {

      // Passes
      for( int j = dim-1; j >= 0; j-- ) {

        // Synthesising
        for( int k = std::pow( 2, float(j-1) ); k >= 0; k-- ) {

          const unsigned int io_o = k * tmp_s_size;   // I/O Buffer offset


          // Common kernel parameters
          cl_int arg_err;
          arg_err = _idwt_k.setArg(    0, _buffers[_bA] );  // Source signal buffer
          std::cout << "Kernel arg 0 status: " << arg_err << std::endl;

          arg_err = _idwt_k.setArg(    1, _buffers[_bB] );  // Dwt signal buffer
          std::cout << "Kernel arg 1 status: " << arg_err << std::endl;

          arg_err = _idwt_k().setArg(  2, (unsigned int)(io_o)  );  // Source buffer offset
          std::cout << "Kernel arg 2 status: " << arg_err << std::endl;

          arg_err = _idwt_k().setArg(  3, (unsigned int)(io_o)  );  // Dwt signal buffer offset
          std::cout << "Kernel arg 3 status: " << arg_err << std::endl;

          arg_err = _idwt_k().setArg(  4, (unsigned int)(tmp_s_size/2)  );  // Dwt signal buffer offset
          std::cout << "Kernel arg 4 status: " << arg_err << std::endl;

          arg_err = _idwt_k.setArg(    5, lp);   // Filter
          std::cout << "Kernel arg 5 status: " << arg_err << std::endl;

          arg_err = _idwt_k().setArg(  6, (unsigned int)(lp_len)  );   // Filter LEN
          std::cout << "Kernel arg 6 status: " << arg_err << std::endl;

          arg_err = _idwt_k.setArg(    7, hp );   // Filter
          std::cout << "Kernel arg 7 status: " << arg_err << std::endl;

          arg_err = _idwt_k().setArg(  8, (unsigned int)(hp_len)  );   // Filter LEN
          std::cout << "Kernel arg 8 status: " << arg_err << std::endl;

          arg_err = _idwt_k().setArg(  9, (unsigned int)(res/std::pow( 2, float(i) ))  );    // Signal resolution (size)
          std::cout << "Kernel arg 9 status: " << arg_err << std::endl;

          arg_err = _idwt_k().setArg( 10, (unsigned int)(j+1) );    // Pass dimension (1)
          std::cout << "Kernel arg 10 status: " << arg_err << std::endl;


          // Enqueue kernel for execution
          _queue.enqueueNDRangeKernel(
                _idwt_k,
                cl::NullRange,
                cl::NDRange(tmp_s_size/2),
                cl::NDRange(64),
                0x0,
                &_event
                );
          _event.wait();   // Wait for kernel

          std::cout << "Running kernel status: " << err << std::endl;
        }

        tmp_s_size *= 2;

        // Swap "working" buffers
        swapBuffers();
      }
    }

    swapBuffers();

  }

  template <typename T>
  void
  Dwt<T>::init() {

    CL::OpenCL *cli =  CL::OpenCL::getInstance();

    cl::Program::Sources sources;

    const std::string dwt1_nd_src (
      "__kernel void \n"
      "dwt_nd( __global const float* src, \n"
      "        __global float* dst, \n"
      "        unsigned int src_offset, \n"
      "        unsigned int dst_offset, \n"
      "        __global const float* filter, unsigned int filter_len, \n"
      "        unsigned int r, unsigned int p \n"
      "        ) \n"
      "{ \n"
      "  const int idx = get_global_id(0); \n"
      "  const int a = pow( (float)(r/2), (float)(p-1) ); \n"
      "  const int i0 = idx + (int)( idx / a ) * a; \n"
      "  const int i1 = i0 + a; \n"
      "\n"
      "  dst[dst_offset + idx] = filter[1] * src[src_offset+i1] + filter[0] * src[src_offset+i0]; \n"
      "\n"
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
      "        __global const float* lp, unsigned int lp_len, \n"
      "        __global const float* hp, unsigned int hp_len, \n"
      "        unsigned int r, unsigned int p ) \n"
      "{ \n"        "  const int idx = get_global_id(0); \n"
      "  const int a = pow( (float)(r/2), (float)(p-1) ); \n"
      "  const int i0 = idx + (int)( idx / a ) * a; \n"
      "  const int i1 = i0 + a; \n"
      "\n"
      "  dst[dst_offset+i0] = lp[0] * src[src_offset+idx] + hp[1] * src[src_offset+src_h_offset+idx]; \n"
      "  dst[dst_offset+i1] = lp[1] * src[src_offset+idx] + hp[0] * src[src_offset+src_h_offset+idx]; \n"
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

    _dwt_k= _program.getKernel("dwt_nd");
    _idwt_k = _program.getKernel("idwt_nd");

  }

  template <typename T>
  void
  Dwt<T>::initBuffers(int length) {


  //TODO: Find "optimal" buffer-size, aka: work size. Tune to "warp-size"


    _buffers[_bA] = CL::Buffer( CL_MEM_READ_WRITE, length * sizeof(T) );
    _buffers[_bB] = CL::Buffer( CL_MEM_READ_WRITE, length * sizeof(T) );
  }

  template <typename T>
  void
  Dwt<T>::swapBuffers() {

    BUFFER tmp = _bB;
    _bB = _bA;
    _bA = tmp;
  }

  template <typename T>
  const CL::Buffer&
  Dwt<T>::getNativeInBuffer() const {

    return _buffers[_bA];
  }

  template <typename T>
  const CL::Buffer&
  Dwt<T>::getNativeOutBuffer() const {

    return _buffers[_bB];
  }


  template <typename T>
  void
  Dwt<T>::writeToInBuffer( const T* signal, unsigned long int length ) {

    initBuffers(length);
    _queue().enqueueWriteBuffer( _buffers[_bA](), CL_TRUE, 0, length * sizeof(T), signal, 0x0, &_event );
    _event.wait();
  }

  template <typename T>
  void
  Dwt<T>::writeToInBuffer( const DVector<T>& signal ) {

    initBuffers(signal.getDim());
    _queue.enqueueWriteBuffer( _buffers[_bA], CL_TRUE, signal, 0x0, &_event );
    _event.wait();
  }

  template <typename T>
  void
  Dwt<T>::writeToInBuffer( const DMatrix<T>& signal ) {

    initBuffers(signal.getDim1()*signal.getDim2());
    cl_int error;
    error = _queue.enqueueWriteBuffer( _buffers[_bA], CL_TRUE, signal, 0x0, &_event );
    _event.wait();
  }

  template <typename T>
  void
  Dwt<T>::writeToInBuffer( const CL::Buffer& signal, unsigned long int length ) {

    initBuffers(length);
    _queue.enqueueCopyBuffer( signal, _buffers[_bA], 0, 0, length * sizeof(T), 0x0, &_event );
    _event.wait();
  }

  template <typename T>
  void
  Dwt<T>::readFromOutBuffer( T* signal, unsigned long int length ) const {

    CL::Buffer &bo = _buffers[_bB];
    _queue().enqueueReadBuffer( bo(), CL_TRUE, 0, length * sizeof(T), signal, 0x0, &_event );
    _event.wait();
  }

  template <typename T>
  void
  Dwt<T>::readFromOutBuffer( DVector<T>& signal ) const {


    _queue.enqueueReadBuffer( _buffers[_bB], CL_TRUE, signal, 0x0, &_event );
    _event.wait();
  }

  template <typename T>
  void
  Dwt<T>::readFromOutBuffer( DMatrix<T>& signal ) const {

    cl_int error;
    error = _queue.enqueueReadBuffer( _buffers[_bB], CL_TRUE, signal );
    std::cout << "  Reading DMatrix data from buffer: " << error << std::endl;;
  }

  template <typename T>
  void
  Dwt<T>::readFromOutBuffer( CL::Buffer& signal, unsigned long int length) const {

    _queue.enqueueCopyBuffer( _buffers[_bB], signal, 0, 0, length * sizeof(T), 0x0, &_event );
    _event.wait();
  }




} // END namespace Wavelet
} // END namespace GMlib
