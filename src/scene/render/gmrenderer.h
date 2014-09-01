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



/*! \file gmrender.h
 *  \brief Pending Documentation
 *
 *  Pending Documentation
 */

#ifndef __gmRENDERER_H__
#define __gmRENDERER_H__


// GMlib
#include <core/types/gmpoint.h>
#include <core/containers/gmarray.h>
#include <core/utils/gmcolor.h>

namespace GMlib {

  class Scene;
  class DisplayObject;
  class Camera;
  class RenderTarget;

  class Renderer {
  public:
    Renderer();
    virtual ~Renderer();

    const Color&      getClearColor() const;
    void              setClearColor( const Color& color );

    /* prepare stuff */
    void              render(Camera* cam );
    void              renderTo();
    virtual void      reshape( int x, int y, int w, int h );

    // TEST FUNCTIONS (SHOULD BE MADE FOR LIST OF RENDER TARGETS)
    void              setRenderTarget( RenderTarget* rt );

  private:
    int                                     _x, _y, _w, _h;
    Color                                   _clear_color;
    RenderTarget*                           _rt;
    mutable Array<DisplayObject *>          _objs;


    virtual void      prepare( Array<DisplayObject*>& objs, Camera* cam );
    virtual void      renderObjects( Array<DisplayObject*>& objs, Camera* cam ) = 0;
    virtual void      renderToTarget() = 0;

    void              setupViewport( int x, int y, int w, int h );


  }; // END class Renderer


} // END namespace GMlib

#endif // __gmRENDERER_H__
