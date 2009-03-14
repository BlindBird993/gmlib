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



/*! \file gmVContours.c
 *
 *  VContours class function implementations.
 *
 *  \date   2009-01-27
 */

//
//#define GM_STREAM 1
//#include "gmStream.h"
//#include "gmColor.h"


namespace GMlib {

  template <typename T, int n>
  VContours<T,n>::VContours() {

    _init();
  }


  template <typename T, int n>
  inline
  VContours<T,n>::VContours( const VContours<T,n>& copy ) : Visualizer<T,n>( copy ) {
  }


  template <typename T, int n>
  inline
  VContours<T,n>::~VContours() {

    if( _dlist )
      glDeleteLists( _dlist, 1 );
  }


  template <typename T, int n>
  inline
  Color VContours<T,n>::_getColor( T d ) {

    // Find Index
    int idx;
    idx = d * (_colors.getSize()-1);
    if( idx == _colors.getSize()-1 ) idx--;
    if( (idx < 0) || (idx > _colors.getSize()-1) ) idx = 0;


    double local_d = (double( _colors.getSize()-1 ) * d) - idx;
    Color ret = _colors[idx].getInterpolatedHSV( local_d, _colors[idx+1] );

    return ret;
  }


  template <typename T, int n>
  inline
  T VContours<T,n>::_getCurvature( DVector< Vector<T,3> >& p ) {

    Vector<T,3> d1 = p[1];
    T a1= d1.getLength();

    if( a1 < T(1.0e-5) )
      return T(0);

    d1 /= a1;

    Vector<T,3> d2 = ( p[2] - ( d1 * p[2] ) * d1 ) / ( a1 * a1 );

    return d2.getLength();
  }


  template <typename T, int n>
  inline
  void VContours<T,n>::_init() {

    _dlist = 0;
    _mapping = GM_VISUALIZER_CONTOURS_MAP_X;
    _colors += GMcolor::Red;
    _colors += GMcolor::Blue;
  }


  template <typename T, int n>
  inline
  void VContours<T,n>::display() {

    // Push GL Attribs
    glPushAttrib( GL_LIGHTING_BIT | GL_POINT_BIT | GL_LINE_BIT );

    // Set Properties
    glDisable( GL_LIGHTING );


    // Display; dependant on dynamic/static status
    if( this->_ref->isDynamic() ) {

      switch( n ) {
        case 1: {

          // Get Vertex data
          const DVector< Vector< float, 3 > > &v = this->_ref->getVerticesN1();

          // Enable the Vertex Array
          glEnableClientState( GL_VERTEX_ARRAY );
          glEnableClientState( GL_COLOR_ARRAY );

          // Give Pointer to Vertex Data
          glColorPointer( 4, GL_UNSIGNED_BYTE, 0, &_color_pointer_n1[0] );
          glVertexPointer( 3, GL_FLOAT, 0, v(0).getPtr() );

          // Draw
          glDrawArrays( GL_LINE_STRIP, 0, v.getDim() );

          glDisableClientState( GL_VERTEX_ARRAY );
          glDisableClientState( GL_COLOR_ARRAY );
        }
        break;

        case 2:
        default: {

          // Get Vertex, Texture and Material Data
          const DMatrix< Arrow<float,3> > &v = this->_ref->getVerticesN2();

          // Enable Vertex and Normal Array
          glEnableClientState( GL_VERTEX_ARRAY );
          glEnableClientState( GL_COLOR_ARRAY );

          // Draw
          for( int i = 0; i < v.getDim1(); i++ ) {

            // Give Pointers to Vertex and Normal Data
            glVertexPointer( 3, GL_FLOAT, 2*3*sizeof(float), v(i)(0).getPos().getPtr() );
            glColorPointer( 4, GL_UNSIGNED_BYTE, 0, &_color_pointer_n2[0][0] );

            // Draw Strip
            glDrawArrays( GL_TRIANGLE_STRIP, 0, v(i).getDim() );
          }

          // Disable Client States
          glDisableClientState( GL_VERTEX_ARRAY );
          glDisableClientState( GL_COLOR_ARRAY );
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
  const Array<Color>& VContours<T,n>::getColors() const {

    return _colors;
  }


  template <typename T, int n>
  inline
  std::string VContours<T,n>::getIdentity() const {

    return "Contours Visualizer";
  }


  template <typename T, int n>
  inline
  GM_VISUALIZER_CONTOURS_MAP VContours<T,n>::getMapping() const {

    return _mapping;
  }


  template <typename T, int n>
  inline
  void VContours<T,n>::replot(
    DVector< DVector< Vector<T, 3> > >& p,
    int m, int d
  ) {



    // Color Countours
    DVector<Color> ccs;

    T min, max;
    T C; // Color Factor, (map to local)
    ccs.setDim( p.getDim() );
    switch( _mapping ) {

      case GM_VISUALIZER_CONTOURS_MAP_X:
      case GM_VISUALIZER_CONTOURS_MAP_Y:
      case GM_VISUALIZER_CONTOURS_MAP_Z:
      {

        int coord;
        switch( _mapping ) {
          case GM_VISUALIZER_CONTOURS_MAP_X:  coord = 0;  break;
          case GM_VISUALIZER_CONTOURS_MAP_Y:  coord = 1;  break;
          case GM_VISUALIZER_CONTOURS_MAP_Z:
          default:                            coord = 2;  break;
        }

        min = max = p[0][0][coord];

        // Extract all "height"-coords
        for( int i = 0; i < p.getDim(); i++ ) {

          const T value = p[i][0][coord];
          if( value < min )
            min = value;
          if( value > max )
            max = value;
        }

        // Correct interval
        if( max - min > 0 ) {
          C = 1.0f / (max - min);
          min /= (max - min);
        }
        else {
          C = min = T(0);
        }


        // Compute colors
        for( int i = 0; i < p.getDim(); i++ ) {

          const T value = p[i][0][coord];
          ccs[i] = _getColor( ( C * value ) - min );
        }
      }
      break;

      case GM_VISUALIZER_CONTOURS_MAP_T:
      case GM_VISUALIZER_CONTOURS_MAP_U:
      {
        for( int i = 0; i < p.getDim(); i++ )
          ccs[i] = _getColor( double(i) / double(p.getDim()-1) );
      }
      break;


      case GM_VISUALIZER_CONTOURS_MAP_SPEED:
      {
        // Init min/max
        min = max = (p[0][1]).getLength();

        // Extract all speed data
        for( int i = 0; i < p.getDim(); i++ ) {

          const T speed = (p[i][1]).getLength();
          if( speed < min )
            min = speed;
          if( speed > max )
            max = speed;
        }

        // Correct interval
        if( max - min > 0 ) {
          C = 1.0f / (max - min);
          min /= (max - min);
        }
        else {
          C = min = T(0);
        }

        // Compute interpolated color values
        for( int i = 0; i < p.getDim(); i++ ) {

          const T speed = (p[i][1]).getLength();
          ccs[i] = _getColor( ( C * speed ) - min );
        }
      }
      break;

      case GM_VISUALIZER_CONTOURS_MAP_CURVATURE:
      {
        // Init min/max
        min = max = _getCurvature(p[0]);

        // Extract all speed data
        for( int i = 0; i < p.getDim(); i++ ) {

          const T curvature = _getCurvature(p[i]);
          if( curvature < min )
            min = curvature;
          if( curvature > max )
            max = curvature;
        }

        // Correct interval
        if( (max-min) < 1e-5 ) {

          for( int i = 0; i < p.getDim(); i++ )
            ccs[i] == _colors[0];
        }
        else {
          C = 1.0f / (max-min);
          min /= (max-min);

          // Compute interpolated color values
          for( int i = 0; i < p.getDim(); i++ ) {

            const T curvature = _getCurvature(p[i]);
            ccs[i] = _getColor( ( C * curvature ) - min );
          }
        }
      }
      break;



      default:
      {
        // Compute colors
        for( int i = 0; i < p.getDim(); i++ )
          ccs[i] = _colors[0];
      }
      break;
    }


    // Create Vertex arrays ^^
    if( this->_ref->isDynamic() ) {

      _color_pointer_n1 = ccs;
    }
    else {

      if( _dlist )
        glDeleteLists( _dlist, 1 );

      _dlist = glGenLists(1);

      // Create the Curve Display List
      glNewList( _dlist, GL_COMPILE ); {
        glBegin(GL_LINE_STRIP); {

          for( int i = 0; i < p.getDim(); i++ ) {
            glColor( ccs[i] );
            glPoint( Point<float, 3>( p[i][0].toFloat() ) );
          }

        }glEnd();
      } glEndList();
    }
  }


  template <typename T, int n>
  inline
  void VContours<T,n>::replot(
    DMatrix< DMatrix< Vector<T, 3> > >& p,
    DMatrix< Vector<T, 3> >& normals,
    int m1, int m2, int d1, int d2
  ) {

    // Color Countours
    DMatrix<Color> ccs;

    T min, max;
    T C;
    ccs.setDim( p.getDim1(), p.getDim2() );
    switch( _mapping ) {



      case GM_VISUALIZER_CONTOURS_MAP_T:
      case GM_VISUALIZER_CONTOURS_MAP_U:
      {
        for( int i = 0; i < p.getDim1(); i++ )
          for( int j = 0; j < p.getDim2(); j++ )
            ccs[i][j] = _getColor( double(i) / double(p.getDim1()-1) );
      }
      break;
      case GM_VISUALIZER_CONTOURS_MAP_V:
      {
        for( int i = 0; i < p.getDim1(); i++ )
          for( int j = 0; j < p.getDim2(); j++ )
            ccs[i][j] = _getColor( double(j) / double(p.getDim2()-1) );
      }
      break;


      case GM_VISUALIZER_CONTOURS_MAP_X:
      case GM_VISUALIZER_CONTOURS_MAP_Y:
      case GM_VISUALIZER_CONTOURS_MAP_Z:
      {

        int coord;
        switch( _mapping ) {
          case GM_VISUALIZER_CONTOURS_MAP_X:  coord = 0;  break;
          case GM_VISUALIZER_CONTOURS_MAP_Y:  coord = 1;  break;
          case GM_VISUALIZER_CONTOURS_MAP_Z:
          default:                            coord = 2;  break;
        }

        min = max = p[0][0][0][0][coord];

        // Extract all "height"-coords
        for( int i = 0; i < p.getDim1(); i++ ) {
          for( int j = 0; j < p.getDim2(); j++ ) {

            const T value = p[i][j][0][0][coord];
            if( value < min )
              min = value;
            if( value > max )
              max = value;
          }
        }

        // Correct interval
        if( max - min > 0 ) {
          C = 1.0f / (max - min);
  //        ccs *= ( 1.0 / ( max - min ) );
          min /= (max - min);
        }
        else {
          C = min = T(0);
        }


        // Compute colors
        for( int i = 0; i < p.getDim1(); i++ ) {
          for( int j = 0; j < p.getDim2(); j++ ) {

            const T value = p[i][j][0][0][coord];
            ccs[i][j] = _getColor( ( C * value ) - min );
          }
        }
      }
      break;

      default:
      {
        // Compute colors
        for( int i = 0; i < p.getDim1(); i++ )
          for( int j = 0; j < p.getDim2(); j++ )
            ccs[i][j] = _colors[0];

      }
      break;
    }


    // Create Vertex arrays ^^
    if( this->_ref->isDynamic() ) {

      _color_pointer_n2.setDim( p.getDim1()-1, p.getDim2()*2 );

      for( int i = 0; i < p.getDim1()-1; i++ ) {
        for( int j = 0; j < p.getDim2(); j++ ) {

          _color_pointer_n2[i][ 2*j   ] = ccs[ i   ][j];
          _color_pointer_n2[i][ 2*j+1 ] = ccs[ i+1 ][j];
        }
      }
    }
    else {

      if( _dlist )
        glDeleteLists( _dlist, 1 );

      _dlist = glGenLists(1);

      // Create the Curve Display List
      glNewList( _dlist, GL_COMPILE ); {

        for( int i = 0; i < p.getDim1() - 1; i++ ) {
          glBegin(GL_TRIANGLE_STRIP); {
            for( int j = 0; j < p.getDim2(); j++ ) {

//              glTexCoord( Point2D<float>( (i) / float( p.getDim1() - 1 ), j / float( p.getDim2() - 1 ) ) );
              glColor( ccs[i][j] );
              glVertex( Arrow<float, 3>(
                Point3D<float>( ( p[i][j][0][0] ).toFloat() ),
                ( normals[i][j] ).getNormalized().toFloat()
              ) );

//              glTexCoord( Point2D<float>( (i+1) / float( p.getDim1() - 1 ), j / float( p.getDim2() - 1 ) ) );
              glColor( ccs[i+1][j] );
              glVertex( Arrow<float, 3>(
                Point3D<float>( ( p[i+1][j][0][0] ).toFloat() ),
                ( normals[i+1][j] ).getNormalized().toFloat()
              ) );
            }
          } glEnd();
        }
      } glEndList();
    }
  }


  template <typename T, int n>
  inline
  void VContours<T,n>::setColors( const Array<Color>& c ) {

    _colors = c;
  }


  template <typename T, int n>
  inline
  void VContours<T,n>::setMapping( GM_VISUALIZER_CONTOURS_MAP mapping ) {

    _mapping = mapping;
  }
}
