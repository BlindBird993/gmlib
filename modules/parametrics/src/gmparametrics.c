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



/*! \file gmparametrics.c
 *
 *  Implementation of the Parametrics class.
 */


namespace GMlib {

  template <typename T, int m, int n>
  inline
  Parametrics<T,m,n>::Parametrics() {

    _dm = GM_DERIVATION_EXPLICIT;
    _initSoType();
  }


  template <typename T, int m, int n>
  inline
  Parametrics<T,m,n>::Parametrics( const Parametrics<T,m,n>& copy ) : SceneObject( copy ) {}


  template <typename T, int m, int n>
  inline
  Parametrics<T,m,n>::~Parametrics() {}


  template <typename T, int m, int n>
  void Parametrics<T,m,n>::_initSoType() {

    switch( m ) {

      case GM_POINT:
        _type_id = GM_SO_TYPE_POINT;
        break;
      case GM_CURVE:
        _type_id = GM_SO_TYPE_CURVE;
        break;
      case GM_SURFACE:
        _type_id = GM_SO_TYPE_SURFACE;
        break;
      case GM_VOLUME:
        _type_id = GM_SO_TYPE_VOLUME;
        break;
      case GM_FLOW:
        _type_id = GM_SO_TYPE_FLOW;
        break;
    }
  }


  template <typename T, int m, int n>
  inline
  void Parametrics<T,m,n>::rotate(Angle a, const Vector<T,n>& rot_axel) {

    SceneObject::rotate( a, rot_axel );
    if( this->_parent )
      this->_parent->edit( this );
  }


  template <typename T, int m, int n>
  inline
  void Parametrics<T,m,n>::rotate(Angle a, const Point<T,n>& p,const UnitVector<T,n>& d) {

    SceneObject::rotate( a, p, d );
    if( this->_parent )
      this->_parent->edit( this );
  }


  template <typename T, int m, int n>
  inline
  void Parametrics<T,m,n>::rotateGlobal(Angle a, const Vector<T,n>& rot_axel) {

    SceneObject::rotateGlobal( a, rot_axel );
    if( this->_parent )
      this->_parent->edit( this );
  }


  template <typename T, int m, int n>
  inline
  void Parametrics<T,m,n>::rotateGlobal(Angle a, const Point<T,n>& p,const UnitVector<T,n>& d) {

    SceneObject::rotateGlobal( a, p, d );
    if( this->_parent )
      this->_parent->edit( this );
  }


  template <typename T, int m, int n>
  void Parametrics<T,m,n>::setDerivationMethod( GM_DERIVATION_METHOD method ) {

    _dm = method;
  }


  template <typename T, int m, int n>
  inline
  void Parametrics<T,m,n>::translate( const Vector<T,n>& trans_vector ) {

    SceneObject::translate( trans_vector.template toType<float>() );
    if( this->_parent )
      this->_parent->edit( this );
  }


  template <typename T, int m, int n>
  inline
  void Parametrics<T,m,n>::translateGlobal( const Vector<T,n>& trans_vector ) {

    SceneObject::translateGlobal( trans_vector.template toType<float>() );
    if( this->_parent )
      this->_parent->edit( this );
  }

} // END namespace GMlib
