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


#ifndef __gmFRAMEBUFFEROBJECT_H__
#define __gmFRAMEBUFFEROBJECT_H__


#include "gmopengl.h"


namespace GMlib {

namespace GL {

  class FramebufferObject {
  public:
    explicit FramebufferObject();
    explicit FramebufferObject( const std::string name );
    FramebufferObject( const FramebufferObject& copy );
    ~FramebufferObject();

    void                    bind() const;
    GLuint                  getId() const;
    std::string             getName() const;
    bool                    isValid() const;
    void                    unbind() const;

  protected:
    std::string             _name;
    GLuint                  _id;
    bool                    _valid;

  private:
    static GLuintCMap       _ids;


  }; // END class FramebufferObject


  inline
  void FramebufferObject::bind() const {

    glBindFramebuffer( GL_FRAMEBUFFER, _id );
  }

  inline
  void FramebufferObject::unbind() const {

    glBindFramebuffer( GL_FRAMEBUFFER, 0x0 );
  }

} // END namespace GL

} // END namespace GMlib


#endif // __gmFRAMEBUFFEROBJECT_H__
