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



/*! \file gmglshadermanager.h
 *
 *  Pending Documentation
 */


#ifndef __gmGLSHADERMANAGER_H__
#define __gmGLSHADERMANAGER_H__



#include "gmopengl.h"

// stl
#include <string>
#include <set>
#include <map>



namespace GMlib {


  class GLShaderManager {
  public:
    struct ProgramInfo {
      GLuint    id;

    };

    struct ShaderInfo {
      GLuint    id;
      GLenum    type;
    };


    static bool                                   addShaderToProgram( const std::string& prog_name, const std::string& shader_name );
    static void                                   cleanUp();
    static bool                                   compileShader( const std::string& name );
    static bool                                   createProgram( const std::string& name );
    static bool                                   createShader( const std::string& name, GLenum type );
    static bool                                   deleteProgram( const std::string& name );
    static bool                                   deleteShader( const std::string& name );
    static const std::string&                     getLog();
    static const std::string&                     getInfoLog();
    static GLuint                                 getProgramID( const std::string& name );
    static const std::map< std::string, GLShaderManager::ProgramInfo >   getPrograms();
    static std::set< std::string >                getProgramShaders( const std::string& name );
    static GLuint                                 getShaderID( const std::string& name );
    static std::set< std::string >                getShaderPrograms( const std::string& name );
    static const std::map< std::string, GLShaderManager::ShaderInfo >    getShaders();
    static std::string                            getShaderSource( const std::string& name );
    static GLenum                                 getShaderType( const std::string& name );
    static const std::map< std::string, std::set< std::string > >&    getTree();
    static void                                   init();
    static bool                                   isInitialized();
    static bool                                   isProgramLinked( const std::string& name );
    static bool                                   isShaderCompiled( const std::string& name );
    static bool                                   linkProgram( const std::string& name );
    static bool                                   setShaderSource( const std::string& name, const std::string& source );
    static bool                                   removeShaderFromProgram( const std::string& prog_name, const std::string& shader_name );

  private:
    static std::map< std::string, ProgramInfo >   _programs;
    static std::map< std::string, ShaderInfo >    _shaders;
    static std::map< std::string, std::set< std::string > >   _program_shader;

    static bool                                   _initialized;

    static std::string                            _log;
    static std::string                            _info_log;

    static void                                   _appendLog( const std::string& log );
    static void                                   _clearLog();
    static bool                                   _initPrograms();
    static bool                                   _initShaders();
    static bool                                   _nameEmpty( const std::string& name, const std::string& type = std::string() );
    static bool                                   _programExists( const std::string& name, bool exist );
    static bool                                   _shaderExists( const std::string& name, bool exist );
    static void                                   _updateInfoLog( bool program, GLuint id );

  }; // END class GLShaderManager

} // END namespace GMlib


#endif // __gmGLSHADERMANAGER_H__
