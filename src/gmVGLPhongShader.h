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



/*! \file gmVGLPhongShader.h
 *
 *  Interface for the VGLPhongShader class.
 *
 *  \date   2009-05-12
 */


#ifndef __gmVGLPHONGSHADER_H__
#define __gmVGLPHONGSHADER_H__


// STL includes
#include <string>

// GMlib includes
#include "gmVisualizer.h"
#include "gmGLPhongShader.h"


#ifdef GM_GPU_GLSL


namespace GMlib {

  namespace GPU {

    namespace GLSL {

      template <typename T, int n>
      class VGLPhongShader : public Visualizer<T,n>, public GLPhongShader {
      public:
        VGLPhongShader();
        ~VGLPhongShader();

        void        display();
        std::string getIdentity() const;

      }; // End VGLPhongShader

    }// End namespace GLSL

  } // End namespace GPU

} // Ene namespace GMlib


// Include VGLPhongShader class function implementations
#include "gmVGLPhongShader.c"


#endif // GM_GPU_GLSL


#endif // __gmVGLPHONGSHADER_H__




