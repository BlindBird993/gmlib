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



/*! \file gmDSurf.h
 *
 *  Interface for the gmDSurf class.
 *
 *  \date   2008-09-04
 */

#ifndef __gmDSURF_H__
#define __gmDSURF_H__


#include "gmArray.h"
#include "gmDParametrics.h"

namespace GMlib {

  template <typename T, int n>
  class PSurf;


  template <typename T>
  class DSurf : public DParametrics<T,2> {
  public:

    DSurf();
    DSurf( const DSurf<T>& copy );
    DSurf( const PSurf<T,3>& copy );
    DSurf( PSurf<T,3>* copy );


    DMatrix< Vector<T, 3> >   evaluate( T u, T v, int du, int dv );
    int                 getNoDerU() const;
    int                 getNoDerV() const;
    int                 getNoSampU() const;
    int                 getNoSampV() const;
    PSurf<T,3>*         getPSurf();
    virtual bool        isClosestPoint( const Point<T,3>& q, T& u, T& v );
    void                replot( int m1 = 0, int m2 = 0 , bool dynamic = false, int d1 = 1, int d2 = 1 );
    void                setPSurf( PSurf<T,3>* psurf );
    virtual void        setSurroundingSphere( const DMatrix< DMatrix< Vector<T, 3> > >& p );

  protected:

    PSurf<T, 3>         *_p_ref;

    int                 _no_der_u;
    int                 _no_der_v;

    int                 _no_samp_u;
    int                 _no_samp_v;

    void                localDisplay();
    void                localSelect();


  private:

    void                _init();

  };

}

// Include DSurf class function implementations
#include "gmDSurf.c"


#endif  //__gmDSURF_H__
