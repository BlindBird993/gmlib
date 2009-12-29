
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



/*! \file gmVDynamicTextureAnimation.c
 *
 *  VDynamicTextureAnimation class function implementations.
 *
 *  \date   2009-07-31
 */


namespace GMlib {

  template <typename T, int n>
  inline
  VDynamicTextureAnimation<T,n>::VDynamicTextureAnimation(){

    _rot_angle = Angle(1);

    _rot_point[0] = 0.0f;
    _rot_point[1] = 0.0f;
    _rot_point[2] = 0.0f;

    _rot_axis[0] = 0.0f;
    _rot_axis[1] = 1.0f;
    _rot_axis[2] = 0.0f;

    _trans_vector[0] = 0.0f;
    _trans_vector[1] = 1.0f;
    _trans_vector[2] = 0.0f;

    _mode = GM_VISUALIZER_DYNTEXANIM_MODE_ROTATION;
  }


  template <typename T, int n>
  inline
  VDynamicTextureAnimation<T,n>::VDynamicTextureAnimation( const VDynamicTextureAnimation<T,n>& copy ) : VDynamicTexture<T,n>( copy ) {}


  template <typename T, int n>
  inline
  GM_VISUALIZER_DYNTEXANIM_MODE VDynamicTextureAnimation<T,n>::getMode() const {

    return _mode;
  }


  template <typename T, int n>
  inline
  std::string VDynamicTextureAnimation<T,n>::getIdentity() const {

    return "VDynamicTextureAnimation";
  }


  template <typename T, int n>
  inline
  const Angle& VDynamicTextureAnimation<T,n>::getRotationAngle() const {

    return _rot_angle;
  }


  template <typename T, int n>
  inline
  const Vector<float,3>& VDynamicTextureAnimation<T,n>::getRotationAxis() const {

    return _rot_axis;
  }


  template <typename T, int n>
  inline
  const Vector<float,3>& VDynamicTextureAnimation<T,n>::getRotationPoint() const {

    return _rot_point;
  }


  template <typename T, int n>
  inline
  const Vector<float,3>& VDynamicTextureAnimation<T,n>::getTranslationVector() const {

    return _trans_vector;
  }


  template <typename T, int n>
  inline
  void VDynamicTextureAnimation<T,n>::setMode( GM_VISUALIZER_DYNTEXANIM_MODE mode ) {

    _mode = mode;
  }


  template <typename T, int n>
  inline
  void VDynamicTextureAnimation<T,n>::setRotation( const Angle& a, const Point<float,3>& p, const UnitVector<float,3>& d ) {

    _rot_angle = a;
    _rot_point = p;
    _rot_axis = d;
  }


  template <typename T, int n>
  inline
  void VDynamicTextureAnimation<T,n>::setTranslation(const Vector<float,3>& trans_vector) {

    _trans_vector = trans_vector;
  }


  template <typename T, int n>
  inline
  void VDynamicTextureAnimation<T,n>::simulate( double dt ) {

    switch( _mode ) {
      case GM_VISUALIZER_DYNTEXANIM_MODE_ROTATION: {

        // Check that the rotation axis is valid
        if( (_rot_axis[0] > 1e-5 || _rot_axis[1] > 1e-5 || _rot_axis[2] > 1e-5) && (_rot_axis[0] + _rot_axis[1] + _rot_axis[2]) > 1e-5 ) {

          // Rotate
          VDynamicTexture<T,n>::rotate( Angle( double( _rot_angle.getRad() * dt) ), _rot_point, _rot_axis );
        }
      } break;

      case GM_VISUALIZER_DYNTEXANIM_MODE_ROTATION_TRANSLATION: {

        // Check that the rotation axis is valid
        if( (_rot_axis[0] > 1e-5 || _rot_axis[1] > 1e-5 || _rot_axis[2] > 1e-5) && (_rot_axis[0] + _rot_axis[1] + _rot_axis[2]) > 1e-5 ) {

          // Rotate
          VDynamicTexture<T,n>::rotate( Angle( double( _rot_angle.getRad() * dt) ), _rot_point, _rot_axis );

          // Translate
          VDynamicTexture<T,n>::translate( _trans_vector * dt );
        }

      } break;

      case GM_VISUALIZER_DYNTEXANIM_MODE_TRANSLATION: {

          // Translate
        VDynamicTexture<T,n>::translate( _trans_vector * dt );

      } break;

      case GM_VISUALIZER_DYNTEXANIM_MODE_TRANSLATION_ROTATION: {

        // Check that the rotation axis is valid
        if( (_rot_axis[0] > 1e-5 || _rot_axis[1] > 1e-5 || _rot_axis[2] > 1e-5) && (_rot_axis[0] + _rot_axis[1] + _rot_axis[2]) > 1e-5 ) {

          // Translate
          VDynamicTexture<T,n>::translate( _trans_vector * dt );

          // Rotate
          VDynamicTexture<T,n>::rotate( Angle( double( _rot_angle.getRad() * dt) ), _rot_point, _rot_axis );
        }

      } break;

      case GM_VISUALIZER_DYNTEXANIM_MODE_NO_ANIMATION:
      default:
        break;
    }
  }

}



