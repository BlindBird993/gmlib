#
# Try to find GLEW library and include path.
# Once done this will define
#
# GLEW_FOUND
# GLEW_INCLUDE_PATH
# GLEW_LIBRARY
# 


set( GLEW_PATH_WIN32 $ENV{PROGRAMFILES}/glew CACHE PATH "Custom GLEW PATH." )
#if( NOT CUSTOM_GLEW_PATH_WIN32 )
#  set( GLEW_PATH $ENV{PROGRAMFILES}/glew )
#else()
#  set( GLEW_PATH ${CUSTOM_GLEW_PATH_WIN32} )
#endif()


IF (WIN32)
  FIND_PATH( GLEW_INCLUDE_PATH GL/glew.h
    ${GLEW_PATH_WIN32}/include
    DOC "The directory where GL/glew.h resides"
    NO_DEFAULT_PATH
    )
  FIND_LIBRARY( GLEW_LIBRARY
    NAMES glew GLEW glew32 glew32s
    PATHS
    ${GLEW_PATH_WIN32}/lib
    DOC "The GLEW library"
    NO_DEFAULT_PATH
    )
ELSE (WIN32)
  FIND_PATH( GLEW_INCLUDE_PATH GL/glew.h
    /usr/include
    /usr/local/include
    /opt/local/include
    DOC "The directory where GL/glew.h resides")
  FIND_LIBRARY( GLEW_LIBRARY
    NAMES GLEW glew
    PATHS
    /usr/lib64
    /usr/lib
    /usr/local/lib64
    /usr/local/lib
    /opt/local/lib
    DOC "The GLEW library")
ENDIF (WIN32)

IF (GLEW_INCLUDE_PATH)
  SET( GLEW_FOUND 1 CACHE STRING "Set to 1 if GLEW is found, 0 otherwise")
ELSE (GLEW_INCLUDE_PATH)
  SET( GLEW_FOUND 0 CACHE STRING "Set to 1 if GLEW is found, 0 otherwise")
ENDIF (GLEW_INCLUDE_PATH)

MARK_AS_ADVANCED( GLEW_FOUND )
