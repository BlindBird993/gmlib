#
# Try to find ACML library and include path.
# Once done this will define
#
# ACML_FOUND
# ACML_INCLUDE_DIRS
# ACML_LIBRARIES
# 

IF (WIN32)
  find_package(OpenCL REQUIRED)
  
  set( APPML_PATH_WIN32 $ENV{PROGRAMFILES}/AMD/clAmdBlas CACHE PATH "Path to APPML." )
  
  find_path(APPML_INCLUDE_DIR clAmdBlas.h
    PATHS
	${APPML_PATH_WIN32}/include
    DOC "The directory where clAmdBlas.h resides")
  
  find_library(APPML_LIBRARY clAmdBlas
    PATHS
	${APPML_PATH_WIN32}/lib64/import
	${APPML_PATH_WIN32}/lib32/import
    DOC "The APPML library")
  
  if(APPML_INCLUDE_DIR AND APPML_LIBRARY)
    mark_as_advanced(FORCE APPML_PATH_WIN32)
  else(APPML_INCLUDE_DIR AND APPML_LIBRARY)
    mark_as_advanced(CLEAR APPML_PATH_WIN32)
  endif(APPML_INCLUDE_DIR AND APPML_LIBRARY)
ELSEIF(APPLE)
#TODO
ELSE (WIN32) #Linux
#TODO
ENDIF (WIN32)

set(APPML_INCLUDE_DIRS ${APPML_INCLUDE_DIR} ${OPENCL_INCLUDE_DIRS})
set(APPML_LIBRARIES ${APPML_LIBRARY} ${OPENCL_LIBRARIES})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(APPML "APPML not found!" APPML_LIBRARY APPML_INCLUDE_DIRS)

MARK_AS_ADVANCED( APPML_INCLUDE_DIR APPML_LIBRARY )
