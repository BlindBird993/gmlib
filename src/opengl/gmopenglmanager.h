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

    // Global
  public:
    static void                 cleanUp();
    static void                 init();



    // System wide buffers

    static VertexBufferObject     _std_rep_cube;
    static IndexBufferObject      _std_rep_cube_indices;
    static IndexBufferObject      _std_rep_frame_indices;
    static UniformBufferObject    _lights_ubo;

    static void                   initSystemWideBuffers();


    // Programs and shaders
  public:

    static void                   initSystemWideShadersAndPrograms();


    // "Default" program
    static Program                _prog_default;
    static VertexShader           _vs_default;
    static FragmentShader         _fs_default;
    static void                   initDefaultProg();


    // "Phong" program
    static Program                _prog_phong;
    static VertexShader           _vs_phong;
    static FragmentShader         _fs_phong;
    static void                   initPhongProg();

    // "Color" program
    static Program                _prog_color;
    static VertexShader           _vs_color;
    static FragmentShader         _fs_color;
    static void                   initColorProg();

    // "Select" program
    static Program                _prog_select;
    static VertexShader           _vs_select;
    static FragmentShader         _fs_select;
    static void                   initSelectProg();

    // "Render" program
    static Program                _prog_render;
    static VertexShader           _vs_render;
    static FragmentShader         _fs_render;
    static void                   initRenderProg();

    // "Render select" program
    static Program                _prog_render_select;
    static VertexShader           _vs_render_select;
    static FragmentShader         _fs_render_select;
    static void                   initRenderSelectProg();

    // "PCurve: Contours" program
    static Program                _prog_pcurve_contours;
    static VertexShader           _vs_pcurve_contours;
    static FragmentShader         _fs_pcurve_contours;
    static void                   initPCurveContoursProg();


    // "PSurf: Phong NMap" program
    static Program                _prog_psurf_phong_nmap;
    static VertexShader           _vs_psurf_phong_nmap;
    static FragmentShader         _fs_psurf_phong_nmap;
    static void                   initPSurfPhongNMapProg();


    // "PSurf: Phong NMap PTex" program
    static Program                _prog_psurf_phong_nmap_ptex;
    static VertexShader           _vs_psurf_phong_nmap_ptex;
    static FragmentShader         _fs_psurf_phong_nmap_ptex;
    static void                   initPSurfPhongNMapPTexProg();


    // "PSurf: Contours" program
    static Program                _prog_psurf_contours;
    static VertexShader           _vs_psurf_contours;
    static FragmentShader         _fs_psurf_contours;
    static void                   initPSurfContours();

  private:
    static std::string            glslFnComputeLighting();
    static std::string            glslDefHeader150();
    static std::string            glslStructMaterial();
    static std::string            glslStructLight();
    static std::string            glslUniformLights();
    static std::string            glslFnSunlight();
    static std::string            glslFnPointlight();
    static std::string            glslFnSpotlight();



  }; // END class OpenGL



} // END namespace GL
} // END namespace GMlib




#endif // __gm_OPENGL_OPENGLMANAGER_H__
