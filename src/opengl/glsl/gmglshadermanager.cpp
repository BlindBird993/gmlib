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

#include "../gmopengl.h"

// gmlib
#include <core/containers/gmdvector.h>


// stl
#include <iostream>


namespace GMlib{

namespace GL {

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

  bool GLShaderManager::_initDefaultPrograms() {

    createProgram( "default" );
    addShaderToProgram( "default", "default_vs" );
    addShaderToProgram( "default", "default_fs" );
    if( !linkProgram( "default" ) )
      return false;

    createProgram( "phong" );
    addShaderToProgram( "phong", "phong_vs" );
    addShaderToProgram( "phong", "phong_fs" );
    if( !linkProgram( "phong" ) )
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

    createProgram( "pcurve_contours" );
    addShaderToProgram( "pcurve_contours", "pcurve_contours_vs" );
    addShaderToProgram( "pcurve_contours", "pcurve_contours_fs" );
    if( !linkProgram( "pcurve_contours" ) )
      return false;

    createProgram( "psurf_phong_nmap" );
    addShaderToProgram( "psurf_phong_nmap", "psurf_phong_nmap_vs" );
    addShaderToProgram( "psurf_phong_nmap", "psurf_phong_nmap_fs" );
    if( !linkProgram( "psurf_phong_nmap" ) )
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

    createProgram( "render_select" );
    addShaderToProgram( "render_select", "render_select_vs" );
    addShaderToProgram( "render_select", "render_select_fs" );
    if( !linkProgram( "render_select" ) )
      return false;

    return true;
  }

  bool GLShaderManager::_initDefaultShaders() {


    std::string header_150(

      "#version 150 core\n"
      "\n"
      "layout(std140) uniform;\n"
      "\n"
    );

    std::string struct_material(

      "struct Material {\n"
      "  vec4  ambient;\n"
      "  vec4  diffuse;\n"
      "  vec4  specular;\n"
      "  float shininess;\n"
      "};\n"
      "\n"
    );

    std::string struct_light(

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
    );

   std::string uniform_lights;
   uniform_lights.append( struct_light );
   uniform_lights.append(
      "uniform Lights {\n"
      "  uvec4 info;\n"
      "  Light light[200];\n"
      "} u_lights;\n"
      "\n"
    );

    std::string func_sunlight(
      "vec4\n"
      "sunLight( Light light, Material mat, vec3 normal, vec3 cam_pos ) {\n"
      "\n"
      "  float sun_att, sun_fact;\n"
      "  sun_fact = dot( normal, normalize( light.direction ).xyz );\n"
      "  sun_fact = clamp( sun_fact, 0.0, 1.0 );\n"
      "\n"
      "  return light.ambient * sun_fact;\n"
      "}\n"
      "\n"
    );

    std::string func_pointlight(
      "vec4\n"
      "pointLight( Light light, Material mat, vec3 normal, vec3 cam_pos ) {\n"
      "\n"
      "  vec3  L = vec3(light.position) - cam_pos;\n"
      "  float dL = length( L );\n"
      "  L = normalize( L );\n"
      "  vec3  E = normalize( -cam_pos );\n"
      "  vec3  R = normalize( -reflect(L,normal) );\n"
      "\n"
      "  float attenuation =  1.0 / ( light.att[0] +\n"
      "                               light.att[1] * dL +\n"
      "                               light.att[2] * dL * dL );\n"
      "  // calculate ambient term\n"
      "  vec4 amb =  light.ambient * mat.ambient;\n"
      "\n"
      "  // calculate diffuse term\n"
      "  vec4 diff = light.diffuse * mat.diffuse * max( dot(normal,L), 0.0);\n"
      "  diff = clamp( diff, 0.0, 1.0 );\n"
      "\n"
      "  // calculate specular term\n"
      "  vec4 spec = light.specular * mat.specular *\n"
      "               pow( max( dot(R,E), 0.0), 0.3 * mat.shininess );\n"
      "  spec = clamp( spec, 0.0, 1.0 );\n"
      "\n"
      "  // return color\n"
      "  return (amb + diff + spec) * attenuation;\n"
      "}\n"
      "\n"
    );

    std::string func_spotlight(
      "vec4\n"
      "spotLight( Light light, Material mat, vec3 normal, vec3 cam_pos ) {\n"
      "\n"
      "  vec3  L = vec3(light.position) - cam_pos;\n"
      "  float dL = length( L );\n"
      "  L = normalize( L );\n"
      "  vec3  E = normalize( -cam_pos );\n"
      "  vec3  R = normalize( -reflect(L,normal) );\n"
      "\n"
      "  // Attenuation\n"
      "  float attenuation =  1.0 / ( light.att[0] +\n"
      "                               light.att[1] * dL +\n"
      "                               light.att[2] * dL * dL );\n"
      "\n"
      "  // Spot attenuation\n"
      "  float spot_att = dot(-L, normalize(light.direction));\n"
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
      "  vec4 diff = light.diffuse * mat.diffuse * max( dot(normal,L), 0.0);\n"
      "  diff = clamp( diff, 0.0, 1.0 );\n"
      "\n"
      "  // calculate specular term\n"
      "  vec4 spec = light.specular * mat.specular *\n"
      "               pow( max( dot(R,E), 0.0), 0.3 * mat.shininess );\n"
      "  spec = clamp( spec, 0.0, 1.0 );\n"
      "\n"
      "  // return color\n"
      "  return (amb + diff + spec) * attenuation;\n"
      "}\n"
      "\n"
    );



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
    if( !compileShader( "default_fs" ) )
      return false;



    ///////////////
    // Phong shader
    std::string phong_vs_str;
    phong_vs_str.append( header_150 );
    phong_vs_str.append(
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

    createShader( "phong_vs", GL_VERTEX_SHADER );
    setShaderSource( "phong_vs", phong_vs_str );


    std::string phong_fs_str;
    phong_fs_str.append( header_150 );
    phong_fs_str.append( struct_material );
    phong_fs_str.append( uniform_lights );
    phong_fs_str.append( func_sunlight );
    phong_fs_str.append( func_pointlight );
    phong_fs_str.append( func_spotlight );
    phong_fs_str.append(
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
      "  // Compute sun contribution\n"
      "  for( uint i = uint(0); i < u_lights.info[1]; ++i )\n"
      "    light_color += sunLight( u_lights.light[i], mat, normal, ex_pos );\n"
      "\n"
      "  // Compute point light contribution\n"
      "  for( uint i = u_lights.info[1]; i < u_lights.info[1] + u_lights.info[2]; ++i )\n"
      "    light_color += pointLight( u_lights.light[i], mat, normal, ex_pos );\n"
      "\n"
      "  // Compute spot light contribution\n"
      "  for( uint i = u_lights.info[1] + u_lights.info[2]; i < u_lights.info[3]; ++i )\n"
      "    light_color += spotLight(  u_lights.light[i], mat, normal, ex_pos );\n"
      "\n"
      "  gl_FragColor = light_color;\n"
      "}\n"
    );

    createShader( "phong_fs", GL_FRAGMENT_SHADER );
    setShaderSource( "phong_fs", phong_fs_str );


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
        "out vec4 gl_FragColor;\n"
        "\n"
        "void main() {\n"
        "\n"
        "  gl_FragColor = u_color;\n"
        "}\n"
        );
    if( !compileShader( "color_fs" ) )
      return false;




    ///////////////////////////
    // Render select shader

    // Vertex shader
    createShader( "render_select_vs", GL_VERTEX_SHADER );
    setShaderSource(
        "render_select_vs",

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

    if( !compileShader( "render_select_vs" ) )
      return false;

    // Fragment shader
    createShader( "render_select_fs", GL_FRAGMENT_SHADER );
    setShaderSource(
        "render_select_fs",

        "#version 150 compatibility \n"
        "\n"
        "out vec4 gl_FragColor; \n"
        "\n"
        "void main() \n"
        "{ \n"
        "  gl_FragColor = vec4( 1.0, 1.0, 1.0, 1.0 ); \n"
        "} \n"
        );

    if( !compileShader( "render_select_fs" ) )
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
        "out vec4 gl_FragColor;\n"
        "\n"
        "void main() {\n"
        "\n"
        "  gl_FragColor = ex_color;\n"
        "}\n"
        );

    if( !compileShader( "pcurve_contours_fs" ) )
      return false;


    /////////////////////////////
    // PSurf phong shader: NMap

    // Vertex shader
    std::string psurf_phong_nmap_vs_str;
    psurf_phong_nmap_vs_str.append( header_150 );
    psurf_phong_nmap_vs_str.append(
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

    createShader( "psurf_phong_nmap_vs", GL_VERTEX_SHADER );
    setShaderSource( "psurf_phong_nmap_vs", psurf_phong_nmap_vs_str );



    // Fragment shader
    std::string psurf_phong_nmap_fs_str;
    psurf_phong_nmap_fs_str.append( header_150 );
    psurf_phong_nmap_fs_str.append( struct_material );
    psurf_phong_nmap_fs_str.append( uniform_lights );
    psurf_phong_nmap_fs_str.append( func_sunlight );
    psurf_phong_nmap_fs_str.append( func_pointlight );
    psurf_phong_nmap_fs_str.append( func_spotlight );
    psurf_phong_nmap_fs_str.append(
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
      "  // Compute sun contribution\n"
      "  for( uint i = uint(0); i < u_lights.info[1]; ++i )\n"
      "    light_color += sunLight( u_lights.light[i], mat, normal, ex_pos );\n"
      "\n"
      "  // Compute point light contribution\n"
      "  for( uint i = u_lights.info[1]; i < u_lights.info[1] + u_lights.info[2]; ++i )\n"
      "    light_color += pointLight( u_lights.light[i], mat, normal, ex_pos );\n"
      "\n"
      "  // Compute spot light contribution\n"
      "  for( uint i = u_lights.info[1] + u_lights.info[2]; i < u_lights.info[3]; ++i )\n"
      "    light_color += spotLight(  u_lights.light[i], mat, normal, ex_pos );\n"
      "\n"
      "  gl_FragColor = light_color;\n"
      "\n"
      "}\n"
    );

    createShader( "psurf_phong_nmap_fs", GL_FRAGMENT_SHADER );
    setShaderSource( "psurf_phong_nmap_fs", psurf_phong_nmap_fs_str );





    ////////////////////////
    // PSurf Contours Shader

    // Vertex shader
    std::string psurf_contours_vs_str;
    psurf_contours_vs_str.append( header_150 );
    psurf_contours_vs_str.append(
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

    createShader( "psurf_contours_vs", GL_VERTEX_SHADER );
    setShaderSource( "psurf_contours_vs", psurf_contours_vs_str );







    // Fragment shader
    std::string psurf_contours_fs_str;
    psurf_contours_fs_str.append( header_150 );
    psurf_contours_fs_str.append( struct_material );
    psurf_contours_fs_str.append( uniform_lights );
    psurf_contours_fs_str.append( func_sunlight );
    psurf_contours_fs_str.append( func_pointlight );
    psurf_contours_fs_str.append( func_spotlight );
    psurf_contours_fs_str.append(
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
      "  // Compute sun contribution\n"
      "  for( uint i = uint(0); i < u_lights.info[1]; ++i )\n"
      "    light_color += sunLight( u_lights.light[i], mat, normal, ex_pos );\n"
      "\n"
      "  // Compute point light contribution\n"
      "  for( uint i = u_lights.info[1]; i < u_lights.info[1] + u_lights.info[2]; ++i )\n"
      "    light_color += pointLight( u_lights.light[i], mat, normal, ex_pos );\n"
      "\n"
      "  // Compute spot light contribution\n"
      "  for( uint i = u_lights.info[1] + u_lights.info[2]; i < u_lights.info[3]; ++i )\n"
      "    light_color += spotLight(  u_lights.light[i], mat, normal, ex_pos );\n"
      "\n"
      "  gl_FragColor = light_color;\n"
      "}\n"
    );

    createShader( "psurf_contours_fs", GL_FRAGMENT_SHADER );
    setShaderSource( "psurf_contours_fs", psurf_contours_fs_str );




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
      GL_CHECK(glGetProgramiv( id, GL_INFO_LOG_LENGTH, &len ));
    else
      GL_CHECK(glGetShaderiv( id, GL_INFO_LOG_LENGTH, &len ));

    if( len > 0 ) {

      len = len+1;
      log = new char[len];
      if( program )
        GL_CHECK(glGetProgramInfoLog( id, len, &written, log ));
      else
        GL_CHECK(glGetShaderInfoLog( id, len, &written, log ));

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
    GL_CHECK(glAttachShader( _programs[prog_name].id, _shaders[shader_name].id ));
    return true;
  }

  void GLShaderManager::cleanUp() {

    // Detach shaders from programs
    std::map< std::string, std::set< std::string > >::iterator itr;
    for( itr = _program_shader.begin(); itr != _program_shader.end(); itr++ ) {

      std::set< std::string >::iterator itr2;
      for( itr2 = (*itr).second.begin(); itr2 != (*itr).second.end(); itr2++ )
        GL_CHECK(glDetachShader( _programs[(*itr).first].id, _shaders[(*itr2)].id ));
    }

    // Delete shaders
    std::map< std::string, ShaderInfo>::iterator itr3;
    for( itr3 = _shaders.begin(); itr3 != _shaders.end(); itr3++ )
      GL_CHECK(glDeleteShader( (*itr3).second.id ));

    // Delete programs
    std::map< std::string, ProgramInfo>::iterator itr4;
    for( itr4 = _programs.begin(); itr4 != _programs.end(); itr4++ )
      GL_CHECK(glDeleteProgram( (*itr4).second.id ));
  }

  bool GLShaderManager::compileShader( const std::string &name ) {

    _clearLog();

    if( _nameEmpty(name, "Shader") )
      return false;

    if( !_shaderExists( name, true ) )
      return false;

    GL_CHECK(glCompileShader( _shaders[name].id ));

    int param;
    GL_CHECK(glGetShaderiv( _shaders[name].id, GL_COMPILE_STATUS, &param ));

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
    GL_CHECK(prog.id = glCreateProgram());

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
    GL_CHECK(shader.id = glCreateShader( type ));
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
      GL_CHECK(glDetachShader( _programs[name].id, _shaders[(*itr)].id ));

    GL_CHECK(glDeleteProgram( _programs[name].id ));

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

        GL_CHECK(glDetachShader( _programs[(*itr).first].id, _shaders[name].id ));
        (*itr).second.erase( name );
      }
    }

    GL_CHECK(glDeleteShader( _shaders[name].id ));

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
    GL_CHECK(glGetShaderiv( _shaders[name].id, GL_SHADER_SOURCE_LENGTH, &param ));

    param++;
    int read;
    DVector<char> buff(param);
    GL_CHECK(glGetShaderSource( _shaders[name].id, param, &read, buff.getPtr() ));

    return std::string( buff.getPtr() );
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
    if( !_initDefaultShaders() )
      return;

    // Build default programs
    if( !_initDefaultPrograms() )
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
    GL_CHECK(glGetProgramiv( _programs[name].id, GL_LINK_STATUS, &linked ));

    return linked == GL_TRUE;
  }

  bool GLShaderManager::isShaderCompiled(const std::string &name) {

    _clearLog();

    if( _nameEmpty(name, "Shader") )
      return false;

    if( !_shaderExists(name, true) )
      return false;

    int compiled;
    GL_CHECK(glGetShaderiv( _shaders[name].id, GL_COMPILE_STATUS, &compiled ));

    return compiled == GL_TRUE;
  }

  bool GLShaderManager::linkProgram(const std::string &name) {

    _clearLog();

    if( _nameEmpty(name, "Program") )
      return false;

    if( !_programExists(name, true) )
      return false;

    // Link program
    GL_CHECK(glLinkProgram( _programs[name].id ));

    // get link status
    int param;
    GL_CHECK(glGetProgramiv( _programs[name].id, GL_LINK_STATUS, &param ));

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
    GL_CHECK(glDetachShader( _programs[prog_name].id, _shaders[shader_name].id ));
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
    GL_CHECK(glShaderSource( _shaders[name].id, 1, &src, 0x0 ));

    return true;
  }
} // END namespace GL

} // END namespace GMlib
