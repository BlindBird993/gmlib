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



namespace GMlib {



  template <typename T, int n>
  inline
  VNormals<T,n>::VNormals() {

    _color = GMcolor::Black;
    _size = 1.0;
  }


  template <typename T, int n>
  inline
  VNormals<T,n>::VNormals( const VNormals<T,n>& copy ) : Visualizer<T,n>( copy ) {}


  template <typename T, int n>
  inline
  VNormals<T,n>::~VNormals() {}


  template <typename T, int n>
  inline
  void VNormals<T,n>::display() {

    // Push GL Attributes
    glPushAttrib( GL_LINE_BIT | GL_LIGHTING_BIT );

    // Set Properties
    glDisable( GL_LIGHTING );
    glColor( _color );

    // Enable vertex array
    glEnableClientState( GL_VERTEX_ARRAY );

    if( n == 1 ) {
    }
    else if( n == 2 ) {

      // Draw
      for( int i = 0; i < _n2.getDim1(); i++ ) {

        // Give pointer to vertex data and draw
        glVertexPointer( 3, GL_FLOAT, 3*sizeof(float), _n2(i)(0).getPos().getPtr() );
        glDrawArrays( GL_LINES, 0, _n2(i).getDim()*2 );
      }
    }

    // Disable vertex array
    glDisableClientState( GL_VERTEX_ARRAY );

    // Pop GL Attributes
    glPopAttrib();
  }


  template <typename T, int n>
  inline
  const Color& VNormals<T,n>::getColor() const {

    return _color;
  }


  template <typename T, int n>
  inline
  std::string VNormals<T,n>::getIdentity() const {

    return "VNormals";
  }


  template <typename T, int n>
  inline
  double VNormals<T,n>::getSize() const {

    return _size;
  }


  template <typename T, int n>
  inline
  void VNormals<T,n>::replot(
    DVector< DVector< Vector<T, 3> > >& p,
    int /*m*/, int /*d*/
  ) {

    _n1.setDim( p.getDim() );
  }


  template <typename T, int n>
  void VNormals<T,n>::replot(
    DMatrix< DMatrix< Vector<T, 3> > >& p,
    DMatrix< Vector<T, 3> >& normals,
    int /*m1*/, int /*m2*/, int /*d1*/, int /*d2*/
  ) {

    _n2.setDim( normals.getDim1(), normals.getDim2() );
    for( int i = 0; i < normals.getDim1(); i++ )
      for( int j = 0; j < normals.getDim2(); j++ )
        _n2[i][j] = Arrow<float,3>(
          p[i][j][0][0].toFloat(),
          ( p[i][j][0][0] + ( normals[i][j].getNormalized() * _size ) ).toFloat()
        );
  }


  template <typename T, int n>
  void VNormals<T,n>::setColor( const Color& color ) {

    _color = color;
  }


  template <typename T, int n>
  inline
  void VNormals<T,n>::setSize( double size ) {

    _size = size;
  }

} // END namespace GMlib

