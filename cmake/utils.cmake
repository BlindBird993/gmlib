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



# JOIN function to join lists
# ref: Andrey Kamaev - stackoverflow.com
# http://stackoverflow.com/questions/7172670/best-shortest-way-to-join-a-list-in-cmake
FUNCTION(JOIN VALUES GLUE OUTPUT)
  string (REGEX REPLACE "([^\\]|^);" "\\1${GLUE}" _TMP_STR "${VALUES}")
  string (REGEX REPLACE "[\\](.)" "\\1" _TMP_STR "${_TMP_STR}") #fixes escaping
  set (${OUTPUT} "${_TMP_STR}" PARENT_SCOPE)
ENDFUNCTION()

FUNCTION(TOUPPERFIRST INPUT OUTPUT)
  string(SUBSTRING ${INPUT} 0 1 IN_PART0)
  string(SUBSTRING ${INPUT} 1 -1 IN_PART1)
  string(TOUPPER ${IN_PART0} IN_PART0)
  set(${OUTPUT} ${IN_PART0}${IN_PART1} PARENT_SCOPE)
ENDFUNCTION()


FUNCTION(GM_ADD_LIBRARY)
  add_library( gm${PROJECT_NAME} ${ARGN} )
ENDFUNCTION(GM_ADD_LIBRARY)

FUNCTION(GM_ADD_LIBRARY_DEPENDENCIES TARGET )
  foreach(ARG ${ARGN})
    add_dependencies( gm${TARGET} gm${ARG})
  endforeach(ARG)
ENDFUNCTION(GM_ADD_LIBRARY_DEPENDENCIES)

FUNCTION(GM_SET_DEFAULT_TARGET_PROPERTIES)

  set_target_properties( gm${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
  )
ENDFUNCTION(GM_SET_DEFAULT_TARGET_PROPERTIES)





FUNCTION(GM_TARGET_LINK_LIBRARIES)
  target_link_libraries(gm${PROJECT_NAME} ${ARGN})
ENDFUNCTION(GM_TARGET_LINK_LIBRARIES)







FUNCTION(GM_ADD_TEMPLATE_TARGET)

  add_custom_target( ${PROJECT_NAME}TemplateModuleTarget SOURCES ${ARGN} )

ENDFUNCTION(GM_ADD_TEMPLATE_TARGET)



FUNCTION(GM_ADD_HEADERS)

  # Helper vars
  set( INCLUDE_DIR "${CMAKE_BINARY_DIR}/include" )
  set( MODULE_INCLUDE_DIR "${INCLUDE_DIR}/${PROJECT_NAME}" )

  # Create include directory if it doesn't exist
  file( MAKE_DIRECTORY ${MODULE_INCLUDE_DIR} )

  foreach(ARG ${ARGN})

    get_filename_component( HEADER_DIR ${ARG} DIRECTORY )
    if(HEADER_DIR)
      file( MAKE_DIRECTORY "${MODULE_INCLUDE_DIR}/${HEADER_DIR}" )
    endif(HEADER_DIR)
#    message( "ARG: ${ARG}" )
#    message( "...: ${MODULE_INCLUDE_DIR}/${ARG}" )
    configure_file( ${ARG} "${MODULE_INCLUDE_DIR}/${ARG}" COPYONLY )

    # Extract filename without directory and longest extension
    get_filename_component(CXX_HEADER ${ARG} NAME_WE)

    # Create C++ header
    list( APPEND CXX_HEADER_INCLUDES "#include \"${PROJECT_NAME}/${CXX_HEADER}\"" )
    set( CXX_HEADER "${MODULE_INCLUDE_DIR}/${CXX_HEADER}" )
    if(GM_DEVELOPER_MODE)
      set( CONF_HEADER_INCLUDES "#include \"${CMAKE_CURRENT_SOURCE_DIR}/${ARG}\""  )
    else()
      set( CONF_HEADER_INCLUDES "#include \"${ARG}\"" )
    endif(GM_DEVELOPER_MODE)
    configure_file( ${CMAKE_SOURCE_DIR}/cmake/common/redirect_header.h.in ${CXX_HEADER} @ONLY )

  endforeach(ARG)

  TOUPPERFIRST(${PROJECT_NAME} MODULE_NAME)
  set( CXX_MODULE_HEADER "${INCLUDE_DIR}/gm${MODULE_NAME}Module" )

  JOIN( "${CXX_HEADER_INCLUDES}" "\n" CONF_HEADER_INCLUDES )
  configure_file( ${CMAKE_SOURCE_DIR}/cmake/common/redirect_header.h.in ${CXX_MODULE_HEADER} @ONLY )

ENDFUNCTION(GM_ADD_HEADERS)

FUNCTION(GM_ADD_HEADER_SOURCES)

  # Helper vars
  set( INCLUDE_DIR "${CMAKE_BINARY_DIR}/include" )
  set( MODULE_INCLUDE_DIR "${INCLUDE_DIR}/${PROJECT_NAME}" )

  # Create include directory if it doesn't exist
  file( MAKE_DIRECTORY ${MODULE_INCLUDE_DIR} )

  foreach(ARG ${ARGN})

    get_filename_component( HEADER_DIR ${ARG} DIRECTORY )
    if(HEADER_DIR)
      file( MAKE_DIRECTORY "${MODULE_INCLUDE_DIR}/${HEADER_DIR}" )
    endif(HEADER_DIR)
    configure_file( ${ARG} "${MODULE_INCLUDE_DIR}/${ARG}" COPYONLY )

    # Extract filename without directory and longest extension
    get_filename_component(CXXHEADER ${ARG} NAME_WE)
  endforeach(ARG)

ENDFUNCTION(GM_ADD_HEADER_SOURCES)
















FUNCTION(GM_ADD_TEST TEST_NAME)
  if(GM_UNITTESTS)
    add_executable(${TEST_NAME} ${TEST_NAME}.cpp)
    target_link_libraries(${TEST_NAME} ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)
    add_test( NAME ${TEST_NAME} COMMAND ${TEST_NAME})
  endif(GM_UNITTESTS)
ENDFUNCTION(GM_ADD_TEST)

FUNCTION(GM_ADD_TESTS TEST_SET_NAME)
  if(GM_UNITTESTS)
    add_executable( ${TEST_SET_NAME} ${TEST_SET_NAME}.cc )
    target_link_libraries(${TEST_SET_NAME} ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)
    gtest_add_tests( ${TEST_SET_NAME} "" ${TEST_SET_NAME}.cc )
  endif(GM_UNITTESTS)
ENDFUNCTION(GM_ADD_TESTS)









