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

# Process files in the source directory
add_subdirectory(src)
