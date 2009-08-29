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



/*! \file gmVCoordinateSystem.c
 *  \brief VCoordinateSystem class function implementations
 *
 *  Implementation of the VCoordinateSystem class.
 *
 *  \date   2009-08-25
 */


// GMlib includes
#include "gmSphere3D.h"


namespace GMlib {



  template <typename T, int n>
  inline
  VCoordinateSystem<T,n>::VCoordinateSystem() {

    init();
  }


  template <typename T, int n>
  inline
  VCoordinateSystem<T,n>::VCoordinateSystem( const VCoordinateSystem<T,n>& copy ) : Visualizer<T,n>( copy ) {}


  template <typename T, int n>
  inline
  VCoordinateSystem<T,n>::~VCoordinateSystem() {

    if( _dlist )
      glDeleteLists( _dlist, 1 );
  }


  template <typename T, int n>
  inline
  void VCoordinateSystem<T,n>::display() {

    glPushMatrix(); {

      switch( _cs ) {
        case GM_VISUALIZER_COORDSYS_GLOBAL: {

          HqMatrix<float,3> mat = this->_ref->getMatrixGlobal();
          mat.invertOrthoNormal();
          mat[0][3] = 0.0f;
          mat[1][3] = 0.0f;
          mat[2][3] = 0.0f;
          glMultMatrix( mat );
        }
        break;

        case GM_VISUALIZER_COORDSYS_PARENT: {

          HqMatrix<float,3> mat = this->_ref->getMatrix();
          mat.invertOrthoNormal();
          mat[0][3] = 0.0f;
          mat[1][3] = 0.0f;
          mat[2][3] = 0.0f;
          glMultMatrix( mat );
        }
        break;

        case GM_VISUALIZER_COORDSYS_LOCAL:
        default:
          break;
      }

      // Push GL Attributes
      glPushAttrib( GL_LIGHTING_BIT );

        // Disable Lighting
        glDisable( GL_LIGHTING );

        glCallList( _dlist );

      // Pop GL Attributes
      glPopAttrib();

    } glPopMatrix();
  }


  template <typename T, int n>
  inline
  GM_VISUALIZER_COORDSYS VCoordinateSystem<T,n>::getCoordinateSystem() const {

    return _cs;
  }


  template <typename T, int n>
  inline
  std::string VCoordinateSystem<T,n>::getIdentity() const {

    return "VCoordinateSystem";
  }


  template <typename T, int n>
  inline
  void VCoordinateSystem<T,n>::genDList() {

    if( !this->_ref->isDynamic() ) {

      if( _dlist )
        glDeleteLists( _dlist, 1 );

      _dlist = glGenLists(1);

      glPushAttrib( GL_LIGHTING_BIT | GL_LINE_BIT | GL_POLYGON_BIT ); {

        // Make displaylist for display of pointed curve
        glNewList( _dlist, GL_COMPILE ); {

          glBegin(GL_LINES); {

            // x-axis
            glColor( GMcolor::Red );
            glPoint( Point3D<float>( 0.0f, 0.0f, 0.0f ) );
            glPoint( Point3D<float>( 1.0f, 0.0f, 0.0f ) );

            // y-axis
            glColor( GMcolor::Green );
            glPoint( Point3D<float>( 0.0f, 0.0f, 0.0f ) );
            glPoint( Point3D<float>( 0.0f, 1.0f, 0.0f ) );

            // z-axis
            glColor( GMcolor::Blue );
            glPoint( Point3D<float>( 0.0f, 0.0f, 0.0f ) );
            glPoint( Point3D<float>( 0.0f, 0.0f, 1.0f ) );

          }glEnd();
        }glEndList();

      } glPopAttrib();
    }
  }

  template <typename T, int n>
  inline
  void VCoordinateSystem<T,n>::init() {

    _cs = GM_VISUALIZER_COORDSYS_LOCAL;
    _dlist = 0;
  }


  template <typename T, int n>
  inline
  void VCoordinateSystem<T,n>::replot(
    DVector< DVector< Vector<T, 3> > >& /*p*/,
    int /*m*/, int /*d*/
  ) {

    genDList();
  }


  template <typename T, int n>
  inline
  void VCoordinateSystem<T,n>::replot(
    DMatrix< DMatrix< Vector<T, 3> > >& /*p*/,
    DMatrix< Vector<T, 3> >& /*normals*/,
    int /*m1*/, int /*m2*/, int /*d1*/, int /*d2*/
  ) {

    genDList();
  }


  template <typename T, int n>
  void VCoordinateSystem<T,n>::setCoordinateSystem( GM_VISUALIZER_COORDSYS coordsys ) {

    _cs = coordsys;
  }


}

