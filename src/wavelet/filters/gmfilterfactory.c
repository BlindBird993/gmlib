
#include "gmfilterfactory.h"

namespace GMlib {
namespace Wavelet {

template<typename T>
OrthoFilter<T>*
FilterFactory<T>::createHaarFilter() {
  GMlib::DVector<float> coefs;
  coefs.append(0.5);
  coefs.append(0.5);
  GMlib::Wavelet::OrthoFilter<float>* f = new OrthoFilter<float>;
  f->setFilterCoefs(coefs);
  return f;
}


}
}
