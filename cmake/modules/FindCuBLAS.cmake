#
# Try to find OpenBLAS library and include path.
# Once done this will define
#
# CUBLAS_FOUND
# CUBLAS_INCLUDE_DIRS
# CUBLAS_LIBRARIES
# 

set(CUBLAS_64 "YES" CACHE BOOL "Use 64-bit CuBLAS implementation"	)
option(CUBLAS_64 "64-bit CuBLAS")
if(CUBLAS_64)
  set(CUBLAS_64_SUFFIX "64")
else(CUBLAS_64)
  set(CUBLAS_64_SUFFIX "")
endif(CUBLAS_64)

IF (WIN32)
#TODO
ELSEIF(APPLE)
#TODO
ELSE (WIN32)
  FIND_PATH( CUBLAS_INCLUDE_DIR cublas_v2.h
    /usr/local/cuda/include
    DOC "The directory where cublas_v2.h (and cuda_runtime.h) resides")
  FIND_LIBRARY( CUDA_LIBRARY
    NAMES cudart
    PATHS
    /usr/local/cuda/lib${CUBLAS_64_SUFFIX}
    DOC "The CUDA library")
  FIND_LIBRARY( CUBLAS_LIBRARY
    NAMES cublas
    PATHS
    /usr/local/cuda/lib${CUBLAS_64_SUFFIX}
    DOC "The CuBLAS library")
ENDIF (WIN32)

set(CUBLAS_INCLUDE_DIRS ${CUBLAS_INCLUDE_DIR})
set(CUBLAS_LIBRARIES ${CUDA_LIBRARY} ${CUBLAS_LIBRARY})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CuBLAS "CuBLAS not found!" CUBLAS_INCLUDE_DIR CUBLAS_LIBRARY)

MARK_AS_ADVANCED( CUBLAS_INCLUDE_DIR CUBLAS_LIBRARY CUDA_LIBRARY )
