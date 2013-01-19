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
    virtual void      prepare( Camera* cam ) = 0;
    virtual void      resize( int w, int h ) = 0;

  protected:
    void              markAsInitialized();
    void              setBufferSize( int w, int h );

    /* internal cache */
    Array<SceneObject*>     _objs;

    //
    Scene             *_scene;

  private:
    /* Scene and sceneobject */
    bool              _stereo;

    /* Buffer */
    bool              _initialized;
    int               _buffer_width;
    int               _buffer_height;


  }; // END class Renderer


  class DisplayRenderer : public Renderer {
  public:
    DisplayRenderer( Scene* scene );

    void      renderSelect( Camera* cam );

    /* virtual from Renderer */
    void      prepareRendering();
    void      beginRendering();
    void      endRendering();

    void      init();
    void      prepare(Camera *cam);
    void      render( Camera* cam );
    void      resize(int w, int h);

  }; // END class DisplayRenderer

  class SelectRenderer : public Renderer {
  public:
    SelectRenderer( Scene* scene );

    SceneObject*                findObject( int x, int y );
    Array<SceneObject*>         findObjects(int xmin, int ymin, int xmax, int ymax );

    /* virtual from Renderer */
    void                        prepareRendering();
    void                        beginRendering();
    void                        endRendering();

    void                        init();
    void                        prepare(Camera *cam);
    void                        select(Camera* cam, int type_id );
    void                        resize(int w, int h);

  };

} // END namespace GMlib

#endif // __gmRENDERER_H__
