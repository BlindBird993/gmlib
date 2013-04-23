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



/*! \file gmviennaclmatinv.c
 *
 *  Implementation of ViennaCL-specific matrix inversion operators.
 */

#include "gmviennaclconfig.h"
#include <viennacl/ocl/backend.hpp>
#include <viennacl/matrix_proxy.hpp>
#include <viennacl/linalg/lu.hpp>

namespace GMlib
{
	DMatrix<float>& DMatrix<float>::invert() {
		if(getDim1()==getDim2() && getDim1()>1)
		{
			std::vector<float> stl(getDim1() * getDim2());
			for(int i=0; i<getDim1(); i++)
				for(int j=0; j<getDim2(); j++)
					stl[i*getDim2()+j] = (*this)[i][j];

#ifdef VIENNACL_WITH_OPENCL
			viennacl::ocl::set_context_device_type(0, viennacl::ocl::gpu_tag());
#endif

			viennacl::matrix<float> vcl(getDim1(), getDim2());

#ifdef VIENNACL_WITH_OPENCL
			std::vector<viennacl::ocl::device> devices = viennacl::ocl::current_context().devices();
#else
			std::vector<long> devices(1);
#endif

#ifdef VIENNACL_WITH_OPENCL
			viennacl::ocl::current_context().switch_device(devices[0]);
#endif

			viennacl::fast_copy(&stl[0], &stl[0] + stl.size(), vcl);

			viennacl::linalg::lu_factorize(vcl);
			viennacl::backend::finish();

			viennacl::matrix<float> inverse(viennacl::identity_matrix<float>(vcl.size1()));

			viennacl::linalg::lu_substitute(vcl, inverse);
			viennacl::backend::finish();

			viennacl::fast_copy(inverse, &stl[0]);

			for(int i=0; i<getDim1(); i++)
				for(int j=0; j<getDim2(); j++)
					(*this)[i][j]=(float) stl[i*getDim2()+j];
		}
		return (*this);
	}

	DMatrix<double>& DMatrix<double>::invert() {
		if(getDim1()==getDim2() && getDim1()>1)
		{
			std::vector<double> stl(getDim1() * getDim2());
			for(int i=0; i<getDim1(); i++)
				for(int j=0; j<getDim2(); j++)
					stl[i*getDim2()+j] = (*this)[i][j];

#ifdef VIENNACL_WITH_OPENCL
			viennacl::ocl::set_context_device_type(0, viennacl::ocl::gpu_tag());
#endif

			viennacl::matrix<double> vcl(getDim1(), getDim2());

#ifdef VIENNACL_WITH_OPENCL
			std::vector<viennacl::ocl::device> devices = viennacl::ocl::current_context().devices();
#else
			std::vector<long> devices(1);
#endif

#ifdef VIENNACL_WITH_OPENCL
			viennacl::ocl::current_context().switch_device(devices[0]);
#endif

			viennacl::fast_copy(&stl[0], &stl[0] + stl.size(), vcl);

			viennacl::linalg::lu_factorize(vcl);
			viennacl::backend::finish();

			viennacl::matrix<double> inverse(viennacl::identity_matrix<double>(vcl.size1()));

			viennacl::linalg::lu_substitute(vcl, inverse);
			viennacl::backend::finish();

			viennacl::fast_copy(inverse, &stl[0]);

			for(int i=0; i<getDim1(); i++)
				for(int j=0; j<getDim2(); j++)
					(*this)[i][j]=(double) stl[i*getDim2()+j];
		}
		return (*this);
	}
} // namespace GMlib
