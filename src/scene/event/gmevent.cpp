#include "gmevent.h"

using namespace GMlib;

Event::Event(double x) :
  _x(x) {
}

inline
double
Event::getX() const {
  return _x;
}

inline
bool
Event::operator <(const Event &v) const {
  return _x < v._x;
}

inline
bool
Event::operator ==(const Event &v) const {
  return _x == v._x;
}
