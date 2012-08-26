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



/*! \file gmisocamera.h
 *
 *  Interface for the IsoCamera class.
 */


#ifndef __gmISOCAMERA_H__
#define __gmISOCAMERA_H__


#include "gmcamera.h"

// gmlib
#include <core/utils/gmstream.h>

namespace GMlib {



  /*! \class IsoCamera gmisocamera.h <gmIsoCamera>
	 *	\brief Pending Documentation
	 *
	 *	Pending Documentation
	 */
  class IsoCamera : public Camera {
	public:
    IsoCamera(Scene* s);
    IsoCamera(
			const Point<float,3>&  pos,
			const Point<float,3>&  look_pos
		);
    IsoCamera(
			const Point<float,3>&  pos,
			const Vector<float,3>& dir,
			const Vector<float,3>& up,
			float zoom=1
		);
    ~IsoCamera();

		double					deltaTranslate(DisplayObject *);
		std::string 		getIdentity() const;

		void 						go(bool stereo=false);
		void						lockTarget(SceneObject* obj);
		void						lockTarget(const Point<float,3>& p);
		void						lockTarget(double d);
		SceneObject*		lockTargetAtPixel(int,int);
		void 						move(float d);
		void 						move(const Vector<float,3>& t);


		void 						rotate(Angle, const Vector<float,3>&);
		void 						rotate(Angle, const Point<float,3>&,const UnitVector<float,3>&);
		void 						rotateGlobal(Angle, const Vector<float,3>&);
		void 						rotateGlobal(Angle, const Point<float,3>&,const UnitVector<float,3>&);

		void 						setGrid(double w, double h);
		void 						tilt(Angle a);
		void 						translate(const Vector<float,3>& trans_vector);
		void 						translateGlobal(const Vector<float,3>&);
		void 						turn(Angle a);
		void 						zoom(float z);


	protected:
		// ***********
		// From Camera
		void						setPerspective();

		// ****************
		// From SceneObject
		void						localDisplay();
		void						localSelect();


	private:
		double					_horisontal;
		double					_gh,_gw;

		// ***********
		// From Camera
		void						drawActiveCam();
		SceneObject*		find(unsigned int name);				/// \todo ????? NOT IMPLEMENTED !!`????? why??
		void						resetC(float z=1);


  };	// END class IsoCamera


  /*! void IsoCamera::drawActivCam()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void IsoCamera::drawActiveCam() {

//    int i,ih,iw;
//    iw = _horisontal/_gw;
//    ih = _ratio*_horisontal/_gh;
//    Point3D<float> cp=_pos+(0.99*_near_plane+0.01*_far_plane)*_dir;
//    GLboolean lg;
//    glGetBooleanv(GL_LIGHTING,&lg);
//    if(lg) glDisable(GL_LIGHTING);
//    Color gr(120,120,120);
//    glColor(gr);
//    glBegin(GL_LINES);
//      Vector<float,3> dside = _gw*_side;
//      Vector<float,3> dup   = _gh*_up;
//      Vector<float,3> side  = ih*dside;
//      Vector<float,3> up    = iw*dup;
//      for(i=-iw; i<=iw; i++)
//      {
//        glPoint(cp+double(i)*dup-side);
//        glPoint(cp+double(i)*dup+side);
//      }
//      for(i=-ih; i<=ih; i++)
//      {
//        glPoint(cp-up+double(i)*dside);
//        glPoint(cp+up+double(i)*dside);
//      }
//    glEnd();
//    if (lg) glEnable(GL_LIGHTING);
  }


  /*! std::string IsoCamera::getIdentity() const
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  std::string IsoCamera::getIdentity() const {

    return "IsoCamera";
  }


  /*! void IsoCamera::move(float d)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   *	Moveing in shooting direction
   */
  inline
  void IsoCamera::move( float /* delta */ ) {}


  /*! void IsoCamera::move(const Vector<float,3>& t)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   *	Move in direction t.
   */
  inline
  void IsoCamera::move( const Vector<float,3>& /* delta */ ) {}


  /*! void IsoCamera::rotate(Angle, const Vector<float,3>&)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void IsoCamera::rotate( Angle /*angle*/, const Vector<float,3>& /* axel */ ) {}


  /*! void IsoCamera::rotate(Angle, const Point<float,3>&,const UnitVector<float,3>&)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void IsoCamera::rotate(Angle, const Point<float,3>&,const UnitVector<float,3>&) {}


  /*! void IsoCamera::rotateGlobal(Angle, const Vector<float,3>&)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void IsoCamera::rotateGlobal(Angle, const Vector<float,3>&) {}


  /*! void IsoCamera::rotateGlobal(Angle, const Point<float,3>&,const UnitVector<float,3>&)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void IsoCamera::rotateGlobal(Angle, const Point<float,3>&,const UnitVector<float,3>&) {}


  /*! void IsoCamera::setGrid(double w, double h)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void IsoCamera::setGrid(double w, double h) {
    _gw=w;
    _gh=h;
  }


  /*! void IsoCamera::tilt(Angle a)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void IsoCamera::tilt( Angle /* angle */ ) {}


  /*! void IsoCamera::translate(const Vector<float,3>& trans_vector)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void IsoCamera::translate( const Vector<float,3>& /*trans_vector*/ ) {}


  /*! void IsoCamera::translateGlobal(const Vector<float,3>&)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void IsoCamera::translateGlobal( const Vector<float,3>& /*trans_vector*/ ) {}


  /*! void IsoCamera::turn(Angle a)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void IsoCamera::turn( Angle /*angle*/ ) {}






}	// END namespace GMlib

#endif // __gmISOCAMERA_H__
