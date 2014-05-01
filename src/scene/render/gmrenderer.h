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
#include <core/containers/gmarray.h>

namespace GMlib {

  class Scene;
  class DisplayObject;
  class Camera;
  class RenderTarget;

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

    virtual void      resize( int w, int h );

  protected:
    void              markAsInitialized();

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

    virtual void      prepare( Array<DisplayObject*>& objs, Camera* cam ) const;
  }; // END class MultiObjectRenderer


} // END namespace GMlib

#endif // __gmRENDERER_H__
