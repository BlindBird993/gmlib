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

#ifndef __GM_SCENE_EVENT_GMEVENTCONTROLLER_H__
#define __GM_SCENE_EVENT_GMEVENTCONTROLLER_H__

#include "gmevent.h"

#include <gmCoreModule>

namespace GMlib {

  class SceneObject;

  /*!
   * \class EventController gmeventcontroller.h <gmEventController>
   * \brief EventController base class.
   *
   *  Provides an interface to detect and control Events that can happen
   *  to SceneObjects during a time step dt.
   *
   *  Inherited classes need to implement functions which detects:
   *    1. Events within a given dt (first pass)
   *    2. Any events following after handling of a specific event
   *       within that dt (second pass)
   *    NB! Use insertAlways on the provided Array<Event>&
   *        for performance reasons. (See EventManager::processEvents().
   *        It removes duplicates after insert).
   *
   *  Optionally, inherited classes can store customized information
   *  and perform updates based on events.
   *
   */
  class EventController {
  public:
    EventController();

    bool add(SceneObject* so);
    bool getEvents(Array<Event>& events, double dt);
    bool handleEvent(Array<Event>& events, Event& event);

  private:
    virtual bool detectEvents(Array<Event>& events, double dt) = 0;
    virtual bool detectEvents(Array<Event>& events, Event& event) = 0;
    virtual bool doInsert(SceneObject* so);
    virtual bool doUpdate(Event& event);

  protected:
    Array<SceneObject*> _scene_objects;
  };

}

#endif
