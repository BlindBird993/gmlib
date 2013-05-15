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

#include "../gmvisualizer.h"

// gmlib
#include <core/utils/gmcolor.h>
#include <opengl/gmbufferobject.h>


namespace GMlib {

  class Camera;

  class VisualizerStdRep : public Visualizer {
    GM_VISUALIZER(VisualizerStdRep)
  public:
    VisualizerStdRep();

    void              render( const DisplayObject* obj, const Camera* cam ) const;
    void              renderGeometry( const GL::AttributeLocation& vert_loc ) const;


    void              render( const HqMatrix<float,3>& mvmat,
                               const HqMatrix<float,3>& pmat ) const;

    static VisualizerStdRep*    getInstance();


  private:

    // Cube buffer objects
    GL::BufferObject    _bo_cube;
    GL::BufferObject    _bo_cube_indices;
    GL::BufferObject    _bo_cube_frame_indices;

    static VisualizerStdRep*    _s_instance;

  }; // END class VisualizerStdRep

} // END namespace GMlib


#endif // __gmVISUALIZERSTDREP_H__
