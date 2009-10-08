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



/*! \file gmVGLShader.h
 *
 *  Interface for the VGLShader class.
 *
 *  \date   2009-05-10
 */


#ifndef __gmVGLSHADER_H__
#define __gmVGLSHADER_H__


// STL includes
#include <string>

// GMlib includes
#include "gmGLSL.h"
#include "gmVDefault.h"


#ifdef GM_GPU_GLSL


namespace GMlib {

  namespace GPU {

    namespace GLSL {

      template <typename T, int n>
      class VGLShader : public VDefault<T,n>, public GLShader {
      public:
        VGLShader();
        VGLShader( const char* vs, const char* fs, bool compile = false );
        VGLShader( const VGLShader<T,n>& cpy );
        ~VGLShader();

        void        display();
        std::string getIdentity() const;


      }; // End VGLShader

    }// End namespace GLSL

  } // End namespace GPU

} // Ene namespace GMlib


// Include VGLShader class function implementations
#include "gmVGLShader.c"


#endif // GM_GPU_GLSL


#endif // __gmVGLSHADER_H__




