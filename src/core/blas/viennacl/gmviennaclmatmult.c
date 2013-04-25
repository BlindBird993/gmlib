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

} // namespace GMlib
