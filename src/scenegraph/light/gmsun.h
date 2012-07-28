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



/*! \file gmsun.h
 *
 */



#ifndef __gmSUN_H__
#define __gmSUN_H__


// gmlib
#include "../gmdisplayobject.h"

// stl
#include <string>


namespace GMlib{



  /*!	\class Sun gmsun.h <gmSun>
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  class Sun : public Light, public SceneObject {
  public:
    Sun(const Vector<float,3>& dir = Vector3D<float>(1,1,1));
    virtual ~Sun();

    std::string             getIdentity() const;
    void                    scaleDayLight( double d );
    void                    setDayLight( const Color& amb = Color( 0.1f, 0.1f, 0.1f ) );


  protected:
    void                    lighting();


  private:
    Vector<float,3>         _dir;
                Color                   _global_ambient;

    void                    _setDayLight(double d);

  }; // END class Sun





  /*! const std::string Sun::getIdentity()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  std::string Sun::getIdentity() const {

    return "Sun";
  }


  /*! void Sun::scaleDayLight(double d)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void Sun::scaleDayLight(double d) {

    _setDayLight(d);
  }


}	// END namespace GMlib


#endif // __gmSUN_H__
