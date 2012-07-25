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


# Set a library prefix
macro(setLibPrefix PREFIX)
  set( LIB_PREFIX ${PREFIX} )
endmacro(setLibPrefix)

# Setup function for a module
macro(setModule NAME)
  set( MODULE ${NAME} )
  set( MODULE_TARGET ${LIB_PREFIX}${MODULE} )
  set( MODULE_DIR ${CMAKE_CURRENT_SOURCE_DIR} )
endmacro(setModule)

# Functions for adding source files and propagating these to the parent directory
macro(addHeaders)
  addSourceFiles( ${MODULE_DIR} HEADERS ${ARGV} )
endmacro(addHeaders)

macro(addTemplateSources)
  addSourceFiles( ${MODULE_DIR} TEMPLATE_HEADERS ${ARGV} )
endmacro(addTemplateSources)

macro(addSources)
  addSourceFiles( ${MODULE_DIR} SOURCES ${ARGV} )
endmacro(addSources)

macro(addSourceFiles MOD_DIR VAR)

  file( RELATIVE_PATH REL_PATH "${MOD_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" )
  foreach( SOURCE ${ARGN} )

    if( REL_PATH )
      list( APPEND ${VAR} "${REL_PATH}/${SOURCE}" )
    else()
      list( APPEND ${VAR} ${SOURCE} )
    endif()
  endforeach()

  set( ${VAR} ${${VAR}} PARENT_SCOPE )
endmacro(addSourceFiles)




# Sets "default" target build properties
function(set_default_target_properties MODULE_TARGET)

  set_target_properties( ${MODULE_TARGET} PROPERTIES DEBUG_POSTFIX _debug )
  set_target_properties( ${MODULE_TARGET} PROPERTIES LINKER_LANGUAGE CXX )
endfunction(set_default_target_properties)

# Copies generated module files and sources after module build
# Files to be compied are passed as arguments to the end of the function call
function(add_module_cpy_commands MODULE MODULE_TARGET )

  add_custom_command( TARGET ${MODULE_TARGET} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory 
      ${CMAKE_BINARY_DIR}/build/lib/gmlib/
    COMMAND ${CMAKE_COMMAND} -E copy
      ${CMAKE_BINARY_DIR}/modules/${MODULE}/lib${MODULE_TARGET}.a
      ${CMAKE_BINARY_DIR}/build/lib/gmlib/lib${MODULE_TARGET}.a
    COMMAND ${CMAKE_COMMAND} -E copy
      ${CMAKE_BINARY_DIR}/modules/${MODULE}/lib${MODULE_TARGET}.a
      ${CMAKE_BINARY_DIR}/lib/gmlib/lib${MODULE_TARGET}.a
  )
  
  foreach(f ${ARGN})
    add_custom_command( TARGET ${MODULE_TARGET} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E make_directory
        ${CMAKE_BINARY_DIR}/build/modules/${MODULE}
      COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/${f}
        ${CMAKE_BINARY_DIR}/build/modules/${MODULE}/${f}
    )
  endforeach(f)

endfunction(add_module_cpy_commands)



