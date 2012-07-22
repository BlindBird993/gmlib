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

########################
# GMLib library prefix
set( LIB_PREFIX "gm" )

##########################
# Include helper functions
#include(../cmake/Functions/custom_functions.cmake)

#####################
# Process each individual module

# Core
add_subdirectory(core)

# Container
#add_subdirectory(container)

# OpenGL
#add_subdirectory(opengl)

# Parametrics
#add_subdirectory(parametrics)

# SceneGraph
#add_subdirectory(scenegraph)

# SceneGraphUtils
#add_subdirectory(scenegraphutils)

# TriangleSystem
#add_subdirectory(trianglesystem)

# Utils
#add_subdirectory(utils)

