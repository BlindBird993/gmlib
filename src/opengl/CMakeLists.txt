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

addHeaders(
  gmBufferObject
  gmFramebufferObject
  gmGLObject
  gmOpenGL
  gmOpenGLManager
  gmProgram
  gmRenderbufferObject
  gmShader
  gmTexture
)

addSources(
  gmbufferobject.cpp
  gmframebufferobject.cpp
  gmopenglmanager.cpp
  gmprogram.cpp
  gmrenderbufferobject.cpp
  gmshader.cpp
  gmtexture.cpp
)

addSubDirectory(bufferobjects)          # <bufferobjects> sub-module
addSubDirectory(glsl)                   # <glsl> sub-module
addSubDirectory(shaders)                # <shaders> sub-module
addSubDirectory(utils)                  # <utils> sub-module

moduleLinkLibrary( ${GLEW_LIBRARY} )
moduleLinkLibrary( ${OPENGL_LIBRARIES} )

addTestDir(test)
