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



/*! \file gmStlObject.c
 *
 *  Implementation of StlObject class inline functions.
 *
 *  \date   2008-10-21
 */


namespace GMlib {



  inline
  string StlObject::getIdentity() const {

    return _identity;
  }


  inline
  unsigned int StlObject::getNoPoints() {

    return _vertices.getSize();
  }


  inline
  Array< UnitVector3D<float> > StlObject::getNormals() {

    return _normals;
  }


  inline
  Array< Point<float,3> > StlObject::getVertices() {

    Array< Point<float,3> > v;         // returns copy, no cast between Point3D<float> and Point<float,3>
    v.setSize( _vertices.getSize() );
    for( int i = 0; i < _vertices.getSize(); i++ )
      v[i] = _vertices[i];

    return v;
  }


  inline
  ArrayLX< Vertex<float> > StlObject::getVertex() {

    ArrayLX< Vertex<float> > v;         // returns copy, no cast between Point3D<float> and Point<float,3>
    v.setSize( _vertices.getSize() );
    for( int i = 0; i < _vertices.getSize(); i++ )
      v[i] = Vertex<float>( _vertices[i], _normals[i/3] );

    return v;
  }


  inline
  void StlObject::localDisplay() {

    _color.glSet();
    if( _dlist )
      glCallList( _dlist );
  }


  inline
  void StlObject::localSelect() {

    glCallList( _dlist+1 );
  }


  inline
  void StlObject::setColor( const GLColor& color ) {

    _color = color;
  }

}
