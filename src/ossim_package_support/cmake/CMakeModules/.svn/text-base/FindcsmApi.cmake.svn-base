# - Find csmApi library
# Find the native csmApi includes and library
# This module defines
#  CSMAPI_INCLUDE_DIRS, where to find cam api headers, etc.
#  CSMAPI_LIBRARIES, libraries to link against to use csmApi.
#  CSMAPI_FOUND, If false, do not try to use csmApi.
# also defined, but not for general use are
#  CSMAPI_LIBRARY, where to find the CSMAPI library.
SET(CMAKE_FIND_FRAMEWORK "LAST")
FIND_PATH(CSMAPI_INCLUDE_DIRS SMManager.h
	HINTS 
		$ENV{OSSIM_DEV_HOME}/csmApi/include
		$ENV{OSSIM_DEV_HOME}/csmApi/include/TSM
		$ENV{OSSIM_DEV_HOME}/csmApi/lib
		$ENV{OSSIM_INSTALL_PREFIX}/include
	PATHS
		$ENV{OSSIM_DEV_HOME}/csmApi/include
		$ENV{OSSIM_DEV_HOME}/csmApi/include/TSM
		$ENV{OSSIM_INSTALL_PREFIX}
    	PATH_SUFFIXES 
		lib
		include
)

SET(CSMAPI_NAMES ${CSMAPI_NAMES} csmApi libcsmApi)
FIND_LIBRARY(CSMAPI_LIBRARY NAMES ${CSMAPI_NAMES}
	HINTS 
		$ENV{OSSIM_DEV_HOME}/csmApi/lib
	PATHS
		$ENV{OSSIM_DEV_HOME}/csmApi/lib
		$ENV{OSSIM_INSTALL_PREFIX}
    	PATH_SUFFIXES 
		lib
		Frameworks
)

# handle the QUIETLY and REQUIRED arguments and set CSMAPI_FOUND to TRUE if 
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(CSMAPI  DEFAULT_MSG  CSMAPI_LIBRARY  CSMAPI_INCLUDE_DIR)

IF(CSMAPI_FOUND)
  SET( CSMAPI_LIBRARIES ${CSMAPI_LIBRARY} )
  SET(CSMAPI_INCLUDE_DIRS ${CSMAPI_INCLUDE_DIRS} ${CSMAPI_INCLUDE_DIRS}/TSM)
ENDIF(CSMAPI_FOUND)
MARK_AS_ADVANCED(CSMAPI_INCLUDE_DIRS CSMAPI_LIBRARY)
