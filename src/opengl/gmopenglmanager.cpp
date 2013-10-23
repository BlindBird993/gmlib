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




  ///////////////////////
  ///
  /// System wide buffers
  ///

  VertexBufferObject  OpenGLManager::_std_rep_cube;
  IndexBufferObject   OpenGLManager::_std_rep_cube_indices;
  IndexBufferObject   OpenGLManager::_std_rep_frame_indices;

  UniformBufferObject OpenGLManager::_lights_ubo;

  void OpenGLManager::initSystemWideBuffers() {

    _std_rep_cube.create("std_rep_cube");
    _std_rep_cube_indices.create("std_rep_cube_indices");
    _std_rep_frame_indices.create("std_rep_frame_indices");

    _lights_ubo.create("lights_ubo");
  }




  ////////////////////////////////////
  ///
  /// System wide Programs and Shaders
  ///

  void OpenGLManager::initSystemWideShadersAndPrograms() {

    initDefaultProg();
    initPhongProg();
    initColorProg();

    initSelectProg();

    initRenderProg();
    initRenderSelectProg();

    initPCurveContoursProg();

    initPSurfPhongNMapProg();
    initPSurfPhongNMapPTexProg();
    initPSurfContours();
  }



  Program         OpenGLManager::_prog_default;
  VertexShader    OpenGLManager::_vs_default;
  FragmentShader  OpenGLManager::_fs_default;

  void OpenGLManager::initDefaultProg() {

    // Vertex shader
    std::string vs_src (
        "#version 150 compatibility\n"
        "\n"
        "uniform mat4 u_mvmat;\n"
        "uniform mat4 u_mvpmat;\n"
        "uniform bool u_selected;\n"
        "uniform vec4 u_mat_dif;\n"
        "uniform vec4 u_light_pos;\n"
        "uniform vec4 u_light_dif;\n"
        "uniform vec4 u_amb;\n"
        "uniform vec4 u_dif;\n"
        "\n"
        "in vec4 in_vertex;\n"
        "in vec4 in_normal;\n"
        "\n"
        "out vec4 ex_amb_global, ex_amb, ex_dif;\n"
        "out vec3 ex_normal, ex_light_dir, ex_half_vector;\n"
        "out float ex_light_length;\n"
        "\n"
        "out vec4 gl_Position;\n"
        "\n"
        "void main() {\n"
        "\n"
        "  vec4 vertex;\n"
        "  vec3 light_vector;\n"
        "\n"
        "  // Transform the normal to eye space (normalized)\n"
        "  mat3 nmat = inverse( transpose( mat3( u_mvmat ) ) );\n"
        "  ex_normal = normalize(nmat * vec3(in_normal));\n"
        "\n"
        "  // Light direction\n"
        "  vertex = u_mvmat * in_vertex;\n"
        "  light_vector = vec3(gl_LightSource[0].position-vertex);\n"
        "  ex_light_dir = normalize(light_vector);\n"
        "  ex_light_length = length(light_vector);\n"
        "\n"
        "  ex_half_vector = normalize(gl_LightSource[0].halfVector.xyz);\n"
        "\n"
        "  // Compute the diffuse term\n"
        "  ex_dif = u_dif * gl_LightSource[0].diffuse;\n"
        "\n"
        "  // Compute ambient attenuation\n"
        "  ex_amb = u_amb * gl_LightSource[0].ambient;\n"
        "  ex_amb_global = gl_LightModel.ambient * u_amb;\n"
        "\n"
        "  gl_Position = u_mvpmat * in_vertex;\n"
        "}\n"
        );


    // Fragment shader
    std::string fs_src(
        "#version 150 compatibility\n"
        "\n"
        "uniform vec4 u_spc;\n"
        "uniform float u_shin;\n"
        "uniform bool u_selected;\n"
        "uniform vec4 u_color;\n"
        "uniform bool u_lighted;\n"
        "\n"
        "in vec4 ex_amb_global, ex_amb, ex_dif;\n"
        "in vec3 ex_normal, ex_light_dir, ex_half_vector;\n"
        "in float ex_light_length;\n"
        "\n"
        "out vec4 gl_FragColor;\n"
        "\n"
        "void main() {\n"
        "\n"
        "  vec3 N, halfV, viewV, ldir;\n"
        "  float NdotL, NdotHV;\n"
        "  vec4 color;\n"
        "  float att;\n"
        "\n"
        "  // Set color to the ambient global color\n"
        "  color = ex_amb_global;\n"
        "\n"
        "  // Normalize the interpolated normal\n"
        "  N = normalize(ex_normal);\n"
        "\n"
        "  // Compute the length of the projection of the light onto the normal\n"
        "  NdotL = max( dot( N, normalize(ex_light_dir) ), 0.0 );\n"
        "\n"
        "  // If the length of the projection is positive compute the spesific light\n"
        "  // contribution to the color of the fragment\n"
        "  if( NdotL > 0.0 ) {\n"
        "\n"
        "    // Attenuation of difuse and ambient terms\n"
        "    att =\n"
        "      1.0 / (gl_LightSource[0].constantAttenuation +\n"
        "      gl_LightSource[0].linearAttenuation * ex_light_length +\n"
        "      gl_LightSource[0].quadraticAttenuation * ex_light_length * ex_light_length);\n"
        "\n"
        "    color += att * (ex_dif * NdotL + ex_amb);\n"
        "\n"
        "    // Specular term and shininess\n"
        "    halfV = normalize(ex_half_vector);\n"
        "    NdotHV = max(dot(N,halfV),0.0);\n"
        "\n"
        "    color +=\n"
        "      att *\n"
        "      u_spc * gl_LightSource[0].specular *\n"
        "      pow( NdotHV, u_shin );\n"
        "  }\n"
        "\n"
        "  if( !u_lighted )\n"
        "    color = u_color;\n"
        "\n"
        "  gl_FragColor = color;\n"
        "}\n"
        );


    _vs_default.create("default_vs");
    _vs_default.setSource(vs_src);
    assert(_vs_default.compile());

    _fs_default.create("default_fs");
    _fs_default.setSource(fs_src);
    assert(_fs_default.compile()) ;

    _prog_default.create("default");
    _prog_default.attachShader(_vs_default);
    _prog_default.attachShader(_fs_default);
    assert(_prog_default.link());
  }



  Program         OpenGLManager::_prog_phong;
  VertexShader    OpenGLManager::_vs_phong;
  FragmentShader  OpenGLManager::_fs_phong;

  void OpenGLManager::initPhongProg() {

    ///////////////
    // Phong shader
    std::string vs_str;
    vs_str.append( glslDefHeader150() );
    vs_str.append(
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
      "smooth out vec2 ex_tex;\n"
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
      "  // Pass through the tex coord\n"
      "  ex_tex = in_tex;\n"
      "\n"
      "  // Compute vertex position\n"
      "  gl_Position = u_mvpmat * in_vertex;\n"
      "}\n"
    );

    std::string fs_str;
    fs_str.append( glslDefHeader150() );
    fs_str.append( glslStructMaterial() );
    fs_str.append( glslUniformLights() );
    fs_str.append( glslFnSunlight() );
    fs_str.append( glslFnPointlight() );
    fs_str.append( glslFnSpotlight() );
    fs_str.append( glslFnComputeLighting() );
    fs_str.append(
      "uniform mat4      u_mvmat;\n"
      "\n"
      "uniform vec4      u_mat_amb;\n"
      "uniform vec4      u_mat_dif;\n"
      "uniform vec4      u_mat_spc;\n"
      "uniform float     u_mat_shi;\n"
      "\n"
      "smooth in vec3    ex_pos;\n"
      "smooth in vec3    ex_normal;\n"
      "smooth in vec2    ex_tex;\n"
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
      "  gl_FragColor = computeLighting( mat, normal, ex_pos );\n"
      "}\n"
    );


    _vs_phong.create("phong_vs");
    _vs_phong.setSource(vs_str);
    assert(_vs_phong.compile());

    _fs_phong.create("phong_fs");
    _fs_phong.setSource(fs_str);
    assert( _fs_phong.compile() );

    _prog_phong.create("phong");
    _prog_phong.attachShader( _vs_phong );
    _prog_phong.attachShader( _fs_phong );
    assert( _prog_phong.link() );
  }



  Program         OpenGLManager::_prog_color;
  VertexShader    OpenGLManager::_vs_color;
  FragmentShader  OpenGLManager::_fs_color;

  void OpenGLManager::initColorProg() {

    std::string vs_src(
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
          );


    std::string fs_src (
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
          );


    _vs_color.create("color_vs");
    _vs_color.setSource(vs_src);
    assert(_vs_color.compile());

    _fs_color.create("color_fs");
    _fs_color.setSource(fs_src);
    assert(_fs_color.compile()) ;

    _prog_color.create("color");
    _prog_color.attachShader(_vs_color);
    _prog_color.attachShader(_fs_color);
    assert(_prog_color.link());
  }



  Program         OpenGLManager::_prog_select;
  VertexShader    OpenGLManager::_vs_select;
  FragmentShader  OpenGLManager::_fs_select;

  void OpenGLManager::initSelectProg() {

    std::string vs_src(
          "#version 150 compatibility \n"
          "uniform mat4 u_mvpmat; \n"
          "uniform vec4 u_color; \n"
          "\n"
          "in vec4 in_vertex; \n"
          "\n"
          "out vec4 ex_color; \n"
          "out vec4 gl_Position; \n"
          "\n"
          "void main() \n"
          "{ \n"
          "  gl_Position = u_mvpmat * in_vertex; \n"
          "  ex_color = u_color; \n"
          "}\n"
          );

    std::string fs_src(
          "#version 150 compatibility \n"
          "\n"
          "in vec4 ex_color; \n"
          "\n"
          "out vec4 gl_FragColor; \n"
          "\n"
          "void main() \n"
          "{ \n"
          "  gl_FragColor = ex_color; \n"
          "} \n"
          );

    _vs_select.create("select_vs");
    _vs_select.setSource(vs_src);
    assert(_vs_select.compile());

    _fs_select.create("select_fs");
    _fs_select.setSource(fs_src);
    assert(_fs_select.compile()) ;

    _prog_select.create("select");
    _prog_select.attachShader(_vs_select);
    _prog_select.attachShader(_fs_select);
    assert(_prog_select.link());
  }



  Program         OpenGLManager::_prog_render;
  VertexShader    OpenGLManager::_vs_render;
  FragmentShader  OpenGLManager::_fs_render;

  void OpenGLManager::initRenderProg() {

    std::string vs_src(
          "#version 150 core\n"
          "\n"
          "uniform mat4 u_mvpmat;\n"
          "\n"
          "in vec4 in_vertex;\n"
          "in vec2 in_tex_coord;\n"
          "\n"
          "out vec2 ex_tex_coord;\n"
          "out vec4 gl_Position;\n"
          "\n"
          "void main() {\n"
          "\n"
          "  ex_tex_coord = in_tex_coord;\n"
          "  gl_Position = u_mvpmat * in_vertex;\n"
          "}\n"
          );

    std::string fs_src(
          "#version 150 core\n"
          "\n"
          "uniform sampler2D u_tex;\n"
          "uniform sampler2D u_tex_selected;\n"
          "uniform float u_buf_w;\n"
          "uniform float u_buf_h;\n"
          "uniform vec4 u_select_color;\n"
          "\n"
          "in vec2 ex_tex_coord;\n"
          "\n"
          "out vec4 gl_FragColor;\n"
          "\n"
          "float avg( vec4 v ) {\n"
          "\n"
          "  return ( v.r + v.g + v. b ) / 4.0;\n"
          "}\n"
          "\n"
          "\n"
          "float runFilter( mat3 mask, float w, float h ) {\n"
          "\n"
          "  float result = 0; //vec4( 0.0, 0.0, 0.0, 0.0 );\n"
          "\n"
          "  for( float i = -1.0; i <= 1.0; i = i + 1.0 ) {\n"
          "    for( float j = -1.0; j <= 1.0; j = j + 1.0 ) {\n"
          "\n"
          "      float x = ex_tex_coord.x + ( (i + 0.5) / w );\n"
          "      float y = ex_tex_coord.y + ( (j + 0.5) / h );\n"
          "\n"
          "      float sub_res = avg( texture2D( u_tex_selected, vec2( x, y ) ) );\n"
          "\n"
          "      result += sub_res * avg(\n"
          "        vec4(\n"
          "          mask[int(i+1.0)][int(j+1.0)],\n"
          "          mask[int(i+1.0)][int(j+1.0)],\n"
          "          mask[int(i+1.0)][int(j+1.0)],\n"
          "          mask[int(i+1.0)][int(j+1.0)]\n"
          "        )\n"
          "        );\n"
          "    }\n"
          "  }\n"
          "\n"
          "  return result;\n"
          "}\n"
          "\n"
          "void main() {\n"
          "\n"
          "  // x and y sobel filters\n"
          "  mat3 mask_x = mat3(\n"
          "    -1.0, 0.0, 1.0,\n"
          "    -2.0, 0.0, 2.0,\n"
          "    -1.0, 0.0, 1.0\n"
          "    );\n"
          "\n"
          "  mat3 mask_y =  mat3(\n"
          "     1.0,  2.0,  1.0,\n"
          "     0.0,  0.0,  0.0,\n"
          "    -1.0, -2.0, -1.0\n"
          "    );\n"
          "\n"
          "  // summation vars.\n"
          "  float res_x = runFilter( mask_x, u_buf_w, u_buf_h );\n"
          "  float res_y = runFilter( mask_y, u_buf_w, u_buf_h );\n"
          "  float res = sqrt( res_x * res_x + res_y * res_y );\n"
          "\n"
          "  gl_FragColor = texture( u_tex, ex_tex_coord );\n"
          "\n"
          "  if( res > 0.0 )\n"
          "   gl_FragColor = u_select_color;\n"
          "}\n"
          );


    _vs_render.create("render_vs");
    _vs_render.setSource(vs_src);
    assert(_vs_render.compile());

    _fs_render.create("render_fs");
    _fs_render.setSource(fs_src);
    assert(_fs_render.compile()) ;

    _prog_render.create("render");
    _prog_render.attachShader(_vs_render);
    _prog_render.attachShader(_fs_render);
    assert(_prog_render.link());
  }



  Program         OpenGLManager::_prog_render_select;
  VertexShader    OpenGLManager::_vs_render_select;
  FragmentShader  OpenGLManager::_fs_render_select;

  void OpenGLManager::initRenderSelectProg() {

    std::string vs_src(
          "#version 150 compatibility \n"
          "uniform mat4 u_mvpmat; \n"
          "uniform vec4 u_color; \n"
          "\n"
          "in vec4 in_vertex; \n"
          "\n"
          "out vec4 gl_Position; \n"
          "\n"
          "void main() \n"
          "{ \n"
          "  gl_Position = u_mvpmat * in_vertex; \n"
          "}\n"
          );

    std::string fs_src(
          "#version 150 compatibility \n"
          "\n"
          "out vec4 gl_FragColor; \n"
          "\n"
          "void main() \n"
          "{ \n"
          "  gl_FragColor = vec4( 1.0, 1.0, 1.0, 1.0 ); \n"
          "} \n"
          );

    _vs_render_select.create("render_select_vs");
    _vs_render_select.setSource(vs_src);
    assert(_vs_render_select.compile());

    _fs_render_select.create("render_select_fs");
    _fs_render_select.setSource(fs_src);
    assert(_fs_render_select.compile()) ;

    _prog_render_select.create("render_select");
    _prog_render_select.attachShader(_vs_render_select);
    _prog_render_select.attachShader(_fs_render_select);
    assert(_prog_render_select.link());
  }



  Program         OpenGLManager::_prog_pcurve_contours;
  VertexShader    OpenGLManager::_vs_pcurve_contours;
  FragmentShader  OpenGLManager::_fs_pcurve_contours;

  void OpenGLManager::initPCurveContoursProg() {

    std::string vs_src(
          "#version 150 core\n"
          "\n"
          "uniform mat4 u_mvpmat;\n"
          "\n"
          "in vec4 in_vertex;\n"
          "in vec4 in_color;\n"
          "\n"
          "out vec4 ex_color;\n"
          "out vec4 gl_Position;\n"
          "\n"
          "void main() {\n"
          "\n"
          "  ex_color = in_color;\n"
          "  gl_Position = u_mvpmat * in_vertex;\n"
          "}\n"
          );

    std::string fs_src(
          "#version 150 core\n"
          "\n"
          "uniform bool u_selected;\n"
          "\n"
          "in vec4 ex_color;\n"
          "\n"
          "out vec4 gl_FragColor;\n"
          "\n"
          "void main() {\n"
          "\n"
          "  gl_FragColor = ex_color;\n"
          "}\n"
          );

    _vs_pcurve_contours.create("pcurve_contours_vs");
    _vs_pcurve_contours.setSource(vs_src);
    assert(_vs_pcurve_contours.compile());

    _fs_pcurve_contours.create("pcurve_contours_fs");
    _fs_pcurve_contours.setSource(fs_src);
    assert(_fs_pcurve_contours.compile()) ;

    _prog_pcurve_contours.create("pcurve_contours");
    _prog_pcurve_contours.attachShader(_vs_pcurve_contours);
    _prog_pcurve_contours.attachShader(_fs_pcurve_contours);
    assert(_prog_pcurve_contours.link());
  }




  Program         OpenGLManager::_prog_psurf_phong_nmap;
  VertexShader    OpenGLManager::_vs_psurf_phong_nmap;
  FragmentShader  OpenGLManager::_fs_psurf_phong_nmap;

  void OpenGLManager::initPSurfPhongNMapProg() {

    std::string vs_src;
    vs_src.append( glslDefHeader150() );
    vs_src.append(
      "uniform mat4 u_mvmat, u_mvpmat;\n"
      "\n"
      "in vec4 in_vertex;\n"
      "in vec2 in_tex;\n"
      "\n"
      "out vec4 gl_Position;\n"
      "\n"
      "smooth out vec3 ex_pos;\n"
      "smooth out vec2 ex_tex;\n"
      "\n"
      "void main() {\n"
      "\n"
      "  vec4 v_pos = u_mvmat * in_vertex;\n"
      "  ex_pos = v_pos.xyz * v_pos.w;\n"
      "\n"
      "  ex_tex = in_tex;\n"
      "\n"
      "  gl_Position = u_mvpmat * in_vertex;\n"
      "}\n"
    );

    std::string fs_src;
    fs_src.append( glslDefHeader150() );
    fs_src.append( glslStructMaterial() );
    fs_src.append( glslUniformLights() );
    fs_src.append( glslFnSunlight() );
    fs_src.append( glslFnPointlight() );
    fs_src.append( glslFnSpotlight() );
    fs_src.append( glslFnComputeLighting() );
    fs_src.append(
      "uniform sampler2D u_nmap;\n"
      "uniform mat4      u_mvmat;\n"
      "\n"
      "uniform vec4      u_mat_amb;\n"
      "uniform vec4      u_mat_dif;\n"
      "uniform vec4      u_mat_spc;\n"
      "uniform float     u_mat_shi;\n"
      "\n"
      "smooth in vec3    ex_pos;\n"
      "smooth in vec2    ex_tex;\n"
      "\n"
      "out vec4 gl_FragColor;\n"
      "\n"
      "void main() {\n"
      "\n"
      "  mat3 nmat = inverse( transpose( mat3( u_mvmat ) ) );\n"
      "  vec3 nmap_normal = texture( u_nmap, ex_tex.st).xyz;\n"
      "  vec3 normal = normalize( nmat * nmap_normal );\n"
      "\n"
      "  Material mat;\n"
      "  mat.ambient   = u_mat_amb;\n"
      "  mat.diffuse   = u_mat_dif;\n"
      "  mat.specular  = u_mat_spc;\n"
      "  mat.shininess = u_mat_shi;\n"
      "\n"
      "  vec4 light_color = vec4(0.0);\n"
      "\n"
      "  gl_FragColor = computeLighting( mat, normal, ex_pos );\n"
      "\n"
      "}\n"
    );

    _vs_psurf_phong_nmap.create("psurf_phong_nmap_vs");
    _vs_psurf_phong_nmap.setSource(vs_src);
    assert(_vs_psurf_phong_nmap.compile());

    _fs_psurf_phong_nmap.create("psurf_phong_nmap_fs");
    _fs_psurf_phong_nmap.setSource(fs_src);
    assert(_fs_psurf_phong_nmap.compile()) ;

    _prog_psurf_phong_nmap.create("psurf_phong_nmap");
    _prog_psurf_phong_nmap.attachShader(_vs_psurf_phong_nmap);
    _prog_psurf_phong_nmap.attachShader(_fs_psurf_phong_nmap);
    assert(_prog_psurf_phong_nmap.link());
  }



  Program         OpenGLManager::_prog_psurf_phong_nmap_ptex;
  VertexShader    OpenGLManager::_vs_psurf_phong_nmap_ptex;
  FragmentShader  OpenGLManager::_fs_psurf_phong_nmap_ptex;

  void OpenGLManager::initPSurfPhongNMapPTexProg() {

    std::string vs_src;
    vs_src.append( glslDefHeader150() );
    vs_src.append(
      "uniform mat4 u_mvmat, u_mvpmat;\n"
      "\n"
      "in vec4 in_vertex;\n"
      "in vec2 in_tex;\n"
      "\n"
      "out vec4 gl_Position;\n"
      "\n"
      "smooth out vec3 ex_pos;\n"
      "smooth out vec2 ex_tex;\n"
      "\n"
      "void main() {\n"
      "\n"
      "  vec4 v_pos = u_mvmat * in_vertex;\n"
      "  ex_pos = v_pos.xyz * v_pos.w;\n"
      "\n"
      "  ex_tex = in_tex;\n"
      "\n"
      "  gl_Position = u_mvpmat * in_vertex;\n"
      "}\n"
    );

    std::string fs_src;
    fs_src.append( glslDefHeader150() );
    fs_src.append( glslStructMaterial() );
    fs_src.append( glslUniformLights() );
    fs_src.append( glslFnSunlight() );
    fs_src.append( glslFnPointlight() );
    fs_src.append( glslFnSpotlight() );
    fs_src.append( glslFnComputeLighting() );
    fs_src.append(
      "uniform sampler2D u_nmap;\n"
      "uniform sampler2D u_ptex_u;\n"
      "uniform sampler2D u_ptex_v;\n"
      "uniform mat4      u_mvmat;\n"
      "\n"
      "uniform vec4      u_mat_amb;\n"
      "uniform vec4      u_mat_dif;\n"
      "uniform vec4      u_mat_spc;\n"
      "uniform float     u_mat_shi;\n"
      "\n"
      "uniform vec4      u_mat_line_amb;\n"
      "uniform vec4      u_mat_line_dif;\n"
      "uniform vec4      u_mat_line_spc;\n"
      "uniform float     u_mat_line_shi;\n"
      "\n"
      "smooth in vec3    ex_pos;\n"
      "smooth in vec2    ex_tex;\n"
      "\n"
      "out vec4 gl_FragColor;\n"
      "\n"
      "void main() {\n"
      "\n"
      "  mat3 nmat = inverse( transpose( mat3( u_mvmat ) ) );\n"
      "  vec3 nmap_normal = texture( u_nmap, ex_tex.st).xyz;\n"
      "  vec3 normal = normalize( nmat * nmap_normal );\n"
      "\n"
      "  float pf_u = texture( u_ptex_u, ex_tex.st ).r;\n"
      "  float pf_v = texture( u_ptex_v, ex_tex.st ).r;\n"
      "\n"
      "  Material mat;\n"
      "\n"
      "  if( max(pf_u,pf_v) < 0.5 ) {\n"
      "    mat.ambient   = u_mat_amb;\n"
      "    mat.diffuse   = u_mat_dif;\n"
      "    mat.specular  = u_mat_spc;\n"
      "    mat.shininess = u_mat_shi;\n"
      "  }\n"
      "  else {\n"
      "    mat.ambient   = u_mat_line_amb;\n"
      "    mat.diffuse   = u_mat_line_dif;\n"
      "    mat.specular  = u_mat_line_spc;\n"
      "    mat.shininess = u_mat_line_shi;\n"
      "  }\n"
      "\n"
      "  vec4 light_color = vec4(0.0);\n"
      "\n"
      "  gl_FragColor = computeLighting( mat, normal, ex_pos );\n"
      "\n"
      "}\n"
    );

    _vs_psurf_phong_nmap_ptex.create("psurf_phong_nmap_ptex_vs");
    _vs_psurf_phong_nmap_ptex.setSource(vs_src);
    assert(_vs_psurf_phong_nmap_ptex.compile());

    _fs_psurf_phong_nmap_ptex.create("psurf_phong_nmap_ptex_fs");
    _fs_psurf_phong_nmap_ptex.setSource(fs_src);
    assert(_fs_psurf_phong_nmap_ptex.compile()) ;

    _prog_psurf_phong_nmap_ptex.create("psurf_phong_nmap_ptex");
    _prog_psurf_phong_nmap_ptex.attachShader(_vs_psurf_phong_nmap_ptex);
    _prog_psurf_phong_nmap_ptex.attachShader(_fs_psurf_phong_nmap_ptex);
    assert(_prog_psurf_phong_nmap_ptex.link());
  }



  Program         OpenGLManager::_prog_psurf_contours;
  VertexShader    OpenGLManager::_vs_psurf_contours;
  FragmentShader  OpenGLManager::_fs_psurf_contours;

  void OpenGLManager::initPSurfContours() {

    std::string vs_src;
    vs_src.append( glslDefHeader150() );
    vs_src.append(
      "uniform mat4 u_mvmat, u_mvpmat;\n"
      "\n"
      "in vec4 in_vertex;\n"
      "in vec2 in_tex;\n"
      "\n"
      "out vec4 gl_Position;\n"
      "\n"
      "smooth out vec3 ex_pos;\n"
      "smooth out vec2 ex_tex;\n"
      "\n"
      "void main() {\n"
      "\n"
      "  vec4 v_pos = u_mvmat * in_vertex;\n"
      "  ex_pos = v_pos.xyz * v_pos.w;\n"
      "\n"
      "  ex_tex = in_tex;\n"
      "\n"
      "  gl_Position = u_mvpmat * in_vertex;\n"
      "}\n"
    );

    std::string fs_src;
    fs_src.append( glslDefHeader150() );
    fs_src.append( glslStructMaterial() );
    fs_src.append( glslUniformLights() );
    fs_src.append( glslFnSunlight() );
    fs_src.append( glslFnPointlight() );
    fs_src.append( glslFnSpotlight() );
    fs_src.append( glslFnComputeLighting() );
    fs_src.append(
      "uniform bool      u_selected;\n"
      "uniform vec4      u_color;\n"
      "uniform sampler2D u_nmap;\n"
      "uniform sampler2D u_du_map;\n"
      "uniform sampler2D u_dv_map;\n"
      "uniform mat4      u_mvmat;\n"
      "\n"
      "uniform vec4      u_mat_amb;\n"
      "uniform vec4      u_mat_dif;\n"
      "uniform vec4      u_mat_spc;\n"
      "uniform float     u_mat_shi;\n"
      "\n"
      "smooth in vec3    ex_pos;\n"
      "smooth in vec2    ex_tex;\n"
      "\n"
      "out vec4 gl_FragColor;\n"
      "\n"
      "void main() {\n"
      "\n"
      "  mat3 nmat = inverse( transpose( mat3( u_mvmat ) ) );\n"
      "  vec3 nmap_normal = texture( u_nmap, ex_tex.st).xyz;\n"
      "  vec3 normal = normalize( nmat * nmap_normal );\n"
      "\n"
      "  Material mat;\n"
      "  mat.ambient   = u_mat_amb;\n"
      "  mat.diffuse   = u_mat_dif;\n"
      "  mat.specular  = u_mat_spc;\n"
      "  mat.shininess = u_mat_shi;\n"
      "\n"
      "  vec4 light_color = vec4(0.0);\n"
      "\n"
      "  gl_FragColor = computeLighting( mat, normal, ex_pos );\n"
      "}\n"
    );

    _vs_psurf_contours.create("psurf_contours_vs");
    _vs_psurf_contours.setSource(vs_src);
    assert(_vs_psurf_contours.compile());

    _fs_psurf_contours.create("psurf_contours_fs");
    _fs_psurf_contours.setSource(fs_src);
    assert(_fs_psurf_contours.compile()) ;

    _prog_psurf_contours.create("psurf_contours");
    _prog_psurf_contours.attachShader(_vs_psurf_contours);
    _prog_psurf_contours.attachShader(_fs_psurf_contours);
    assert(_prog_psurf_contours.link());
  }




  /////////////////////////
  ///
  /// GLSL Helper functions
  ///

  std::string OpenGLManager::glslFnComputeLighting() {

    return
        "vec4\n"
        "computeLighting(Material mat, vec3 normal, vec3 cam_pos) {\n"
        "\n"
        "  vec4 color = vec4(0.0);\n"
        "\n"
        "  // Compute sun contribution\n"
        "  for( uint i = uint(0); i < u_lights.info[0]; ++i )\n"
        "    color += sunLight( u_lights.light[i], mat, normal, cam_pos );\n"
        "\n"
        "  // Compute point light contribution\n"
        "  for( uint i = u_lights.info[0]; i < u_lights.info[1]; ++i )\n"
        "    color += pointLight( u_lights.light[i], mat, normal, cam_pos );\n"
        "\n"
        "  // Compute spot light contribution\n"
        "  for( uint i = u_lights.info[1]; i < u_lights.info[2]; ++i )\n"
        "    color += spotLight(  u_lights.light[i], mat, normal, cam_pos );\n"
        "\n"
        "  return color;\n"
        "}\n"
        "\n"
        ;
  }

  std::string OpenGLManager::glslDefHeader150() {

    return
        "#version 150 core\n"
        "\n"
        "layout(std140) uniform;\n"
        "\n"
        ;
  }

  std::string OpenGLManager::glslStructMaterial() {

    return
        "struct Material {\n"
        "  vec4  ambient;\n"
        "  vec4  diffuse;\n"
        "  vec4  specular;\n"
        "  float shininess;\n"
        "};\n"
        "\n"
        ;
  }

  std::string OpenGLManager::glslStructLight() {

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

  std::string OpenGLManager::glslUniformLights() {

    std::string uniform_lights;
    uniform_lights.append( glslStructLight() );
    uniform_lights.append(
       "uniform Lights {\n"
       "  uvec4 info;\n"
       "  Light light[200];\n"
       "} u_lights;\n"
       "\n"
     );

    return uniform_lights;
  }

  std::string OpenGLManager::glslFnSunlight() {

    return
        "vec4\n"
        "sunLight( Light light, Material mat, vec3 n, vec3 cam_pos ) {\n"
        "\n"
        "  vec3 L = normalize( light.direction ).xyz;\n"
        "  float sun_att, sun_fact;\n"
        "  sun_fact = abs( dot(L,n) );\n"
        "  sun_fact = clamp( sun_fact, 0.0, 1.0 );\n"
        "\n"
        "  return light.ambient * sun_fact;\n"
        "}\n"
        "\n"
        ;
  }

  std::string OpenGLManager::glslFnPointlight() {

    return
        "vec4\n"
        "pointLight( Light light, Material mat, vec3 n, vec3 pos ) {\n"
        "\n"
        "  vec3  L = vec3(light.position) - pos;\n"
        "  float dL = length( L );\n"
        "  L = normalize( L );\n"
        "  vec3  e = normalize( -pos );\n"
        "  vec3  s = normalize( L + e );\n"
        "\n"
        "  float attenuation =  1.0 / ( light.att[0] +\n"
        "                               light.att[1] * dL +\n"
        "                               light.att[2] * dL * dL );\n"
        "  // calculate ambient term\n"
        "  vec4 amb =  light.ambient * mat.ambient;\n"
        "\n"
        "  // calculate diffuse term\n"
        "  vec4 diff = light.diffuse * mat.diffuse * max( abs( dot(L,n) ), 0.0);\n"
        "  diff = clamp( diff, 0.0, 1.0 );\n"
        "\n"
        "  // calculate specular term\n"
        "  vec4 spec = light.specular * mat.specular * \n"
        "              pow( max( dot(s,n), 0.0), 0.3 * mat.shininess );\n"
        "  spec = clamp( spec, 0.0, 1.0 );\n"
        "\n"
        "  // return color\n"
        "  return (amb + diff + spec) * attenuation;\n"
        "}\n"
        "\n"
        ;
  }

  std::string OpenGLManager::glslFnSpotlight() {

    return
        "vec4\n"
        "spotLight( Light light, Material mat, vec3 n, vec3 cam_pos ) {\n"
        "\n"
        "  vec3  L = vec3(light.position) - cam_pos;\n"
        "  float dL = length( L );\n"
        "  L = normalize( L );\n"
        "  vec3  e = normalize( -cam_pos );\n"
        "  vec3  s = normalize( L + e );\n"
        "\n"
        "  // Attenuation\n"
        "  float attenuation =  1.0 / ( light.att[0] +\n"
        "                               light.att[1] * dL +\n"
        "                               light.att[2] * dL * dL );\n"
        "\n"
        "  // Spot attenuation\n"
        "  float spot_att = abs( dot(-L, normalize(light.direction)) );\n"
        "  if( spot_att < light.spot_cut )\n"
        "    spot_att = 0.0;\n"
        "  else\n"
        "    spot_att = pow( spot_att, light.spot_exp );\n"
        "  attenuation *= spot_att;\n"
        "\n"
        "  // calculate ambient term\n"
        "  vec4 amb =  light.ambient * mat.ambient;\n"
        "\n"
        "  // calculate diffuse term\n"
        "  vec4 diff = light.diffuse * mat.diffuse * max( abs( dot(L,n) ), 0.0);\n"
        "  diff = clamp( diff, 0.0, 1.0 );\n"
        "\n"
        "  // calculate specular term\n"
        "  vec4 spec = light.specular * mat.specular * \n"
        "              pow( max( dot(s,n), 0.0), 0.3 * mat.shininess );\n"
        "  spec = clamp( spec, 0.0, 1.0 );\n"
        "\n"
        "  // return color\n"
        "  return (amb + diff + spec) * attenuation;\n"
        "}\n"
        "\n"
        ;

  }



} // END namespace GL
} // END namespace GMlib
