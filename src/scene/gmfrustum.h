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



/*! \file gmfrustum.h
 *
 *  Frustum class definitions
 */


#ifndef __GMFRUSTUM_H__
#define __GMFRUSTUM_H__

// gmlib
#include <core/types/gmpoint.h>
#include <core/types/gmmatrix.h>


namespace GMlib {


  /*! \class Frustum
   *  \brief  Pending Documentation
   *
   *  A class to describe a frutrum to a perspectiv or isometric view.
   */
  class Frustum {
  public:
    explicit Frustum();

    const Point<float,3>&         getRUBCorner() const;
    const Point<float,3>&         getLDFCorner() const;

    const Vector<float,3>&        getRightNormal() const;
    const Vector<float,3>&        getUpNormal() const;
    const Vector<float,3>&        getBackNormal() const;

    const Vector<float,3>&        getLeftNormal() const;
    const Vector<float,3>&        getDownNormal() const;
    const Vector<float,3>&        getFrontNormal() const;

    int                           isInterfering(const Sphere<float,3>& s) const;
    const HqMatrix<float,3>&      getProjectionMatrix() const;

//    const Point<float,3>&            getPos(int i) const;
//    const Vector<float,3>&           getNormal(int i) const;

  protected:
    Point<float,3>            _p[2];    // p[0]: høyre/opp/bak-hjørne  p[1]: venstre/ned/foran-hjørne
    Vector<float,3>           _v[6];    // normal: venstre, høyre, opp, ned, bak, fram.

    HqMatrix<float,3>         _matrix;  // Projection matrix
  };


  class PerspectiveFrustum : public Frustum {
  public:
    explicit PerspectiveFrustum( const HqMatrix<float,3>& m,
                                 const Point<float,3>& p,
                                 const Vector<float,3>& d,
                                 const Vector<float,3>& u,
                                 const Vector<float,3>& s,
                                 float nearplane,
                                 float farplane,
                                 float ratio,
                                 float angle_tan );

    void        set( const HqMatrix<float,3>& m,
                     const Point<float,3>& p,
                     const Vector<float,3>& d,
                     const Vector<float,3>& u,
                     const Vector<float,3>& s,
                     float nearplane,
                     float farplane,
                     float ratio,
                     float angle_tan );

  private:
    void        computeProjectionMatrix( float nearplane,
                                         float farplane,
                                         float ratio,
                                         float angle_tan );

  };

  class IsoFrustum : public Frustum {
  public:
    explicit IsoFrustum( const HqMatrix<float,3>& m,
                         const Point<float,3>& p,
                         const Vector<float,3>& d,
                         const Vector<float,3>& u,
                         const Vector<float,3>& s,
                         float nearplane,
                         float farplane,
                         float ratio,
                         float width );

    void        set( const HqMatrix<float,3>& m,
                     const Point<float,3>& p,
                     const Vector<float,3>& d,
                     const Vector<float,3>& u,
                     const Vector<float,3>& s,
                     float nearplane,
                     float farplane,
                     float ratio,
                     float width );

  private:
    void        computeProjectionMatrix( float nearplane,
                                         float farplane,
                                         float ratio,
                                         float width );

  };



















  inline
  Frustum::Frustum() {}

  inline
  const Point<float,3>&
  Frustum::getRUBCorner() const {

    return _p[0];
  }

  inline
  const Point<float,3>&
  Frustum::getLDFCorner() const {

    return _p[1];
  }

  inline
  const Vector<float,3>&
  Frustum::getLeftNormal() const {

    return _v[0];
  }

  inline
  const Vector<float,3>&
  Frustum::getRightNormal() const {

    return _v[1];
  }

  inline
  const Vector<float,3>&
  Frustum::getUpNormal() const {

    return _v[2];
  }

  inline
  const Vector<float,3>&
  Frustum::getDownNormal() const {

    return _v[3];
  }

  inline
  const Vector<float,3>&
  Frustum::getBackNormal() const {

    return _v[4];
  }

  inline
  const Vector<float,3>&
  Frustum::getFrontNormal() const {

    return _v[5];
  }

  inline
  int
  Frustum::isInterfering(const Sphere<float,3>& s) const {

    if(!s.isValid())  return -1;
    int ret = 1;

    Vector<float,3> d = s.getPos()-_p[0];
    float dv = d*_v[1];              // Høyre
    if(dv >= s.getRadius())    return -1;
    else if(dv > -s.getRadius())  ret = 0;
    dv = d*_v[2];                // Opp
    if(dv >= s.getRadius())    return -1;
    else if(dv > -s.getRadius())  ret = 0;
    dv = d*_v[4];                // Bak
    if(dv >= s.getRadius())    return -1;
    else if(dv > -s.getRadius())  ret = 0;

    d=s.getPos()-_p[1];
    dv = d*_v[0];                // Venstre
    if(dv >= s.getRadius())    return -1;
    else if(dv > -s.getRadius())  ret = 0;
    dv = d*_v[3];                // Ned
    if(dv >= s.getRadius())    return -1;
    else if(dv > -s.getRadius())  ret = 0;
    dv = d*_v[5];                // Fram
    if(dv >= s.getRadius())    return -1;
    else if(dv > -s.getRadius())  ret = 0;
    return ret;
  }

  inline
  const HqMatrix<float,3>&
  Frustum::getProjectionMatrix() const {

    return _matrix;
  }

  inline
  PerspectiveFrustum::PerspectiveFrustum( const HqMatrix<float,3>& m,
                                          const Point<float,3>& p,
                                          const Vector<float,3>& d,
                                          const Vector<float,3>& u,
                                          const Vector<float,3>& s,
                                          float nearplane, float farplane,
                                          float ratio, float angle_tan ) {

    set(m,p,d,u,s,nearplane,farplane,ratio,angle_tan);
  }

  inline
  void
  PerspectiveFrustum::set( const HqMatrix<float,3>& m,
                                const Point<float,3>& p,
                                const Vector<float,3>& d,
                                const Vector<float,3>& u,
                                const Vector<float,3>& s,
                                float nearplane, float farplane,
                                float ratio, float angle_tan ) {

    computeProjectionMatrix( nearplane, farplane, ratio, angle_tan );

    ratio *= angle_tan;
    double rr = sqrt(1+ratio*ratio);
    double tt = sqrt(1+angle_tan*angle_tan);
    Vector<float,3> f  = m*d;
    Vector<float,3> oe = m*u;
    Vector<float,3> ve = m*s;
    Vector<float,3> pp = ratio*ve-angle_tan*oe;
    _p[0] = m*p;      // Venstre, høyre, opp, ned (posisjon)
    _p[1] = _p[0]+farplane*(f+pp);
    _p[0] += nearplane*(f-pp);
    _v[0] = ve-ratio*f;      // Venstre  (normal)
    _v[1] = (_v[0]-2*ve)/rr;  // Høyre  (normal)
    _v[0] /= rr;
    _v[2] = oe-angle_tan*f;      // Opp    (normal)
    _v[3] = (_v[2]-2*oe)/tt;  // ned    (normal)
    _v[2] /= tt;
    _v[4] = -f;        // Bak    (normal)
    _v[5] = f;        // Fram    (normal)

  }

  inline
  void
  PerspectiveFrustum::computeProjectionMatrix( float nearplane,
                                               float farplane,
                                               float ratio,
                                               float angle_tan ) {

    float  hh = nearplane * angle_tan;
    float  rr = ratio*hh;

    float l, r, b, t, n, f;
    l = -rr;
    r = rr;
    b = -hh;
    t = hh;
    n = nearplane;
    f = farplane;

    float A, B, C, D;
    A =  ( r + l ) / ( r - l );
    B =  ( t + b ) / ( t - b );
    C = - ( f + n ) / ( f - n );
    D = - 2 * f * n / ( f - n );

    _matrix[0][0] = 2.0f / (r - l);
    _matrix[0][1] = 0.0f;
    _matrix[0][2] = A;
    _matrix[0][3] = 0.0f;

    _matrix[1][0] = 0.0f;
    _matrix[1][1] = 2.0f / ( t - b );
    _matrix[1][2] = B;
    _matrix[1][3] = 0.0f;

    _matrix[2][0] = 0.0f;
    _matrix[2][1] = 0.0f;
    _matrix[2][2] = C;
    _matrix[2][3] = D;

    _matrix[3][0] = 0.0f;
    _matrix[3][1] = 0.0f;
    _matrix[3][2] = -1.0f;
    _matrix[3][3] = 0.0f;

  }

  inline
  IsoFrustum::IsoFrustum( const HqMatrix<float,3>& m,
                          const Point<float,3>& p,
                          const Vector<float,3>& d,
                          const Vector<float,3>& u,
                          const Vector<float,3>& s,
                          float nearplane,
                          float farplane,
                          float ratio,
                          float width ) {

    set( m, p, d, u, s, nearplane,farplane,ratio, width );
  }

  inline
  void
  IsoFrustum::set( const HqMatrix<float,3>& m,
                        const Point<float,3>& p,
                        const Vector<float,3>& d,
                        const Vector<float,3>& u,
                        const Vector<float,3>& s,
                        float nearplane,
                        float farplane,
                        float ratio,
                        float width ) {

    Vector<float,3> f  = m*d;
    Vector<float,3> oe = m*u;
    Vector<float,3> ve = m*s;
    _p[0] = m*p;
    _p[1] = _p[0]+farplane*f+width*(ratio*ve-oe);
    _p[0] += nearplane*f-width*(ratio*ve-oe);
    _v[0] = ve;        // Venstre  (normal)
    _v[1] = -ve;        // Høyre  (normal)
    _v[2] = oe;        // Opp    (normal)
    _v[3] = -oe;        // ned    (normal)
    _v[4] = -f;        // Bak    (normal)
    _v[5] = f;        // Fram    (normal)
  }

  inline
  void
  IsoFrustum::computeProjectionMatrix( float nearplane,
                                       float farplane,
                                       float ratio,
                                       float width ) {

    float  hh = width;
    float  rr = ratio*width;

    float l, r, b, t, n, f;
    l = -rr;
    r = rr;
    b = -hh;
    t = hh;
    n = nearplane;
    f = farplane;

    float tx, ty, tz;
    tx = -(r+l)/(r-l);
    ty = -(t+b)/(t-b);
    tz = -(f+n)/(f-n);

    _matrix[0][0] = 2.0f / (r - l);
    _matrix[0][1] = 0.0f;
    _matrix[0][2] = 0.0f;
    _matrix[0][3] = tx;

    _matrix[1][0] = 0.0f;
    _matrix[1][1] = 2.0f / ( t - b );
    _matrix[1][2] = 0.0f;
    _matrix[1][3] = ty;

    _matrix[2][0] = 0.0f;
    _matrix[2][1] = 0.0f;
    _matrix[2][2] = (-2.0f)/(f-n);
    _matrix[2][3] = tz;

    _matrix[3][0] = 0.0f;
    _matrix[3][1] = 0.0f;
    _matrix[3][2] = 0.0f;
    _matrix[3][3] = 1.0f;
  }

} // END namespace GMlib


#endif // __GMFRUSTUM_H__
