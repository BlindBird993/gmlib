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



/*! \file gmCameraIso.cpp
 *  \brief Inline CameraIso class implementations
 *
 *  Inline implementation of the CameraIso class.
 *
 *  \date   2008-08-03
 */


namespace GMlib {


  /*! std::string CameraIso::getIdentity() const
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  std::string CameraIso::getIdentity() const {

    return "CameraIso";
  }


  /*! void CameraIso::move(float d)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   *	Moveing in shooting direction
   */
  inline
  void CameraIso::move(float d) {}


  /*! void CameraIso::move(const Vector<float,3>& t)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   *	Move in direction t.
   */
  inline
  void CameraIso::move(const Vector<float,3>& t) {}


  /*! void CameraIso::rotate(Angle, const Vector<float,3>&)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void CameraIso::rotate(Angle, const Vector<float,3>&) {}


  /*! void CameraIso::rotate(Angle, const Point<float,3>&,const UnitVector<float,3>&)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void CameraIso::rotate(Angle, const Point<float,3>&,const UnitVector<float,3>&) {}


  /*! void CameraIso::rotateGlobal(Angle, const Vector<float,3>&)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void CameraIso::rotateGlobal(Angle, const Vector<float,3>&) {}


  /*! void CameraIso::rotateGlobal(Angle, const Point<float,3>&,const UnitVector<float,3>&)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void CameraIso::rotateGlobal(Angle, const Point<float,3>&,const UnitVector<float,3>&) {}


  /*! void CameraIso::setGrid(double w, double h)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void CameraIso::setGrid(double w, double h) {
    _gw=w;
    _gh=h;
  }


  /*! void CameraIso::tilt(Angle a)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void CameraIso::tilt(Angle a) {}


  /*! void CameraIso::translate(const Vector<float,3>& trans_vector)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void CameraIso::translate(const Vector<float,3>& trans_vector) {}


  /*! void CameraIso::translateGlobal(const Vector<float,3>&)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void CameraIso::translateGlobal(const Vector<float,3>&) {}


  /*! void CameraIso::turn(Angle a)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void CameraIso::turn(Angle a) {}

}
