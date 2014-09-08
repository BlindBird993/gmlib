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



/*! \file gmPHermiteSurf.c
 *
 *  Implementation of the PHermiteSurf template class.
 *
 *  \date   2012-04-09, ALA
 */


#include "../evaluators/gmevaluatorstatic.h"


namespace GMlib {



  template <typename T>
  inline
  PHermiteSurf<T>::PHermiteSurf(  const DMatrix<Vector<T,3> >& m )
  {
    this->_dm = GM_DERIVATION_EXPLICIT;

    _m = m;
  }


  template <typename T>
  inline
  PHermiteSurf<T>::PHermiteSurf( const DMatrix<Vector<T,3> >& c1, const DMatrix<Vector<T,3> >& c2,
                                 const DMatrix<Vector<T,3> >& c3, const DMatrix<Vector<T,3> >& c4 )
  {
    this->_dm = GM_DERIVATION_EXPLICIT;

    _m.setDim(4,4);

    _m[0][0] = c1(0)(0);  _m[0][1] = c2(0)(0);  _m[1][0] = c3(0)(0); _m[1][1] = c4(0)(0);
    _m[0][2] = c1(0)(1);  _m[0][3] = c2(0)(1);  _m[1][2] = c3(0)(1); _m[1][3] = c4(0)(1);
    _m[2][0] = c1(1)(0);  _m[2][1] = c2(1)(0);  _m[3][0] = c3(1)(0); _m[3][1] = c4(1)(0);
    _m[2][2] = c1(1)(1);  _m[2][3] = c2(1)(1);  _m[3][2] = c3(1)(1); _m[3][3] = c4(1)(1);
  }


  template <typename T>
  inline
  PHermiteSurf<T>::PHermiteSurf( const PHermiteSurf<T>& copy ) : PSurf<T,3>( copy )
  {
    _m = copy._m;
  }


  template <typename T>
  inline
  PHermiteSurf<T>::~PHermiteSurf() {}



  template <typename T>
  inline
  void PHermiteSurf<T>::eval( T u, T v, int d1, int d2, bool /*lu*/, bool /*lv*/ )
  {
    this->_p.setDim( d1+1, d2+1 );

    DMatrix<T> hu, hv;
    EvaluatorStatic<T>::evaluateHp( hu, d1, u);
    EvaluatorStatic<T>::evaluateHp( hv, d2, v);

    for( int i = 0; i < hu.getDim1(); i++ )
      for( int j = 0; j < hv.getDim1(); j++ )
        this->_p[i][j] = hu[i] * ( _m^hv[j] );
  }



  template <typename T>
  inline
  T PHermiteSurf<T>::getEndPU()
  {
    return T(1);
  }


  template <typename T>
  inline
  T PHermiteSurf<T>::getEndPV()
  {
    return T(1);
  }



  template <typename T>
  inline
  T PHermiteSurf<T>::getStartPU()
  {
    return T(0);
  }


  template <typename T>
  inline
  T PHermiteSurf<T>::getStartPV()
  {
    return T(0);
  }


  template <typename T>
  inline
  bool PHermiteSurf<T>::isClosedU() const
  {
    return false; //_cu;
  }


  template <typename T>
  inline
  bool PHermiteSurf<T>::isClosedV() const
  {
    return false; //_cv;
  }


} // END namespace GMlib


