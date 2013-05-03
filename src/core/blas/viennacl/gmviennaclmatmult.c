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



/*! \file gmviennaclmatmult.c
 *
 *  Implementation of ViennaCL-specific matrix multiplication operators.
 */

#include <viennacl/ocl/backend.hpp>
#include <viennacl/linalg/prod.hpp>
#include <viennacl/matrix_proxy.hpp>

namespace GMlib
{

inline
const DMatrix<float>&  operator*(const DMatrix<float>& m, const DMatrix<float>& b)
{
	static DMatrix<float> r;
	r.setDim(m.getDim1(), b.getDim2());

	std::vector<float> stl_A(m.getDim1() * m.getDim2());
	std::vector<float> stl_B(b.getDim1() * b.getDim2());
	std::vector<float> stl_C(m.getDim1() * b.getDim2());

	for(int i=0; i<m.getDim1(); i++)
		for(int j=0; j<m.getDim2(); j++)
			stl_A[i*m.getDim2()+j] = m(i)(j);
	for(int i=0; i<b.getDim1(); i++)
		for(int j=0; j<b.getDim2(); j++)
			stl_B[i*b.getDim2()+j] = b(i)(j);

#ifdef VIENNACL_WITH_OPENCL
	viennacl::ocl::set_context_device_type(0, viennacl::ocl::gpu_tag());
#endif

	viennacl::matrix<float> vcl_A(m.getDim1(), m.getDim2());
	viennacl::matrix<float> vcl_B(b.getDim1(), b.getDim2());
	viennacl::matrix<float> vcl_C(m.getDim1(), b.getDim2());

#ifdef VIENNACL_WITH_OPENCL
	std::vector<viennacl::ocl::device> devices = viennacl::ocl::current_context().devices();
#else
	std::vector<long> devices(1);
#endif

#ifdef VIENNACL_WITH_OPENCL
	viennacl::ocl::current_context().switch_device(devices[0]);
#endif

	viennacl::fast_copy(&stl_A[0], &stl_A[0] + stl_A.size(), vcl_A);
	viennacl::fast_copy(&stl_B[0], &stl_B[0] + stl_B.size(), vcl_B);

	vcl_C = viennacl::linalg::prod(vcl_A, vcl_B);
	viennacl::backend::finish();

	viennacl::fast_copy(vcl_C, &stl_C[0]);

	for(int i=0; i<r.getDim1(); i++)
		for(int j=0; j<r.getDim2(); j++)
			r[i][j]=(float) stl_C[i*r.getDim2()+j];

	return r;
}

inline
const DMatrix<double>&  operator*(const DMatrix<double>& m, const DMatrix<double>& b)
{
	static DMatrix<double> r;
	r.setDim(m.getDim1(), b.getDim2());

	std::vector<double> stl_A(m.getDim1() * m.getDim2());
	std::vector<double> stl_B(b.getDim1() * b.getDim2());
	std::vector<double> stl_C(m.getDim1() * b.getDim2());

	for(int i=0; i<m.getDim1(); i++)
		for(int j=0; j<m.getDim2(); j++)
			stl_A[i*m.getDim2()+j] = m(i)(j);
	for(int i=0; i<b.getDim1(); i++)
		for(int j=0; j<b.getDim2(); j++)
			stl_B[i*b.getDim2()+j] = b(i)(j);

#ifdef VIENNACL_WITH_OPENCL
	viennacl::ocl::set_context_device_type(0, viennacl::ocl::gpu_tag());
#endif

	viennacl::matrix<double> vcl_A(m.getDim1(), m.getDim2());
	viennacl::matrix<double> vcl_B(b.getDim1(), b.getDim2());
	viennacl::matrix<double> vcl_C(m.getDim1(), b.getDim2());

#ifdef VIENNACL_WITH_OPENCL
	std::vector<viennacl::ocl::device> devices = viennacl::ocl::current_context().devices();
#else
	std::vector<long> devices(1);
#endif

#ifdef VIENNACL_WITH_OPENCL
	viennacl::ocl::current_context().switch_device(devices[0]);
#endif

	viennacl::fast_copy(&stl_A[0], &stl_A[0] + stl_A.size(), vcl_A);
	viennacl::fast_copy(&stl_B[0], &stl_B[0] + stl_B.size(), vcl_B);

	vcl_C = viennacl::linalg::prod(vcl_A, vcl_B);
	viennacl::backend::finish();

	viennacl::fast_copy(vcl_C, &stl_C[0]);

	for(int i=0; i<r.getDim1(); i++)
		for(int j=0; j<r.getDim2(); j++)
			r[i][j]=(double) stl_C[i*r.getDim2()+j];

	return r;
}

inline
const DMatrix<std::complex<float> >&  operator*(const DMatrix<std::complex<float> >& m, const DMatrix<std::complex<float> >& b)
{
	static DMatrix<std::complex<float> > r;
	r.setDim(m.getDim1(), b.getDim2());

	std::vector<float> stl_A_r(m.getDim1() * m.getDim2());
	std::vector<float> stl_B_r(b.getDim1() * b.getDim2());
	std::vector<float> stl_C_r(m.getDim1() * b.getDim2());
	std::vector<float> stl_A_i(m.getDim1() * m.getDim2());
	std::vector<float> stl_B_i(b.getDim1() * b.getDim2());
	std::vector<float> stl_C_i(m.getDim1() * b.getDim2());

	for(int i=0; i<m.getDim1(); i++)
	{
		for(int j=0; j<m.getDim2(); j++)
		{
			stl_A_r[i*m.getDim2()+j] = m(i)(j).real();
			stl_A_i[i*m.getDim2()+j] = m(i)(j).imag();
		}
	}
	for(int i=0; i<b.getDim1(); i++)
	{
		for(int j=0; j<b.getDim2(); j++)
		{
			stl_B_r[i*b.getDim2()+j] = b(i)(j).real();
			stl_B_i[i*b.getDim2()+j] = b(i)(j).imag();
		}
	}
	
#ifdef VIENNACL_WITH_OPENCL
	viennacl::ocl::set_context_device_type(0, viennacl::ocl::gpu_tag());
#endif
	
	viennacl::matrix<float> vcl_A_r(m.getDim1(), m.getDim2());
	viennacl::matrix<float> vcl_B_r(b.getDim1(), b.getDim2());
	viennacl::matrix<float> vcl_C_r(m.getDim1(), b.getDim2());
	viennacl::matrix<float> vcl_A_i(m.getDim1(), m.getDim2());
	viennacl::matrix<float> vcl_B_i(b.getDim1(), b.getDim2());
	viennacl::matrix<float> vcl_C_i(m.getDim1(), b.getDim2());
	
#ifdef VIENNACL_WITH_OPENCL
	std::vector<viennacl::ocl::device> devices = viennacl::ocl::current_context().devices();
#else
	std::vector<long> devices(1);
#endif

#ifdef VIENNACL_WITH_OPENCL
	viennacl::ocl::current_context().switch_device(devices[0]);
#endif
	
	viennacl::fast_copy(&stl_A_r[0], &stl_A_r[0] + stl_A_r.size(), vcl_A_r);
	viennacl::fast_copy(&stl_B_r[0], &stl_B_r[0] + stl_B_r.size(), vcl_B_r);
	viennacl::fast_copy(&stl_A_i[0], &stl_A_i[0] + stl_A_i.size(), vcl_A_i);
	viennacl::fast_copy(&stl_B_i[0], &stl_B_i[0] + stl_B_i.size(), vcl_B_i);

	vcl_C_r = viennacl::linalg::prod(vcl_A_r, vcl_B_r) - viennacl::linalg::prod(vcl_A_i, vcl_B_i);
	vcl_C_i = viennacl::linalg::prod(vcl_A_r, vcl_B_i) + viennacl::linalg::prod(vcl_A_i, vcl_B_r);
	viennacl::backend::finish();

	viennacl::fast_copy(vcl_C_r, &stl_C_r[0]);
	viennacl::fast_copy(vcl_C_i, &stl_C_i[0]);
	
	for(int i=0; i<r.getDim1(); i++)
		for(int j=0; j<r.getDim2(); j++)
			r[i][j] = std::complex<float>(stl_C_r[i*r.getDim2()+j], stl_C_i[i*r.getDim2()+j]);

	return r;
}

inline
const DMatrix<std::complex<double> >&  operator*(const DMatrix<std::complex<double> >& m, const DMatrix<std::complex<double> >& b)
{
	static DMatrix<std::complex<double> > r;
	r.setDim(m.getDim1(), b.getDim2());

	std::vector<double> stl_A_r(m.getDim1() * m.getDim2());
	std::vector<double> stl_B_r(b.getDim1() * b.getDim2());
	std::vector<double> stl_C_r(m.getDim1() * b.getDim2());
	std::vector<double> stl_A_i(m.getDim1() * m.getDim2());
	std::vector<double> stl_B_i(b.getDim1() * b.getDim2());
	std::vector<double> stl_C_i(m.getDim1() * b.getDim2());

	for(int i=0; i<m.getDim1(); i++)
	{
		for(int j=0; j<m.getDim2(); j++)
		{
			stl_A_r[i*m.getDim2()+j] = m(i)(j).real();
			stl_A_i[i*m.getDim2()+j] = m(i)(j).imag();
		}
	}
	for(int i=0; i<b.getDim1(); i++)
	{
		for(int j=0; j<b.getDim2(); j++)
		{
			stl_B_r[i*b.getDim2()+j] = b(i)(j).real();
			stl_B_i[i*b.getDim2()+j] = b(i)(j).imag();
		}
	}
	
#ifdef VIENNACL_WITH_OPENCL
	viennacl::ocl::set_context_device_type(0, viennacl::ocl::gpu_tag());
#endif
	
	viennacl::matrix<double> vcl_A_r(m.getDim1(), m.getDim2());
	viennacl::matrix<double> vcl_B_r(b.getDim1(), b.getDim2());
	viennacl::matrix<double> vcl_C_r(m.getDim1(), b.getDim2());
	viennacl::matrix<double> vcl_A_i(m.getDim1(), m.getDim2());
	viennacl::matrix<double> vcl_B_i(b.getDim1(), b.getDim2());
	viennacl::matrix<double> vcl_C_i(m.getDim1(), b.getDim2());
	
#ifdef VIENNACL_WITH_OPENCL
	std::vector<viennacl::ocl::device> devices = viennacl::ocl::current_context().devices();
#else
	std::vector<long> devices(1);
#endif

#ifdef VIENNACL_WITH_OPENCL
	viennacl::ocl::current_context().switch_device(devices[0]);
#endif
	
	viennacl::fast_copy(&stl_A_r[0], &stl_A_r[0] + stl_A_r.size(), vcl_A_r);
	viennacl::fast_copy(&stl_B_r[0], &stl_B_r[0] + stl_B_r.size(), vcl_B_r);
	viennacl::fast_copy(&stl_A_i[0], &stl_A_i[0] + stl_A_i.size(), vcl_A_i);
	viennacl::fast_copy(&stl_B_i[0], &stl_B_i[0] + stl_B_i.size(), vcl_B_i);

	vcl_C_r = viennacl::linalg::prod(vcl_A_r, vcl_B_r) - viennacl::linalg::prod(vcl_A_i, vcl_B_i);
	vcl_C_i = viennacl::linalg::prod(vcl_A_r, vcl_B_i) + viennacl::linalg::prod(vcl_A_i, vcl_B_r);
	viennacl::backend::finish();

	viennacl::fast_copy(vcl_C_r, &stl_C_r[0]);
	viennacl::fast_copy(vcl_C_i, &stl_C_i[0]);
	
	for(int i=0; i<r.getDim1(); i++)
		for(int j=0; j<r.getDim2(); j++)
			r[i][j] = std::complex<double>(stl_C_r[i*r.getDim2()+j], stl_C_i[i*r.getDim2()+j]);

	return r;
}

} // namespace GMlib
