PROJECT(ossimcore)
Message("################## Setting up OSSIM core library #########################")

IF(NOT OSSIM_BUILD_ADDITIONAL_OSSIM_DIRECTORIES)
   SET(OSSIM_BUILD_ADDITIONAL_OSSIM_DIRECTORIES "" CACHE PATH "Specify full paths separated by ; to additional OSSIM applications you wish to include into the ossim build framework.  These will have variables setup for the ossim includes" FORCE)
ENDIF(NOT OSSIM_BUILD_ADDITIONAL_OSSIM_DIRECTORIES)

IF(NOT APPLE)
  cmake_minimum_required(VERSION 2.6)
ELSE(NOT APPLE)
  cmake_minimum_required(VERSION 2.8)
ENDIF(NOT APPLE)

SET(CMAKE_MODULE_PATH "${${PROJECT_NAME}_SOURCE_DIR}/CMakeModules;${CMAKE_MODULE_PATH}")

INCLUDE(OssimVersion)
INCLUDE(OssimCommonVariables)


SET(OSSIM_SVN_REVISION_NUMBER "?")

# Expose some build options
OPTION(BUILD_OSSIM_FREETYPE_SUPPORT "Set to ON to build OSSIM with freetype support.  Use OFF to turn off freetype support." ON)

OPTION(BUILD_OSSIM_MPI_SUPPORT "Set to ON to build OSSIM with MPI support.  Use OFF to turn off MPI support." ON)

OPTION(BUILD_OSSIM_ID_SUPPORT "Set to ON to build OSSIM SVN ID support into the library.  Use OFF to turn off ID support." ON)

OPTION(BUILD_OSSIM_TEST_APPS "Set to ON to build ossim test apps.  Use OFF to disable." OFF)

###################################################################################
# Include the Utilities in the root make
###################################################################################
INCLUDE(OssimUtilities)

INCLUDE(CheckIncludeFile)
CHECK_INCLUDE_FILE("dirent.h" CMAKE_HAVE_DIRENT_H)
CHECK_INCLUDE_FILE("unistd.h" CMAKE_HAVE_UNISTD_H)
CHECK_INCLUDE_FILE("getopt.h" CMAKE_HAVE_GETOPT_H)
CHECK_INCLUDE_FILE("fcntl.h" CMAKE_HAVE_FCNTL_H)
CHECK_INCLUDE_FILE("dbmalloc.h" CMAKE_HAVE_DBMALLOC_H)
CHECK_INCLUDE_FILE("malloc.h" CMAKE_HAVE_MALLOC_H)
CHECK_INCLUDE_FILE("dlfcn.h" CMAKE_HAVE_DLFCN_H)

find_package(OpenThreads)
find_package(TIFF)
find_package(JPEG)
find_package(GEOTIFF)
find_package(ZLIB)

IF(BUILD_OSSIM_FREETYPE_SUPPORT)
find_package(Freetype)
ENDIF(BUILD_OSSIM_FREETYPE_SUPPORT)

IF(BUILD_OSSIM_MPI_SUPPORT)
find_package(MPI)
ENDIF(BUILD_OSSIM_MPI_SUPPORT)


INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${PROJECT_BINARY_DIR}/include)
INCLUDE_DIRECTORIES(${OPENTHREADS_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${TIFF_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${JPEG_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${GEOTIFF_INCLUDE_DIR})


####### Call the OSSIM macros found in OssimUtilities.cmake #######
TODAYS_DATE(OSSIM_BUILD_DATE)
GET_SVN_REVISION(OSSIM_SVN_REVISION_NUMBER)

#####################################################################################
# Call the configure files for ossimConfig and ossimVersion setup
#####################################################################################
set(OSSIM_VERSION_NUMBER "\"${OSSIM_VERSION}\"")
set(OSSIM_BUILD_DATE "\"${OSSIM_BUILD_DATE}\"")

set(OSSIM_HAS_FREETYPE 0)
set(OSSIM_HAS_LIBZ     0)
set(OSSIM_HAS_MPI      0)
set(OSSIM_HAS_GEOTIFF  0)
set(OSSIM_ID_ENABLED   1)

IF(NOT BUILD_OSSIM_ID_SUPPORT)
   set(OSSIM_ID_ENABLED 0)
ENDIF(NOT BUILD_OSSIM_ID_SUPPORT)

IF(GEOTIFF_FOUND)
   set(OSSIM_HAS_GEOTIFF 1)
ENDIF(GEOTIFF_FOUND)

IF(MPI_FOUND)
   set(OSSIM_HAS_MPI 1)
   INCLUDE_DIRECTORIES(${MPI_INCLUDE_PATH})
ELSE(MPI_FOUND)
   set(MPI_LIBRARIES "")
   set(MPI_LIBRARY "")
ENDIF(MPI_FOUND)

IF(FREETYPE_FOUND)
   set(OSSIM_HAS_FREETYPE 1)
   INCLUDE_DIRECTORIES(${FREETYPE_INCLUDE_DIRS})
ELSE(FREETYPE_FOUND)
   set(FREETYPE_LIBRARY "")
   set(FREETYPE_LIBRARIES "")
ENDIF(FREETYPE_FOUND)

IF(ZLIB_FOUND)
   set(OSSIM_HAS_LIBZ 1)
ELSE(ZLIB_FOUND)
   set(ZLIB_LIBRARY "")
ENDIF(ZLIB_FOUND)

IF(UNIX)
    FIND_LIBRARY(DL_LIBRARY dl)
    IF(NOT DL_LIBRARY)
        SET(DL_LIBRARY "") # change from NOTFOUND to empty when passed to linker
    ENDIF()
ENDIF(UNIX)

SET(OSSIM_CONFIGURE_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/include/ossim/ossimConfig.h")
CONFIGURE_FILE("${CMAKE_CURRENT_SOURCE_DIR}/src/ossim/ossimConfig.h.in"
	       "${OSSIM_CONFIGURE_HEADER}")
SET(OSSIM_VERSION_HEADER_CONFIG "${CMAKE_CURRENT_SOURCE_DIR}/src/ossim/ossimVersion.h.in")
SET(OSSIM_VERSION_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/include/ossim/ossimVersion.h")
CONFIGURE_FILE("${OSSIM_VERSION_HEADER_CONFIG}"
               "${OSSIM_VERSION_HEADER}")


##################################################################################################
# Instead of creating another CMakeLists under src we will just add the subdirectories to build
# here
##################################################################################################
SUBDIRS(src/ossim)
SUBDIRS(src/apps)

#---
# Building test apps optional.
#---
IF(BUILD_OSSIM_TEST_APPS)
  SUBDIRS(src/test)
ENDIF(BUILD_OSSIM_TEST_APPS)

set(TARGET_COMMON_LIBRARIES ossim ${OPENTHREADS_LIBRARY})

##################################################################################################
#
# Setup install destinations for the shared files
#
##################################################################################################
FILE(GLOB ossim_projection_codes_csv ${${PROJECT_NAME}_SOURCE_DIR}/share/ossim/*.csv ${${PROJECT_NAME}_SOURCE_DIR}/share/ossim/*.txt)
INSTALL(FILES ${ossim_projection_codes_csv} DESTINATION share/ossim/projection COMPONENT ossim)

###################### OUTPUT GENERAL VARIABLE SETTINGS #######################

MESSAGE( STATUS "BUILD_LIBRARY_DIR               = ${BUILD_LIBRARY_DIR}" )
MESSAGE( STATUS "BUILD_RUNTIME_DIR               = ${BUILD_RUNTIME_DIR}" )
MESSAGE( STATUS "BUILD_OSSIM_FREETYPE_SUPPORT    = ${BUILD_OSSIM_FREETYPE_SUPPORT}" )
MESSAGE( STATUS "BUILD_OSSIM_TEST_APPS           = ${BUILD_OSSIM_TEST_APPS}" )
MESSAGE( STATUS "CMAKE_BUILD_TYPE                = ${CMAKE_BUILD_TYPE}" )
MESSAGE( STATUS "CMAKE_CXX_COMPILER              = ${CMAKE_CXX_COMPILER}" )
MESSAGE( STATUS "CMAKE_CXX_FLAGS                 = ${CMAKE_CXX_FLAGS}" )
MESSAGE( STATUS "CMAKE_CXX_FLAGS_DEBUG           = ${CMAKE_CXX_FLAGS_DEBUG}" )
MESSAGE( STATUS "CMAKE_CXX_FLAGS_RELEASE         = ${CMAKE_CXX_FLAGS_RELEASE}" )
MESSAGE( STATUS "CMAKE_INSTALL_PREFIX            = ${CMAKE_INSTALL_PREFIX}" )
MESSAGE( STATUS "FREETYPE_LIBRARY                = ${FREETYPE_LIBRARIES}" )
MESSAGE( STATUS "FREETYPE_INCLUDE                = ${FREETYPE_INCLUDE_DIRS}" )
MESSAGE( STATUS "GEOTIFF_LIBRARY                 = ${GEOTIFF_LIBRARIES}" )
MESSAGE( STATUS "GEOTIFF_INCLUDE                 = ${GEOTIFF_INCLUDE_DIR}" )
MESSAGE( STATUS "JPEG_LIBRARY                    = ${JPEG_LIBRARIES}" )
MESSAGE( STATUS "JPEG_INCLUDE                    = ${JPEG_INCLUDE_DIR}" )
MESSAGE( STATUS "MPI_LIBRARY                     = ${MPI_LIBRARIES}" )
MESSAGE( STATUS "MPI_INCLUDE                     = ${MPI_INCLUDE_PATH}" )
MESSAGE( STATUS "OPENTHREADS_LIBRARY             = ${OPENTHREADS_LIBRARY}" )
MESSAGE( STATUS "OPENTHREADS_INCLUDE             = ${OPENTHREADS_INCLUDE_DIR}" )
MESSAGE( STATUS "OSSIM_COMPILE_WITH_FULL_WARNING = ${OSSIM_COMPILE_WITH_FULL_WARNING}" )
MESSAGE( STATUS "TIFF_LIBRARY                    = ${TIFF_LIBRARIES}" )
MESSAGE( STATUS "TIFF_INCLUDE                    = ${TIFF_INCLUDE_DIR}" )
MESSAGE( STATUS "ZLIB_LIBRARY                    = ${ZLIB_LIBRARIES}" )
MESSAGE( STATUS "ZLIB_INCLUDE                    = ${ZLIB_INCLUDE_DIR}" )

#-----------------------------------------------------------------------------
# uninstall target
#-----------------------------------------------------------------------------
OSSIM_ADD_COMMON_MAKE_UNINSTALL()

message("################## end of OSSIM core library setup #########################")
