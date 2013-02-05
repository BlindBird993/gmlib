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

#include "gmopencl.h"


// stl
#include <iostream>

namespace GMlib {
namespace CL {


  OpenCL* OpenCL::_instance = 0x0;



  OpenCL::OpenCL(cl_device_type device_type) {

    std::vector<cl::Platform> platforms = getPlatforms();
    if( platforms.size() ) {

      cl_context_properties properties[] =
         { CL_CONTEXT_PLATFORM, (cl_context_properties)(platforms[0])(), 0};
      _context = cl::Context( device_type,properties );
    }
  }

  OpenCL::~OpenCL() {}

  OpenCL *OpenCL::getInstance() {

    return _instance;
  }

  bool OpenCL::initialize( cl_device_type dev_type ) {

    if( _instance )
      return false;

    _instance = new OpenCL(dev_type);

    return getPlatforms().size() && _instance->getDevices().size();
  }

  std::vector<cl::Platform> OpenCL::getPlatforms() {

    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);
    return platforms;
  }

  const cl::Context &OpenCL::getContext() const {

    _context;
  }

  std::vector<cl::Device> OpenCL::getDevices() const {

    return _context.getInfo<CL_CONTEXT_DEVICES>();
  }


  bool OpenCL::createCommandQueue( const std::string &name,
                                   const cl::Device &device,
                                   cl_command_queue_properties properties) {

    if( name.empty() )
      return false;

    if( _command_queues.find(name) != _command_queues.end() )
      return false;

    cl_int error;
    _command_queues[name] = cl::CommandQueue(_context,device,properties,&error);
    return error == CL_SUCCESS;
  }

  void OpenCL::deleteCommandQueue(const std::string &name) {

    _command_queues.erase(name);
  }

  cl::CommandQueue& OpenCL::getCommandQueue(const std::string &name) {

    CommandQueueMap::iterator itr = _command_queues.find(name);
    if( itr == _command_queues.end() ) {
      static cl::CommandQueue invalid_queue;
      return invalid_queue;
    }

    return (*itr).second;
  }

  bool OpenCL::createProgram(const std::string &name) {

    if( name.empty() )
      return false;

    if( _programs.find(name) != _programs.end() )
      return false;

    _programs[name] = cl::Program();
    return true;
  }

  bool OpenCL::createProgram( const std::string &name,
                              const cl::Program::Sources &sources) {

    if( name.empty() )
      return false;

    if( _programs.find(name) != _programs.end() )
      return false;

    cl_int error;
    _programs[name] = cl::Program(_context,sources,&error);
    return error == CL_SUCCESS;
  }

  bool OpenCL::buildProgram( const std::string &name,
                             const cl::Program::Sources &sources) {

    if( _programs.find(name) == _programs.end() )
      return false;

    cl_int error;
    _programs[name] = cl::Program(_context,sources,&error);
    return error == CL_SUCCESS;
  }

  cl::Program &OpenCL::getProgram(const std::string &name) {

    ProgramMap::iterator itr = _programs.find(name);
    if( itr == _programs.end() ) {
      static cl::Program invalid_program;
      return invalid_program;
    }

    return (*itr).second;
  }

  void OpenCL::deleteProgram(const std::string &name) {

    _programs.erase(name);
  }

  cl::Kernel &OpenCL::getKernel(const std::string &program_name,
                                const std::string &kernel_name) {

    ProgramMap::iterator itr = _programs.find(program_name);
    if( itr == _programs.end() ) {
      static cl::Kernel invalid_kernel;
      return invalid_kernel;
    }

    cl_int error;
    cl::Kernel( (*itr).second, kernel_name.c_str(), &error );
  }

  bool OpenCL::createEvent(const std::string &name) {

    if( name.empty() )
      return false;

    if( _events.find(name) != _events.end() )
      return false;

    _events[name].event = cl::Event();
    _events[name].type  = EventInfo::EVENT;
  }

  bool OpenCL::createUserEvent(const std::string &name) {

    if( name.empty() )
      return false;

    if( _events.find(name) != _events.end() )
      return false;

    _events[name].event = cl::UserEvent();
    _events[name].type  = EventInfo::USER_EVENT;
  }

  void OpenCL::deleteEvent(const std::string &name) {

    _events.erase(name);
  }

  cl::Event &OpenCL::getEvent(const std::string &name) {

    EventMap::iterator itr = _events.find(name);
    if( itr == _events.end() ) {
      static cl::Event neutral_event;
      return neutral_event;
    }

    return (*itr).second.event;
  }

  OpenCL::EventInfo::TYPE OpenCL::getEventType(const std::string &name) {

    EventMap::iterator itr = _events.find(name);
    if( itr == _events.end() )
      return EventInfo::INVALID;

    return (*itr).second.type;
  }

  bool OpenCL::createBuffer(const std::string &name, cl_mem_flags flags,
                            size_t size, void *host_ptr) {

    if( name.empty() )
      return false;

    if( _memory_objs.find(name) != _memory_objs.end() )
      return false;

    cl_int error;
    _memory_objs[name].memory = cl::Buffer(_context,flags,size,host_ptr,&error);
    _memory_objs[name].type   = MemoryInfo::BUFFER;

    return error == CL_SUCCESS;
  }

  bool OpenCL::createBufferGL(const std::string &name, cl_mem_flags flags,
                              GLuint bufobj) {

    if( name.empty() )
      return false;

    if( _memory_objs.find(name) != _memory_objs.end() )
      return false;

    cl_int error;
    _memory_objs[name].memory = cl::BufferGL(_context,flags,bufobj,&error);
    _memory_objs[name].type   = MemoryInfo::BUFFER_GL;

    return error == CL_SUCCESS;
  }

  bool OpenCL::createBufferRenderGL(const std::string &name, cl_mem_flags flags,
                                    GLuint bufobj) {

    if( name.empty() )
      return false;

    if( _memory_objs.find(name) != _memory_objs.end() )
      return false;

    cl_int error;
    _memory_objs[name].memory = cl::BufferRenderGL(_context,flags,bufobj,&error);
    _memory_objs[name].type   = MemoryInfo::BUFFER_RENDER_GL;

    return error == CL_SUCCESS;
  }

  bool OpenCL::createImage2D(const std::string &name, cl_mem_flags flags,
                             cl::ImageFormat format, ::size_t width, ::size_t height,
                             size_t row_pitch, void *host_ptr) {

    if( name.empty() )
      return false;

    if( _memory_objs.find(name) != _memory_objs.end() )
      return false;

    cl_int error;
    _memory_objs[name].memory = cl::Image2D(_context,
                                         flags,format,
                                         width,height,row_pitch,
                                         host_ptr,
                                         &error);
    _memory_objs[name].type   = MemoryInfo::IMAGE_2D;

    return error == CL_SUCCESS;
  }

  bool OpenCL::createImage2DGL(const std::string &name, cl_mem_flags flags,
                               GLenum target, GLint miplevel, GLuint texobj) {

    if( name.empty() )
      return false;

    if( _memory_objs.find(name) != _memory_objs.end() )
      return false;

    cl_int error;
    _memory_objs[name].memory = cl::Image2DGL(_context,
                                         flags,target,
                                         miplevel, texobj,
                                         &error);
    _memory_objs[name].type   = MemoryInfo::IMAGE_2D_GL;

    return error == CL_SUCCESS;
  }

  bool OpenCL::createImage3D(const std::string &name, cl_mem_flags flags,
                             cl::ImageFormat format,
                             ::size_t width, ::size_t height, ::size_t depth,
                             ::size_t row_pitch, ::size_t slice_pitch,
                             void *host_ptr) {

    if( name.empty() )
      return false;

    if( _memory_objs.find(name) != _memory_objs.end() )
      return false;

    cl_int error;
    _memory_objs[name].memory = cl::Image3D(_context,
                                         flags,format,
                                         width,height,depth,
                                         row_pitch,slice_pitch,
                                         host_ptr,
                                         &error);
    _memory_objs[name].type   = MemoryInfo::IMAGE_3D;

    return error == CL_SUCCESS;
  }

  bool OpenCL::createImage3DGL(const std::string &name, cl_mem_flags flags,
                               GLenum target, GLint miplevel, GLuint texobj) {

    if( name.empty() )
      return false;

    if( _memory_objs.find(name) != _memory_objs.end() )
      return false;

    cl_int error;
    _memory_objs[name].memory = cl::Image3DGL(_context,
                                         flags,target,
                                         miplevel, texobj,
                                         &error);
    _memory_objs[name].type = MemoryInfo::IMAGE_3D_GL;

    return error == CL_SUCCESS;
  }

  void OpenCL::deleteMemory(const std::string &name) {

    _memory_objs.erase(name);
  }

  cl::Memory &OpenCL::getMemory(const std::string &name) {

    MemoryMap::iterator itr = _memory_objs.find(name);
    if( itr == _memory_objs.end() ) {
      static cl::Memory invalid_memory_object;
      return invalid_memory_object;
    }

    return (*itr).second.memory;
  }

  OpenCL::MemoryInfo::TYPE OpenCL::getMemoryType(const std::string &name) {

    MemoryMap::iterator itr = _memory_objs.find(name);
    if( itr == _memory_objs.end() )
      return MemoryInfo::INVALID;

    return (*itr).second.type;
  }

  bool OpenCL::createSampler( const std::string &name,
                              cl_bool normalized_coords,
                              cl_addressing_mode addressing_mode,
                              cl_filter_mode filter_mode) {

    if( name.empty() )
      return false;

    if( _samplers.find(name) != _samplers.end() )
      return false;

    _samplers[name] = cl::Sampler( _context, normalized_coords,
                                   addressing_mode, filter_mode );
  }

  void OpenCL::deleteSampler(const std::string &name) {

    _samplers.erase(name);
  }

  cl::Sampler &OpenCL::getSampler(const std::string &name) {

    SamplerMap::iterator itr = _samplers.find(name);
    if( itr == _samplers.end() ) {
      static cl::Sampler invalid_sampler;
      return invalid_sampler;
    }

    return (*itr).second;
  }





} // END namespace CL

} // END namespace GMlib
