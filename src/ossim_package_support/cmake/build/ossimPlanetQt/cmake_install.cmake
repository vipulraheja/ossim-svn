# Install script for directory: /home/vipul/ossim-svn/src/ossimPlanetQt

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
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libossimPlanetQt.so.1.8.12"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libossimPlanetQt.so.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libossimPlanetQt.so"
      )
    IF(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      FILE(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    ENDIF()
  ENDFOREACH()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/libossimPlanetQt.so.1.8.12"
    "/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/libossimPlanetQt.so.1"
    "/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/libossimPlanetQt.so"
    )
  FOREACH(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libossimPlanetQt.so.1.8.12"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libossimPlanetQt.so.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libossimPlanetQt.so"
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
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ossimPlanetQtActionAdapter.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ossimPlanetQtDropDownDelegate.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ossimPlanetQtLegendNodeItem.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ossimPlanetQtVideoControlWidget.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ossimPlanetQtActivityThread.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ossimPlanetQtAlertLayer.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ossimPlanetQtLegendItem.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ossimPlanetQtNewHttpConnection.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ossimPlanetQtActivityWindow.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ossimPlanetQtVersion.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ossimPlanetQtOperation.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ossimPlanetQtMessageLog.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ossimPlanetQtLegendVideoItem.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ossimPlanetQtLegend.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ossimPlanetQtApplication.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ossimPlanetQtImage.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ossimPlanetQtLayerOperation.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ossimPlanetQtLegendLocationInfo.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ossimPlanetQtRuler.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ossimPlanetQtWmsDialog.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ossimPlanetQtLegendKmlItem.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ossimPlanetQtEvent.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ossimPlanetQtLegendTextureItem.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ossimPlanetQtActivityWidget.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ossimPlanetQtPreferences.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ossimPlanetQtExport.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ossimPlanetQtActivityThreadQueueItem.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ossimPlanetQtMainWindow.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ossimPlanetQtAboutDialog.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ossimPlanetQtGlWidget.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ossimPlanetQtLegendAnimationPathItem.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ossimPlanetQtActivityItem.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ossimPlanetQtLegendLocatioInfo.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ui_ossimPlanetQtLayerOperation.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ui_ossimPlanetQtWmsDialog.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ui_ossimPlanetQtAboutDialog.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ui_ossimPlanetQtNewHttpConnection.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ui_ossimPlanetQtVideoControlWidget.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ui_ossimPlanetQtMessageLog.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ui_ossimPlanetQtMainWindow.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ui_ossimPlanetQtActivityWindow.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ui_ossimPlanetQtPreferences.h"
    "/home/vipul/ossim-svn/src/ossimPlanetQt/include/ossimPlanetQt/ui_ossimPlanetQtRuler.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "ossim-dev")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "ossim")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ossimplanet" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ossimplanet")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ossimplanet"
         RPATH "")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossimplanet")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ossimplanet" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ossimplanet")
    FILE(RPATH_REMOVE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ossimplanet")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ossimplanet")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "ossim")

