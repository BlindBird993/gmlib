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




namespace GMlib {


  template <typename T, int n>
  inline
  VDerivatives<T,n>::VDerivatives() {

    _color = GMcolor::Green;
    _u = 1;
    _v = 1;
    _size_mode = GM_VISUALIZER_DERIVATIVES_NORMALIZED;
    _size = 1.0;
  }


  template <typename T, int n>
  inline
  VDerivatives<T,n>::VDerivatives( const VDerivatives<T,n>& copy ) : Visualizer<T,n>( copy ) {}


  template <typename T, int n>
  inline
  VDerivatives<T,n>::~VDerivatives() {}


  template <typename T, int n>
  inline
  void VDerivatives<T,n>::display() {

    // Push GL Attributes
    glPushAttrib( GL_LINE_BIT | GL_LIGHTING_BIT );

    // Set Properties
    glDisable( GL_LIGHTING );
    glColor( _color );

    // Enable Vertex and Normal Array
    glEnableClientState( GL_VERTEX_ARRAY );

    if( n == 1 ) {

      // Give pointer to beginning of vertex data and draw derivatives
      glVertexPointer( 3, GL_FLOAT, 3 * sizeof(float), _n1(0).getPos().getPtr() );
      glDrawArrays( GL_LINES, 0, _n1.getDim()*2 );
    }
    else if( n == 2 ) {

      // Draw
      for( int i = 0; i < _n2.getDim1(); i++ ) {

        // Give pointer to beginning of vertex data and draw derivatives
        glVertexPointer( 3, GL_FLOAT, 3 * sizeof(float), _n2(i)(0).getPos().getPtr() );
        glDrawArrays( GL_LINES, 0, _n2(i).getDim()*2 );
      }
    }

    // Disable Client States
    glDisableClientState( GL_VERTEX_ARRAY );

    // Pop GL Attributes
    glPopAttrib();
  }


  template <typename T, int n>
  inline
  const Color& VDerivatives<T,n>::getColor() const {

    return _color;
  }


  template <typename T, int n>
  inline
  std::string VDerivatives<T,n>::getIdentity() const {

    return "VDerivatives";
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

    int der = 0;
    if( (_u >= 0) || (_u <= p[0].getDim()-1) )
      der = _u;

    _n1.setDim( p.getDim() );
    for( int i = 0; i < p.getDim(); i++ ) {

      switch( _size_mode ) {
        case GM_VISUALIZER_DERIVATIVES_PERCENT:
          _n1[i] = Arrow<float,3>( p[i][0].toFloat(), ( p[i][0] + ( p[i][der] * _size ) ).toFloat() );
          break;

        case GM_VISUALIZER_DERIVATIVES_VERTEX:
          _n1[i] = Arrow<float,3>( p[i][0].toFloat(), ( p[i][0] + ( p[i][der].getNormalized() * _size ) ).toFloat() );
          break;

        case GM_VISUALIZER_DERIVATIVES_NORMALIZED:
        default:
          _n1[i] = Arrow<float,3>( p[i][0].toFloat(), ( p[i][0] + p[i][der].getNormalized() ).toFloat() );
          break;
      }
    }
  }


  template <typename T, int n>
  inline
  void VDerivatives<T,n>::replot(
    DMatrix< DMatrix< Vector<T, 3> > >& p,
    DMatrix< Vector<T, 3> >& /*normals*/,
    int /*m1*/, int /*m2*/, int /*d1*/, int /*d2*/
  ) {

    int der_u = 0;
    int der_v = 0;

    if( (_u >= 0) || (_u <= p[0][0].getDim1()-1) )
      der_u = _u;

    if( (_v >= 0) || (_v <= p[0][0].getDim2()-1) )
      der_v = _v;

    _n2.setDim( p.getDim1(), p.getDim2() );
    for( int i = 0; i < p.getDim1(); i++ ) {
      for( int j = 0; j < p.getDim2(); j++ ) {

        switch( _size_mode ) {
          case GM_VISUALIZER_DERIVATIVES_PERCENT:
            _n2[i][j] = Arrow<float,3>( p[i][j][0][0].toFloat(), ( p[i][j][0][0] + ( p[i][j][der_u][der_v] * _size ) ).toFloat() );
            break;

          case GM_VISUALIZER_DERIVATIVES_VERTEX:
            _n2[i][j] = Arrow<float,3>( p[i][j][0][0].toFloat(), ( p[i][j][0][0] + ( p[i][j][der_u][der_v].getNormalized() * _size ) ).toFloat() );
            break;

          case GM_VISUALIZER_DERIVATIVES_NORMALIZED:
          default:
            _n2[i][j] = Arrow<float,3>( p[i][j][0][0].toFloat(), ( p[i][j][0][0] + p[i][j][der_u][der_v].getNormalized() ).toFloat() );
            break;
        }
      }
    }
  }


  template <typename T, int n>
  inline
  void VDerivatives<T,n>::setColor( const Color& color ) {

    _color = color;
  }


  template <typename T, int n>
  inline
  void VDerivatives<T,n>::setDerivative( int u, int v ) {

    _u = u;
    _v = v;
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
}
