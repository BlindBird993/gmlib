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



/*! \file gmevaluatorstatic.c
 *
 *  EvaluatorStatic class function implementations
 */


namespace GMlib {

  template <typename T>
  void EvaluatorStatic<T>::evaluateBhp( DMatrix<T>& mat, int d, T t, T scale ) {

    // Initiate result matrix
    mat.setDim( d+1, d+1 );

    // Escape if no derivatives has to be computed
    if( d < 1 ) {

      mat[0][0] = T(1);
      return;
    }

    // Compute the Bernstein-Hermite polynomials 1 -> d.
    // One for each row, starting from the bottom up.
    mat[d-1][0] = 1 - t;
    mat[d-1][1] = t;


    for( int i = d-2; i >= 0; i-- ) {

      mat[i][0] = ( 1 - t) * mat[i+1][0];
      for( int j = 1; j < d - i; j++ )
        mat[i][j] = t * mat[i+1][j-1] + (1 - t) * mat[i+1][j];
      mat[i][d-i] = t * mat[i+1][d-i-1];
    }

    // Compute all the deriatives :P
    mat[d][0] = -scale;
    mat[d][1] = scale;

    for( int k = 2; k <= d; k++ ) {

      const double s = k * scale;
      for( int i = d; i > d - k; i-- ) {

        mat[i][k] = s * mat[i][k-1];
        for( int j = k - 1; j > 0; j-- )
          mat[i][j] = s * ( mat[i][j-1] - mat[i][j] );
        mat[i][0] = - s * mat[i][0];
      }
    }
  }

  template <typename T>
  void EvaluatorStatic<T>::evaluateHp( DMatrix<T>& mat, int d, T t) {

    mat.setDim( d+1, 4 );

    T t2 = t*t;
    T t3 = t*t2;

    // Compute the four Hermite polynomials (f_1, f_2, f'_1, f'_2)
    mat[0][1] = 3*t2 - 2*t3;
    mat[0][0] = 1 - mat[0][1];
    mat[0][2] = t - 2*t2 + t3;
    mat[0][3] = t3 - t2;
    if(d>0)   // First derivatives
    {
      mat[1][1] = 6*(t - t2);
      mat[1][0] = - mat[1][1];
      mat[1][2] = 1 - 4*t + 3*t2;
      mat[1][3] = 3*t2 - 2*t;
      if(d>1)  // Second derivatives
      {
        mat[2][1] = 6 - 12*t;
        mat[2][0] = - mat[2][1];
        mat[2][2] = - 4 + 6*t;
        mat[2][3] = 6*t - 2;
        if(d>2)  // Third derivatives
        {
          mat[3][1] = -12;
          mat[3][0] = 12;
          mat[3][2] = 6;
          mat[3][3] = 6;
        }
      }
    }
  }

} // END namespace GMlib
