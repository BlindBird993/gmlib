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



/*! \file gmVPoints.c
 *
 *  VPoints class function implementations.
 *
 *  \date   2009-01-27
 */


namespace GMlib {


  template <typename T, int n>
  inline
  VPoints<T,n>::VPoints() {

      _size = 1.0;
      _color = GMcolor::BlueViolet;
  }


  template <typename T, int n>
  inline
  VPoints<T,n>::VPoints( const VPoints<T,n>& v ) {}


  template <typename T, int n>
  inline
  VPoints<T,n>::~VPoints() {}


  template <typename T, int n>
  inline
  void VPoints<T,n>::display() {

    // Push GL Attribs
    glPushAttrib( GL_LIGHTING_BIT | GL_POINT_BIT );

    // Set Properties
    glDisable( GL_LIGHTING );
    Color( _color );
    glPointSize( _size );

    // Enable vertex array
    glEnableClientState( GL_VERTEX_ARRAY );

    if( n == 1 ) {

      // Give pointer to vertex data & draw
      glVertexPointer( 3, GL_FLOAT, 0, _n1(0).getPtr() );
      glDrawArrays( GL_POINTS, 0, _n1.getDim() );
    }
    else if( n == 2 ) {

      // Draw
      for( int i = 0; i < _n2.getDim1(); i++ ) {

        // Give pointer to vertex data and draw
        glVertexPointer( 3, GL_FLOAT, 3*sizeof(float), _n2(i)(0).getPtr() );
        glDrawArrays( GL_POINTS, 0, _n2(i).getDim() );
      }
    }

    // Disable vertex array
    glDisableClientState( GL_VERTEX_ARRAY );

    // Pop GL Attribs
    glPopAttrib();
  }


  template <typename T, int n>
  inline
  const Color& VPoints<T,n>::getColor() const {

    return _color;
  }


  template <typename T, int n>
  inline
  std::string VPoints<T,n>::getIdentity() const {

    return "VPoints";
  }


  template <typename T, int n>
  inline
  float VPoints<T,n>::getSize() const {

    return _size;
  }


  template <typename T, int n>
  inline
  void VPoints<T,n>::replot(
    DVector< DVector< Vector<T, 3> > >& p,
    int /*m*/, int /*d*/
  ) {

    _n1.setDim( p.getDim() );
    for( int i = 0; i < p.getDim(); i++ )
      _n1[i] = p[i][0];
  }


  template <typename T, int n>
  inline
  void VPoints<T,n>::replot(
    DMatrix< DMatrix< Vector<T, 3> > >& p,
    DMatrix< Vector<T, 3> >& /*normals*/,
    int /*m1*/, int /*m2*/, int /*d1*/, int /*d2*/
  ) {

    _n2.setDim( p.getDim1(), p.getDim2() );
    for( int i = 0; i < p.getDim1(); i++ )
      for( int j = 0; j < p.getDim2(); j++ )
        _n2[i][j] = p[i][j][0][0];
  }


  template <typename T, int n>
  inline
  void VPoints<T,n>::setColor( const Color& color ) {

    _color = color;
  }

  template <typename T, int n>
  inline
  void VPoints<T,n>::setSize( float size ) {

    _size = size;
  }

} // END namespace GMlib

