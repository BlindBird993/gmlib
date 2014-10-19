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



/*! \file gmdisplayrender.h
 *  \brief Pending Documentation
 *
 *  Pending Documentation
 */

#ifndef __GM_SCENE_RENDER_DEFAULTRENDERER_H__
#define __GM_SCENE_RENDER_DEFAULTRENDERER_H__


#include "gmrenderer.h"

// local
#include "../camera/gmcamera.h"
#include "../visualizers/gmstdrepvisualizer.h"
#include "../visualizers/gmcoordsysrepvisualizer.h"
//#include "../window/gmviewset.h"
//#include "../window/gmwindow.h"
#include "gmrendertarget.h"

// gmlib
#include <opengl/gmframebufferobject.h>
#include <opengl/gmrenderbufferobject.h>
#include <opengl/gmtexture.h>
#include <opengl/bufferobjects/gmvertexbufferobject.h>
#include <scene/render/rendertargets/gmtexturerendertarget.h>


namespace GMlib {


  class DefaultRenderer : public Renderer {
  public:
    explicit DefaultRenderer();
    virtual ~DefaultRenderer();

    const GL::Texture&      getRenderTexture() const;
    const GL::Texture&      getSelectTexture() const;

    void                    setSelectColor( const Color& color );

    /* virtual from Renderer */
    void                    prepare() {}
    void                    render();
    void                    swap();
    void                    reshape( const Vector<int,2>& size );


    const TextureRenderTarget&      getFrontRenderTarget() const;
    const TextureRenderTarget&      getBackRenderTarget() const;

    const GL::UniformBufferObject&    getLightUBO() const;

  protected:
    virtual void            prepare(Camera *cam);

    mutable Array<DisplayObject*>    _objs;


  private:
    /* Object rendering */
    GL::Program             _render_prog;
    GL::FramebufferObject   _fbo;
    GL::Texture             _rbo_color;
    GL::Texture             _rbo_depth;

    /* Selection rendering */
    GL::Program             _render_select_prog;
    GL::FramebufferObject   _fbo_select;
    GL::Texture             _rbo_select;

    GL::FramebufferObject   _fbo_select_depth;
    GL::Texture             _rbo_select_depth;

    Color                   _select_color;

    /* other suff */
    HqMatrix<float,3>       _ortho_mat;

    GL::VertexBufferObject  _quad_vbo;

    void                    render(const DisplayObject *obj) const;
    void                    renderSelectedGeometry(const DisplayObject *obj) const;
    void                    renderCoordSys() const;


    CoordSysRepVisualizer   *_coord_sys_visu;

    void                    initRenderProgram();
    void                    initRenderSelectProgram();



    void                    renderScene();
    void                    renderToTarget();


    Vector<int,2>           _size;
    TextureRenderTarget     *_front_rt;
    TextureRenderTarget     *_back_rt;
    TextureRenderTarget     *_rt_test_dummy;

    GL::UniformBufferObject           _light_ubo;
    void                              updateLightUBO();




  }; // END class DisplayRenderer













} // END namespace GMlib

#endif // __GM_SCENE_RENDER_DEFAULTRENDERER_H__
