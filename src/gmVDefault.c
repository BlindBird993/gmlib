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
  VDefault<T,n>::VDefault() {}


  template <typename T, int n>
  inline
  VDefault<T,n>::VDefault( const VDefault<T,n>& copy ) : Visualizer<T,n>( copy ) {}


  template <typename T, int n>
  inline
  void VDefault<T,n>::display() {

    // Push GL Attributes
    glPushAttrib( GL_LIGHTING_BIT | GL_LINE_BIT ); {


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


      // Dimension dependant settings
      switch( n ) {
        case 1: {

          glLineWidth( this->_ref_n1->getLineWidth() );
        }
        break;

        case 2:
        default: {

          // Empty
        }
        break;
      }


      // Display; dependant on dynamic/static status
      if( this->_ref->isDynamic() ) {

        switch( n ) {
          case 1: {

            // Get Vertex data
            const DVector< Vector< float, 3 > > &v = this->_ref->getVerticesN1();

            // Enable the Vertex Array
            glEnableClientState( GL_VERTEX_ARRAY );

            // Give Pointer to Vertex Data
            glVertexPointer( 3, GL_FLOAT, 0, v(0).getPtr() );

            // Draw
            glDrawArrays( GL_LINE_STRIP, 0, v.getDim() );
          }
          break;

          case 2:
          default: {

            // Get Vertex, Texture and Material Data
            const DMatrix< Arrow<float,3> > &v = this->_ref->getVerticesN2();
            const DMatrix<Point<float,2> > &t = this->_ref->getTextureCoords();
            const Material &m = this->_ref->getMaterial();

            // Enable Vertex and Normal Array
            glEnableClientState( GL_VERTEX_ARRAY );
            glEnableClientState( GL_NORMAL_ARRAY );

            // If Valid Texture enable Texture Array
            if( m.getTextureID() )
              glEnableClientState( GL_TEXTURE_COORD_ARRAY );

            // Draw
            for( int i = 0; i < v.getDim1(); i++ ) {

              // Give Pointers to Vertex and Normal Data
              glVertexPointer( 3, GL_FLOAT, 2*3*sizeof(float), v(i)(0).getPos().getPtr() );
              glNormalPointer( GL_FLOAT, 2*3*sizeof(float), v(i)(0).getDir().getPtr() );

              // Give Pointer to Texture Data if any
              if( m.getTextureID() )
                glTexCoordPointer( 2, GL_FLOAT, 2*sizeof(float), ( t(i)(0) ).getPtr() );

              // Draw Strip
              glDrawArrays( GL_TRIANGLE_STRIP, 0, v(i).getDim() );
            }

            // Disable Client States
            glDisableClientState( GL_VERTEX_ARRAY );
            glDisableClientState( GL_NORMAL_ARRAY );
            glDisableClientState( GL_TEXTURE_COORD_ARRAY );
          }
          break;
        }
      }
      else {

        glCallList( this->_ref->getDisplayListIdx() );
      }

    // Pop GL Attributes
    } glPopAttrib();
  }


  template <typename T, int n>
  inline
  std::string VDefault<T,n>::getIdentity() const {

    return "Default Visualizer";
  }




}
