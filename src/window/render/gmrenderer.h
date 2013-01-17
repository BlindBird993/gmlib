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

#ifndef __gmRENDERER_H__
#define __gmRENDERER_H__


// GMlib
#include <opengl/gmopengl.h>


namespace GMlib {

  class Scene;
  class SceneObject;
  class Camera;

  class Renderer {
  public:
    Renderer( Scene *scene );
    virtual ~Renderer();


    /* scene/sceneobject stuff */
    bool              isStereoEnabled() const;
    void              enableStereo( bool enable = true );




    /* Rendering control */
    virtual void      beginRendering() = 0;
    virtual void      endRendering() = 0;
    virtual void      prepareRendering() = 0;


    /* Rendring stuff */

    int               getBufferWidth() const;
    int               getBufferHeight() const;
    bool              isInitialized() const;

    virtual void      init() = 0;
    virtual void      render( Camera* cam ) = 0;
    virtual void      resize( int w, int h ) = 0;

    void              prepare( Camera* cam );

  protected:
    void              markAsInitialized();
    void              setBufferSize( int w, int h );

    /* internal cache */
    mutable Array<SceneObject*>     _objs;

  private:
    /* Scene and sceneobject */
    Scene             *_scene;
    bool              _stereo;

    /* Buffer */
    bool              _initialized;
    int               _buffer_width;
    int               _buffer_height;


  }; // END class Renderer


  class DisplayRenderer : public Renderer {
  public:
    DisplayRenderer( Scene* scene );

    /* virtual from Renderer */
    void      prepareRendering();
    void      beginRendering();
    void      endRendering();

    /* */
    void      init();
    void      render( Camera* cam );
    void      resize(int w, int h);

    public:

    GLuint       _render_rbo_color;
    GLuint       _render_rbo_selected;
    GLuint       _render_rbo_depth;


  }; // END class DisplayRenderer

} // END namespace GMlib

#endif // __gmRENDERER_H__
