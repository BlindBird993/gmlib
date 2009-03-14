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



/*! \file gmArray.h
 *
 *  Interface for the Array classes.
 *
 *  \date   2008-07-02
 */


#ifndef __gmSTLOBJECT_H__
#define __gmSTLOBJECT_H__


#include <string>
using std::string;

#include "gmDisplayObject.h"
#include "gmArrayLX.h"
#include "gmDPSphere.h"
#include "gmTriangle.h"

//
//#include <GM_Sphere.h>
//#include <GM_PSurf.h>
//#include <GM_Triangle.h>



namespace GMlib {

  class StlObject : public DisplayObject {
  public:
    StlObject( const string& filename, const GLColor& color = 5, int flip = 1 ); // From file, in given color
    StlObject( float r = 10 );				 // Makes a Sphere, just for debugging
    ~StlObject();

    std::string                     getIdentity() const;
    unsigned int                    getNoPoints();
    Array< UnitVector3D<float> >    getNormals();
    Array<Point<float,3> >          getVertices();
    ArrayLX< Vertex<float> >        getVertex();

    void                            setColor( const GLColor& color );

  protected:
    void localDisplay();
    void localSelect();


  private:
    unsigned int                          _dlist_name;
    DPSphere<float>                 *_sphere;          // Debug

    string                          _fname;						 // I put the filename in here,
    FILE*                           _stl_file;
    GLColor                         _color;

    Array<Point3D<float> >          _vertices;     // storage, each three makes a triangle
    Array<UnitVector3D<float> >     _normals; // with one normal for each triangle
    Box<float,3>                    _bbox;					 // Bounding box, should be an options

    // binary file utility functions to render it.
    float                           _getFloat();
    unsigned int                    _getUint();
    unsigned long                   _getUli();
    int                             _readStlBinary( const string& filename );

  };

}


// Include inline function implementations
#include "gmStlObject.c"



#endif // __gmSTLOBJECT_H__




