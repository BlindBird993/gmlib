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


#ifndef __gm_OPENGL_OBJECT_H__
#define __gm_OPENGL_OBJECT_H__


#include "gmopengl.h"


namespace GMlib {

namespace GL {



#define GM_GLOBJECT \
  private: \
    static GLuintCMap       _ids; \
  protected: \
    GLuintCMap&             getStaticIdMap() { return _ids; } \
  public: \
    static GLuintCMap&      staticIdMap() { return _ids; } \
  private:

#define GM_GLOBJECT_CPP( CNAME ) \
  GLuintCMap CNAME::_ids;




  class Object {
  public:
    explicit Object();
    explicit Object( const std::string& name );
    Object( const Object& copy );
  protected:
    explicit Object( GLuint id );


  public:
    bool                    bind() const;
    bool                    unbind() const;

    void                    makeCopy( const Object& copy );

    const std::string&      getName() const;
    GLuint                  getId() const;

    bool                    isManaged() const;
    bool                    isValid() const;

    Object&                 operator = ( const Object& obj );

  protected:
    void                    create();
    void                    createManaged();
    void                    destroy();

    /* safe-bind */
    GLuint                  safeBind() const;
    void                    safeUnbind( GLuint id ) const;

  private:
    bool                    _managed;
    bool                    _valid;

    /* variables "managed" by the backend */
    std::string             _name;
    mutable GLuint          _id;

    /* pure virtual functions */
    virtual GLuint          getCurrentBoundId() const = 0;
    virtual void            doBind( GLuint id ) const = 0;
    virtual GLuintCMap&     getStaticIdMap() = 0;

    virtual GLuint          doCreate() const = 0;
    virtual GLuint          doCreateManaged() const = 0;
    virtual void            doDestroy() const = 0;
  }; // END class Object




  inline
  Object& Object::operator = (const Object& other) {

    if( _valid && !_managed )
      getStaticIdMap()[_id]--;

    _managed  = other._managed;
    _valid    = other._valid;

    if( !_valid )
      return (*this);

    _name     = other._name;
    _id       = other._id;

    if( !_managed )
      getStaticIdMap()[_id]++;
  }

  inline
  bool Object::bind() const { doBind(_id); }

  inline
  bool Object::unbind() const { doBind(0); }





} // END namespace GL

} // END namespace GMlib


#endif // __gm_OPENGL_OBJECT_H__
