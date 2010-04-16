
#include "gmTriangleSystem.h"

namespace GMlib {

	template <typename T>
	inline
	TSVEdge<T>::TSVEdge() {}

	template <typename T>
	inline
	TSVEdge<T>::TSVEdge(const Point<T,2> &p, const Point<T,2> &q) {
		_pnts[0] = p;
		_pnts[1] = q;
	}

	template <typename T>
	inline
	bool TSVEdge<T>::operator==(const TSVEdge<T> &e) const {

		bool a=false ,b= false;
		if ((e._pnts[0] == _pnts[0])||(e._pnts[0] == _pnts[1])) a = true;
		if ((e._pnts[1] == _pnts[0])||(e._pnts[1] == _pnts[1])) b = true;

		return (a && b);
	}

	template <typename T>
	inline
	bool TSVEdge<T>::operator<(const TSVEdge<T> &e) const {
		return false;
	}

	template <typename T>
	inline
	Point<T,2> const &TSVEdge<T>::operator() (int i) const {
		return _pnts[i];
	}

}