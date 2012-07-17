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



/*! \file gmVisualizerStdRep.h
 *
 *  Header for the VisualizerStdRep class.
 *
 *  \date   2011-01-17
 */


#ifndef __gmVISUALIZERSTDREP_H__
#define __gmVISUALIZERSTDREP_H__


#include "gmColor.h"
#include "gmOpenGL.h"
#include "gmVisualizer.h"

namespace GMlib {

  class Camera;

  class VisualizerStdRep : public Visualizer {
  public:
    VisualizerStdRep();
    ~VisualizerStdRep();

    void              display( Camera* cam );
    std::string       getIdentity() const;
    void              select( Camera* cam, const Color& name = Color() );

  protected:
    GLProgram         _display;
    GLProgram         _select;

    // Cube buffer objects
    GLBufferObject    _bo_cube;
    GLBufferObject    _bo_cube_indices;
    GLBufferObject    _bo_cube_frame_indices;

  }; // END class VisualizerStdRep

} // END namespace GMlib


#endif // __gmVISUALIZERSTDREP_H__
