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



/*! \file gmstaticproc.c
 *  StaticProc implementations
 */

// stl
#include <cmath>
#include <algorithm>

namespace GMlib {



  ///////////////////////////////
  // template <typename T, int n>
  // class GM_Static_<T, n>::


  /*! T	GM_Static_<T, n>::dpr(T *a, T *b)
   *  \brief  a*b innerproduct
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  T	GM_Static_<T, n>::dpr(T *a, T *b) {
    return (*a) * (*b) + GM_Static_<T,n-1>::dpr(a+1,b+1);
  }


  /*! T	GM_Static_<T, n>::dprm(T *a, T *b)
   *  \brief  -a*b innerproduct
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  T	GM_Static_<T, n>::dprm(T *a, T *b) {
    return -(*a) * (*b) + GM_Static_<T,n-1>::dprm(a+1,b+1);
  }

  /*! void GM_Static_<T, n>::eq(T *a, const T& b)
   *  \brief  a =  b  set equal
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void GM_Static_<T, n>::eq(T *a, const T& b) {
    (*a) = b;
    GM_Static_<T,n-1>::eq(a+1,b);
  }

  /*! void GM_Static_<T, n>::eqm(T *a, T* b)
   *  \brief  a = -b
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void GM_Static_<T, n>::eqm(T *a, T* b) {
    (*a) = -(*b);
    GM_Static_<T,n-1>::eqm(a+1,b+1);
  }

  /*! void GM_Static_<T, n>::sc(T *a, double b)
   *  \brief  a *= b  scale
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void GM_Static_<T, n>::sc(T *a, double b) {
    (*a) *= b;
    GM_Static_<T,n-1>::sc(a+1,b);
  }

  /*! void GM_Static_<T, n>::sc_r(T *a, T *b, double c)
   *  \brief  a = b*c scale
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void GM_Static_<T, n>::sc_r(T *a, T *b, double c)	{
    (*a) = (*b)*c;
    GM_Static_<T,n-1>::sc_r(a+1,b+1,c);
  }

  /*! void GM_Static_<T, n>::peq(T *a, T *b)
   *  \brief  a += b
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void GM_Static_<T, n>::peq(T *a, T *b) {
    (*a) += (*b);
    GM_Static_<T,n-1>::peq(a+1,b+1);
  }

  /*! void GM_Static_<T, n>::meq(T *a, T *b)
   *  \brief  a -= b
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void GM_Static_<T, n>::meq(T *a, T *b) {
    (*a) -= (*b);
    GM_Static_<T,n-1>::meq(a+1,b+1);
  }

  /*! void GM_Static_<T, n>::xeq(T *a, T* b)
   *  \brief  a %= b
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void GM_Static_<T, n>::xeq(T *a, T* b) {
    (*a) *= (*b);
    GM_Static_<T,n-1>::xeq(a+1,b+1);
  }

  /*! void GM_Static_<T, n>::eq_p(T *a, T* b, T*c)
   *  \brief  a = b + c
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void GM_Static_<T, n>::eq_p(T *a, T* b, T*c) {
    (*a)=(*b)+(*c);
    GM_Static_<T,n-1>::eq_p(a+1,b+1,c+1);
  }

  /*! void GM_Static_<T, n>::eq_m(T *a, T* b, T*c)
   *  \brief  a = b - c
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void GM_Static_<T, n>::eq_m(T *a, T* b, T*c) {
    (*a)=(*b)-(*c);
    GM_Static_<T,n-1>::eq_m(a+1,b+1,c+1);
  }

  /*! void GM_Static_<T, n>::eq_x(T *a, T* b, T*c)
   *  \brief  a = b % c
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void GM_Static_<T, n>::eq_x(T *a, T* b, T*c) {
    (*a)=(*b)*(*c);
    GM_Static_<T,n-1>::eq_x(a+1,b+1,c+1);
  }

  /*! void GM_Static_<T, n>::rot_xy(T *a, T *b, const T& sa, const T& ca)
   *  \brief  Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void GM_Static_<T, n>::rot_xy(T *a, T *b, const T& sa, const T& ca) {
    T tmp=(*b)*sa+(*a)*ca;
    (*b)=(*b)*ca-(*a)*sa;
    (*a)=tmp;
    GM_Static_<T,n-1>::rot_xy(a+1,b+1,sa,ca);
  }

  /*! void GM_Static_<T, n>::decomp(T *a, T *b, const T& c)
   *  \brief  a -= c*b
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void GM_Static_<T, n>::decomp(T *a, T *b, const T& c)	{
    (*a) -= c * (*b);
    GM_Static_<T,n-1>::decomp(a+1,b+1,c);
  }

  /*! void GM_Static_<T, n>::normalizeHq(T *a, T *b, const T& c)
   *  \brief  Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void GM_Static_<T, n>::normalizeHq(T *a, T *b, const T& c) {
    T d = GM_Static_<T,n>::dpr(b,b);
    d = 1/d; GM_Static_<T,n>::sc_r(a,b,d);
    (*(a+n)) = c;
  }

  /*! int  GM_Static_<T, n>::maxIndex(T *a)
   *  \brief  Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  int  GM_Static_<T, n>::maxIndex(T *a) {
    int i=n;
    GM_Static_<T,n-1>::maxIdx(a+1,i);
    return n-i;
  }

  /*! void GM_Static_<T, n>::maxIdx(T *a, int& i)
   *  \brief  Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void GM_Static_<T, n>::maxIdx(T *a, int& i) {
    if( std::abs(*a) > std::abs(*(a+n-i))) i = n;
    GM_Static_<T,n-1>::maxIdx(a+1,i);
  }









  ///////////////////////////////
  // template <typename T>
  // class GM_Static_<T, 1>::





  /*! T GM_Static_<T, 1>::dpr(T *a, T *b)
   *  \brief a*b innerproduct
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  T GM_Static_<T, 1>::dpr(T *a, T *b) {
    return (*a) * (*b);
  }


  /*! T GM_Static_<T, 1>::dprm(T *a, T *b)
   *  \brief  a*b innerproduct
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  T GM_Static_<T, 1>::dprm(T *a, T *b) {
    return -(*a) * (*b);
  }


  /*! void GM_Static_<T, 1>::eq(T *a, const T& b)
   *  \brief  a =  b  set equal
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  void GM_Static_<T, 1>::eq(T *a, const T& b) {
    (*a) = b;
  }


  /*! void GM_Static_<T, 1>::eqm(T *a, T* b)
   *  \brief  a = -b
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  void GM_Static_<T, 1>::eqm(T *a, T* b) {
    (*a) = -(*b);
  }


  /*! void GM_Static_<T, 1>::sc(T *a, double b)
   *  \brief  a *= b  scale a with b
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  void GM_Static_<T, 1>::sc(T *a, double b) {
    (*a) *= b;
  }


  /*! void GM_Static_<T, 1>::sc_r(T *a, T *b, double c)
   *  \brief  a = b*c
   *
   *  scale b with c and put into a
   */
  template <typename T>
  inline
  void GM_Static_<T, 1>::sc_r(T *a, T *b, double c)	{
    (*a) = (*b)*c;
  }


  /*! void GM_Static_<T, 1>::peq(T *a, T *b)
   *  \brief  a += b
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  void GM_Static_<T, 1>::peq(T *a, T *b) {
    (*a) += (*b);
  }


  /*! void GM_Static_<T, 1>::meq(T *a, T *b)
   *  \brief  a -= b
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  void GM_Static_<T, 1>::meq(T *a, T *b) {
    (*a) -= (*b);
  }


  /*! void GM_Static_<T, 1>::xeq(T *a, T* b)
   *  \brief  a %= b
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  void GM_Static_<T, 1>::xeq(T *a, T* b) {
    (*a) *= (*b);
  }


  /*! void GM_Static_<T, 1>::eq_p(T *a, T* b, T*c)
   *  \brief  a = b + c
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  void GM_Static_<T, 1>::eq_p(T *a, T* b, T*c) {
    (*a)=(*b)+(*c);
  }


  /*! void GM_Static_<T, 1>::eq_m(T *a, T* b, T*c)
   *  \brief  a = b - c
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  void GM_Static_<T, 1>::eq_m(T *a, T* b, T*c) {
    (*a)=(*b)-(*c);
  }


  /*! void GM_Static_<T, 1>::eq_x(T *a, T* b, T*c)
   *  \brief  a = b % c
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  void GM_Static_<T, 1>::eq_x(T *a, T* b, T*c) {
    (*a)=(*b)*(*c);
  }


  /*! void GM_Static_<T, 1>::rot_xy(T *a, T *b, const T& sa, const T& ca)
   *  \brief  Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  void GM_Static_<T, 1>::rot_xy(T *a, T *b, const T& sa, const T& ca) {
    T tmp=(*b)*sa+(*a)*ca;
    (*b)=(*b)*ca-(*a)*sa;
    (*a)=tmp;
  }


  /*! void GM_Static_<T, 1>::decomp(T *a, T *b, const T& c)
   *  \brief  a -= c*b
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  void GM_Static_<T, 1>::decomp(T *a, T *b, const T& c)	{
    (*a) -= c * (*b);
  }


  /*! void GM_Static_<T, 1>::maxIdx(T *a, int& i)
   *  \brief  Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  void GM_Static_<T, 1>::maxIdx(T *a, int& i) {
    if(std::fabs(*a) > std::fabs(*(a+1-i))) i = 1;
  }

  ///////////////////////////////////////////
  // template <typename T, typename G, int n>
  // class GM_Static1_<T, G, n>::

  /*! void GM_Static1_<T, G, n>::eq(T *a, G* b)
   *  \brief a =  b  set equal
   *
   *  Pending Documentation
   */
  template <typename T, typename G, int n>
  inline
  void GM_Static1_<T, G, n>::eq(T *a, G* b) {
    (*a) = (T)(*b);
    GM_Static1_<T,G,n-1>::eq(a+1,b+1);
  }




  ////////////////////////////////////
  // template <typename T, typename G>
  // class GM_Static1_<T, G, 1>::

  /*! void GM_Static1_<T, G, 1>::eq(T *a, G* b)
   *  \brief a =  b  set equal b
   *
   *  Pending Documentation
   */
  template<typename T, typename G>
  void GM_Static1_<T, G, 1>::eq(T *a, G* b) {
    (*a) = (T)(*b);
  }

  ///////////////////////////////////////
  // template <typename T, int n, int m>
  // class GM_Static2_<T, n, m>::

  /*! T	GM_Static2_<T, n, m>::dpr(T *a, T *b)
   *  \brief a*b innerproduct (row x column) (n x m)
   *
   *  Pending Documentation
   */
  template <typename T, int n, int m>
  inline
  T	GM_Static2_<T, n, m>::dpr(T *a, T *b)	{
    return (*a)*(*b)+ GM_Static2_<T,n-1,m>::dpr(a+1,b+m);
  }


  /*! T	GM_Static2_<T, n, m>::dpc(T *a, T *b)
   *  \brief a*b innerproduct (column x column) (n x m)
   *
   *  Pending Documentation
   */
  template <typename T, int n, int m>
  inline
  T	GM_Static2_<T, n, m>::dpc(T *a, T *b)	{
    return (*a)*(*b)+ GM_Static2_<T,n-1,m>::dpc(a+m,b+m);
  }

  /*! void GM_Static2_<T, n, m>::eq1(T *a, T *b)
   *  \brief a = b  a-vector in n x m  matrix, b-column in m x n matrix
   *
   *  Pending Documentation
   */
  template <typename T, int n, int m>
  inline
  void GM_Static2_<T, n, m>::eq1(T *a, T *b) {
    (*a) = (*b);
    GM_Static2_<T,n-1,m>::eq1(a+1,b+m);
  }

  /*! void GM_Static2_<T, n, m>::eq2(T *a, T *b)
   *  \brief b = a  a-vector in n x m  matrix, b-column in m x n matrix
   *
   *  Pending Documentation
   */
  template <typename T, int n, int m>
  inline
  void GM_Static2_<T, n, m>::eq2(T *a, T *b) {
    (*b) = (*a);
    GM_Static2_<T,n-1,m>::eq2(a+1,b+m);
  }

  /*! void GM_Static2_<T, n, m>::eq3(T *a, T *b)
   *  \brief a = b  a-column in n x m  matrix, b-column in n x m matrix
   *
   *  Pending Documentation
   */
  template <typename T, int n, int m>
  inline
  void GM_Static2_<T, n, m>::eq3(T *a, T *b) {
    (*a) = (*b);
    GM_Static2_<T,n-1,m>::eq3(a+m,b+m);
  }

  /*! void GM_Static2_<T, n, m>::sc(T *a, double b)
   *  \brief a *= b scale column vector
   *
   *  Pending Documentation
   */
  template <typename T, int n, int m>
  inline
  void GM_Static2_<T, n, m>::sc(T *a, double b)	{
    (*a) *= b;	GM_Static2_<T,n-1,m>::sc(a+m,b);
  }

  /*! void GM_Static2_<T, n, m>::decomp(T *a, T* b)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n, int m>
  inline
  void GM_Static2_<T, n, m>::decomp(T *a, T* b) {
    T c = GM_Static_<T,m>::dpr(a,b);
    GM_Static_<T,m>::decomp(a,b,c);
    GM_Static2_<T,n-1,m>::decomp1(a,b+m,c);
  }

  /*! void GM_Static2_<T, n, m>::decomp1(T *a, T* b, T& c)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n, int m>
  inline
  void GM_Static2_<T, n, m>::decomp1(T *a, T* b, T& c) {
    c = GM_Static_<T,m>::dpr(a,b);
    GM_Static_<T,m>::decomp(a,b,c);
    GM_Static2_<T,n-1,m>::decomp1(a,b+m,c);
  }







  ///////////////////////////////////////
  // template <typename T, int m>
  // class GM_Static2_<T, 1, m>::

  /*! T	GM_Static2_<T, 1, m>::dpr(T *a, T *b)
   *  \brief a*b innerproduct (row x column) (n x m)
   *
   *  Pending Documentation
   */
  template <typename T, int m>
  inline
  T	GM_Static2_<T, 1, m>::dpr(T *a, T *b)	{
    return (*a) * (*b);
  }


  /*! T	GM_Static2_<T, 1, m>::dpc(T *a, T *b)
   *  \brief a*b innerproduct (column x column) (n x m)
   *
   *  Pending Documentation
   */
  template <typename T, int m>
  inline
  T	GM_Static2_<T, 1, m>::dpc(T *a, T *b)	{
    return (*a) * (*b);
  }


  /*! void GM_Static2_<T, 1, m>::eq1(T *a, T *b)
   *  \brief a = b  a-vector in n x m  matrix, b-column in transposed matrix
   *
   *  Pending Documentation
   */
  template <typename T, int m>
  inline
  void GM_Static2_<T, 1, m>::eq1(T *a, T *b) {
    (*a) = (*b);
  }


  /*! void GM_Static2_<T, 1, m>::eq2(T *a, T *b)
   *  \brief b = a  a-vector in n x m  matrix, b-column in transposed matrix
   *
   *  Pending Documentation
   */
  template <typename T, int m>
  inline
  void GM_Static2_<T, 1, m>::eq2(T *a, T *b) {
    (*b) = (*a);
  }


  /*! void GM_Static2_<T, 1, m>::eq3(T *a, T *b)
   *  \brief b = a  a-column in n x m  matrix, b-column in n x m matrix
   *
   *  Pending Documentation
   */
  template <typename T, int m>
  inline
  void GM_Static2_<T, 1, m>::eq3(T *a, T *b)	{
    (*a) = (*b);
  }


  /*! void GM_Static2_<T, 1, m>::sc(T *a, double b)
   *  \brief a *= b scale column vector
   *
   *  Pending Documentation
   */
  template <typename T, int m>
  inline
  void GM_Static2_<T, 1, m>::sc(T *a, double b)	{
    (*a) *= b;
  }


  /*! void GM_Static2_<T, 1, m>::decomp1(T *a, T* b, T& c)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int m>
  inline
  void GM_Static2_<T, 1, m>::decomp1(T *a, T* b, T& c) {
    c = GM_Static_<T,m>::dpr(a,b);
    GM_Static_<T,m>::decomp(a,b,c);
  }

  ///////////////////////////////////////
  // template <typename T, int n, int m>
  // class GM_Static3_<T, n, m>::

  /*! T	GM_Static3_<T, n, m>::dpr(T *a, T *b)
   *  \brief a*b innerproduct (row x column) (n x m)
   *
   *  Pending Documentation
   */
  template <typename T, int n, int m>
  inline
  T	GM_Static3_<T, n, m>::dpr(T *a, T *b)	{
    return (*a)*(*b)+ GM_Static3_<T,n-1,m>::dpr(a+1,b+m+1);
  }

  /*! void GM_Static3_<T, n, m>::eq1(T *a, T *b)
   *  \brief a = b  a-vector, b-diagonal in matrix
   *
   *  Pending Documentation
   */
  template <typename T, int n, int m>
  inline
  void GM_Static3_<T, n, m>::eq1(T *a, T *b) {
    (*a) = (*b);
    GM_Static3_<T,n-1,m>::eq1(a+1,b+m+1);
  }

  /*! void GM_Static3_<T, n, m>::eq2(T *a, T *b)
   *  \brief b = a  a-vector, b-diagonal in matrix
   *
   *  Pending Documentation
   */
  template <typename T, int n, int m>
  inline
  void GM_Static3_<T, n, m>::eq2(T *a, T *b) {
    (*b) = (*a);
    GM_Static3_<T,n-1,m>::eq2(a+1,b+m+1);
  }

  /*! void GM_Static3_<T, n, m>::eq3(T *a, T *b)
   *  \brief b = -a  a-vector, b-diagonal in matrix
   *
   *  Pending Documentation
   */
  template <typename T, int n, int m>
  inline
  void GM_Static3_<T, n, m>::eq3(T *a, T *b) {
    (*b) = -(*a);
    GM_Static3_<T,n-1,m>::eq3(a+1,b+m+1);
  }

  /*! void GM_Static3_<T, n, m>::sc(T *a, double b)
   *  \brief a *= b scale column vector
   *
   *  Pending Documentation
   */
  template <typename T, int n, int m>
  inline
  void GM_Static3_<T, n, m>::sc(T *a, double b)	{
    (*a) *= b;
    GM_Static2_<T,n-1,m>::sc(a+m+1,b);
  }

  /*! void GM_Static3_<T, n, m>::swp(T* a, T* b)
   *  \brief swap colomn a and line b
   *
   *  Pending Documentation
   */
  template <typename T, int n, int m>
  inline
  void GM_Static3_<T, n, m>::swp(T* a, T* b) {
    std::swap(*a,*b);
    GM_Static3_<T,n-1,m>::swp(a+m,b+1);
  }

  /*! void GM_Static3_<T, n, m>::trn(T* a, T* b)
   *  \brief // swap colomn a and line b
   *
   *  Pending Documentation
   */
  template <typename T, int n, int m>
  inline
  void GM_Static3_<T, n, m>::trn(T* a, T* b) {
    GM_Static3_<T,n,m>::swp(a,b);
    GM_Static3_<T,n-1,m>::trn(a+m+1,b+m+1);
  }

  /*! void GM_Static3_<T, n, m>::cm_x(T *a, T* b, T* c)
   *  \brief col = -mat x vec
   *
   *  Pending Documentation
   */
  template <typename T, int n, int m>
  inline
  void GM_Static3_<T, n, m>::cm_x(T *a, T* b, T* c)	{
    (*a) = -GM_Static_<T,m>::dpr(b,c);
    GM_Static3_<T,n-1,m>::cm_x(a+m+1,b+m+1,c);
  }

  /*! void GM_Static3_<T, n, m>::decomp(T *a, T* b)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n, int m>
  inline
  void GM_Static3_<T, n, m>::decomp(T *a, T* b) {
    T c = GM_Static_<T,m>::dpr(a,b);
    GM_Static_<T,m>::decomp(a,b,c);
    GM_Static2_<T,n-1,m>::decomp1(a,b+m+1,c);
  }

  /*! void GM_Static3_<T, n, m>::decomp1(T *a, T* b, T& c)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n, int m>
  inline
  void GM_Static3_<T, n, m>::decomp1(T *a, T* b, T& c) {
    c = GM_Static_<T,m>::dpr(a,b);
    GM_Static_<T,m>::decomp(a,b,c);
    GM_Static2_<T,n-1,m>::decomp1(a,b+m+1,c);
  }





  ///////////////////////////////////////
  // template <typename T, int m>
  // class GM_Static3_<T, 1, m>::


  /*! T	GM_Static3_<T, 1, m>::dpr(T *a, T *b)
   *  \brief a*b innerproduct (row x column) (n x m)
   *
   *  Pending Documentation
   */
  template <typename T, int m>
  inline
  T	GM_Static3_<T, 1, m>::dpr(T *a, T *b)	{
    return (*a) * (*b);
  }


  /*! void GM_Static3_<T, 1, m>::eq1(T *a, T *b)
   *  \brief a = b  a-vector, b-diagonal in matrix
   *
   *  Pending Documentation
   */
  template <typename T, int m>
  inline
  void GM_Static3_<T, 1, m>::eq1(T *a, T *b) {
    (*a) = (*b);
  }


  /*! void GM_Static3_<T, 1, m>::eq2(T *a, T *b)
   *  \brief b = a  a-vector, b-diagonal in matrix
   *
   *  Pending Documentation
   */
  template <typename T, int m>
  inline
  void GM_Static3_<T, 1, m>::eq2(T *a, T *b) {
    (*b) = (*a);
  }


  /*! void GM_Static3_<T, 1, m>::eq3(T *a, T *b)
   *  \brief b = a  a-vector, b-diagonal in matrix
   *
   *  Pending Documentation
   */
  template <typename T, int m>
  inline
  void GM_Static3_<T, 1, m>::eq3(T *a, T *b) {
    (*b) = -(*a);
  }


  /*! void GM_Static3_<T, 1, m>::sc(T *a, double b)
   *  \brief a *= b scale column vector
   *
   *  Pending Documentation
   */
  template <typename T, int m>
  inline
  void GM_Static3_<T, 1, m>::sc(T *a, double b)	{
    (*a) *= b;
  }


  /*! void GM_Static3_<T, 1, m>::swp(T* a, T* b)
   *  \brief swap colomn a and line b
   *
   *  Pending Documentation
   */
  template <typename T, int m>
  inline
  void GM_Static3_<T, 1, m>::swp(T* a, T* b) {
    std::swap(*a,*b);
  }


  /*! void GM_Static3_<T, 1, m>::trn(T* a, T* b)
   *  \brief swap colomn a and line b
   *
   *  Pending Documentation
   */
  template <typename T, int m>
  inline
  void GM_Static3_<T, 1, m>::trn(T* a, T* b) {
    std::swap(*a,*b);
  }


  /*! void GM_Static3_<T, 1, m>::cm_x(T *a, T* b, T* c)
   *  \brief col = -mat x vec
   *
   *  Pending Documentation
   */
  template <typename T, int m>
  inline
  void GM_Static3_<T, 1, m>::cm_x(T *a, T* b, T* c)	{
    (*a) = -GM_Static_<T,m>::dpr(b,c);
  }


  /*! void GM_Static3_<T, 1, m>::decomp1(T *a, T* b, T& c)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int m>
  inline
  void GM_Static3_<T, 1, m>::decomp1(T *a, T* b, T& c) {
    c = GM_Static_<T,m>::dpr(a,b);
    GM_Static_<T,m>::decomp(a,b,c);
  }

  ///////////////////////////////
  // template <typename T, int n>
  // class GM_Std_<T, n>::


  /*! void GM_Std_<T, n>::b_min_d_c( T *a, T* b, T* c, const T& d)
   *  \brief a = b - d*c,    a,b,c is n-dim vector, and d is scalar
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void GM_Std_<T, n>::b_min_d_c( T *a, T* b, T* c, const T& d) {
    (*a) = (*b) - d*(*c);
    GM_Std_<T,n-1>::b_min_d_c(a+1,b+1,c+1,d);
  }

  /*! void GM_Std_<T, n>::orto(T *a, T* b, T* c)
   *  \brief a = b - <b,c> c , where |c| = 1, and all are n-dim vectors
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void GM_Std_<T, n>::orto(T *a, T* b, T* c) {
    T d = GM_Static_<T,n>::dpr(b,c);
    GM_Std_<T,n>::b_min_d_c(a,b,c,d);
  }

  /*! void GM_Std_<T, n>::ortoNormal(T *a, T* b, T* c)
   *  \brief The same as abow, but normalizing the result 'a' after \see void GM_Std_<T, n>::orto(T *a, T* b, T* c)
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void GM_Std_<T, n>::ortoNormal(T *a, T* b, T* c) {
    GM_Std_<T,n>::orto(a,b,c);
    T d = GM_Static_<T,n>::dpr(a,a);
    GM_Static_<T,n>::sc(a,sqrt(1/d));
  }






  ////////////////////////
  // template <typename T>
  // class GM_Std_<T, 1>::

  /*! void GM_Std_<T, 1>b_min_d_c(T *a, T* b, T* c, const T& d)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  void GM_Std_<T, 1>::b_min_d_c(T *a, T* b, T* c, const T& d) {
    (*a) = (*b) - d*(*c);
  }


} //END namespace GMlib
