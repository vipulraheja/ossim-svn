# Install script for directory: /home/vipul/ossim-svn/src/ossim

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
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ossim/projection" TYPE FILE FILES
    "/home/vipul/ossim-svn/src/ossim/share/ossim/ossim_epsg_projections-v7_4.csv"
    "/home/vipul/ossim-svn/src/ossim/share/ossim/ossim_harn_state_plane_esri.csv"
    "/home/vipul/ossim-svn/src/ossim/share/ossim/ossim_harn_state_plane_epsg.csv"
    "/home/vipul/ossim-svn/src/ossim/share/ossim/ossim_wkt_pcs.csv"
    "/home/vipul/ossim-svn/src/ossim/share/ossim/ossim_state_plane_spcs.csv"
    "/home/vipul/ossim-svn/src/ossim/share/ossim/ossim_state_plane_readme.txt"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "ossim")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/ossim/cmake_install.cmake")
  INCLUDE("/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

