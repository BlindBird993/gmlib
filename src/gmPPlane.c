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



/*! \file gmPPlane.c
 *
 *  Implementation of the gmPPlane template class.
 *
 *  \date   2008-09-06
 */




namespace GMlib {


  template <typename T, int n>
  inline
  PPlane<T, n>::PPlane( const Point<T,n>& p, const Vector<T,n>& u, const Vector<T,n>& v ) {

    _pt = p;
    _u = u;
    _v = v;

    if(n==3)
      _n = Vector3D<T>(u)^v;

    this->_dm = GM_DERIVATION_EXPLICIT;
  }

  template <typename T, int n>
  inline
  PPlane<T, n>::PPlane( const PPlane<T,n>& pl ) {

    _pt   = pl._pt;
    _u    = pl._u;
    _v    = pl._v;
    _n    = pl._n;
  }


  template <typename T, int n>
  inline
  const UnitVector<T,n>& PPlane<T, n>::getNormal() const {

    return _n;
  }

  template <typename T, int n>
  void PPlane<T, n>::eval(T u, T v, int d1, int d2, bool lu, bool lv ) {

    this->_p[0][0] = _pt + u*_u + v*_v ;

    if( this->_dm == GM_DERIVATION_EXPLICIT ) {

      if(d1) {

        this->_p[1][0] = _u;	// S_u
      }
      if(d2) {

        this->_p[0][1] = _v;	// S_v
      }
      if(d1>1) {

        this->_p[2][0][0] = T(0);	// S_uu
        this->_p[2][0][1] = T(0);
        this->_p[2][0][2] = T(0);
      }
      if(d1>1 && d2>1) {

        this->_p[1][1][0] = T(0);	// S_uv
        this->_p[1][1][1] = T(0);
        this->_p[1][1][2] = T(0);
      }
      if(d2>1) {

        this->_p[0][2][0] = T(0);	// S_vv
        this->_p[0][2][1] = T(0);
        this->_p[0][2][2] = T(0);
      }
      if(d1>2) {

        this->_p[3][0][0] = T(0);	// S_uuu
        this->_p[3][0][1] = T(0);
        this->_p[3][0][2] = T(0);
      }
      if(d1>2 && d2>2) {

        this->_p[1][2][0] = T(0);	// S_uuv
        this->_p[1][2][1] = T(0);
        this->_p[1][2][2] = T(0);
      }
      if(d1>2 && d2>2) {

        this->_p[2][1][0] = T(0);	// S_uvv
        this->_p[2][1][1] = T(0);
        this->_p[2][1][2] = T(0);
      }
      if(d2>2) {

        this->_p[0][3][0] = T(0);	// S_vvv
        this->_p[0][3][1] = T(0);
        this->_p[0][3][2] = T(0);
      }
    }
  }


  template <typename T, int n>
  inline
  T PPlane<T, n>::getEndPU()	{

    return T(1);
  }

  template <typename T, int n>
  inline
  T PPlane<T, n>::getEndPV()	{

    return T(1);
  }


  template <typename T, int n>
  std::string PPlane<T,n>::getIdentity() const {

    return "PPlane";
  }


  template <typename T, int n>
  inline
  T PPlane<T, n>::getStartPU() {

    return T(0);
  }


  template <typename T, int n>
  inline
  T PPlane<T, n>::getStartPV() {

    return T(0);
  }


  template <typename T, int n>
  inline
  const Vector<T,n>& PPlane<T,n>::getU() const {

    return _u;
  }


  template <typename T, int n>
  inline
  const Vector<T,n>& PPlane<T,n>::getV() const {

    return _v;
  }


  template <typename T, int n>
  inline
  bool PPlane<T,n>::isClosedU() const {

    return false;
  }


  template <typename T, int n>
  inline
  bool PPlane<T,n>::isClosedV() const {

    return false;
  }


  template <typename T, int n>
  inline
  void PPlane<T,n>::setU( const Vector<T,n>& u ) {

    _u = u;
  }


  template <typename T, int n>
  inline
  void PPlane<T,n>::setV( const Vector<T,n>& v ) {

    _v = v;
  }

}
