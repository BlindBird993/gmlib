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



/*! \file gmPSubSurf.c
 *
 *  Implementation of the PSubSurf template class.
 *
 *  \date   2012-11-25, ALA
 */


namespace GMlib {


  // Constructors and destructors
  //******************************

  template <typename T>
  inline
  PSubSurf<T>::PSubSurf( PSurf<T>* s, T su, T eu, T sv, T ev )
  {
    this->_dm = GM_DERIVATION_EXPLICIT;
    set(s, su, eu, (su+eu)/2, sv, ev, (sv+ev)/2);
    // Set local coordinate system
    DMatrix<Vector<T,3> > tr = _s->evaluateParent(_u, _v, 0);
    _trans = tr[0][0];
    this->DisplayObject::translate(_trans);
  }


  template <typename T>
  inline
  PSubSurf<T>::PSubSurf( PSurf<T>* s, T su, T eu, T u, T sv, T ev, T v )
  {
    this->_dm = GM_DERIVATION_EXPLICIT;
    set(s, su, eu, u, sv, ev, v);
    // Set local coordinate system
    DMatrix<Vector<T,3> > tr = _s->evaluateParent(_u, _v, 0, 0);
    _trans = tr[0][0];
    this->DisplayObject::translate( _trans );
  }


  template <typename T>
  inline
  PSubSurf<T>::PSubSurf( const PSubSurf<T>& copy ) : PSurf<T>( copy )
  {
    set(copy._s, copy._su, copy._eu, copy._u, copy._sv, copy._ev, copy._v);
    // Set local coordinate system
    _trans = copy._trans;
  }


  template <typename T>
  PSubSurf<T>::~PSubSurf() {}



  // Virtual functions from PSurf
  //******************************

  template <typename T>
  void PSubSurf<T>::eval( T u, T v, int d1, int d2, bool /*lu*/, bool /*lv*/)
  {
    this->_p        = _s->evaluateParent(u, v, d1, d2);
    this->_p[0][0] -= _trans;
  }

  template <typename T>
  T PSubSurf<T>::getStartPU()
  {
    return _su;
  }

  template <typename T>
  T PSubSurf<T>::getStartPV()
  {
    return _sv;
  }

  template <typename T>
  T PSubSurf<T>::getEndPU()
  {
    return _eu;
  }

  template <typename T>
  T PSubSurf<T>::getEndPV()
  {
    return _ev;
  }

  template <typename T>
  bool PSubSurf<T>::isClosedU() const
  {
    return false;
  }

  template <typename T>
  bool PSubSurf<T>::isClosedV() const
  {
    return false;
  }


  // Private help functions
  //*************************

  template <typename T>
  inline
  void PSubSurf<T>::set(PSurf<T>* s, T su, T eu, T u, T sv, T ev, T v)
  {
    _s  = s;
    _su = su;
    _u  = u;
    _eu = eu;
    _sv = sv;
    _v  = v;
    _ev = ev;
  }

} // END namespace GMlib

