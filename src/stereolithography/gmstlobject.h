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



/*! \file gmstlobject.h
 *
 */


#ifndef __gmSTLOBJECT_H__
#define __gmSTLOBJECT_H__


// gmlib
#include <core/containers/gmarraylx.h>
#include <scene/gmdisplayobject.h>
#include <parametrics/surfaces/gmpsphere.h>
#include <trianglesystem/gmtrianglesystem.h>

// stl
#include <string>


namespace GMlib {


  template <typename T>
  class TSVertex;


  enum GM_STL_VISUALIZATION {
    GM_STL_POINT,
    GM_STL_TRIANGLE
  };


  class StlObject : public DisplayObject {
  public:
    StlObject( const std::string& filename, const Color& color = 5, int flip = 1 ); // From file, in given color
    StlObject( std::ifstream& stream, bool binary = true, const Color& color = GMcolor::Aqua );
    StlObject( PSurf<float> *obj, int m1 = 20, int m2 = 20, GM_STL_VISUALIZATION gsv = GM_STL_TRIANGLE );
    StlObject( float r = 10 );				 // Makes a Sphere, just for debugging
    ~StlObject();

    std::string                       getIdentity() const;
    unsigned int                      getNoNormals() const;
    unsigned int                      getNoPoints() const;
    Array< Vector<float,3> >          getNormals();
    const Array< Vector<float,3> >&   getNormals() const;
    Array<Point<float,3> >            getPoints();
    const Array<Point<float,3> >&     getPoints() const;
    float                             getPointSize();
    ArrayLX< TSVertex<float> >          getVertices();

    void                              load( std::ifstream& stream, bool binary = true );
    void                              replot( GM_STL_VISUALIZATION gsv = GM_STL_TRIANGLE );
    void                              save( std::ofstream& stream, bool binary = true );
    void                              setPointSize( float s = 5.0 );

  protected:
    void                              localDisplay();
    void                              localSelect();


  private:
    float                             _getFloat();
    unsigned int                      _getUint();
    unsigned long                     _getUli();
    int                               _readStlBinary( const std::string& filename );
    void                              _updateBounding();
    void                              _makeList( GLenum e = GL_TRIANGLES );
    void                              _init();

    unsigned int                      _dlist;
    PSphere<float>                    *_sphere;         // Debug

    std::string                       _identity;				// I put the filename in here,
    FILE*                             _stl_file;

    Array<Point<float,3> >            _vertices;        // storage, each three makes a triangle
    Array<Vector<float,3> >           _normals;         // with one normal for each triangle
    Box<float,3>                      _bbox;					  // Bounding box, should be an options
    float                             _point_size;

    // binary file utility functions to render it.


  }; // END class StlObject








  inline
  std::string StlObject::getIdentity() const {

    return _identity;
  }


  inline
  unsigned int StlObject::getNoNormals() const {

    return _normals.getSize();
  }


  inline
  unsigned int StlObject::getNoPoints() const {

    return _vertices.getSize();
  }


  inline
  Array< Vector<float,3> > StlObject::getNormals() {

    return _normals;
  }


  inline
  const Array< Vector<float,3> >& StlObject::getNormals() const {

    return _normals;
  }


  inline
  Array< Point<float,3> > StlObject::getPoints() {

    Array< Point<float,3> > v;         // returns copy, no cast between Point3D<float> and Point<float,3>
    v.setSize( _vertices.getSize() );
    for( int i = 0; i < _vertices.getSize(); i++ )
      v[i] = _vertices[i];

    return v;
  }


  inline
  const Array< Point<float,3> >& StlObject::getPoints() const {

    return _vertices;
  }


  inline
  ArrayLX< TSVertex<float> > StlObject::getVertices() {

    ArrayLX< TSVertex<float> > v;         // returns copy, no cast between Point3D<float> and Point<float,3>
    v.setSize( _vertices.getSize() );
    for( int i = 0; i < _vertices.getSize(); i++ )
      v[i] = TSVertex<float>( _vertices[i], _normals[i/3] );

    return v;
  }


  inline
  void StlObject::localDisplay() {

//    glPushAttrib( GL_LIGHTING_BIT );

//    if( this->isLighted() )
//    {
//      this->_material.glSet();
//    }
//    else
//    {
//      glDisable( GL_LIGHTING );
//      glColor(this->_color);
//    }

//    if( _dlist )
//      glCallList( _dlist );

//    glPopAttrib();
  }


  inline
  void StlObject::localSelect() {

    glCallList( _dlist+1 );
  }

} // END namespace GMlib


#endif // __gmSTLOBJECT_H__




