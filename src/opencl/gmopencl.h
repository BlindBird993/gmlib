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
    typedef   std::map<std::string, cl::Memory>          MemoryMap;

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
    bool                                  buildProgram( const std::string& name,
                                                        const cl::Program::Sources& sources );
    void                                  deleteProgram( const std::string& name );
    cl::Program&                          getProgram( const std::string& name );

    // Kernel
    cl::Kernel&                           getKernel( const std::string& program_name,
                                                     const std::string& kernel_name );

    // Memory
    bool                                  createMemory( const std::string& name );
    void                                  deleteMemory( const std::string& name );
    cl::Memory&                           getMemory( const std::string& name );



  private:
    std::string         _error_log;

    cl::Context         _context;

    CommandQueueMap     _command_queues;
    ProgramMap          _programs;
    MemoryMap           _memory_objs;



  }; // END class OpenCL


} // END namespace CL

} // END namespace GMlib
