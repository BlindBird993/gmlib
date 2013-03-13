#
# Try to find ACML library and include path.
# Once done this will define
#
# ACML_FOUND
# ACML_INCLUDE_DIRS
# ACML_LIBRARIES
# 

option(ACML_MULTITHREAD "Multithreaded ACML")
if(ACML_MULTITHREAD)
  set(ACML_MP_SUFFIX "_mp")
else(ACML_MULTITHREAD)
  set(ACML_MP_SUFFIX "")
endif(ACML_MULTITHREAD)

IF (WIN32)
#TODO
ELSEIF(APPLE)
#TODO
ELSE (WIN32) #Linux
  unset(ACML_INCLUDE_DIR CACHE)
  unset(ACML_LIBRARY CACHE)

  file(GLOB ACML_H_DIRS "/opt/acml*/gfortran32${ACML_MP_SUFFIX}/include")
  list(GET ACML_H_DIRS 0 ACML_H_DIRS)
  if(NOT ACML_H_DIRS)
    set(ACML_H_DIRS "/usr/include")
  endif()
  FIND_PATH( ACML_INCLUDE_DIR acml.h
    ${ACML_H_DIRS}
    /usr/include
    /usr/local/include
    /opt/local/include
    DOC "The directory where acml.h resides")

  file(GLOB ACML_SO_DIRS "/opt/acml*/gfortran32${ACML_MP_SUFFIX}/lib")
  list(GET ACML_SO_DIRS 0 ACML_SO_DIRS)
  if(NOT ACML_SO_DIRS)
    set(ACML_SO_DIRS "/usr/lib")
  endif()
  FIND_LIBRARY( ACML_LIBRARY
    NAMES acml acml_mp
    PATHS
    ${ACML_SO_DIRS}
    /usr/lib64
    /usr/lib
    /usr/local/lib64
    /usr/local/lib
    /opt/local/lib
    DOC "The ACML library")
#TODO: 64 bit
ENDIF (WIN32)

set(ACML_INCLUDE_DIRS ${ACML_INCLUDE_DIR})
set(ACML_LIBRARIES ${ACML_LIBRARY})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ACML "ACML not found!" ACML_INCLUDE_DIR ACML_LIBRARY)

MARK_AS_ADVANCED( ACML_INCLUDE_DIR ACML_LIBRARY )
