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


#ifndef __gm_OPENGL_GLOBJECT_H__
#define __gm_OPENGL_GLOBJECT_H__


#include "gmopengl.h"

// gmlib
#include <core/gmglobal.h>
#include <core/utils/gmutils.h>

// stl
#include <map>


namespace GMlib {

namespace GL {


  struct GLObjectInfo {
    std::string   name;
  };



  /** class GLObject gmGLObject.h <opengl/gmGLObject>
   *
   *  Base class for overbuilding of OpenGL GLObjects.
   *  Can be named. Internally identified by an id OR a name.
   *
   *  If named the internal id is invalid and vice versa
   */
  template <typename T>
  class GLObject : GMutils::DerivedFrom<T,GLObjectInfo> {
  public:
    explicit GLObject();
    explicit GLObject( const std::string& name );
    GLObject( const GLObject& copy );
    virtual ~GLObject() {}

  protected:
    explicit GLObject( GLuint id );


  public:
    bool                    bind() const;
    bool                    unbind() const;

    GLuint                  getId() const;
    const T&                getInfo() const;

    bool                    isValid() const;

    GLObject&               operator = ( const GLObject& obj );

  protected:
    void                    create( const T& info );
    void                    destroy();

    /* safe-bind */
    GLuint                  safeBind() const;
    void                    safeUnbind( GLuint id ) const;

  private:
    GLuint                  _id;
    bool                    copy( const GLObject<T>& other );

    /* pure virtual functions */
    virtual GLuint          getCurrentBoundId() const = 0;
    virtual void            doBind( GLuint id ) const = 0;
    virtual GLuint          doGenerate() const = 0;
    virtual void            doDelete( GLuint id ) const = 0;


  protected:
    class GLObjectDataPrivate {
    public:
      GLObjectDataPrivate() {}

      void                add( GLuint id, const T& info ) {
        _counters[id] = 1;
        _info[id] = info;
      }

      unsigned int        count( GLuint id ) const {

        return _counters.count(id) ? _counters.find(id)->second : 0;

      }
      const std::string&  getName( GLuint id ) const { return static_cast<GLObjectInfo>(_info[id]).name; }
      GLuint              getId( const std::string& name ) const {

        if( name.length() <= 0 ) return 0;

        typename std::map<GLuint,T>::const_iterator itr;
        for( itr = _info.begin(); itr != _info.end(); ++itr ) {

          if( static_cast<GLObjectInfo>(itr->second).name == name )
            return itr->first;
        }

        return 0;
      }
      const T&            getInfo( GLuint id ) const { return _info[id]; }

      void                inc( GLuint id ) { _counters[id]++; }
      void                dec( GLuint id ) { _counters[id]--; }

    private:
      std::map<GLuint, unsigned int>  _counters;
      mutable std::map<GLuint,T>              _info;
    };

    static GLObjectDataPrivate          _objs;

  }; // END class GLObject








  template <typename T>
  GLObject<T>::GLObject() : GMutils::DerivedFrom<T,GLObjectInfo>(), _id(0) {}

  template <typename T>
  GLObject<T>::GLObject(const std::string& name) : GMutils::DerivedFrom<T,GLObjectInfo>() {

    _id = _objs.getId(name);
    std::cout << "Using existing GLObject: " << name << " (" << _id << ")" << std::endl;
    if( _id )
      _objs.inc(_id);
  }

  template <typename T>
  GLObject<T>::GLObject(const GLObject& other) : GMutils::DerivedFrom<T,GLObjectInfo>() { copy(other); }

  template <typename T>
  GLObject<T>::GLObject(GLuint id) : _id( _objs.count(id) ? id : 0 ) {

    if(_id)
      _objs.inc(_id);
  }

  template <typename T>
  bool GLObject<T>::copy(const GLObject<T>& other) {

    // clean up this
    if( isValid() )
      _objs.dec(getId());

    // check and assign other
    if( !other.isValid() ) {
      _id = 0;
      return false;
    }
    else {

      _id   = other._id;
      _objs.inc(getId());
    }

    return true;
  }

  template <typename T>
  void GLObject<T>::create(const T &info) {

    std::cout << "Creating GLObject: " << std::endl;
    GLuint existing_id = _objs.getId(info.name);
    if( existing_id ) {

      std::cout << "  Named object exists, using existing: '" << info.name << "' (" << existing_id << ")" << std::endl;
      _id = existing_id;
      _objs.inc(_id);
      return;
    }


    _id = doGenerate();
    _objs.add(_id, info);

    std::cout << "  Adding created object: '" << info.name << "' (" << _id << ")" << std::endl;
  }

  template <typename T>
  void GLObject<T>::destroy() {

    std::cout << "Destroying GLObject: " << std::endl;

    if( !isValid() ) {

      std::cout << "  Not valid" << std::endl;
      return;
    }

    _objs.dec(_id);
    if(_objs.count(_id) <= 0)
      doDelete(_id);
  }

  template <typename T>
  GLuint GLObject<T>::getId() const {

    return _id;
  }

  template <typename T>
  const T& GLObject<T>::getInfo() const {

    static T invalid;
    return isValid() ? _objs.getInfo(_id) : invalid;
  }

  template <typename T>
  bool GLObject<T>::isValid() const {

    return _id ? _objs.count(_id) : false;
  }

  template <typename T>
  GLuint GLObject<T>::safeBind() const {

    if( !isValid() ) return 0;

    GLuint id = getCurrentBoundId();
    bind();
    return id;
  }

  template <typename T>
  void GLObject<T>::safeUnbind(GLuint id) const {

    if( !isValid() ) return;

    doBind(id);
  }





  template <typename T>
  inline
  GLObject<T>& GLObject<T>::operator = (const GLObject<T>& other) {

    copy(other);
    return *this;
  }

  template <typename T>
  inline
  bool GLObject<T>::bind() const { doBind(getId()); }

  template <typename T>
  inline
  bool GLObject<T>::unbind() const { doBind(0); }


  template <typename T>
  typename GLObject<T>::GLObjectDataPrivate GLObject<T>::_objs;

} // END namespace GL

} // END namespace GMlib



#endif // __gm_OPENGL_GLOBJECT_H__
