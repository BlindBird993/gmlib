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



/*! \file gmspotlight.h
 */



#ifndef __gmSPOTLIGHT_H__
#define __gmSPOTLIGHT_H__


// gmlib
#include "gmpointlight.h"

// stl
#include <string>


namespace GMlib{

  /*! \class SpotLight gmspotlight.h <gmSpotLight>
   * \brief Pending Documentatioo
   *
   *	Pending Documentatioo
   */
  class SpotLight : public PointLight {
  public:
    SpotLight();
    SpotLight(
      const Point<float,3>& pos,
      const Vector<float,3>& dir,
      Angle cut_off );
    SpotLight(
      const Color& amb,
      const Color& dif,
      const Color& spe,
      const Point<float,3>& pos,
      const Vector<float,3>& dir,
      Angle cut_off = 90);
    SpotLight( const SpotLight& pl);
    virtual ~SpotLight();

    const Angle&            getCutOff() const;
    double                  getExponent() const;
    std::string             getIdentity() const;

    virtual void            setCutOff( const Angle& cut_off);
    void                    setExponent(double exp);


  protected:
    Vector3D<float>	        _dir;
    Angle				            _cutoff;
    double				          _exp;

    void lighting();

  };	// END class SpotLight





  /*! const std::string SpotLight::getIdentity() const
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  std::string SpotLight::getIdentity() const {

    return "Spot Light";
  }


}	// END namespace GMlib


#endif // __gmSPOTLIGHT_H__