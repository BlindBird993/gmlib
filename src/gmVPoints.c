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

    _init();
  }


  template <typename T, int n>
  inline
  VPoints<T,n>::VPoints( const VPoints<T,n>& v ) {}


  template <typename T, int n>
  inline
  VPoints<T,n>::~VPoints() {

    if( _dlist )
      glDeleteLists( _dlist, 1 );
  }


  template <typename T, int n>
  inline
  void VPoints<T,n>::_init() {

      _dlist = 0;
      _size = 1.0;
      _color = GMcolor::BlueViolet;
  }



  template <typename T, int n>
  inline
  void VPoints<T,n>::display() {

    // Push GL Attribs
    glPushAttrib( GL_LIGHTING_BIT | GL_POINT_BIT );

    // Set Properties
    glDisable( GL_LIGHTING );
    glColor( _color );
    glPointSize( _size );


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
          glDrawArrays( GL_POINTS, 0, v.getDim() );
        }
        break;

        case 2:
        default: {

          // Get Vertex, Texture and Material Data
          const DMatrix< Arrow<float,3> > &v = this->_ref->getVerticesN2();

          // Enable Vertex and Normal Array
          glEnableClientState( GL_VERTEX_ARRAY );

          // Draw
          for( int i = 0; i < v.getDim1(); i++ ) {

            // Give Pointer to Vertex Data
            glVertexPointer( 3, GL_FLOAT, 2*3*sizeof(float), v(i)(0).getPos().getPtr() );

            // Draw
            glDrawArrays( GL_POINTS, 0, v(i).getDim() );
          }
        }
        break;
      }
    }
    else {

      glCallList( _dlist );
    }

    // Pop GL Attribs
    glPopAttrib();
  }


  template <typename T, int n>
  inline
  const GLColor& VPoints<T,n>::getColor() const {

    return _color;
  }


  template <typename T, int n>
  inline
  std::string VPoints<T,n>::getIdentity() const {

    return "Points Visualizer";
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
    int m, int d
  ) {

    if( !this->_ref->isDynamic() ) {

      if( _dlist )
        glDeleteLists( _dlist, 1 );

      _dlist = glGenLists(1);

      // Make displaylist for display of pointed curve
      glNewList( _dlist, GL_COMPILE ); {

        glBegin(GL_POINTS); {

          for( int i = 0; i < p.getDim(); i++ )
            glPoint( Point<float, 3>( (p[i][0]).toFloat() ) );

        }glEnd();
      }glEndList();
    }
  }


  template <typename T, int n>
  inline
  void VPoints<T,n>::replot(
    DMatrix< DMatrix< Vector<T, 3> > >& p,
    DMatrix< Vector<T, 3> >& normals,
    int m1, int m2, int d1, int d2
  ) {

    if( !this->_ref->isDynamic() ) {

      if( _dlist )
        glDeleteLists( _dlist, 1 );

      _dlist = glGenLists(1);

      // Make displaylist for display of pointed curve
      glNewList( _dlist, GL_COMPILE ); {

        glBegin(GL_POINTS); {

          for( int i = 0; i < p.getDim1(); i++ )
            for( int j = 0; j < p.getDim2(); j++ )
              glPoint( Point<float, 3>( (p[i][j][0][0]).toFloat() ) );

        }glEnd();
      }glEndList();
    }
  }


  template <typename T, int n>
  inline
  void VPoints<T,n>::setColor( const GLColor& color ) {

    _color = color;
  }

  template <typename T, int n>
  inline
  void VPoints<T,n>::setSize( float size ) {

    _size = size;
  }

}

