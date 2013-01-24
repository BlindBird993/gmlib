#include "gmeventmanager.h"

#include <assert.h>
#include "gmevent.h"

using namespace GMlib;

EventManager::EventManager() {
}

EventManager::~EventManager() {
}

bool
EventManager::processEvents(double dt) {
  clearEvents();
  for (int i=0; i < _event_controllers.size(); i++) {
    _event_controllers[i]->getEvents(_events, dt);
  }

  sortEvents();
  removeDuplicateEvents();

  while ( !_events.empty() ) {
    Event& c = _events.front();
    for (int i=0; i < _event_controllers.size(); i++) {
      _event_controllers[i]->handleEvent(_events, c);
    }
    _events.remove(c);
    sortEvents();
    removeDuplicateEvents();
  }
}

bool
EventManager::registerController(EventController *controller) {
  return _event_controllers.insert(controller);
}

void
EventManager::clearEvents() {
  _events.resetSize();
}

Event&
EventManager::firstEvent() {
  assert(_events.size());
  return _events.front();
}

void
EventManager::removeDuplicateEvents() {
}

void
EventManager::sortEvents() {
  if (!_events.isSorted())
    _events.sort();
}
