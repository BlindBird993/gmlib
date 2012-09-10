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


########################
# Build options

# Core types stream operators
option( GMLIB_STREAM "Enable output stream operators for core types." FALSE )

# Namespace options
option( GMLIB_NAMESPACE "Set to TRUE to enable the <GMlib> namespace." FALSE )
option( GMLIB_MODULE_NAMESPACES "Set to TRUE to enable pr. module namespace." FALSE )

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
else()
  set( BUILD_SHARED_LIBS FALSE )
endif()

# Build documentation
option( GMLIB_DOXYGEN "Create build target for doxygen documentation." FALSE )

# Turn on unit-test creation
option( GMLIB_TEST "Create unit tests." FALSE )


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
if( GLEW_FOUND )
  message( "GLEW FOUND!" )
  addCustomConfigLine( "set(GLEW_FOUND ${GLEW_FOUND})" )
  addCustomConfigLine( "set(GLEW_INCLUDE_PATH \"${GLEW_INCLUDE_PATH}\")" )
  addCustomConfigLine( "set(GLEW_LIBRARY \"${GLEW_LIBRARY}\")" )
  include_directories(${GLEW_INCLUDE_PATH})
else( GLEW_FOUND )
  message( "GLEW NOT FOUND!" )
endif( GLEW_FOUND )

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
