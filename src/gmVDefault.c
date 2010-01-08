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



/*! \file gmVDefault.c
 *
 *  VDefault class function implementations.
 *
 *  \date   2009-01-27
 */


namespace GMlib {

  template <typename T, int n>
  inline
  VDefault<T,n>::VDefault() {

    _blend_sfactor = GL_SRC_ALPHA;
    _blend_dfactor = GL_ONE_MINUS_SRC_ALPHA;
  }


  template <typename T, int n>
  inline
  VDefault<T,n>::VDefault( const VDefault<T,n>& copy ) : Visualizer<T,n>( copy ) {

    _blend_sfactor = copy._blend_sfactor;
    _blend_dfactor = copy._blend_dfactor;
  }


  template <typename T, int n>
  inline
  void VDefault<T,n>::display() {

    // Push GL Attributes
    glPushAttrib( GL_LIGHTING_BIT | GL_LINE_BIT | GL_TEXTURE_BIT ); {


      // Handle lighting and set Color/Material accordingly
      if( this->_ref->isLighted() ) {

        glEnable( GL_LIGHTING );

        // Get Material Data
        const Material &m = this->_ref->getMaterial();
        m.glSet();
      }
      else {

        glDisable( GL_LIGHTING );

        // Get Color Data
        const GLColor &c = this->_ref->getColor();
        c.glSet();
      }


      // Handle Opacity/Transparency
      if( this->_ref->isOpaque() ) {

        glBlendFunc(_blend_sfactor, _blend_dfactor);
      }


      // Render dependent on dimension
      if( n == 1 ) {

        // GL States
        glLineWidth( this->_ref_n1->getLineWidth() );

        // Enable vertex array
        glEnableClientState( GL_VERTEX_ARRAY );

        // Give Pointer to Vertex Data
        glVertexPointer( 3, GL_FLOAT, 0, _n1(0).getPtr() );

        // Draw
        glDrawArrays( GL_LINE_STRIP, 0, _n1.getDim() );

        // Disable vertex array
        glDisableClientState( GL_VERTEX_ARRAY );
      }
      else if( n == 2 ) {

        // Material
        const Material &m = this->_ref->getMaterial();

        // Enable Vertex and Normal Array
        glEnableClientState( GL_VERTEX_ARRAY );
        glEnableClientState( GL_NORMAL_ARRAY );

        // If Valid Texture enable Texture Array
        if( m.getTextureID() )
          glEnableClientState( GL_TEXTURE_COORD_ARRAY );

        // Draw
        for( int i = 0; i < _n2.getDim1(); i++ ) {

          // Give Pointers to Vertex and Normal Data
          glVertexPointer( 3, GL_FLOAT, 2*3*sizeof(float), _n2(i)(0).getPos().getPtr() );
          glNormalPointer( GL_FLOAT, 2*3*sizeof(float), _n2(i)(0).getDir().getPtr() );

          // Give Pointer to Texture Data if any
          if( m.getTextureID() )
            glTexCoordPointer( 2, GL_FLOAT, 2*sizeof(float), ( _t2(i)(0) ).getPtr() );

          // Draw Strip
          glDrawArrays( GL_TRIANGLE_STRIP, 0, _n2(i).getDim() );
        }

        // Disable Client States
        glDisableClientState( GL_VERTEX_ARRAY );
        glDisableClientState( GL_NORMAL_ARRAY );
        glDisableClientState( GL_TEXTURE_COORD_ARRAY );
      }

    // Pop GL Attributes
    } glPopAttrib();
  }


  template <typename T, int n>
  inline
  std::string VDefault<T,n>::getIdentity() const {

    return "VDefault";
  }


  template <typename T, int n>
  inline
  void VDefault<T,n>::replot(
    DVector< DVector< Vector<T, 3> > >& p,
    int /*m*/, int /*d*/
  ) {

    // Compute vertices
    _n1.setDim( p.getDim() );
    for( int i = 0; i < p.getDim(); i++ )
      _n1[i] = p[i][0].toFloat();
  }


  template <typename T, int n>
  inline
  void VDefault<T,n>::replot(
    DMatrix< DMatrix< Vector<T, 3> > >& p,
    DMatrix< Vector<T, 3> >& normals,
    int /*m1*/, int /*m2*/, int /*d1*/, int /*d2*/
  ) {

    // Compute vertices and normals
    _n2.setDim( p.getDim1()-1, p.getDim2()*2 );
    for( int i = 0; i < p.getDim1()-1; i++ ) {
      for( int j = 0; j < p.getDim2(); j++ ) {

        _n2[i][ 2*j   ].setPos( p[ i   ][j][0][0].toFloat() );
        _n2[i][ 2*j   ].setDir( ( normals[i][j] ).getNormalized().toFloat() );

        _n2[i][ 2*j+1 ].setPos( p[ i+1 ][j][0][0].toFloat() );
        _n2[i][ 2*j+1 ].setDir( ( normals[i+1][j] ).getNormalized().toFloat() );
      }
    }

    // Compute texture coordinates.
    _t2.setDim( p.getDim1() - 1, p.getDim2() * 2 );
    for( int i = 0; i < p.getDim1() - 1; i++ ) {
      for( int j = 0; j < p.getDim2(); j++ ) {

        _t2[i][ 2 * j       ] = Point2D<float>( i / float( p.getDim1() - 1 ), j / float( p.getDim2() - 1 ) );
        _t2[i][ (2 * j) + 1 ] = Point2D<float>( (i+1) / float( p.getDim1()- 1 ), j / float( p.getDim2() - 1 ) );
      }
    }
  }


  template <typename T, int n>
  inline
  void VDefault<T,n>::select() {

    glEnableClientState( GL_VERTEX_ARRAY );

    if( n == 1 ) {

      glVertexPointer( 3, GL_FLOAT, 3*sizeof(float), _n1[0].getPtr() );
      glDrawArrays( GL_LINE_STRIP, 0, _n1.getDim() );
    }
    else if( n == 2 ) {

      for( int i = 0; i < _n2.getDim1(); i++ ) {

        glVertexPointer( 3, GL_FLOAT, 2*3*sizeof(float), ( _n2[i][0].getPos() ).getPtr() );
        glDrawArrays( GL_TRIANGLE_STRIP, 0, _n2[i].getDim() );
      }
    }

    glDisableClientState( GL_VERTEX_ARRAY );
  }


  template <typename T, int n>
  void VDefault<T,n>::setGLBlendFunc( GLenum sfactor, GLenum dfactor ) {

    _blend_sfactor = sfactor;
    _blend_dfactor = dfactor;
  }

} // END namespace GMlib
