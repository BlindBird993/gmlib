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

  class EventController {
  public:
    EventController();

    bool getEvents(Array<Event>& events, double dt);
    bool handleEvent(Array<Event>& events, Event& event);
    bool insert(SceneObject* so);

  private:
    virtual bool detectEvents(Array<Event>& events, double dt) = 0;
    virtual bool detectEvents(Array<Event>& events, Event& event) = 0;
    virtual bool doInsert(SceneObject* so) = 0;
    virtual bool doUpdate(Event& event) = 0;

  protected:
    Array<SceneObject*> _scene_objects;
  };

}

#endif
