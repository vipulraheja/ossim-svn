set(LIB_NAME ossimhdf_plugin)
MESSAGE( "************** LIBRARY SETUP FOR ossimhdf_plugin******************")

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

SET(requiredLibs)

find_package(HDF4)
IF(HDF4_FOUND)
   INCLUDE_DIRECTORIES( ${HDF4_INCLUDE_DIR} )
   SET(requiredLibs ${requiredLibs} ${HDF4_LIBRARIES} )
ELSE(HDF4_FOUND)
   MESSAGE(FATAL_ERROR "Could not find hdf4")
ENDIF(HDF4_FOUND)

FILE(GLOB_RECURSE OSSIMPLUGIN_SRCS *.cpp)
FILE(GLOB_RECURSE OSSIMPLUGIN_HEADERS *.h)

OSSIM_LINK_LIBRARY(${LIB_NAME}
                   COMPONENT_NAME ossim TYPE "${OSSIM_USER_DEFINED_DYNAMIC_OR_STATIC}"
		   LIBRARIES ${OSSIM_LIBRARY} ${requiredLibs}
                   HEADERS "${OSSIMPLUGIN_HEADERS}"
		   SOURCE_FILES "${OSSIMPLUGIN_SRCS}"
                   INSTALL_LIB)

MESSAGE( STATUS "HDF Plugin required libs          = ${requiredLibs}" )
