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

//! \file gmopencl.h


#ifndef __GM_OPENCL_GMOPENCL_H__
#define __GM_OPENCL_GMOPENCL_H__


// OpenCL
#define __CL_ENABLE_EXCEPTIONS
#include <CL/cl.hpp>

// stl
#include <string>
#include <vector>
#include <map>





namespace GMlib {

namespace CL {





  class OpenCL {
  public:
    typedef   std::map<std::string, cl::CommandQueue>     CommandQueueMap;
    typedef   std::map<std::string, cl::Program>          ProgramMap;

    struct EventInfo {
      enum TYPE {
        EVENT,
        USER_EVENT,

        INVALID
      };

      cl::Event   event;
      TYPE        type;
    };

    typedef   std::map<std::string, EventInfo>            EventMap;

    struct MemoryInfo {
      enum TYPE {
        BUFFER,
        BUFFER_GL,
        BUFFER_RENDER_GL,
        IMAGE_2D,
        IMAGE_2D_GL,
        IMAGE_3D,
        IMAGE_3D_GL,

        INVALID
      };

      cl::Memory    memory;
      TYPE          type;
    };
    typedef   std::map<std::string, MemoryInfo>           MemoryMap;

    typedef   std::map<std::string, cl::Sampler>          SamplerMap;

  public:
    static OpenCL*                        getInstance();
    static bool                           initialize(cl_device_type dev_type = CL_DEVICE_TYPE_ALL);
    // OpenCL info
    static std::vector<cl::Platform>      getPlatforms();

  private:
    OpenCL(cl_device_type device_type);
    virtual ~OpenCL();

    static OpenCL                         *_instance;


  public:

    // Error/"event" logging
    //! Log  \todo{Implement log functionality}
    const std::string&                    getLog() const;

    // Context
    const cl::Context&                    getContext() const;

    // Devices
    std::vector<cl::Device>               getDevices() const;

    // Command Queues
    bool                                  createCommandQueue( const std::string& name,
                                                              const cl::Device& device ,
                                                              cl_command_queue_properties properties = 0);
    void                                  deleteCommandQueue( const std::string& name);
    cl::CommandQueue&                     getCommandQueue( const std::string& name );

    // Program
    bool                                  createProgram( const std::string& name);
    bool                                  createProgram( const std::string& name,
                                                         const cl::Program::Sources& sources );
    bool                                  buildProgram( const std::string& name,
                                                        const cl::Program::Sources& sources );
    void                                  deleteProgram( const std::string& name );
    cl::Program&                          getProgram( const std::string& name );

    // Kernel
    cl::Kernel&                           getKernel( const std::string& program_name,
                                                     const std::string& kernel_name );

    // Event
    bool                                  createEvent( const std::string& name );
    bool                                  createUserEvent( const std::string& name );
    void                                  deleteEvent( const std::string& name );
    cl::Event&                            getEvent( const std::string& name );
    EventInfo::TYPE                       getEventType( const std::string& name );

    // Memory
    bool                                  createBuffer( const std::string& name,
                                                        cl_mem_flags flags,
                                                        ::size_t size,
                                                        void* host_ptr = 0x0);
    bool                                  createBufferGL( const std::string& name,
                                                          cl_mem_flags flags,
                                                          GLuint bufobj );
    bool                                  createBufferRenderGL( const std::string& name,
                                                                cl_mem_flags flags,
                                                                GLuint bufobj );
    bool                                  createImage2D( const std::string& name,
                                                         cl_mem_flags flags,
                                                         cl::ImageFormat format,
                                                         ::size_t width,
                                                         ::size_t height,
                                                         ::size_t row_pitch = 0,
                                                         void* host_ptr = 0x0 );
    bool                                  createImage2DGL( const std::string& name,
                                                           cl_mem_flags flags,
                                                           GLenum target,
                                                           GLint  miplevel,
                                                           GLuint texobj );
    bool                                  createImage3D( const std::string& name,
                                                         cl_mem_flags flags,
                                                         cl::ImageFormat format,
                                                         ::size_t width,
                                                         ::size_t height,
                                                         ::size_t depth,
                                                         ::size_t row_pitch = 0,
                                                         ::size_t slice_pitch = 0,
                                                         void* host_ptr = 0x0 );
    bool                                  createImage3DGL( const std::string& name,
                                                           cl_mem_flags flags,
                                                           GLenum target,
                                                           GLint  miplevel,
                                                           GLuint texobj );
    void                                  deleteMemory( const std::string& name );
    cl::Memory&                           getMemory( const std::string& name );
    MemoryInfo::TYPE                      getMemoryType( const std::string& name );

    // Sampler
    bool                                  createSampler( const std::string& name,
                                                         cl_bool normalized_coords,
                                                         cl_addressing_mode addressing_mode,
                                                         cl_filter_mode filter_mode );
    void                                  deleteSampler( const std::string& name );
    cl::Sampler&                          getSampler( const std::string& name );


  private:
    std::string         _error_log;

    cl::Context         _context;

    CommandQueueMap     _command_queues;
    ProgramMap          _programs;
    EventMap            _events;
    MemoryMap           _memory_objs;
    SamplerMap          _samplers;


  }; // END class OpenCL







  /*!
   *  \brief Base class for all "shallow" OpenCL objects
   */
  template <typename T>
  class CLObject {
  public:
    explicit CLObject();
    explicit CLObject( const std::string& name );
    explicit CLObject( const std::string& name, T& obj );
    explicit CLObject( const CLObject& copy );

    bool                    isValid() const;
    CLObject&               operator = ( const CLObject& other );

    // CL++ object access
    T                       getObject();
    const T&                getObject() const;

    // Shallow propery access
    const std::string&      getName() const;

    // OCL object access
    typename T::cl_type     operator() () const;
    typename T::cl_type&    operator() ();


  protected:
    bool                    _valid;

    // variables "managed" by the backend
    mutable T               _obj;
    mutable std::string     _name;

  }; // END class CLObject



  template <typename T>
  CLObject<T>::CLObject() : _valid(false), _obj(), _name() {}

  template <typename T>
  CLObject<T>::CLObject(const std::string &name) : _valid(false), _obj(), _name(name) {}

  template <typename T>
  CLObject<T>::CLObject(const std::string &name, T& obj) : _valid(false), _obj(obj), _name(name) {}

  template <typename T>
  inline
  const std::string& CLObject<T>::getName() const {

    return _name;
  }

  template <typename T>
  inline
  T CLObject<T>::getObject() {

    return _obj;
  }

  template <typename T>
  inline
  const T& CLObject<T>::getObject() const {

    return _obj;
  }

  template <typename T>
  inline
  bool CLObject<T>::isValid() const {

    return _valid;
  }

  template <typename T>
  inline
  typename T::cl_type CLObject<T>::operator() () const {

    return _obj();
  }

  template <typename T>
  inline
  typename T::cl_type& CLObject<T>::operator() () {

    return _obj();
  }

  template <typename T>
  inline
  CLObject<T>& CLObject<T>::operator = ( const CLObject<T>& other ) {

    _valid =  other._valid;
    _obj =    other._obj;
    _name =   other._name;
  }


} // END namespace CL

} // END namespace GMlib

#endif //__GM_OPENCL_GMOPENCL_H__
