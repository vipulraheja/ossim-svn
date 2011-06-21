set(LIB_NAME ossimkakadu_plugin)
MESSAGE( "************** LIBRARY SETUP FOR ossimkakdu_plugin******************")

find_package(ossim)
find_package(OpenThreads)
find_package(TIFF)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${OPENTHREADS_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${TIFF_INCLUDE_DIR})

IF(NOT KAKADU_ROOT_SRC)
  MESSAGE(SEND_ERROR "Please pass in the KAKADU_ROOT_SRC and point it to the root source tree")
  SET(KAKADU_ROOT_SRC "" CACHE STRING "Specify the root location where the kakadu source tree is located")
ENDIF(NOT KAKADU_ROOT_SRC)

IF(NOT KAKADU_LIBRARY)
        MESSAGE(SEND_ERROR "Please pass in the KAKADU_LIBRARY and point it to the library")
	SET(KAKADU_LIBRARY "" CACHE STRING "Specify the full path to the library to link to")
ENDIF(NOT KAKADU_LIBRARY)


IF(NOT KAKADU_AUX_LIBRARY)
  MESSAGE(SEND_ERROR "Please pass in the KAKADU_AUX_LIBRARY and point it to the library")
  SET(KAKADU_AUX_LIBRARY "" CACHE STRING "Specify the full path to the library to link to")
ENDIF(NOT KAKADU_AUX_LIBRARY)

FILE(GLOB OSSIMPLUGIN_SRCS *.cpp)


FILE(GLOB OSSIMPLUGIN_HEADERS *.h)

INCLUDE_DIRECTORIES(${KAKADU_ROOT_SRC}/coresys
                    ${KAKADU_ROOT_SRC}/managed/all_includes)

MESSAGE( STATUS "KAKADU_ROOT_SRC = ${KAKADU_ROOT_SRC}")
MESSAGE( STATUS "KAKADU_LIBRARY  = ${KAKADU_LIBRARY}")
MESSAGE( STATUS "OSSIM_LIBRARIES = ${OSSIM_LIBRARIES}")

OSSIM_LINK_LIBRARY(${LIB_NAME}
                   COMPONENT_NAME ossim TYPE "${OSSIM_USER_DEFINED_DYNAMIC_OR_STATIC}"
		   LIBRARIES ${OSSIM_LIBRARIES} ${OPENTHREADS_LIBRARY}  ${KAKADU_AUX_LIBRARY} ${KAKADU_LIBRARY} ${TIFF_LIBRARY}
                   HEADERS "${OSSIMPLUGIN_HEADERS}"
		   SOURCE_FILES "${OSSIMPLUGIN_SRCS}"
                   INSTALL_LIB)
