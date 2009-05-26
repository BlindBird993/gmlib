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



/*! \file gmDSurf.c
 *
 *  Implementation of the gmDSurf template class.
 *
 *  \date   2008-09-04
 */


// STL
#include <sstream>
#include <iomanip>

//#define GM_STREAM 1
//#include "gmOpenGL.h"

#include "gmPSurf.h"

namespace GMlib {


  template <typename T>
  inline
  DSurf<T>::DSurf() {

//    _p_ref = 0;
    _init();




    ////////////// PSURF ///////////////////

    _d1                             = -1;
    _d2                             = -1;
    _tr_u                           = T(0);
    _sc_u                           = T(1);
    _tr_v                           = T(0);
    _sc_v                           = T(1);
    //_setSam( s1, s2 );
  }


  template <typename T>
  inline
  DSurf<T>::DSurf( const DSurf<T>& copy ) : DParametrics<T,2>( copy ) {

//    _p_ref        = copy._p_ref;
    _no_der_u     = copy._no_der_u;
    _no_der_v     = copy._no_der_v;
    _no_samp_u    = copy._no_samp_u;
    _no_samp_v    = copy._no_samp_v;




    ////////////// PSURF ///////////////////

    _p                              = copy._p;
    _n                              = copy._n;
    _u                              = copy._u;
    _v                              = copy._v;
    _d1                             = copy._d1;
    _d2                             = copy._d2;
    _tr_u                           = copy._tr_u;
    _sc_u                           = copy._sc_u;
    _tr_v                           = copy._tr_v;
    _sc_v                           = copy._sc_v;
    _sam_p_u                        = copy._sam_p_u;
    _sam_p_v                        = copy._sam_p_v;
    _sam1                           = copy._sam1;
    _sam2                           = copy._sam2;
    _default_d                      = copy._default_d;
  }


//  template <typename T>
//  inline
//  DSurf<T>::DSurf( const PSurf<T,3>& copy ) : DParametrics<T,2>( copy ), _p_ref(copy) {
//
//    _init();
//  }
//
//
//  template <typename T>
//  inline
//  DSurf<T>::DSurf( PSurf<T,3>* copy ) : DParametrics<T,2>( copy ) {
//
//    _p_ref = copy;
//
//    _init();
//  }


  template <typename T>
  void DSurf<T>::_init() {

    _no_der_u = 1;
    _no_der_v = 1;
    _no_samp_u = 2;
    _no_samp_v = 2;

    this->_default_visualizer.set( this );
  }


  template <typename T>
  inline
  int DSurf<T>::getNoDerU() const {

    return _no_der_u;
  }


  template <typename T>
  inline
  int DSurf<T>::getNoDerV() const {

    return _no_der_v;
  }


  template <typename T>
  inline
  int DSurf<T>::getNoSampU() const {

    return _no_samp_u;
  }


  template <typename T>
  inline
  int DSurf<T>::getNoSampV() const {

    return _no_samp_v;
  }


//  template <typename T>
//  inline
//  PSurf<T,3>* DSurf<T>::getPSurf() {
//
//    return _p_ref;
//  }


  template <typename T>
  inline
  bool DSurf<T>::isClosestPoint( const Point<T,3>& q, T& u, T& v ) {

    T a11, a12, a21, a22, b1, b2;
    T du, dv, det;

    /*! \todo fix matrix */
    HqMatrix<float,3> invmat = this->_present;
    invmat.invertOrthoNormal();
    Point<T,3> p = invmat * q;  // Egentlig _present


    for(int i = 0; i < 20; i++ ) {

//      eval(u, v, 2, 2);
//      DMatrix< Vector<T,3> > &r = _p_ref->evaluateLocal( u, v, 2, 2 );
      DMatrix< Vector<T,3> > &r = evaluateLocal( u, v, 2, 2 );
      Vector<T,3> d = p-r[0][0];

      a11 = d*r[2][0] - r[1][0] * r[1][0];
      a12 = d*r[1][1] - r[1][0] * r[0][1];
      a21 = a12;
      a22 = d*r[0][2] - r[0][1] * r[0][1];

      b1  = -(d*r[1][0]);
      b2  = -(d*r[0][1]);

      det = a11*a22 - a12*a21;
      du  = (b1*a22 - a12*b2) / det;
      dv  = (a11*b2 - b1*a21) / det;
      u   += du;
      v   += dv;

      if(fabs(du) < 1e-6 && fabs(dv) < 1e-6)
        return true;
    }

    return false;
  }


  template <typename T>
  inline
  void DSurf<T>::localDisplay() {

    for( int i = 0; i < this->_visualizers.getSize(); i++ )
      this->_visualizers[i]->display();
  }


  template <typename T>
  inline
  void DSurf<T>::localSelect() {

    if( this->_dynamic ) {
      glEnableClientState( GL_VERTEX_ARRAY );

      for( int i = 0; i < this->_vertices_n2.getDim1(); i++ ) {

        glVertexPointer( 3, GL_FLOAT, 2*3*sizeof(float), ( this->_vertices_n2[i][0].getPos() ).getPtr() );
        glDrawArrays( GL_TRIANGLE_STRIP, 0, this->_vertices_n2[i].getDim() );
      }
    }
    else
      glCallList( this->_dlist + 1 );

    for( int i = 0; i < this->_visualizers.getSize(); i++ )
      this->_visualizers[i]->select();
  }


  template <typename T>
  inline
  void DSurf<T>::replot( int m1, int m2, bool dynamic, int d1, int d2 ) {

    // Check wheather or not PSurf is valid
//    if( !_p_ref )
//      return;

    // Correct sample domain
    if( m1 < 2 )
      m1 = _sam1.getDim();
    else
      _sam1.setDim( m1 );

    if( m2 < 2 )
      m2 = _sam2.getDim();
    else
      _sam2.setDim( m2 );

    // Set Properties
    this->_dynamic = dynamic;
    _no_der_u = d1;
    _no_der_v = d2;
    _no_samp_u = m1;
    _no_samp_v = m2;

    // Sample Positions and related Derivatives
    DMatrix< DMatrix< Vector<T, 3> > > p;
    resample(
      p, m1, m2, d1, d2,
      getStartPU(),
      getStartPV(),
      getEndPU(),
      getEndPV()
    );

    // Sample Normals
    DMatrix< Vector<T, 3> > normals;
    resampleNormals( p, normals );


    // Set The Surrounding Sphere
    setSurroundingSphere( p );

    // Clean up Display Lists
    if( this->_dlist ) {

      glDeleteLists( this->_dlist, 2 );
      this->_dlist = 0;
    }


    // Create Display lists or input data into vertex arrays...
    // Dependent on wheather or not the Surface is dynamic
    if( this->_dynamic ) {

      this->_vertices_n2.setDim( p.getDim1()-1, p.getDim2()*2 );

      for( int i = 0; i < p.getDim1()-1; i++ ) {
        for( int j = 0; j < p.getDim2(); j++ ) {

          this->_vertices_n2[i][ 2*j   ].setPos( p[ i   ][j][0][0].toFloat() );
          this->_vertices_n2[i][ 2*j   ].setDir( ( normals[i][j] ).getNormalized().toFloat() );

          this->_vertices_n2[i][ 2*j+1 ].setPos( p[ i+1 ][j][0][0].toFloat() );
          this->_vertices_n2[i][ 2*j+1 ].setDir( ( normals[i+1][j] ).getNormalized().toFloat() );
        }
      }


      if( this->_material.getTextureID() ) {

        this->_texture_coords.setDim( p.getDim1() - 1, p.getDim2() * 2 );

        for( int i = 0; i < p.getDim1() - 1; i++ ) {
          for( int j = 0; j < p.getDim2(); j++ ) {

            this->_texture_coords[i][ 2 * j       ] = Point2D<float>( i / float( p.getDim1() - 1 ), j / float( p.getDim2() - 1 ) );
            this->_texture_coords[i][ (2 * j) + 1 ] = Point2D<float>( (i+1) / float( p.getDim1()- 1 ), j / float( p.getDim2() - 1 ) );
          }
        }
      }

    }
    else {

      this->_dlist = glGenLists(2);


      // Create display list for Display
      // Display list no. 0 main list
      glNewList( this->_dlist, GL_COMPILE ); {

        if( this->_material.getTextureID() )
          this->_material.glSet();

        for( int i = 0; i < p.getDim1() - 1; i++ ) {

          glBegin(GL_TRIANGLE_STRIP); {

            for( int j = 0; j < p.getDim2(); j++ ) {

              glTexCoord( Point2D<float>( (i) / float( p.getDim1() - 1 ), j / float( p.getDim2() - 1 ) ) );
              glVertex( Arrow<float, 3>(
                Point3D<float>( ( p[i][j][0][0] ).toFloat() ),
                ( normals[i][j] ).getNormalized().toFloat()
              ) );

              glTexCoord( Point2D<float>( (i+1) / float( p.getDim1() - 1 ), j / float( p.getDim2() - 1 ) ) );
              glVertex( Arrow<float, 3>(
                Point3D<float>( ( p[i+1][j][0][0] ).toFloat() ),
                ( normals[i+1][j] ).getNormalized().toFloat()
              ) );
            }
          } glEnd();
        }
      } glEndList();

      // Create display list for Select
      // Display list no. 1
      glNewList(this->_dlist+1, GL_COMPILE); {

        for( int i = 0; i < p.getDim1() - 1 ; i++ ) {

          glBegin(GL_TRIANGLE_STRIP); {

            for( int j = 0; j < p.getDim2(); j++ ) {


              glPoint( Point3D<float>( ( p[i][j][0][0] ).toFloat() ) );
              glPoint( Point3D<float>( ( p[i+1][j][0][0] ).toFloat() ) );
            }
          } glEnd();
        }
      } glEndList();
    }


    // Replot Visaulizers
    for( int i = 0; i < this->_visualizers.getSize(); i++ )
      this->_visualizers[i]->replot( p, normals, m1, m2, d1, d2 );
  }


//  template <typename T>
//  inline
//  void DSurf<T>::replot( int m1, int m2, bool dynamic, int d1, int d2 ) {
//
//    // Check wheather or not PSurf is valid
//    if( !_p_ref )
//      return;
//
//    // Correct sample domain
//    if( m1 < 2 )
//      m1 = _p_ref->_sam1.getDim();
//    else
//      _p_ref->_sam1.setDim( m1 );
//
//    if( m2 < 2 )
//      m2 = _p_ref->_sam2.getDim();
//    else
//      _p_ref->_sam2.setDim( m2 );
//
//    // Set Properties
//    this->_dynamic = dynamic;
//    _no_der_u = d1;
//    _no_der_v = d2;
//    _no_samp_u = m1;
//    _no_samp_v = m2;
//
//    // Sample Positions and related Derivatives
//    DMatrix< DMatrix< Vector<T, 3> > > p;
//    _p_ref->resample(
//      p, m1, m2, d1, d2,
//      _p_ref->getStartPU(),
//      _p_ref->getStartPV(),
//      _p_ref->getEndPU(),
//      _p_ref->getEndPV()
//    );
//
//    // Sample Normals
//    DMatrix< Vector<T, 3> > normals;
//    _p_ref->resampleNormals( p, normals );
//
//
//    // Set The Surrounding Sphere
//    setSurroundingSphere( p );
//
//    // Clean up Display Lists
//    if( this->_dlist ) {
//
//      glDeleteLists( this->_dlist, 2 );
//      this->_dlist = 0;
//    }
//
//
//    // Create Display lists or input data into vertex arrays...
//    // Dependent on wheather or not the Surface is dynamic
//    if( this->_dynamic ) {
//
//      this->_vertices_n2.setDim( p.getDim1()-1, p.getDim2()*2 );
//
//      for( int i = 0; i < p.getDim1()-1; i++ ) {
//        for( int j = 0; j < p.getDim2(); j++ ) {
//
//          this->_vertices_n2[i][ 2*j   ].setPos( p[ i   ][j][0][0].toFloat() );
//          this->_vertices_n2[i][ 2*j   ].setDir( ( normals[i][j] ).getNormalized().toFloat() );
//
//          this->_vertices_n2[i][ 2*j+1 ].setPos( p[ i+1 ][j][0][0].toFloat() );
//          this->_vertices_n2[i][ 2*j+1 ].setDir( ( normals[i+1][j] ).getNormalized().toFloat() );
//        }
//      }
//
//
//      if( this->_material.getTextureID() ) {
//
//        this->_texture_coords.setDim( p.getDim1() - 1, p.getDim2() * 2 );
//
//        for( int i = 0; i < p.getDim1() - 1; i++ ) {
//          for( int j = 0; j < p.getDim2(); j++ ) {
//
//            this->_texture_coords[i][ 2 * j       ] = Point2D<float>( i / float( p.getDim1() - 1 ), j / float( p.getDim2() - 1 ) );
//            this->_texture_coords[i][ (2 * j) + 1 ] = Point2D<float>( (i+1) / float( p.getDim1()- 1 ), j / float( p.getDim2() - 1 ) );
//          }
//        }
//      }
//
//    }
//    else {
//
//      this->_dlist = glGenLists(2);
//
//
//      // Create display list for Display
//      // Display list no. 0 main list
//      glNewList( this->_dlist, GL_COMPILE ); {
//
//        if( this->_material.getTextureID() )
//          this->_material.glSet();
//
//        for( int i = 0; i < p.getDim1() - 1; i++ ) {
//
//          glBegin(GL_TRIANGLE_STRIP); {
//
//            for( int j = 0; j < p.getDim2(); j++ ) {
//
//              glTexCoord( Point2D<float>( (i) / float( p.getDim1() - 1 ), j / float( p.getDim2() - 1 ) ) );
//              glVertex( Arrow<float, 3>(
//                Point3D<float>( ( p[i][j][0][0] ).toFloat() ),
//                ( normals[i][j] ).getNormalized().toFloat()
//              ) );
//
//              glTexCoord( Point2D<float>( (i+1) / float( p.getDim1() - 1 ), j / float( p.getDim2() - 1 ) ) );
//              glVertex( Arrow<float, 3>(
//                Point3D<float>( ( p[i+1][j][0][0] ).toFloat() ),
//                ( normals[i+1][j] ).getNormalized().toFloat()
//              ) );
//            }
//          } glEnd();
//        }
//      } glEndList();
//
//      // Create display list for Select
//      // Display list no. 1
//      glNewList(this->_dlist+1, GL_COMPILE); {
//
//        for( int i = 0; i < p.getDim1() - 1 ; i++ ) {
//
//          glBegin(GL_TRIANGLE_STRIP); {
//
//            for( int j = 0; j < p.getDim2(); j++ ) {
//
//
//              glPoint( Point3D<float>( ( p[i][j][0][0] ).toFloat() ) );
//              glPoint( Point3D<float>( ( p[i+1][j][0][0] ).toFloat() ) );
//            }
//          } glEnd();
//        }
//      } glEndList();
//    }
//
//
//    // Replot Visaulizers
//    for( int i = 0; i < this->_visualizers.getSize(); i++ )
//      this->_visualizers[i]->replot( p, normals, m1, m2, d1, d2 );
//  }


//  template <typename T>
//  inline
//  void DSurf<T>::setPSurf( PSurf<T,3>* psurf ) {
//
//    _p_ref = psurf;
//    DParametrics<T,2>::setParametrics( _p_ref );
//  }


  template <typename T>
  inline
  void DSurf<T>::setSurroundingSphere( const DMatrix< DMatrix< Vector<T, 3> > >& p ) {

    Sphere<float, 3>  s( (p(0)(0)(0)(0)).toFloat() );
    s += Point<float,3>( p( p.getDim1()-1 )( p.getDim2()-1 )(0)(0));
    s += Point<float,3>( p( p.getDim1()/2 )( p.getDim2()/2 )(0)(0));
    s += Point<float,3>( p( p.getDim1()-1 )( 0             )(0)(0));
    s += Point<float,3>( p( 0             )( p.getDim2()-1 )(0)(0));
    s += Point<float,3>( p( p.getDim1()-1 )( p.getDim2()/2 )(0)(0));
    s += Point<float,3>( p( p.getDim1()/2 )( p.getDim2()-1 )(0)(0));
    s += Point<float,3>( p( 0             )( p.getDim2()/2 )(0)(0));
    s += Point<float,3>( p( p.getDim1()/2 )( 0             )(0)(0));
    DParametrics<T,2>::setSurroundingSphere(s);
  }












  //////////////////////// PSurf !!!!!!!!!!!!!! PSurf ////////////////////////
  //////////////////////// PSurf !!!!!!!!!!!!!! PSurf ////////////////////////
  //////////////////////// PSurf !!!!!!!!!!!!!! PSurf ////////////////////////
  //////////////////////// PSurf !!!!!!!!!!!!!! PSurf ////////////////////////
  //////////////////////// PSurf !!!!!!!!!!!!!! PSurf ////////////////////////
  //////////////////////// PSurf !!!!!!!!!!!!!! PSurf ////////////////////////
  //////////////////////// PSurf !!!!!!!!!!!!!! PSurf ////////////////////////
  //////////////////////// PSurf !!!!!!!!!!!!!! PSurf ////////////////////////
  //////////////////////// PSurf !!!!!!!!!!!!!! PSurf ////////////////////////
  //////////////////////// PSurf !!!!!!!!!!!!!! PSurf ////////////////////////
  //////////////////////// PSurf !!!!!!!!!!!!!! PSurf ////////////////////////
  //////////////////////// PSurf !!!!!!!!!!!!!! PSurf ////////////////////////
  //////////////////////// PSurf !!!!!!!!!!!!!! PSurf ////////////////////////
  //////////////////////// PSurf !!!!!!!!!!!!!! PSurf ////////////////////////
  //////////////////////// PSurf !!!!!!!!!!!!!! PSurf ////////////////////////
  //////////////////////// PSurf !!!!!!!!!!!!!! PSurf ////////////////////////























  template <typename T>
  inline
  void DSurf<T>::_eval( T u, T v, int d1, int d2 ) {

    if( !(d1 <= _d1 && d2 <=_d2 && u == _u && v == _v) ) {

      _u  = u;
      _v  = v;
      _d1 = d1;
      _d2 = d2;

      eval( shiftU(u), shiftV(v), d1, d2 );
    }
  }


  template <typename T>
  inline
  void DSurf<T>::_evalDerDD( DMatrix<DMatrix <Vector<T,3> > >& a, int d1, int d2, T du, T dv ) const {

    T one_over_du;
    T one_over_dv;



    // Handle all singular patial derivatives in v direction;
    // the case of v == 0
    for( int u = 1, v = 0; u <= d1; u++ ) {

      one_over_du = T(1) / ( pow( T(2) * du, T(u) ) );
  //    T one_over_du = T(1);

      // Handle all partial derivatives in v direction.
      for( int i = 1; i < a.getDim1() - 1; i++ ) {
        for( int j = 0; j < a.getDim2(); j++ ) {

          // Iterate throug each component of the "point"
          for( int k = 0; k < 3; k++ )
            a[i][j][u][v][k] = a[i+1][j][u-1][v][k] - a[i-1][j][u-1][v][k];

          a[i][j][u][v] *= one_over_du;
        }
      }




      if( isClosedU() ) {

        // Handle the edges, for partial derivatives of the dataset; i1 = 0, i2 = a.getDim1()-1
        for( int i1 = 0, i2 = a.getDim1() - 1, j = 0; j < a.getDim2(); j++ ) {

          // Iterate throug each component of the "point"
          for( int k = 0; k < 3; k++ ) {

            a[i1][j][u][v][k] = a[i2][j][u][v][k] = ( a[i1+1][j][u-1][v][k] - a[i2-1][j][u-1][v][k]   );
          }
          a[i1][j][u][v] = a[i2][j][u][v] *= one_over_du;
        }
      }
      else {
        // Handle the edges, for partial derivatives of the dataset; i1 = 0, i2 = a.getDim1()-1
        for( int i1 = 0, i2 = a.getDim1() - 1, j = 0; j < a.getDim2(); j++ ) {

          // Iterate throug each component of the "point"
          for( int k = 0; k < 3; k++ ) {

            a[i1][j][u][v][k] = a[i1+1][j][u-1][v][k] - ( a[i1][j][u-1][v][k] + ( a[i1][j][u-1][v][k] - a[i1+1][j][u-1][v][k] ) );
            a[i2][j][u][v][k] = ( a[i2][j][u-1][v][k] + ( a[i2][j][u-1][v][k] - a[i2-1][j][u-1][v][k] ) ) - a[i2][j][u-1][v][k];
          }
          a[i1][j][u][v] *= one_over_du;
          a[i2][j][u][v] *= one_over_du;
        }
      }
    }




    for( int u = 0; u <= d1; u++ ) {
      for( int v = 1; v <= d2; v++ ) {

        one_over_dv = T(1) / ( pow( T(2) * dv, T(v) ) );
  //      T one_over_dv = T(1);

        // Handle all partial derivatives in v direction.
        for( int i = 0; i < a.getDim1(); i++ ) {
          for( int j = 1; j < a.getDim2() - 1; j++ ) {

            // Iterate throug each component of the "point"
            for( int k = 0; k < 3; k++ )
              a[i][j][u][v][k] = a[i][j+1][u][v-1][k] - a[i][j-1][u][v-1][k];

            a[i][j][u][v] *= one_over_dv;
          }
        }

        if( isClosedV() ) {

          // Handle the edges, for partial derivatives of the dataset; j1 = 0, j2 = a.getDim2()-1
          for( int i = 0, j1 = 0, j2 = a.getDim2() - 1; i < a.getDim1(); i++ ) {

            // Iterate throug each component of the "point"
            for( int k = 0; k < 3; k++ ) {

              a[i][j1][u][v][k] = a[i][j2][u][v][k] = ( a[i][j1+1][u][v-1][k] - a[i][j2-1][u][v-1][k] );
            }
            a[i][j1][u][v] = a[i][j2][u][v] *= one_over_dv;
          }
        }
        else {

          // Handle the edges, for partial derivatives of the dataset; j1 = 0, j2 = a.getDim2()-1
          for( int i = 0, j1 = 0, j2 = a.getDim2() - 1; i < a.getDim1(); i++ ) {

            // Iterate throug each component of the "point"
            for( int k = 0; k < 3; k++ ) {

              a[i][j1][u][v][k] = a[i][j1+1][u][v-1][k] - ( a[i][j1][u][v-1][k] + ( a[i][j1][u][v-1][k] - a[i][j1+1][u][v-1][k] )   );
              a[i][j2][u][v][k] = ( a[i][j2][u][v-1][k] + ( a[i][j2][u][v-1][k] - a[i][j2-1][u][v-1][k] )  ) - a[i][j2-1][u][v-1][k];
            }
            a[i][j1][u][v] *= one_over_dv;
            a[i][j2][u][v] *= one_over_dv;
          }
        }
      }
    }
  }


  template <typename T>
  inline
  void DSurf<T>::_evalNormal() {

    _n = Vector3D<T>( _p(1)(0) ) ^ Vector3D<T>( _p(0)(1) );
  }


  template <typename T>
  inline
  void DSurf<T>::setDomainU( T start, T end ) {

    _sc_u  = (end - start) / (getEndPU() - getStartPU());
    _tr_u  = start - getStartPU();
  }


  template <typename T>
  inline
  void DSurf<T>::setDomainUScale( T sc ) {

    _sc_u = sc;
  }


  template <typename T>
  inline
  void DSurf<T>::setDomainUTrans( T tr ) {

    _tr_u = tr;
  }


  template <typename T>
  inline
  void DSurf<T>::setDomainV( T start, T end ) {

    _sc_v  = (end - start) / (getEndPV() - getStartPV());
    _tr_v  = start - getStartPV();
  }


  template <typename T>
  inline
  void DSurf<T>::setDomainVScale( T sc ) {

    _sc_v = sc;
  }


  template <typename T>
  inline
  void DSurf<T>::setDomainVTrans( T tr ) {

    _tr_v = tr;
  }


  template <typename T>
  inline
  T DSurf<T>::getParDeltaU() {

    return _sc_u * (getEndPU() - getStartPU());
  }


  template <typename T>
  inline
  T DSurf<T>::getParDeltaV() {

    return _sc_v * (getEndPV() - getStartPV());
  }


  template <typename T>
  inline
  T DSurf<T>::getParEndU() {

    return getParStartU() + getParDeltaU();
  }


  template <typename T>
  inline
  T DSurf<T>::getParEndV() {

    return getParStartV() + getParDeltaV();
  }


  template <typename T>
  inline
  T DSurf<T>::getParStartU() {

    return getStartPU() + _tr_u;
  }


  template <typename T>
  inline
  T DSurf<T>::getParStartV() {

    return getStartPV() + _tr_v;
  }


  template <typename T>
  inline
  int DSurf<T>::getSamU( int i ) {

    return _sam1[i];
  }


  template <typename T>
  inline
  int DSurf<T>::getSamV( int i ) {

    return _sam2[i];
  }

  template <typename T>
  inline
  int DSurf<T>::getDerU() {

    return _d1;
  }


  template <typename T>
  inline
  int DSurf<T>::getDerV() {

    return _d2;
  }


  template <typename T>
  inline
  void DSurf<T>::setEval( int d ) {

     _default_d  = d;
  }


  template <typename T>
  inline
  T DSurf<T>::shiftU( T u ) {

    return getStartPU() + _sc_u * ( u - getParStartU() );
  }


  template <typename T>
  inline
  T DSurf<T>::shiftV( T v ) {

    return getStartPV() + _sc_v * ( v - getParStartV() );
  }


  template <typename T>
  inline
  Point<T,3>& DSurf<T>::operator () ( T u, T v ) {

    _eval(u, v, _default_d, _default_d);
    return static_cast<Point<T,3> >(_p[0][0]);
  }


  template <typename T>
  inline
  Vector<T,3>& DSurf<T>::getDerU( T u, T v ) {

    _eval(u, v, 1, 0);
    return _p[1][0];
  }


  template <typename T>
  inline
  Vector<T,3>& DSurf<T>::getDerV( T u, T v ) {

    _eval(u, v, 0, 1);
    return _p[0][1];
  }


  template <typename T>
  inline
  Vector<T,3>& DSurf<T>::getDerUU( T u, T v ) {

    _eval(u, v, 2, 0);
    return _p[2][0];
  }


  template <typename T>
  inline
  Vector<T,3>& DSurf<T>::getDerVV( T u, T v ) {

    _eval(u, v, 0, 2);
    return _p[0][2];
  }


  template <typename T>
  inline
  Vector<T,3>& DSurf<T>::getDerUV( T u, T v ) {

    _eval(u, v, 2, 2);
    return _p[1][1];
  }


  template <typename T>
  inline
  std::string DSurf<T>::getIdentity() const {

    return "PSurf";
  }


  template <typename T>
  inline
  T DSurf<T>::getLocalMapping( T t, T ts, T tt, T te ) {

    return t;
  }


  template <typename T>
  inline
  Vector<T,3>& DSurf<T>::getNormal() {

    return _n;
  }


  template <typename T>
  inline
  DMatrix<Vector<T,3> >& DSurf<T>::evaluate( Point<T,2> p, int d ) {

    return evaluate( p[0], p[1], d, d);
  }


  template <typename T>
  inline
  DMatrix<Vector<T,3> >& DSurf<T>::evaluate( T u, T v, int d1, int d2 ) {

    static DMatrix<Vector<T,3> > p;
    p.setDim( d1+1, d2+1 );

    eval(u,v,d1,d2);

    p[0][0] = this->_present * (Point<T,3>)_p[0][0];

    for( int j = 1; j < p.getDim2(); j++ )
      p[0][j] = this->_present * (Vector<T,3>)_p[0][j];

    for( int i = 1; i < p.getDim1(); i++ )
      for( int j = 0; j < p.getDim2(); j++ )
        p[i][j] = this->_present * (Vector<T,3>)_p[i][j];

    return p;
  }


  template <typename T>
  inline
  DVector<Vector<T,3> > DSurf<T>::evaluateD( Point<T,2> p, int d ) {

    return evaluateD(p[0], p[1], d, d);
  }


  template <typename T>
  inline
  DVector<Vector<T,3> > DSurf<T>::evaluateD( T u, T v, int d1, int d2 ) {

    // Here we are coopying diagonal wise the matrix into an vector
    // One problem is if d1 is not equal d2.
    _eval(u, v, d1, d2);
    DVector<Vector<T,3> > p(_sum(d1, d2));
    int i,j;

    for(i = 0; i <= d1; i++) {
      for(j = 0; j<= min(i, d2); j++)	{
        p += _p[i-j][j];
      }
    }

    // Origin --> for(;i <= max(d1, d2); i++)
    for(i = 0; i <= max(d1, d2); i++) {
      for(j = i-d1; j <= min(i, d2); j++) {
        p += _p[i-j][j];
      }
    }

    return p;
  }


  template <typename T>
  inline
  DMatrix<Vector<T,3> >& DSurf<T>::evaluateLocal( Point<T,2> p, int d ) {

    return evaluateLocal( p[0], p[1], d, d);
  }


  template <typename T>
  inline
  DMatrix<Vector<T,3> >& DSurf<T>::evaluateLocal( T u, T v, int d1, int d2 ) {

    _eval(u, v, d1, d2);
    _evalNormal();
    return _p;
  }


  template <typename T>
  inline
  DMatrix<Vector<T,3> >& DSurf<T>::evaluateParent( Point<T,2> p, int d ) {

    return evaluate( p[0], p[1], d, d);
  }


  template <typename T>
  inline
  DMatrix<Vector<T,3> >& DSurf<T>::evaluateParent( T u, T v, int d1, int d2 ) {

    static DMatrix<Vector<T,3> > p;
    p.setDim( d1+1, d2+1 );

    eval(u,v,d1,d2);

    p[0][0] = this->_matrix * (Point<T,3>)_p[0][0];

    for( int j = 1; j < p.getDim2(); j++ )
      p[0][j] = this->_matrix * (Vector<T,3>)_p[0][j];

    for( int i = 1; i < p.getDim1(); i++ )
      for( int j = 0; j < p.getDim2(); j++ )
        p[i][j] = this->_matrix * (Vector<T,3>)_p[i][j];

    return p;
  }


  template <typename T>
  inline
  T DSurf<T>::getCurvatureGauss( T u, T v ) {

    _eval(u, v, 2, 2);
    UnitVector<T,3> N   = Vector3D<T>(_p[1][0])^_p[0][1];
    Vector<T,3>		  du  = _p[1][0];
    Vector<T,3>		  dv  = _p[0][1];
    Vector<T,3>		  duu = _p[2][0];
    Vector<T,3>		  duv = _p[1][1];
    Vector<T,3>		  dvv = _p[0][2];

//    UnitVector<T,3> N   = normal(u, v);	    // _p[0][1]^_p[1][0];
//    Vector<T,3>		  du  = getDerU(u, v);	  // _p[0][1];
//    Vector<T,3>		  dv  = getDerV(u, v);	  // _p[1][0];
//    Vector<T,3>		  duu = getDerUU(u, v);	  // _p[0][2];
//    Vector<T,3>		  duv = getDerUV(u, v);	  // _p[1][1];
//    Vector<T,3>		  dvv = getDerVV(u, v);	  // _p[2][0];

    T E = du  * du;
    T F = du  * dv;
    T G = dv  * dv;
    T e = N   * duu;
    T f = N   * duv;
    T g = N   * dvv;

    return (e*g - f*f) / (E*G - F*F);
  }


  template <typename T>
  inline
  T DSurf<T>::getCurvatureMean( T u, T v ) {

    _eval(u,v,2,2);
    UnitVector<T,3> N   = Vector3D<T>(_p[1][0])^_p[0][1];
    Vector<T,3>		  du  = _p[1][0];
    Vector<T,3>		  dv  = _p[0][1];
    Vector<T,3>		  duu = _p[2][0];
    Vector<T,3>		  duv = _p[1][1];
    Vector<T,3>		  dvv = _p[0][2];

    T E = du  * du;
    T F = du  * dv;
    T G = dv  * dv;
    T e = N   * duu;
    T f = N   * duv;
    T g = N   * dvv;

    return 0.5 * (e*G - 2 * (f*F) + g*E) / (E*G - F*F);
  }


//  template <typename T>
//  inline
//  void DSurf<T>::estimateClpPar( const Point<T,3>& p, T& u, T& v ) {
//  }


  template <typename T>
  inline
  PSurf<T,3>* DSurf<T>::split( T t, int uv ) {

    return 0;
  }


  template <typename T>
  inline
  void DSurf<T>::resampleNormals( const DMatrix<DMatrix<Vector<T, 3> > > &sample, DMatrix<Vector<T, 3> > &normals ) const {

    normals.setDim( sample.getDim1(), sample.getDim2() );

//    cout << "Generating Normals:" << endl;

    for( int i = 0; i < sample.getDim1(); i++ ) {
      for( int j = 0; j < sample.getDim2(); j++ ) {
        normals[i][j] = Vector3D<T>( sample(i)(j)(1)(0) ) ^ sample(i)(j)(0)(1);
//        normals[i][j] = Vector3D<T>( sample(i)(j)(0)(1) ) ^ sample(i)(j)(1)(0);
  //
  //      cout << "\t[" << i << ", " << j << "] (";
  //      for( int k = 0; k < n; k++ ){
  //
  //        cout << setw(3) << sample(i)(j)(1)(0)(k);
  //        if( k != n-1 )
  //          cout << ", ";
  //      }
  //      cout << ") u'";
  //      cout << endl;
  //
  //      cout << "\t[" << i << ", " << j << "] (";
  //      for( int k = 0; k < n; k++ ){
  //
  //        cout << setw(3) << sample(i)(j)(0)(1)(k);
  //        if( k != n-1 )
  //          cout << ", ";
  //      }
  //      cout << ") v'";
  //      cout << endl;
  //
  //      cout << "\t[" << i << ", " << j << "] (";
  //      for( int k = 0; k < n; k++ ){
  //
  //        cout << setw(3) << normals[i][j][k];
  //        if( k != n-1 )
  //          cout << ", ";
  //      }
  //      cout << ") norm";
  //      cout << endl << endl;
      }
  //      cout << endl;
    }
  }


  template <typename T>
  inline
  void DSurf<T>::resample(
    DMatrix< DMatrix < Vector<T,3> > >& a,
    int m1,
    int m2,
    int d1,
    int d2,
    T s_u,
    T s_v,
    T e_u,
    T e_v
  ) {

    T du = (e_u-s_u)/(m1-1);
    T dv = (e_v-s_v)/(m2-1);

    _p.setDim( d1 + 1, d2 + 1 );
    a.setDim(m1, m2);

    for(int i=0; i<m1-1; i++) {

      T u = s_u + i*du;
      for(int j=0;j<m2-1;j++) {

        eval(u, s_v + j*dv, d1, d2 );
        a[i][j] = _p;
      }

      eval(u, e_v, d1, d2, false, true);
      a[i][m2-1] = _p;
    }

    for(int j=0;j<m2-1;j++) {

      eval(e_u, s_v + j*dv, d1, d2, true, false);
      a[m1-1][j] = _p;
    }

    eval(e_u, e_v, d1, d2, true, true);
    a[m1-1][m2-1] = _p;

    switch( this->_dm ) {
      case GM_DERIVATION_EXPLICIT:
        // Do nothing, evaluator algorithms for explicite calculation of derivatives
        // should be defined in the eval( ... ) function enclosed by
        // if( this->_derivation_method == this->EXPLICIT ) { ... eval algorithms for derivatives ... }
        break;

      case GM_DERIVATION_DD:
      default:
        _evalDerDD( a, d1, d2, du, dv );
        break;
    }
  }


  template <typename T>
  inline
  void DSurf<T>::resample(
    DMatrix<DMatrix <DMatrix <Vector<T,3> > > >	& a,
    int m1,
    int m2,
    int d1,
    int d2
  ) {

//    if(m1>0)
//    for(int i=0; i< _sam1.getDim(); i++)
//      _sam1[i]= max(2,int(0.5+(m1*(_sam_p_u[i+1] - _sam_p_u[i]))/(_sam_p_u.back() - _sam_p_u[0])));
//    if(m2>0)
//    for(int i=0; i< _sam2.getDim(); i++)
//      _sam2[i]= max(2,int(0.5+(m2*(_sam_p_v[i+1] - _sam_p_v[i]))/(_sam_p_v.back() - _sam_p_v[0])));
//
//    a.setDim(_sam1.getDim(),_sam2.getDim());
//
//    for(int i = 0; i < a.getDim1(); i++)
//      for(int j = 0; j < a.getDim2(); j++)
//        resample(a[i][j],_sam1[i],_sam2[j], d1, d2, _sam_p_u[i],_sam_p_v[j],_sam_p_u[i+1],_sam_p_v[j+1]);
  }
}
