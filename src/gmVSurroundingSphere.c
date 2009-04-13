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



/*! \file gmVSurroundingSphere.c
 *  \brief VSurroundingSphere class function implementations
 *
 *  Implementation of the VSurroundingSphere class.
 *
 *  \date   2009-01-27
 */


// GMlib includes
#include "gmSphere3D.h"


namespace GMlib {



  template <typename T, int n>
  inline
  VSurroundingSphere<T,n>::VSurroundingSphere() {

    _init();
  }


  template <typename T, int n>
  inline
  VSurroundingSphere<T,n>::VSurroundingSphere( const VSurroundingSphere<T,n>& v ) : Visualizer<T,n>( v ) {}


  template <typename T, int n>
  inline
  void VSurroundingSphere<T,n>::_init() {

    _color = GMcolor::Yellow;
    _color_clean = GMcolor::White;
    _spheres = GM_VISUALIZER_SS_CLEAN;
    _wireframe = true;
  }


  template <typename T, int n>
  inline
  void VSurroundingSphere<T,n>::display() {

    // Push GL Attributes
    glPushAttrib( GL_LIGHTING_BIT | GL_POLYGON_BIT );

      // Disable Lighting
      glDisable( GL_LIGHTING );

      // Set Wireframe or not
      if( _wireframe )
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

      // Display Clean Surrounding Sphere
      if( (_spheres & GM_VISUALIZER_SS_CLEAN) == GM_VISUALIZER_SS_CLEAN ) {

        _color_clean.glSet();
        Sphere3D( this->_ref->getSurroundingSphereClean(), 10, 10 ).display();
      }

      // Display Surrounding Sphere
      if( (_spheres & GM_VISUALIZER_SS_SPHERE) == GM_VISUALIZER_SS_SPHERE ) {

        _color.glSet();
        Sphere3D( this->_ref->getSurroundingSphere(), 10, 10 ).display();
      }

    // Pop GL Attributes
    glPopAttrib();
  }

  template <typename T, int n>
  inline
  const GLColor& VSurroundingSphere<T,n>::getColor( unsigned int mask ) const {

    if( mask == GM_VISUALIZER_SS_SPHERE )
      return _color;
    else if( mask == GM_VISUALIZER_SS_CLEAN )
      return _color_clean;
    else {
      static GLColor error;
      return error;
    }
  }


  template <typename T, int n>
  inline
  std::string VSurroundingSphere<T,n>::getIdentity() const {

    return "SurroundingSphere Visualizer";
  }


  template <typename T, int n>
  inline
  unsigned int VSurroundingSphere<T,n>::getSpheres() const {

    return _spheres;
  }


  template <typename T, int n>
  inline
  bool VSurroundingSphere<T,n>::isWireframe() const {

    return _wireframe;
  }


  template <typename T, int n>
  inline
  void VSurroundingSphere<T,n>::replot(
    DVector< DVector< Vector<T, 3> > >& p,
    int m, int d
  ) {}


  template <typename T, int n>
  inline
  void VSurroundingSphere<T,n>::replot(
    DMatrix< DMatrix< Vector<T, 3> > >& p,
    DMatrix< Vector<T, 3> >& normals,
    int m1, int m2, int d1, int d2
  ) {}


  template <typename T, int n>
  void VSurroundingSphere<T,n>::setColor( const GLColor& color, unsigned int mask ) {

    if( (mask & GM_VISUALIZER_SS_SPHERE) == GM_VISUALIZER_SS_SPHERE )
      _color = color;

    if( (mask & GM_VISUALIZER_SS_CLEAN) == GM_VISUALIZER_SS_CLEAN )
      _color_clean = color;
  }


  template <typename T, int n>
  void VSurroundingSphere<T,n>::setSpheres( unsigned int mask ) {

    _spheres = mask;
  }


  template <typename T, int n>
  void VSurroundingSphere<T,n>::setWireframe( bool wireframe ) {

    _wireframe = wireframe;
  }

}
