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

#include "gmobject.h"


// gmlib
#include <core/gmglobal.h>

using namespace GMlib::GL;

Object::Object() : _managed(false), _valid(false) {}

Object::Object(const std::string& name) : _managed(true), _valid(false), _name(name) {}

Object::Object(const Object& copy) { GM_UNUSED(copy) }

void Object::makeCopy(const Object &copy) {

  if( _valid && !_managed )
    getStaticIdMap()[_id]--;

  _managed  = copy._managed;
  _valid    = copy._valid;

  if( !_valid )
    return;

  _name     = copy._name;
  _id       = copy._id;

  if( !_managed )
    getStaticIdMap()[_id]++;
}

void Object::create() {

  _id = doCreate();
  _valid = _id > 0;
}

void Object::createManaged() {

  _id = doCreateManaged();
  _valid = _id > 0;
}

void Object::destroy() {

  if( _managed || !_valid )
    return;

  getStaticIdMap()[_id]--;
  if( getStaticIdMap().count(_id) <= 0 )
    doDestroy();
}

GLuint Object::getId() const {

  return _id;
}

const std::string& Object::getName() const {

  return _name;
}

bool Object::isManaged() const {

  return _managed;
}

bool Object::isValid() const {

  return _valid;
}

GLuint Object::safeBind() const {

  GLuint id = getCurrentBoundId();
  bind();
  return id;
}

void Object::safeUnbind(GLuint id) const {

  doBind(id);
}


