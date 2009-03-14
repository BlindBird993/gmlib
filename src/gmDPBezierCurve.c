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



/*! \file gmDPBezierCurve.c
 *
 *  Implementation of the DPBezierCurve template class.
 *
 *  \date   2008-10-28
 */


namespace GMlib {


  template <typename T>
  inline
  DPBezierCurve<T>::DPBezierCurve( const DVector< Vector<T, 3> >& cp ) : DCurve<T>( new PBezierCurve<T,3>( cp ) ) {

    init();
  }


  template <typename T>
  inline
  DPBezierCurve<T>::DPBezierCurve( const DVector< Vector<T, 3> >& cp, T s, T t, T e ) : DCurve<T>( new PBezierCurve<T,3>( cp, s, t, e ) ) {

    init();
  }


  template <typename T>
  inline
  DPBezierCurve<T>::DPBezierCurve( const DPBezierCurve<T>& copy ) : DCurve<T>( copy ) {

    init();
  }


  template <typename T>
  inline
  DPBezierCurve<T>::DPBezierCurve( const PBezierCurve<T,3>& copy ) : DCurve<T>( copy ) {

    init();
  }


  template <typename T>
  inline
  DPBezierCurve<T>::DPBezierCurve( PBezierCurve<T,3>* copy ) : DCurve<T>( copy ) {

    _l_ref = copy;
  }


  template <typename T>
  DPBezierCurve<T>::~DPBezierCurve() {}


  template <typename T>
  void DPBezierCurve<T>::edit( int selector ) {

    DCurve<T>::replot(0,false);
    if( this->_parent )
      this->_parent->edit( this );
  }


  template <typename T>
  inline
  string DPBezierCurve<T>::getIdentity() const {

    return "DPBezierCurve";
  }


  template <typename T>
  inline
  PBezierCurve<T,3>* DPBezierCurve<T>::getPBezierCurve() {

    return _l_ref;
  }


  template <typename T>
  inline
  void DPBezierCurve<T>::hideSelectors() {

    if( !_selectors )
      return;

    // Remove Selector Grid
    DisplayObject::remove( _sg );
    delete _sg;
    _sg = 0;

    // Remove Selectors
    for( int i = 0; i < _s.getDim(); i++ ) {
      DisplayObject::remove( _s[i] );
      delete _s[i];
    }

    _selectors = false;
  }


  template <typename T>
  void DPBezierCurve<T>::init() {

    _l_ref = dynamic_cast<PBezierCurve<T,3>*>(this->_p_ref);
    _selectors = false;
    _sg = 0;
  }


  template <typename T>
  inline
  void DPBezierCurve<T>::localDisplay() {

    DCurve<T>::localDisplay();
  }


  template <typename T>
  inline
  void DPBezierCurve<T>::rotate(Angle a, const Vector<float,3>& rot_axel) {

    DParametrics<T,1>::rotate( a, rot_axel );
    if( this->_parent )
      this->_parent->edit( this );
  }


  template <typename T>
  inline
  void DPBezierCurve<T>::rotate(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d) {

    DParametrics<T,1>::rotate( a, p, d );
    if( this->_parent )
      this->_parent->edit( this );
  }


  template <typename T>
  inline
  void DPBezierCurve<T>::rotateGlobal(Angle a, const Vector<float,3>& rot_axel) {

    DParametrics<T,1>::rotateGlobal( a, rot_axel );
    if( this->_parent )
      this->_parent->edit( this );
  }


  template <typename T>
  inline
  void DPBezierCurve<T>::rotateGlobal(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d) {

    DParametrics<T,1>::rotateGlobal( a, p, d );
    if( this->_parent )
      this->_parent->edit( this );
  }


  template <typename T>
  inline
  void DPBezierCurve<T>::showSelectors( bool grid, const GLColor& _selector_color, const GLColor& grid_color ) {

    if( _selectors )
      return;

    DVector< Vector<T, 3> > &c = _l_ref->getControlPoints();

    _s.setDim( c.getDim() );
    for( int i = 0, s_id = 0; i < c.getDim(); i++ ) {

      Selector<T,3> *sel = new Selector<T,3>( c[i], s_id++, this, T(1), _selector_color );
      DisplayObject::insert( sel );
      _s[i] = sel;
    }


    if( grid ) {

      _sg = new SelectorGrid<T,3>( c[0], this, grid_color );

      for( int i = 1; i < c.getDim(); i++ )
          _sg->add(c[i-1], c[i]);  // Lines in grid

      DisplayObject::insert( _sg );
    }

    _selectors = true;
  }


  template <typename T>
  inline
  void DPBezierCurve<T>::translate( const Vector<float,3>& trans_vector ) {


    DParametrics<T,1>::translate( trans_vector );
    if( this->_parent )
      this->_parent->edit( this );
  }


  template <typename T>
  inline
  void DPBezierCurve<T>::translateGlobal( const Vector<float,3>& trans_vector ) {


    DParametrics<T,1>::translateGlobal( trans_vector );
    if( this->_parent )
      this->_parent->edit( this );
  }

}

