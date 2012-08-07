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


#############################
# Setup && Load EnhancedCMake
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake )
#include( ${CMAKE_SOURCE_DIR}/cmake/enhanced.cmake )
include( enhanced )
setupEnhancedCMake( ${CMAKE_SOURCE_DIR}/cmake/ )
message( "CMakeModulePath: " ${CMAKE_MODULE_PATH} )

# Setup library - name and version [major,minor,patch]
setupLibrary( GMlib 0 4 0 )

# add GM_STREAM definition
if( GMLIB_STREAM )
  addDefinitions( -DGM_STREAM )
endif()

#############################
# Find 3rd party dependencies

# Find OpenGL
find_package(OpenGL REQUIRED)

# Find GLEW package (local package)
find_package(Glew REQUIRED)


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



#  add_executable(foo test/core/containers/gmarray/foo.cpp)
#  target_link_libraries(foo ${GTEST_BOTH_LIBRARIES} ${GMLIB_LIBRARIES} )

#  add_test(AllTestsInFoo ${BUILD_BIN_DIR}/foo)





message( "Library version: " ${LIBRARY_VERSION_STR} )
