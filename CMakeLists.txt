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


#############################
# Setup && Load EnhancedCMake
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake )
#include( ${CMAKE_SOURCE_DIR}/cmake/enhanced.cmake )
include( enhanced )
setupEnhancedCMake( ${CMAKE_SOURCE_DIR}/cmake/ )
message( "CMakeModulePath: " ${CMAKE_MODULE_PATH} )

#############
# Setup GMlib

# Setup library - name and version [major,minor,patch]
setupLibrary( GMlib 0 4 0 )



#############################
# Find 3rd party dependencies

# Find OpenGL
find_package(OpenGL REQUIRED)

# Find GLEW package (local package)
find_package(Glew REQUIRED)


################################
# Create source code build rules
add_subdirectory(src)


###############################
# Create cmake config directory
#execute_process( COMMAND ${CMAKE_COMMAND} -E make_directory ${BUILD_CMAKE_DIR} )

######################
# Generate config file
message( "Generating config file" )
file( RELATIVE_PATH INC_RELPATH ${BUILD_CMAKE_DIR} ${BUILD_INCLUDE_DIR} )
file( RELATIVE_PATH LIB_RELPATH ${BUILD_CMAKE_DIR} ${BUILD_LIB_DIR} )

set( VAR_LIBRARY ${LIBRARY_NAME} )
set( VAR_INC_RELPATH ${INC_RELPATH} )
set( VAR_LIB_RELPATH ${LIB_RELPATH} )

#list( REVERSE LIBRARY_MODULE_TARGETS )
#foreach( MODULE_TRG ${LIBRARY_MODULE_TARGETS} )
#
#  message( "Module TRG: " ${MODULE_TRG} )
#  set( VAR_LIBS ${VAR_LIBS} ${BUILD_LIB_DIR}/${LIB_RELPATH}/lib${MODULE_TRG}.a )
#endforeach()

list( REVERSE LIBRARY_MODULE_TARGETS )
foreach( MODULE_TRG ${LIBRARY_MODULE_TARGETS} )

  message( "Module TRG: " ${MODULE_TRG} )
  set( VAR_LIBS "${VAR_LIBS} -l${MODULE_TRG}" )
endforeach()


configure_file(
  ${ECMAKE_TEMPLATE_DIR}/config.cmake.in
  ${BUILD_CMAKE_DIR}/gmlib-config.cmake
  @ONLY
)

##############################
# Generate version config file
set( VAR_LIBRARY_VERSION ${LIBRARY_VERSION} )

configure_file(
  ${ECMAKE_TEMPLATE_DIR}/config_version.cmake.in
  ${BUILD_CMAKE_DIR}/gmlib-config-version.cmake
  @ONLY
)

###########################
# BUILD GMlib documentation
if( GMLIB_DOXYGEN )

  ##################################
  # Create documentation build rules
  add_subdirectory(doc)

endif()







message( "Library version: " ${LIBRARY_VERSION_STR} )
