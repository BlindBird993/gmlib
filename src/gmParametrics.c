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



/*! \file gmParametrics.c
 *  \brief Parametrics class implementations
 *
 *  Implementations of the Parametrics class.
 *
 *  \date   2008-11-24
 */


namespace GMlib {

  template <typename T, int n>
  inline
  Parametrics<T,n>::Parametrics() {}


  template <typename T, int n>
  inline
  Parametrics<T,n>::Parametrics( const Parametrics<T,n>& copy ) : AffineSpace<T,n>(copy) {}


  template <typename T, int n>
  std::string Parametrics<T,n>::getIdentity() const {

    return "Parameterics";
  }


  template <typename T, int n>
  void Parametrics<T,n>::setDerivationMethod( GM_DERIVATION_METHOD method ) {

    _dm = method;
  }
}
