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



/*! \file gmopengl.cpp
 *
 *  Pending Documentation
 */


#include "gmopengl.h"

#include "glsl/gmglshadermanager.h"

// stl
#include <cassert>
#include <limits>
#include <iostream>


namespace GMlib {

namespace GL {

  std::string OGL::_log;
  OGL::FBOMap   OGL::_fbos;
  OGL::RBOMap   OGL::_rbos;
  OGL::BOMap    OGL::_bos;
  OGL::TexMap   OGL::_texs;


  // Light stuff
  GLuint OGL::_light_ubo = 0;
  GLVector<4,GLuint> OGL::_lights_header;
  std::vector<GLLight> OGL::_lights;
  OGL::LightIdMap OGL::_light_id_map;



  void OGL::_appendLog(const std::string &log) {

    _log.append( log );
    _log.append( "\n" );
  }

  void OGL::_clearLog() {

    _log.clear();
  }

  bool OGL::_nameEmpty( const std::string& name, const std::string& type ) {

    if( name.empty() ) {

      std::string log;
      log.append( type );
      log.append( " name empty." );
      _appendLog( log );

      return true;
    }

    return false;
  }

  bool OGL::bindRbo(const std::string &name) {


    _clearLog();

    if( _nameEmpty( name, "RBO" ) )
      return false;

    if( !_rboExists(name, true) )
      return false;

    GL_CHECK(glBindRenderbuffer( GL_RENDERBUFFER, _rbos[name].id ));

    return true;
  }

  GLuint OGL::createRbo() {

    GLuint id;
    GL_CHECK(glGenRenderbuffers( 1, &id ));
    return id;
  }

  bool OGL::createRbo(const std::string &name) {

    _clearLog();

    if( _nameEmpty( name, "RBO" ) )
      return false;

    if( _rboExists(name, false) )
      return false;

    RBOInfo rbo;
    GL_CHECK(glGenRenderbuffers( 1, &rbo.id ));

    _rbos[name] = rbo;

    return true;
  }

  void OGL::deleteRbo(GLuint id) {

    GL_CHECK(glDeleteRenderbuffers( 1, &id ));
  }

  bool OGL::deleteRbo(const std::string &name) {

    _clearLog();

    if( _nameEmpty( name, "RBO" ) )
      return false;

    if( !_rboExists(name, true) )
      return false;

    // Detach "render" buffers

    GL_CHECK(glDeleteRenderbuffers( 1, &(_rbos[name].id) ));

    _rbos.erase( name );

    return true;
  }

  GLuint OGL::getRboId(const std::string &name) {

    _clearLog();

    if( _nameEmpty( name, "RBO" ) )
      return false;

    if( !_rboExists(name, true) )
      return false;

    GL_CHECK(glDeleteRenderbuffers( 1, &(_rbos[name].id) ));

    _rbos.erase( name );

    return true;
  }

  const OGL::RBOMap &OGL::getRbos() {

    return _rbos;
  }

  bool OGL::unbindRbo(const std::string &name) {

    _clearLog();

    if( _nameEmpty( name, "RBO" ) )
      return false;

    if( !_rboExists(name, true) )
      return false;

    GL_CHECK(glBindRenderbuffer( GL_RENDERBUFFER, 0x0 ));

    return true;
  }

  bool OGL::_rboExists(const std::string &name, bool exist) {

    bool rbo_ex = _rbos.find(name) != _rbos.end();

    if( rbo_ex != exist ) {

      std::string log;
      log.append( "RBO " );
      log.append( name );

      if( exist == false )
        log.append( " exists." );
      else if( exist == true )
        log.append( " does not exist." );

      _appendLog( log );
    }

    return rbo_ex;
  }

  bool OGL::_boExists(const std::string &name, bool exist) {

    bool bo_ex = _bos.find(name) != _bos.end();

    if( bo_ex != exist ) {

      std::string log;
      log.append( "BO " );
      log.append( name );

      if( exist == false )
        log.append( " exists." );
      else if( exist == true )
        log.append( " does not exist." );

      _appendLog( log );
    }

    return bo_ex;
  }

  bool OGL::bindTex(const std::string &name) {

    _clearLog();

    if( _nameEmpty( name, "RBO" ) )
      return false;

    if( !_rboExists(name, true) )
      return false;

    GL_CHECK(glBindRenderbuffer( GL_RENDERBUFFER, _rbos[name].id ));

    return true;
  }

  GLuint OGL::createTex() {

    GLuint id;
    GL_CHECK(glGenTextures( 1, &id ));
    return id;
  }

  bool OGL::createTex(const std::string &name, GLenum target) {

    _clearLog();

    if( _nameEmpty( name, "TEX" ) )
      return false;

    if( _texExists(name, false) )
      return false;

    TexInfo tex;
    GL_CHECK(glGenTextures( 1, &tex.id ));
    tex.target = target;

    _texs[name] = tex;

    return true;
  }

  void OGL::deleteTex(GLuint id) {

    GL_CHECK(glDeleteTextures( 1, &id ));
  }

  bool OGL::deleteTex(const std::string &name) {

    _clearLog();

    if( _nameEmpty( name, "TEX" ) )
      return false;

    if( !_texExists(name, true) )
      return false;

    GL_CHECK(glDeleteTextures( 1, &(_texs[name].id) ));

    _texs.erase( name );

    return true;
  }

  GLuint OGL::getTexId(const std::string &name) {

    _clearLog();

    if( _nameEmpty(name, "TEX") )
      return -1;

    if( !_texExists(name, true) )
      return -1;

    return _texs[name].id;
  }

  GLenum OGL::getTexTarget(const std::string &name) {

    _clearLog();

    if( _nameEmpty(name, "TEX") )
      return GL_NONE;

    if( !_texExists(name, true) )
      return GL_NONE;

    return _texs[name].target;
  }

  const OGL::TexMap &OGL::getTexs() {

    return _texs;
  }

  bool OGL::setTexTarget(const std::string &name, GLenum target) {

    _clearLog();

    if( _nameEmpty( name, "TEX" ) )
      return false;

    if( !_texExists(name, true) )
      return false;

    _texs[name].target = target;

    return true;
  }

  bool OGL::unbindTex(const std::string &name) {

    _clearLog();

    if( _nameEmpty( name, "TEX" ) )
      return false;

    if( !_texExists(name, true) )
      return false;

    GL_CHECK(glBindTexture( _texs[name].target, 0x0 ));

    return true;
  }

  bool OGL::_texExists(const std::string &name, bool exist) {

    bool tex_ex = _texs.find(name) != _texs.end();

    if( tex_ex != exist ) {

      std::string log;
      log.append( "TEX" );
      log.append( name );

      if( exist == false )
        log.append( " exists." );
      else if( exist == true )
        log.append( " does not exist." );

      _appendLog( log );
    }

    return tex_ex;
  }

  bool OGL::_fboExists(const std::string &name, bool exist) {

    bool fbo_ex = _fbos.find(name) != _fbos.end();

    if( fbo_ex != exist ) {

      std::string log;
      log.append( "FBO " );
      log.append( name );

      if( exist == false )
        log.append( " exists." );
      else if( exist == true )
        log.append( " does not exist." );

      _appendLog( log );
    }

    return fbo_ex;
  }

  bool OGL::bindFbo(const std::string &name) {

    _clearLog();

    if( _nameEmpty( name, "FBO" ) )
      return false;

    if( !_fboExists(name, true) )
      return false;

    GL_CHECK(glBindFramebuffer( GL_FRAMEBUFFER, _fbos[name].id ));

    return true;
  }

  bool OGL::bindBo(const std::string &name) {

    _clearLog();

    if( _nameEmpty( name, "VBO" ) )
      return false;

    if( !_boExists(name, true) )
      return false;

    GL_CHECK(glBindBuffer( _bos[name].target, _bos[name].id ));

    return true;
  }

  void OGL::cleanUp() {

    deleteLightBuffer();
    deleteStandardRepBOs();
    GLShaderManager::cleanUp();
  }

  GLuint OGL::createFbo() {

    GLuint id;
    GL_CHECK(glGenFramebuffers( 1, &id ));
    return id;
  }

  bool OGL::createFbo(const std::string &name) {

    _clearLog();

    if( _nameEmpty( name, "FBO" ) )
      return false;

    if( _fboExists(name, false) )
      return false;

    FBOInfo fbo;
    GL_CHECK(glGenFramebuffers( 1, &fbo.id ));

    _fbos[name] = fbo;

    return true;
  }

  GLuint OGL::createBo() {

    GLuint id;
    GL_CHECK(glGenBuffers( 1, &id ));
    return id;
  }

  bool OGL::createBo(const std::string &name, GLenum target ) {

    _clearLog();

    if( _nameEmpty( name, "BO" ) )
      return false;

    if( _boExists(name, false) )
      return false;

    BOInfo bo;
    GL_CHECK(glGenBuffers( 1, &bo.id ));
    bo.target = target;

    _bos[name] = bo;

    return true;
  }

  void OGL::deleteFbo(GLuint id) {

    GL_CHECK(glDeleteFramebuffers( 1, &id ));
  }

  bool OGL::deleteFbo(const std::string &name) {

    _clearLog();

    if( _nameEmpty( name, "FBO" ) )
      return false;

    if( !_fboExists(name, true) )
      return false;

    // Detach "render" buffers

    GL_CHECK(glDeleteFramebuffers( 1, &(_fbos[name].id) ));

    _fbos.erase( name );

    return true;
  }

  void OGL::deleteBo(GLuint id) {

    GL_CHECK(glDeleteBuffers( 1, &id ));
  }

  bool OGL::deleteBo(const std::string &name) {

    _clearLog();

    if( _nameEmpty( name, "BO" ) )
      return false;

    if( !_boExists(name, true) )
      return false;

    GL_CHECK(glDeleteBuffers( 1, &(_bos[name].id) ));

    _bos.erase( name );

    return true;
  }

  GLuint OGL::getFboId(const std::string &name) {

    _clearLog();

    if( _nameEmpty(name, "FBO") )
      return false;

    if( !_fboExists(name, true) )
      return false;

    return _fbos[name].id;
  }

  const OGL::FBOMap &OGL::getFbos() {

    return _fbos;
  }

  const std::string& OGL::getLog() {

    return _log;
  }

  GLuint OGL::getBoId(const std::string &name) {

    _clearLog();

    if( _nameEmpty(name, "BO") )
      return -1;

    if( !_boExists(name, true) )
      return -1;

    return _bos[name].id;
  }

  const OGL::BOMap &OGL::getBos() {

    return _bos;
  }

  GLenum OGL::getBoTarget(const std::string &name) {

    _clearLog();

    if( _nameEmpty(name, "BO") )
      return GL_NONE;

    if( !_boExists(name, true) )
      return GL_NONE;

    return _bos[name].target;
  }

  void OGL::init() {

    // Init GLEW
    GLenum err = glewInit();
    if( err == GLEW_OK )
      std::cout << "GLEW Init OK - using GLEW version " << glewGetString(GLEW_VERSION) << std::endl;
    else
      std::cout << "GLEW Init FAILED!!" << std::endl;
    std::cout << std::flush;


    GLShaderManager::init();
    createStandardRepBOs();
    createLightBuffer();
  }

  bool OGL::unbindFbo(const std::string &name) {

    _clearLog();

    if( _nameEmpty( name, "FBO" ) )
      return false;

    if( !_fboExists(name, true) )
      return false;

    GL_CHECK(glBindFramebuffer( GL_FRAMEBUFFER, 0x0 ));

    return true;
  }

  bool OGL::unbindBo(const std::string &name) {

    _clearLog();

    if( _nameEmpty( name, "BO" ) )
      return false;

    if( !_boExists(name, true) )
      return false;

    GL_CHECK(glBindBuffer( _bos[name].target, 0x0 ));

    return true;
  }

  bool OGL::setBoTarget(const std::string &name, GLenum target) {

    _clearLog();

    if( _nameEmpty( name, "BO" ) )
      return false;

    if( !_boExists(name, true) )
      return false;

    _bos[name].target = target;

    return true;
  }




























  void OGL::createSelectorRepBOs() {

  //    float ir = 0.07;

  //    createBo( )
  }

  void OGL::createStandardRepBOs() {

    float ir = 0.07;

    createBo( "std_rep_cube", GL_ARRAY_BUFFER );
    createBo( "std_rep_cube_indices", GL_ELEMENT_ARRAY_BUFFER );
    createBo( "std_rep_frame_indices", GL_ELEMENT_ARRAY_BUFFER );

    // Vertices
    GLfloat cube[] = {

    /* 0 */     -ir,    -ir,    -ir,      // Back/Left/Down
    /* 1 */      ir,    -ir,    -ir,
    /* 2 */      ir,     ir,    -ir,
    /* 3 */     -ir,     ir,    -ir,
    /* 4 */     -ir,    -ir,     ir,      // Front/Left/Down
    /* 5 */      ir,    -ir,     ir,
    /* 6 */      ir,     ir,     ir,
    /* 7 */     -ir,     ir,     ir
    };

    // Indice Coords
    GLushort cube_indices[] = {

      4,  5,  6,  7,    // Front
      1,  2,  6,  5,    // Right
      0,  1,  5,  4,    // Bottom
      0,  3,  2,  1,    // Back
      0,  4,  7,  3,    // Left
      2,  3,  7,  6     // Top
    };

    // Frame indice coords
    GLushort frame_indices [] = {

      0,  1,    // x-axis
      0,  3,    // y-axis
      0,  4,    // z-axis

      // Remaining frame
      2,  3,
      2,  1,
      2,  6,

      7,  6,
      7,  4,
      7,  3,

      5,  4,
      5,  6,
      5,  1

    };

    OGL::bindBo( "std_rep_cube" );
    GL_CHECK(glBufferData( GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), cube, GL_STATIC_DRAW ));
    OGL::unbindBo( "std_rep_cube" );

    OGL::bindBo( "std_rep_cube_indices" );
    GL_CHECK(glBufferData( GL_ELEMENT_ARRAY_BUFFER, 24 * sizeof(GLushort), cube_indices, GL_STATIC_DRAW ));
    OGL::unbindBo( "std_rep_cube_indices" );

    OGL::bindBo( "std_rep_frame_indices" );
    GL_CHECK(glBufferData( GL_ELEMENT_ARRAY_BUFFER, 24 * sizeof(GLushort), frame_indices, GL_STATIC_DRAW ));
    OGL::unbindBo( "std_rep_frame_indices" );
  }

  void OGL::deleteStandardRepBOs() {

    deleteBo( "std_rep_cube");
    deleteBo( "std_rep_cube_indices");
    deleteBo( "std_rep_frame_indices" );
  }

  void OGL::bindLightBuffer() {

    bindBo( "light_ubo" );
  }

  void OGL::createLightBuffer() {

    createBo( "light_ubo", GL_UNIFORM_BUFFER );
  }

  void OGL::deleteLightBuffer() {

    deleteBo( "light_ubo" );
  }

  GLuint OGL::getLightBuffer() {

    return getBoId( "light_ubo" );
  }

  void OGL::resetLightBuffer(const GLVector<4,GLuint>& header, const std::vector<unsigned int>& light_ids, const std::vector<GLLight>& lights) {

    std::cout << "------------------------------------------" << std::endl;
    std::cout << "Resetting light UBO to:" << std::endl;
    std::cout << "Header:" << std::endl;
    std::cout << " - Suns   end: " << header.p[0] << std::endl;
    std::cout << " - PLs    end: " << header.p[1] << std::endl;
    std::cout << " - SLs    end: " << header.p[2] << std::endl;
    std::cout << " - Lights end: " << header.p[2] << std::endl;
    std::cout << std::endl;

    std::cout << "Lights:" << std::endl;
    for( int i = 0; i < lights.size(); ++i ) {

      std::cout << "Light id: " << light_ids[i] << std::endl;
      std::cout << " - Ambient:       " << " (" << lights[i].amb.p[0]
                                        << ", " << lights[i].amb.p[1]
                                        << ", " << lights[i].amb.p[2]
                                        << ", " << lights[i].amb.p[3]
                                        << ")"  << std::endl;
      std::cout << " - Diffuse:       " << " (" << lights[i].dif.p[0]
                                        << ", " << lights[i].dif.p[1]
                                        << ", " << lights[i].dif.p[2]
                                        << ", " << lights[i].dif.p[3]
                                        << ")"  << std::endl;
      std::cout << " - Specular:      " << " (" << lights[i].spc.p[0]
                                        << ", " << lights[i].spc.p[1]
                                        << ", " << lights[i].spc.p[2]
                                        << ", " << lights[i].spc.p[3]
                                        << ")"  << std::endl;
      std::cout << " - Position:      " << " (" << lights[i].pos.p[0]
                                        << ", " << lights[i].pos.p[1]
                                        << ", " << lights[i].pos.p[2]
                                        << ", " << lights[i].pos.p[3]
                                        << ")"  << std::endl;
      std::cout << " - Direction:     " << " (" << lights[i].dir.p[0]
                                        << ", " << lights[i].dir.p[1]
                                        << ", " << lights[i].dir.p[2]
                                        << ")"  << std::endl;
      std::cout << " - Attenuation:   " << " (" << lights[i].att.p[0]
                                        << ", " << lights[i].att.p[1]
                                        << ", " << lights[i].att.p[2]
                                        << ")"  << std::endl;
      std::cout << " - Spot cut-off:  " << lights[i].spot_cut << std::endl;
      std::cout << " - Spot exponent: " << lights[i].spot_exp << std::endl;
      std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "------------------------------------------" << std::endl;


    _lights_header = header;
    _lights = lights;

    // fill inn light id map
    _light_id_map.clear();
    std::vector<unsigned int>::const_iterator id_itr;
    int light_id;
    for( light_id = 0, id_itr = light_ids.begin(); id_itr != light_ids.end(); ++id_itr, ++light_id )
      _light_id_map[*id_itr] = light_id;

    bindLightBuffer();

    // create/reset buffer size
    GL_CHECK(glBufferData( GL_UNIFORM_BUFFER,
                  sizeof(GLVector<4,GLuint>) + lights.size() * sizeof(GLLight),
                  0x0, GL_DYNAMIC_DRAW ));

    // upload header ( "number of info" )
    GL_CHECK(glBufferSubData(  GL_UNIFORM_BUFFER, 0, sizeof(GLVector<4,GLuint>), &header ));

    // upload light data
    GL_CHECK(glBufferSubData(  GL_UNIFORM_BUFFER,
                      sizeof(GLVector<4,GLuint>), sizeof(GLLight) * lights.size(), &lights[0] ));

    unbindLightBuffer();
  }

  void OGL::unbindLightBuffer() {

    unbindBo( "light_ubo" );
  }

  void OGL::updateLight(unsigned int id, const GLLight& light) {

    LightIdMap::iterator itr;
    assert( (itr = _light_id_map.find(id) ) == _light_id_map.end() );

    unsigned int buffer_offset = itr->second;

    bindLightBuffer();

    // update light data
    GL_CHECK(glBufferSubData(  GL_UNIFORM_BUFFER,
                      sizeof(GLVector<4>) + buffer_offset * sizeof(GLLight), sizeof(GLLight), &light ));

    unbindLightBuffer();
  }

} // END namespace GL

} // END namespace GMlib
