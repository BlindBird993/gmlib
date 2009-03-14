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



/*! \file gmEvaluatorERBS.h
 *
 *  Interface for the EvaluatorERBS class.
 *
 *  \date   2008-10-31
 */

#ifndef __gmEVALUATRORERBS_H__
#define __gmEVALUATRORERBS_H__


#include <gmDMatrix>
#include <gmDVector>


namespace GMlib {


  template <typename T>
  class EvaluatorERBS {
  public:
    EvaluatorERBS( int m = 1024, double alpha = 1, double beta = 1, double gamma = 1, double lambda = 0.5 );
    EvaluatorERBS( const EvaluatorERBS<T>& eval );
    virtual ~EvaluatorERBS();

    T             getDer( int i ) const;
    T             getDer1() const;
    T             getDer1( T t );
    T             getDer2() const;
    T             getDer2( T t );
    T             getScale() const;


    void          set( T t = 0, T dt = 1 );
    void          setCoefficients( double alpha = 1, double beta = 1, double gamma = 1, double lambda = 0.5 );

    T             operator () ( T t );

  private:

    DMatrix<T>    _a;
    DVector<T>		_b;

    int           _m;

    int           _local;         //  j
    T             _local_dt;        //  dt
    T             _dt;              // _dt

    T             _tk;
    T             _dtk;

    int           _der;

    T             _scale;
    T             _scale1;
    T             _scale2;


    T		          _alpha;
    T             _beta;
    T             _gamma;
    T             _lambda;



    T             _getF2( T t );
    T             _getIntegral( T a, T b, T sum, T eps );
    T             _getPhi( T t );
    void          _init( int m );
    void          _interpolate( int i, double p0, double p1, double f0, double f1 );
    void          _prepare( T t );


  }; // END class EvaluatorERBS

} // END namespace GMlib

// Include EvaluatorERBS class function implementations
#include "gmEvaluatorERBS.c"

#endif // __gmEVALUATRORERBS_H__
