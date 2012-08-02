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

# Set local cmake dir: where on could find custom functions, modules, templates, etc.
macro(setupEnhancedCMake ENHANCED_CMAKE_PATH)

  # Set EnhancedCMake Root Path
  if( ENHANCED_CMAKE_PATH )
    set( ENHANCED_CMAKE_PATH )
  else()
    get_filename_component( ENHANCED_CMAKE_PATH ${CMAKE_CURRENT_LIST_FILE} PATH )
  endif()
  message( "Enahanced CMake Path: " ${ENHANCED_CMAKE_PATH} )

  # Set EnhancedCmake paths
  set( ECMAKE_MODULE_DIR "${ENHANCED_CMAKE_PATH}/modules" )
  set( ECMAKE_TEMPLATE_DIR "${ENHANCED_CMAKE_PATH}/templates" )

  # Update CMake module path to include the EnhancedCMake module path
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECMAKE_MODULE_DIR} )

endmacro(setupEnhancedCMake)

# JOIN function to join lists
# ref: Andrey Kamaev - stackoverflow.com
# http://stackoverflow.com/questions/7172670/best-shortest-way-to-join-a-list-in-cmake
function(JOIN VALUES GLUE OUTPUT)
  string (REGEX REPLACE "([^\\]|^);" "\\1${GLUE}" _TMP_STR "${VALUES}")
  string (REGEX REPLACE "[\\](.)" "\\1" _TMP_STR "${_TMP_STR}") #fixes escaping
  set (${OUTPUT} "${_TMP_STR}" PARENT_SCOPE)
endfunction()


# Set a library prefix
macro(setLibPrefix PREFIX)
  set( LIB_PREFIX ${PREFIX} )
endmacro(setLibPrefix)

# Set a module suffix
macro(setModuleSuffix SUFFIX)
  set( MODULE_SUFFIX ${SUFFIX} )
endmacro(setModuleSuffix)

# Setup library
macro(setupLibrary NAME VERSION_MAJOR VERSION_MINOR VERSION_PATCH )

  # Clear cache
  unset( LIBRARY_MODULE_TARGETS CACHE )

  # Library name
  set( LIBRARY_NAME ${NAME} )
  string( TOLOWER ${LIBRARY_NAME} LIBRARY )
  string( TOUPPER ${LIBRARY_NAME} LIBRARY_NAME_UPPER )

  # Set library prefix
  setLibPrefix( "gm" )
  setModuleSuffix( "Module" )

  # Project name
  project( ${LIBRARY_NAME} )

  # Version
  set( LIBRARY_VERSION_MAJOR ${VERSION_MAJOR} )
  set( LIBRARY_VERSION_MINOR ${VERSION_MINOR} )
  set( LIBRARY_VERSION_PATCH ${VERSION_PATCH} )
  set( LIBRARY_VERSION ${LIBRARY_VERSION_MAJOR}.${LIBRARY_VERSION_MINOR} )
  if( LIBRARY_VERSION_PATCH )
    set( LIBRARY_VERSION ${LIBRARY_VERSION}.${LIBRARY_VERSION_PATCH} )
  endif()
  set( LIBRARY_VERSION_STR ${LIBRARY}-${LIBRARY_VERSION} )

  # Library dir, for use when dealing with build dirs
  set( LIBRARY_DIR ${LIBRARY_VERSION_STR} )

  # Namespace
  if( ${LIBRARY_NAME_UPPER}_NAMESPACE )
    set( VAR_NAMESPACE_OPEN  "namespace ${LIBRARY_NAME} {" )
    set( VAR_NAMESPACE_CLOSE "}" )
  endif()

  # Define build directories
  set( BUILD_DIR
    ${CMAKE_BINARY_DIR}/build )
  set( BUILD_INCLUDE_DIR
    ${BUILD_DIR}/include/${LIBRARY_DIR} )
  set( BUILD_LIB_DIR
    ${BUILD_DIR}/lib/${LIBRARY_DIR} )
  set( BUILD_BIN_DIR
    ${BUILD_DIR}/bin/${LIBRARY_DIR} )
  set( BUILD_CMAKE_DIR
    ${BUILD_DIR}/lib/cmake/${LIBRARY_DIR} )
  set( BUILD_TMP_DIR
    ${BUILD_DIR}/tmp )
  set( BUILD_DOC_DIR
    ${BUILD_DIR}/doc/${LIBRARY_DIR} )

  # Set output vars (THESE ARE CMAKE_VARS)
  set( LIBRARY_OUTPUT_PATH ${BUILD_LIB_DIR} )
  set( EXECUTABLE_OUTPUT_PATH ${BUILD_BIN_DIR} )
  # These vars is supposed to supercede the two previous
  # (anyways, it should result in the same bahavious)
  set( ARCHIVE_OUTPUT_DIRECTORY ${BUILD_LIB_DIR} )
  set( LIBRARY_OUTPUT_DIRECTORY ${BUILD_LIB_DIR} )
  set( RUNTIME_OUTPUT_DIRECTORY ${BUILD_BIN_DIR} )

  # If out of source dir, add build/include/{library} to include paths else add src/
  file( RELATIVE_PATH BIN_SRC_RELPATH "${CMAKE_BINARY_DIR}" "${CMAKE_SOURCE_DIR}" )
  if( BIN_SRC_RELPATH )
    include_directories(${BUILD_INCLUDE_DIR})
  else()
    include_directories(${CMAKE_SOURCE_DIR}/src)
  endif()

  message( "Lib build dir:         " ${BUILD_DIR} )
  message( "Lib build/include dir: " ${BUILD_INCLUDE_DIR} )
  message( "Lib build/lib dir:     " ${BUILD_LIB_DIR} )

  # Generate build directories
  execute_process(
    COMMAND ${CMAKE_COMMAND} -E make_directory ${BUILD_INCLUDE_DIR}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${BUILD_LIB_DIR}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${BUILD_BIN_DIR}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${BUILD_CMAKE_DIR}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${BUILD_TMP_DIR}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${BUILD_DOC_DIR}
  )

  # Set a file config/generate message
  getLibraryVersionStr( LIB_VSTR )
  set( VAR_GENERATE_MESSAGE "This file was generated by CMake for ${LIBRARY_NAME} v${LIB_VSTR}." )

endmacro(setupLibrary)

# Returns the set library version string in the form of <major.minor.patch>.
function(getLibraryVersionStr LIB_VERSION_STR)

  set( ${LIB_VERSION_STR} "${LIBRARY_VERSION_MAJOR}.${LIBRARY_VERSION_MINOR}.${LIBRARY_VERSION_PATCH}" PARENT_SCOPE )
endfunction(getLibraryVersionStr)

# Add module function (must be called from module-parent directory (CMakeFile.txt)
macro(addModule NAME)

  # Setup the module
  setupModule( ${NAME} )

  # Look for files and stuff in module directory
  add_subdirectory( ${MODULE} )




  # Finalize module
  finalizeModule()

  foreach( DEPENDENCY ${ARGN} )

    string(TOLOWER ${DEPENDENCY} DEPENDENCY_LOWER )
    getModuleTarget( ${DEPENDENCY_LOWER} DEPENDENCY_TARGET )
    message( "${MODULE_TARGET} depends on <${DEPENDENCY_TARGET}>" )
    add_dependencies( ${MODULE_TARGET} ${DEPENDENCY_TARGET} )

  endforeach()

endmacro(addModule)

# Setup function for a module
macro(setupModule NAME)

  # set vars
  set( MODULE_NAME ${NAME} )
  string( TOLOWER ${MODULE_NAME} MODULE )
  getModuleTarget( ${MODULE} MODULE_TARGET )
  set( MODULE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${MODULE} )

  message( "Module name:    " ${MODULE_NAME} )
  message( "Module:         " ${MODULE} )
  message( "Module dir:     " ${MODULE_DIR} )
  message( "Module target:  " ${MODULE_TARGET} )

  # Define build directories
  set( MODULE_BUILD_INCLUDE_DIR "${BUILD_INCLUDE_DIR}/${MODULE}" )

  # Generate module build directories
  execute_process(
    COMMAND ${CMAKE_COMMAND} -E make_directory ${MODULE_BUILD_INCLUDE_DIR}
  )

  # Module Namespace
  if( ${LIBRARY_NAME_UPPER}_MODULE_NAMESPACES )
    set( VAR_MODULE_NAMESPACE_OPEN  "namespace ${MODULE_NAME} {" )
    set( VAR_MODULE_NAMESPACE_CLOSE "}" )
  endif()

  # Clear cache
  unset( HEADERS CACHE )
  unset( SOURCES CACHE )
  unset( TEMPLATE_SOURCES CACHE )

endmacro(setupModule)

function(getModuleTarget MODULE_NAME MODULE_TARGET)
  set( ${MODULE_TARGET} ${LIB_PREFIX}${MODULE_NAME} PARENT_SCOPE )
endfunction(getModuleTarget)

# Functions for adding source files and propagating these to the parent directory
macro(addHeaders)
  addSourceFiles2( ${MODULE_DIR} HEADERS ${ARGV} )
endmacro(addHeaders)

macro(addTemplateSources)
  addSourceFiles3( ${MODULE_DIR} TEMPLATE_SOURCES ${ARGV} )
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

  set( ${VAR} ${${VAR}} CACHE INTERNAL "My cache" )
endmacro(addSourceFiles)

macro(addSourceFiles2 MOD_DIR VAR)

  file( RELATIVE_PATH REL_PATH "${MOD_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" )
  foreach( SOURCE ${ARGN} )

    # build entry (name,header,relative path) e.g.: [gmGlobal;gmGlobal.h;core]
    list( APPEND ${SOURCE} ${SOURCE} )

    string( TOLOWER ${SOURCE} SOURCE_LOWER )
    list( APPEND ${SOURCE} ${SOURCE_LOWER}.h )

    list( APPEND ${SOURCE} "RELPATH${REL_PATH}" )

    set( ${SOURCE} ${${SOURCE}} CACHE INTERNAL "My cache" )

#    message( "Entry: " ${${SOURCE}} )

    # add entry to list
    list( APPEND ${VAR} ${SOURCE} )

  endforeach()

  set( ${VAR} ${${VAR}} CACHE INTERNAL "My cache" )

endmacro(addSourceFiles2)

macro(addSourceFiles3 MOD_DIR VAR)

  file( RELATIVE_PATH REL_PATH "${MOD_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" )
  foreach( SOURCE ${ARGN} )

    # build entry (name,header,relative path) e.g.: [gmGlobal;gmGlobal.h;core]
    list( APPEND ${SOURCE} ${SOURCE} )
    list( APPEND ${SOURCE} "RELPATH${REL_PATH}" )

    set( ${SOURCE} ${${SOURCE}} CACHE INTERNAL "My cache" )

#    message( "Entry: " ${${SOURCE}} )

    # add entry to list
    list( APPEND ${VAR} ${SOURCE} )

  endforeach()

  set( ${VAR} ${${VAR}} CACHE INTERNAL "My cache" )

endmacro(addSourceFiles3)

# Function which finalizes the module by setting up linker targest
# as well as pos-process hooks
macro(finalizeModule)

  # Add files to the library
  addModuleLibrary()

  # Set target properties
  setModuleTargetProperties()

  # Add cxx header generation target
  generateModuleCXXHeaders()

  # Copy module header files to build directory if this is an out of source build
  createModuleCopyCmds()

  #######################
  # Post-build copy files
  #set( FILES_CPY ${HDRS} )
  #add_module_cpy_commands( ${MODULE} ${MODULE_TARGET} ${FILES_CPY} )

  printModuleSourceFiles()
endmacro(finalizeModule)

# Add a subdirectory inside a module
macro(addSubDirectory NAME)

  add_subdirectory( ${NAME} )

  file( RELATIVE_PATH SRC_CSRC_RELPATH "${CMAKE_SOURCE_DIR}/src" "${CMAKE_CURRENT_SOURCE_DIR}" )
  set( NEW_DIR ${BUILD_LIB_DIR}/${SRC_CSRC_RELPATH}/${NAME} )
  message( "New Dir: " ${NEW_DIR} )

  add_custom_command( TARGET ${MODULE_TARGET} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${NEW_DIR}
  )

endmacro(addSubDirectory)

# Copy module headers to build/include directory
function(createModuleCopyCmds)

  # Generate configure commands, which will create redirect headers to source files
  foreach( HDR_SET ${HEADERS} )

    list( GET ${HDR_SET} 1 HDR_FILE )
    list( GET ${HDR_SET} 2 HDR_LOC )

    extractHeaderRelPath( ${HDR_LOC} HDR_LOC_MOD )
    if( HDR_LOC_MOD )

      set( OUTFILE ${MODULE_BUILD_INCLUDE_DIR}/${HDR_LOC_MOD}/${HDR_FILE} )
      set( OUTFILE_DIR ${MODULE_BUILD_INCLUDE_DIR}/${HDR_LOC_MOD} )

      file( RELATIVE_PATH
        FILE_RELPATH
        ${MODULE_BUILD_INCLUDE_DIR}/${HDR_LOC_MOD}
        ${CMAKE_SOURCE_DIR}/src/${MODULE}/${HDR_LOC_MOD}
      )
    else()

      set( OUTFILE ${MODULE_BUILD_INCLUDE_DIR}/${HDR_FILE} )
      set( OUTFILE_DIR ${MODULE_BUILD_INCLUDE_DIR} )

      file( RELATIVE_PATH
        FILE_RELPATH
        ${MODULE_BUILD_INCLUDE_DIR}
        ${CMAKE_SOURCE_DIR}/src/${MODULE}
      )
    endif()

  endforeach()

  # Generate PRE_BUILD cmake configure script which generates redirect headers
  unset( HEADERS_TXT )
  list( APPEND HEADERS_TXT "set( VAR_GENERATE_MESSAGE \"${VAR_GENERATE_MESSAGE}\" )\n" )
  list( APPEND HEADERS_TXT "set( TEMPLATE_LOC \"${ECMAKE_TEMPLATE_DIR}/redirect_header.h.in\" )\n" )
  list( APPEND HEADERS_TXT "unset( HEADERS )\n" )
  foreach( HDR_SET ${HEADERS} )

    list( GET ${HDR_SET} 0 HDR_NAME )
    list( GET ${HDR_SET} 1 HDR_FILE )
    list( GET ${HDR_SET} 2 HDR_LOC )

    set( GET_VAR "${HDR_NAME}__apofijs" )

    extractHeaderRelPath( ${HDR_LOC} HDR_LOC_MOD )
    if( HDR_LOC_MOD )
      set( GEN_DIR "${MODULE_BUILD_INCLUDE_DIR}/${HDR_LOC_MOD}" )
      set( GEN_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/src/${MODULE}/${HDR_LOC_MOD}" )
      set( GEN_FILE "${HDR_FILE}" )
    else()
      set( GEN_DIR "${MODULE_BUILD_INCLUDE_DIR}" )
      set( GEN_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/src/${MODULE}" )
      set( GEN_FILE "${HDR_FILE}" )
    endif()

#    list( APPEND HEADERS_TXT "unset( HDR_SET )\n" )
    list( APPEND HEADERS_TXT "list( APPEND ${GET_VAR} \"${GEN_DIR}\" )\n" )
    list( APPEND HEADERS_TXT "list( APPEND ${GET_VAR} \"${GEN_INCLUDE_DIR}\" )\n" )
    list( APPEND HEADERS_TXT "list( APPEND ${GET_VAR} \"${GEN_FILE}\" )\n" )
    list( APPEND HEADERS_TXT "list( APPEND HEADERS ${GET_VAR} )\n" )
  endforeach()

  JOIN( "${HEADERS_TXT}" "" VAR_HEADERS_TXT )
#  message( "--------------------------------------------------------------------" )
#  message( "VAR_HEADERS_TXT" )
#  message( "--------------------------------------------------------------------" )
#  message( "${VAR_HEADERS_TXT}" )
#  message( "--------------------------------------------------------------------" )
  configure_file(
    ${ECMAKE_TEMPLATE_DIR}/gen_redirect_header.cmake.in
    ${BUILD_TMP_DIR}/${MODULE}_conf.cmake
    @ONLY
  )

  add_custom_command( TARGET ${MODULE_TARGET} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -P ${BUILD_TMP_DIR}/${MODULE}_conf.cmake
  )

endfunction(createModuleCopyCmds)

# Helper function for printing file info
function(printModuleSourceFiles)

  message( "\n\n\n" )

  message( "Module <" ${MODULE} "> source files" )

  message( "  Headers:" )
  foreach( HDR_ENTRY ${HEADERS} )
    message( "  - " ${HDR_ENTRY} )
    list( GET ${HDR_ENTRY} 0 CXX_HDR )
    list( GET ${HDR_ENTRY} 1 HDR_FILE )
    list( GET ${HDR_ENTRY} 2 HDR_LOC )

    extractHeaderRelPath( ${HDR_LOC} HDR_LOC_MOD )
    message( "  - " ${CXX_HDR} " (${HDR_FILE}) in \"${HDR_LOC_MOD}\"" )

  endforeach()

  message( "  Template Sources:" )
  foreach( TSRC ${TEMPLATE_SOURCES} )
    message( "  - " ${TSRC} )
  endforeach()

  message( "  Sources:" )
  foreach( SRC ${SOURCES} )
    message( "  - " ${SRC} )
  endforeach()


  message( "\n\n\n" )

endfunction(printModuleSourceFiles)

# Add module library target
function(addModuleLibrary)

  getModuleTargetHeaders( TARGET_HEADERS )
  getModuleTargetSources( TARGET_SOURCES )
  message( "Current source dir: " ${CMAKE_CURRENT_SOURCE_DIR} )
  add_library( ${MODULE_TARGET} ${TARGET_HEADERS} ${TARGET_SOURCES} )

  set( LIBRARY_MODULE_TARGETS ${LIBRARY_MODULE_TARGETS} ${MODULE_TARGET} CACHE INTERNAL "My cache" )
endfunction(addModuleLibrary)

function(getModuleTargetHeaders TARGET_HEADERS )

  unset( THEADERS )
  foreach( HDR_SET ${HEADERS} )
    list( GET ${HDR_SET} 1 HDR_FILE )
    list( GET ${HDR_SET} 2 HDR_LOC )

    extractHeaderRelPath( ${HDR_LOC} HDR_LOC_MOD )
    if( HDR_LOC_MOD )
      set( THEADER "${MODULE}/${HDR_LOC_MOD}/${HDR_FILE}" )
    else()
      set( THEADER "${MODULE}/${HDR_FILE}" )
    endif()

    message( "THEADER: ${THEADER}" )
    list( APPEND THEADERS ${THEADER} )
  endforeach()

  set( ${TARGET_HEADERS} ${THEADERS} PARENT_SCOPE )
endfunction(getModuleTargetHeaders)

function(getModuleTargetSources TARGET_SOURCES)

  unset(TSOURCES)
  foreach( SRC ${SOURCES} )

    set( TSOURCE ${MODULE}/${SRC} )
    list( APPEND TSOURCES ${TSOURCE} )
  endforeach()

  set( ${TARGET_SOURCES} ${TSOURCES} PARENT_SCOPE )
endfunction(getModuleTargetSources)

function(extractHeaderRelPath HDR_REL_PATH_ENTRY HDR_REL_PATH )
  string( SUBSTRING ${HDR_REL_PATH_ENTRY} 7 -1 REL_PATH )
  set( ${HDR_REL_PATH} ${REL_PATH} PARENT_SCOPE )
endfunction(extractHeaderRelPath)

# Sets target build properties for current module
function(setModuleTargetProperties)

  set_target_properties( ${MODULE_TARGET} PROPERTIES DEBUG_POSTFIX _debug )
  set_target_properties( ${MODULE_TARGET} PROPERTIES LINKER_LANGUAGE CXX )
endfunction(setModuleTargetProperties)


# PRE_BUILD
# Create targets which generates CXX headers
function(generateModuleCXXHeaders)

  message( "Generating Module CXX Headers" )

  # Generate MODULE CXX headers
  unset( CXX_HEADER_INCLUDES )
  foreach( HEADER_SET ${HEADERS} )

    list( GET ${HEADER_SET} 0 CXX_HDR )
    list( GET ${HEADER_SET} 1 HDR )
    list( GET ${HEADER_SET} 2 HDR_RELPATH )
    extractHeaderRelPath( ${HDR_RELPATH} HDR_RELPATH_MOD )

    set( CXX_HEADER_INCLUDE "#include \"${MODULE}/${CXX_HDR}\"\n" )
    list( APPEND CXX_HEADER_INCLUDES ${CXX_HEADER_INCLUDE} )


    # Find header relative path, to module dir
    if( HDR_RELPATH_MOD )
      set( HDR_RELPATH_FILE ${HDR_RELPATH_MOD}/${HDR} )
    else()
      set( HDR_RELPATH_FILE ${HDR} )
    endif()

    # Define header include relative path
    file( RELATIVE_PATH BIN_SRC_RELPATH "${CMAKE_BINARY_DIR}" "${CMAKE_SOURCE_DIR}" )
    if( BIN_SRC_RELPATH )
      set( HEADER_INCLUDE "#include \"${HDR_RELPATH_FILE}\"" )
    else()
      file( RELATIVE_PATH MOD_SRC_CURRENT_RELPATH "${MODULE_BUILD_INCLUDE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/${MODULE}" )
      set( HEADER_INCLUDE "#include \"${MOD_SRC_CURRENT_RELPATH}/${HDR_RELPATH_FILE}\"" )
    endif()

    # Generate individual CXX Header
    unset( VAR_HEADER_INCLUDES )
    set( VAR_HEADER_INCLUDES ${HEADER_INCLUDE} )
    configure_file(
      ${ECMAKE_TEMPLATE_DIR}/namespace_header.h.in
      ${MODULE_BUILD_INCLUDE_DIR}/${CXX_HDR}
      @ONLY
    )

  endforeach()

  # Generate module CXX Header
  unset( VAR_HEADER_INCLUDES )
  JOIN( "${CXX_HEADER_INCLUDES}" "" VAR_HEADER_INCLUDES )
  set( MODULE_CXX_HEADER_FILE "${BUILD_INCLUDE_DIR}/${LIB_PREFIX}${MODULE_NAME}${MODULE_SUFFIX}" )
  configure_file(
    ${ECMAKE_TEMPLATE_DIR}/redirect_header.h.in
    ${MODULE_CXX_HEADER_FILE}
    @ONLY
  )

endfunction(generateModuleCXXHeaders)


function(outputVarTest OUTPUT_VAR)

  set( ${OUTPUT_VAR} "test" PARENT_SCOPE )
endfunction(outputVarTest)































