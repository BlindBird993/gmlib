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



/*! \file gmopengl.h
 *
 *  GMlib interface to the OpenGL API
 */

#ifndef __gmOPENGL_H__
#define __gmOPENGL_H__


//#if defined(_WIN32)
////  To avoid including <windows.h> to avoid name space pollution,
////	but Win32's <GL/gl.h> needs APIENTRY and WINGDIAPI defined properly.
//# if 1
//#  define  WIN32_LEAN_AND_MEAN
//#  include <windows.h>
//# else
//   // XXX This is from Win32's <windef.h>
//#  ifndef APIENTRY
//#   define GLUT_APIENTRY_DEFINED
//#   if (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED)
//#    define APIENTRY    __stdcall
//#   else
//#    define APIENTRY
//#   endif
//#  endif
//   // XXX This is from Win32's <winnt.h>
//#  ifndef CALLBACK
//#   if (defined(_M_MRX000) || defined(_M_IX86) || defined(_M_ALPHA) || defined(_M_PPC)) && !defined(MIDL_PASS)
//#    define CALLBACK __stdcall
//#   else
//#    define CALLBACK
//#   endif
//#  endif
//   // XXX This is from Win32's <wingdi.h> and <winnt.h>
//#  ifndef WINGDIAPI
//#   define GLUT_WINGDIAPI_DEFINED
//#   define WINGDIAPI __declspec(dllimport)
//#  endif
//   // XXX This is from Win32's <ctype.h>
//#  ifndef _WCHAR_T_DEFINED
//typedef unsigned short wchar_t;
//#   define _WCHAR_T_DEFINED
//#  endif
//# endif
//#endif




// gmlib
#include <core/containers/gmdmatrix.h>
#include <core/types/gmpoint.h>
#include <core/types/gmmatrix.h>
#include <core/utils/gmcolor.h>
#include <core/utils/gmstream.h>

// Include Glew header and leave the gl mangling to GLEW
#include <GL/glew.h>

//#if defined(_WIN32)
////  To avoid including <windows.h> to avoid name space pollution,
////	but Win32's <GL/gl.h> needs APIENTRY and WINGDIAPI defined properly.
//# if 1
//#  define  WIN32_LEAN_AND_MEAN
//#  include <windows.h>
//# else
//   // XXX This is from Win32's <windef.h>
//#  ifndef APIENTRY
//#   define GLUT_APIENTRY_DEFINED
//#   if (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED)
//#    define APIENTRY    __stdcall
//#   else
//#    define APIENTRY
//#   endif
//#  endif
//   // XXX This is from Win32's <winnt.h>
//#  ifndef CALLBACK
//#   if (defined(_M_MRX000) || defined(_M_IX86) || defined(_M_ALPHA) || defined(_M_PPC)) && !defined(MIDL_PASS)
//#    define CALLBACK __stdcall
//#   else
//#    define CALLBACK
//#   endif
//#  endif
//   // XXX This is from Win32's <wingdi.h> and <winnt.h>
//#  ifndef WINGDIAPI
//#   define GLUT_WINGDIAPI_DEFINED
//#   define WINGDIAPI __declspec(dllimport)
//#  endif
//   // XXX This is from Win32's <ctype.h>
//#  ifndef _WCHAR_T_DEFINED
//typedef unsigned short wchar_t;
//#   define _WCHAR_T_DEFINED
//#  endif
//# endif
//#endif


//#include <GL/gl.h>


//#ifndef GL_GLEXT_VERSION
//# define GL_GLEXT_VERSION 86
//#endif

//#include <GL/glext.h>
//#include <GL/glu.h>

// local
#include "utils/gmutils.h"

// STL
#include <vector>
#include <map>
#include <string>
#include <iostream>


namespace GMlib {

namespace GL {

  /***********
   * Constants
   */
  const unsigned int GM_TEXTURE_1D = GL_TEXTURE_1D;
  const unsigned int GM_TEXTURE_2D = GL_TEXTURE_2D;

  const unsigned int GM_OBJECT_LINEAR = GL_OBJECT_LINEAR;
  const unsigned int GM_EYE_LINEAR = GL_EYE_LINEAR;
  const unsigned int GM_SPHERE_MAP = GL_SPHERE_MAP;



  inline
  void glClearColor( const Color& c ) {

    GL_CHECK(::glClearColor( GLclampf(c.getRedC()), GLclampf(c.getGreenC()), GLclampf(c.getBlueC()), GLclampf(c.getAlphaC()) ));
  }



  // ***********
  // SwapBuffers

  void swapBuffers(void);






  struct GLuintType {
    explicit GLuintType() {}
    explicit GLuintType( GLuint uint_data ) : data(uint_data) {}

    const GLuint& operator() () const { return data; }
    const GLuintType& operator = ( const GLuint& data_in ) { data = data_in; return *this; }

    GLuint data;
  };

//  struct AttribLocation : GLuintType {
//    explicit AttribLocation() {}
//    AttribLocation( GLuint location_id ) : GLuintType(location_id) {}
//  };


  typedef GLuintType    AttributeLocation;
  typedef GLuintType    UniformLocation;

  typedef GLuintType    UniformBlockIndex;










  struct GLViewVertex {
    GLclampf x, y;
  };

  struct GLVertex {
    GLfloat x, y, z;
  };

  struct GLNormal {
    GLfloat nx, ny, nz;
  };

  struct GLTex1D {
    GLfloat s;
  };

  struct GLTex2D : GLTex1D {
    GLfloat t;
  };

  struct GLTex3D : GLTex2D {
    GLfloat r;
  };

  struct GLVertexNormal : GLVertex, GLNormal {};
  struct GLVertexNormalTex2D : GLVertex, GLNormal, GLTex2D {};
  struct GLVertexTex1D : GLVertex, GLTex1D {};
  struct GLVertexTex2D : GLVertex, GLTex2D {};

  template <int n,typename T = GLfloat>
  struct GLVector {
    T p[n];
  };

  struct GLLight {
    GLVector<4>   amb;
    GLVector<4>   dif;
    GLVector<4>   spc;

    GLVector<4>   pos;
    GLVector<3>   dir;
    GLfloat       _padding01;

    GLVector<3>   att;
    GLfloat       _padding02;

    GLint         spot_cut;
    GLfloat       spot_exp;
    GLfloat       _padding03[2];
  };

  struct GLMaterial {

    GLVector<4>   amb;
    GLVector<4>   dif;
    GLVector<4>   spc;

    GLfloat       shininess;
    GLfloat       _padding[3];
  };










  typedef std::map< GLuint, int > GLuintCMap;



  /*! \class OGL
   *
   *  static OpenGL class
   */
  class OGL {

    // Global
  public:
    static void                 cleanUp();
    static void                 init();


  }; // END class OpenGL

} // END namespace GL

} // END namespace GMlib


#endif // __gmOPENGL_H__
