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


#ifndef __gm_OPENGL_RENDERBUFFEROBJECT_H__
#define __gm_OPENGL_RENDERBUFFEROBJECT_H__


#include "gmglobject.h"


namespace GMlib {

namespace GL {

  namespace Private {
    struct RBOInfo : public GLObjectInfo {};
  }


  class RenderbufferObject : public Private::GLObject<Private::RBOInfo> {
  public:
    explicit RenderbufferObject();
    ~RenderbufferObject();

    void                    create();
    void                    create( const std::string& name );

    void                    renderbufferStorage( GLenum internal_format, GLsizei width, GLsizei height ) const;

  private:
    /* pure-virtual functions from Object */
    virtual GLuint          getCurrentBoundId() const;
    virtual void            doBind( GLuint id ) const;

    virtual GLuint          doGenerate() const;
    virtual void            doDelete(GLuint id) const;

  }; // END class RenderbufferObject


} // END namespace GL

} // END namespace GMlib


#endif // __gm_OPENGL_RENDERBUFFEROBJECT_H__