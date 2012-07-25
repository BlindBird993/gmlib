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



/*! \file gmpoint3d.c
 *  File Description
 */



namespace GMlib {


  /*! Point3D<T>::Point3D(const T p[3])
   *  \brief  Default Constructor
   *
   *  Detailed description of
   *  the default constructor
   */
  template <typename T>
  inline
  Point3D<T>::Point3D(T d) : Point<T,3>(d) {
  }

  /*! Point3D<T>::Point3D(const T p[3])
   *  \brief  Default Constructor
   *
   *  Detailed description of
   *  the default constructor
   */
  template <typename T>
  inline
  Point3D<T>::Point3D(const T p[3]) : Point<T,3>(p) {
  }

  /*! Point3D<T>::Point3D(const Point<T,3>& v)
   *  \brief  Default Constructor
   *
   *  Detailed description of
   *  the default constructor
   */
  template <typename T>
  inline
  Point3D<T>::Point3D(const Point<T,3>& v) : Point<T,3>(v) {
  }

  /*! Point3D<T>::Point3D(const T& x,const T& y,const T& z)
   *  \brief  Default Constructor
   *
   *  Detailed description of
   *  the default constructor
   */
  template <typename T>
  inline
  Point3D<T>::Point3D(const T& x,const T& y,const T& z) {
    Point<T,3>::_pt[0]=x; Point<T,3>::_pt[1]=y; Point<T,3>::_pt[2]=z;
  }

  /*! Point<T,3> Point<T,3> ::operator^(const Point<T,3>& v)  const
   *  \brief  Vector product
   *
   *  Detailed description of
   *  the operator
   */
  template <typename T>
  inline
  Point<T,3> Point3D<T>::operator^(const Point<T,3>& v)  const {
    return Point3D<T>(
      this->_pt[1]*v(2) - this->_pt[2]*v(1),
      this->_pt[2]*v(0) - this->_pt[0]*v(2),
      this->_pt[0]*v(1) - this->_pt[1]*v(0)
    );
  }

  /*! Vector3D<T>::Vector3D(T d=1)
   *  \brief  Default Constructor
   *
   *  Detailed description of
   *  the default constructor
   */
  template <typename T>
  inline
  Vector3D<T>::Vector3D(T d) : Vector<T,3>(d) {}


  /*! Vector3D<T>::Vector3D(const Point<T,3>& v)
   *  \brief  Default Constructor
   *
   *  Detailed description of
   *  the default constructor
   */
  template <typename T>
  inline
  Vector3D<T>::Vector3D(const T p[3]) : Vector<T,2>(p) {}


  /*! Vector3D<T>::Vector3D(const Point<T,3>& v)
   *  \brief  Default Constructor
   *
   *  Detailed description of
   *  the default constructor
   */
  template <typename T>
  inline
  Vector3D<T>::Vector3D(const Point<T,3>& v) : Vector<T,3>(v) {}


  /*! Vector3D<T>::Vector3D(const T& x,const T& y,const T& z)
   *  \brief  Default Constructor
   *
   *  Detailed description of
   *  the default constructor
   */
  template <typename T>
  inline
  Vector3D<T>::Vector3D(const T& x,const T& y,const T& z) : Vector<T,3>(Point3D<T>(x,y,z)) {}


  /*! Point<T,3> Vector<T,3>::operator^(const Point<T,3>& v) const
   *  \brief  Vector product
   *
   *  Detailed description of
   *  the operator
   */
  template <typename T>
  inline
  Point<T,3> Vector3D<T>::operator^(const Point<T,3>& v) const {

    return Point3D<T>(
      this->_pt[1]*v(2) - this->_pt[2]*v(1),
      this->_pt[2]*v(0) - this->_pt[0]*v(2),
      this->_pt[0]*v(1) - this->_pt[1]*v(0)
    );
  }

  /*! UnitVector3D<T>:: UnitVector3D(T d=1)
   *  \brief  Default Constructor
   *
   *  Detailed description of
   *  the default constructor
   */
  template <typename T>
  inline
  UnitVector3D<T>::UnitVector3D(T d) : UnitVector<T,3>(d) {
  }

  /*! UnitVector3D<T>::UnitVector3D(const T p[3])
   *  \brief  Default Constructor
   *
   *  Detailed description of
   *  the default constructor
   */
  template <typename T>
  inline
  UnitVector3D<T>::UnitVector3D(const T p[3]) : UnitVector<T,2>(p) {
  }

  /*! UnitVector3D<T>::UnitVector3D(const Point<T,3>& v)
   *  \brief  Default Constructor
   *
   *  Detailed description of
   *  the default constructor
   */
  template <typename T>
  inline
  UnitVector3D<T>::UnitVector3D(const Point<T,3>& v) : UnitVector<T,3>(v) {
  }

  /*! UnitVector3D<T>::UnitVector3D(const T& x,const T& y,const T& z)
   *  \brief  Default Constructor
   *
   *  Detailed description of
   *  the default constructor
   */
  template <typename T>
  inline
  UnitVector3D<T>::UnitVector3D(const T& x,const T& y,const T& z) : UnitVector<T,3>(Point3D<T>(x,y,z)) {
  }

  /*! Point<T,3> UnitVector3D<T>::operator^(const Point<T,3>& v) const
   *  \brief  Vector product
   *
   *  Detailed description of
   *  the operator
   */
  template <typename T>
  inline
  Point<T,3> UnitVector3D<T>::operator^(const Point<T,3>& v) const {
    return Point3D<T>(
      Point<T,3>::_pt[1]*v(2) - Point<T,3>::_pt[2]*v(1),
      Point<T,3>::_pt[2]*v(0) - Point<T,3>::_pt[0]*v(2),
      Point<T,3>::_pt[0]*v(1) - Point<T,3>::_pt[1]*v(0)
    );
  }

  /*! Plane3D<T,n>:: Plane3D()
   *  \brief  Default Constructor
   *
   *  Detailed description of
   *  the default constructor
   */
  template <typename T, int n>
  inline
  Plane3D<T,n>::Plane3D() : Arrow<T,3>() {
  }

  /*! Plane3D<T,n>:: Plane3D()
   *  \brief  Default Constructor
   *
   *  Detailed description of
   *  the default constructor
   */
  template <typename T, int n>
  inline
  Plane3D<T,n>::Plane3D(const Point<T,3>& p) : Arrow<T,3>(p) {
  }

  /*! Plane3D<T,n>:: Plane3D()
   *  \brief  Default Constructor
   *
   *  Detailed description of
   *  the default constructor
   */
  template <typename T, int n>
  inline
  Plane3D<T,n>::Plane3D(const Point<T,3>& p ,const Vector<T,n>& v) : Arrow<T,3>(p,v) {
  }

  /*! Plane3D<T,n>:: Plane3D()
   *  \brief  Default Constructor
   *
   *  Detailed description of
   *  the default constructor
   */
  template <typename T, int n>
  inline
  Plane3D<T,n>::Plane3D(const Arrow<T,3>& a) : Arrow<T,3>(a) {
  }

  /*! void Plane3D<T,n>::setNormal(const Vector<T,3>& v)
   *  \brief  setNormal
   *
   *  Detailed description of
   *  the function
   */
  template <typename T, int n>
  inline
  void Plane3D<T,n>::setNormal(const Vector<T,3>& v) {
    setDir(v);
  }

  /*! const Vector<T,3>&	Plane3D<T,n>::getNormal()
   *  \brief  getNormal
   *
   *  \return normal
   *  Detailed description of
   *  the function
   */
  template <typename T, int n>
  inline
  const Vector<T,3>&	Plane3D<T,n>::getNormal() const {
    return Arrow<T, n>::getDir();
  }

  /*! Point<T,3> Plane3D<T,n>::getClosestPoint(const Point<T,3>& p) const
   *  \brief  getNormal
   *
   *  Detailed description of
   *  the function
   *
   *	\param[in] 	p
   *  \return 		closestPoint
   */
  template <typename T, int n>
  inline
  Point<T,3> Plane3D<T,n>::getClosestPoint(const Point<T,3>& p) const {

    Vector<T,3> d = p-Arrow<T, n>::getPos();
    return Arrow<T, n>::getPos()+d-(d*getNormal())*getNormal();
  }

  /*! Vector<T,3> Plane3D<T,n>::getDistanceVector(const Point<T,3>& p) const
   *  \brief  getDistanceVector
   *
   *  \return distanceVector
   *  Detailed description of
   *  the function
   */
  template <typename T, int n>
  inline
  Vector<T,3> Plane3D<T,n>::getDistanceVector(const Point<T,3>& p) const {

    Vector<T,3> d = p-Arrow<T,n>::getPos();
    return (d*getNormal())*getNormal();
  }

  /*! T Plane3D<T,n>::getDistanceTo(const Point<T,3>& p) const
   *  \brief  getDistanceTo
   *
   *  \return distanceTo
   *  Detailed description of
   *  the function
   */
  template <typename T, int n>
  inline
  T Plane3D<T,n>::getDistanceTo(const Point<T,3>& p) const {

    return (p-Arrow<T,n>::getPos())*getNormal();
  }

} // END namespace GMlib
