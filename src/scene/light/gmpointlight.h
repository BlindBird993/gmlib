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



/*! \file gmpointlight.h
 */



#ifndef __gmPOINTLIGHT_H__
#define __gmPOINTLIGHT_H__


#include "gmlight.h"
#include "../gmdisplayobject.h"

// stl
#include <string>



namespace GMlib{


  /*! \class PointLight gmpointlight.h <gmPointLight>
   * \brief Pending Documentatioo
   *
   *	Pending Documentatioo
   */
  class PointLight : public Light, public DisplayObject {
  public:
    PointLight();
    PointLight(	const Point<float,3>& pos);
    PointLight(
      const Color& amb,
      const Color& dif,
      const Color& spe,
      const Point<float,3>& pos
    );
    PointLight(	const PointLight& pl);
    virtual ~PointLight();

    virtual void 			culling( const Frustum& frustum );
    std::string		    getIdentity() const;
    void 							setAttenuation(float constant, float linear, float quadratic);
    void 							setAttenuation(const float att[]);

  protected:
    void 							calculateRadius(float constant, float linear, float quadratic);
    void 							lighting();

    Point3D<float>		_pos;
    Point3D<float>		_attenuation;


  private:
    Sphere<float,3>   _light_sphere;

  };	// END class PointLight












  /*! const std::string PointLight::getIdentity() const
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  std::string PointLight::getIdentity() const {

    return "Point Light";
  }


}	// END namespace GMlib

#endif // __gmPOINTLIGHT_H__
