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



/*! \file gmpcurvevisualizer.h
 *
 *  Interface for the PCurveVisualizer class.
 */


#ifndef __GMPCURVEVISUALIZER_H__
#define __GMPCURVEVISUALIZER_H__


// gmlib::core
#include <core/types/gmpoint.h>
#include <core/containers/gmdvector.h>
#include <core/utils/gmcolor.h>

// gmlib::scene
#include <scene/visualizer/gmvisualizer.h>


namespace GMlib {

  template <typename T>
  class PCurve;

  template <typename T>
  class PCurveVisualizer : public Visualizer {
  public:
    PCurveVisualizer();
    ~PCurveVisualizer();

    std::string   getIdentity() const;
    virtual void  replot(
      DVector< DVector< Vector<T, 3> > >& p,
      int m, int d
    );
    void          set( SceneObject* obj );

    static void   fillStandardVBO( GLVertexBufferObject& vbo, unsigned int& no_vertices,
                                   DVector< DVector< Vector<T, 3> > >& p, int d = 0);
//    static void   populateLineStripVBO( GLuint _vbo_id, int& no_dp, DVector< DVector< Vector<T, 3> > >& p, int d = 0 );

  protected:
    PCurve<T>     *_curve;

  }; // END class PCurveVisualizer

} // END namespace GMlib

// Include PCurveVisualizer class function implementations
#include "gmpcurvevisualizer.c"


#endif // __GMPCURVEVISUALIZER_H__
