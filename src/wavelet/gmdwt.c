
//---- REMOVE
#include "gmdwt.h"
//---- remove

#include "gmfilter.h"

//- GMlib includes
#include <opencl/gmopencl.h>

#include <string>


using namespace GMlib;
using namespace GMlib::CL;
using namespace GMlib::Wavelet;

template<typename T>
Dwt<T>::Dwt(int dim) :
  _dimension(dim) {
  _filters.setDim(dim);
  init();
}

template<typename T>
void
Dwt<T>::setFilter(int dim, Filter<T> *filter) {
  _filters[dim] = filter;
}

template<typename T>
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

  OpenCL* cl_instance = OpenCL::getInstance();


}
