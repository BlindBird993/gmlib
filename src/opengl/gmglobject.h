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
#include <core/utils/gmutils.h>

// stl
#include <functional>
#include <list>
#include <cassert>


namespace GMlib {

namespace GL {

namespace Private {





  struct GLObjectInfo {
    std::string     name;
    GLuint          id;
    unsigned int    counter;

    GLObjectInfo() {

      id      = 0;
      counter = 1;
    }

    void            increment() { ++counter; }
    void            decrement() { --counter; }
  };



  template <typename T>
  struct InfoHasName : std::binary_function<T,std::string,bool> {
    bool operator () ( const T& info, const std::string& name) const { return info.name == name; }
  };

  template <typename T>
  struct InfoHasId : std::binary_function<T,GLuint,bool> {
    bool operator() ( const T& info, GLuint id ) const { return info.id == id; }
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
    typedef typename std::list<T>::const_iterator InfoIterC;
    typedef typename std::list<T>::iterator       InfoIter;

  public:

    explicit GLObject();
    GLObject( const GLObject& copy );
    virtual ~GLObject();

  public:
    void                    bind() const;
    void                    unbind() const;

    GLuint                  getId() const;
    InfoIterC               getInfoIter() const;

    bool                    isValid() const;

    GLObject&               operator = ( const GLObject& obj );

    void                    acquire( const std::string&name );

  protected:
    void                    createObject( const T& info );
    void                    destroyObject();

    /* safe-bind */
    GLuint                  safeBind() const;
    void                    safeUnbind( GLuint id ) const;

  private:
    InfoIter                _info_iter;
    bool                    _is_valid;

    bool                    copy( const GLObject<T>& other );

    /* pure virtual functions */
    virtual GLuint          getCurrentBoundId() const = 0;
    virtual void            doBind( GLuint id ) const = 0;
    virtual GLuint          doGenerate() const = 0;
    virtual void            doDelete( GLuint id ) const = 0;


  // Backend
  private:
    static std::list<T>     _data;      // List as internal data structure as it's
                                        // iterators is not invalidated on insert/remove

    InfoIter                add( const T& info );
    void                    decrement( InfoIter itr );
    bool                    exists( const std::string& name ) const;
    InfoIter                get( const std::string& name ) const;

    const std::string&      getName( GLuint id ) const;

  }; // END class GLObject










  template <typename T>
  GLObject<T>::GLObject() : _is_valid(0) {}

  template <typename T>
  GLObject<T>::GLObject(const GLObject& other) {

    copy(other);
  }

  template <typename T>
  GLObject<T>::~GLObject() {}

  template <typename T>
  bool GLObject<T>::copy(const GLObject<T>& other) {

    // clean up this
    if( isValid() )
      this->decrement( _info_iter );

    // check and assign other
    _is_valid = other.isValid();
    if( !_is_valid ) return false;

    // copy
    _info_iter = other._info_iter;
    _info_iter->increment();
    return true;
  }

  template <typename T>
  void GLObject<T>::createObject(const T &new_info) {

    // if exists; fetch existing
    if( new_info.name.length() > 0 && this->exists(new_info.name) ) {

      _is_valid = false;
    }
    // else; generate and add new
    else {

      T info = new_info;
      info.id = doGenerate();
      assert( info.id != 0 );

      _info_iter = this->add(info);
      _is_valid = true;
    }

    // Check wether valid. Should allways be valid
    assert(_is_valid);
  }

  template <typename T>
  void GLObject<T>::destroyObject() {

    if( !isValid() ) return;

    if( getInfoIter()->counter == 1 )
      doDelete( getInfoIter()->id );

    this->decrement( _info_iter );
  }

  template <typename T>
  GLuint GLObject<T>::getId() const {

    return this->getInfoIter()->id;
  }

  template <typename T>
  typename GLObject<T>::InfoIterC GLObject<T>::getInfoIter() const {

    return _info_iter;
  }

  template <typename T>
  bool GLObject<T>::isValid() const {

    return _is_valid;
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
  void GLObject<T>::acquire(const std::string& name) {

    if( name.length() > 0 && this->exists(name) ) {

      // clean up this
      if( isValid() )
        this->decrement( _info_iter );

      // get new
      _info_iter = this->get(name);
      _info_iter->increment();
    }
    // Else mark as invalid (should not happen)
    else {

      _is_valid = false;
    }

    assert(_is_valid);
  }

  template <typename T>
  inline
  void GLObject<T>::bind() const { doBind(getId()); }

  template <typename T>
  inline
  void GLObject<T>::unbind() const { doBind(0); }

  template <typename T>
  typename GLObject<T>::InfoIter GLObject<T>::add(const T &info) {

    return _data.insert( _data.end(), info );
  }

  template <typename T>
  void GLObject<T>::decrement(InfoIter itr) {

    itr->decrement();
  }

  template <typename T>
  bool GLObject<T>::exists(const std::string& name) const {

    typename std::list<T>::iterator itr =
        std::find_if( _data.begin(), _data.end(),
                      std::bind2nd( InfoHasName<T>(), name ) );
    return itr != _data.end();
  }

  template <typename T>
  typename GLObject<T>::InfoIter GLObject<T>::get(const std::string& name) const {

    typename std::list<T>::iterator itr =
        std::find_if( _data.begin(), _data.end(),
                      std::bind2nd( InfoHasName<T>(), name) );
    return itr != _data.end() ? itr : InfoIter(0x0);
  }

  template <typename T>
  const std::string& GLObject<T>::getName( GLuint id ) const {

    typename std::list<T>::const_iterator itr =
        std::find_if( _data.begin(), _data.end(),
                      std::bind2nd( InfoHasId<T>(), id) );
    return itr != _data.end() ? (*itr).name : "";
  }

} // END namespace Private

} // END namespace GL

} // END namespace GMlib



#endif // __gm_OPENGL_GLOBJECT_H__
