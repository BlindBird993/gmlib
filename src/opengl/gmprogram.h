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


#ifndef __gm_OPENGL_PROGRAM_H__
#define __gm_OPENGL_PROGRAM_H__


#include "gmglobject.h"

//local
#include "gmtexture.h"
#include "gmshader.h"
#include "bufferobjects/gmuniformbufferobject.h"


namespace GMlib {

namespace GL {

  namespace Private {
    struct ProgramInfo : public GLObjectInfo {
      std::string linker_log;
    };
  }


  class Program : public Private::GLObject<Private::ProgramInfo> {
  public:
    explicit Program();
    ~Program();

    void                      create();
    void                      create( const std::string& name );

    bool                      link();
    const std::string&        getLinkerLog() const;


    void                      disableAttributeArray( const std::string& name ) const;
    void                      disableAttributeArray( const GL::AttributeLocation& location ) const;
    void                      enableAttributeArray( const std::string& name ) const;
    void                      enableAttributeArray( const GL::AttributeLocation& location ) const;
    GL::AttributeLocation     getAttributeLocation( const std::string& name ) const;

    GL::UniformBlockIndex     getUniformBlockIndex( const std::string& name ) const;
    GL::UniformLocation       getUniformLocation( const std::string& name ) const;

    void                      setUniform( const std::string& name, bool b ) const;
    void                      setUniform( const std::string& name, float f ) const;
    void                      setUniform( const std::string& name, int i ) const;
    void                      setUniform( const std::string& name, const Color& c ) const;
    void                      setUniform( const std::string& name, const Matrix<float,3,3>& matrix, int count = 1, bool transpose = true ) const;
    void                      setUniform( const std::string& name, const Matrix<float,4,4>& matrix, int count = 1, bool transpose = true ) const;
    void                      setUniform( const std::string& name, const APoint<float,3>& p ) const;
    void                      setUniform( const std::string& name, const APoint<float,4>& p ) const;
    void                      setUniform( const std::string& name, const Texture&, GLenum tex_unit, GLuint tex_nr ) const;
    void                      setUniformBlockBinding( const std::string& name, const UniformBufferObject& ubo, GLuint binding_point ) const;

    void                      attachShader( const Shader& shader ) const;
    void                      detachShader( const Shader& shader ) const;


  private:
    void                      updateLinkerLog();
    std::vector<GLuint>       getAttachedShaders() const;
    void                      attachShaderInternal( GLuint id ) const;
    void                      detachShaderInternal( GLuint id ) const;

    /* pure-virtual functions from Object */
    virtual GLuint            getCurrentBoundId() const;
    virtual void              doBind( GLuint id ) const;
    virtual GLuint            doGenerate() const;
    virtual void              doDelete(GLuint id) const;


  }; // END class Program


} // END namespace GL

} // END namespace GMlib


#endif // __gm_OPENGL_PROGRAM_H__
