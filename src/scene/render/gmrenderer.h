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
#include <opengl/gmframebufferobject.h>


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



    /* Rendring stuff */
    int               getBufferWidth() const;
    int               getBufferHeight() const;
    bool              isInitialized() const;

    virtual void      resize( int w, int h ) = 0;

  protected:
    void              markAsInitialized();
    void              setBufferSize( int w, int h );

    Scene             *_scene;

  private:
    /* Scene and sceneobject */
    bool              _stereo;

    /* Buffer */
    bool              _initialized;
    int               _buffer_width;
    int               _buffer_height;


  }; // END class Renderer



  class SingleObjectRenderer : public Renderer {
  public:
    SingleObjectRenderer( Scene* scene );
  }; // END class SingleObjectRenderer

  class MultiObjectRenderer : public Renderer {
  public:
    MultiObjectRenderer( Scene* scene );

    virtual void      prepare( Array<SceneObject*>& objs, Camera* cam ) = 0;
  }; // END class MultiObjectRenderer














  class DisplayRenderer : public MultiObjectRenderer {
  public:
    DisplayRenderer( Scene* scene );

    void      render(Array<SceneObject*>& objs, const Array<Camera*>& cameras );
    void      renderSelect(Array<SceneObject*>& objs, const Array<Camera*>& cameras );

    /* virtual from Renderer */
    void      resize(int w, int h);

    /* virtual from MultiObjectRenderer */
    void      prepare(Array<SceneObject*>& objs, Camera *cam);


//  private:

    FramebufferObject   _fbo;
    FramebufferObject   _fbo_color;
    FramebufferObject   _fbo_select;

    /* Textures */
    GLuint              _rbo_color;
    GLuint              _rbo_select;

    /* Render buffer objects */
    GLuint              _rbo_depth;




  }; // END class DisplayRenderer















  class SelectRenderer : public MultiObjectRenderer {
  public:
    SelectRenderer( Scene* scene );

    SceneObject*                findObject( int x, int y );
    Array<SceneObject*>         findObjects(int xmin, int ymin, int xmax, int ymax );

    void                        select(Array<SceneObject*>& objs, Camera* cam, int type_id );


    /* virtual from Renderer */
    void                        resize(int w, int h);

    /* virtual from MultiObjectRenderer */
    void                        prepare(Array<SceneObject*>& objs, Camera *cam);

  };

} // END namespace GMlib

#endif // __gmRENDERER_H__
