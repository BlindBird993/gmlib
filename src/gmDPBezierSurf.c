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



/*! \file gmDPBezierSurf.c
 *
 *  Implementation of the DPBezierSurf template class.
 *
 *  \date   2008-11-20
 */


namespace GMlib {


  template <typename T>
  inline
  DPBezierSurf<T>::DPBezierSurf( const DMatrix< Vector<T, 3> >& cp )
    : DSurf<T>( new PBezierSurf<T,3>( cp ) ) {

    init();
  }


  template <typename T>
  inline
  DPBezierSurf<T>::DPBezierSurf( const DMatrix< Vector<T, 3> >& cp, T s_u, T u, T e_u, T s_v, T v, T e_v  )
    : DSurf<T>( new PBezierSurf<T,3>( cp, s_u, u, e_u, s_v, v, e_v ) ) {

    init();
  }


  template <typename T>
  inline
  DPBezierSurf<T>::DPBezierSurf( const DPBezierSurf<T>& dpbs ) : DSurf<T>( dpbs ) {

    init();
  }


  template <typename T>
  inline
  DPBezierSurf<T>::DPBezierSurf( const PBezierSurf<T,3>& pbs ) : DSurf<T>( pbs ) {

    init();
  }


  template <typename T>
  inline
  DPBezierSurf<T>::DPBezierSurf( PBezierSurf<T,3>* pbs ) : DSurf<T>( pbs ) {

    init();
  }

  template <typename T>
  inline
  DPBezierSurf<T>::~DPBezierSurf() {}


  template <typename T>
  void DPBezierSurf<T>::edit( int selector ) {

    DSurf<T>::replot(0,0,false);
    if( this->_parent )
      this->_parent->edit( this );
  }


  template <typename T>
  inline
  string DPBezierSurf<T>::getIdentity() const {

    return "DPBezierSurf";
  }


  template <typename T>
  inline
  PBezierSurf<T,3>* DPBezierSurf<T>::getPBezierSurf() {

    return _l_ref;
  }


  template <typename T>
  void DPBezierSurf<T>::hideSelectors() {

    if( !_selectors )
      return;

    // Remove Selector Grid
    DisplayObject::remove( _sg );
    delete _sg;
    _sg = 0;

    // Remove Selectors
    for( int i = 0; i < _s.getDim1(); i++ ) {
      for( int j = 0; j < _s.getDim2(); j++ ) {
        DisplayObject::remove( _s[i][j] );
        delete _s[i][j];
      }
    }

    _selectors = false;
  }


  template <typename T>
  void DPBezierSurf<T>::init() {

    _l_ref = dynamic_cast<PBezierSurf<T,3>*>( this->_p_ref );
    _selectors = false;
    _sg = 0;
  }


  template <typename T>
  inline
  void DPBezierSurf<T>::localDisplay() {

//    glPushAttrib( GL_LIGHTING_BIT | GL_POINT_BIT );
//
//
//    glDisable( GL_LIGHTING );
//    glColor( GMcolor::Green );
//    glPointSize( 1.5f );
//
//    glBegin( GL_POINTS ); {
//
//
//      glPoint( (this->evaluate(0.5, 0))[0] );
//
//
//    } glEnd();
//
//    glPopAttrib();

    DSurf<T>::localDisplay();

  }


  template <typename T>
  inline
  void DPBezierSurf<T>::rotate(Angle a, const Vector<float,3>& rot_axel) {

    DParametrics<T,2>::rotate( a, rot_axel );
    if( this->_parent )
      this->_parent->edit( this );
  }


  template <typename T>
  inline
  void DPBezierSurf<T>::rotate(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d) {

    DParametrics<T,2>::rotate( a, p, d );
    if( this->_parent )
      this->_parent->edit( this );
  }


  template <typename T>
  inline
  void DPBezierSurf<T>::rotateGlobal(Angle a, const Vector<float,3>& rot_axel) {

    DParametrics<T,2>::rotateGlobal( a, rot_axel );
    if( this->_parent )
      this->_parent->edit( this );
  }


  template <typename T>
  inline
  void DPBezierSurf<T>::rotateGlobal(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d) {

    DParametrics<T,2>::rotateGlobal( a, p, d );
    if( this->_parent )
      this->_parent->edit( this );
  }


  template <typename T>
  inline
  void DPBezierSurf<T>::setResampleMode( GM_RESAMPLE_MODE mode ) {

    PBezierSurf<T,3> *tmp = dynamic_cast<PBezierSurf<T,3>*>( this->_p_ref);
    if( tmp )
      tmp->setResampleMode( mode );
  }


  template <typename T>
  void DPBezierSurf<T>::showSelectors( bool grid, const GLColor& _selector_color, const GLColor& grid_color ) {

    if( _selectors ) {
      cout << "Selectors already present" << endl;
      return;
    }

    DMatrix< Vector<T, 3> > &c = _l_ref->getControlPoints();

    _s.setDim( c.getDim1(), c.getDim2() );
    for( int i = 0, s_id = 0; i < c.getDim1(); i++ ) {
      for( int j = 0; j < c.getDim2(); j++ ) {

        Selector<T,3> *sel = new Selector<T,3>( c[i][j], s_id++, this, T(1), _selector_color );
        DisplayObject::insert( sel );
        _s[i][j] = sel;
      }
    }


    if( grid ) {

      DMatrix< Vector<T, 3> > &c = _l_ref->getControlPoints();

      _sg = new SelectorGrid<T,3>( c[0][0], this, grid_color );

      for( int i = 0; i < c.getDim1(); i++ ) {
        for( int j = 0; j < c.getDim2(); j++ ) {

          if(j!=0) _sg->add(c[i][j-1], c[i][j]);  // Horisontal lines in grid
          if(i!=0) _sg->add(c[i-1][j], c[i][j]);  // Vertical ilines in grid
        }
      }

      DisplayObject::insert( _sg );
    }

    _selectors = true;
  }


  template <typename T>
  inline
  void DPBezierSurf<T>::translate( const Vector<float,3>& trans_vector ) {


    DParametrics<T,2>::translate( trans_vector );
    if( this->_parent )
      this->_parent->edit( this );
  }


  template <typename T>
  inline
  void DPBezierSurf<T>::translateGlobal( const Vector<float,3>& trans_vector ) {


    DParametrics<T,2>::translateGlobal( trans_vector );
    if( this->_parent )
      this->_parent->edit( this );
  }

}


