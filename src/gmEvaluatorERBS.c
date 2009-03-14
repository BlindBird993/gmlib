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



/*! \file gmEvaluatorERBS.c
 *
 *  EvaluatorERBS class function implementations
 *
 *  \date   2008-10-31
 */


namespace GMlib {

  template <typename T>
  inline
  EvaluatorERBS<T>::EvaluatorERBS( int m, double alpha, double beta, double gamma, double lambda ) {

    _der = 1;
		setCoefficients( alpha, beta, gamma, lambda );
		set();
		_init( m );
  }


  template <typename T>
  inline
  EvaluatorERBS<T>::~EvaluatorERBS() {}


  template <typename T>
  inline
  T EvaluatorERBS<T>::_getF2( T t ) {

		if( t == _lambda ||  t < 2.3e-308 || t == 1 )
      return T(0);


		T h = ( t-1 / (1+_gamma) ) * abs(t-_lambda) / ( t * (1-t) );
		if( t < _lambda )
      h -= T(1);
		else
      h += T(1);

		h *= -_scale * _alpha * _beta * (1+_gamma) / pow( t*pow( 1-t, _gamma ), _alpha );


		if( (1+_gamma)*_alpha < 1 ) {

			const T g = pow( abs(t-_lambda), 1-(1+_gamma)*_alpha ) / h;
			if( g < 2.3e-308 )
        return 0.0;
			else
        return 1 / g;
		}
		else if( (1+_gamma)*_alpha > 1 )
			return	h * pow( abs(t-_lambda), (1+_gamma)*_alpha-1 );
		else
			return	h;
	}


  template <typename T>
  inline
  T EvaluatorERBS<T>::_getIntegral( T a, T b, T sum, T eps ) {

		T t = b - a;

		T mat[16][16];
		mat[0][0] = sum * t;

    T s;
		int i,j, k;
		for( i = 1; i < 16; i++ ) {

			s = T(0);
			k = 1 << i;
			t /= 2.0;

			for( j = 1; j < k; j += 2 )
        s += _getPhi( a + t * j );

			mat[0][i] = t * ( sum += s );

			for (j=1; j<=i; j++) {

				b = 1 << (j << 1);
				mat[j][i-j] = ( b*mat[j-1][i-j+1] - mat[j-1][i-j] ) / (b-1.0);
			}

			if( abs( mat[i][0] - mat[i-1][0] ) < eps )
        return mat[i][0];
		}

		return mat[15][0];
  }


  template <typename T>
  inline
  T EvaluatorERBS<T>::_getPhi( T t ) {

		const T d = pow( t*pow( 1-t, _gamma ), _alpha );
		if( d < 2.3e-308 )
			return T(0);
		else
			return exp(
        -_beta * pow( abs(t-_lambda),
        _alpha * (1+_gamma) ) / d
      );
  }


  template <typename T>
  inline
  void EvaluatorERBS<T>::_init( int m ) {

		int i,j;
		T p0, p1;
		T f0, f1;

		_b.setDim(m+1);
		_a.setDim( m, 5 );
		_m    = m;
		_dt   = T(1) / m;
		_scale   = T(1);
		_b[0] = p0 = f0 = T(0);

    T t;
		for( i = 1; i < m; i++ ) {

			t = _dt * i;
			p1    = _getPhi(t);
			f1    = _getF2(t) * p1;
			_b[i] = _getIntegral( t-_dt, t, 0.5*(p0+p1), 1e-17 );

			_interpolate( i-1, p0, p1, _dt*f0, _dt*f1 );

			p0    = p1;
			f0    = f1;
		}

		_b[m] = _getIntegral( _dt*(m-1), 1, 0.5*p0, 1e-17 );
		_interpolate( m-1, p0, p1, _dt*f0, T(0) );

		for( i = 1; i <= m; i <<= 1 )
			for( j = m; j >= i; j -= 1 )
				_b[j] += _b[j-i];

		_scale = T(1)/_b[m];
  }


  template <typename T>
  inline
  void EvaluatorERBS<T>::_interpolate( int i, double p0, double p1, double f0, double f1 ) {

		_a[i][0] = p0;
		_a[i][1] = f0;
		_a[i][2] = 3 * (p1-p0) - 2*f0 - f1;
		_a[i][3] = -2*(p1-p0) + f0 + f1;
		_a[i][4] = (p0+p1)/2 + (f0-f1)/12;
  }


  template <typename T>
  inline
  void EvaluatorERBS<T>::_prepare( T t ) {

    // Translate/Scale the input paramter
		t  = ( t - _tk ) / _dtk;

		// Find the local interval
		_local   = min( int(t*_m), _m-1 );

		// Translate/Scale the local dt parameter
		_local_dt  = ( t - _local*_dt ) / _dt;
  }


  template <typename T>
  inline
  T EvaluatorERBS<T>::getDer( int i ) const {

		switch(i) {
		  case 1:
        return getDer1();

      case 2:
        return getDer2();
		}
  }


  template <typename T>
  inline
  T EvaluatorERBS<T>::getDer1() const {

    return _scale1 * (
      _a(_local)(0) + _local_dt * (
        _a(_local)(1) + _local_dt * (
          _a(_local)(2) + _local_dt * _a(_local)(3)
        )
      )
    );
  }


  template <typename T>
  inline
  T EvaluatorERBS<T>::getDer1( T t ) {

    _prepare( t );
    return getDer1();
  }


  template <typename T>
  inline
  T EvaluatorERBS<T>::getDer2() const {

    return _scale2 * (
      _a(_local)(1) + _local_dt * (
        2 * _a(_local)(2) + _local_dt *
          3 * _a(_local)(3)
      )
    );
  }


  template <typename T>
  inline
  T EvaluatorERBS<T>::getDer2( T t ) {

    _prepare( t );
    return getDer2();
  }


  template <typename T>
  inline
  T EvaluatorERBS<T>::getScale() const {

    return _scale;
  }


  template <typename T>
  inline
  void EvaluatorERBS<T>::set( T tk, T dtk ) {

		_tk = tk;
		_dtk = dtk;

		_scale1 = _scale / _dtk;
		_scale2 = _scale / ( _dt*_dtk*_dtk);
  }


  template <typename T>
  inline
  void EvaluatorERBS<T>::setCoefficients( double alpha, double beta, double gamma, double lambda ) {

    _alpha  = alpha;
    _beta   = beta;
    _gamma  = gamma;
    _lambda = lambda;
  }


  template <typename T>
  inline
  T EvaluatorERBS<T>::operator () ( T t ) {

    _prepare(t);

		if( _local_dt > 0.5 )
			return _scale * (
        _b[_local+1] - _dt * (
          _a[_local][4] - _local_dt * (
            _a[_local][0] + _local_dt * (
              _a[_local][1] / 2 + _local_dt * (
                _a[_local][2] / 3 + _local_dt * _a[_local][3]/4
              )
            )
          )
        )
      );
		else
			return _scale * (
        _b[_local] + _dt * _local_dt * (
          _a[_local][0] + _local_dt * (
            _a[_local][1]/2 + _local_dt * (
              _a[_local][2]/3 + _local_dt * _a[_local][3]/4
            )
          )
        )
      );
  }
}
