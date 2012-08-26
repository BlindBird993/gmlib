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
#include <core/types/gmpoint2d.h>
#include <core/types/gmpoint3d.h>
#include <core/types/gmmatrix.h>
#include <core/utils/gmcolor.h>
#include <core/utils/gmstream.h>

// Include Glew header and leave the gl mangling to GLEW
#include <GL/glew.h>

// STL
#include <map>
#include <string>


namespace GMlib {

  template <typename T>
  class TriangleFacets;



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

    ::glClearColor( GLclampf(c.getRedC()), GLclampf(c.getGreenC()), GLclampf(c.getBlueC()), GLclampf(c.getAlphaC()) );
  }



  // ***********
  // SwapBuffers

  void swapBuffers(void);






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

    static const std::string&   getLog();

  private:
    static std::string          _log;

    static void                 _appendLog( const std::string& log );
    static void                 _clearLog();
    static bool                 _nameEmpty( const std::string& name, const std::string& type = std::string() );



    // FramebufferObject
  public:

    struct FBOInfo {
      GLuint    id;
    };

    typedef std::map< std::string, OGL::FBOInfo >   FBOMap;

    static bool               bindFbo( const std::string& name );
    static GLuint             createFbo();
    static bool               createFbo( const std::string& name );
    static void               deleteFbo( GLuint id );
    static bool               deleteFbo( const std::string& name );
    static GLuint             getFboId( const std::string& name );
    static const FBOMap&      getFbos();
    static bool               releaseFbo( const std::string& name );

  private:
    static FBOMap             _fbos;

    static bool               _fboExists( const std::string& name, bool exist );





    // BufferObject
  public:

    struct BOInfo {
      GLuint    id;
      GLenum    target;
    };

    typedef std::map< std::string, OGL::BOInfo >    BOMap;

    static bool             bindBo( const std::string& name );
    static GLuint           createBo();
    static bool             createBo( const std::string& name, GLenum target = GL_ARRAY_BUFFER );
    static void             deleteBo( GLuint id );
    static bool             deleteBo( const std::string& name );
    static GLuint           getBoId( const std::string& name );
    static GLenum           getBoTarget( const std::string& name );
    static const BOMap&     getBos();
    static bool             releaseBo( const std::string& name );
    static bool             setBoTarget( const std::string& name, GLenum target = GL_ARRAY_BUFFER  );

  private:
    static std::map< std::string, OGL::BOInfo >    _bos;

    static bool                 _boExists( const std::string& name, bool exist );














    // Default render buffer
  public:
    static void         bindRenderBuffer();
    static void         clearRenderBuffer();
    static void         createRenderBuffer();
    static void         deleteRenderBuffer();
    static GLuint       getRenderBuffer();
    static int          getRenderBufferHeight();
    static int          getRenderBufferWidth();
    static GLuint       getRenderColorBuffer();
    static GLuint       getRenderSelectedBuffer();
    static void         releaseRenderBuffer();
    static void         setRenderBufferSize( int width, int height );

  private:
    static GLuint       _render_rbo_color;
    static GLuint       _render_rbo_selected;
    static GLuint       _render_rbo_depth;

    static int          _render_fbo_w;
    static int          _render_fbo_h;

    static bool         _render_exists;


    // Selection Buffer
  public:
    static void         bindSelectBuffer();
    static void         clearSelectBuffer();
    static void         createSelectBuffer();
    static void         deleteSelectBuffer();
    static GLuint       getSelectBuffer();
    static int          getSelectBufferHeight();
    static int          getSelectBufferWidth();
    static void         releaseSelectBuffer();
    static void         setSelectBufferSize( int width, int height );

  private:
    static GLuint       _select_fbo;
    static GLuint       _select_rbo_color;
    static GLuint       _select_rbo_depth;

    static int          _select_fbo_w;
    static int          _select_fbo_h;

    static bool         _select_exists;

    // Buffer Objects
  public:
    static void         createSelectorRepBOs();
    static void         deleteSelectorRepBOs();
    static void         createStandardRepBOs();
    static void         deleteStandardRepBOs();


  }; // END class OpenGL





























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










} // END namespace GMlib


#endif // __gmOPENGL_H__
