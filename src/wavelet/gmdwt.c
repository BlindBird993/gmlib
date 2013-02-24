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
#include <cmath>

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

//    ////// HACK
//    CL::OpenCL *cli =  CL::OpenCL::getInstance();
//    _queue = CL::CommandQueue( cli->getDevices()[0] );
//    ////// HACK

    cl_int                  err;

    const unsigned int s_size  = std::pow(res, dim);

    int lp_len, hp_len;
    lp_len = filter->getDecomposeLP().getDim();
    hp_len = filter->getDecomposeHP().getDim();

    std::cout << "deComp: LP Filter:" << filter->getDecomposeLP() << std::endl;
    std::cout << "deComp: HP Filter:" << filter->getDecomposeHP() << std::endl;

    CL::Buffer lp, hp;
    lp = CL::Buffer( CL_MEM_READ_ONLY, lp_len * sizeof(T) );
    hp = CL::Buffer( CL_MEM_READ_ONLY, hp_len * sizeof(T) );

    err = _queue.enqueueWriteBuffer( lp, CL_TRUE, filter->getDecomposeLP(), 0x0, &_event );
    _event.wait();
    std::cout << "Load LP filter status: " << err << std::endl;

    err = _queue.enqueueWriteBuffer( hp, CL_TRUE, filter->getDecomposeHP(), 0x0, &_event );
    _event.wait();
    std::cout << "Load HP filter status: " << err << std::endl;

//    FILTER f = FILTER_LP;

    ////////////////////
    // Execute kernel(s)

    // tmp vars
    unsigned int tmp_s_size = s_size;


    // levels
    for( unsigned int i = 0; i < lvls; ++i ) {

      // Passes
      for( unsigned int j = 0; j < dim; ++j ) {

        // Filter passes
        for( int k = 0; k < j + 1; ++k ) {

          // Compute kernel parameters
          const unsigned int vsrc_offset = static_cast<unsigned int>( k * tmp_s_size );
          const unsigned int vsrc_size   = static_cast<unsigned int>( tmp_s_size );

          const unsigned int vdst_offset = static_cast<unsigned int>( k * tmp_s_size );
          const unsigned int vdst_size   = static_cast<unsigned int>( tmp_s_size / std::pow( 2, dim-1 ) );

          const int r = res/std::pow( 2, i );
          const int p = dim - j - 1;
          const unsigned int a = static_cast<unsigned int>( std::pow( r, p ) );

          // Set kernel parameters
          cl_int arg_err;
          arg_err = _dwt_k.setArg(    0, _buffers[_bA] );         // src buffer
          arg_err = _dwt_k.setArg(    1, _buffers[_bB] );         // dst buffer
          arg_err = _dwt_k().setArg(  2, vsrc_offset );           // virtual source buffer offset
          arg_err = _dwt_k().setArg(  3, vsrc_size );             // virtual source buffer size
          arg_err = _dwt_k().setArg(  4, vdst_offset );           // virtual destination buffer offset
          arg_err = _dwt_k().setArg(  5, vdst_size );             // virtual destination buffer size
          arg_err = _dwt_k.setArg(    6, lp );    // LP filter
          arg_err = _dwt_k().setArg(  7, lp_len );
          arg_err = _dwt_k.setArg(    8, hp );    // HP filter
          arg_err = _dwt_k().setArg(  9, lp_len );
          arg_err = _dwt_k().setArg( 10, a );

          // Enqueue kernel for execution
          err = _queue.enqueueNDRangeKernel( _dwt_k,
                                             cl::NullRange,
                                             cl::NDRange(tmp_s_size/2),
                                             cl::NDRange(16),
                                             0x0, &_event );
          _event.wait();   // Wait for kernel

          std::cout << "Running kernel status: " << err << std::endl;

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

    const unsigned int d_size  = std::pow(res,dim);


    int lp_len, hp_len;
    lp_len = filter->getReconstructLP().getDim();
    hp_len = filter->getReconstructHP().getDim();

    std::cout << "reConst: LP Filter:" << filter->getReconstructLP() << std::endl;
    std::cout << "reConst: HP Filter:" << filter->getReconstructHP() << std::endl;

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
    unsigned int tmp_d_size = d_size / ( 2<<(lvls*dim-2) );

    // levels
    for( int i = lvls-1; i >= 0; i-- ) {
      std::cout << "---------- LVL: " << i << std::endl;

      // Passes
//      for( int j = 0; j < dim; ++j ) {
      for( int j = dim-1; j >= /*dim-1*/0; j-- ) {
        std::cout << "----------   PASS: " << j << std::endl;

        // Synthesising
        for( int k = 0; k < std::pow( 2, j ); ++k ) {
//        for( int k = std::pow( 2, float(j-1) ); k >= 0; k-- ) {
          std::cout << "----------     SYNTH: " << k << std::endl;

          std::cout << "  i: " << i << ", j: " << j << ", k: " << k << std::endl;



          // Compute kernel parameters
          const unsigned int vdst_offset = static_cast<unsigned int>( tmp_d_size * k );
          const unsigned int vdst_size   = static_cast<unsigned int>( tmp_d_size );

          const unsigned int vsrc_offset = static_cast<unsigned int>( tmp_d_size * k);
          const unsigned int vsrc_size   = static_cast<unsigned int>( tmp_d_size / std::pow( 2, dim-1) );

          const int r = res/std::pow( 2, i );
          const int p = dim - j - 1;
          const unsigned int a = static_cast<unsigned int>( std::pow( r, p ) );

          std::cout << "  vsrc offset:  " << vsrc_offset << ", vdst offset:  " << vdst_offset << std::endl;
          std::cout << "  vsrc size:    " << vsrc_size   << ", vdst size:    " << vdst_size << std::endl;
          std::cout << "  ---" << std::endl;
          std::cout << "  r:            " << r << std::endl;
          std::cout << "  p:            " << p << std::endl;
          std::cout << "  a:            " << a << std::endl;







          // Set kernel parameters
          cl_int arg_err;
          arg_err = _idwt_k.setArg(    0, _buffers[_bA] );         // src buffer
          arg_err = _idwt_k.setArg(    1, _buffers[_bB] );         // dst buffer
          arg_err = _idwt_k().setArg(  2, vsrc_offset );           // virtual source buffer offset
          arg_err = _idwt_k().setArg(  3, vsrc_size );             // virtual source buffer size
          arg_err = _idwt_k().setArg(  4, vdst_offset );           // virtual destination buffer offset
          arg_err = _idwt_k().setArg(  5, vdst_size );             // virtual destination buffer size
          arg_err = _idwt_k.setArg(    6, lp );    // LP filter
          arg_err = _idwt_k().setArg(  7, lp_len );
          arg_err = _idwt_k.setArg(    8, hp );    // HP filter
          arg_err = _idwt_k().setArg(  9, lp_len );
          arg_err = _idwt_k().setArg( 10, a );

          // Enqueue kernel for execution
          err = _queue.enqueueNDRangeKernel( _idwt_k,
                                             cl::NullRange,
                                             cl::NDRange(tmp_d_size/2),
                                             cl::NDRange(16),
                                             0x0, &_event );
          _event.wait();   // Wait for kernel

          std::cout << "Running kernel status: " << err << std::endl;




//          const unsigned int io_o = k * tmp_s_size;   // I/O Buffer offset

//          unsigned int r = static_cast<unsigned int>( res/std::pow( 2, i ) );
//          unsigned int p = static_cast<unsigned int>( dim - j - 1 );
//          unsigned int a = static_cast<unsigned int>( std::pow( r, p ) );

//          // Common kernel parameters
//          cl_int arg_err;
//          arg_err = _idwt_k.setArg(    0, _buffers[_bA] );  // Source signal buffer
//          arg_err = _idwt_k.setArg(    1, _buffers[_bB] );  // Dwt signal buffer
//          arg_err = _idwt_k().setArg(  2, static_cast<unsigned int>(io_o)  );  // Source buffer offset
//          arg_err = _idwt_k().setArg(  3, static_cast<unsigned int>(io_o)  );  // Dwt signal buffer offset
//          arg_err = _idwt_k().setArg(  4, static_cast<unsigned int>(tmp_s_size/2)  );  // Dwt signal buffer offset
//          arg_err = _idwt_k.setArg(    5, lp);   // Filter
//          arg_err = _idwt_k().setArg(  6, static_cast<unsigned int>(lp_len)  );   // Filter LEN
//          arg_err = _idwt_k.setArg(    7, hp );   // Filter
//          arg_err = _idwt_k().setArg(  8, static_cast<unsigned int>(hp_len)  );   // Filter LEN
//          arg_err = _idwt_k().setArg(  9, static_cast<unsigned int>(res/std::pow( 2, float(i) ))  );    // Signal resolution (size)
//          arg_err = _idwt_k().setArg( 10, static_cast<unsigned int>(j) );    // Pass dimension (1)

//          // Enqueue kernel for execution
//          _queue.enqueueNDRangeKernel(
//                _idwt_k,
//                cl::NullRange,
//                cl::NDRange(tmp_s_size/2),
//                cl::NDRange(64),
//                0x0,
//                &_event
//                );
//          _event.wait();   // Wait for kernel

//          std::cout << "Running kernel status: " << err << std::endl;
        }

        tmp_d_size *= 2;

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

    _queue = CL::CommandQueue( cli->getDevices()[0] );

    cl::Program::Sources sources;

    const std::string dwt1_nd_src (
      "\n"
      "int \n"
      "cmpDstI( unsigned int offset ) { \n"
      "\n"
      "  return offset + get_global_id(0); \n"
      "} \n"
      "\n"
      "int \n"
      "cmpSrcI( unsigned int offset, unsigned int d, unsigned int a ) { \n"
      "\n"
      "  const int b = 2;  // diadic \n"
      "  const int g = get_global_id(0); \n"
      "  const int cycle = (int)( g / a ); \n"
      "\n"
      "  return offset + g + cycle * a * ( b - 1 ); \n"
      "} \n"
      "\n"
      "float \n"
      "computeConvol( __global const float* src, \n"
      "               unsigned int vsrc_offset, unsigned int vsrc_size, \n"
      "               __global const float* f, int f_len, \n"
      "               unsigned int a \n"
      "               ) { \n"
      "\n"
      "  const int base_idx = cmpSrcI( vsrc_offset, vsrc_size, a ); \n"
      "\n"
      "  float conv_val = 0; \n"
      "  for( int i = 0; i < f_len; ++i ) { \n"
      "\n"
      "    const int si = base_idx + a * i + (1-f_len%2) - (f_len/2); \n"
      "    if( si < ( vsrc_offset + vsrc_size ) ) \n"
      "      conv_val += f[i] * src[si]; \n"
      "  } \n"
      "\n"
      "  return conv_val; \n"
      "} \n"
      "\n"
      "void \n"
      "filter( __global const float* src, \n"
      "        __global float* dst, \n"
      "        unsigned int vsrc_offset, unsigned int vsrc_size, \n"
      "        unsigned int vdst_offset, unsigned int vdst_size, \n"
      "        __global const float* f, int f_len, \n"
      "        unsigned int alpha \n"
      ") { \n"
      "\n"
      "  const int out_idx = cmpDstI( vdst_offset ); \n"
      "  const int out_bnd = out_idx + vdst_size; \n"
      "  if( out_idx < out_bnd ) \n"
      "    dst[out_idx] = computeConvol( src, vsrc_offset, vsrc_size, f, f_len, alpha ) * sqrt((float)f_len); \n"
      "} \n"
      "\n"
      "__kernel void \n"
      "dwt_nd( __global const float* src, \n"
      "        __global float* dst, \n"
      "        unsigned int vsrc_offset, unsigned int vsrc_size, \n"
      "        unsigned int vdst_offset, unsigned int vdst_size, \n"
      "        __global const float* lp, int lp_len, \n"
      "        __global const float* hp, int hp_len, \n"
      "        unsigned int alpha \n"
      ") { \n"
      "\n"
      "  // LP \n"
      "  filter( src, dst, vsrc_offset, vsrc_size, vdst_offset, vdst_size, lp, lp_len, alpha ); \n"
      "\n"
      "  // HP \n"
      "  filter( src, dst, vsrc_offset, vsrc_size, vdst_offset + vdst_size, vdst_size*2, hp, hp_len, alpha ); \n"
      "} \n"
      "\n"
      );
//    sources.push_back( std::make_pair( dwt1_nd_src.c_str(), dwt1_nd_src.length() - 1 ) );



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
      "  const int a = pow( (float)(r/2), (float)(p) ); \n"
      "  const int i0 = idx + (int)( idx / a ) * a; \n"
      "  const int i1 = i0 + a; \n"
      "\n"
      "  dst[dst_offset+i0] = lp[0] * src[src_offset+idx] + hp[1] * src[src_offset+src_h_offset+idx]; \n"
      "  dst[dst_offset+i1] = lp[1] * src[src_offset+idx] + hp[0] * src[src_offset+src_h_offset+idx]; \n"
      "} \n"
      "\n"
      );
//    sources.push_back( std::make_pair(idwt1_nd_src.c_str(),idwt1_nd_src.length()) );

//    std::cout << "Building dwt cl kernels: " << std::endl;
//    _program = CL::Program( sources );

//    cl_int error;
//    error = _program.build( cli->getDevices() ) ;
//    std::cout << "  Compiling: " << error << std::endl;
//    if( error != CL_SUCCESS ) {

//      size_t length;
//      char buffer[2048];
//      clGetProgramBuildInfo( _program()(), cli->getDevices()[0](),CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &length);

//      std::cout << "  * Build log [BEGIN]: " << std::endl;
//      std::cout << "-------------------------------------" << std::endl;
//      std::cout << buffer << std::endl;
//      std::cout << "-------------------------------------" << std::endl;
//      std::cout << "  * Build log [BEGIN]: " << std::endl;
//    }



//    _dwt_k= _program.getKernel("dwt_nd");
//    _idwt_k = _program.getKernel("idwt_nd");

    setDwtSrc( dwt1_nd_src, idwt1_nd_src );
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

//    std::cout << "    ------------  SWAPPING BUFFERS" << std::endl;
    BUFFER tmp = _bB;
    _bB = _bA;
    _bA = tmp;
  }

  template <typename T>
  bool
  Dwt<T>::setDwtSrc(const std::string &dwt_src, const std::string &idwt_src) {

    CL::OpenCL *cli =  CL::OpenCL::getInstance();

    cl::Program::Sources sources;
    sources.push_back( std::make_pair(dwt_src.c_str(),dwt_src.length()) );
    sources.push_back( std::make_pair(idwt_src.c_str(),idwt_src.length()) );


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

      return false;
    }

    _dwt_k= _program.getKernel("dwt_nd");
    _idwt_k = _program.getKernel("idwt_nd");

    return true;
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
