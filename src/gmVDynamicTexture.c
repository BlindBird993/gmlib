
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



/*! \file gmVDynamicTexture.c
 *
 *  VDynamicTexture class function implementations.
 *
 *  \date   2009-07-31
 */


namespace GMlib {

  template <typename T, int n>
  inline
  VDynamicTexture<T,n>::VDynamicTexture() : VDefault<T,n>() {}


  template <typename T, int n>
  inline
  VDynamicTexture<T,n>::VDynamicTexture( const VDynamicTexture<T,n>& copy ) : VDefault<T,n>( copy ) {}


  template <typename T, int n>
  inline
  void VDynamicTexture<T,n>::display() {
    glMatrixMode( GL_TEXTURE ); {
      glPushMatrix(); {

        glMultMatrix( _matrix );

        VDefault<T,n>::display();

      } glPopMatrix();
    } glMatrixMode( GL_MODELVIEW );
  }


  template <typename T, int n>
  inline
  std::string VDynamicTexture<T,n>::getIdentity() const {

    return "VDynamicTexture";
  }


  template <typename T, int n>
  inline
  const HqMatrix<T,3>& VDynamicTexture<T,n>::getMatrix() const {

    return _matrix;
  }


  template <typename T, int n>
  inline
  void VDynamicTexture<T,n>::rotate( const Angle& a, const Point<float,3>& p, const UnitVector<float,3>& d ) {

    Vector3D<float> ra = d;
    Vector3D<float> lu = ra.getLinIndVec();
    Vector<float,3> u = lu ^ ra;
    Vector<float,3> v = ra ^ u;

    _matrix.rotate(a, u, v, p);
  }


  template <typename T, int n>
  inline
  void VDynamicTexture<T,n>::translate(const Vector<float,3>& trans_vector) {

    _matrix.translate(trans_vector);
  }


}










