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


  bool OpenCL::createCommandQueue( const std::string &name, const cl::Device &device,
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

  bool OpenCL::buildProgram(const std::string &name, const cl::Program::Sources &sources) {

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

  cl::Kernel &OpenCL::getKernel(const std::string &program_name, const std::string &kernel_name) {

    ProgramMap::iterator itr = _programs.find(program_name);
    if( itr == _programs.end() ) {
      static cl::Kernel invalid_kernel;
      return invalid_kernel;
    }

    cl_int error;
    cl::Kernel( (*itr).second, kernel_name.c_str(), &error );
  }

  bool OpenCL::createMemory(const std::string &name) {

    if( name.empty() )
      return false;

    if( _memory_objs.find(name) != _memory_objs.end() )
      return false;

    _memory_objs[name] = cl::Memory();
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

    return (*itr).second;
  }































} // END namespace CL

} // END namespace GMlib
