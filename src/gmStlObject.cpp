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



/*! \file gmStlObject.cpp
 *
 *  Implementation of StlObject class functions.
 *
 *  \date   2008-10-21
 */



#include "gmStlObject.h"


namespace GMlib {


  StlObject::StlObject(float r) {
    _fname = string( "STL place holder" );
    _sphere = new DPSphere<float>( r );
    _sphere->replot();
    insert( _sphere );

    // update bounding sphere
    Point3D<float> pos(0,0,0);
    Sphere<float,3> s(pos,r);

    setSurroundingSphere(s);
  }


  StlObject::StlObject( const std::string& filename, const GLColor& color, int flip ) {

    _color = color;
    _fname = filename;

    _readStlBinary( filename );

    // update bounding box
    _bbox.reset( _vertices[0] );
    for( int i = 0; i < _vertices.getSize()-1; i++ )
      _bbox += _vertices[i];

    // make display lists
    _dlist_name = glGenLists( 2 );
    glNewList( _dlist_name, GL_COMPILE ); {
      glBegin( GL_TRIANGLES ); {

        for( int i = 0; i < _normals.getSize()-1; i++) {
          glNormal( _normals[i] );                // STL file only carries one normal
          for( int j = 0; j < 3; j++ )            // for each triangle, makes a facet shading,
            glPoint( _vertices[ 3*i+j ] );        // they must be averaged for true smooth surfaces.
        }
      } glEnd();
    } glEndList();

    // Build a new list for selection
    glNewList( _dlist_name+1, GL_COMPILE ); {
      glBegin( GL_TRIANGLES ); {

        for( int i = 0; i < _normals.getSize()-1; i++ ) {
          glNormal( _normals[i] );
          for( int j = 0;j < 3; j++ )
            glPoint( _vertices[ 3*i+j ] );
        }
      } glEnd();
    } glEndList();

    // update bounding sphere
    Point3D<float> pos( _bbox.getPointCenter() );          // which can be far from origo
    Sphere<float,3> s( pos, _bbox.getPointDelta().getLength() * 0.5 );

    setSurroundingSphere( s );

  }



  StlObject::~StlObject() {

    glDeleteLists( _dlist_name, 2 );
  }


  unsigned long StlObject::_getUli() {

    unsigned char byte1,byte2,byte3,byte4;
    unsigned long int number;
    byte1=(unsigned char)fgetc( _stl_file );
    byte2=(unsigned char)fgetc( _stl_file );
    byte3=(unsigned char)fgetc( _stl_file );
    byte4=(unsigned char)fgetc( _stl_file );
    number = (unsigned long int)byte1 + ((unsigned long int)byte2<<8)
        + ((unsigned long int)byte3<<16) + ((unsigned long int)byte4<<24);
    return( number );
  }


  float StlObject::_getFloat() {

    float number;
    unsigned char stream[5];
    // used to be 3,2,1,0
    stream[0]=(unsigned char)fgetc( _stl_file );
    stream[1]=(unsigned char)fgetc( _stl_file );
    stream[2]=(unsigned char)fgetc( _stl_file );
    stream[3]=(unsigned char)fgetc( _stl_file );

    stream[4] = '\0';

    memcpy( &number, &stream, 4 );

    return( number );
  }


  unsigned int StlObject::_getUint() {

    unsigned char byte1,byte2;
    unsigned int number;
    byte1=(unsigned char)fgetc( _stl_file );
    byte2=(unsigned char)fgetc( _stl_file );
    number = (unsigned int)byte1 + ((unsigned int)byte2<<8);
    return( number );
  }


  int StlObject::_readStlBinary(const string& filename) {

    if( ( _stl_file = fopen( filename.c_str(), "rb" ) ) == NULL )
      return(-1);

    unsigned long int t;

    // Skipping comment line
    for( t=0; t<80 ; t++ )
      fgetc( _stl_file );

    // Get number for triangles
    unsigned long int n_triangles = _getUli();
    float x,y,z;
    _normals.setMaxSize( n_triangles+1 );
    _vertices.setMaxSize( (n_triangles*3)+1 );

    // Read all the triangles
    for( t=0; t<n_triangles; t++ ) {

      // and put in array
      x=_getFloat(); y=_getFloat(); z=_getFloat();
      _normals.insertAlways( UnitVector3D<float>(x,y,z) );


      x=_getFloat(); y=_getFloat(); z=_getFloat();
      _vertices.insertAlways( Point3D<float> (x,y,z) );

      x=_getFloat(); y=_getFloat(); z=_getFloat();
      _vertices.insertAlways( Point3D<float> (x,y,z) );

      x=_getFloat(); y=_getFloat(); z=_getFloat();
      _vertices.insertAlways( Point3D<float> (x,y,z) );

      // Get number of attribute bytes (is always zero and can be ignored)
      _getUint();
    }

    fclose( _stl_file );
    return 1;
  }

}
