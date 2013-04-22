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


#define VIENNACL_WITH_OPENCL
#include <viennacl/ocl/backend.hpp>
#include <viennacl/matrix.hpp>
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

			viennacl::matrix<float> inverse(vcl.size1(), vcl.size2());

			viennacl::linalg::lu_substitute(vcl, inverse);
			viennacl::backend::finish();



			int nk=getDim1();
			Array<float> aa;
			aa.setSize(nk*nk);
			for(int i=0; i<nk; i++)	// daft cast
				for(int j=0; j<nk; j++) aa[i+nk*j] = (float) (*this)[i][j];

			Array<int> ipiv; ipiv.setSize(nk);		// pivot table (result), size max(1,mmm,nnn)
			int info=0;								// error message, i=info>0 means that a[i][i]=0 ): singular,
/*
			sgetrf(nk, nk, aa.ptr(), nk, ipiv.ptr(), &info);				 // using Lapack LU-fact a is overwritten by LU
			sgetri(nk, aa.getPtr(), nk, ipiv.getPtr(), &info);
*/
			// if(info==0)
			for(int i=0; i<nk; i++)
				for(int j=0; j<nk; j++) (*this)[i][j]=(float) aa[i+j*nk];
		}
		return (*this);
	}

	DMatrix<double>& DMatrix<double>::invert() {
		if(getDim1()==getDim2() && getDim1()>1)
		{
			int nk=getDim1();
			Array<double> aa;
			aa.setSize(nk*nk);
			for(int i=0; i<nk; i++)	// daft cast
				for(int j=0; j<nk; j++) aa[i+nk*j] = (double) (*this)[i][j];

			Array<int> ipiv; ipiv.setSize(nk);		// pivot table (result), size max(1,mmm,nnn)
			int info=0;								// error message, i=info>0 means that a[i][i]=0 ): singular,
			/*
			dgetrf(nk, nk, aa.ptr(), nk, ipiv.ptr(), &info);				 // using Lapack LU-fact a is overwritten by LU
			dgetri(nk, aa.getPtr(), nk, ipiv.getPtr(), &info);
*/
			// if(info==0)
			for(int i=0; i<nk; i++)
				for(int j=0; j<nk; j++) (*this)[i][j]=(double) aa[i+j*nk];
		}
		return (*this);
	}
} // namespace GMlib