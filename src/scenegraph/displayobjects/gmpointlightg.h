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



/*! \file gmpointlightg.h
 *
 *  Graphical PointLight Class
 */



#ifndef __gmPOINTLIGHTG_H__
#define __gmPOINTLIGHTG_H__


#include "../light/gmpointlight.h"


// stl
#include <string>


namespace GMlib{


  class PointLightG : public PointLight {
  public:
    PointLightG();
		PointLightG(	const Point<float,3>& pos);
		PointLightG(
      const Color& amb,
			const Color& dif,
			const Color& spe,
			const Point<float,3>& pos
		);
		PointLightG( const PointLight& copy );
		PointLightG( const PointLightG& copy );

		std::string     getIdentity() const;

  protected:
    void            localDisplay();
    void            localSelect();

  private:
    unsigned int    _dlist;

    void            _init();
    void            _makeDisplayList();

  }; // END class PointLightG

} // END namespace GMlib


#endif // __gmPOINTLIGHTG_H__
