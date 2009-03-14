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


//#define GM_STREAM 1
//#include "gmOpenGL.h"

#include "gmPSurf.h"

namespace GMlib {


  template <typename T>
  inline
  DSurf<T>::DSurf() {

    _p_ref = 0;
    _init();
  }


  template <typename T>
  inline
  DSurf<T>::DSurf( const DSurf<T>& copy ) : DParametrics<T,2>( copy ) {

    _p_ref        = copy._p_ref;
    _no_der_u     = copy._no_der_u;
    _no_der_v     = copy._no_der_v;
    _no_samp_u    = copy._no_samp_u;
    _no_samp_v    = copy._no_samp_v;
  }


  template <typename T>
  inline
  DSurf<T>::DSurf( const PSurf<T,3>& copy ) : DParametrics<T,2>( copy ), _p_ref(copy) {

    _init();
  }


  template <typename T>
  inline
  DSurf<T>::DSurf( PSurf<T,3>* copy ) : DParametrics<T,2>( copy ) {

    _p_ref = copy;

    _init();
  }


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
  DMatrix< Vector<T, 3> > DSurf<T>::evaluate( T u, T v, int d1, int d2 ) {

    DMatrix<Vector<T,3> > q = _p_ref->evaluateLocal( u, v, d1, d2 );

    DMatrix<Vector<T,3> > p( d1+1, d2+1 );

    Vector<float,3> tmp;

    for( int i = 0; i < p.getDim1(); i++ ) {
      for( int j = 0; j < p.getDim2(); j++ ) {

        if( i==0 && j==0 ) {
          tmp = this->_present * (Point<float,3>)q[0][0].toFloat();
          for( int k = 0; k < 3; k++ )
            p[i][j][k] = tmp[k];
        }
        else {
          tmp = this->_present * (Vector<float,3>)q[i][j].toFloat();

          for( int k = 0; k < 3; k++ )
            p[i][j][k] = tmp[k];
        }
      }
    }
    return p;
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


  template <typename T>
  inline
  PSurf<T,3>* DSurf<T>::getPSurf() {

    return _p_ref;
  }


  template <typename T>
  inline
  bool DSurf<T>::isClosestPoint( const Point<T,3>& q, T& u, T& v ) {

    T a11, a12, a21, a22, b1, b2;
    T du, dv, det;
    Point<T,3> p = this->_present.getInverse() * q;  // Egentlig _present


    for(int i = 0; i < 20; i++ ) {

//      eval(u, v, 2, 2);
      DMatrix< Vector<T,3> > &r = _p_ref->evaluateLocal( u, v, 2, 2 );
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
    if( !_p_ref )
      return;

    // Correct sample domain
    if( m1 < 2 )
      m1 = _p_ref->_sam1.getDim();
    else
      _p_ref->_sam1.setDim( m1 );

    if( m2 < 2 )
      m2 = _p_ref->_sam2.getDim();
    else
      _p_ref->_sam2.setDim( m2 );

    // Set Properties
    this->_dynamic = dynamic;
    _no_der_u = d1;
    _no_der_v = d2;
    _no_samp_u = m1;
    _no_samp_v = m2;

    // Sample Positions and related Derivatives
    DMatrix< DMatrix< Vector<T, 3> > > p;
    _p_ref->resample(
      p, m1, m2, d1, d2,
      _p_ref->getStartPU(),
      _p_ref->getStartPV(),
      _p_ref->getEndPU(),
      _p_ref->getEndPV()
    );

    // Sample Normals
    DMatrix< Vector<T, 3> > normals;
    _p_ref->resampleNormals( p, normals );


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


  template <typename T>
  inline
  void DSurf<T>::setPSurf( PSurf<T,3>* psurf ) {

    _p_ref = psurf;
    DParametrics<T,2>::setParametrics( _p_ref );
  }


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

}
