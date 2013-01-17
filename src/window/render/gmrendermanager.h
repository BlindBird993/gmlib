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



/*! \file gmrendermanager.h
 *  \brief Pending Documentation
 *
 *  Pending Documentation
 */

#ifndef __gmRENDERMANAGER_H__
#define __gmRENDERMANAGER_H__


// local

//gmlib
#include <core/containers/gmarray.h>
#include <scene/gmfrustum.h>


namespace GMlib {

  class Scene;
  class SceneObject;
  class Camera;
  class ViewSet;

  class Renderer;
  class DisplayRenderer;


  class RenderManager {
  public:
    RenderManager( Scene* scene );

    void        init();
    void        render( ViewSet& view_set );
    void        resize( int w, int h );

  private:
    Scene                     *_scene;
    DisplayRenderer           *_disp;

//    Renderer                *_object_renderer;
//    Renderer                *_select_renderer;



  }; // END class RenderManager

} // END namespace GMlib

#endif // __gmRENDERMANAGER_H__
