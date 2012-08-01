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

#############
# Setup CMAKE

# Set internal cmake dirs
set( ICMAKE_DIR "${CMAKE_SOURCE_DIR}/cmake" )
set( ICMAKE_FUNCTION_DIR "${ICMAKE_DIR}/functions" )
set( ICMAKE_MODULE_DIR "${ICMAKE_DIR}/modules" )

include(${ICMAKE_FUNCTION_DIR}/custom_functions.cmake)
setFunctionDir( "${ICMAKE_DIR}/functions" )
setTemplateDir( "${ICMAKE_DIR}/templates" )

# Update the cmake module path to include custom modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ICMAKE_MODULE_DIR} )
#message( "CMAKE_MODULE_PATH: " ${CMAKE_MODULE_PATH} )


#############
# Setup GMlib

# Setup library - name and version [major,minor,patch]
setupLibrary( GMlib 0 4 0 )

# Find OpenGL
find_package(OpenGL REQUIRED)

# Find GLEW package (local package)
find_package(Glew REQUIRED)


########################
# GMLib library prefix

# Disable the use of the GMlib namespace
option( GMLIB_NAMESPACE "Set to TRUE to enable the <GMlib> namespace." FALSE )

# Process files in the source directory
add_subdirectory(src)


###############################
# Create cmake config directory
execute_process( COMMAND ${CMAKE_COMMAND} -E make_directory ${BUILD_CMAKE_DIR} )

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
  ${ICMAKE_DIR}/templates/config.cmake.in
  ${BUILD_CMAKE_DIR}/gmlib-config.cmake
  @ONLY
)

##############################
# Generate version config file
set( VAR_LIBRARY_VERSION ${LIBRARY_VERSION} )

configure_file(
  ${ICMAKE_DIR}/templates/config_version.cmake.in
  ${BUILD_CMAKE_DIR}/gmlib-config-version.cmake
  @ONLY
)
message( "Library version: " ${LIBRARY_VERSION_STR} )
