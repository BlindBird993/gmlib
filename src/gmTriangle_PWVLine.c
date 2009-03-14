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



/*! \file gmTriangle_PWVLine.c
 *  \brief PWVLine class function implementations
 *
 *  \date   2008-10-24
 */



namespace GMlib {



  template <typename T>
  inline
  PWVLine<T>::PWVLine( int d ) : Array<Vertex<T> >( d ) {}


  template <typename T>
  inline
  PWVLine<T>::PWVLine(const Array<Vertex<T> >& v) : Array<Vertex<T> >(v) {}


  template <typename T>
  Vertex<T> PWVLine<T>::interpolate( int i, double t ) const {

  //	if( i < 0 || i > getSize() - 2 ) {
  //		// Errormessage for debug purpose
  //	}

    Point<T,3> pos = (1-t)*( (*this)(i).getPosition() ) + t*( (*this)(i+1).getPosition() );
    Point<T,3> nor = (1-t)*( (*this)(i).getNormal() ) + t*( (*this)(i+1).getNormal() );

    return Vertex<T>( pos, nor );
  }

}

