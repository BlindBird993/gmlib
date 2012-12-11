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



/*! \file gmpsubcurve.c
 *
 *  Implementation of the PSubCurve template class.
 */


namespace GMlib {


  // Constructors and destructors
  //******************************

  template <typename T>
  inline
  PSubCurve<T>::PSubCurve( PCurve<T>* c, T s, T e )
  {
    this->_dm = GM_DERIVATION_EXPLICIT;

    set(c, s, e, (e+s)/2);

    DVector<Vector<T,3> > tr = _c->evaluateParent(_t, 0);
    _trans = tr[0];
    this->DisplayObject::translate( _trans );
  }


  template <typename T>
  inline
  PSubCurve<T>::PSubCurve( PCurve<T>* c, T s, T e, T t )
  {
    this->_dm = GM_DERIVATION_EXPLICIT;

    set(c, s, e, t);

    DVector<Vector<T,3> > tr = _c->evaluateParent(_t, 0);
    _trans = tr[0];
    this->DisplayObject::translate( _trans );
  }


  template <typename T>
  inline
  PSubCurve<T>::PSubCurve( const PSubCurve<T>& copy ) : PCurve<T>( copy )
  {
    set(copy._c, copy._s, copy._e, copy._t);

    _trans = copy._trans;
  }


  template <typename T>
  PSubCurve<T>::~PSubCurve() {}


  // Virtual functions from PSurf
  //******************************

  template <typename T>
  void PSubCurve<T>::eval( T t, int d, bool /*l*/ )
  {
    this->_p     = _c->evaluateParent(t , d);
    this->_p[0] -= _trans;
  }


  template <typename T>
  T PSubCurve<T>::getStartP()
  {
    return _s;
  }


  template <typename T>
  T PSubCurve<T>::getEndP()
  {
    return _e;
  }


  template <typename T>
  bool PSubCurve<T>::isClosed() const
  {
    return false;
  }


  // Private help functions
  //*************************

  template <typename T>
  inline
  void PSubCurve<T>::set(PCurve<T>* c, T s, T e, T t)
  {
    _c = c;
    _s = s;
    _t = t;
    _e = e;
  }


} // END namespace GMlib

