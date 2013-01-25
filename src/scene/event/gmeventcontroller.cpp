#include "gmeventcontroller.h"

using namespace GMlib;


EventController::EventController() {
}

/*!
 * \brief EventController::add
 * \param so - scene object
 *
 *  Adds a scene object to be controlled by this controller
 *
 */
bool
EventController::add(SceneObject *so) {
  _scene_objects.insert(so);
  return doInsert(so);
}

/*!
 * \brief EventController::getEvents
 * \param events - list of events
 * \param dt - delta time
 * \return Whether any events was added to the list of events
 */
bool
EventController::getEvents(Array<Event*>& events, double dt) {
  return detectEvents(events, dt);
}

/*!
 * \brief EventController::handleEvent
 * \param events - list of events
 * \param event - event to handle
 * \return Whether any events did update the scene
 */
bool
EventController::handleEvent(Array<Event*>& events, Event* event) {
  bool did_update = doUpdate(event);
  detectEvents(events, event);
  return did_update;
}

bool
EventController::doInsert(SceneObject *so) {
  //- Default does nothing
  return false;
}

bool
EventController::doUpdate(Event* event) {
  //- Default does nothing
  return false;
}
