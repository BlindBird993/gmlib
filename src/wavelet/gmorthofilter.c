
using namespace GMlib;
using namespace GMlib::Wavelet;

template<typename T>
OrthoFilter<T>::OrthoFilter() :
  Filter<T>() {
}

template<typename T>
void
OrthoFilter<T>::calcFilters(const DVector<T> &coefs) {
  //- Normalize filter sum and store as decompose low-pass filter
  this->_d_lp = coefs * ( T(1) / coefs.getSum() ) * sqrt(T(2));

  //- Compute hi-pass from low-pass
  this->qmf(this->_d_lp, this->_d_hp);

  //- Reconstruct filters are simply decompose filters reversed
  this->_r_lp = this->_d_lp.getReversed();
  this->_r_hp = this->_d_hp.getReversed();
}
