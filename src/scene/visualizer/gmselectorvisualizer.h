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


#ifndef __GM_SCENE_VISUALIZERS_SELECTORVISUALIZER_H__
#define __GM_SCENE_VISUALIZERS_SELECTORVISUALIZER_H__

#include "gmvisualizer.h"

// gmlib
#include <core/utils/gmcolor.h>
#include <opengl/bufferobjects/gmvertexbufferobject.h>
#include <opengl/bufferobjects/gmindexbufferobject.h>
#include <scene/utils/gmmaterial.h>


namespace GMlib {

  class Camera;

  class SelectorVisualizer: public Visualizer {
  public:
    SelectorVisualizer( float radius = 0.27, Material mat = GMmaterial::Jade );
    SelectorVisualizer( int m1, int m2, float radius = 0.27, Material mat = GMmaterial::Jade );
    ~SelectorVisualizer();

    void                          display();
    void                          select();

    static SelectorVisualizer*    getInstance();

  private:
    void                          makeGeometry( float radius, int m1, int m2 );

    // Cube buffer objects
    GL::VertexBufferObject        _vbo;
    GL::IndexBufferObject         _ibo;

    int                           _top_bot_verts;
    int                           _mid_strips;
    int                           _mid_strips_verts;

    Material                      _mat;



    static SelectorVisualizer*    _s_instance;

  }; // END class SelectorVisualizer

} // END namespace GMlib


#endif // __GM_SCENE_VISUALIZERS_SELECTORVISUALIZER_H__
