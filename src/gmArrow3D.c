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



/*! \file gmArrow3D.c
 *  \brief Inline Arrow3D class implementations
 *
 *  Inline implementation of the Arrow3D class.
 *
 *  \date   2009-03-06
 */


#include "gmPoint3D.h"
#include "gmOpenGL.h"

namespace GMlib {


  inline
  Arrow3D::Arrow3D( const Arrow<float,3>& a, int m ) : Arrow<float,3>( a ) {

    _m = m;
    _l = a.getDir().getLength();  // Length
    _r = _l * 0.1f;               // Radius
    _h = 0.29f;                   // Head Size factor
    _lw = 1.8f;                   // Line Width factor

  }

  inline
  void Arrow3D::display() {

    const Point<float,3> pos = Vector3D<float>( 0.0f, 0.0f, getDir().getLength() );
    const Vector3D<float> axis = Vector3D<float>(0.0f, 0.0f, 1.0f)^getDir();

    glPushMatrix();

        glTranslate( getPos() );

      glPushMatrix();

      glRotate( Vector3D<float>( 0.0f, 0.0f, 1.0f ).getAngle( getDir() ), axis );

        glPushMatrix();
  //        glLoadIdentity();

          // Arrow Head
          glBegin( GL_TRIANGLE_FAN ); {

            glPoint( pos );

            float x,y;
            for (int i = 0; i < _m; i++) {

              x = _r*cosf(((float)i*2.0f*M_PI)/(float)_m);
              y = _r*sinf(((float)i*2.0f*M_PI)/(float)_m);
              glPoint( pos + Point3D<float>( x, y, -_l*_h ) );
            }
            x = _r*cosf( 0.0f );
            y = _r*sinf( 0.0f );
            glPoint( pos + Point3D<float>( x, y, -_l*_h ) );

          } glEnd();

          // Arrow Head Bottom
          glBegin( GL_TRIANGLE_FAN ); {

            glPoint( pos + Point3D<float>( 0.0f, 0.0f, -_l*_h ) );

            float x,y;
            for (int i = 0; i < _m; i++) {

              x = _r*cosf(((float)i*2.0f*M_PI)/(float)_m);
              y = _r*sinf(((float)i*2.0f*M_PI)/(float)_m);
              glPoint( pos + Point3D<float>( x, y, -_l*_h ) );
            }
            x = _r*cosf( 0.0f );
            y = _r*sinf( 0.0f );
            glPoint( pos + Point3D<float>( x, y, -_l*_h ) );

          } glEnd();


          // Arrow Body
          glBegin( GL_QUAD_STRIP ); {

            float x,y;
            for (int i = 0; i < _m; i++) {

              x = _r*0.5f*cosf(((float)i*2.0f*M_PI)/(float)_m);
              y = _r*0.5f*sinf(((float)i*2.0f*M_PI)/(float)_m);
              glPoint( pos + Point3D<float>( x, y, -_l ) );
              glPoint( pos + Point3D<float>( x, y, -_l * _h) );
            }
            x = _r*0.5f*cosf( 0.0f );
            y = _r*0.5f*sinf( 0.0f );
            glPoint( pos + Point3D<float>( x, y, -_l ) );
            glPoint( pos + Point3D<float>( x, y, -_l * _h ) );

          } glEnd();


          // Arrow Body Bottom
          glBegin( GL_TRIANGLE_FAN ); {

            glPoint( pos + Point3D<float>( 0.0f, 0.0f, -_l ) );

            float x,y;
            for (int i = 0; i < _m; i++) {

              x = _r*0.5f*cosf(((float)i*2.0f*M_PI)/(float)_m);
              y = _r*0.5f*sinf(((float)i*2.0f*M_PI)/(float)_m);
              glPoint( pos + Point3D<float>( x, y, -_l ) );
            }
            x = _r*0.5f*cosf( 0.0f );
            y = _r*0.5f*sinf( 0.0f );
            glPoint( pos + Point3D<float>( x, y, -_l ) );

          } glEnd();

        glPopMatrix();

      glPopMatrix();

    glPopMatrix();
  }

} // END namespace GMlib

