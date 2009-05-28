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

#include "gmDisplayObject.h"
#include "gmArrayLX.h"
#include "gmDPSphere.h"
#include "gmTriangle.h"



namespace GMlib {

  class StlObject : public DisplayObject {
  public:
    StlObject( const string& filename, const GLColor& color = 5, int flip = 1 ); // From file, in given color
    StlObject( std::ifstream& stream, bool binary = true, const GLColor& color = GMcolor::Aqua );
    StlObject( DSurf<float> *obj, int m1 = 20, int m2 = 20 );
    StlObject( float r = 10 );				 // Makes a Sphere, just for debugging
    ~StlObject();

    std::string                     getIdentity() const;
    unsigned int                    getNoPoints();
    Array< Vector<float,3> >        getNormals();
    Array<Point<float,3> >          getPoints();
    ArrayLX< Vertex<float> >        getVertices();

    void                            load( std::ifstream& stream, bool binary = true );
    void                            replot();
    void                            save( std::ofstream& stream, bool binary = true );
    void                            setColor( const GLColor& color );

  protected:
    void localDisplay();
    void localSelect();


  private:
    unsigned int                    _dlist;
    DPSphere<float>                 *_sphere;         // Debug

    std::string                     _identity;				// I put the filename in here,
    FILE*                           _stl_file;
    GLColor                         _color;

    Array<Point<float,3> >          _vertices;        // storage, each three makes a triangle
    Array<Vector<float,3> >         _normals;         // with one normal for each triangle
    Box<float,3>                    _bbox;					  // Bounding box, should be an options

    // binary file utility functions to render it.
    float                           _getFloat();
    unsigned int                    _getUint();
    unsigned long                   _getUli();
    int                             _readStlBinary( const string& filename );

    void                            _updateBounding();
    void                            _makeList();

  };

}


// Include inline function implementations
#include "gmStlObject.c"



#endif // __gmSTLOBJECT_H__




