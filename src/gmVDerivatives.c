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



/*! \file gmVDerivatives.c
 *  \brief VDerivatives class function implementations
 *
 *  Implementation of the VDerivatives class.
 *
 *  \date   2009-01-28
 */


// GMlib includes
#include "gmArrow3D.h"

namespace GMlib {


  template <typename T, int n>
  inline
  VDerivatives<T,n>::VDerivatives() {

    _init();
  }


  template <typename T, int n>
  inline
  VDerivatives<T,n>::VDerivatives( const VDerivatives<T,n>& copy ) : Visualizer<T,n>( copy ) {}


  template <typename T, int n>
  inline
  VDerivatives<T,n>::~VDerivatives() {

    if( _dlist )
      glDeleteLists( _dlist, 1 );
  }

  template <typename T, int n>
  inline
  void VDerivatives<T,n>::_init() {

    _dlist = 0;
    _color = GMcolor::Green;
    _u = 1;
    _v = 1;
    _size_mode = GM_VISUALIZER_DERIVATIVES_NORMALIZED;
    _size = 1.0;
  }


  template <typename T, int n>
  inline
  void VDerivatives<T,n>::display() {

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
  const GLColor& VDerivatives<T,n>::getColor() const {

    return _color;
  }


  template <typename T, int n>
  inline
  std::string VDerivatives<T,n>::getIdentity() const {

    return "Derivatives Visualizer";
  }


  template <typename T, int n>
  inline
  int VDerivatives<T,n>::getIdxU() const {

    return _u;
  }


  template <typename T, int n>
  inline
  int VDerivatives<T,n>::getIdxV() const {

    return _v;
  }


  template <typename T, int n>
  inline
  double VDerivatives<T,n>::getSize() const {

    return _size;
  }


  template <typename T, int n>
  inline
  GM_VISUALIZER_DERIVATIVES_SIZE VDerivatives<T,n>::getSizeMode() const {

    return _size_mode;
  }


  template <typename T, int n>
  inline
  void VDerivatives<T,n>::replot(
    DVector< DVector< Vector<T, 3> > >& p,
    int /*m*/, int /*d*/
  ) {

    if( !this->_ref->isDynamic() ) {

      if( _dlist )
        glDeleteLists( _dlist, 1 );

      _dlist = glGenLists(1);

      int der = 0;
      if( (_u >= 0) || (_u <= p[0].getDim()-1) )
        der = _u;


      glNewList( _dlist, GL_COMPILE ); {
        for( int i = 0; i < p.getDim(); i++ ) {
          glBegin(GL_LINES); {

            glPoint( Point3D<float>( ( p[i][0] ).toFloat() ) );

            switch( _size_mode ) {
              case GM_VISUALIZER_DERIVATIVES_PERCENT:
                glPoint( Point3D<float>( ( p[i][0] + ( p[i][der] * _size ) ).toFloat() ) );
                break;

              case GM_VISUALIZER_DERIVATIVES_VERTEX:
                glPoint( Point3D<float>( ( p[i][0] + ( p[i][der].getNormalized() * _size ) ).toFloat() ) );
                break;

              case GM_VISUALIZER_DERIVATIVES_NORMALIZED:
              default:
                glPoint( Point3D<float>( ( p[i][0] + p[i][der].getNormalized() ).toFloat() ) );
                break;
            }
          } glEnd();
        }

      } glEndList();
    }
  }


  template <typename T, int n>
  inline
  void VDerivatives<T,n>::replot(
    DMatrix< DMatrix< Vector<T, 3> > >& p,
    DMatrix< Vector<T, 3> >& /*normals*/,
    int /*m1*/, int /*m2*/, int /*d1*/, int /*d2*/
  ) {

    if( !this->_ref->isDynamic() ) {

      if( _dlist )
        glDeleteLists( _dlist, 1 );

      _dlist = glGenLists(1);

      int der_u = 0;
      int der_v = 0;

      if( (_u >= 0) || (_u <= p[0][0].getDim1()-1) )
        der_u = _u;

      if( (_v >= 0) || (_v <= p[0][0].getDim2()-1) )
        der_v = _v;


      glNewList( _dlist, GL_COMPILE ); {
        for( int i = 0; i < p.getDim1(); i++ ) {
          for( int j = 0; j < p.getDim2(); j++ ) {

            switch( _size_mode ) {
              case GM_VISUALIZER_DERIVATIVES_PERCENT:
                Arrow3D( Arrow<T,3>( p[i][j][0][0], ( p[i][j][der_u][der_v] * _size ) ) ).display();
                break;

              case GM_VISUALIZER_DERIVATIVES_VERTEX:
                Arrow3D( Arrow<T,3>( p[i][j][0][0], p[i][j][der_u][der_v].getNormalized() * _size ) ).display();
                break;

              case GM_VISUALIZER_DERIVATIVES_NORMALIZED:
              default:
                Arrow3D( Arrow<T,3>( p[i][j][0][0], p[i][j][der_u][der_v].getNormalized() ) ).display();
                break;
            }
          }
        }

      } glEndList();
    }
  }


  template <typename T, int n>
  inline
  void VDerivatives<T,n>::setColor( const GLColor& color ) {

    _color = color;
  }


  template <typename T, int n>
  inline
  void VDerivatives<T,n>::setSize( GM_VISUALIZER_DERIVATIVES_SIZE mode, double size ) {

    _size_mode = mode;

    switch( _size_mode ) {

      case GM_VISUALIZER_DERIVATIVES_PERCENT:
        if( size < 0.0 || size > 1.0 )
          _size = 1.0;
        else
          _size = size;
        break;

      case GM_VISUALIZER_DERIVATIVES_NORMALIZED:
      case GM_VISUALIZER_DERIVATIVES_VERTEX:
      default:
        _size = size;
        break;
    }
  }


  template <typename T, int n>
  inline
  void VDerivatives<T,n>::showDerivative( int u, int v ) {

    _u = u;
    _v = v;
  }
}
