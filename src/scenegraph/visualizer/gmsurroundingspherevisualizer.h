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



/*! \file gmsurroundingspherevisualizer.h
 *
 *  Header for the SurroundingSphereVisualizer class.
 */


#ifndef __gmSURROUNDINGSPHEREVISUALIZER_H__
#define __gmSURROUNDINGSPHEREVISUALIZER_H__

#include "gmvisualizer.h"

// gmlib::core
#include <core/utils/gmcolor.h>

// gmlib::opengl
#include <opengl/gmopengl.h>


namespace GMlib {

  class Camera;
  class Sphere3D;

  class SurroundingSphereVisualizer : public GMlib::Visualizer {
    public:
      SurroundingSphereVisualizer();
      ~SurroundingSphereVisualizer();

      void              display( Camera* cam );
      void              enableCleanSphere( bool enable );
      void              enableTotalSphere( bool enable );
      const Color&      getCleanSphereColor() const;
      std::string       getIdentity() const;
      const Color&      getTotalSphereColor() const;
      bool              isCleanSphereEnabled() const;
      bool              isTotalSphereEnabled() const;
      void              setCleanSphereColor( const Color& color );
      void              setTotalSphereColor( const Color& color );
      void              setWireframe( bool wireframe );

    protected:
      enum {
        TOTAL_SPHERE =  0x01,
        CLEAN_SPHERE =  0x02,
      };

      GLProgram         _display;

      unsigned int      _spheres;
      bool              _wireframe;
      Color             _cs_color;
      Color             _ts_color;

      Sphere3D          *_sphere;

  private:
      void              _displaySphere( const Sphere<float,3>& ss, GMlib::Camera* cam );

    }; // END class SurroundingSphereVisualizer

} // END namespace GMlib

#endif // __gmSURROUNDINGSPHEREVISUALIZER_H__
