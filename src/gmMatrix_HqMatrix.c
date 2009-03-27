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



/*! \file gmMatrix_HqMatrix.c
 *
 *  File Description
 *
 *  \date   2008-07-14
 */

namespace GMlib {


  /*! HqMatrix<T, n>::HqMatrix():SqMatrix<T,n+1>()
   *  \brief The default constructor
   *
   *  The constructer gives an I-matrix
   */
  template <typename T, int n>
  inline
  HqMatrix<T, n>::HqMatrix():SqMatrix<T,n+1>()				{}


  /*! HqMatrix<T, n>::HqMatrix(bool i):SqMatrix<T,n+1>(i)
   *  \brief The fast constructor
   *
   *  The constructer gives random contents, there will be no initializing
   */
  template <typename T, int n>
  inline
  HqMatrix<T, n>::HqMatrix(bool i):SqMatrix<T,n+1>(i)			{}


  /*! HqMatrix<T, n>::HqMatrix(const Matrix<T,n+1,n+1>& v):SqMatrix<T,n+1>(v)
   *  \brief The copy constructor
   *
   *  The constructer gives a copy of the input (homogenious) matrix
   */
  template <typename T, int n>
  inline
  HqMatrix<T, n>::HqMatrix(const Matrix<T,n+1,n+1>& v):SqMatrix<T,n+1>(v)	{}


  /*! HqMatrix<T, n>::HqMatrix(const Matrix<T,n+1,n+1>& v, bool trans):SqMatrix<T,n+1>(v,trans)
   *  \brief The transpose copy constructor
   *
   *  The constructer gives a transposed copy of the input (homogenious) matrix if "trans" is true.
   */
  template <typename T, int n>
  inline
  HqMatrix<T, n>::HqMatrix(const Matrix<T,n+1,n+1>& v, bool trans):SqMatrix<T,n+1>(v,trans)	{}


  /*! HqMatrix<T, n>::HqMatrix(const Matrix<T,n,n>& v, bool trans=false):SqMatrix<T,n+1>(false)
   *  \brief The  copy or transpose copy constructor from a sub matrix.
   *
   *  The constructer gives a copy (or transposed copy if "trans" is true) of the
   *  input matrix in the upper left corner.
   *  The rightmost and lowermost vectors are set to 0 exept
   *  for the right lower corner value that is 1.
   */
  template <typename T, int n>
  inline
  HqMatrix<T, n>::HqMatrix( const Matrix<T,n,n>& v, bool trans=false) : SqMatrix<T,n+1>(false)	{}


  /*! HqMatrix<T, n>::HqMatrix(const Vector<T,n>& d)
   *  \brief The translation constructor
   *
   *  The constructer gives an homogenious translation matrix.
   */
  template <typename T, int n>
  inline
  HqMatrix<T, n>::HqMatrix( const Vector<T,n>& d  ){
    GM_Static2_<T,n,n+1>::eq2(d.ptr(),ptr()+n);
  }


  /*! HqMatrix<T, n>::HqMatrix(Angle a,  int x, int y)
   *  \brief The clean rotation constructor
   *
   *  The constructer gives a clean rotation matrix rotating in one
   *  of the main planes (x,y) around origin,
   *  i.e. the default (0,1) - is the xy-plane. Remark the for example (0,1) and (1,0)
   *  is rotation in opposit direction.
   */
  template <typename T, int n>
  inline
  HqMatrix<T, n>::HqMatrix(Angle a,  int x, int y){
    T sina = T(sin(a)), cosa = T(cos(a));
    (*this)[x][x]=cosa; (*this)[y][x]=-sina; (*this)[x][y]=sina; (*this)[y][y]=cosa;
  }


  /*! HqMatrix<T, n>::HqMatrix(Angle a, const Vector<T,n>& u, const Vector<T,n>& v)
   *  \brief The clean general rotation constructor
   *
   *  The constructer gives a rotation matrix rotating in the plane
   *  spanned by the two vectors u and v, but located in origin.
   */
  template <typename T, int n>
  inline
  HqMatrix<T, n>::HqMatrix(Angle a, const Vector<T,n>& u, const Vector<T,n>& v){
    makeOrtho(u, v, *this);
    Matrix<T,n+1,n+1> x(*this);
    rotateXY(a);
    basisChange(x);
  }


  /*! HqMatrix<T, n>::HqMatrix(Angle a, const Vector<T,n>& u, const Vector<T,n>& v, const Point<T,n>& p)
   *  \brief The general rotation constructor
   *
   *  The constructer gives a rotation matrix rotating in the plane
   *  spanned by the two vectors u and v and that is located in the point p.
   */
  template <typename T, int n>
  inline
  HqMatrix<T, n>::HqMatrix(Angle a, const Vector<T,n>& u, const Vector<T,n>& v, const Point<T,n>& p) {
    Vector<T,n> r;
    T sina = sin(a);
    T cosa = cos(a);
    makeOrtho(u, v, *this);
    SqMatrix<T,n+1> x(*this);
    GM_Static_<T,n>::rot_xy(getPtr(),getPtr()+(n+1), sina, cosa);
    basisChange(x);

    T x0 = GM_Static_<T,n>::dpr(p.getPtr(),x.getPtr());
    T x1 = GM_Static_<T,n>::dpr(p.getPtr(),x[1].getPtr());
    r[0] = (x0*cosa-x1*sina);
    r[1] = (x0*sina+x1*cosa);
    GM_Static_P_<T,n-2,n>::hq_2x(r.getPtr()+2,x[2].getPtr(),p);
    GM_Static_P_<T,n,n>::hq_3x(getPtr()+n,x.getPtr(),r,p.getPtr());
  }





  /*! Matrix<T,n+1,n+1>& HqMatrix<T, n>::setTranspose(const Matrix<T,n+1,n+1>& v)
   *  \brief
   *
   *
   */
  template <typename T, int n>
  inline
  Matrix<T,n+1,n+1>& HqMatrix<T, n>::setTranspose(const Matrix<T,n+1,n+1>& v) {
    cpy_t(v); return(*this);
  }





  /*! void HqMatrix<T, n>::rotateXY(Angle a, int x=0, int y=1)
   *  \brief Add a rotation to this matrix: (*this) = SqMatrix<T,n>(a,x,y)* (*this)
   *
   *  Add a rotation to this matrix: (*this) = SqMatrix<T,n>(a,x,y)* (*this)
   */
  template <typename T, int n>
  inline
  void HqMatrix<T, n>::rotateXY(Angle a, int x , int y ) {
    GM_Static_<T,n>::rot_xy(ptr()+x*(n+1),ptr()+y*(n+1), T(sin(a)), T(cos(a)));
  }


  /*! void HqMatrix<T, n>::rotate(Angle a, const Vector<T,n>& u, const Vector<T,n>& v)
   *  \brief Add a rotation to this matrix: (*this) = SqMatrix<T,n>(a,u,v)* (*this)
   *
   *  Add a rotation to this matrix: (*this) = SqMatrix<T,n>(a,u,v)* (*this)
   */
  template <typename T, int n>
  inline
  void HqMatrix<T, n>::rotate(Angle a, const Vector<T,n>& u, const Vector<T,n>& v){
    HqMatrix<T,n> x(a,u,v);
    *this = *this * x;
  }


  /*! HqMatrix<T, n>::rotate(Angle a, const Vector<T,n>& u, const Vector<T,n>& v, const Point<T,n>& p)
   *  \brief Add a rotation to this matrix: (*this) = SqMatrix<T,n>(a,u,v)* (*this)
   *
   *  Add a rotation to this matrix: (*this) = SqMatrix<T,n>(a,u,v)* (*this)
   */
  template <typename T, int n>
  inline
  void HqMatrix<T, n>::rotate(Angle a, const Vector<T,n>& u, const Vector<T,n>& v, const Point<T,n>& p){
    HqMatrix<T,n> x(a,u,v,p);
    *this = *this * x;
  }


  /*! void HqMatrix<T, n>::translate(const Vector<T,n> d)
   *  \brief Add a rotation to this matrix: (*this) = SqMatrix<T,n>(a,u,v)* (*this)
   *
   *  Add a rotation to this matrix: (*this) = SqMatrix<T,n>(a,u,v)* (*this)
   */
  template <typename T, int n>
  inline
  void HqMatrix<T, n>::translate(const Vector<T,n> d) {
    HqMatrix<T,n> m(d);
    (*this) = (*this)*m;
  }


  /*! void HqMatrix<T, n>::invert2()
   *  \brief Invert
   *
   *  overloaded and use only for orthonormal (n-1 x n-1) sub-matrices.
   *  Inverting this matrix using transposing the nxn upper-left submatrix)
   *  and making the right column equal - multiplication of the right column
   *  with the orginal sub-matrix
   *  NB!  ONLY ROTATION and TRANSLATION !!!!!!
   */
  template <typename T, int n>
  inline
  void HqMatrix<T, n>::invertOrthoNormal() {		// overloaded and use only for orthonormal (n-1 x n-1) sub-matrices (rotation matrices)
    T v[n];
    GM_Static3_<T,n,n>::eq1(v,ptr()+n);
    GM_Static3_<T,n-1,n+1>::trn(ptr()+n+1, ptr()+1);
    GM_Static3_<T,n,n>::cm_x(ptr()+n,ptr(),v);
  }




  /*! Matrix<T,n+1,n+1>& HqMatrix<T, n>::operator=(const Matrix<T,n+1,n+1>& v)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  Matrix<T,n+1,n+1>& HqMatrix<T, n>::operator=(const Matrix<T,n+1,n+1>& v) {
    cpy(v);
    return(*this);
  }


  /*! Point<T,n>		HqMatrix<T, n>::operator*(const Point<T,n>& v)		const
   *  \brief p =  T * q, where p and q are points
   *
   *  Returning a point: p =  T * q, where p and q are points i R^n
   *  and T is this matrix.
   */
  template <typename T, int n>
  inline
  Point<T,n>		HqMatrix<T, n>::operator*(const Point<T,n>& v)		const {
    Point<T,n> r;
    GM_Static_P_<T,n,n>::mv_xqP(r.getPtr(), getPtr(), p, getPtr()+n);
    return r;
  }


  /*! Vector<T,n>		HqMatrix<T, n>::operator*(const Vector<T,n>& v)		const
   *  \brief u =  T * v, where u and v are vectors
   *
   *  Returning a vector: u =  T * v, where u and v are vectors i R^n
   *  and T is this matrix. NB!! u is not infected by translation.
   */
  template <typename T, int n>
  inline
  Vector<T,n>		HqMatrix<T, n>::operator*(const Vector<T,n>& v)		const {
    Vector<T,n> r;
    GM_Static_P_<T,n,n>::mv_xq(r.getPtr(), getPtr(), v);
    return r;
  }


  /*! ScalarPoint<T,n> HqMatrix<T, n>::operator*(const ScalarPoint<T,n>& v)const
   *  \brief  Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  ScalarPoint<T,n> HqMatrix<T, n>::operator*(const ScalarPoint<T,n>& v) const {
    ScalarPoint<T,n> r
    GM_Static_P_<T,n,n>::mv_xq(r.getPtr(), getPtr(), p.getPos());
    return r;
  }


  /*! Sphere<T,n>		HqMatrix<T, n>::operator*(const Sphere<T,n>& v)		const
   *  \brief  Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  Sphere<T,n>		HqMatrix<T, n>::operator*(const Sphere<T,n>& v)		const{
    Sphere<T,n> r
    GM_Static_P_<T,n,n>::mv_xq(r.getPtr(), getPtr(), s.getPos());
    return r;
  }


  /*! Arrow<T,n>		HqMatrix<T, n>::operator*(const Arrow<T,n>& v)		const
   *  \brief  Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  Arrow<T,n>		HqMatrix<T, n>::operator*(const Arrow<T,n>& v)		const{
    Arrow<T,n> r;
    GM_Static_P_<T,n,n>::mv_xqP(r.getPtr(),  getPtr(), a.getPos(), getPtr()+n);
    GM_Static_P_<T,n,n>::mv_xq(r.getPtr()+n, getPtr(), a.getDir());
    return _r;
  }

  /*! Box<T,n>		HqMatrix<T, n>::operator*(const Box<T,n>& v)		const
   *  \brief  Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  Box<T,n>		HqMatrix<T, n>::operator*(const Box<T,n>& v)		const {
    Box<T,n> r;
    GM_Static_P_<T,n,n>::mv_xqP(r.getPtr(),   getPtr(), v.getPtr(),   getPtr()+n);
    GM_Static_P_<T,n,n>::mv_xqP(r.getPtr()+n, getPtr(), v.getPtr()+n, getPtr()+n);
    return _r;
  }


  /*! Matrix<T,n+1,n+1>const&	HqMatrix<T, n>::operator*(const HqMatrix<T,n>& v)	const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  Matrix<T,n+1,n+1>const&	HqMatrix<T, n>::operator*(const HqMatrix<T,n>& v)	const {
    return (*reinterpret_cast<Matrix<T,n+1,n+1>const*>(this)) *
      (reinterpret_cast<const Matrix<T,n+1,n+1>&>(v));
  }





  // **************************
  // Protected Member Functions


  /*! void HqMatrix<T, n>::hq_cpy(const Matrix<T,n,n>& v)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void HqMatrix<T, n>::hq_cpy(const Matrix<T,n,n>& v) {
    memcpy(getPtr(), v.getPtr(),sizeof(Matrix<T,n,m>));
  }


  /*! void HqMatrix<T, n>::hq_cpy_t(const Matrix<T,n,n>& v)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void HqMatrix<T, n>::hq_cpy_t(const Matrix<T,n,n>& v) {
    GM_Static_P_<T,n,n>::eq_t(getPtrP(),v.getPtr());
  }


  /*! void HqMatrix<T, n>::hq_cpy_r(const Point<T,n>& p,int i)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void HqMatrix<T, n>::hq_cpy_r(const Point<T,n>& p,int i) {
    memcpy((*this)[i].getPtr(),p.getPtr(),sizeof(Point<T,n>));
  }


  /*! void HqMatrix<T, n>::hq_cpy_c(const Point<T,n>& p,int j)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void HqMatrix<T, n>::hq_cpy_c(const Point<T,n>& p,int j) {
    GM_Static3_<T,n,n>::eq2(p.getPtr(),getPtr()+j);
  }


  /*! void HqMatrix<T, n>::makeOrtho(const Vector<T,n>& u, const Vector<T,n>& v, Matrix<T,n+1,n+1>& x)
   *  \brief To make an orthonormal set of basis-vectors using vector u and vector v as a start.
   *
   *  To make an orthonormal set of basis-vectors using vector u and vector v as a start.
   */
  template <typename T, int n>
  inline
  void HqMatrix<T, n>::makeOrtho(const Vector<T,n>& u, const Vector<T,n>& v, Matrix<T,n+1,n+1>& x) {
    int i,j,k,ku,kv;
    GM_Static_<T,n>::sc_r(x.ptr(), u.ptr(), (1/u.length()));
    x[0][n]=T(0);
    GM_Std_<T,n>::ortoNormal(x[1].ptr(),v.ptr(), x.ptr());
    x[1][n]=T(0);
    ku = u.maxAbsIndex();
    kv = x[1].maxAbsIndex();

    for(k=0,i=2; i<n; i++,k++)
    {
      if(k==ku) k++;
      if(k==kv)
      {
        k++;
        if(k==ku) k++;
      }
      x.initRow(i, k);
    }

    for(i=2;i<n;i++)
    {
      for(j=0; j<i; j++)
      {
        T tmp = GM_Static_<T,n>::dpr(x[i].ptr(),x[j].ptr());
        GM_Static_<T,n>::decomp(x[i].ptr(),x[j].ptr(),tmp);
      }
      x[i].normalize();
    }
    x.initRow(n,n);
  }

}
