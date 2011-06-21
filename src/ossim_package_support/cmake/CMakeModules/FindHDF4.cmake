# - Find HDF4 library
# Find the native hdf4 includes and library
# This module defines
#  HDF4_INCLUDE_DIR, where to find tiff.h, etc.
#  HDF4_LIBRARIES, libraries to link against to use HDF4.
#  HDF4_FOUND, If false, do not try to use HDF4.
# also defined, but not for general use are
#  HDF4_LIBRARY, where to find the HDF4 library.

FIND_PATH(HDF4_INCLUDE_DIR hdf/hdf.h PATHS /usr/include /usr/local/include)

SET(HDF4_NAMES ${HDF4_NAMES} df libdf)
FIND_LIBRARY( HDF4_LIBRARY
              NAMES ${HDF4_NAMES} 
              PATHS
              /usr/lib64/hdf
              /usr/lib/hdf
              /usr/lib64
              /usr/lib
              /usr/local/lib64/hdf
              /usr/local/lib/hdf
              /usr/local/lib64
              /usr/local/lib )


# handle the QUIETLY and REQUIRED arguments and set HDF4_FOUND to TRUE if 
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(HDF4  DEFAULT_MSG  HDF4_LIBRARY  HDF4_INCLUDE_DIR)

IF(HDF4_FOUND)
  SET( HDF4_LIBRARIES ${HDF4_LIBRARY} )
ENDIF(HDF4_FOUND)

MARK_AS_ADVANCED(HDF4_INCLUDE_DIR HDF4_LIBRARY)
