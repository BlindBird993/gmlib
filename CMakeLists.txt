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

# Global name of the project
project(GMlib)

# Version
set(VERSION_MAJOR 0)
set(VERSION_MINOR 3)
set(VERSiON_PATCH 0)

option( GM_GL_EXTENSION "GL Extensions" ON )

# Pass compiler options
if( GM_GL_EXTENSION )

  include_directories( /usr/include/GL)
endif( GM_GL_EXTENSION )

# Process files in the source directory
add_subdirectory(src)
