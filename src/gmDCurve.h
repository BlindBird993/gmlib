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



/*! \file gmDCurve.h
 *
 *  Interface for the gmDCurve class.
 *
 *  \date   2008-09-09
 */

#ifndef __gmDCURVE_H__
#define __gmDCURVE_H__


#include "gmArray.h"
#include "gmDParametrics.h"



namespace GMlib {

  template <typename T, int n>
  class PCurve;


  template <typename T>
  class DCurve : public DParametrics<T,1> {
  public:
    DCurve();
    DCurve( const DCurve<T>& copy );
    DCurve( const PCurve<T,3>& copy );
    DCurve( PCurve<T,3>* copy );


    float           getLineWidth() const;
    int             getNoDer() const;
    int             getNoSamp() const;
    PCurve<T,3>*    getPCurve();
    void            replot( int m = 0, bool dynamic = false, int d = 1 );
    void            setLineWidth( float width = 1.0 );
    void            setPCurve( PCurve<T,3>* pcurve );
    virtual void    setSurroundingSphere( const DVector< DVector< Vector<T, 3> > >& p );


  protected:
    PCurve<T, 3>    *_p_ref;
    int             _no_der;
    int             _no_samp;
    float           _line_width;
    void            localDisplay();
    void            localSelect();


  private:
    void            _init();

  };

}

// Include DSurf class function implementations
#include "gmDCurve.c"


#endif  //__gmDCURVE_H__

