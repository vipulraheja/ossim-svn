# Install script for directory: /home/vipul/ossim-svn/src/oms/coms

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "ossim")
  FOREACH(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liboms.so.1.8.12"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liboms.so.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liboms.so"
      )
    IF(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      FILE(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    ENDIF()
  ENDFOREACH()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/liboms.so.1.8.12"
    "/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/liboms.so.1"
    "/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/liboms.so"
    )
  FOREACH(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liboms.so.1.8.12"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liboms.so.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liboms.so"
      )
    IF(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      FILE(RPATH_REMOVE
           FILE "${file}")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "${file}")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDFOREACH()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "ossim")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "ossim-dev")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/oms" TYPE FILE FILES
    "/home/vipul/ossim-svn/src/oms/coms/include/oms/CoordinateUtility.h"
    "/home/vipul/ossim-svn/src/oms/coms/include/oms/Projection.h"
    "/home/vipul/ossim-svn/src/oms/coms/include/oms/Info.h"
    "/home/vipul/ossim-svn/src/oms/coms/include/oms/WmsMap.h"
    "/home/vipul/ossim-svn/src/oms/coms/include/oms/Constants.h"
    "/home/vipul/ossim-svn/src/oms/coms/include/oms/WktUtility.h"
    "/home/vipul/ossim-svn/src/oms/coms/include/oms/ImageStager.h"
    "/home/vipul/ossim-svn/src/oms/coms/include/oms/ImageOutputFormat.h"
    "/home/vipul/ossim-svn/src/oms/coms/include/oms/SingleImageChain.h"
    "/home/vipul/ossim-svn/src/oms/coms/include/oms/Mosaic.h"
    "/home/vipul/ossim-svn/src/oms/coms/include/oms/OutputSource.h"
    "/home/vipul/ossim-svn/src/oms/coms/include/oms/ImageModel.h"
    "/home/vipul/ossim-svn/src/oms/coms/include/oms/WmsView.h"
    "/home/vipul/ossim-svn/src/oms/coms/include/oms/DataInfo.h"
    "/home/vipul/ossim-svn/src/oms/coms/include/oms/Util.h"
    "/home/vipul/ossim-svn/src/oms/coms/include/oms/Init.h"
    "/home/vipul/ossim-svn/src/oms/coms/include/oms/Video.h"
    "/home/vipul/ossim-svn/src/oms/coms/include/oms/ImageData.h"
    "/home/vipul/ossim-svn/src/oms/coms/include/oms/Chain.h"
    "/home/vipul/ossim-svn/src/oms/coms/include/oms/Object.h"
    "/home/vipul/ossim-svn/src/oms/coms/include/oms/Source.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "ossim-dev")

