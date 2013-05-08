/**********************************************************************************
**
** Copyright (C) 2013 Narvik University College
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



/*! \file gmmklmatmult.c
 *
 *  Implementation of MKL-specific matrix multiplication operators.
 */

#include <mkl.h>

namespace GMlib
{

inline
const DMatrix<float>&  operator*(const DMatrix<float>& m, const DMatrix<float>& b)
{
	static const char transpose = 'T';
	static const char noTranspose = 'N';
	static DMatrix<float> r;
	static Array<float> cA;
	static Array<float> cB;
	r.setDim(m.getDim1(), b.getDim2());
	cA.setSize(m.getDim1() * m.getDim2());
	cB.setSize(b.getDim1() * b.getDim2());

	for(int i=0; i<m.getDim1(); i++)
	{
		memcpy(&cA[i*m.getDim2()], &m(i)(0), m.getDim2()*sizeof(float));
	}
	for(int i=0; i<b.getDim1(); i++)
	{
		memcpy(&cB[i*b.getDim2()], &b(i)(0), b.getDim2()*sizeof(float));
	}

	static Array<float> work;
	work.setSize(m.getDim1() * b.getDim2());

	int M = m.getDim1();
	int N = b.getDim2();
	int K = m.getDim2();
	const float alpha = 1.0f;
	const float beta = 0.0f;
	sgemm(&transpose, &transpose, &M, &N, &K, &alpha, cA.getPtr(), &K, cB.getPtr(), &N, &beta, work.getPtr(), &M);

	for(int i=0; i<r.getDim1(); i++)
		for(int j=0; j<r.getDim2(); j++)
			r[i][j]=(float) work[i+j*r.getDim1()];

	return r;
}

inline
const DMatrix<double>&  operator*(const DMatrix<double>& m, const DMatrix<double>& b)
{
	static const char transpose = 'T';
	static const char noTranspose = 'N';
	static DMatrix<double> r;
	static Array<double> cA;
	static Array<double> cB;
	r.setDim(m.getDim1(), b.getDim2());
	cA.setSize(m.getDim1() * m.getDim2());
	cB.setSize(b.getDim1() * b.getDim2());

	for(int i=0; i<m.getDim1(); i++)
	{
		memcpy(&cA[i*m.getDim2()], &m(i)(0), m.getDim2()*sizeof(double));
	}
	for(int i=0; i<b.getDim1(); i++)
	{
		memcpy(&cB[i*b.getDim2()], &b(i)(0), b.getDim2()*sizeof(double));
	}

	static Array<double> work;
	work.setSize(m.getDim1() * b.getDim2());
	
	int M = m.getDim1();
	int N = b.getDim2();
	int K = m.getDim2();
	const double alpha = 1.0;
	const double beta = 0.0;
	dgemm(&transpose, &transpose, &M, &N, &K, &alpha, cA.getPtr(), &K, cB.getPtr(), &N, &beta, work.getPtr(), &M);

	for(int i=0; i<r.getDim1(); i++)
		for(int j=0; j<r.getDim2(); j++)
			r[i][j]=(double) work[i+j*r.getDim1()];

	return r;
}

inline
const DVector<float>&  operator*(const DMatrix<float>& m, const DVector<float>& b) {
	static DVector<float> r;

	if(m.getDim2() != b.getDim()) return r;

	r.setDim(m.getDim1());
	int n = m.getDim2();
	const float* vec = &b(0);
	for(int i=0;i<m.getDim1();i++)
	{
		static const int inc = 1;
		r[i] = sdot(&n, &m(i)(0), &inc, vec, &inc);
	}
	return r;
}

inline
const DVector<double>&  operator*(const DMatrix<double>& m, const DVector<double>& b) {
	static DVector<double> r;

	if(m.getDim2() != b.getDim()) return r;

	r.setDim(m.getDim1());
	int n = m.getDim2();
	const double* vec = &b(0);
	for(int i=0;i<m.getDim1();i++)
	{
		static const int inc = 1;
		r[i] = ddot(&n, &m(i)(0), &inc, vec, &inc);
	}
	return r;
}

inline
const DVector<std::complex<float> >&  operator*(const DMatrix<std::complex<float> >& m, const DVector<std::complex<float> >& b) {
	static DVector<std::complex<float> > r;

	if(m.getDim2() != b.getDim()) return r;

	r.setDim(m.getDim1());
	int n = m.getDim2();
	const MKL_Complex8* vec = reinterpret_cast<const MKL_Complex8*>(&b(0));
	for(int i=0;i<m.getDim1();i++)
	{
		static const int inc = 1;
		cdotu(reinterpret_cast<MKL_Complex8*>(&r[i]), &n, reinterpret_cast<const MKL_Complex8*>(&m(i)(0)), &inc, vec, &inc);
	}
	return r;
}

inline
const DVector<std::complex<double> >&  operator*(const DMatrix<std::complex<double> >& m, const DVector<std::complex<double> >& b) {
	static DVector<std::complex<double> > r;

	if(m.getDim2() != b.getDim()) return r;

	r.setDim(m.getDim1());
	int n = m.getDim2();
	const MKL_Complex16* vec = reinterpret_cast<const MKL_Complex16*>(&b(0));
	for(int i=0;i<m.getDim1();i++)
	{
		static const int inc = 1;
		zdotu(reinterpret_cast<MKL_Complex16*>(&r[i]), &n, reinterpret_cast<const MKL_Complex16*>(&m(i)(0)), &inc, vec, &inc);
	}
	return r;
}

inline
const DMatrix<std::complex<float> >&  operator*(const DMatrix<std::complex<float> >& m, const DMatrix<std::complex<float> >& b)
{
	static const char transpose = 'T';
	static const char noTranspose = 'N';
	static DMatrix<std::complex<float> > r;
	std::complex<float>* cA = new std::complex<float>[m.getDim1() * m.getDim2()];
	std::complex<float>* cB = new std::complex<float>[b.getDim1() * b.getDim2()];
	r.setDim(m.getDim1(), b.getDim2());

	for(int i=0; i<m.getDim1(); i++)
	{
		memcpy(&cA[i*m.getDim2()], &m(i)(0), m.getDim2()*sizeof(std::complex<float>));
	}
	for(int i=0; i<b.getDim1(); i++)
	{
		memcpy(&cB[i*b.getDim2()], &b(i)(0), b.getDim2()*sizeof(std::complex<float>));
	}

	std::complex<float>* work = new std::complex<float>[m.getDim1() * b.getDim2()];
	MKL_Complex8 alpha = {1.0f, 0.0f};
	MKL_Complex8 beta = {0.0f, 0.0f};
	const int m_ = m.getDim1();
	const int n_ = b.getDim2();
	const int k_ = m.getDim2();

	cgemm(&transpose, &transpose, &m_, &n_, &k_, &alpha, reinterpret_cast<MKL_Complex8*>(cA), &k_,
		reinterpret_cast<MKL_Complex8*>(cB), &n_, &beta, reinterpret_cast<MKL_Complex8*>(work), &m_);

	for(int i=0; i<r.getDim1(); i++)
		for(int j=0; j<r.getDim2(); j++)
			r[i][j] = work[i+j*r.getDim1()];
	delete[] cA;
	delete[] cB;
	delete[] work;
	return r;
}

inline
const DMatrix<std::complex<double> >&  operator*(const DMatrix<std::complex<double> >& m, const DMatrix<std::complex<double> >& b)
{
	static const char transpose = 'T';
	static const char noTranspose = 'N';
	static DMatrix<std::complex<double> > r;
	std::complex<double>* cA = new std::complex<double>[m.getDim1() * m.getDim2()];
	std::complex<double>* cB = new std::complex<double>[b.getDim1() * b.getDim2()];
	r.setDim(m.getDim1(), b.getDim2());

	for(int i=0; i<m.getDim1(); i++)
	{
		memcpy(&cA[i*m.getDim2()], &m(i)(0), m.getDim2()*sizeof(std::complex<double>));
	}
	for(int i=0; i<b.getDim1(); i++)
	{
		memcpy(&cB[i*b.getDim2()], &b(i)(0), b.getDim2()*sizeof(std::complex<double>));
	}

	std::complex<double>* work = new std::complex<double>[m.getDim1() * b.getDim2()];
	MKL_Complex16 alpha = {1.0, 0.0};
	MKL_Complex16 beta = {0.0, 0.0};
	const int m_ = m.getDim1();
	const int n_ = b.getDim2();
	const int k_ = m.getDim2();

	zgemm(&transpose, &transpose, &m_, &n_, &k_, &alpha, reinterpret_cast<MKL_Complex16*>(cA), &k_,
		reinterpret_cast<MKL_Complex16*>(cB), &n_, &beta, reinterpret_cast<MKL_Complex16*>(work), &m_);

	for(int i=0; i<r.getDim1(); i++)
		for(int j=0; j<r.getDim2(); j++)
			r[i][j] = work[i+j*r.getDim1()];
	delete[] cA;
	delete[] cB;
	delete[] work;
	return r;
}

} // namespace GMlib