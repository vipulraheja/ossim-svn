# Install script for directory: /home/vipul/ossim-svn/src/csmApi

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
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcsmApi.so.1.8.12"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcsmApi.so.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcsmApi.so"
      )
    IF(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      FILE(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    ENDIF()
  ENDFOREACH()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/libcsmApi.so.1.8.12"
    "/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/libcsmApi.so.1"
    "/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/libcsmApi.so"
    )
  FOREACH(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcsmApi.so.1.8.12"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcsmApi.so.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcsmApi.so"
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

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "ossim")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/csmApi" TYPE FILE FILES
    "/home/vipul/ossim-svn/src/csmApi/include/Utilities.h"
    "/home/vipul/ossim-svn/src/csmApi/include/VTSMisc.h"
    "/home/vipul/ossim-svn/src/csmApi/include/CSMOutput.h"
    "/home/vipul/ossim-svn/src/csmApi/include/CSMSensorModelLoader.h"
    "/home/vipul/ossim-svn/src/csmApi/include/SMManager.h"
    "/home/vipul/ossim-svn/src/csmApi/include/csmApiExport.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "ossim")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "ossim")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/csmApi/TSM" TYPE FILE FILES
    "/home/vipul/ossim-svn/src/csmApi/include/TSM/TSMISDByteStream.h"
    "/home/vipul/ossim-svn/src/csmApi/include/TSM/TSMWarning.h"
    "/home/vipul/ossim-svn/src/csmApi/include/TSM/TSMISDFilename.h"
    "/home/vipul/ossim-svn/src/csmApi/include/TSM/TSMISDNITF20.h"
    "/home/vipul/ossim-svn/src/csmApi/include/TSM/TSMPlugin.h"
    "/home/vipul/ossim-svn/src/csmApi/include/TSM/TSMError.h"
    "/home/vipul/ossim-svn/src/csmApi/include/TSM/TSMISDNITF21.h"
    "/home/vipul/ossim-svn/src/csmApi/include/TSM/TSMMisc.h"
    "/home/vipul/ossim-svn/src/csmApi/include/TSM/TSMSensorModel.h"
    "/home/vipul/ossim-svn/src/csmApi/include/TSM/TSMImageSupportData.h"
    "/home/vipul/ossim-svn/src/csmApi/include/TSM/TSMCovarianceModel.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "ossim")

