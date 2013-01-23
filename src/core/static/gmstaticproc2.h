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



/*! \file gmstaticproc2.h
 *
 * gmstaticproc2.h: interface for the Static meta programming
 * to roll out the code usen in:
 * Matrix SqMatrix, HqMatrix classes.
 */

#ifndef __gmSTATICPROC2_H__
#define __gmSTATICPROC2_H__

#include "../types/gmpoint.h"

namespace GMlib {

  /*! \class  GM_Static_P_ gmstaticproc2.h <gmStaticProc2.h>
   *  \brief  For Matrices ( 2 dimentional)
   *
   *  Detailed Description of class
   */
  template <typename T, int n, int m>
  class GM_Static_P_ {
  public:
    static void mv_x(T *a, APoint<T,m>* b, const APoint<T,m>& c);		// vec = mat x vec
    static void mv_xq(T *a, T* b, const APoint<T,m>& c);				// vec = HqMat x vec
    static void mv_xqP(T *a, T* b, const APoint<T,m>& c, T* d);		// vec = HqMat x vec + h(homogen col)

    static void eq_t(APoint<T,m> *a, T *b);							// a = b^T	matrix transposeing
    static void sc(APoint<T,m>* a, T *b);							// scaling of matrix (row by row)
    static void vv_ox(APoint<T,m> *a, const APoint<T,m> *b, T *c);	// a = b x c tensor (outer) product

    static void cm_x(T *a, T* b, T* c);								// vec = col x mat
    static void mc_x(T *a, T *b, T *c);								// a = b(col)*c	matrix multiplication, but b is transposed

    static void   hq_2x(T *a, T* b, const APoint<T,m>& c);			// vec = HqMat x vec
    static void   hq_3x(T *a, T* b, const Vector<T,m>& r, T* p);	// col = vec - vec x HqMat

    //static APoint<T,m>& orto(const APoint<T,m>& a, APoint<T,m> *b)	// To orthogonalization of vectors
    //{ return GM_Static_<T,m>::dpr(a.ptr(),b->ptr())*(*b) + GM_Static_P_<T,n-1,m>::orto(a,b+1); }
  }; // END class GM_Static_P_


  /*! \class  GM_Static_P_ gmstaticproc2.h <gmStaticProc2.h>
   *  \brief  For Matrices ( 2 dimentional)
   *
   *  Detailed Description of class
   */
  template <typename T,int m>
  class GM_Static_P_<T,1,m> {
  public:
    static void mv_x(T *a, APoint<T,m>* b, const APoint<T,m>& c);
    static void mv_xq(T *a, T* b, const APoint<T,m>& c);
    static void mv_xqP(T *a, T* b, const APoint<T,m>& c, T* d);

    static void vv_ox(APoint<T,m> *a, const APoint<T,m> *b, T *c);

    static void cm_x(T *a, T* b, T* c);
    static void mc_x(T *a, T *b, T *c);

    static void sc(APoint<T,m>* a, T *b);

    static void hq_2x(T *a, T* b, const APoint<T,m>& c);
    static void hq_3x(T *a, T* b, const Vector<T,m>& r, T* p);

    //static APoint<T,m>& orto(const APoint<T,m>& a, APoint<T,m> *b) { return GM_Static_<T,m>::dpr(a.ptr(),b->ptr())*(*b); }
  }; // END class GM_Static_P_<T, 1, m> "Terminator"











  template <typename T, int n, int m>
  inline
  void v_eq_m_x_v(T *a, APoint<T,m>* b, const APoint<T,m>& c) {}


  /*! \class  GM_Static_P2_ gmstaticproc2.h <gmStaticProc2.h>
   *  \brief
   *
   *  Detailed Description of class
   */
  template <typename T, int n, int m, int k>
  class GM_Static_P2_ {
  public:
    static void vm_x(T *a, APoint<T,m>* b, T* c);					// vec = vec x mat
    static void vm_xHT(T *a, APoint<T,m+1>* b, T* c);				// vec =  mat x vec (a = c x b)
    static void vm_xH(T *a, APoint<T,m+1>* b, T* c);					// vec(a) = vec(c) x mat(b) (b homogen)
    static void vm_xT(T *a, APoint<T,m>* b, T* c);					// vec =  mat x vec (a = c x b)
    static void vm_xTT(T *a, T* b, T* c);							// a(vec) = b(col) x mat

    static void mm_xT(APoint<T,k> *a, APoint<T,m> *b, T *c);			// a = b*c	matrix multiplication (c transposed)
    static void mm_xTT(APoint<T,k> *a, T *b, T *c);					// a = b*c	matrix multiplication (b transposed)
    static void mm_xH(APoint<T,k> *a, APoint<T,m+1> *b, T *c);		// a = b*c	matrix multiplication (b homogen)
    static void mm_x(APoint<T,k> *a, APoint<T,m> *b, T *c);			// a = b*c	matrix multiplication
    static void mm_xHT(T *a, APoint<T,m+1> *b, T *c);				// a = b*c	matrix multiplication (c transposed)

    static void eq_t(APoint<T,m> *a, T *b);							// a = b^T	matrix transposeing (a = n x m)

  }; // END class GM_Static_P2_


  /*! \class  GM_Static_P2_ gmstaticproc2.h <gmStaticProc2.h>
   *  \brief
   *
   *  Detailed Description of class
   */
  template <class T, int m, int k>
  class GM_Static_P2_<T,1,m,k> {
  public:
    static void vm_x(T *a, APoint<T,m>* b, T* c);
    static void vm_xT(T *a, APoint<T,m>* b, T* c);
    static void vm_xTT(T *a, T* b, T* c);
    static void vm_xH(T *a, APoint<T,m+1>* b, T* c);
    static void vm_xHT(T *a, APoint<T,m+1>* b, T* c);

    static void mm_x(APoint<T,k> *a, APoint<T,m> *b, T *c);
    static void mm_xT(APoint<T,k> *a, APoint<T,m> *b, T *c);
    static void mm_xTT(APoint<T,k> *a, T *b, T *c);
    static void mm_xH(APoint<T,k> *a, APoint<T,m+1> *b, T *c);
    static void mm_xHT(T *a, APoint<T,m+1> *b, T *c);

  }; // END class GM_Static_P2_<T, 1, m, k> "Terminator"


  /*! \class  GM_Static_P2_ gmstaticproc2.h <gmStaticProc2.h>
   *  \brief  a = b^T	matrix transposeing
   *
   *  Detailed Description of class
   */
  template <class T, int n, int m>
  class GM_Static_P2_<T,n,m,1> {
  public:
    static void eq_t(APoint<T,m> *a, T *b);

  }; // END class GM_Static_P2_<T, n, m, 1> "Terminator"

} // END namespace GMlib



// Include implementations
#include "gmstaticproc2.c"




#endif   // GM_STATIC_PROC2_H_

