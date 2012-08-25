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

#include "gmglshadermanager.h"

// gmlib::trianglesystem
#include <trianglesystem/gmtrianglesystem.h>

// stl
#include <limits>
#include <iostream>


namespace GMlib {


  std::string OGL::_log;
  OGL::FBOMap   OGL::_fbos;
  OGL::BOMap    OGL::_bos;

  GLuint OGL::_select_fbo = 0;
  GLuint OGL::_select_rbo_color = 0;
  GLuint OGL::_select_rbo_depth = 0;
  int OGL::_select_fbo_h = 0;
  int OGL::_select_fbo_w = 0;

  bool OGL::_select_exists = false;


  //  GLuint OGL::_render_fbo = 0;
  GLuint OGL::_render_rbo_color = 0;
  GLuint OGL::_render_rbo_selected = 0;
  GLuint OGL::_render_rbo_depth = 0;
  int OGL::_render_fbo_h = 0;
  int OGL::_render_fbo_w = 0;

  bool OGL::_render_exists = false;

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

    glBindFramebuffer( GL_FRAMEBUFFER, _fbos[name].id );

    return true;
  }

  bool OGL::bindBo(const std::string &name) {

    _clearLog();

    if( _nameEmpty( name, "VBO" ) )
      return false;

    if( !_boExists(name, true) )
      return false;

    glBindBuffer( _bos[name].target, _bos[name].id );

    return true;
  }

  void OGL::cleanUp() {

    deleteStandardRepBOs();
    deleteSelectBuffer();
    deleteRenderBuffer();
    GLShaderManager::cleanUp();
  }

  GLuint OGL::createFbo() {

    GLuint id;
    glGenFramebuffers( 1, &id );
    return id;
  }

  bool OGL::createFbo(const std::string &name) {

    _clearLog();

    if( _nameEmpty( name, "FBO" ) )
      return false;

    if( _fboExists(name, false) )
      return false;

    FBOInfo fbo;
    glGenFramebuffers( 1, &fbo.id );

    _fbos[name] = fbo;

    return true;
  }

  GLuint OGL::createBo() {

    GLuint id;
    glGenBuffers( 1, &id );
    return id;
  }

  bool OGL::createBo(const std::string &name, GLenum target ) {

    _clearLog();

    if( _nameEmpty( name, "BO" ) )
      return false;

    if( _boExists(name, false) )
      return false;

    BOInfo bo;
    glGenBuffers( 1, &bo.id );
    bo.target = target;

    _bos[name] = bo;

    return true;
  }

  void OGL::deleteFbo(GLuint id) {

    glDeleteFramebuffers( 1, &id );
  }

  bool OGL::deleteFbo(const std::string &name) {

    _clearLog();

    if( _nameEmpty( name, "FBO" ) )
      return false;

    if( !_fboExists(name, true) )
      return false;

    // Detach "render" buffers

    glDeleteFramebuffers( 1, &(_fbos[name].id) );

    _fbos.erase( name );

    return true;
  }

  void OGL::deleteBo(GLuint id) {

    glDeleteBuffers( 1, &id );
  }

  bool OGL::deleteBo(const std::string &name) {

    _clearLog();

    if( _nameEmpty( name, "BO" ) )
      return false;

    if( !_boExists(name, true) )
      return false;

    glDeleteBuffers( 1, &(_bos[name].id) );

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
    createRenderBuffer();
    createSelectBuffer();
    createStandardRepBOs();
  }

  bool OGL::releaseFbo(const std::string &name) {

    _clearLog();

    if( _nameEmpty( name, "FBO" ) )
      return false;

    if( !_fboExists(name, true) )
      return false;

    glBindFramebuffer( GL_FRAMEBUFFER, 0x0 );

    return true;
  }

  bool OGL::releaseBo(const std::string &name) {

    _clearLog();

    if( _nameEmpty( name, "FBO" ) )
      return false;

    if( !_boExists(name, true) )
      return false;

    glBindFramebuffer( _bos[name].target, 0x0 );

    return true;
  }

  bool OGL::setBoTarget(const std::string &name, GLenum target) {

    _clearLog();

    if( _nameEmpty( name, "FBO" ) )
      return false;

    if( !_boExists(name, true) )
      return false;

    _bos[name].target = target;

    return true;
  }




























  void OGL::bindRenderBuffer() {

    bindFbo( "render_fbo" );

    GLenum buffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
    glDrawBuffers( 2, buffers );
  }

  void OGL::bindSelectBuffer() {

    glBindFramebuffer( GL_FRAMEBUFFER, OGL::_select_fbo );
  }

  void OGL::clearRenderBuffer() {

    if( !_render_exists )
      return;

    bindFbo( "render_fbo" );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    releaseFbo( "render_fbo" );

    float cc[4];
    glGetFloatv( GL_COLOR_CLEAR_VALUE, cc );
    Color c = GMcolor::Black;
    glClearColor( c );

    bindFbo( "render_fbo_selected" );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    releaseFbo( "render_fbo_selected" );

    ::glClearColor( GLclampf(cc[0]), GLclampf(cc[1]), GLclampf(cc[2]), GLclampf(cc[3]) );
  }

  void OGL::clearSelectBuffer() {

    if( !_select_exists )
      return;

    const Color &c = GMcolor::Black;

    glBindFramebuffer( GL_FRAMEBUFFER, OGL::_select_fbo );
    glClearColor( c );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glBindFramebuffer( GL_FRAMEBUFFER, 0x0 );
  }

  void OGL::createRenderBuffer() {

    if( _render_exists )
      return;

    // Create a render FBO
    createFbo( "render_fbo" );

    // Create a render color RBO
    glGenTextures( 1, &_render_rbo_color );
    glBindTexture( GL_TEXTURE_2D, _render_rbo_color ); {

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    } glBindTexture( GL_TEXTURE_2D, 0x0 );

    // Create a render color RBO
    glGenTextures( 1, &_render_rbo_selected );
    glBindTexture( GL_TEXTURE_2D, _render_rbo_selected ); {

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    } glBindTexture( GL_TEXTURE_2D, 0x0 );

    // Create a render depth RBO
    glGenRenderbuffers( 1, &_render_rbo_depth );

    // Bind render buffers to frame buffer.
    bindFbo( "render_fbo" ); {

      glBindRenderbuffer( GL_RENDERBUFFER, _render_rbo_depth );
      glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _render_rbo_depth );
      glBindRenderbuffer( GL_RENDERBUFFER, 0x0 );

      glBindTexture( GL_TEXTURE_2D, _render_rbo_color );
      glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _render_rbo_color, 0 );
      glBindTexture( GL_TEXTURE_2D, 0x0 );

      glBindTexture( GL_TEXTURE_2D, _render_rbo_selected );
      glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, _render_rbo_selected, 0 );
      glBindTexture( GL_TEXTURE_2D, 0x0 );

    } releaseFbo( "render_fbo" );

    // Create a render FBO which only contains the selected texture as a rendering target
    // and one for the color.
    // This is mainly for individual clearing of the buffers.
    createFbo( "render_fbo_color" );

    bindFbo( "render_fbo_color" ); {

      glBindTexture( GL_TEXTURE_2D, _render_rbo_color );
      glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _render_rbo_color, 0 );
      glBindTexture( GL_TEXTURE_2D, 0x0 );
    } releaseFbo( "render_fbo_color" );

    createFbo( "render_fbo_selected" );

    bindFbo( "render_fbo_selected" ); {

      glBindTexture( GL_TEXTURE_2D, _render_rbo_selected );
      glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _render_rbo_selected, 0 );
      glBindTexture( GL_TEXTURE_2D, 0x0 );
    } releaseFbo( "render_fbo_selected" );



    _render_exists = true;
  }

  void OGL::createSelectBuffer() {

    if( _select_exists )
      return;

    // Create a selection FBO
    glGenFramebuffers( 1, &_select_fbo );

    // Create a selection color RBO
    glGenRenderbuffers( 1, &_select_rbo_color );

    // Create a selection depth RBO
    glGenRenderbuffers( 1, &_select_rbo_depth );

    // Bind render buffers to frame buffer.
    glBindFramebuffer( GL_FRAMEBUFFER, _select_fbo ); {

      glBindRenderbuffer( GL_RENDERBUFFER, _select_rbo_depth );
      glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _select_rbo_depth );

      glBindRenderbuffer( GL_RENDERBUFFER, _select_rbo_color );
      glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _select_rbo_color );

      glBindRenderbuffer( GL_RENDERBUFFER, 0x0 );

    } glBindFramebuffer( GL_FRAMEBUFFER, 0x0 );

    _select_exists = true;
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
    glBufferData( GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), cube, GL_STATIC_DRAW );
    OGL::releaseBo( "std_rep_cube" );

    OGL::bindBo( "std_rep_cube_indices" );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, 24 * sizeof(GLushort), cube_indices, GL_STATIC_DRAW );
    OGL::releaseBo( "std_rep_cube_indices" );

    OGL::bindBo( "std_rep_frame_indices" );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, 24 * sizeof(GLushort), frame_indices, GL_STATIC_DRAW );
    OGL::releaseBo( "std_rep_frame_indices" );
  }

  void OGL::deleteRenderBuffer() {

    if( !_render_exists )
      return;

    // Delete the buffers used for the render buffer
    deleteFbo( "render_fbo" );
    glDeleteTextures( 1, &_render_rbo_color );
    glDeleteTextures( 1, &_render_rbo_selected );
    glDeleteRenderbuffers( 1, &_render_rbo_depth );

    _render_exists = false;
  }

  void OGL::deleteSelectBuffer() {

    if( !_select_exists )
      return;

    // Delete the buffers used for the selection buffer
    glDeleteFramebuffers( 1, &_select_fbo );
    glDeleteRenderbuffers( 1, &_select_rbo_color );
    glDeleteRenderbuffers( 1, &_select_rbo_depth );

    _select_exists = false;
  }

  void OGL::deleteStandardRepBOs() {

    deleteBo( "std_rep_cube");
    deleteBo( "std_rep_cube_indices");
    deleteBo( "std_rep_frame_indices" );
  }

  GLuint OGL::getRenderBuffer() {


    return getFboId( "render_fbo" );
  }

  GLuint OGL::getSelectBuffer() {

    return _select_fbo;
  }

  int OGL::getRenderBufferHeight() {

    return _render_fbo_h;
  }

  int OGL::getSelectBufferHeight() {

    return _select_fbo_h;
  }

  int OGL::getRenderBufferWidth() {

    return _render_fbo_w;
  }

  int OGL::getSelectBufferWidth() {

    return _select_fbo_w;
  }

  GLuint OGL::getRenderColorBuffer() {

    return _render_rbo_color;
  }

  GLuint OGL::getRenderSelectedBuffer() {

    return _render_rbo_selected;
  }

  void OGL::releaseRenderBuffer() {

    glBindFramebuffer( GL_FRAMEBUFFER, 0x0 );
  }

  void OGL::releaseSelectBuffer() {

    glBindFramebuffer( GL_FRAMEBUFFER, 0x0 );
  }

  void OGL::setRenderBufferSize(int width, int height) {

    _render_fbo_w = width;
    _render_fbo_h = height;

    glBindRenderbuffer( GL_RENDERBUFFER, _render_rbo_depth );
    glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH_COMPONENT, _render_fbo_w, _render_fbo_h );
    glBindRenderbuffer( GL_RENDERBUFFER, 0x0 );

    glBindTexture( GL_TEXTURE_2D, _render_rbo_color);
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, _render_fbo_w, _render_fbo_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0x0 );
    glBindTexture( GL_TEXTURE_2D, 0x0 );

    glBindTexture( GL_TEXTURE_2D, _render_rbo_selected);
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, _render_fbo_w, _render_fbo_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0x0 );
    glBindTexture( GL_TEXTURE_2D, 0x0 );
  }

  void OGL::setSelectBufferSize(int width, int height) {

    _select_fbo_w = width;
    _select_fbo_h = height;

    glBindRenderbuffer( GL_RENDERBUFFER, _select_rbo_depth );
    glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH_COMPONENT, _select_fbo_w, _select_fbo_h );
    glBindRenderbuffer( GL_RENDERBUFFER, _select_rbo_color );
    glRenderbufferStorage( GL_RENDERBUFFER, GL_RGB, _select_fbo_w, _select_fbo_h );
    glBindRenderbuffer( GL_RENDERBUFFER, 0x0 );
  }























  GLuintCMap GLFramebufferObject::_ids;

  GLFramebufferObject::GLFramebufferObject() {

    _name = "";

    _id = OGL::createFbo();
    _valid = true;

    _ids[_id] = 1;
  }

  GLFramebufferObject::GLFramebufferObject(const std::string name) {

    _name = name;

    _valid = OGL::createFbo( name );
    _id = OGL::getFboId( name );

    _ids[_id] = 1;
  }

  GLFramebufferObject::GLFramebufferObject(const GLFramebufferObject &copy) {

    _name = copy._name;
    _id = copy._id;

    _ids[_id]++;
  }

  GLFramebufferObject::~GLFramebufferObject() {

    _ids[_id]--;
    if( _ids.count(_id) <= 0 )
      OGL::deleteFbo( _id );
  }

  void GLFramebufferObject::bind() const {

    glBindFramebuffer( GL_FRAMEBUFFER, _id );
  }

  GLuint GLFramebufferObject::getId() const {

    return _id;
  }

  std::string GLFramebufferObject::getName() const {

    return _name;
  }

  bool GLFramebufferObject::isValid() const {

    return _valid;
  }

  void GLFramebufferObject::unbind() const {

    glBindFramebuffer( GL_FRAMEBUFFER, 0x0 );
  }















  GLuintCMap GLBufferObject::_ids;

  GLBufferObject::GLBufferObject( GLenum target ) {

    _name = "";
    _id = OGL::createBo();
    _target = target;
    _valid = true;

    _ids[_id] = 1;
  }

  GLBufferObject::GLBufferObject( const std::string name ) {

    _name = name;

    _valid = OGL::createBo( _name, GL_ARRAY_BUFFER );

    _target = OGL::getBoTarget( _name );
    _id = OGL::getBoId( _name );

    _ids[_id] = 1;
  }

  GLBufferObject::GLBufferObject( const std::string name, GLenum target ) {

    _name = name;
    _target = target;

    _valid = OGL::createBo( _name, _target );
    _id = OGL::getBoId( _name );

    _ids[_id] = 1;
  }

  GLBufferObject::GLBufferObject( const GLBufferObject& copy ) {

    _name = copy._name;
    _id   = copy._id;
    _target = copy._target;
    _valid = copy._valid;

    _ids[_id]++;
  }

  GLBufferObject::~GLBufferObject() {

    _ids[_id]--;
    if( _ids.count(_id) <= 0 )
      OGL::deleteBo(_id);
  }

  void GLBufferObject::createBufferData(GLsizeiptr size, const GLvoid *data, GLenum usage) {

    glBufferData( _target, size, data, usage );
  }

  void GLBufferObject::disableVertexArrayPointer( GLuint vert_loc ) {

    glDisableVertexAttribArray( vert_loc );
  //  release();
  }

  void GLBufferObject::enableVertexArrayPointer( GLuint vert_loc, int size, GLenum type, bool normalized, GLsizei stride, const void* offset ) {

  //  bind();
    glVertexAttribPointer( vert_loc, size, type, normalized, stride, offset );
    glEnableVertexAttribArray( vert_loc );

  }

  GLuint GLBufferObject::getId() const {

    return _id;
  }

  GLenum GLBufferObject::getTarget() const {

    return _target;
  }

  std::string GLBufferObject::getName() const {

    return _name;
  }

  bool GLBufferObject::isValid() const {

    return _valid;
  }

  void GLBufferObject::setTarget( GLenum target ) {

    _target = target;
    OGL::setBoTarget( _name, _target );
  }

  void GLBufferObject::unmapBuffer() const {

    glUnmapBuffer( _target );
  }





















  GLVertexBufferObject::GLVertexBufferObject() :
    GLBufferObject( GL_ARRAY_BUFFER ) {}

  GLVertexBufferObject::GLVertexBufferObject( const std::string& name ) :
    GLBufferObject( name, GL_ARRAY_BUFFER ) {}




























  IndexBufferObject::IndexBufferObject() : GLBufferObject( GL_ELEMENT_ARRAY_BUFFER ) {

    _type = GL_UNSIGNED_INT;
    _type_size = sizeof(GLuint);
  }

  IndexBufferObject::IndexBufferObject(const std::string &name) :
    GLBufferObject( name, GL_ELEMENT_ARRAY_BUFFER ) {
  }

  void IndexBufferObject::createBufferData(unsigned int no_indices, const GLvoid *data, GLenum usage) {

    GLBufferObject::createBufferData( no_indices * _type_size, data, usage );
  }

  void IndexBufferObject::draw() {}

  const GLenum &IndexBufferObject::getMode() const {

    return _mode;
  }

  const GLenum &IndexBufferObject::getType() const {

    return _type;
  }

  const GLsizei &IndexBufferObject::getTypeSize() const {

    return _type_size;
  }













  TrianglesIBO::TrianglesIBO() : IndexBufferObject() {

    init();
  }

  TrianglesIBO::TrianglesIBO(const std::string &name) :
    IndexBufferObject( name ) {

    init();
  }

  void TrianglesIBO::draw() {

    bind();
    glDrawElements( GL_TRIANGLES, _no_indices, getType(), (const GLvoid*)0x0 );
    unbind();
  }

  void TrianglesIBO::fill(const TriangleFacets<float> *tf) {

    _no_indices = tf->getNoTriangles() * 3;

    GLuint indices[_no_indices];
    GLuint *iptr = indices;

    for( int i = 0; i < tf->getNoTriangles(); i++ ) {

      Array< TSVertex<float>* > tri_verts = tf->getTriangle(i)->getVertices();
      for( int j = 0; j < tri_verts.getSize(); j++ )
        for( int k = 0; k < tf->getSize(); k++ )
          if( tri_verts[j] == tf->getVertex(k) )
            *iptr++ = k;
    }

    createBufferData( _no_indices, indices, GL_STATIC_DRAW );
  }

  void TrianglesIBO::init() {

    _no_indices = 0;
  }
















  TriangleStripIBO::TriangleStripIBO() : IndexBufferObject() {

    init();
  }

  TriangleStripIBO::TriangleStripIBO(const std::string &name) :
    IndexBufferObject(name) {

    init();
  }

  void TriangleStripIBO::draw() {

    bind();
    for( int i = 0; i < _no_strips; ++i )
      glDrawElements( GL_TRIANGLE_STRIP, _no_indices_per_strip, getType(), (const GLvoid*)(i * _strip_size) );
    unbind();
  }

  void TriangleStripIBO::fill( int m1, int m2 ) {

    _no_strips = m1 - 1;
    _no_indices_per_strip = m2 * 2;

    int no_indices = _no_strips * _no_indices_per_strip;

    GLuint indices[no_indices];
    for( int i = 0; i < m1-1; i++ ) {

      const int idx_i = i * m2 * 2;
      for( int j = 0; j < m2; j++ ) {

        const int idx_j = idx_i + (j*2);
        indices[idx_j]   = i*m2 + j;
        indices[idx_j+1] = (i+1)*m2 + j;
      }
    }

    bind();
    createBufferData( no_indices, indices, GL_STATIC_DRAW );
    unbind();

    // Strip size must be set after createBufferData( ... ) is called
    // as the type size is defined by the createBufferData function
    _strip_size = getTypeSize() * _no_indices_per_strip;
  }

  void TriangleStripIBO::init() {

    _no_strips = 0;
    _no_indices_per_strip = 0;
    _strip_size = 0;
  }




} // END namespace GMlib
