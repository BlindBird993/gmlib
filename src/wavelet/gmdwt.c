
#include "gmfilter.h"

using namespace GMlib;
using namespace GMlib::Wavelet;

template<typename T>
Dwt<T>::Dwt(int dim) :
  _dimension(dim) {
  _filters.setDim(dim);
}

template<typename T>
void
Dwt<T>::setFilter(int dim, Filter<T> *filter) {
  _filters[dim] = filter;
}
