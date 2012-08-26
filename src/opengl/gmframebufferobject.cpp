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



#include "gmframebufferobject.h"


namespace GMlib {

  GLuintCMap FramebufferObject::_ids;

  FramebufferObject::FramebufferObject() {

    _name = "";

    _id = OGL::createFbo();
    _valid = true;

    _ids[_id] = 1;
  }

  FramebufferObject::FramebufferObject(const std::string name) {

    _name = name;

    _valid = OGL::createFbo( name );
    _id = OGL::getFboId( name );

    _ids[_id] = 1;
  }

  FramebufferObject::FramebufferObject(const FramebufferObject &copy) {

    _name = copy._name;
    _id = copy._id;

    _ids[_id]++;
  }

  FramebufferObject::~FramebufferObject() {

    _ids[_id]--;
    if( _ids.count(_id) <= 0 )
      OGL::deleteFbo( _id );
  }

  GLuint FramebufferObject::getId() const {

    return _id;
  }

  std::string FramebufferObject::getName() const {

    return _name;
  }

  bool FramebufferObject::isValid() const {

    return _valid;
  }



} // END namespace GMlib
