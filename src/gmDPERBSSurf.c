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



/*! \file gmDPERBSSurf.c
 *
 *  Implementation of the DPERBSSurf template class.
 *
 *  \date   2008-11-22
 */

#include "gmDPBezierSurf.h"

namespace GMlib {


  template <typename T>
  inline
  DPERBSSurf<T>::DPERBSSurf( PSurf<T,3>* g, int no_locals_u, int no_locals_v, int d1, int d2 )
    : DSurf<T>( new PERBSSurf<T,3>( g, no_locals_u, no_locals_v, d1, d2 ) ) {

    init();
  }


  template <typename T>
  inline
  DPERBSSurf<T>::DPERBSSurf( const DPERBSSurf<T>& copy ) : DSurf<T>( copy ) {

    init();
  }


  template <typename T>
  inline
  DPERBSSurf<T>::DPERBSSurf( const PERBSSurf<T,3>& copy ) : DSurf<T>( copy ) {

    init();
  }


  template <typename T>
  inline
  DPERBSSurf<T>::DPERBSSurf( PERBSSurf<T,3>* copy ) : DSurf<T>( copy ) {

    _l_ref = copy;
  }


  template <typename T>
  inline
  DPERBSSurf<T>::~DPERBSSurf() {}


  template <typename T>
  inline
  void DPERBSSurf<T>::edit( SceneObject* obj ) {

    DSurf<T>::replot(0,0);
  }


  template <typename T>
  inline
  string DPERBSSurf<T>::getIdentity() const {

    return "DPERBSSurf";
  }


  template <typename T>
  inline
  PERBSSurf<T,3>* DPERBSSurf<T>::getPERBSSurf() {

    return _l_ref;
  }

  template <typename T>
  inline
  void DPERBSSurf<T>::hideLocalPatches() {

    if( !_p_visible )
      return;

    for( int i = 0; i < _p.getDim1(); i++ ) {
      for( int j = 0; j < _p.getDim2(); j++ ) {
        SceneObject::remove( _p[i][j] );
        delete _p[i][j];
      }
    }

    _p_visible = false;
  }


  template <typename T>
  inline
  void DPERBSSurf<T>::init() {

    _l_ref = dynamic_cast<PERBSSurf<T,3>*>(this->_p_ref);
    _p_visible = false;
  }


  template <typename T>
  inline
  bool DPERBSSurf<T>::isLocalPatchesVisible() const {

    return _p_visible;
  }


  template <typename T>
  inline
  void DPERBSSurf<T>::localDisplay() {

    DSurf<T>::localDisplay();
  }


  template <typename T>
  inline
  void DPERBSSurf<T>::showLocalPatches( bool collapsed ) {

    if( _p_visible )
      return;

    DMatrix< PSurf<T,3>* > &p = getPERBSSurf()->getLocalPatches();

    // Number of Surfs U
    int no_surfs_u;
    if( getPERBSSurf()->isClosedU() )
      no_surfs_u = p.getDim1() - 1;
    else
      no_surfs_u = p.getDim1();

    // Number of Surfs V
    int no_surfs_v;
    if( getPERBSSurf()->isClosedV() )
      no_surfs_v = p.getDim2() - 1;
    else
      no_surfs_v = p.getDim2();



    _p.setDim( no_surfs_u, no_surfs_v );

    for( int i = 0; i < no_surfs_u; i++ )
      for( int j = 0; j < no_surfs_v; j++ )
        visualizeLocalPatch( p[i][j], i, j, no_surfs_u, no_surfs_v, collapsed );

    _p_visible = true;
  }


  template <typename T>
  inline
  void DPERBSSurf<T>::visualizeLocalPatch( PSurf<T,3>* p, int i, int j, int n, int m, bool collapsed ) {


    // Bezier Curve
    PBezierSurf<T,3> *bsObj = dynamic_cast<PBezierSurf<T,3>* >( p );
    if( bsObj ) {

      _p[i][j] =  new DPBezierSurf<T>( bsObj );
      visualizeLocalPatchInit( i, j, n, m, collapsed );
      return;
    }
  }


  template <typename T>
  inline
  void DPERBSSurf<T>::visualizeLocalPatchInit( int i, int j, int n, int m, bool collapsed ) {

    // if-then: Set collapsed
    if( collapsed )
      _p[i][j]->setCollapsed( true );

    // Create Plot
    _p[i][j]->replot( 10, 10 );

    // Insert in scene
    SceneObject::insert( _p[i][j] );
  }

}


