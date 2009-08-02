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



/*! \file gmVDynamicTextureAnimation.h
 *
 *  Interface for the VDynamicTextureAnimation class.
 *  Visualizes Textures Dynamically Animated on Displayable Curves, Surfaces, etc.
 *
 *  \date   2009-07-31
 */

#ifndef __gmVDYNAMICTEXTUREANIMATION_H__
#define __gmVDYNAMICTEXTUREANIMATION_H__


// STL includes
#include <string>

// GMlib includes
#include "gmVDynamicTexture.h"


namespace GMlib {


  enum GM_VISUALIZER_DYNTEXANIM_MODE {
    GM_VISUALIZER_DYNTEXANIM_MODE_NO_ANIMATION,
    GM_VISUALIZER_DYNTEXANIM_MODE_ROTATION,
    GM_VISUALIZER_DYNTEXANIM_MODE_TRANSLATION,
    GM_VISUALIZER_DYNTEXANIM_MODE_ROTATION_TRANSLATION,
    GM_VISUALIZER_DYNTEXANIM_MODE_TRANSLATION_ROTATION
  };


  template <typename T, int n>
  class VDynamicTextureAnimation : public VDynamicTexture<T,n> {
  public:
    VDynamicTextureAnimation();
    VDynamicTextureAnimation( const VDynamicTextureAnimation<T,n>& copy );

    std::string                     getIdentity() const;

    GM_VISUALIZER_DYNTEXANIM_MODE   getMode() const;
    const Angle&                    getRotationAngle() const;
    const Vector<float,3>&          getRotationAxis() const;
    const Vector<float,3>&          getRotationPoint() const;
    const Vector<float,3>&          getTranslationVector() const;

    void                            setMode( GM_VISUALIZER_DYNTEXANIM_MODE mode );
    void                            setRotation( const Angle& a, const Point<float,3>& p, const UnitVector<float,3>& d );
    void                            setTranslation( const Vector<float,3>& trans_vector );

    void                            simulate( double dt );


  protected:
    GM_VISUALIZER_DYNTEXANIM_MODE   _mode;

    Angle                           _rot_angle;
    Vector<float,3>                 _rot_point;
    Vector<float,3>                 _rot_axis;
    Vector<float,3>                 _trans_vector;


  }; // END class VDynamicTextureAnimation

} // END namespace GMlib

// Include VDynamicTextureAnimation class function implementations
#include "gmVDynamicTextureAnimation.c"


#endif // __gmVDYNAMICTEXTUREANIMATION_H__


