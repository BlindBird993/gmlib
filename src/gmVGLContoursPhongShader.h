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



/*! \file gmVGLContoursPhongShader.h
 *
 *  Interface for the VGLContoursPhongShader class.
 *
 *  \date   2009-05-23
 */


#ifndef __gmVGLCONTOURSPHONGSHADER_H__
#define __gmVGLCONTOURSPHONGSHADER_H__


// STL includes
#include <string>

// GMlib includes
#include "gmVContours.h"
#include "gmGLPhongShader.h"


#ifdef GM_GPU_GLSL


namespace GMlib {

  namespace GPU {

    namespace GLSL {

      template <typename T, int n>
      class VGLContoursPhongShader : public VContours<T,n>, public GLPhongShader {
      public:
        VGLContoursPhongShader();
        ~VGLContoursPhongShader();

        void display();
        std::string getIdentity() const;


      }; // End VGLContoursPhongShader

    }// End namespace GLSL

  } // End namespace GPU

} // Ene namespace GMlib


// Include VGLShader class function implementations
#include "gmVGLContoursPhongShader.c"


#endif // GM_GPU_GLSL


#endif // __gmVGLCONTOURSPHONGSHADER_H__





