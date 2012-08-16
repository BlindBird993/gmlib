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



/*! \file gmvisualizerstdrep.h
 *
 *  Header for the VisualizerStdRep class.
 */


#ifndef __gmVISUALIZERSTDREP_H__
#define __gmVISUALIZERSTDREP_H__

#include "gmvisualizer.h"

// gmlib::core
#include <core/utils/gmcolor.h>

// gmlib::opengl
#include <opengl/gmopengl.h>


namespace GMlib {

  class Camera;

  class VisualizerStdRep : public Visualizer {
  public:
    VisualizerStdRep();
    ~VisualizerStdRep();

    void              display( Camera* cam );
    std::string       getIdentity() const;
    void              select();

  protected:
    GLProgram         _display;

    // Cube buffer objects
    GLBufferObject    _bo_cube;
    GLBufferObject    _bo_cube_indices;
    GLBufferObject    _bo_cube_frame_indices;

  }; // END class VisualizerStdRep

} // END namespace GMlib


#endif // __gmVISUALIZERSTDREP_H__
