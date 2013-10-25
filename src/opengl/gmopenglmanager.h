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



#ifndef __gm_OPENGL_OPENGLMANAGER_H__
#define __gm_OPENGL_OPENGLMANAGER_H__



#include "gmopengl.h"

#include "bufferobjects/gmvertexbufferobject.h"
#include "bufferobjects/gmindexbufferobject.h"
#include "bufferobjects/gmuniformbufferobject.h"

#include "gmprogram.h"
#include "shaders/gmvertexshader.h"
#include "shaders/gmfragmentshader.h"

namespace GMlib {
namespace GL {



  class OpenGLManager {

  public:

    // init functions
    static void                 init();
    static void                 cleanUp();

    // GLSL snipet functions
    static std::string            glslDefHeader150Source();
    static std::string            glslStructMaterialSource();
    static std::string            glslStructLightSource();
    static std::string            glslUniformLightsSource();
    static std::string            glslFnSunlightSource();
    static std::string            glslFnPointlightSource();
    static std::string            glslFnSpotlightSource();
    static std::string            glslFnComputeLightingSource();

  private:
    static bool                 _initialized;

    // System wide buffers
    static void                   initSystemWideBuffers();


    // Programs and shaders

    static void                   initSystemWideShadersAndPrograms();

    // System wide programs/shaders
    static void                   initPhongProg();
    static void                   initColorProg();

//    // "PCurve: Contours" program
//    static Program                _prog_pcurve_contours;
//    static VertexShader           _vs_pcurve_contours;
//    static FragmentShader         _fs_pcurve_contours;
//    static void                   initPCurveContoursProg();


//    // "PSurf: Contours" program
//    static Program                _prog_psurf_contours;
//    static VertexShader           _vs_psurf_contours;
//    static FragmentShader         _fs_psurf_contours;
//    static void                   initPSurfContours();

  public:



  }; // END class OpenGL



} // END namespace GL
} // END namespace GMlib




#endif // __gm_OPENGL_OPENGLMANAGER_H__
