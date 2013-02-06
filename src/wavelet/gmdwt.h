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

#ifndef __GM_WAVELET_DWT_H__
#define __GM_WAVELET_DWT_H__

#include <core/containers/gmdvector.h>

namespace GMlib {
namespace Wavelet {

  template <typename T> class Filter;

  template<typename T>
  class Dwt {
  public:
    Dwt(int dim);

    void setFilter(int dim, Filter<T>* filter);

    void deCompose();
    void reConstruct();

  private:
    int                  _dimension;
    DVector<Filter<T>* > _filters;
  };

}
}

#include "gmdwt.c"

#endif
