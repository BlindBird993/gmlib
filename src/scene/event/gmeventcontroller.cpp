#include "gmeventcontroller.h"

using namespace GMlib;


EventController::EventController() {
}

bool
EventController::getEvents(Array<Event> &events, double dt) {
  return detectEvents(events, dt);
}

bool
EventController::handleEvent(Array<Event> &events, Event &event) {
  doUpdate(event);
  return detectEvents(events, event);
}

bool
EventController::insert(SceneObject *so) {
  _scene_objects.insert(so);
  doInsert(so);
}
