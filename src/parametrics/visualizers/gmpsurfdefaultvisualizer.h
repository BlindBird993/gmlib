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



/*! \file gmpsurfdefaultvisualizer.h
 *
 *  Default PSurf Visualizer
 */


#ifndef __gmPSURFDEFAULTVISUALIZER_H__
#define __gmPSURFDEFAULTVISUALIZER_H__

#include "gmpsurfvisualizer.h"

namespace GMlib {

  template <typename T>
  class PSurfDefaultVisualizer : public PSurfVisualizer<T> {
  public:
    PSurfDefaultVisualizer();
    ~PSurfDefaultVisualizer();
    void          display( Camera * cam );
    std::string   getIdentity() const;
    virtual void  replot(
      DMatrix< DMatrix< Vector<T, 3> > >& p,
      DMatrix< Vector<T, 3> >& normals,
      int m1, int m2, int d1, int d2
    );
    void          select( Camera * cam, const Color& name );

  protected:
    GLVertex2DBufferObject    _vbo;
    TriangleStripIBO          _ibo;
    GLuint                    _tex;

    int                       _tri_strips;
    GLsizei                   _tri_strip_offset;
    int                       _indices_per_tri_strip;

    GLProgram                 _display;
    GLProgram                 _select;

  }; // END class PSurfDefaultVisualizer

} // END namespace GMlib

// Include PSurfDefaultVisualizer class function implementations
#include "gmpsurfdefaultvisualizer.c"


#endif // __gmPSURFDEFAULTVISUALIZER_H__
