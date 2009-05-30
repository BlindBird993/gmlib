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



/*! \file gmGLSL.h
 *
 *  Pending Documentation
 *
 *  \date   2009-05-02
 */


#ifndef __gmGPUGLSL_H__
#define __gmGPUGLSL_H__

#include "gmOpenGL.h"

#ifdef GM_GL_EXTENSION
  #define GM_GPU_GLSL
#endif


#ifdef  GM_GPU_GLSL


namespace GMlib {

  namespace GPU {

    namespace GLSL {


      class GLShader {
      public:
        GLShader();
        GLShader( const char* vs, const char* fs, bool compile = false );
        GLShader( const GLShader& cpy );
        GLShader( GLShader* cpy );
        ~GLShader();

        char*         getFragmentError();
        const char*   getFragmentSource();
        unsigned int  getProgramData() const;
        char*         getProgramError();
        char*         getVertexError();
        const char*   getVertexSource();
        void          glSet();
        void          glUnSet();
        bool          isActive() const;
        bool          isChanged() const;
        bool          isValid() const;
        bool          initShader( bool clean_first = false );
        void          resetShader();
        void          set( const char* vs, const char* fs );
        void          setFragmentShader( const char* fs );
        void          setVertexShader( const char* vs );
        void          toggleShader( bool force = false );


      protected:
        bool          _active;
        bool          _changed;
        bool          _valid;


        unsigned int  _prog;
        unsigned int  _prog_backup;
        unsigned int  _vs;
        unsigned int  _fs;


        const char    *_vs_src;
        const char    *_fs_src;


      private:
        char*         _get_error_info( bool shader, unsigned int v );
        void          _init();


      }; // End class Shader


    } // End namespace GLSL

  } // End namespace GPU

} // End namespace GMlib


#endif // GM_GPU_GLSL

#endif // __gmGPUGLSL_H__
