# ###############################################################################
# #
# # Copyright (C) 1994 Narvik University College
# # Contact: GMlib Online Portal at http://episteme.hin.no
# #
# # This file is part of the Geometric Modeling Library, GMlib.
# #
# # GMlib is free software: you can redistribute it and/or modify
# # it under the terms of the GNU Lesser General Public License as published by
# # the Free Software Foundation, either version 3 of the License, or
# # (at your option) any later version.
# #
# # GMlib is distributed in the hope that it will be useful,
# # but WITHOUT ANY WARRANTY; without even the implied warranty of
# # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# # GNU Lesser General Public License for more details.
# #
# # You should have received a copy of the GNU Lesser General Public License
# # along with GMlib. If not, see <http://www.gnu.org/licenses/>.
# #
# ###############################################################################

# Minimum CMake version required
cmake_minimum_required(VERSION 2.8)

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/" )

########################
# Build options

# Core types stream operators
option( GMLIB_STREAM "Enable output stream operators for core types." TRUE )
option( GMLIB_OGL_DEBUG "Enable opengl debug. OpenGL function calls are safe called." FALSE )

# Open CL options
option( GMLIB_OPENCL "Enable building of OpenCL dependent modules." FALSE )
if( GMLIB_OPENCL )
  set( OPENCL_ENABLED TRUE )
endif()

# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
    "MinSizeRel" "RelWithDebInfo")
endif()

# Build shared libs instead of static libs
option( GMLIB_SHARED_LIBS "Build shared libs instead of static libs." TRUE )
if( GMLIB_SHARED_LIBS )
  set( BUILD_SHARED_LIBS TRUE )
  message( "GMlib: Building shared libs!" )
else()
  set( BUILD_SHARED_LIBS FALSE )
  message( "GMlib: Building static libs!" )
endif()

# Build documentation
option( GMLIB_DOXYGEN "Create build target for doxygen documentation." FALSE )

# Turn on unit-test creation
option( GMLIB_TEST "Create unit tests." FALSE )

# Select BLAS implementation
set(GMLIB_BLAS NONE CACHE STRING "Choose the type of BLAS implementation.")
set_property(CACHE GMLIB_BLAS PROPERTY STRINGS "NONE" "CBLAS" "OpenBLAS" "ACML" "MKL" "APPML" "CuBLAS" "ViennaCL")
add_definitions(-DGMLIB_BLAS=${GMLIB_BLAS})

##############################
# EnhancedCMake: Setup && Load
include( ecmake/enhanced.cmake )
setupEnhancedCMake( ${CMAKE_SOURCE_DIR}/ecmake )

# Setup library - name and version [major,minor,patch]
setupLibrary( GMlib 0 4 0 )

# add GM_STREAM definition
if( GMLIB_STREAM )
  addDefinitions( GM_STREAM )
endif()

# add GM_OPENGL_DEBUG definition
if( GMLIB_OGL_DEBUG )
  addDefinitions( GM_GL_DEBUG )
endif()

###########
# CXX Flags
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

#############################
# Find 3rd party dependencies

# Find OpenGL
find_package(OpenGL REQUIRED)
if( OPENGL_FOUND )
  addCustomConfigLine( "set(OPENGL_FOUND ${OPENGL_FOUND})" )
  addCustomConfigLine( "set(OPENGL_INCLUDE_DIR ${OPENGL_INCLUDE_DIR})" )
  addCustomConfigLine( "set(OPENGL_LIBRARIES ${OPENGL_LIBRARIES})" )
endif( OPENGL_FOUND )

option( CUSTOM_GLEW_PATH "Set custom GLEW dir." FALSE )
option( NO_DEFAULT_GLEW_PATHS "Don't search for GLEW in predefined & default paths." FALSE )

# Find GLEW package (local package)
include(cmake/modules/FindGlew.cmake)
#if( GLEW_FOUND )
  message( "GLEW FOUND!" )
  addCustomConfigLine( "set(GLEW_FOUND ${GLEW_FOUND})" )
  addCustomConfigLine( "set(GLEW_INCLUDE_PATH \"${GLEW_INCLUDE_PATH}\")" )
  addCustomConfigLine( "set(GLEW_LIBRARY \"${GLEW_LIBRARY}\")" )
  include_directories(${GLEW_INCLUDE_PATH})
#else( GLEW_FOUND )
#  message( "GLEW NOT FOUND!" )
#endif( GLEW_FOUND )

# Find OpenCL
if( OPENCL_ENABLED )

  include( cmake/modules/findopencl/FindOpenCL.cmake)
  set( OPENCL_ENABLED ${OPENCL_FOUND} )

  if( OPENCL_ENABLED )
    addCustomConfigLine( "set(OPENCL_FOUND ${OPENCL_FOUND})" )
    addCustomConfigLine( "set(OPENCL_INCLUDE_DIRS ${OPENCL_INCLUDE_DIRS})" )
    addCustomConfigLine( "set(OPENCL_LIBRARIES ${OPENCL_LIBRARIES})" )
    include_directories(${OPENCL_INCLUDE_DIRS})
  endif()
endif()

message("Selected BLAS configuration: " ${GMLIB_BLAS})
if(GMLIB_BLAS STREQUAL "OpenBLAS")
  # Find OpenBLAS
  find_package(OpenBLAS)
  if(OPENBLAS_FOUND)
    addCustomConfigLine( "set(OPENBLAS_FOUND ${OPENBLAS_FOUND})" )
    addCustomConfigLine( "set(OPENBLAS_INCLUDE_DIRS \"${OPENBLAS_INCLUDE_DIRS}\")" )
    addCustomConfigLine( "set(OPENBLAS_LIBRARIES \"${OPENBLAS_LIBRARIES}\")" )
    include_directories(${OPENBLAS_INCLUDE_DIRS})
  endif(OPENBLAS_FOUND)
elseif(GMLIB_BLAS STREQUAL "MKL")
  find_package(MKL)
  if(MKL_FOUND)
    addCustomConfigLine( "set(MKL_FOUND ${MKL_FOUND})" )
    addCustomConfigLine( "set(MKL_INCLUDE_DIRS \"${MKL_INCLUDE_DIRS}\")" )
    addCustomConfigLine( "set(MKL_LIBRARIES \"${MKL_LIBRARIES}\")" )
    include_directories(${MKL_INCLUDE_DIRS})
  endif()
elseif(GMLIB_BLAS STREQUAL "ACML")
  find_package(ACML)
  if(ACML_FOUND)
    addCustomConfigLine( "set(ACML_FOUND ${ACML_FOUND})" )
    addCustomConfigLine( "set(ACML_INCLUDE_DIRS \"${ACML_INCLUDE_DIRS}\")" )
    addCustomConfigLine( "set(ACML_LIBRARIES \"${ACML_LIBRARIES}\")" )
    include_directories(${ACML_INCLUDE_DIRS})
  endif(ACML_FOUND)
elseif(GMLIB_BLAS STREQUAL "APPML")
  #TODO
elseif(GMLIB_BLAS STREQUAL "CuBLAS")
  #TODO
elseif(GMLIB_BLAS STREQUAL "ViennaCL")
  #TODO
elseif(GMLIB_BLAS STREQUAL "CBLAS")
  set(GMLIB_BLAS_GENERIC_LIBRARY "/usr/lib/libgenericblas.so" CACHE FILEPATH "Path to a generic CBLAS implementation")
  if(NOT EXISTS GMLIB_BLAS_GENERIC_LIBRARY)
    message(WARNING "GMLIB_BLAS_GENERIC_LIBRARY=\"${GMLIB_BLAS_GENERIC_LIBRARY}\" is not an existing file!")
  endif(NOT EXISTS GMLIB_BLAS_GENERIC_LIBRARY)
else(GMLIB_BLAS STREQUAL "OpenBLAS") #NONE
  #TODO
endif(GMLIB_BLAS STREQUAL "OpenBLAS")


################################
# Create source code build rules
setSourceRootDir(src)

###########################
# BUILD GMlib documentation
if( GMLIB_DOXYGEN )

  ##################################
  # Create documentation build rules
  add_subdirectory(doc)

endif()

#########################
# ECMake: Finalize Module
finalizeLibrary()


message( "Library version: " ${LIBRARY_VERSION_STR} )
