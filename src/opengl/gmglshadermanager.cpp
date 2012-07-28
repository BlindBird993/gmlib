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



/*! \file gmglshadermanager.cpp
 *
 *  Pending Documentation
 */


#include "gmglshadermanager.h"
using namespace GMlib;


// stl
#include <iostream>



bool GLShaderManager::_initialized = false;
std::string GLShaderManager::_log;
std::string GLShaderManager::_info_log;
std::map< std::string, GLShaderManager::ProgramInfo >   GLShaderManager::_programs;
std::map< std::string, GLShaderManager::ShaderInfo >    GLShaderManager::_shaders;
std::map< std::string, std::set< std::string > >   GLShaderManager::_program_shader;


void GLShaderManager::_appendLog(const std::string &log) {

  _log.append( log );
  _log.append( "\n" );
}

void GLShaderManager::_clearLog() {

  _log.clear();
}

bool GLShaderManager::_initPrograms() {

  createProgram( "default" );
  addShaderToProgram( "default", "default_vs" );
  addShaderToProgram( "default", "default_fs" );
  if( !linkProgram( "default" ) )
    return false;

  createProgram( "color" );
  addShaderToProgram( "color", "color_vs" );
  addShaderToProgram( "color", "color_fs" );
  if( !linkProgram( "color" ) )
    return false;

  createProgram( "select" );
  addShaderToProgram( "select", "select_vs" );
  addShaderToProgram( "select", "select_fs" );
  if( !linkProgram( "select" ) )
    return false;

  createProgram( "pcurve" );
  addShaderToProgram( "pcurve", "pcurve_vs" );
  addShaderToProgram( "pcurve", "pcurve_fs" );
  if( !linkProgram( "pcurve" ) )
    return false;

  createProgram( "pcurve_contours" );
  addShaderToProgram( "pcurve_contours", "pcurve_contours_vs" );
  addShaderToProgram( "pcurve_contours", "pcurve_contours_fs" );
  if( !linkProgram( "pcurve_contours" ) )
    return false;

  createProgram( "psurf_contours" );
  addShaderToProgram( "psurf_contours", "psurf_contours_vs" );
  addShaderToProgram( "psurf_contours", "psurf_contours_fs" );
  if( !linkProgram( "psurf_contours" ) )
    return false;

  createProgram( "render" );
  addShaderToProgram( "render", "render_vs" );
  addShaderToProgram( "render", "render_fs" );
  if( !linkProgram( "render" ) )
    return false;

//    createProgram( "default_pass2" );
//    addShaderToProgram( "default_pass2", "default_pass2_vs" );
//    addShaderToProgram( "default_pass2", "default_pass2_fs" );
//    if( !linkProgram( "default_pass2" ) )
//      return false;

  return true;
}

bool GLShaderManager::_initShaders() {

  ///////////////////////////
  // Default rendering shader

  // Vertex shader
  createShader( "default_vs",  GL_VERTEX_SHADER );
  setShaderSource(
      "default_vs",

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

  if( !compileShader( "default_vs" ) )
    return false;


  // Fragment shader
  createShader( "default_fs", GL_FRAGMENT_SHADER );
  setShaderSource(
      "default_fs",

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
      "out vec4 gl_FragData[2];\n"
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
      "  gl_FragData[0] = color;\n"
      "\n"
      "  vec4 sel_color = vec4( 0.0, 0.0, 0.0, 1.0 );\n"
      "\n"
      "  if( u_selected )\n"
      "    sel_color = vec4( 1.0, 1.0, 1.0, 1.0 );\n"
      "  gl_FragData[1] = sel_color;\n"
      "}\n"
      );
  if( !compileShader( "default_fs" ) )
    return false;



  //////////////////////
  // Single color shader

  // Vertex shader
  createShader( "color_vs",  GL_VERTEX_SHADER );
  setShaderSource(
      "color_vs",

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

  if( !compileShader( "color_vs" ) )
    return false;


  // Fragment shader
  createShader( "color_fs", GL_FRAGMENT_SHADER );
  setShaderSource(
      "color_fs",

      "#version 150 core\n"
      "\n"
      "uniform vec4 u_color;\n"
      "uniform bool u_selected;\n"
      "\n"
      "out vec4 gl_FragData[2];\n"
      "\n"
      "void main() {\n"
      "\n"
      "  gl_FragData[0] = u_color;\n"
      "  gl_FragData[1] = vec4( 0.0, 0.0, 0.0, 1.0 );\n"
      "  if( u_selected )\n"
      "    gl_FragData[1] = vec4( 1.0, 1.0, 1.0, 1.0 );\n"
      "}\n"
      );
  if( !compileShader( "color_fs" ) )
    return false;



  /////////////////////////
  // Default PCurve Shaders

  // Vertex shader
  createShader( "pcurve_vs",  GL_VERTEX_SHADER );
  setShaderSource(
      "pcurve_vs",

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

  if( !compileShader( "pcurve_vs" ) )
    return false;


  // Fragment shader
  createShader( "pcurve_fs", GL_FRAGMENT_SHADER );
  setShaderSource(
      "pcurve_fs",

      "#version 150 core\n"
      "\n"
      "uniform vec4 u_color;\n"
      "uniform bool u_selected;\n"
      "\n"
      "out vec4 gl_FragData[2];\n"
      "\n"
      "void main() {\n"
      "\n"
      "  gl_FragData[0] = u_color;\n"
      "  gl_FragData[1] = vec4( 0.0, 0.0, 0.0, 1.0 );\n"
      "  if( u_selected )\n"
      "    gl_FragData[1] = vec4( 1.0, 1.0, 1.0, 1.0 );\n"
      "}\n"
      );
  if( !compileShader( "pcurve_fs" ) )
    return false;



  ///////////////////////////
  // Default select shader

  // Vertex shader
  createShader( "select_vs", GL_VERTEX_SHADER );
  setShaderSource(
      "select_vs",

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

  if( !compileShader( "select_vs" ) )
    return false;

  // Fragment shader
  createShader( "select_fs", GL_FRAGMENT_SHADER );
  setShaderSource(
      "select_fs",

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

  if( !compileShader( "select_fs" ) )
    return false;



  ////////////////////////
  // PCurve Contours Shader

  // Vertex shader
  createShader( "pcurve_contours_vs", GL_VERTEX_SHADER );
  setShaderSource(
      "pcurve_contours_vs",

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

  if( !compileShader( "pcurve_contours_vs" ) )
    return false;


  // Fragment shader
  createShader( "pcurve_contours_fs", GL_FRAGMENT_SHADER );
  setShaderSource(
      "pcurve_contours_fs",

      "#version 150 core\n"
      "\n"
      "uniform bool u_selected;\n"
      "\n"
      "in vec4 ex_color;\n"
      "\n"
      "out vec4 gl_FragData[2];\n"
      "\n"
      "void main() {\n"
      "\n"
      "  gl_FragData[0] = ex_color;\n"
      "\n"
      "  gl_FragData[1] = vec4( 0.0, 0.0, 0.0, 1.0 );\n"
      "  if( u_selected )\n"
      "    gl_FragData[1] = vec4( 1.0, 1.0, 1.0, 1.0 );\n"
      "}\n"
      );

  if( !compileShader( "pcurve_contours_fs" ) )
    return false;



  ////////////////////////
  // PSurf Contours Shader

  // Vertex shader
  createShader( "psurf_contours_vs", GL_VERTEX_SHADER );
  setShaderSource(
      "psurf_contours_vs",

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

  if( !compileShader( "psurf_contours_vs" ) )
    return false;


  // Fragment shader
  createShader( "psurf_contours_fs", GL_FRAGMENT_SHADER );
  setShaderSource(
      "psurf_contours_fs",

      "#version 150 core\n"
      "\n"
      "uniform bool u_selected;\n"
      "\n"
      "in vec4 ex_color;\n"
      "\n"
      "out vec4 gl_FragData[2];\n"
      "\n"
      "void main() {\n"
      "\n"
      "  gl_FragData[0] = ex_color;\n"
      "\n"
      "  gl_FragData[1] = vec4( 0.0, 0.0, 0.0, 1.0 );\n"
      "  if( u_selected )\n"
      "    gl_FragData[1] = vec4( 1.0, 1.0, 1.0, 1.0 );\n"
      "}\n"
      );

  if( !compileShader( "psurf_contours_fs" ) )
    return false;



  ////////////////
  // Render shader

  // Vertex shader
  createShader( "render_vs", GL_VERTEX_SHADER );
  setShaderSource(
      "render_vs",

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

  if( !compileShader( "render_vs" ) )
    return false;


  // Fragment shader
  createShader( "render_fs", GL_FRAGMENT_SHADER );
  setShaderSource(
      "render_fs",

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

  if( !compileShader( "render_fs" ) )
    return false;



//    ///////////////////////
//    // *pass shader: pass 2

//    // Vertex shader
//    createShader( "default_pass2_vs", GL_VERTEX_SHADER );
//    setShaderSource(
//        "default_pass2_vs",

//        "#version 150 core\n"
//        "\n"
//        "uniform mat4 u_mvpmat;\n"
//        "\n"
//        "in vec4 in_vertex;\n"
//        "in vec2 in_tex_coord;\n"
//        "\n"
//        "out vec2 ex_tex_coord;\n"
//        "out vec4 gl_Position;\n"
//        "\n"
//        "void main() {\n"
//        "\n"
//        "  ex_tex_coord = in_tex_coord;\n"
//        "  gl_Position = u_mvpmat * in_vertex;\n"
//        "}\n"
//        );

//    if( !compileShader( "default_pass2_vs" ) )
//      return false;


//    // Fragment shader
//    createShader( "default_pass2_fs", GL_FRAGMENT_SHADER );
//    setShaderSource(
//        "default_pass2_fs",

//        "#version 150 core\n"
//        "\n"
//        "uniform sampler2D u_tex;\n"
//        "uniform sampler2D u_tex_selected;\n"
//        "uniform float u_buf_w;\n"
//        "uniform float u_buf_h;\n"
//        "uniform vec4 u_select_color;\n"
//        "\n"
//        "in vec2 ex_tex_coord;\n"
//        "\n"
//        "float avg( vec4 v ) {\n"
//        "\n"
//        "  return ( v.r + v.g + v. b ) / 4.0;\n"
//        "}\n"
//        "\n"
//        "\n"
//        "float runFilter( mat3 mask, float w, float h ) {\n"
//        "\n"
//        "  float result = 0; //vec4( 0.0, 0.0, 0.0, 0.0 );\n"
//        "\n"
//        "  for( float i = -1.0; i <= 1.0; i = i + 1.0 ) {\n"
//        "    for( float j = -1.0; j <= 1.0; j = j + 1.0 ) {\n"
//        "\n"
//        "      float x = ex_tex_coord.x + ( (i + 0.5) / w );\n"
//        "      float y = ex_tex_coord.y + ( (j + 0.5) / h );\n"
//        "\n"
//        "      float sub_res = avg( texture2D( u_tex_selected, vec2( x, y ) ) );\n"
//        "\n"
//        "      result += sub_res * avg(\n"
//        "        vec4(\n"
//        "          mask[int(i+1.0)][int(j+1.0)],\n"
//        "          mask[int(i+1.0)][int(j+1.0)],\n"
//        "          mask[int(i+1.0)][int(j+1.0)],\n"
//        "          mask[int(i+1.0)][int(j+1.0)]\n"
//        "        )\n"
//        "        );\n"
//        "    }\n"
//        "  }\n"
//        "\n"
//        "  return result;\n"
//        "}\n"
//        "\n"
//        "void main() {\n"
//        "\n"
//        "  // x and y sobel filters\n"
//        "  mat3 mask_x = mat3(\n"
//        "    -1.0, 0.0, 1.0,\n"
//        "    -2.0, 0.0, 2.0,\n"
//        "    -1.0, 0.0, 1.0\n"
//        "    );\n"
//        "\n"
//        "  mat3 mask_y =  mat3(\n"
//        "     1.0,  2.0,  1.0,\n"
//        "     0.0,  0.0,  0.0,\n"
//        "    -1.0, -2.0, -1.0\n"
//        "    );\n"
//        "\n"
//        "  // summation vars.\n"
//        "  float res_x = runFilter( mask_x, u_buf_w, u_buf_h );\n"
//        "  float res_y = runFilter( mask_y, u_buf_w, u_buf_h );\n"
//        "  float res = sqrt( res_x * res_x + res_y * res_y );\n"
//        "\n"
//        "  gl_FragColor = texture( u_tex, ex_tex_coord );\n"
//        "\n"
//        "  if( res > 0.0 )\n"
//        "   gl_FragColor = u_select_color;\n"
//        "}\n"
//        );

//    if( !compileShader( "default_pass2_fs" ) )
//      return false;


  return true;
}

bool GLShaderManager::_nameEmpty(const std::string &name, const std::string &type) {

  if( name.empty() ) {

    std::string log;
    log.append( type );
    log.append( " name empty." );
    _appendLog( log );

    return true;
  }

  return false;
}

bool GLShaderManager::_programExists( const std::string& name, bool exist ) {

  bool prog_ex = _programs.find(name) != _programs.end();

  if( prog_ex != exist ) {

    std::string log;
    log.append( "Program " );
    log.append( name );

    if( exist == false )
      log.append( " exists." );
    else if( exist == true )
      log.append( " does not exist." );

    _appendLog( log );
  }

  return prog_ex;
}

bool GLShaderManager::_shaderExists( const std::string& name, bool exist ) {

  bool shader_ex = _shaders.find(name) != _shaders.end();

  if( shader_ex != exist ) {

    std::string log;
    log.append( "Shader " );
    log.append( name );

    if( exist == false )
      log.append( " exists." );
    else if( exist == true )
      log.append( " does not exist." );

    _appendLog( log );
  }

  return shader_ex;
}

void GLShaderManager::_updateInfoLog( bool program, GLuint id ) {

  int len = 0;
  int written = 0;
  char *log;

  _info_log.clear();
  if( program )
    glGetProgramiv( id, GL_INFO_LOG_LENGTH, &len );
  else
    glGetShaderiv( id, GL_INFO_LOG_LENGTH, &len );

  if( len > 0 ) {

    len = len+1;
    log = new char[len];
    if( program )
      glGetProgramInfoLog( id, len, &written, log );
    else
      glGetShaderInfoLog( id, len, &written, log );

    _info_log.append( log, len );
    delete log;
  }
}

bool GLShaderManager::addShaderToProgram(const std::string &prog_name, const std::string &shader_name) {

  _clearLog();

  if( _nameEmpty(prog_name, "Program") || _nameEmpty(shader_name, "Shader") )
    return false;

  if( !_programExists(prog_name, true) || !_shaderExists(shader_name, true) )
    return false;

  if( _program_shader[prog_name].find( shader_name ) != _program_shader[prog_name].end() ) {

    _appendLog( "Shader already added to program." );
    return false;
  }

  _program_shader[prog_name].insert( shader_name );
  glAttachShader( _programs[prog_name].id, _shaders[shader_name].id );
  return true;
}

void GLShaderManager::cleanUp() {

  // Detach shaders from programs
  std::map< std::string, std::set< std::string > >::iterator itr;
  for( itr = _program_shader.begin(); itr != _program_shader.end(); itr++ ) {

    std::set< std::string >::iterator itr2;
    for( itr2 = (*itr).second.begin(); itr2 != (*itr).second.end(); itr2++ )
      glDetachShader( _programs[(*itr).first].id, _shaders[(*itr2)].id );
  }

  // Delete shaders
  std::map< std::string, ShaderInfo>::iterator itr3;
  for( itr3 = _shaders.begin(); itr3 != _shaders.end(); itr3++ )
    glDeleteShader( (*itr3).second.id );

  // Delete programs
  std::map< std::string, ProgramInfo>::iterator itr4;
  for( itr4 = _programs.begin(); itr4 != _programs.end(); itr4++ )
    glDeleteProgram( (*itr4).second.id );
}

bool GLShaderManager::compileShader( const std::string &name ) {

  _clearLog();

  if( _nameEmpty(name, "Shader") )
    return false;

  if( !_shaderExists( name, true ) )
    return false;

  glCompileShader( _shaders[name].id );

  int param;
  glGetShaderiv( _shaders[name].id, GL_COMPILE_STATUS, &param );

  _updateInfoLog( false, _shaders[name].id );

  return param == GL_TRUE;
}

bool GLShaderManager::createProgram( const std::string &name ) {

  _clearLog();

  if( _nameEmpty(name, "Program") )
    return false;

  if( _programExists(name, false) )
    return false;

  ProgramInfo prog;
  prog.id = glCreateProgram();

  _programs[name] = prog;

  return true;
}

bool GLShaderManager::createShader( const std::string &name, GLenum type ) {

  _clearLog();

  if( _nameEmpty(name, "Shader") )
    return false;

  if( _shaderExists( name, false ) )
    return false;

  if( ( type & ( GL_VERTEX_SHADER | GL_FRAGMENT_SHADER ) ) != type ) {

    _appendLog( "Shader type must be VERTEX or FRAGMENT." );
    return false;
  }

  ShaderInfo shader;
  shader.id = glCreateShader( type );
  shader.type = type;

  _shaders[name] = shader;

  return true;
}

bool GLShaderManager::deleteProgram( const std::string &name ) {

  _clearLog();

  if( _nameEmpty(name, "Program") )
    return false;

  if( !_programExists( name, true ) )
    return false;

  std::set< std::string > shaders = _program_shader[name];
  std::set< std::string >::iterator itr;
  for( itr = shaders.begin(); itr != shaders.end(); itr++ )
    glDetachShader( _programs[name].id, _shaders[(*itr)].id );

  glDeleteProgram( _programs[name].id );

  _program_shader.erase( name );
  _programs.erase( name );

  return true;
}

bool GLShaderManager::deleteShader( const std::string &name ) {

  _clearLog();

  if( _nameEmpty(name, "Shader") )
    return false;

  if( !_shaderExists(name, true ) )
    return false;

  std::map< std::string, std::set< std::string > >::iterator itr;
  for( itr = _program_shader.begin(); itr != _program_shader.end(); itr++ ) {

    if( (*itr).second.find( name ) != (*itr).second.end() ) {

      glDetachShader( _programs[(*itr).first].id, _shaders[name].id );
      (*itr).second.erase( name );
    }
  }

  glDeleteShader( _shaders[name].id );

  _shaders.erase( name );

  return true;
}

const std::string& GLShaderManager::getLog() {

  return _log;
}

const std::string& GLShaderManager::getInfoLog() {

  return _info_log;
}

GLuint GLShaderManager::getProgramID( const std::string &name ) {

  _clearLog();

  if( _nameEmpty(name, "Program") )
    return -1;

  if( !_programExists(name, true ) )
    return -1;

  return _programs[name].id;
}

const std::map< std::string, GLShaderManager::ProgramInfo > GLShaderManager::getPrograms() {

  return _programs;
}

std::set< std::string > GLShaderManager::getProgramShaders(const std::string &name) {

  _clearLog();

  if( _nameEmpty(name, "Program") )
    return std::set< std::string >();

  if( _program_shader.find( name ) == _program_shader.end() ) {

    std::string log;
    log.append( "Program " );
    log.append( name );
    log.append( " has no shaders." );
    _appendLog( log );
    return std::set< std::string >();
  }

  std::set< std::string > shaders = _program_shader[name];
  if( shaders.empty() ) {

    std::string log;
    log.append( "Program " );
    log.append( name );
    log.append( " has no shaders." );
    _appendLog( log );
    return std::set< std::string >();
  }

  return _program_shader[name];
}

GLuint GLShaderManager::getShaderID( const std::string &name ) {

  _clearLog();

  if( _nameEmpty(name, "Shader") )
    return -1;

  if( !_shaderExists(name, true) )
    return -1;

  return _shaders[name].id;
}

std::set< std::string > GLShaderManager::getShaderPrograms(const std::string &name) {

  std::set< std::string > programs;

  std::map< std::string, std::set< std::string > >::iterator itr;
  for( itr = _program_shader.begin(); itr != _program_shader.end(); itr++ ) {

    std::set< std::string >::iterator itr2;
    for( itr2 = (*itr).second.begin(); itr2 != (*itr).second.end(); itr2++ )
      if( name == *itr2 )
        programs.insert( (*itr).first );
  }

  return programs;
}

const std::map< std::string, GLShaderManager::ShaderInfo > GLShaderManager::getShaders() {

  return _shaders;
}

std::string GLShaderManager::getShaderSource(const std::string &name) {

  _clearLog();

  if( _nameEmpty(name, "Shader") )
    return std::string();

  if( !_shaderExists(name, true ) )
    return std::string();

  int param;
  glGetShaderiv( _shaders[name].id, GL_SHADER_SOURCE_LENGTH, &param );

  param++;
  int read;
  char buff[param];
  glGetShaderSource( _shaders[name].id, param, &read, buff );

  return std::string( buff );
}

GLenum GLShaderManager::getShaderType(const std::string &name) {

  _clearLog();

  if( _nameEmpty(name, "Shader") )
    return GL_NONE;

  if( !_shaderExists(name, true) )
    return GL_NONE;

  return _shaders[name].type;
}

const std::map< std::string, std::set< std::string > >& GLShaderManager::getTree() {

  return _program_shader;
}

void GLShaderManager::init() {

  if( _initialized )
    return;

  std::cout << "###### Initializing GLSL Program and shaders!!" << std::endl;

  // Initialize default shaders
  if( !_initShaders() )
    return;

  // Build default programs
  if( !_initPrograms() )
    return;


  _initialized = true;

  std::cout << "###### Done!! Initializing GLSL Programs and shaders!!" << std::endl;
}


bool GLShaderManager::isInitialized() {

  return _initialized;
}

bool GLShaderManager::isProgramLinked(const std::string &name) {

  _clearLog();

  if( _nameEmpty(name, "Program") )
    return false;

  if( !_programExists(name, true) )
    return false;

  int linked;
  glGetProgramiv( _programs[name].id, GL_LINK_STATUS, &linked );

  return linked == GL_TRUE;
}

bool GLShaderManager::isShaderCompiled(const std::string &name) {

  _clearLog();

  if( _nameEmpty(name, "Shader") )
    return false;

  if( !_shaderExists(name, true) )
    return false;

  int compiled;
  glGetShaderiv( _shaders[name].id, GL_COMPILE_STATUS, &compiled );

  return compiled == GL_TRUE;
}

bool GLShaderManager::linkProgram(const std::string &name) {

  _clearLog();

  if( _nameEmpty(name, "Program") )
    return false;

  if( !_programExists(name, true) )
    return false;

  // Link program
  glLinkProgram( _programs[name].id );

  // get link status
  int param;
  glGetProgramiv( _programs[name].id, GL_LINK_STATUS, &param );

  _updateInfoLog( true, _programs[name].id );

  return param == GL_TRUE;
}

bool GLShaderManager::removeShaderFromProgram(const std::string &prog_name, const std::string &shader_name) {

  _clearLog();

  if( _nameEmpty(prog_name, "Program") || _nameEmpty(shader_name, "Shader") )
    return false;

  if( !_programExists(prog_name, true) || !_shaderExists(shader_name, true) )
    return false;

  if( _program_shader[prog_name].find( shader_name ) == _program_shader[prog_name].end() ) {

    std::string log;
    log.append( "Program " );
    log.append( prog_name );
    log.append( " has no shader " );
    log.append( shader_name );
    log.append( "." );
    _appendLog( log );
    return false;
  }

  _program_shader[prog_name].erase( shader_name );
  glDetachShader( _programs[prog_name].id, _shaders[shader_name].id );
  return true;
}

bool GLShaderManager::setShaderSource( const std::string& name, const std::string &source ) {

  _clearLog();

  if( _nameEmpty(name, "Shader") || source.empty() ) {

    if( source.empty() )
      _appendLog( "Source code empty." );
    return false;
  }

  const char* src = source.c_str();
  glShaderSource( _shaders[name].id, 1, &src, 0x0 );

  return true;
}

