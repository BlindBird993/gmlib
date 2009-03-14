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



/*! \file gmVisualizer.c
 *  \brief Visualizer class function implementations
 *
 *  Implementation of the Visualizer class.
 *
 *  \date   2008-09-10
 */


#include "gmDCurve.h"
#include "gmDSurf.h"


namespace GMlib {


  template <typename T, int n>
  inline
  Visualizer<T,n>::Visualizer() {}


  template <typename T, int n>
  inline
  Visualizer<T,n>::Visualizer( const Visualizer<T,n>& copy ) {}


  template <typename T, int n>
  inline
  Visualizer<T,n>::~Visualizer() {}


  template <typename T, int n>
  inline
  void Visualizer<T,n>::_init() {

    _ref = 0;
    _ref_n1 = 0;
    _ref_n2 = 0;
  }


  template <typename T, int n>
  inline
  std::string Visualizer<T,n>::getIdentity() const {

    return "Visualizer Base";
  }


  template <typename T, int n>
  inline
  void Visualizer<T,n>::replot(
    DVector< DVector< Vector<T, 3> > >& p,
    int m, int d
  ) {}


  template <typename T, int n>
  inline
  void Visualizer<T,n>::replot(
    DMatrix< DMatrix< Vector<T, 3> > >& p,
    DMatrix< Vector<T, 3> >& normals,
    int m1, int m2, int d1, int d2
  ) {}


  template <typename T, int n>
  inline
  void Visualizer<T,n>::select() {}


  template <typename T, int n>
  inline
  void Visualizer<T,n>::set( DParametrics<T,n>* obj ) {

    _ref = obj;

    switch( n ) {
      case 1: {

        _ref_n1 = dynamic_cast<DCurve<T>*>( obj );
      }
      break;

      case 2:
      default: {

        _ref_n2 = dynamic_cast<DSurf<T>*>( obj );
      }
      break;
    }
  }


  template <typename T, int n>
  inline
  bool Visualizer<T,n>::operator == ( const Visualizer* v ) const {

    if( this == v )
      return true;

    return false;
  }

}
