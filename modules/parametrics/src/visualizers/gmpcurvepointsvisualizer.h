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



/*! \file gmpcurvepointsvisualizer.h
 *
 *  Interface for the PCurvePointsVisualizer class.
 */


#ifndef __GMPCURVEPOINTSVISUALIZER_H__
#define __GMPCURVEPOINTSVISUALIZER_H__

#include "gmpcurvevisualizer.h"

// gmlib
#include <core/types/gmpoint.h>
#include <core/containers/gmdvector.h>
#include <core/utils/gmcolor.h>
#include <opengl/gmprogram.h>


namespace GMlib {


  template <typename T, int n>
  class PCurvePointsVisualizer : public PCurveVisualizer<T,n> {
    GM_VISUALIZER(PCurvePointsVisualizer)
  public:
    PCurvePointsVisualizer();
    virtual ~PCurvePointsVisualizer();

    void              render(const SceneObject* obj, const DefaultRenderer* render) const;
    const Color&      getColor() const;
    float             getSize() const;
    void              setColor( const Color& color );
    void              setSize( float size );


    void              replot( const DVector< DVector< Vector<T, n> > >& p,
                              int m, int d, bool closed );

  protected:
    GL::Program               _prog;

    GL::VertexBufferObject    _vbo;
    int                       _no_vertices;

    float                     _size;
    Color                     _color;
  };

} // END namespace GMlib

// Include PCurvePointsVisualizer class function implementations
#include "gmpcurvepointsvisualizer.c"


#endif // __GMPCURVEPOINTSVISUALIZER_H__
