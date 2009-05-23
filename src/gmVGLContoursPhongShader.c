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



/*! \file gmVGLContoursPhongShader.c
 *
 *
 *  \date   2009-05-23
 */


#ifdef GM_GPU_GLSL


namespace GMlib {

  namespace GPU {

    namespace GLSL {

      template <typename T, int n>
      inline
      VGLContoursPhongShader<T,n>::VGLContoursPhongShader() : VContours<T,n>(), GLPhongShader() {}


      template <typename T, int n>
      inline
      VGLContoursPhongShader<T,n>::~VGLContoursPhongShader() {}


      template <typename T, int n>
      inline
      void VGLContoursPhongShader<T,n>::display() {

        glSet();
        VContours<T,n>::display();
        glUnSet();
      }


      template <typename T, int n>
      inline
      std::string VGLContoursPhongShader<T,n>::getIdentity() const {

        return "CountoursPhongShader Visualizer";
      }

    } // End namespace GLSL

  } // End namespace GPU

} // End namespace GMlib


#endif // GM_GPU_GLSL
