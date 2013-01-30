#include "gmeventmanager.h"

#include <assert.h>

#include "gmevent.h"
#include "gmeventcontroller.h"

using namespace GMlib;

EventManager::EventManager() {
}

EventManager::~EventManager() {
}

/*!
 * \brief EventManager::processEvents
 * \param dt - delta time
 * \return true if any events were processed.
 *
 *  The algorithm works as follows:
 *    1. Get events within dt from all event controllers
 *    2. Sort events by when they occur
 *    3. Remove any duplicates
 *    4. For all remaining events, starting with the first:
 *      a. Ask all controllers to handle the Event
 *      b. Controllers may add new events due to the handling
 *      c. Sort events
 *      d. Remove duplicates
 *
 */
bool
EventManager::processEvents(double dt) {
  bool any_handled = true;

  clearEvents();
  for (int i=0; i < _event_controllers.size(); i++) {
    _event_controllers[i]->getEvents(_events, dt);
  }

  sortEvents();
  removeDuplicateEvents();

  while ( !_events.empty() ) {
    Event* c = _events.front();
    for (int i=0; i < _event_controllers.size(); i++) {
      any_handled &= _event_controllers[i]->handleEvent(_events, c);
    }
    _events.remove(c);
    sortEvents();
    removeDuplicateEvents();
  }

  return any_handled;
}

/*!
 * \brief EventManager::registerController
 * \param controller - EventController
 * \return false if the controller is already registered
 *
 *  Add a controller to be handled by the manager.
 *
 */
bool
EventManager::registerController(EventController *controller) {
  return _event_controllers.insert(controller);
}

void
EventManager::clearEvents() {
  _events.resetSize();
}

Event*
EventManager::firstEvent() {
  assert(_events.size());
  return _events.front();
}

void
EventManager::removeDuplicateEvents() {
  _events.makeUnique();
}

void
EventManager::sortEvents() {
  if (!_events.isSorted())
    _events.sort();
}
