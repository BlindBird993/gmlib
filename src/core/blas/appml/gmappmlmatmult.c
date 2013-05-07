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



/*! \file gmappmlmatmult.c
 *
 *  Implementation of APPML-specific matrix multiplication operators.
 */

#include "gmappmlmatmult.h"
#include <clAmdBlas.h>
#include <cstdio>

namespace GMlib
{

inline
const DMatrix<float>&  operator*(const DMatrix<float>& m, const DMatrix<float>& b)
{
	static DMatrix<float> r;
	r.setDim(m.getDim1(), b.getDim2());

	static Array<float> work;
	work.setSize(m.getDim1() * b.getDim2());

	cl_int err;
    cl_platform_id platform = 0;
    cl_device_id device = 0;
    cl_context_properties props[3] = { CL_CONTEXT_PLATFORM, 0, 0 };
    cl_context ctx = 0;
    cl_command_queue queue = 0;
    cl_event event = NULL;
    int ret = 0;

    /* Setup OpenCL environment. */
    err = clGetPlatformIDs(1, &platform, NULL);
    if (err != CL_SUCCESS) {
        printf( "clGetPlatformIDs() failed with %d\n", err );
        return r;
    }

    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
    if (err != CL_SUCCESS) {
        printf( "clGetDeviceIDs() failed with %d\n", err );
        return r;
    }

    props[1] = (cl_context_properties)platform;
    ctx = clCreateContext(props, 1, &device, NULL, NULL, &err);
    if (err != CL_SUCCESS) {
        printf( "clCreateContext() failed with %d\n", err );
        return r;
    }

    queue = clCreateCommandQueue(ctx, device, 0, &err);
    if (err != CL_SUCCESS) {
        printf( "clCreateCommandQueue() failed with %d\n", err );
        clReleaseContext(ctx);
        return r;
    }

    /* Setup clAmdBlas. */
    err = clAmdBlasSetup();
    if (err != CL_SUCCESS) {
        printf("clAmdBlasSetup() failed with %d\n", err);
        clReleaseCommandQueue(queue);
        clReleaseContext(ctx);
        return r;
    }

	cl_mem d_A = clCreateBuffer(ctx, CL_MEM_READ_ONLY, m.getDim1() * m.getDim2() * sizeof(float), NULL, &err);
	cl_mem d_B = clCreateBuffer(ctx, CL_MEM_READ_ONLY, b.getDim1() * b.getDim2() * sizeof(float), NULL, &err);
	cl_mem d_C = clCreateBuffer(ctx, CL_MEM_READ_WRITE, work.getSize() * sizeof(float), NULL, &err);
	
	for(int i=0; i<m.getDim1(); i++)
	{
		err = clEnqueueWriteBuffer(queue, d_A, CL_TRUE, i*m.getDim2()*sizeof(float), m(i).getDim()*sizeof(float), &m(i)(0), 0, NULL, NULL);
	}
	for(int i=0; i<b.getDim1(); i++)
	{
		err = clEnqueueWriteBuffer(queue, d_B, CL_TRUE, i*b.getDim2()*sizeof(float), b(i).getDim()*sizeof(float), &b(i)(0), 0, NULL, NULL);
	}
	
	err = clAmdBlasSgemm(clAmdBlasRowMajor, clAmdBlasNoTrans, clAmdBlasNoTrans, m.getDim1(), b.getDim2(), m.getDim2(), 1.0f,
		d_A, m.getDim2(), d_B, b.getDim2(), 0.0f, d_C, m.getDim2(), 1, &queue, 0, NULL, &event);

	if(err == CL_SUCCESS)
	{
		err = clWaitForEvents(1, &event);
		err = clEnqueueReadBuffer(queue, d_C, CL_TRUE, 0, work.getSize()*sizeof(float), work.getPtr(), 0, NULL, NULL);
	}

	clReleaseMemObject(d_C);
	clReleaseMemObject(d_B);
	clReleaseMemObject(d_A);

	clAmdBlasTeardown();

	clReleaseCommandQueue(queue);
	clReleaseContext(ctx);

	for(int i=0; i<r.getDim1(); i++)
		for(int j=0; j<r.getDim2(); j++)
			r[i][j] = work[i*r.getDim2()+j];
			
	return r;
}

inline
const DMatrix<double>&  operator*(const DMatrix<double>& m, const DMatrix<double>& b)
{
	static DMatrix<double> r;
	r.setDim(m.getDim1(), b.getDim2());

	static Array<double> work;
	work.setSize(m.getDim1() * b.getDim2());

	cl_int err;
    cl_platform_id platform = 0;
    cl_device_id device = 0;
    cl_context_properties props[3] = { CL_CONTEXT_PLATFORM, 0, 0 };
    cl_context ctx = 0;
    cl_command_queue queue = 0;
    cl_event event = NULL;
    int ret = 0;

    /* Setup OpenCL environment. */
    err = clGetPlatformIDs(1, &platform, NULL);
    if (err != CL_SUCCESS) {
        printf( "clGetPlatformIDs() failed with %d\n", err );
        return r;
    }

    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
    if (err != CL_SUCCESS) {
        printf( "clGetDeviceIDs() failed with %d\n", err );
        return r;
    }

    props[1] = (cl_context_properties)platform;
    ctx = clCreateContext(props, 1, &device, NULL, NULL, &err);
    if (err != CL_SUCCESS) {
        printf( "clCreateContext() failed with %d\n", err );
        return r;
    }

    queue = clCreateCommandQueue(ctx, device, 0, &err);
    if (err != CL_SUCCESS) {
        printf( "clCreateCommandQueue() failed with %d\n", err );
        clReleaseContext(ctx);
        return r;
    }

    /* Setup clAmdBlas. */
    err = clAmdBlasSetup();
    if (err != CL_SUCCESS) {
        printf("clAmdBlasSetup() failed with %d\n", err);
        clReleaseCommandQueue(queue);
        clReleaseContext(ctx);
        return r;
    }

	cl_mem d_A = clCreateBuffer(ctx, CL_MEM_READ_ONLY, m.getDim1() * m.getDim2() * sizeof(double), NULL, &err);
	cl_mem d_B = clCreateBuffer(ctx, CL_MEM_READ_ONLY, b.getDim1() * b.getDim2() * sizeof(double), NULL, &err);
	cl_mem d_C = clCreateBuffer(ctx, CL_MEM_READ_WRITE, work.getSize() * sizeof(double), NULL, &err);
	
	for(int i=0; i<m.getDim1(); i++)
	{
		err = clEnqueueWriteBuffer(queue, d_A, CL_TRUE, i*m.getDim2()*sizeof(double), m(i).getDim()*sizeof(double), &m(i)(0), 0, NULL, NULL);
	}
	for(int i=0; i<b.getDim1(); i++)
	{
		err = clEnqueueWriteBuffer(queue, d_B, CL_TRUE, i*b.getDim2()*sizeof(double), b(i).getDim()*sizeof(double), &b(i)(0), 0, NULL, NULL);
	}
	
	err = clAmdBlasDgemm(clAmdBlasRowMajor, clAmdBlasNoTrans, clAmdBlasNoTrans, m.getDim1(), b.getDim2(), m.getDim2(), 1.0,
		d_A, m.getDim2(), d_B, b.getDim2(), 0.0, d_C, m.getDim2(), 1, &queue, 0, NULL, &event);

	if(err == CL_SUCCESS)
	{
		err = clWaitForEvents(1, &event);
		err = clEnqueueReadBuffer(queue, d_C, CL_TRUE, 0, work.getSize()*sizeof(float), work.getPtr(), 0, NULL, NULL);
	}

	clReleaseMemObject(d_C);
	clReleaseMemObject(d_B);
	clReleaseMemObject(d_A);

	clAmdBlasTeardown();

	clReleaseCommandQueue(queue);
	clReleaseContext(ctx);

	for(int i=0; i<r.getDim1(); i++)
		for(int j=0; j<r.getDim2(); j++)
			r[i][j] = work[i*r.getDim2()+j];
			
	return r;
}

inline
const DMatrix<std::complex<float> >&  operator*(const DMatrix<std::complex<float> >& m, const DMatrix<std::complex<float> >& b)
{
	static DMatrix<std::complex<float> > r;
	int work_size = m.getDim1() * b.getDim2();

	r.setDim(m.getDim1(), b.getDim2());
	std::complex<float>* work = new std::complex<float>[work_size];

	cl_int err;
    cl_platform_id platform = 0;
    cl_device_id device = 0;
    cl_context_properties props[3] = { CL_CONTEXT_PLATFORM, 0, 0 };
    cl_context ctx = 0;
    cl_command_queue queue = 0;
    cl_event event = NULL;
    int ret = 0;

    /* Setup OpenCL environment. */
    err = clGetPlatformIDs(1, &platform, NULL);
    if (err != CL_SUCCESS) {
        printf( "clGetPlatformIDs() failed with %d\n", err );
        return r;
    }

    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
    if (err != CL_SUCCESS) {
        printf( "clGetDeviceIDs() failed with %d\n", err );
        return r;
    }

    props[1] = (cl_context_properties)platform;
    ctx = clCreateContext(props, 1, &device, NULL, NULL, &err);
    if (err != CL_SUCCESS) {
        printf( "clCreateContext() failed with %d\n", err );
        return r;
    }

    queue = clCreateCommandQueue(ctx, device, 0, &err);
    if (err != CL_SUCCESS) {
        printf( "clCreateCommandQueue() failed with %d\n", err );
        clReleaseContext(ctx);
        return r;
    }

    /* Setup clAmdBlas. */
    err = clAmdBlasSetup();
    if (err != CL_SUCCESS) {
        printf("clAmdBlasSetup() failed with %d\n", err);
        clReleaseCommandQueue(queue);
        clReleaseContext(ctx);
        return r;
    }

	cl_mem d_A = clCreateBuffer(ctx, CL_MEM_READ_ONLY, m.getDim1() * m.getDim2() * sizeof(std::complex<float>), NULL, &err);
	cl_mem d_B = clCreateBuffer(ctx, CL_MEM_READ_ONLY, b.getDim1() * b.getDim2() * sizeof(std::complex<float>), NULL, &err);
	cl_mem d_C = clCreateBuffer(ctx, CL_MEM_READ_WRITE, work_size * sizeof(std::complex<float>), NULL, &err);
	
	for(int i=0; i<m.getDim1(); i++)
	{
		err = clEnqueueWriteBuffer(queue, d_A, CL_TRUE, i*m.getDim2()*sizeof(std::complex<float>), m(i).getDim()*sizeof(std::complex<float>), &m(i)(0), 0, NULL, NULL);
	}
	for(int i=0; i<b.getDim1(); i++)
	{
		err = clEnqueueWriteBuffer(queue, d_B, CL_TRUE, i*b.getDim2()*sizeof(std::complex<float>), b(i).getDim()*sizeof(std::complex<float>), &b(i)(0), 0, NULL, NULL);
	}
	
	static const FloatComplex alpha = floatComplex(1.0f, 0.0f);
	static const FloatComplex beta = floatComplex(0.0f, 0.0f);

	err = clAmdBlasCgemm(clAmdBlasRowMajor, clAmdBlasNoTrans, clAmdBlasNoTrans, m.getDim1(), b.getDim2(), m.getDim2(), alpha,
		d_A, m.getDim2(), d_B, b.getDim2(), beta, d_C, m.getDim2(), 1, &queue, 0, NULL, &event);

	if(err == CL_SUCCESS)
	{
		err = clWaitForEvents(1, &event);
		err = clEnqueueReadBuffer(queue, d_C, CL_TRUE, 0, work_size*sizeof(std::complex<float>), work, 0, NULL, NULL);
	}

	clReleaseMemObject(d_C);
	clReleaseMemObject(d_B);
	clReleaseMemObject(d_A);

	clAmdBlasTeardown();

	clReleaseCommandQueue(queue);
	clReleaseContext(ctx);

	for(int i=0; i<r.getDim1(); i++)
		for(int j=0; j<r.getDim2(); j++)
			r[i][j] = work[i*r.getDim2()+j];

	delete[] work;
			
	return r;
}

inline
const DMatrix<std::complex<double> >&  operator*(const DMatrix<std::complex<double> >& m, const DMatrix<std::complex<double> >& b)
{
	static DMatrix<std::complex<double> > r;
	int work_size = m.getDim1() * b.getDim2();

	r.setDim(m.getDim1(), b.getDim2());
	std::complex<double>* work = new std::complex<double>[work_size];

	cl_int err;
    cl_platform_id platform = 0;
    cl_device_id device = 0;
    cl_context_properties props[3] = { CL_CONTEXT_PLATFORM, 0, 0 };
    cl_context ctx = 0;
    cl_command_queue queue = 0;
    cl_event event = NULL;
    int ret = 0;

    /* Setup OpenCL environment. */
    err = clGetPlatformIDs(1, &platform, NULL);
    if (err != CL_SUCCESS) {
        printf( "clGetPlatformIDs() failed with %d\n", err );
        return r;
    }

    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
    if (err != CL_SUCCESS) {
        printf( "clGetDeviceIDs() failed with %d\n", err );
        return r;
    }

    props[1] = (cl_context_properties)platform;
    ctx = clCreateContext(props, 1, &device, NULL, NULL, &err);
    if (err != CL_SUCCESS) {
        printf( "clCreateContext() failed with %d\n", err );
        return r;
    }

    queue = clCreateCommandQueue(ctx, device, 0, &err);
    if (err != CL_SUCCESS) {
        printf( "clCreateCommandQueue() failed with %d\n", err );
        clReleaseContext(ctx);
        return r;
    }

    /* Setup clAmdBlas. */
    err = clAmdBlasSetup();
    if (err != CL_SUCCESS) {
        printf("clAmdBlasSetup() failed with %d\n", err);
        clReleaseCommandQueue(queue);
        clReleaseContext(ctx);
        return r;
    }

	cl_mem d_A = clCreateBuffer(ctx, CL_MEM_READ_ONLY, m.getDim1() * m.getDim2() * sizeof(std::complex<double>), NULL, &err);
	cl_mem d_B = clCreateBuffer(ctx, CL_MEM_READ_ONLY, b.getDim1() * b.getDim2() * sizeof(std::complex<double>), NULL, &err);
	cl_mem d_C = clCreateBuffer(ctx, CL_MEM_READ_WRITE, work_size * sizeof(std::complex<double>), NULL, &err);
	
	for(int i=0; i<m.getDim1(); i++)
	{
		err = clEnqueueWriteBuffer(queue, d_A, CL_TRUE, i*m.getDim2()*sizeof(std::complex<double>), m(i).getDim()*sizeof(std::complex<double>), &m(i)(0), 0, NULL, NULL);
	}
	for(int i=0; i<b.getDim1(); i++)
	{
		err = clEnqueueWriteBuffer(queue, d_B, CL_TRUE, i*b.getDim2()*sizeof(std::complex<double>), b(i).getDim()*sizeof(std::complex<double>), &b(i)(0), 0, NULL, NULL);
	}
	
	static const DoubleComplex alpha = doubleComplex(1.0, 0.0);
	static const DoubleComplex beta = doubleComplex(0.0, 0.0);

	err = clAmdBlasZgemm(clAmdBlasRowMajor, clAmdBlasNoTrans, clAmdBlasNoTrans, m.getDim1(), b.getDim2(), m.getDim2(), alpha,
		d_A, m.getDim2(), d_B, b.getDim2(), beta, d_C, m.getDim2(), 1, &queue, 0, NULL, &event);

	if(err == CL_SUCCESS)
	{
		err = clWaitForEvents(1, &event);
		err = clEnqueueReadBuffer(queue, d_C, CL_TRUE, 0, work_size*sizeof(std::complex<double>), work, 0, NULL, NULL);
	}

	clReleaseMemObject(d_C);
	clReleaseMemObject(d_B);
	clReleaseMemObject(d_A);

	clAmdBlasTeardown();

	clReleaseCommandQueue(queue);
	clReleaseContext(ctx);

	for(int i=0; i<r.getDim1(); i++)
		for(int j=0; j<r.getDim2(); j++)
			r[i][j] = work[i*r.getDim2()+j];

	delete[] work;
			
	return r;
}

inline
const DVector<float>&  operator*(const DMatrix<float>& m, const DVector<float>& b)
{
	static DVector<float> r;
	r.setDim(m.getDim1());

	cl_int err;
    cl_platform_id platform = 0;
    cl_device_id device = 0;
    cl_context_properties props[3] = { CL_CONTEXT_PLATFORM, 0, 0 };
    cl_context ctx = 0;
    cl_command_queue queue = 0;
    cl_event event = NULL;
    int ret = 0;

    /* Setup OpenCL environment. */
    err = clGetPlatformIDs(1, &platform, NULL);
    if (err != CL_SUCCESS) {
        printf( "clGetPlatformIDs() failed with %d\n", err );
        return r;
    }

    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
    if (err != CL_SUCCESS) {
        printf( "clGetDeviceIDs() failed with %d\n", err );
        return r;
    }

    props[1] = (cl_context_properties)platform;
    ctx = clCreateContext(props, 1, &device, NULL, NULL, &err);
    if (err != CL_SUCCESS) {
        printf( "clCreateContext() failed with %d\n", err );
        return r;
    }

    queue = clCreateCommandQueue(ctx, device, 0, &err);
    if (err != CL_SUCCESS) {
        printf( "clCreateCommandQueue() failed with %d\n", err );
        clReleaseContext(ctx);
        return r;
    }

    /* Setup clAmdBlas. */
    err = clAmdBlasSetup();
    if (err != CL_SUCCESS) {
        printf("clAmdBlasSetup() failed with %d\n", err);
        clReleaseCommandQueue(queue);
        clReleaseContext(ctx);
        return r;
    }

	cl_mem d_A = clCreateBuffer(ctx, CL_MEM_READ_ONLY, m.getDim1() * m.getDim2() * sizeof(float), NULL, &err);
	cl_mem d_B = clCreateBuffer(ctx, CL_MEM_READ_ONLY, b.getDim() * sizeof(float), NULL, &err);
	cl_mem d_C = clCreateBuffer(ctx, CL_MEM_READ_WRITE, r.getDim() * sizeof(float), NULL, &err);

	for(int i=0; i<m.getDim1(); i++)
	{
		err = clEnqueueWriteBuffer(queue, d_A, CL_TRUE, i*m.getDim2()*sizeof(float), m(i).getDim()*sizeof(float), &m(i)(0), 0, NULL, NULL);
	}

	err = clEnqueueWriteBuffer(queue, d_B, CL_TRUE, 0, b.getDim()*sizeof(float), &b(0), 0, NULL, NULL);

	err = clAmdBlasSgemv(clAmdBlasRowMajor, clAmdBlasNoTrans, m.getDim2(), b.getDim(), 1.0f, d_A, m.getDim1(), d_B, 0,
		1, 0.0f, d_C, 0, 1, 1, &queue, 0, NULL, &event);

	if(err == CL_SUCCESS)
	{
		err = clWaitForEvents(1, &event);
		err = clEnqueueReadBuffer(queue, d_C, CL_TRUE, 0, r.getDim()*sizeof(float), &r[0], 0, NULL, NULL);
	}
	
	clReleaseMemObject(d_C);
	clReleaseMemObject(d_B);
	clReleaseMemObject(d_A);

	clAmdBlasTeardown();

	clReleaseCommandQueue(queue);
	clReleaseContext(ctx);
			
	return r;
}

inline
const DVector<double>&  operator*(const DMatrix<double>& m, const DVector<double>& b)
{
	static DVector<double> r;
	r.setDim(m.getDim1());

	cl_int err;
    cl_platform_id platform = 0;
    cl_device_id device = 0;
    cl_context_properties props[3] = { CL_CONTEXT_PLATFORM, 0, 0 };
    cl_context ctx = 0;
    cl_command_queue queue = 0;
    cl_event event = NULL;
    int ret = 0;

    /* Setup OpenCL environment. */
    err = clGetPlatformIDs(1, &platform, NULL);
    if (err != CL_SUCCESS) {
        printf( "clGetPlatformIDs() failed with %d\n", err );
        return r;
    }

    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
    if (err != CL_SUCCESS) {
        printf( "clGetDeviceIDs() failed with %d\n", err );
        return r;
    }

    props[1] = (cl_context_properties)platform;
    ctx = clCreateContext(props, 1, &device, NULL, NULL, &err);
    if (err != CL_SUCCESS) {
        printf( "clCreateContext() failed with %d\n", err );
        return r;
    }

    queue = clCreateCommandQueue(ctx, device, 0, &err);
    if (err != CL_SUCCESS) {
        printf( "clCreateCommandQueue() failed with %d\n", err );
        clReleaseContext(ctx);
        return r;
    }

    /* Setup clAmdBlas. */
    err = clAmdBlasSetup();
    if (err != CL_SUCCESS) {
        printf("clAmdBlasSetup() failed with %d\n", err);
        clReleaseCommandQueue(queue);
        clReleaseContext(ctx);
        return r;
    }

	cl_mem d_A = clCreateBuffer(ctx, CL_MEM_READ_ONLY, m.getDim1() * m.getDim2() * sizeof(double), NULL, &err);
	cl_mem d_B = clCreateBuffer(ctx, CL_MEM_READ_ONLY, b.getDim() * sizeof(double), NULL, &err);
	cl_mem d_C = clCreateBuffer(ctx, CL_MEM_READ_WRITE, r.getDim() * sizeof(double), NULL, &err);

	for(int i=0; i<m.getDim1(); i++)
	{
		err = clEnqueueWriteBuffer(queue, d_A, CL_TRUE, i*m.getDim2()*sizeof(double), m(i).getDim()*sizeof(double), &m(i)(0), 0, NULL, NULL);
	}

	err = clEnqueueWriteBuffer(queue, d_B, CL_TRUE, 0, b.getDim()*sizeof(double), &b(0), 0, NULL, NULL);

	err = clAmdBlasDgemv(clAmdBlasRowMajor, clAmdBlasNoTrans, m.getDim2(), b.getDim(), 1.0, d_A, m.getDim1(), d_B, 0,
		1, 0.0, d_C, 0, 1, 1, &queue, 0, NULL, &event);

	if(err == CL_SUCCESS)
	{
		err = clWaitForEvents(1, &event);
		err = clEnqueueReadBuffer(queue, d_C, CL_TRUE, 0, r.getDim()*sizeof(double), &r[0], 0, NULL, NULL);
	}
	
	clReleaseMemObject(d_C);
	clReleaseMemObject(d_B);
	clReleaseMemObject(d_A);

	clAmdBlasTeardown();

	clReleaseCommandQueue(queue);
	clReleaseContext(ctx);

	return r;
}

} // namespace GMlib
