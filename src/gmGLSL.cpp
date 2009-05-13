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



/*! \file gmGLSL.cpp
 *
 *  Pending Documentation
 *
 *  \date   2009-05-02
 */


#include "gmGLSL.h"
#include <iostream>
using namespace std;

#ifdef GM_GPU_GLSL


namespace GMlib
{
  namespace GPU
  {
    namespace GLSL
    {

      GLShader::GLShader()
      {
        _vs_src = 0x0;
        _fs_src = 0x0;

        _init();
      }


      GLShader::GLShader( const char* vs, const char* fs )
      {
        _vs_src       = vs;
        _fs_src       = fs;

        _init();
      }


      GLShader::GLShader( const GLShader& cpy )
      {
        _vs_src       = cpy._vs_src;
        _fs_src       = cpy._fs_src;

        _prog         = cpy._prog;
        _prog_backup  = cpy._prog_backup;
        _vs           = cpy._vs;
        _fs           = cpy._fs;

        _active       = cpy._active;
        _changed      = cpy._changed;
        _valid        = cpy._valid;
      }


      GLShader::GLShader( GLShader* cpy )
      {
        _vs_src       = cpy->_vs_src;
        _fs_src       = cpy->_fs_src;

        _prog         = cpy->_prog;
        _prog_backup  = cpy->_prog_backup;
        _vs           = cpy->_vs;
        _fs           = cpy->_fs;

        _active       = cpy->_active;
        _changed      = cpy->_changed;
        _valid        = cpy->_valid;
      }


      GLShader::~GLShader()
      {}


      char* GLShader::_get_error_info( bool shader, unsigned int v )
      {
        int   len  = 0;
        char  *log = 0x0;

        if( shader )
        {
          glGetShaderiv( v, GL_INFO_LOG_LENGTH, &len );

          if( len > 0 )
          {
            log = new char[len];
            glGetShaderInfoLog( v, len, &len, log );
            return log;
          }
        }
        else
        {
          glGetProgramiv( v, GL_INFO_LOG_LENGTH, &len );

          if( len > 0 )
          {
            log = new char[len];
            glGetProgramInfoLog( v, len, &len, log );
            return log;
          }
        }

        return 0x0;
      }


      void GLShader::_init()
      {
        _prog         = 0;
        _prog_backup  = 0;
        _fs           = 0;
        _vs           = 0;

        _active       = false;
        _changed      = true;
        _valid        = false;
      }


      char* GLShader::getFragmentError()
      {
        return _get_error_info( true, _fs );
      }


      unsigned int GLShader::getProgramData() const
      {
        return _prog;
      }


      char* GLShader::getProgramError()
      {
        return _get_error_info( false, _prog );
      }


      char* GLShader::getVertexError()
      {
        return _get_error_info( true, _vs );
      }


      void GLShader::glSet()
      {
        glUseProgram( _prog );
        _active = true;
      }


      void GLShader::glUnSet()
      {
        glUseProgram( 0 );
        _active = false;
      }


      bool GLShader::isActive() const
      {
        return _active;
      }


      bool GLShader::isChanged() const
      {
        return _changed;
      }


      bool GLShader::isValid() const
      {
        return _valid;
      }


      bool GLShader::initShader( bool clean_first )
      {
        int success       = 0;

        // Reset if neccesary
        if( clean_first )
          resetShader();

        // Create program
        _prog = glCreateProgram();


        // Create Vertex shader
        if( _vs_src != 0x0 )
        {
          _vs = glCreateShader( GL_VERTEX_SHADER );
          glShaderSource( _vs, 1, &_vs_src, NULL );
          glCompileShader( _vs );

          //glGetShaderiv( _vs, GL_COMPILE_STATUS, &success );

          glAttachShader( _prog, _vs );
        }


        // Create Fragment shader
        if( _fs_src != 0x0 )
        {
          _fs = glCreateShader( GL_FRAGMENT_SHADER );
          glShaderSource( _fs, 1, &_fs_src, NULL );

          //glGetShaderiv( _fs, GL_COMPILE_STATUS, &success );

          glAttachShader( _prog, _fs );
        }


        // Linking shader program
        glLinkProgram( _prog );

        glGetProgramiv( _prog, GL_LINK_STATUS, &success );


        // Validate shader program
        if( success )
        {
          // Validate shader program
          glValidateProgram( _prog );

          glGetProgramiv( _prog, GL_VALIDATE_STATUS, &success );
        }


        // Valid shader program
        if( success ) {
          _changed  = false;
          _valid    = true;
          return true;
        }

        _valid = false;
        return false;
      }


      void GLShader::resetShader()
      {
        // Deactivate program
        glUseProgram( 0 );

        if( _prog )
        {
          // Detatch and delete VertexShader
          if( glIsShader( _vs ) )
          {
            glDetachShader( _prog, _vs );
            glDeleteShader( _vs );
          }


          // Detatch and delete FragmentShader
          if( glIsShader( _fs ) )
          {
            glDetachShader( _prog, _fs );
            glDeleteShader( _fs );
          }


          // Delete program
          glDeleteProgram( _prog );
        }

        _prog         = 0;
        _prog_backup  = 0;
        _vs           = 0;
        _fs           = 0;
        _active       = false;
        _changed      = true;
        _valid        = false;
      }


      void GLShader::set( const char* vs, const char* fs)
      {
        _vs_src   = vs;
        _fs_src   = fs;

        _changed  = true;
      }


      void GLShader::setFragmentShader( const char* fs )
      {
        _fs_src   = fs;
        _changed  = true;
      }


      void GLShader::setVertexShader( const char* vs )
      {
        _vs_src   = vs;
        _changed  = true;
      }


      void GLShader::toggleShader( bool force )
      {
        if( force )
        {
          if( _active )
          {
            glUseProgram( 0 );
            _active = false;
          }
          else
          {
            glUseProgram( _prog );
            _active = true;
          }
        }
        else
        {
          if( glIsProgram( _prog ) )
          {
            _prog_backup  = _prog;
            _prog         = 0;
            _active       = false;
          }
          else if( glIsProgram( _prog_backup ) )
          {
            _prog   = _prog_backup;
            _active = true;
          }
        }
      }


    } // End namespace GLSL

  } // End namespace GPU

} // End namespace GMlib


#endif // GM_GPU_GLSL_ENABLED
