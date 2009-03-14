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



/*! \file gmPSurf.h
 *
 *  Interface for the gmPSurf class.
 *
 *  \date   2008-07-17
 */

#ifndef __gmPSURF_H__
#define __gmPSURF_H__


// STL
#include <iostream>

// GMlib includes
#include "gmDMatrix.h"
#include "gmDSurf.h"
#include "gmParametrics.h"


namespace GMlib {


  /*! \class  PSurf gmPSurfe.h <PSurf>
   *  \brief  This is a numeric PSurf class
   *
   *  This is a numeric PSurf class. Tensor Product surface.
   */
  template <typename T, int n>
  class PSurf : public Parametrics<T,n> {
  public:
    PSurf( int s1 = 20, int s2 = 20 );
    PSurf( const PSurf<T,n>& c );

    virtual ~PSurf();


    //virtual void                  estimateClpPar( const Point<T,n>& p, T& u, T& v );
    DMatrix<Vector<T,n> >&	      evaluate( Point<T,2> p, int d );
    DMatrix<Vector<T,n> >&    	  evaluate( T u, T v, int d1, int d2 );
    DMatrix<Vector<T,n> >&    	  evaluateLocal( T u, T v, int d1, int d2 );
    DVector<Vector<T,n> >	        evaluateD( Point<T,2> p, int d );
    DVector<Vector<T,n> >	        evaluateD( T u, T v, int d1, int d2 );
//    virtual T                     getCurvatureGauss( T u, T v );
//    virtual T                     getCurvatureMean( T u, T v );
    int                           getDerU();
    Vector<T,n>&                  getDerU( T u, T v );
    int                           getDerV();
    Vector<T,n>&                  getDerV( T u, T v );
    Vector<T,n>&                  getDerUU( T u, T v );
    Vector<T,n>&                  getDerVV( T u, T v );
    Vector<T,n>&                  getDerUV( T u, T v );
    std::string                   getIdentity() const;
    virtual T                     getLocalMapping( T t, T ts, T tt, T te );
    Vector<T,n>&                  getNormal();
    T                             getParDeltaU();
    T                             getParDeltaV();
    T                             getParStartU();
    T                             getParStartV();
    T                             getParEndU();
    T                             getParEndV();
    int                           getSamU( int i = 0 );
    int                           getSamV( int i = 0 );
    virtual bool                  isClosedU() const = 0;
    virtual bool                  isClosedV() const = 0;

    virtual void                  resample(DMatrix<DMatrix <DMatrix <Vector<T,n> > > >	& a, int m1, int m2, int d1, int d2 );
    virtual void                  resample(DMatrix<DMatrix <Vector<T,n> > >& a, int m1, int m2, int d1, int d2, T s_u = T(0), T s_v = T(0), T e_u = T(0), T e_v = T(0));
    virtual void                  resampleNormals( const DMatrix<DMatrix<Vector<T, 3> > > &sample, DMatrix<Vector<T, 3> > &normals ) const;

    void                          setDomainU( T start, T end );
    void                          setDomainUScale( T sc );
    void                          setDomainUTrans( T tr );
    void                          setDomainV( T start, T end );
    void                          setDomainVScale( T sc );
    void                          setDomainVTrans( T tr );
    void                          setEval( int d );
    virtual PSurf<T,n>*           split( T t, int uv );

    Point<T,n>&                   operator () ( T u, T v );




  protected:
  friend class DSurf<T>;

    // ****************************
    // Storing samling informations

    // The sampling partition in u. Default first sampling value is
    // getStartParU() and last sampling value is usually getEndParU().
    DVector<T>			              _sam_p_u;

    // The sampling partition in v. Default first sampling value is
    // getStartParV() and last sampling value is usually getEndParV().
    DVector<T>			              _sam_p_v;

    // Samplings-number u directions for each partition.
    DVector<int>		              _sam1;

    // Samplings-number v directions for each partition.
    // NB! Invariant!! dim of _sam* = dim of _sam_p_* -1.
    DVector<int>		              _sam2;

    // Used by operator() for number of derivative to evaluate.
    int					                  _default_d;


    // *************************************
    // The result of the previous evaluation

    DMatrix< Vector<T,n> >        _p;		      // Position and belonging partial derivatives
    Vector<T,3>				            _n;		      // Surface normal, for display in 3D
    T						                  _u;		      // The parameter value in u-direction used for last evaluation
    T						                  _v;		      // The parameter value in v-direction used for last evaluation
    int						                _d1;		    // Number of derivatives in u-direction computed last time
    int						                _d2;		    // Number of derivatives in v-direction computed last time
    bool					                _diagonal;  // True if only upper left half of matrix is evaluated.


    // ******************
    // Shift of parameter
    T	                            _tr_u;		        // Translate u-parametre
    T	                            _sc_u;		        // Scale u-parametre

    T	                            _tr_v;		        // Translate v-parametre
    T	                            _sc_v;		        // Scale v-parametre


    virtual void                  eval( T u, T v, int d1, int d2, bool lu = true, bool lv = true ) = 0;
    virtual T                     getEndPU() = 0;
    virtual T                     getEndPV() = 0;
    virtual T                     getStartPU()  = 0;
    virtual T                     getStartPV()  = 0;
    T                             shiftU(T u);
    T	                            shiftV(T v);

  private:

    void                          _eval( T u, T v, int d1, int d2 );
    void                          _evalDerDD( DMatrix< DMatrix< Vector<T,n> > >& a, int d1, int d2, T du, T dv ) const;
    void                          _evalNormal();
    void                          _setSam( int m1, int m2 );
    int                           _sum( int i, int j );




  public:

    template <typename T_Stream>
    PSurf( T_Stream& in, int st ) {

      _d1 = -1; _d2 = -1;
      setEval(0);
      prIn(in);
    }


    template <typename T_Stream>
    T_Stream& prOut( T_Stream& out ) {

      out << _tr_u << GMseparator::Element << _sc_u << GMseparator::Element;
      out << _tr_v << GMseparator::Element << _sc_v << GMseparator::Element;
      out << _sam1 << GMseparator::Element << _sam2 << GMseparator::Element;
      //out << _default_material << GMseparator::Group;
      return out;
    }


    template <typename T_Stream>
    T_Stream& prIn( T_Stream& in ) {

      static Separator es(GMseparator::Element);
      static Separator gs(GMseparator::Group);
      in >> _tr_u >> es >> _sc_u >> es;
      in >> _tr_v >> es >> _sc_v >> es;
      in >> _sam1 >> es >> _sam2 >> es;
      //in >> _default_material >> gs;
      return in;
    }

    #ifdef GM_STREAM

      template <typename T_Stream>
      friend
      T_Stream& operator << ( T_Stream& out, PSurf<T,n>& s ) {

        return s.prOut(out);
      }


      template <typename T_Stream>
      friend
      T_Stream& operator>>( T_Stream& in,  PSurf<T,n>& s ) {

        return   s.prIn(in);
      }

    #endif

  }; // END PSurf

} // END namespace


// Including template definition file.
#include "gmPSurf.c"

#endif // __gmPSURF_H__


