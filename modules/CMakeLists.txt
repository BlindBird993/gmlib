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


GM_INIT()

include_directories(${CMAKE_BINARY_DIR}/include)


set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" )



# Core
add_subdirectory(core)

## OpenGL
add_subdirectory(opengl)
GM_ADD_LIBRARY_DEPENDENCIES(opengl core)

# Scene
add_subdirectory(scene)
GM_ADD_LIBRARY_DEPENDENCIES(scene core opengl)

# Parametrics
add_subdirectory(parametrics)     # Don't need dependecies as this is a pure template module
#GM_ADD_LIBRARY_DEPENDENCIES(parametrics core opengl scene)

# Trianglesystem
add_subdirectory(trianglesystem)  # Don't need dependecies as this is a pure template module
#GM_ADD_LIBRARY_DEPENDENCIES(trianglesystem core opengl scene)

# Stereolithography
add_subdirectory(stereolithography)
GM_ADD_LIBRARY_DEPENDENCIES(stereolithography core opengl scene)



#message( "custom config: ${GM_CUSTOM_CONFIG}" )

GM_JOIN( "${GM_CUSTOM_CONFIG}" "\n" VAR_CUSTOM_CONFIG )


#foreach( TARGET ${GM_MODULE_TARGETS} )
##  get_target_property( TARGET_LOC ${TARGET} ${CMAKE_BUILD_TYPE}_LOCATION )
##  set( TARGET_LOC $<TARGET_FILE:${TARGET}>)
#  message( "target: ${TARGET}, LOC: ${TARGET_LOC}"  )
#endforeach()


GM_JOIN( "${GM_MODULE_TARGETS}" " " VAR_MODULE_TARGETS )

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/cmake/${PROJECT_NAME}-${PROJECT_VERSION}/${PROJECT_NAME}ConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY ExactVersion
)


set(INCLUDE_INSTALL_DIR ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(SYSCONFIG_INSTALL_DIR ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
configure_package_config_file(
  ${CMAKE_SOURCE_DIR}/cmake/common/config.cmake.in
  ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/cmake/${PROJECT_NAME}-${PROJECT_VERSION}/${PROJECT_NAME}Config.cmake
  INSTALL_DESTINATION ${CMAKE_LIBRARY_PATH}/GMlib/cmake
  PATH_VARS INCLUDE_INSTALL_DIR SYSCONFIG_INSTALL_DIR
)


#################################
## Process each individual module
## addModule( ModuleName [DependModuleName 1] [DependModuleName 2] ... )

#if( GMLIB_TEST )

#  ######################
#  # Add TestUtils module
#  addModule( TestUtils )

#  # Add core module
#  addModule(Core TestUtils)

#  # Add OpenGL module
#  addModule(OpenGL TestUtils Core)

#  # Add Scene module
#  addModule(Scene TestUtils Core OpenGL)

#  # Add Parametrics module
#  addModule(Parametrics TestUtils Core OpenGL Scene)

#  # Add TringleSystem module
#  addModule(TriangleSystem TestUtils Core OpenGL Scene)

#  # Add STereoLithography module
#  addModule(StereoLithography TestUtils Core OpenGL Scene Parametrics TriangleSystem)

#  # Add Script module
#  addModule(Script TestUtils Core)

#  if( OPENCL_ENABLED )

#    # Add OpenCL module
#    addModule(OpenCL TestUtils Core)

#    # Add Wavelet module
#    addModule(Wavelet OpenCL TestUtils Core)

#  endif( OPENCL_ENABLED )

#else( GMLIB_TEST )

#  # Add core module
#  addModule(Core)

#  # Add OpenGL module
#  addModule(OpenGL Core)

#  # Add Scene module
#  addModule(Scene Core OpenGL)

#  # Add Parametrics module
#  addModule(Parametrics Core OpenGL Scene)

#  # Add TringleSystem module
#  addModule(TriangleSystem Core OpenGL Scene)

#  # Add STereoLithography module
#  addModule(StereoLithography Core OpenGL Scene Parametrics TriangleSystem)

#  # Add Script module
#  addModule(Script Core)


#  if( OPENCL_ENABLED )

#    # Add OpenCL module
#    addModule(OpenCL Core)

#    # Add Wavelet module
#    addModule(Wavelet OpenCL Core)

#  endif( OPENCL_ENABLED )

#endif( GMLIB_TEST )




