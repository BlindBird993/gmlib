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


#if defined(_WIN32)
//  To avoid including <windows.h> to avoid name space pollution,
//	but Win32's <GL/gl.h> needs APIENTRY and WINGDIAPI defined properly.
# if 1
#  define  WIN32_LEAN_AND_MEAN
#  include <windows.h>
# else
   // XXX This is from Win32's <windef.h>
#  ifndef APIENTRY
#   define GLUT_APIENTRY_DEFINED
#   if (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED)
#    define APIENTRY    __stdcall
#   else
#    define APIENTRY
#   endif
#  endif
   // XXX This is from Win32's <winnt.h>
#  ifndef CALLBACK
#   if (defined(_M_MRX000) || defined(_M_IX86) || defined(_M_ALPHA) || defined(_M_PPC)) && !defined(MIDL_PASS)
#    define CALLBACK __stdcall
#   else
#    define CALLBACK
#   endif
#  endif
   // XXX This is from Win32's <wingdi.h> and <winnt.h>
#  ifndef WINGDIAPI
#   define GLUT_WINGDIAPI_DEFINED
#   define WINGDIAPI __declspec(dllimport)
#  endif
   // XXX This is from Win32's <ctype.h>
#  ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#   define _WCHAR_T_DEFINED
#  endif
# endif
#endif



// gmlib::core
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


  /***********
   * Constants
   */
  const unsigned int GM_TEXTURE_1D = GL_TEXTURE_1D;
  const unsigned int GM_TEXTURE_2D = GL_TEXTURE_2D;

  const unsigned int GM_OBJECT_LINEAR = GL_OBJECT_LINEAR;
  const unsigned int GM_EYE_LINEAR = GL_EYE_LINEAR;
  const unsigned int GM_SPHERE_MAP = GL_SPHERE_MAP;



  struct GLVertex {
    GLfloat   x, y, z;
    GLfloat   nx, ny, nz;
    GLfloat   s1, t1;
  };

  inline
  GLuint getGLVertexPointOffset() {
    return 0;
  }

  inline
  GLuint getGLVertexNormalOffset() {
    return 3 * sizeof(GLfloat);
  }

  inline
  GLuint getGLVertexTexOffset1() {
    return 6 * sizeof(GLfloat);
  }

  inline
  void glColor(const Color& c) {

    glColor4ubv( c.getRgba() );
  }


  //*************************************************
  //********** overloaded Light functions ***********
  //*************************************************

  inline
  void glLight(GLenum li, GLenum pn, const Color& co) {

    float f[4];
    f[0] = float(co.getRedC());
    f[1] = float(co.getGreenC());
    f[2] = float(co.getBlueC());
    f[3] = float(co.getAlphaC());
    glLightfv(li,pn,f);
  }

  inline
  void glLightSun(GLenum li, const Point<float,3>& pos) {

    float f[4];
    f[0] = pos(0);
    f[1] = pos(1);
    f[2] = pos(2);
    f[3] = float(0.0);
    glLightfv(li,GL_POSITION,f);
  }

  inline
  void glLightPos(GLenum li, const Point<float,3>& pos) {

    float f[4];
    f[0] = pos(0);
    f[1] = pos(1);
    f[2] = pos(2);
    f[3] = float(1.0);
    glLightfv(li,GL_POSITION,f);
  }


  inline
  void glLightDir(GLenum li, const Vector<float,3>& dir) {

    float f[3];
    f[0] = dir(0);
    f[1] = dir(1);
    f[2] = dir(2);
    glLightfv(li,GL_SPOT_DIRECTION,f);
  }


  inline
  void glLight(GLenum li,GLenum pn, float f) {

    glLightf(li,pn,f);
  }

  inline
  void glLight(GLenum li,GLenum pn, int f) {

    glLighti(li,pn,f);
  }


  //***************************************************
  //********** overloaded glMaterial functions ********
  //***************************************************

  inline
  void glMaterial(GLenum li,GLenum pn, const Color& co) {

    float f[4];
    f[0] = float(co.getRedC());
    f[1] = float(co.getGreenC());
    f[2] = float(co.getBlueC());
    f[3] = float(co.getAlphaC());
    glMaterialfv(li,pn,f);
  }

  inline
  void glMaterial(GLenum li,GLenum pn, const Point<float,3>& co) {

    glMaterialfv(li,pn,(float*)(&co));
  }

  inline
  void glMaterial(GLenum li,GLenum pn, float f) {

    glMaterialf(li,pn,f);
  }

  inline
  void glMaterial(GLenum li,GLenum pn, int f) {

    glMateriali(li,pn,f);
  }

  //*************************************************
  //********** overloaded Transformation functions **
  //*************************************************

  //*************float******************
  inline
  void glScale(const Point<float,3>& p) {

    glScalef(p(0),p(1),p(2));
  }

  inline
  void glRotate(Angle a, const Vector<float,3>& p) {

    glRotatef(float(180*a.getRad()/M_PI),p(0),p(1),p(2));
  }

  inline
  void glTranslate(const Point<float,3>& p) {

    glTranslatef(p(0),p(1),p(2));
  }


  //**************double******************
  inline
  void glScale(const Point<double,3>& p) {

    glScaled(p(0),p(1),p(2));
  }

  inline
  void glRotate(Angle a, const Vector<double,3>& p) {

    glRotated(float(180*a.getRad()/M_PI),p(0),p(1),p(2));
  }

  inline
  void glTranslate(const Point<double,3>& p) {

    glTranslated(p(0),p(1),p(2));
  }


  //*************************************************
  //********** overloaded Matrix functions **********
  //*************************************************
//
//  inline
//  void glLoadMatrix(const GLMatrix& m)
//  {
//    glLoadMatrixf(m.getPtr());
//  }
//
//  inline
//  void glMultMatrix(const GLMatrix& m)
//  {
//    glMultMatrixf(m.getPtr());
//  }


  inline
  void glLoadMatrix(const HqMatrix<float,3>& m) {

    glLoadMatrixf(m.getTransposed().getPtr());
  }


  inline
  void glMultMatrix(const HqMatrix<float,3>& m) {

    glMultMatrixf(m.getTransposed().getPtr());
  }


  inline
  void glLoadMatrix(const HqMatrix<double,3>& m) {

    glLoadMatrixd(m.getTransposed().getPtr());
  }


  inline
  void glMultMatrix(const HqMatrix<double,3>& m) {

    glMultMatrixd(m.getTransposed().getPtr());
  }



  //********************************
  //********  DIMENSION  2 *********
  //********************************

  //*********************************************************
  //********** Point<double,2>:based gl-functions ***********
  //*********************************************************

  inline
  void glPoint(const Point<double,2>& p)
  {
    glVertex2dv((double *)&p);
  }

  inline
  void glPoint(Point<double,2>* p)
  {
    glVertex2dv((double *)p);
  }


  //*********************************************************
  //********** Point<float,2>:based gl-functions ************
  //*********************************************************

  inline
  void glPoint(const Point<float,2>& p)
  {
    glVertex2fv((float *)&p);
  }

  inline
  void glPoint(Point<float,2>* p)
  {
    glVertex2fv((float *)p);
  }

  inline
  void glTexCoord( float coord ) {
    glTexCoord1f( coord );
  }

  inline
  void glTexCoord(const Point<float,2>& p)
  {
    glTexCoord2fv((float *)&p);
  }

  //*********************************************************
  //********** Point<int,2>:based gl-functions **************
  //*********************************************************

  inline
  void glPoint(const Point<int,2>& p)
  {
    glVertex2iv((int *)&p);
  }

  inline
  void glPoint(Point<int,2>* p)
  {
    glVertex2iv((int *)p);
  }


  //*********************************************************
  //********** Point<short,2>:based gl-functions ************
  //*********************************************************

  inline
  void glPoint(const Point<short,2>& p)
  {
    glVertex2sv((short *)&p);
  }

  inline
  void glPoint(Point<short,2>* p)
  {
    glVertex2sv((short *)p);
  }




  //********************************
  //********  DIMENSION  3 *********
  //********************************

  //*********************************************************
  //********** Point<double,3>:based gl-functions ***********
  //*********************************************************

  inline
  void glPoint(const Point<double,3>& p)
  {
    glVertex3dv((double *)&p);
  }

  inline
  void glVector(const Vector<double,3>& p)
  {
    double a[4];
    memcpy(a, p.getPtr(),3);
    a[3] = 0;
    glVertex4dv(a);
  }

  inline
  void glNormal(const Vector<double,3>& v)
  {
    glNormal3dv((double *)&v);
  }

  inline
  void glVertex(const Arrow<double,3>& p)
  {
    glNormal3dv((double *)(p.getDir().getPtr()));
    glVertex3dv((double *)&p);
  }


  inline
  void glPoint(Point<double,3>* p)
  {
    glVertex3dv((double *)p);
  }

  inline
  void glVector(Vector<double,3>* p)
  {
    double a[4];
    memcpy(a,p,3);
    a[3] = 0;
    glVertex4dv(a);
  }

  inline
  void glNormal(Vector<double,3>* v)
  {
    glNormal3dv((double *)v);
  }

  inline
  void glVertex(Arrow<double,3>* p)
  {
    glNormal3dv((double *)(p->getDir().getPtr()));
    glVertex3dv((double *)p);

  }

  //*********************************************************
  //********** Point<float,3>:based gl-functions ************
  //*********************************************************

  inline
  void glPoint(const Point<float,3>& p)
  {
    glVertex3fv((float *)&p);
  }

  inline
  void glVector(const Vector<float,3>& p)
  {
    float a[4];
    memcpy(a,p.getPtr(),3);
    a[3] = 0;
    glVertex4fv(a);
  }

  inline
  void glNormal(const Vector<float,3>& v)
  {
    glNormal3fv((float *)&v);
  }

  inline
  void glVertex(const Arrow<float,3>& p)
  {
    glNormal3fv((float *)(p.getDir().getPtr()));
    glVertex3fv((float *)&p);
  }


  inline
  void glPoint(Point<float,3>* p)
  {
    glVertex3fv((float *)p);
  }

  inline
  void glVector(Vector<float,3>* p)
  {
    float a[4];
    memcpy(a,p,3);
    a[3] = 0;
    glVertex4fv(a);
  }

  inline
  void glNormal(Vector<float,3>* v)
  {
    glNormal3fv((float *)v);
  }

  inline
  void glVertex(Arrow<float,3>* p)
  {
    glNormal3fv((float *)(p->getDir().getPtr()));
    glVertex3fv((float *)p);
  }


  //*********************************************************
  //********** Point<int,3>:based gl-functions **************
  //*********************************************************

  inline
  void glPoint(const Point<int,3>& p)
  {
    glVertex3iv((int *)&p);
  }

  inline
  void glNormal(const Vector<int,3>& v)
  {
    glNormal3iv((int *)&v);
  }

  inline
  void glVertex(const Arrow<int,3>& p)
  {
    glNormal3iv((int *)(p.getDir().getPtr()));
    glVertex3iv((int *)&p);
  }


  inline
  void glPoint(Point<int,3>* p)
  {
    glVertex3iv((int *)p);
  }

  inline
  void glNormal(Vector<int,3>* v)
  {
    glNormal3iv((int *)v);
  }

  inline
  void glVertex(Arrow<int,3>* p)
  {
    glNormal3iv((int *)(p->getDir().getPtr()));
    glVertex3iv((int *)p);
  }


  //*********************************************************
  //********** Point<short,3>:based gl-functions ************
  //*********************************************************

  inline
  void glPoint(const Point<short,3>& p)
  {
    glVertex3sv((short *)&p);
  }

  inline
  void glNormal(const Vector<short,3>& v)
  {
    glNormal3sv((short *)&v);
  }

  inline
  void glVertex(const Arrow<short,3>& p)
  {
    glNormal3sv((short *)(p.getDir().getPtr()));
    glVertex3sv((short *)&p);
  }


  inline
  void glPoint(Point<short,3>* p)
  {
    glVertex3sv((short *)p);
  }

  inline
  void glNormal(Vector<short,3>* v)
  {
    glNormal3sv((short *)v);
  }

  inline
  void glVertex(Arrow<short,3>* p)
  {
    glNormal3sv((short *)(p->getDir().getPtr()));
    glVertex3sv((short *)p);
  }



  //********************************
  //********  DIMENSION  4 *********
  //********************************

  //*********************************************************
  //********** Point<double,4>:based gl-functions ***********
  //*********************************************************

  inline
  void glPoint(const Point<double,4>& p)
  {
    glVertex4dv((double *)&p);
  }

  inline
  void glPoint(Point<double,4>* p)
  {
    glVertex4dv((double *)p);
  }


  //*********************************************************
  //********** Point<float,4>:based gl-functions ************
  //*********************************************************

  inline
  void glPoint(const Point<float,4>& p)
  {
    glVertex4fv((float *)&p);
  }

  inline
  void glPoint(Point<float,4>* p)
  {
    glVertex4fv((float *)p);
  }


  //*********************************************************
  //********** Point<int,4>:based gl-functions **************
  //*********************************************************

  inline
  void glPoint(const Point<int,4>& p)
  {
    glVertex4iv((int *)&p);
  }

  inline
  void glPoint(Point<int,4>* p)
  {
    glVertex4iv((int *)p);
  }


  //*********************************************************
  //********** Point<short,4>:based gl-functions ************
  //*********************************************************

  inline
  void glPoint(const Point<short,4>& p)
  {
    glVertex4sv((short *)&p);
  }

  inline
  void glPoint(Point<short,4>* p)
  {
    glVertex4sv((short *)p);
  }


  // ***********
  // SwapBuffers

  void swapBuffers(void);


























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



    // FrameBufferObject
  public:

    struct FBOInfo {
      GLuint    id;
    };

    static bool                 bindFbo( const std::string& name );
    static bool                 createFbo( const std::string& name );
    static bool                 deleteFbo( const std::string& name );
    static GLuint               getFboId( const std::string& name );
    static const std::map< std::string, OGL::FBOInfo >    getFbos();
    static bool                 releaseFbo( const std::string& name );

  private:
    static std::map< std::string, OGL::FBOInfo >    _fbos;

    static bool                 _fboExists( const std::string& name, bool exist );





    // BufferObject
  public:

    struct BOInfo {
      GLuint    id;
      GLenum    target;
    };

    static bool                 bindBo( const std::string& name );
    static bool                 createBo( const std::string& name, GLenum target = GL_ARRAY_BUFFER );
    static bool                 deleteBo( const std::string& name );
    static GLuint               getBoId( const std::string& name );
    static GLenum               getBoTarget( const std::string& name );
    static const std::map< std::string, OGL::BOInfo >    getBos();
    static bool                 releaseBo( const std::string& name );
    static bool                 setBoTarget( const std::string& name, GLenum target = GL_ARRAY_BUFFER  );

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





  class GLFramebufferObject {
  public:
    GLFramebufferObject( const std::string name = "default" );
    GLFramebufferObject( const GLFramebufferObject& copy );
    ~GLFramebufferObject();

    void                  bind() const;
    GLuint                getId() const;
    std::string           getName() const;
    void                  release() const;

  protected:
    std::string           _name;
    GLuint                _id;

  }; // END class GLFrameBufferObject




  class GLBufferObject {
  public:
    GLBufferObject( const std::string name );
    GLBufferObject( const std::string name, GLenum type );
    GLBufferObject( const GLBufferObject& copy );
    ~GLBufferObject();

    void                  bind() const;
    void                  disableVertexArrayPointer( GLuint vert_loc );
    void                  enableVertexArrayPointer( GLuint vert_loc, int size, GLenum type, bool normalized, GLsizei stride, const void* offset );
    GLuint                getId() const;
    GLenum                getTarget() const;
    std::string           getName() const;
    void                  release() const;
    void                  setTarget( GLenum target = GL_ARRAY_BUFFER );

  protected:
    std::string           _name;
    GLuint                _id;
    GLenum                _target;

  }; // END class GLBufferObject


} // END namespace GMlib


#endif // __gmOPENGL_H__
