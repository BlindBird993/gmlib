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


# Set name of module
project(opengl)

# Find OpenGL
find_package(OpenGL REQUIRED)
if( OPENGL_FOUND )
  foreach(OPENGL_INCLUDE_DIR ${OPENGL_INCLUDE_DIRS})
    set(OPENGL_INCLUDE_DIRS_CONC "${OPENGL_INCLUDE_DIRS_CONC}\ \"${OPENGL_INCLUDE_DIR}\"")
  endforeach(OPENGL_INCLUDE_DIR)
  foreach(OPENGL_LIBRARY ${OPENGL_LIBRARIES})
    set(OPENGL_LIBRARIES_CONC "${OPENGL_LIBRARIES_CONC}\ \"${OPENGL_LIBRARY}\"")
  endforeach(OPENGL_LIBRARY)
  GM_ADD_CUSTOM_CONFIG( "set(OPENGL_FOUND ${OPENGL_FOUND})" )
  GM_ADD_CUSTOM_CONFIG( "set(OPENGL_INCLUDE_DIRS${OPENGL_INCLUDE_DIRS_CONC})" )
  GM_ADD_CUSTOM_CONFIG( "set(OPENGL_LIBRARIES${OPENGL_LIBRARIES_CONC})" )
endif( OPENGL_FOUND )

# Find GLEW package (local package)
find_package(Glew)
if( GLEW_FOUND )
  foreach(GLEW_INCLUDE_DIR ${GLEW_INCLUDE_DIRS})
    set(GLEW_INCLUDE_DIRS_CONC "${GLEW_INCLUDE_DIRS_CONC}\ \"${GLEW_INCLUDE_DIR}\"")
  endforeach(GLEW_INCLUDE_DIR)
  foreach(GLEW_LIBRARY ${GLEW_LIBRARIES})
    set(GLEW_LIBRARIES_CONC "${GLEW_LIBRARIES_CONC}\ \"${GLEW_LIBRARY}\"")
  endforeach(GLEW_LIBRARY)

  GM_ADD_CUSTOM_CONFIG( "set(GLEW_FOUND ${GLEW_FOUND})" )
  GM_ADD_CUSTOM_CONFIG( "set(GLEW_INCLUDE_DIRS${GLEW_INCLUDE_DIRS_CONC})" )
  GM_ADD_CUSTOM_CONFIG( "set(GLEW_LIBRARIES${GLEW_LIBRARIES_CONC})" )
#  include_directories(${GLEW_INCLUDE_DIRS})
endif( GLEW_FOUND )



# Add source directory
add_subdirectory(src)

# Add unit test directory
#include_directories(src)
#add_subdirectory(tests)
