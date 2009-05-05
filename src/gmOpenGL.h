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



/*! \file gmOpenGL.h
 *
 *  GMlib interface to the OpenGL API
 *
 *  \date   2008-07-21
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



// STL includes
#include <iostream>
using namespace std;

// OpenGL and extionsion includes
//#define GM_GL_EXTENSION
#ifdef GM_GL_EXTENSION
  #ifdef _WIN32
    #include <GL/GLee.h>
  #endif
#endif


#ifndef __glee_h_
  #ifdef GM_GL_EXTENSION
    #define GL_GLEXT_PROTOTYPES
    #include <GL/gl.h>
    #include <GL/glext.h>
    #include <GL/glx.h>
    #include <GL/glxext.h>
  #else
    #include <GL/gl.h>
  #endif
#endif


#include <GL/glu.h>


// GMlib includes
#include "gmPoint.h"
#include "gmPoint2D.h"
#include "gmPoint3D.h"
#include "gmStream.h"

#include "gmMatrix.h"


namespace GMlib {


  /***********
   * Constants
   */
  const unsigned int GM_TEXTURE_1D = GL_TEXTURE_1D;
  const unsigned int GM_TEXTURE_2D = GL_TEXTURE_2D;

  const unsigned int GM_OBJECT_LINEAR = GL_OBJECT_LINEAR;
  const unsigned int GM_EYE_LINEAR = GL_EYE_LINEAR;
  const unsigned int GM_SPHERE_MAP = GL_SPHERE_MAP;






  /*! \var _I
   *  \brief The Identity Matrix
   *
   */
  static float _I[16] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};


  /*! \class GLMatrix
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  class GLMatrix {
  public:
    GLMatrix();
    GLMatrix(float* m);
    GLMatrix(const GLMatrix& m);
    GLMatrix(Angle a, const UnitVector<float,3>& r);
    GLMatrix(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d);
    GLMatrix(const Vector<float,3>& tr);

    void                basisChangeCam(
                          const Vector<float,3>& x,
                          const Vector<float,3>& y,
                          const Vector<float,3>& z,
                          const Vector<float,3>& p);

    void                basisChange(
                          const Vector<float,3>& x,
                          const Vector<float,3>& y,
                          const Vector<float,3>& z,
                          const Vector<float,3>& p);

    void                basisChangeInv(
                          const Vector<float,3>& x,
                          const Vector<float,3>& y,
                          const Vector<float,3>& z,
                          const Vector<float,3>& p);

    const float&      get(int i,int j) const;
    void                get(GLenum p);
    GLMatrix&           getInverse() const;
    GLMatrix&           getInverseOrtho() const;
    float*            getPtr() const;
    void                invert();
    void                invertOrtho();
    void                mult() const;
    GLMatrix&           multRev(const GLMatrix& m);
    void                put() const;
    void                reset();
    void                rotate( Angle a, const UnitVector<float,3>& d);
    void                rotate( Angle a, const Point<float,3>& p,const UnitVector<float,3>& d);
    void                rotateGlobal( Angle a, const Vector<float,3>& s);
    void                rotateGlobal( Angle a, const Point<float,3>& p,const UnitVector<float,3>& d);
    void                roundoff(int i=1000);
    void                scale( const Point<float,3>& s);
    void                scaleGlobal( const Point<float,3>& s);
    void                translate( const Point<float,3>& s);
    void                translateGlobal( const Point<float,3>& s);

    GLMatrix&           operator =  (float* m);
    GLMatrix&           operator =  (const GLMatrix& m);
    float&            operator () (int i,int j);
    GLMatrix&           operator *= (const GLMatrix& m);
    GLMatrix            operator *  (GLMatrix& m);
    Point<float,3>      operator *  (const Point<float,3>& p) const;
    Vector<float,3>     operator *  (const Vector<float,3>& p) const;
    Arrow<float,3>    operator *  (const Arrow<float,3>& b) const;
    Box<float,3>      operator *  (const Box<float,3>& b) const;
    Sphere<float,3>   operator *  (const Sphere<float,3>& b) const;
    bool                operator <  (const GLMatrix& m) const;


  private:
    float             _matrix[16];

    void                _cpy();
    void                _cpy( const float* m);
    void                _makeOrtho( const UnitVector<float,3>& d, Vector3D<float>& x, Vector3D<float>& y, Vector3D<float>& z);
    void                _mult( const GLMatrix& m1,const GLMatrix& m2);
    void                _mult2( GLMatrix& m1,const GLMatrix& m2) const;







  public:


    friend
    Point<float,3>& operator*=(Point<float,3>& p, const GLMatrix& m) {
      p = m*p;
      return p;
    }

    friend
    Vector<float,3>& operator*=(Vector<float,3>& p, const GLMatrix& m) {
      p = m*p;
      return p;
    }

    friend
    UnitVector<float,3>& operator*=(UnitVector<float,3>& p, const GLMatrix& m) {
      p = m * p;
      return p;
    }

    friend
    Arrow<float,3>& operator*=(Arrow<float,3>& p, const GLMatrix& m) {
      p = m*p; return p;
    }

    friend
    Box<float,3>& operator*=(Box<float,3>& p, const GLMatrix& m) {
      p = m*p; return p;
    }

    friend
    Sphere<float,3>& operator*=(Sphere<float,3>& p, const GLMatrix& m) {
      p = m*p; return p;
    }


    // *****************************
    // IOSTREAM overloaded operators

    #ifdef GM_STREAM

    template<class T_Stream>
    friend T_Stream& operator<<(T_Stream& out, const GLMatrix& mm) {

      float* m = mm.getPtr();
      out << m[0] << GMseparator::Element << m[4] << GMseparator::Element << m[8] << GMseparator::Element << m[12] << GMseparator::Group;
      out << m[1] << GMseparator::Element << m[5] << GMseparator::Element << m[9] << GMseparator::Element << m[13] << GMseparator::Group;
      out << m[2] << GMseparator::Element << m[6] << GMseparator::Element << m[10]<< GMseparator::Element << m[14] << GMseparator::Group;
      out << m[3] << GMseparator::Element << m[7] << GMseparator::Element << m[11]<< GMseparator::Element << m[15] << GMseparator::Group;
      return out;
    }


    template<class T_Stream>
    friend T_Stream& operator>>(T_Stream& in, GLMatrix& mm) {

      float* m = mm.getPtr();
      static Separator es(GMseparator::Element);
      static Separator gs(GMseparator::Group);

      in >> m[0] >> es >> m[4] >> es >> m[8] >> es >> m[12] >> gs;
      in >> m[1] >> es >> m[5] >> es >> m[9] >> es >> m[13] >> gs;
      in >> m[2] >> es >> m[6] >> es >> m[10]>> es >> m[14] >> gs;
      in >> m[3] >> es >> m[7] >> es >> m[11]>> es >> m[15] >> gs;
      return in;
    }


  private:
    istream& _printIn( istream& in );
    ostream& _printOut( ostream& out ) const;


  public:
    friend
    ostream& operator << ( ostream& out, const GLMatrix& v ) {

      return v._printOut( out );
    }

    friend
    ostream& operator << ( ostream& out, const GLMatrix* v ) {

      return v->_printOut( out );
    }

    friend
    istream& operator >> ( istream& in, GLMatrix& v ) {

      return v._printIn (in );
    }

    friend
    istream& operator >> ( istream& in, GLMatrix* v ) {

      return v->_printIn( in );
    }

    void print( char prompt[] = "GLMatrix", ostream & out = cout ) const;

    #endif

  }; // END class GLMatrix










  /*! \class Frustum
   *  \brief  Pending Documentation
   *
   *  A class to describe a frutrum to a perspectiv or isometric view.
   */
  class Frustum {
  public:
    Frustum();													          // Default constructor
    Frustum(
      const HqMatrix<float,3>& m,								// Standar perspective constructor
      const Point<float,3>& p,
      const Vector<float,3>& d,
      const Vector<float,3>& u,
      const Vector<float,3>& s,
      float angle_tan,
      float ratio,
      float nearplane,
      float farplane);

    Frustum(
      const HqMatrix<float,3>& m,								// Iso constructor constructor
      const Point<float,3>& p,
      float width,
      float ratio,
      const Vector<float,3>& d,
      const Vector<float,3>& u,
      const Vector<float,3>& s,
      float nearplane,
      float farplane);

    Frustum(const Frustum&  v);

    void              set(
                        const HqMatrix<float,3>& m,			// Perspective
                        const Point<float,3>& p,
                        const Vector<float,3>& d,
                        const Vector<float,3>& u,
                        const Vector<float,3>& s,
                        float angle_tan,
                        float ratio,
                        float nearplane,
                        float farplane);

    void              set(
                        const HqMatrix<float,3>& m,			// Iso
                        const Point<float,3>& p,
                        float width,
                        float ratio,
                        const Vector<float,3>& d,
                        const Vector<float,3>& u,
                        const Vector<float,3>& s,
                        float nearplane,
                        float farplane);

    Point<float,3>    getPos(int i) const;
    Vector<float,3>   getNormal(int i) const;

    int               isInterfering(const Sphere<float,3>& s) const;

  private:
    Point<float,3>	  _p[2];	// p[0]: høyre/opp/bak-hjørne  p[1]: venstre/ned/foran-hjørne
    Vector<float,3>   _v[6];	// normal: venstre, høyre, opp, ned, bak, fram.

  }; // END class Frustum











  /*! \class ScaleObj
   *  \brief Pending Documentation
   *
   *  Scaleing Object
   */
  class ScaleObj {
  public:
    ScaleObj();
    ScaleObj(float	s);
    ScaleObj(Point<float,3>	sc);

    float                   getMax() const;
    Point<float,3>const&    getScale();
    void                    glScaling();

    bool                    isActive()  const;

    void                    reset();
    void                    reset(const Point<float,3>& sc);
    void                    scale(const Point<float,3>& sc);
    Sphere<float,3>         scaleSphere(const Sphere<float,3>& sp) const;


  private:
    bool			              _scaled;
    Point<float,3>          _s;
    float			              _max;

    void                    _updateMax();


  #ifdef GM_STREAM
    public:
      template<class T_Stream>
      friend T_Stream& operator<<(T_Stream& out, const ScaleObj& v)
      {
        out << (int)v._scaled << GMseparator::Element << v._s << GMseparator::Element << v._max ;
        return out;
      }

      template<class T_Stream>
      friend T_Stream& operator>>(T_Stream& in, ScaleObj& v)
      {
        static Separator es(GMseparator::Element);
        //		GLubyte r,g,b,a;
        int scaled;
        in >> scaled >> es >> v._s >> es >> v._max;
        v._scaled = (bool)scaled;
        return in;
      }

  #endif

  }; // END class ScaleObj






} // END namespace GMlib



// Include GMlib namespace gmOpenGL function definitions/implementations
#include "gmOpenGL.c"

// Include inline GLMatrix implementations
#include "gmOpenGL_GLMatrix.c"

// Include inline Frustum class implementations
#include "gmOpenGL_Frustum.c"

// Include inline ScaleObj class implementations
#include "gmOpenGL_ScaleObj.c"






#endif // __gmOPENGL_H__
