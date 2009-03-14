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



/*! \file gmVNormals.c
 *  \brief VNormals class function implementations
 *
 *  Implementation of the VNormals class.
 *
 *  \date   2009-01-28
 */


// GMlib includes
#include "gmArrow3D.h"

namespace GMlib {



  template <typename T, int n>
  inline
  VNormals<T,n>::VNormals() {

    _init();
  }


  template <typename T, int n>
  inline
  VNormals<T,n>::VNormals( const VNormals<T,n>& copy ) : Visualizer<T,n>( copy ) {}


  template <typename T, int n>
  inline
  VNormals<T,n>::~VNormals() {

    if( _dlist )
      glDeleteLists( _dlist, 1 );
  }


  template <typename T, int n>
  inline
  void VNormals<T,n>::_init() {

    _dlist = 0;
    _color = GMcolor::Black;
    _size = 1.0;
  }


  template <typename T, int n>
  inline
  void VNormals<T,n>::display() {

    // Push GL Attributes
    glPushAttrib( GL_LINE_BIT | GL_LIGHTING_BIT );

    // Set Properties
    glDisable( GL_LIGHTING );
    glColor( _color );

    // Display; dependant on dynamic/static status
    if( this->_ref->isDynamic() ) {
//
//      // Get Vertex, Texture and Material Data
//      const DMatrix< Arrow<float,3> > &v = this->_ref->getVerticesN2();
//
//      // Enable Vertex and Normal Array
//      glEnableClientState( GL_VERTEX_ARRAY );
//
//      // Draw
//      for( int i = 0; i < v.getDim1(); i++ ) {
//
//        // Give Pointers to Vertex and Normal Data
//        glVertexPointer( 3, GL_FLOAT, 3*sizeof(float), v(i)(0).getPos().getPtr() );
//
//        // Draw Strip
//        glDrawArrays( GL_LINES, 0, v(i).getDim()*2 );
//      }
//
//      // Disable Client States
//      glDisableClientState( GL_VERTEX_ARRAY );
    }
    else {

      glCallList( _dlist );
    }

    // Pop GL Attributes
    glPopAttrib();
  }


  template <typename T, int n>
  inline
  const GLColor& VNormals<T,n>::getColor() const {

    return _color;
  }


  template <typename T, int n>
  inline
  std::string VNormals<T,n>::getIdentity() const {

    return "Normals Visualizer";
  }


  template <typename T, int n>
  inline
  double VNormals<T,n>::getSize() const {

    return _size;
  }


  template <typename T, int n>
  void VNormals<T,n>::replot(
    DMatrix< DMatrix< Vector<T, 3> > >& p,
    DMatrix< Vector<T, 3> >& normals,
    int m1, int m2, int d1, int d2
  ) {

    if( !this->_ref->isDynamic() ) {

      if( _dlist )
        glDeleteLists( _dlist, 1 );

      _dlist = glGenLists(1);

      glNewList( _dlist, GL_COMPILE ); {

        for( int i = 0; i < p.getDim1(); i++ )
          for( int j = 0; j < p.getDim2(); j++ )
            Arrow3D( Arrow<T,3>( p[i][j][0][0], normals[i][j].getNormalized() * _size ) ).display();

      } glEndList();
    }
  }


  template <typename T, int n>
  void VNormals<T,n>::setColor( const GLColor& color ) {

    _color = color;
  }


  template <typename T, int n>
  inline
  void VNormals<T,n>::setSize( double size ) {

    _size = size;
  }

}

