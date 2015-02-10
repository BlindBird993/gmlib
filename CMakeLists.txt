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
cmake_minimum_required(VERSION 3.0)

# Nice name for the IDEs
project(GMlib VERSION 0.5)

# Extra CMake modules
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/" )

# Include some cmake utils
include(cmake/utils.cmake)
GM_INIT()





####### TEMP !!!!!!!!!!! TMP
#add_custom_target( ECMake SOURCES ecmake/enhanced.cmake )
add_subdirectory(cmake)
####### TEMP !!!!!!!!!!! TMP





# Options
option( GM_STREAM "Enable output stream operators for core types." ON )

# Developer/debug options
option( GM_DEVELOPER_MODE "Set gmlib in developer mode" OFF )
#option( GM_DEBUG "Enable internal debugging, assertions, etc." FALSE )
option( GM_DEBUG_OPGNGL "Enable opengl debug. OpenGL function calls are safe called." ON )
option( GM_TESTING "Create unit tests." OFF )

# API documentation options
#option( GM_DOXYGEN "Create build target for doxygen documentation." FALSE )



#################
## Developer Mode
if(GM_DEVELOPER_MODE)

  ##########
  ## TESTING
  if(GM_TESTING)
    message("Finding GTest")
    find_package(GTest REQUIRED)
    if(GTEST_FOUND)
      include_directories(${GTEST_INCLUDE_DIRS})
      message("GTest include dir: ${GTEST_INCLUDE_DIRS}")
      enable_testing()
    else(GTEST_FOUND)
      message(WARNING "GTest NOT found: Unittests disabled")
      message(WARNING "GTest include dir: ${GTEST_INCLUDE_DIRS}")
      set(GM_TESTING FALSE)
    endif(GTEST_FOUND)

  endif(GM_TESTING)

  if(GM_DEBUG_OPENGL)
    addDefinitions( GM_GL_DEBUG )
  endif(GM_DEBUG_OPENGL)

endif(GM_DEVELOPER_MODE)

##########################
# Add GM_STREAM definition
if(GM_STREAM)
  GM_ADD_DEFINITION( GM_STREAM )
  add_definitions(-DGM_STREAM)
  message("GMStream enabled")
endif(GM_STREAM)

##########################################
# Build shared libs instead of static libs
option( GM_BUILD_SHARED "Build shared libs instead of static libs." TRUE )
if(GM_BUILD_SHARED)
  message( "GMlib: Building shared libs!" )
else(GM_BUILD_SHARED)
  message( "GMlib: Building static libs!" )
endif(GM_BUILD_SHARED)

################################################
# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
    "MinSizeRel" "RelWithDebInfo")
endif()












set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" )






# Add modules directory
add_subdirectory(modules)






#message( "custom config: ${GM_CUSTOM_CONFIG}" )

GM_JOIN( "${GM_CUSTOM_CONFIG}" "\n" VAR_CUSTOM_CONFIG )


#foreach( TARGET ${GM_MODULE_TARGETS} )
##  get_target_property( TARGET_LOC ${TARGET} ${CMAKE_BUILD_TYPE}_LOCATION )
##  set( TARGET_LOC $<TARGET_FILE:${TARGET}>)
#  message( "target: ${TARGET}, LOC: ${TARGET_LOC}"  )
#endforeach()


set( GM_DEFINITIONS_STR "" )
foreach( DEFINITION ${GM_DEFINITIONS} )
  set( GM_DEFINITIONS_STR "-D${DEFINITION} ${GM_DEFINITIONS_STR}" )
endforeach()
set( VAR_DEFINITIONS "set( ${PROJECT_NAME}_DEFINITIONS ${GM_DEFINITIONS_STR})" )

GM_JOIN( "${GM_MODULE_TARGETS}" " " VAR_MODULE_TARGETS )

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/cmake/${PROJECT_NAME}-${PROJECT_VERSION}/${PROJECT_NAME}ConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY ExactVersion
)

set(INCLUDE_INSTALL_DIR ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(SYSCONFIG_INSTALL_DIR ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
configure_package_config_file(
  ${CMAKE_SOURCE_DIR}/cmake/common/config.cmake.in
  ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/cmake/${PROJECT_NAME}-${PROJECT_VERSION}/${PROJECT_NAME}Config.cmake
  INSTALL_DESTINATION ${CMAKE_LIBRARY_PATH}/GMlib/cmake
  PATH_VARS INCLUDE_INSTALL_DIR SYSCONFIG_INSTALL_DIR
)
























#set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/" )

#########################
## Build options

## Core types stream operators
#option( GMLIB_STREAM "Enable output stream operators for core types." TRUE )
#option( GMLIB_DEBUG "Enable internal debugging, assertions, etc." FALSE )
#option( GMLIB_OGL_DEBUG "Enable opengl debug. OpenGL function calls are safe called." FALSE )

## Open CL options
#option( GMLIB_OPENCL "Enable building of OpenCL dependent modules." FALSE )
#if( GMLIB_OPENCL )
#  set( OPENCL_ENABLED TRUE )
#endif()

## Set a default build type if none was specified
#if(NOT CMAKE_BUILD_TYPE)
#  message(STATUS "Setting build type to 'Release' as none was specified.")
#  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
#  # Set the possible values of build type for cmake-gui
#  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
#    "MinSizeRel" "RelWithDebInfo")
#endif()

## Build shared libs instead of static libs
#option( GMLIB_SHARED_LIBS "Build shared libs instead of static libs." TRUE )
#if( GMLIB_SHARED_LIBS )
#  set( BUILD_SHARED_LIBS TRUE )
#  message( "GMlib: Building shared libs!" )
#else()
#  set( BUILD_SHARED_LIBS FALSE )
#  message( "GMlib: Building static libs!" )
#endif()

## Build documentation
#option( GMLIB_DOXYGEN "Create build target for doxygen documentation." FALSE )

## Turn on unit-test creation
#option( GMLIB_TEST "Create unit tests." FALSE )

## Select BLAS implementation
#set(GMLIB_BLAS NONE CACHE STRING "Choose the type of BLAS implementation.")
#set_property(CACHE GMLIB_BLAS PROPERTY STRINGS "NONE" "CBLAS" "OpenBLAS" "ACML" "MKL" "APPML" "CuBLAS" "ViennaCL")

###############################
## EnhancedCMake: Setup && Load
#include( ecmake/enhanced.cmake )
#setupEnhancedCMake( ${CMAKE_SOURCE_DIR}/ecmake )

## Setup library - name and version [major,minor,patch]
#setupLibrary( GMlib 0 4 0 )

## add GM_STREAM definition
#if( GMLIB_STREAM )
#  addDefinitions( GM_STREAM )
#endif()

## add GM_OPENGL_DEBUG definition
#if(GMLIB_OGL_DEBUG)
#  addDefinitions( GM_GL_DEBUG )
#endif(GMLIB_OGL_DEBUG)

############
## CXX Flags
##set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic -Werror -fopenmp")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

##############################
## Find 3rd party dependencies

## Find OpenGL
#find_package(OpenGL REQUIRED)
#if( OPENGL_FOUND )
#  foreach(OPENGL_INCLUDE_DIR ${OPENGL_INCLUDE_DIRS})
#    set(OPENGL_INCLUDE_DIRS_CONC "${OPENGL_INCLUDE_DIRS_CONC}\ \"${OPENGL_INCLUDE_DIR}\"")
#  endforeach(OPENGL_INCLUDE_DIR)
#  foreach(OPENGL_LIBRARY ${OPENGL_LIBRARIES})
#    set(OPENGL_LIBRARIES_CONC "${OPENGL_LIBRARIES_CONC}\ \"${OPENGL_LIBRARY}\"")
#  endforeach(OPENGL_LIBRARY)
#  addCustomConfigLine( "set(OPENGL_FOUND ${OPENGL_FOUND})" )
#  addCustomConfigLine( "set(OPENGL_INCLUDE_DIRS${OPENGL_INCLUDE_DIRS_CONC})" )
#  addCustomConfigLine( "set(OPENGL_LIBRARIES${OPENGL_LIBRARIES_CONC})" )
#endif( OPENGL_FOUND )

## Find GLEW package (local package)
#find_package(Glew)
#if( GLEW_FOUND )
#  foreach(GLEW_INCLUDE_DIR ${GLEW_INCLUDE_DIRS})
#    set(GLEW_INCLUDE_DIRS_CONC "${GLEW_INCLUDE_DIRS_CONC}\ \"${GLEW_INCLUDE_DIR}\"")
#  endforeach(GLEW_INCLUDE_DIR)
#  foreach(GLEW_LIBRARY ${GLEW_LIBRARIES})
#    set(GLEW_LIBRARIES_CONC "${GLEW_LIBRARIES_CONC}\ \"${GLEW_LIBRARY}\"")
#  endforeach(GLEW_LIBRARY)
#  addCustomConfigLine( "set(GLEW_FOUND ${GLEW_FOUND})" )
#  addCustomConfigLine( "set(GLEW_INCLUDE_DIRS${GLEW_INCLUDE_DIRS_CONC})" )
#  addCustomConfigLine( "set(GLEW_LIBRARIES${GLEW_LIBRARIES_CONC})" )
#  include_directories(${GLEW_INCLUDE_DIRS})
#endif( GLEW_FOUND )

## Find OpenCL
#if( OPENCL_ENABLED )

#  include( cmake/modules/findopencl/FindOpenCL.cmake)
#  set( OPENCL_ENABLED ${OPENCL_FOUND} )

#  if( OPENCL_ENABLED )
#    addCustomConfigLine( "set(OPENCL_FOUND ${OPENCL_FOUND})" )
#    addCustomConfigLine( "set(OPENCL_INCLUDE_DIRS ${OPENCL_INCLUDE_DIRS})" )
#    addCustomConfigLine( "set(OPENCL_LIBRARIES ${OPENCL_LIBRARIES})" )
#    include_directories(${OPENCL_INCLUDE_DIRS})
#  endif()
#endif()

## Find BLAS library
#message("Selected BLAS configuration: " ${GMLIB_BLAS})
#unset(BLAS_FOUND)
#if(GMLIB_BLAS STREQUAL "OpenBLAS")
#  find_package(OpenBLAS REQUIRED)
#  if(OPENBLAS_FOUND)
#    set(BLAS_FOUND ${OPENBLAS_FOUND})
#  set(BLAS_INCLUDE_DIRS ${OPENBLAS_INCLUDE_DIRS})
#  set(BLAS_LIBRARIES ${OPENBLAS_LIBRARIES})
#  endif(OPENBLAS_FOUND)
#elseif(GMLIB_BLAS STREQUAL "MKL")
#  find_package(MKL REQUIRED)
#  if(MKL_FOUND)
#    set(BLAS_FOUND ${MKL_FOUND})
#  set(BLAS_INCLUDE_DIRS ${MKL_INCLUDE_DIRS})
#  set(BLAS_LIBRARIES ${MKL_LIBRARIES})
#  endif(MKL_FOUND)
#elseif(GMLIB_BLAS STREQUAL "ACML")
#  find_package(ACML REQUIRED)
#  if(ACML_FOUND)
#    set(BLAS_FOUND ${ACML_FOUND})
#  set(BLAS_INCLUDE_DIRS ${ACML_INCLUDE_DIRS})
#  set(BLAS_LIBRARIES ${ACML_LIBRARIES})
#  endif(ACML_FOUND)
#elseif(GMLIB_BLAS STREQUAL "APPML")
#  find_package(APPML REQUIRED)
#  if(APPML_FOUND)
#    set(BLAS_FOUND ${APPML_FOUND})
#  set(BLAS_INCLUDE_DIRS ${APPML_INCLUDE_DIRS})
#  set(BLAS_LIBRARIES ${APPML_LIBRARIES})
#  endif(APPML_FOUND)
#elseif(GMLIB_BLAS STREQUAL "CuBLAS")
#  find_package(CUDA REQUIRED)
#  if(CUDA_FOUND)
#    set(BLAS_FOUND ${CUDA_FOUND})
#  set(BLAS_INCLUDE_DIRS ${CUDA_INCLUDE_DIRS})
#  set(BLAS_LIBRARIES ${CUDA_LIBRARIES} ${CUDA_CUBLAS_LIBRARIES})
#  endif(CUDA_FOUND)
#elseif(GMLIB_BLAS STREQUAL "ViennaCL")
#  find_package(ViennaCL REQUIRED)
#  if(VIENNACL_FOUND)
#    set(BLAS_FOUND ${VIENNACL_FOUND})
#  set(BLAS_INCLUDE_DIRS ${VIENNACL_INCLUDE_DIRS})
#  set(BLAS_LIBRARIES ${VIENNACL_LIBRARIES})
#  endif(VIENNACL_FOUND)
#elseif(GMLIB_BLAS STREQUAL "CBLAS")
#  set(GMLIB_BLAS_GENERIC_LIBRARY "/usr/lib/libgenericblas.so" CACHE FILEPATH "Path to a generic CBLAS implementation")
#  set(GMLIB_BLAS_REFERENCE_DIR "${CMAKE_CURRENT_LIST_DIR}/src/core/blas")
#  if(EXISTS ${GMLIB_BLAS_GENERIC_LIBRARY})
#    set(BLAS_FOUND TRUE)
#  set(BLAS_INCLUDE_DIRS ${GMLIB_BLAS_REFERENCE_DIR})
#  set(BLAS_LIBRARIES ${GMLIB_BLAS_GENERIC_LIBRARY})
#  else(EXISTS ${GMLIB_BLAS_GENERIC_LIBRARY})
#    message(WARNING "GMLIB_BLAS_GENERIC_LIBRARY=\"${GMLIB_BLAS_GENERIC_LIBRARY}\" is not an existing file!")
#  endif(EXISTS ${GMLIB_BLAS_GENERIC_LIBRARY})
#else(GMLIB_BLAS STREQUAL "OpenBLAS") #NONE
#  set(GMLIB_BLAS NONE CACHE STRING "Choose the type of BLAS implementation." FORCE)
#endif(GMLIB_BLAS STREQUAL "OpenBLAS")

#if(BLAS_FOUND)
#  foreach(BLAS_INCLUDE_DIR ${BLAS_INCLUDE_DIRS})
#    set(BLAS_INCLUDE_DIRS_CONC "${BLAS_INCLUDE_DIRS_CONC}\ \"${BLAS_INCLUDE_DIR}\"")
#  endforeach(BLAS_INCLUDE_DIR)
#  foreach(BLAS_LIBRARY ${BLAS_LIBRARIES})
#    set(BLAS_LIBRARIES_CONC "${BLAS_LIBRARIES_CONC}\ \"${BLAS_LIBRARY}\"")
#  endforeach(BLAS_LIBRARY)
#  addCustomConfigLine( "set(BLAS_FOUND ${BLAS_FOUND})" )
#  addCustomConfigLine( "set(BLAS_INCLUDE_DIRS${BLAS_INCLUDE_DIRS_CONC})" )
#  addCustomConfigLine( "set(BLAS_LIBRARIES${BLAS_LIBRARIES_CONC})" )
#  include_directories(${BLAS_INCLUDE_DIRS})
#endif(BLAS_FOUND)
##add_definitions(-DGMLIB_BLAS=${GMLIB_BLAS})


#################################
## Create source code build rules
#setSourceRootDir(src)

############################
## BUILD GMlib documentation
#if( GMLIB_DOXYGEN )

#  ##################################
#  # Create documentation build rules
#  add_subdirectory(doc)

#endif()

##########################
## ECMake: Finalize Module
#finalizeLibrary()


#message( "Library version: " ${LIBRARY_VERSION_STR} )
