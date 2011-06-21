# Install script for directory: /home/vipul/ossim-svn/src/libwms

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

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "ossimPredator")
  FOREACH(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libwms.so.1.8.12"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libwms.so.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libwms.so"
      )
    IF(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      FILE(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    ENDIF()
  ENDFOREACH()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/libwms.so.1.8.12"
    "/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/libwms.so.1"
    "/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/libwms.so"
    )
  FOREACH(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libwms.so.1.8.12"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libwms.so.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libwms.so"
      )
    IF(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "${file}")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDFOREACH()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "ossimPredator")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "ossimPredator-dev")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/wms" TYPE FILE FILES
    "/home/vipul/ossim-svn/src/libwms/include/wms/wmsRefPtr.h"
    "/home/vipul/ossim-svn/src/libwms/include/wms/wmsReferenced.h"
    "/home/vipul/ossim-svn/src/libwms/include/wms/wmsMemoryStream.h"
    "/home/vipul/ossim-svn/src/libwms/include/wms/wmsCapabilitiesRoot.h"
    "/home/vipul/ossim-svn/src/libwms/include/wms/wmsStyle.h"
    "/home/vipul/ossim-svn/src/libwms/include/wms/wmsNotify.h"
    "/home/vipul/ossim-svn/src/libwms/include/wms/iso8601.h"
    "/home/vipul/ossim-svn/src/libwms/include/wms/wmsExport.h"
    "/home/vipul/ossim-svn/src/libwms/include/wms/wmsCurlMemoryStream.h"
    "/home/vipul/ossim-svn/src/libwms/include/wms/wmsClient.h"
    "/home/vipul/ossim-svn/src/libwms/include/wms/wms.h"
    "/home/vipul/ossim-svn/src/libwms/include/wms/wmsCapabilitiesParser.h"
    "/home/vipul/ossim-svn/src/libwms/include/wms/wmsCapabilitiesState.h"
    "/home/vipul/ossim-svn/src/libwms/include/wms/wmsUrl.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "ossimPredator-dev")

