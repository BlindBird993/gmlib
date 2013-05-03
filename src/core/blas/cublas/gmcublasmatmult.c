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
 *  Implementation of CuBLAS-specific matrix multiplication operators.
 */

#include <cuda_runtime.h>
#include <cublas_v2.h>

namespace GMlib
{

inline
const DMatrix<float>&  operator*(const DMatrix<float>& m, const DMatrix<float>& b)
{
	static DMatrix<float> r;
	static Array<float> cA;
	static Array<float> cB;
	r.setDim(m.getDim1(), b.getDim2());
	cA.setSize(m.getDim1() * m.getDim2());
	cB.setSize(b.getDim1() * b.getDim2());
	for(int i=0; i<cA.getSize(); i++)
	{
		cA[i] = m(i%m.getDim1())(i/m.getDim1());
	}
	for(int i=0; i<cB.getSize(); i++)
	{
		cB[i] = b(i%b.getDim1())(i/b.getDim1());
	}

	static Array<float> work;
	work.setSize(m.getDim1() * b.getDim2());

	int devID = 0;
	cudaGetDevice(&devID);
	cudaDeviceProp deviceProp;
	cudaGetDeviceProperties(&deviceProp, devID);

	float* d_A;
	float* d_B;
	float* d_C;

	cudaMalloc((void**)&d_A, sizeof(float) * cA.getSize());
	cudaMalloc((void**)&d_B, sizeof(float) * cB.getSize());
	cudaMalloc((void**)&d_C, sizeof(float) * work.getSize());

	cudaMemcpy(d_A, cA.getPtr(), sizeof(float)*cA.getSize(), cudaMemcpyHostToDevice);
	cudaMemcpy(d_B, cB.getPtr(), sizeof(float)*cB.getSize(), cudaMemcpyHostToDevice);

	cublasHandle_t handle;
	cublasCreate(&handle);
	const float alpha = 1.0f;
	const float beta = 0.0f;

	cublasSgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N, m.getDim1(), b.getDim2(), m.getDim2(), &alpha, d_A, m.getDim1(), d_B, b.getDim1(), &beta, d_C, m.getDim1());

	cudaEvent_t stop;
	cudaEventCreate(&stop);
	cudaEventRecord(stop, NULL);
	cudaEventSynchronize(stop);

	cudaMemcpy(work.getPtr(), d_C, sizeof(float)*work.getSize(), cudaMemcpyDeviceToHost);

	cublasDestroy(handle);

	for(int i=0; i<r.getDim1(); i++)
		for(int j=0; j<r.getDim2(); j++)
			r[i][j]=(float) work[i+j*r.getDim1()];
			
	cudaFree(d_A);
	cudaFree(d_B);
	cudaFree(d_C);
	cudaDeviceReset();

	return r;
}

inline
const DMatrix<double>&  operator*(const DMatrix<double>& m, const DMatrix<double>& b)
{
	static DMatrix<double> r;
	static Array<double> cA;
	static Array<double> cB;
	r.setDim(m.getDim1(), b.getDim2());
	cA.setSize(m.getDim1() * m.getDim2());
	cB.setSize(b.getDim1() * b.getDim2());
	for(int i=0; i<cA.getSize(); i++)
	{
		cA[i] = m(i%m.getDim1())(i/m.getDim1());
	}
	for(int i=0; i<cB.getSize(); i++)
	{
		cB[i] = b(i%b.getDim1())(i/b.getDim1());
	}

	static Array<double> work;
	work.setSize(m.getDim1() * b.getDim2());

	int devID = 0;
	cudaGetDevice(&devID);
	cudaDeviceProp deviceProp;
	cudaGetDeviceProperties(&deviceProp, devID);

	double* d_A;
	double* d_B;
	double* d_C;

	cudaMalloc((void**)&d_A, sizeof(double) * cA.getSize());
	cudaMalloc((void**)&d_B, sizeof(double) * cB.getSize());
	cudaMalloc((void**)&d_C, sizeof(double) * work.getSize());

	cudaMemcpy(d_A, cA.getPtr(), sizeof(double)*cA.getSize(), cudaMemcpyHostToDevice);
	cudaMemcpy(d_B, cB.getPtr(), sizeof(double)*cB.getSize(), cudaMemcpyHostToDevice);

	cublasHandle_t handle;
	cublasCreate(&handle);
	const double alpha = 1.0f;
	const double beta = 0.0f;

	cublasDgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N, m.getDim1(), b.getDim2(), m.getDim2(), &alpha, d_A, m.getDim1(), d_B, b.getDim1(), &beta, d_C, m.getDim1());

	cudaEvent_t stop;
	cudaEventCreate(&stop);
	cudaEventRecord(stop, NULL);
	cudaEventSynchronize(stop);

	cudaMemcpy(work.getPtr(), d_C, sizeof(double)*work.getSize(), cudaMemcpyDeviceToHost);

	cublasDestroy(handle);

	for(int i=0; i<r.getDim1(); i++)
		for(int j=0; j<r.getDim2(); j++)
			r[i][j]=(double) work[i+j*r.getDim1()];
			
	cudaFree(d_A);
	cudaFree(d_B);
	cudaFree(d_C);
	cudaDeviceReset();

	return r;
}

inline
const DMatrix<std::complex<float> >&  operator*(const DMatrix<std::complex<float> >& m, const DMatrix<std::complex<float> >& b)
{
	static DMatrix<std::complex<float>> r;
	r.setDim(m.getDim1(), b.getDim2());

	int cA_size = m.getDim1() * m.getDim2();
	int cB_size = b.getDim1() * b.getDim2();
	int work_size = m.getDim1() * b.getDim2();
	std::complex<float>* cA = new std::complex<float>[cA_size];
	std::complex<float>* cB = new std::complex<float>[cB_size];
	std::complex<float>* work = new std::complex<float>[work_size];

	for(int i=0; i<cA_size; i++)
	{
		cA[i] = m(i%m.getDim1())(i/m.getDim1());
	}
	for(int i=0; i<cB_size; i++)
	{
		cB[i] = b(i%b.getDim1())(i/b.getDim1());
	}

	int devID = 0;
	cudaGetDevice(&devID);
	cudaDeviceProp deviceProp;
	cudaGetDeviceProperties(&deviceProp, devID);

	cuComplex* d_A;
	cuComplex* d_B;
	cuComplex* d_C;

	cudaMalloc((void**)&d_A, sizeof(std::complex<float>) * cA_size);
	cudaMalloc((void**)&d_B, sizeof(std::complex<float>) * cB_size);
	cudaMalloc((void**)&d_C, sizeof(std::complex<float>) * work_size);

	cudaMemcpy(d_A, cA, sizeof(std::complex<float>)*cA_size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_B, cB, sizeof(std::complex<float>)*cB_size, cudaMemcpyHostToDevice);

	cublasHandle_t handle;
	cublasCreate(&handle);
	static const cuComplex alpha = make_cuFloatComplex(1.0f, 0.0f);
	static const cuComplex beta = make_cuFloatComplex(0.0f, 0.0f);

	cublasCgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N, m.getDim1(), b.getDim2(), m.getDim2(), &alpha, d_A, m.getDim1(), d_B, b.getDim1(), &beta, d_C, m.getDim1());

	cudaEvent_t stop;
	cudaEventCreate(&stop);
	cudaEventRecord(stop, NULL);
	cudaEventSynchronize(stop);

	cudaMemcpy(work, d_C, sizeof(std::complex<float>)*work_size, cudaMemcpyDeviceToHost);

	cublasDestroy(handle);

	for(int i=0; i<r.getDim1(); i++)
		for(int j=0; j<r.getDim2(); j++)
			r[i][j] = work[i+j*r.getDim1()];
			
	cudaFree(d_A);
	cudaFree(d_B);
	cudaFree(d_C);
	cudaDeviceReset();

	delete[] cA;
	delete[] cB;
	delete[] work;

	return r;
}

inline
const DMatrix<std::complex<double> >&  operator*(const DMatrix<std::complex<double> >& m, const DMatrix<std::complex<double> >& b)
{
	static DMatrix<std::complex<double>> r;
	r.setDim(m.getDim1(), b.getDim2());

	int cA_size = m.getDim1() * m.getDim2();
	int cB_size = b.getDim1() * b.getDim2();
	int work_size = m.getDim1() * b.getDim2();
	std::complex<double>* cA = new std::complex<double>[cA_size];
	std::complex<double>* cB = new std::complex<double>[cB_size];
	std::complex<double>* work = new std::complex<double>[work_size];

	for(int i=0; i<cA_size; i++)
	{
		cA[i] = m(i%m.getDim1())(i/m.getDim1());
	}
	for(int i=0; i<cB_size; i++)
	{
		cB[i] = b(i%b.getDim1())(i/b.getDim1());
	}

	int devID = 0;
	cudaGetDevice(&devID);
	cudaDeviceProp deviceProp;
	cudaGetDeviceProperties(&deviceProp, devID);

	cuDoubleComplex* d_A;
	cuDoubleComplex* d_B;
	cuDoubleComplex* d_C;

	cudaMalloc((void**)&d_A, sizeof(std::complex<double>) * cA_size);
	cudaMalloc((void**)&d_B, sizeof(std::complex<double>) * cB_size);
	cudaMalloc((void**)&d_C, sizeof(std::complex<double>) * work_size);

	cudaMemcpy(d_A, cA, sizeof(std::complex<double>)*cA_size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_B, cB, sizeof(std::complex<double>)*cB_size, cudaMemcpyHostToDevice);

	cublasHandle_t handle;
	cublasCreate(&handle);
	static const cuDoubleComplex alpha = make_cuDoubleComplex(1.0, 0.0);
	static const cuDoubleComplex beta = make_cuDoubleComplex(0.0, 0.0);

	cublasZgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N, m.getDim1(), b.getDim2(), m.getDim2(), &alpha, d_A, m.getDim1(), d_B, b.getDim1(), &beta, d_C, m.getDim1());

	cudaEvent_t stop;
	cudaEventCreate(&stop);
	cudaEventRecord(stop, NULL);
	cudaEventSynchronize(stop);

	cudaMemcpy(work, d_C, sizeof(std::complex<double>)*work_size, cudaMemcpyDeviceToHost);

	cublasDestroy(handle);

	for(int i=0; i<r.getDim1(); i++)
		for(int j=0; j<r.getDim2(); j++)
			r[i][j] = work[i+j*r.getDim1()];
			
	cudaFree(d_A);
	cudaFree(d_B);
	cudaFree(d_C);
	cudaDeviceReset();

	delete[] cA;
	delete[] cB;
	delete[] work;

	return r;
}

} // namespace GMlib