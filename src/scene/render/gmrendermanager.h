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
#include "../gmfrustum.h"

//gmlib
#include <core/containers/gmarray.h>
#include <opengl/gmopengl.h>
#include <opengl/gmframebufferobject.h>
#include <opengl/gmtexture.h>
#include <opengl/bufferobjects/gmvertexbufferobject.h>


namespace GMlib {

  class Scene;
  class DisplayObject;
  class Camera;
  class ViewSet;
  class GMWindow;

  class Renderer;
  class DisplayRenderer;
  class SelectRenderer;


  class RenderManager {
  public:
    RenderManager( GMWindow* window );

    /* Buffers and internal workings */
    void            updateMaxObjects( int no_objs );
    void            resize( int w, int h );

    /* Rendering */
    void            render(const Array<Camera *> &cameras );
    void            renderTo();

    /* Selecting */
    DisplayObject*  findObject( int x, int y );
    void            select(Camera* cam, int type_id );

    /* Rendering properties */
    const Color&    getClearColor() const;
    void            setClearColor( const Color& c );

    const Color&    getSelectColor() const;
    void            setSelectColor( const Color& c );


  private:
    GMWindow                  *_window;
    Scene                     *_scene;
    Array<DisplayObject*>       _objs;      //! Render objects "cache" array

    DisplayRenderer           *_disp;
    SelectRenderer            *_select;


    int                       _w, _h;
    Color                     _clear_color;
    Color                     _select_color;

    GLuint                    _vbo_quad;
    GLuint                    _vbo_quad_tex;

  }; // END class RenderManager

} // END namespace GMlib

#endif // __gmRENDERMANAGER_H__
