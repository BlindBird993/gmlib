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



/*! \file gmselectrender.h
 *  \brief Pending Documentation
 *
 *  Pending Documentation
 */

#ifndef __gmSELECTRENDERER_H__
#define __gmSELECTRENDERER_H__


#include "gmrenderer.h"

// local
#include "../camera/gmcamera.h"
#include "../visualizers/gmstdrepvisualizer.h"

// gmlib
#include <opengl/gmframebufferobject.h>
#include <opengl/gmtexture.h>
#include <opengl/gmprogram.h>


namespace GMlib {

  class SelectRenderer : public Renderer {
  public:
    explicit SelectRenderer();

    const DisplayObject*        findObject(int x, int y) const;
    DisplayObject*              findObject(int x, int y);
    Array<const DisplayObject*> findObjects(int xmin, int ymin, int xmax, int ymax) const;
    Array<DisplayObject*>       findObjects(int xmin, int ymin, int xmax, int ymax);


    /* virtual from Renderer */

    void    setRBOcolorName( const std::string& name ) { _rbo_color.setName(name); }

    void                        select(int what);
  protected:
    void                        reshape();
    void                        render();
    void                        prepare(Camera* cam);

  private:
    GL::Program                 _prog;

    GL::FramebufferObject       _fbo;
    GL::Texture                 _rbo_color;
    GL::Texture                 _rbo_depth;

    mutable int                 _what;
    mutable Array<DisplayObject*>    _objs;

    void                        initSelectProgram();

    /* virtual from Renderer */
    void                        renderScene(Camera *cam);
  };





} // END namespace GMlib

#endif // __gmSELECTRENDERER_H__
