
using namespace GMlib;
using namespace GMlib::Wavelet;

/*!
 * \brief Filter<T>::Filter
 * \param dim - Dimension
 * \param coefs - The raw coefficients for a low-pass filter (not normalized)
 */
template<typename T>
Filter<T>::Filter() {
}

template<typename T>
void Filter<T>::setFilterCoefs(const DVector<T> &coefs) {
  calcFilters(coefs);
}

template<typename T>
DVector<T>&
Filter<T>::getDecomposeHP() const {
  return _d_hp;
}

template<typename T>
DVector<T>&
Filter<T>::getDecomposeLP() const {
  return _d_lp;
}

template<typename T>
DVector<T>&
Filter<T>::getReconstructHP() const {
  return _r_hp;
}

template<typename T>
DVector<T>&
Filter<T>::getReconstructLP() const {
  return _r_lp;
}

/*!
 * \brief Filter<T>::qmf - Computes a quadrature mirror filter
 * \param f - Original filter
 * \param v - Resulting filter
 * \param p - Even or odd number
 *
 *  Changes the sign of the even index entries of the reversed
 *  vector filter coefficients f if p is even. If p is odd the
 *  same holds for odd index entries.
 *
 */
template<typename T>
void
Filter<T>::qmf(const DVector<T> &f, DVector<T> &v, int p) const {
  v = f.getReversed();
  for (int i=1-p%2; i < v.getDim(); i++) {
    v[i] = -v[i];
  }
}
