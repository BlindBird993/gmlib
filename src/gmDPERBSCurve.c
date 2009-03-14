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



/*! \file gmDPERBSCurve.c
 *
 *  Implementation of the DPERBSCurve template class.
 *
 *  \date   2008-10-30
 */

#include "gmDPBezierCurve.h"
#include "gmDPArc.h"

namespace GMlib {


  template <typename T>
  inline
  DPERBSCurve<T>::DPERBSCurve( PCurve<T,3>* g, int n, int d ) : DCurve<T>( new PERBSCurve<T, 3>( g, n, d ) ) {

    init();
  }


  template <typename T>
  inline
  DPERBSCurve<T>::DPERBSCurve( PCurve<T,3>* g, int n ) : DCurve<T>( new PERBSCurve<T, 3>( g, n ) ) {

    init();
  }


  template <typename T>
  inline
  DPERBSCurve<T>::DPERBSCurve( const DPERBSCurve<T>& copy ) : DCurve<T>( copy ) {

    init();
  }


  template <typename T>
  inline
  DPERBSCurve<T>::DPERBSCurve( const PERBSCurve<T,3>& copy ) : DCurve<T>( copy ) {

    init();
  }


  template <typename T>
  inline
  DPERBSCurve<T>::DPERBSCurve( PERBSCurve<T,3>* copy ) : DCurve<T>() {

    _l_ref = copy;
  }


  template <typename T>
  DPERBSCurve<T>::~DPERBSCurve() {}


  template <typename T>
  inline
  void DPERBSCurve<T>::edit( SceneObject *obj ) {

    DCurve<T>::replot( 0 );
  }


  template <typename T>
  inline
  string DPERBSCurve<T>::getIdentity() const {

    return "DPERBSCurve";
  }


  template <typename T>
  inline
  PERBSCurve<T,3>* DPERBSCurve<T>::getPERBSCurve() {

    return _l_ref;
  }


  template <typename T>
  inline
  void DPERBSCurve<T>::hideLocalPatches() {

    if( !_p_visible )
      return;

    for( int i = 0; i < _p.getDim(); i++ )
      SceneObject::remove( _p[i] );

    _p.clear();

    _p_visible = false;
  }


  template <typename T>
  void DPERBSCurve<T>::init() {

    _l_ref = dynamic_cast<PERBSCurve<T,3>*>( this->_p_ref );
    _p_visible = false;
  }


  template <typename T>
  inline
  bool DPERBSCurve<T>::isLocalPatchesVisible() const {

    return _p_visible;
  }


  template <typename T>
  inline
  void DPERBSCurve<T>::localDisplay() {

    DCurve<T>::localDisplay();
  }


  template <typename T>
  inline
  void DPERBSCurve<T>::showLocalPatches( bool collapsed ) {

    if( _p_visible )
      return;

    DVector< PCurve<T,3>* > &p = getPERBSCurve()->getLocalPatches();

    int no_curves;
    if( getPERBSCurve()->isClosed() )
      no_curves = p.getDim() - 1;
    else
      no_curves = p.getDim();

    _p.setDim( no_curves );

    for( int i = 0; i < no_curves; i++ ) {

      visualizeLocalPatch(p[i], i, no_curves, collapsed );
    }

    _p_visible = true;
  }


  template <typename T>
  inline
  void DPERBSCurve<T>::visualizeLocalPatch( PCurve<T,3>* p, int i, int m, bool collapsed ) {

    // Arc
    PArc<T,3> *arcObj = dynamic_cast<PArc<T,3>*>( p );
    if( arcObj ) {

      _p[i] = new DPArc<T>( arcObj );
      visualizeLocalPatchInit( i, m, collapsed );
      return;
    }

    // Bezier Curve
    PBezierCurve<T,3> *bcObj = dynamic_cast<PBezierCurve<T, 3>* >( p );
    if( bcObj ) {

      _p[i] = new DPBezierCurve<T>( bcObj );
      visualizeLocalPatchInit( i, m, collapsed );
      return;
    }
  }


  template <typename T>
  inline
  void DPERBSCurve<T>::visualizeLocalPatchInit( int i, int m, bool collapsed ) {

    // if-then: Set collapsed
    if( collapsed )
      _p[i]->setCollapsed( true );

    // Create Plot
    _p[i]->replot( 10 );

    // Insert in scene
    SceneObject::insert( _p[i] );
  }

}


