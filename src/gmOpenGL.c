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



/*! \file gmOpenGL.c
 *  \brief OpenGL GMlib namespace functions
 *
 *  OpenGL GMlib namespace functions
 *
 *  \date   2008-08-03
 */


#include "gmGLColor.h"


namespace GMlib {


  inline
  void glColor(const GLColor& c) {

    c.glSet();
  }

  //*************************************************
  //********** overloaded Light functions ***********
  //*************************************************

  inline
  void glLight(GLenum li, GLenum pn, const GLColor& co) {

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
  void glMaterial(GLenum li,GLenum pn, const GLColor& co) {

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

  inline
  void glLoadMatrix(const GLMatrix& m)
  {
    glLoadMatrixf(m.getPtr());
  }

  inline
  void glMultMatrix(const GLMatrix& m)
  {
    glMultMatrixf(m.getPtr());
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


} // END namespace GMlib
