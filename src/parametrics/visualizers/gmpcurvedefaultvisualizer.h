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



/*! \file gmpcurvedefaultvisualizer.h
 *
 *  Interface for the PCurveDefaultVisualizer class.
 */


#ifndef __gmPCURVEDEFAULTVISUALIZER_H__
#define __gmPCURVEDEFAULTVISUALIZER_H__

#include "gmpcurvevisualizer.h"


namespace GMlib {

  template <typename T, int n>
  class PCurveDefaultVisualizer : public PCurveVisualizer<T,n> {
  public:
    PCurveDefaultVisualizer();

    void          render(const DisplayObject* obj, const Camera *cam) const;
    void          renderGeometry(const GL::AttributeLocation& attrib_loc) const;

    virtual void  replot( const DVector< DVector< Vector<T, n> > >& p,
                          int m, int d, bool closed );

  protected:
    GL::VertexBufferObject    _vbo;
    unsigned int              _no_vertices;
    GLfloat                   _line_width;

  }; // END class PCurveDefaultVisualizer

} // END namespace GMlib

// Include PCurveDefaultVisualizer class function implementations
#include "gmpcurvedefaultvisualizer.c"

#endif // __gmPCURVEDEFAULTVISUALIZER_H__
