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

#include "gmopenglmanager.h"

// stl
#include <cassert>


namespace GMlib {
namespace GL {


  bool OpenGLManager::_initialized = false;


  void OpenGLManager::init() {

    assert(!_initialized);
    _initialized = true;

    // Init GLEW
    glewExperimental = true;
    GLenum err = glewInit();
    if( err == GLEW_OK )
      std::cout << "GLEW Init OK - using GLEW version " << glewGetString(GLEW_VERSION) << std::endl;
    else
      std::cout << "GLEW Init FAILED!!" << std::endl;
    std::cout << std::flush;

    initSystemWideBuffers();
    initSystemWideShadersAndPrograms();

  }

  void OpenGLManager::cleanUp() {

    //! \todo Implement this... It crashes bad!!
    assert(false);
  }




  ///////////////////////
  ///
  /// System wide buffers
  ///

  void OpenGLManager::initSystemWideBuffers() {

    VertexBufferObject _std_rep_cube;
    _std_rep_cube.create("std_rep_cube");
    _std_rep_cube.setPersistent(true);

    IndexBufferObject std_rep_cube_indices;
    std_rep_cube_indices.create("std_rep_cube_indices");
    std_rep_cube_indices.setPersistent(true);

    IndexBufferObject std_rep_frame_indices;
    std_rep_frame_indices.create("std_rep_frame_indices");
    std_rep_frame_indices.setPersistent(true);

    UniformBufferObject lights_ubo;
    lights_ubo.create("lights_ubo");
    lights_ubo.setPersistent(true);
  }




  ////////////////////////////////////
  ///
  /// System wide Programs and Shaders
  ///

  void OpenGLManager::initSystemWideShadersAndPrograms() {

    initPhongProg();
    initColorProg();

//    initPCurveContoursProg();
//    initPSurfContours();
  }




  void OpenGLManager::initPhongProg() {

    ///////////////
    // Phong shader
    std::string vs_str =
        glslDefHeader150Source() +

        "uniform mat4 u_mvmat, u_mvpmat;\n"
        "\n"
        "in vec4 in_vertex;\n"
        "in vec4 in_normal;\n"
        "in vec2 in_tex;\n"
        "\n"
        "out vec4 gl_Position;\n"
        "\n"
        "smooth out vec3 ex_pos;\n"
        "smooth out vec3 ex_normal;\n"
        "\n"
        "void main() {\n"
        "\n"
        "  // Transform the normal to view space\n"
        "  mat3 nmat = inverse( transpose( mat3( u_mvmat ) ) );\n"
        "  ex_normal = nmat * vec3(in_normal);\n"
        "\n"
        "  // Transform position into view space;\n"
        "  vec4 v_pos = u_mvmat * in_vertex;\n"
        "  ex_pos = v_pos.xyz * v_pos.w;\n"
        "\n"
        "  // Compute vertex position\n"
        "  gl_Position = u_mvpmat * in_vertex;\n"
        "}\n"
        ;

    std::string fs_str =
        glslDefHeader150Source() +
        glslFnComputeLightingSource() +

        "uniform mat4      u_mvmat;\n"
        "\n"
        "uniform vec4      u_mat_amb;\n"
        "uniform vec4      u_mat_dif;\n"
        "uniform vec4      u_mat_spc;\n"
        "uniform float     u_mat_shi;\n"
        "\n"
        "smooth in vec3    ex_pos;\n"
        "smooth in vec3    ex_normal;\n"
        "\n"
        "out vec4 gl_FragColor;\n"
        "\n"
        "void main() {\n"
        "\n"
        "  vec3 normal = normalize( ex_normal );\n"
        "\n"
        "  Material mat;\n"
        "  mat.ambient   = u_mat_amb;\n"
        "  mat.diffuse   = u_mat_dif;\n"
        "  mat.specular  = u_mat_spc;\n"
        "  mat.shininess = u_mat_shi;\n"
        "\n"
        "  vec4 light_color = vec4(0.0);\n"
        "\n"
        "  gl_FragColor = computeLighting( mat, ex_pos, normal );\n"
        "}\n"
        ;

    bool compile_ok, link_ok;

    VertexShader vshader;
    vshader.create("phong_vs");
    vshader.setPersistent(true);
    vshader.setSource(vs_str);
    compile_ok = vshader.compile();
    assert(compile_ok);

    FragmentShader fshader;
    fshader.create("phong_fs");
    fshader.setPersistent(true);
    fshader.setSource(fs_str);
    compile_ok = fshader.compile();
    if( !compile_ok ) {
      std::cout << "Src:" << std::endl << fshader.getSource() << std::endl << std::endl;
      std::cout << "Error: " << fshader.getCompilerLog() << std::endl;
    }
    assert(compile_ok);

    Program phong_prog;
    phong_prog.create("phong");
    phong_prog.setPersistent(true);
    phong_prog.attachShader( vshader );
    phong_prog.attachShader( fshader );
    link_ok = phong_prog.link();
    assert(link_ok);
  }



//  Program         OpenGLManager::_prog_color;
//  VertexShader    OpenGLManager::_vs_color;
//  FragmentShader  OpenGLManager::_fs_color;

  void OpenGLManager::initColorProg() {

    std::string vs_src =
          "#version 150 core\n"
          "\n"
          "uniform mat4 u_mvpmat;\n"
          "\n"
          "in vec4 in_vertex;\n"
          "\n"
          "out vec4 gl_Position;\n"
          "\n"
          "void main() {\n"
          "\n"
          "  gl_Position = u_mvpmat * in_vertex;\n"
          "}\n"
          ;


    std::string fs_src =
          "#version 150 core\n"
          "\n"
          "uniform vec4 u_color;\n"
          "\n"
          "out vec4 gl_FragColor;\n"
          "\n"
          "void main() {\n"
          "\n"
          "  gl_FragColor = u_color;\n"
          "}\n"
          ;

    bool compile_ok, link_ok;

    VertexShader _vs_color;
    _vs_color.create("color_vs");
    _vs_color.setPersistent(true);
    _vs_color.setSource(vs_src);
    compile_ok = _vs_color.compile();
    assert(compile_ok);

    FragmentShader _fs_color;
    _fs_color.create("color_fs");
    _fs_color.setPersistent(true);
    _fs_color.setSource(fs_src);
    compile_ok = _fs_color.compile();
    assert(compile_ok);

    Program _prog_color;
    _prog_color.create("color");
    _prog_color.setPersistent(true);
    _prog_color.attachShader(_vs_color);
    _prog_color.attachShader(_fs_color);
    link_ok = _prog_color.link();
    assert(link_ok);
  }




//  Program         OpenGLManager::_prog_pcurve_contours;
//  VertexShader    OpenGLManager::_vs_pcurve_contours;
//  FragmentShader  OpenGLManager::_fs_pcurve_contours;

//  void OpenGLManager::initPCurveContoursProg() {

//    std::string vs_src(
//          "#version 150 core\n"
//          "\n"
//          "uniform mat4 u_mvpmat;\n"
//          "\n"
//          "in vec4 in_vertex;\n"
//          "in vec4 in_color;\n"
//          "\n"
//          "out vec4 ex_color;\n"
//          "out vec4 gl_Position;\n"
//          "\n"
//          "void main() {\n"
//          "\n"
//          "  ex_color = in_color;\n"
//          "  gl_Position = u_mvpmat * in_vertex;\n"
//          "}\n"
//          );

//    std::string fs_src(
//          "#version 150 core\n"
//          "\n"
//          "uniform bool u_selected;\n"
//          "\n"
//          "in vec4 ex_color;\n"
//          "\n"
//          "out vec4 gl_FragColor;\n"
//          "\n"
//          "void main() {\n"
//          "\n"
//          "  gl_FragColor = ex_color;\n"
//          "}\n"
//          );

//  bool compile_ok, link_ok;

//    _vs_pcurve_contours.create("pcurve_contours_vs");
//    _vs_pcurve_contours.setSource(vs_src);
//    compile_ok = _vs_pcurve_contours.compile();
//  assert(compile_ok);

//    _fs_pcurve_contours.create("pcurve_contours_fs");
//    _fs_pcurve_contours.setSource(fs_src);
//    compile_ok = _fs_pcurve_contours.compile();
//  assert(compile_ok);

//    _prog_pcurve_contours.create("pcurve_contours");
//    _prog_pcurve_contours.attachShader(_vs_pcurve_contours);
//    _prog_pcurve_contours.attachShader(_fs_pcurve_contours);
//    link_ok = _prog_pcurve_contours.link();
//  assert(link_ok);
//  }



//  Program         OpenGLManager::_prog_psurf_contours;
//  VertexShader    OpenGLManager::_vs_psurf_contours;
//  FragmentShader  OpenGLManager::_fs_psurf_contours;

//  void OpenGLManager::initPSurfContours() {

//    std::string vs_src;
//    vs_src.append( glslDefHeader150Source() );
//    vs_src.append(
//      "uniform mat4 u_mvmat, u_mvpmat;\n"
//      "\n"
//      "in vec4 in_vertex;\n"
//      "in vec2 in_tex;\n"
//      "\n"
//      "out vec4 gl_Position;\n"
//      "\n"
//      "smooth out vec3 ex_pos;\n"
//      "smooth out vec2 ex_tex;\n"
//      "\n"
//      "void main() {\n"
//      "\n"
//      "  vec4 v_pos = u_mvmat * in_vertex;\n"
//      "  ex_pos = v_pos.xyz * v_pos.w;\n"
//      "\n"
//      "  ex_tex = in_tex;\n"
//      "\n"
//      "  gl_Position = u_mvpmat * in_vertex;\n"
//      "}\n"
//    );

//    std::string fs_src;
//    fs_src.append( glslDefHeader150Source() );
//    fs_src.append( glslStructMaterialSource() );
//    fs_src.append( glslUniformLightsSource() );
//    fs_src.append( glslFnSunlightSource() );
//    fs_src.append( glslFnPointlightSource() );
//    fs_src.append( glslFnSpotlightSource() );
//    fs_src.append( glslFnComputeLightingSource() );
//    fs_src.append(
//      "uniform bool      u_selected;\n"
//      "uniform vec4      u_color;\n"
//      "uniform sampler2D u_nmap;\n"
//      "uniform sampler2D u_du_map;\n"
//      "uniform sampler2D u_dv_map;\n"
//      "uniform mat4      u_mvmat;\n"
//      "\n"
//      "uniform vec4      u_mat_amb;\n"
//      "uniform vec4      u_mat_dif;\n"
//      "uniform vec4      u_mat_spc;\n"
//      "uniform float     u_mat_shi;\n"
//      "\n"
//      "smooth in vec3    ex_pos;\n"
//      "smooth in vec2    ex_tex;\n"
//      "\n"
//      "out vec4 gl_FragColor;\n"
//      "\n"
//      "void main() {\n"
//      "\n"
//      "  mat3 nmat = inverse( transpose( mat3( u_mvmat ) ) );\n"
//      "  vec3 nmap_normal = texture( u_nmap, ex_tex.st).xyz;\n"
//      "  vec3 normal = normalize( nmat * nmap_normal );\n"
//      "\n"
//      "  Material mat;\n"
//      "  mat.ambient   = u_mat_amb;\n"
//      "  mat.diffuse   = u_mat_dif;\n"
//      "  mat.specular  = u_mat_spc;\n"
//      "  mat.shininess = u_mat_shi;\n"
//      "\n"
//      "  vec4 light_color = vec4(0.0);\n"
//      "\n"
//      "  gl_FragColor = computeLighting( mat, normal, ex_pos );\n"
//      "}\n"
//    );

//  bool compile_ok, link_ok;

//    _vs_psurf_contours.create("psurf_contours_vs");
//    _vs_psurf_contours.setSource(vs_src);
//    compile_ok = _vs_psurf_contours.compile();
//  assert(compile_ok);

//    _fs_psurf_contours.create("psurf_contours_fs");
//    _fs_psurf_contours.setSource(fs_src);
//    compile_ok = _fs_psurf_contours.compile();
//  assert(compile_ok);

//    _prog_psurf_contours.create("psurf_contours");
//    _prog_psurf_contours.attachShader(_vs_psurf_contours);
//    _prog_psurf_contours.attachShader(_fs_psurf_contours);
//    link_ok = _prog_psurf_contours.link();
//  assert(link_ok);
//  }




  /////////////////////////
  ///
  /// GLSL Helper functions
  ///

  std::string OpenGLManager::glslDefHeader150Source() {

    return
        "#version 150 core\n"
        "\n"
        "layout(std140) uniform;\n"
        "\n"
        ;
  }

  std::string OpenGLManager::glslStructMaterialSource() {

    return
        "\n"
        "struct Material {\n"
        "  vec4  ambient;\n"
        "  vec4  diffuse;\n"
        "  vec4  specular;\n"
        "  float shininess;\n"
        "};\n"
        "\n"
        "\n"
        ;
  }

  std::string OpenGLManager::glslStructLightSource() {

    return
        "struct Light {\n"
        "\n"
        "  vec4  ambient;\n"
        "  vec4  diffuse;\n"
        "  vec4  specular;\n"
        "  \n"
        "  vec4  position;\n"
        "  vec3  direction;\n"
        "\n"
        "  vec3  att;\n"
        "\n"
        "  float spot_cut;\n"
        "  float spot_exp;\n"
        "};\n"
        "\n"
        ;
  }

  std::string OpenGLManager::glslUniformLightsSource() {

    return
        glslStructLightSource() +

        "uniform Lights {\n"
        "  uvec4 info;\n"
        "  Light light[200];\n"
        "} u_lights;\n"
        "\n"
        "\n"
        ;
  }

  std::string OpenGLManager::glslFnSunlightSource() {

    return
        "vec4\n"
        "sunLight( Light light, Material mat, vec3 pos, vec3 normal ) {\n"
        "\n"
        "  vec4 eyeCoords = vec4( pos, 1.0 ); \n"
        "  vec3 s = normalize( vec3( light.position - eyeCoords ) ); \n"
        "  return mat.diffuse * light.ambient * max( dot( s, normal ), 0.0 ); \n"
        "}\n"
        "\n"
        ;
  }

  std::string OpenGLManager::glslFnPointlightSource() {

    return
        "vec4\n"
        "pointLight( Light light, Material mat, vec3 pos, vec3 normal ) {\n"
        "\n"
        "  vec4 eyeCoords = vec4(pos,1.0); \n"
        "\n"
        "  vec3 s = normalize( vec3( light.position - eyeCoords ) ); \n"
        "  vec3 v = normalize( -eyeCoords.xyz ); \n"
        "  vec3 r = reflect( -s, normal ); \n"
        "\n"
        "  vec3 ambient = vec3(light.ambient * mat.ambient); \n"
        "  float sDotN = max( dot(s,normal), 0.0 ); \n"
        "\n"
        "  vec3 diffuse = vec3(light.diffuse * mat.diffuse * sDotN); \n"
        "\n"
        "  vec3 spec = vec3(0.0); \n"
        "  if( sDotN > 0.0 ) \n"
        "    spec = vec3(light.specular * mat.specular * pow( max( dot(r,v), 0.0 ), mat.shininess )); \n"
        "\n"
        "  return vec4(ambient + diffuse + spec, 1.0); \n"
        "}\n"
        "\n"
        ;
  }

  std::string OpenGLManager::glslFnSpotlightSource() {

    return
        "vec4\n"
        "spotLight( Light light, Material mat, vec3 pos, vec3 normal ) {\n"
        "\n"
        "  vec4 eyeCoords = vec4(pos,1.0); \n"
        "\n"
        "  vec3 s = normalize( vec3( light.position - eyeCoords ) ); \n"
        "  vec3 v = normalize( -eyeCoords.xyz ); \n"
        "  vec3 r = reflect( -s, normal ); \n"
        "\n"
        "  vec3 ambient = vec3(light.ambient * mat.ambient); \n"
        "  float sDotN = max( dot(s,normal), 0.0 ); \n"
        "\n"
        "  vec3 diffuse = vec3(light.diffuse * mat.diffuse * sDotN); \n"
        "\n"
        "  vec3 spec = vec3(0.0); \n"
        "  if( sDotN > 0.0 ) \n"
        "    spec = vec3(light.specular * mat.specular * pow( max( dot(r,v), 0.0 ), mat.shininess )); \n"
        "\n"
        "  // Attenuation \n"
        "  float attenuation = 0.0; \n"
        "\n"
        "  // Spot attenuation\n"
        "  float sDotLdir = dot(-s, normalize(light.direction)); \n"
        "  if( sDotLdir > cos( light.spot_cut ) ) \n"
        "    attenuation += pow( sDotLdir, light.spot_exp ); \n"
        "    "
        "  return vec4( (ambient + diffuse + spec) * attenuation, 1.0); \n"
        "}\n"
        "\n"
        ;
  }

  std::string OpenGLManager::glslFnComputeLightingSource() {

    return
        glslStructMaterialSource() +
        glslUniformLightsSource() +
        glslFnSunlightSource() +
        glslFnPointlightSource() +
        glslFnSpotlightSource() +

        "vec4\n"
        "computeLighting(Material mat, vec3 pos, vec3 normal ) {\n"
        "\n"
        "  vec4 color = vec4(0.0);\n"
        "\n"
        "  // Compute sun contribution\n"
        "  for( uint i = uint(0); i < u_lights.info[0]; ++i )\n"
        "    color += sunLight( u_lights.light[i], mat, pos, normal );\n"
        "\n"
        "  // Compute point light contribution\n"
        "  for( uint i = u_lights.info[0]; i < u_lights.info[1]; ++i )\n"
        "    color += pointLight( u_lights.light[i], mat, pos, normal );\n"
        "\n"
        "  // Compute spot light contribution\n"
        "  for( uint i = u_lights.info[1]; i < u_lights.info[2]; ++i )\n"
        "    color += spotLight( u_lights.light[i], mat, pos, normal );\n"
//        "    color += spotLight(  u_lights.light[i], mat, pos, normal );\n"
        "\n"
//        "  if( gl_FrontFacing )\n"
        "    return color;\n"
//        "  else\n"
//        "    return vec4(0.0);\n"
        "}\n"
        "\n"
        ;
  }


} // END namespace GL
} // END namespace GMlib
