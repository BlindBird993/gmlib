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



/*! \file gmpsurftexvisualizer.h
 *
 *  Texture PSurf Visualizer
 */


#ifndef __gmPSURFTEXVISUALIZER_H__
#define __gmPSURFTEXVISUALIZER_H__

#include "gmpsurfvisualizer.h"

// gmlib
#include <opengl/gmvertexbufferobject.h>
#include <opengl/gmindexbufferobject.h>



namespace GMlib {

  template <typename T>
  class PSurfTexVisualizer : public PSurfVisualizer<T> {
  public:
    PSurfTexVisualizer();
    virtual ~PSurfTexVisualizer();
    void          display();
    std::string   getIdentity() const;
    virtual void  replot(
      DMatrix< DMatrix< Vector<T, 3> > >& p,
      DMatrix< Vector<T, 3> >& normals,
      int m1, int m2, int d1, int d2
    );
    void          select();

    void          setTex( GLuint tex ) {

      _tex = tex;
    }

  protected:
    VertexBufferObject        _vbo;
    TriangleStripIBO          _ibo;
    GLuint                    _nmap;
    GLuint                    _tex;

    unsigned int              _no_vertices;

  }; // END class PSurfTexVisualizer

} // END namespace GMlib

// Include PSurfTexVisualizer class function implementations
#include "gmpsurftexvisualizer.c"


#endif // __gmPSURFTEXVISUALIZER_H__
