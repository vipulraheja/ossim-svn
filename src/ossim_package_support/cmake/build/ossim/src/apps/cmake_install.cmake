# Install script for directory: /home/vipul/ossim-svn/src/ossim/src/apps

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

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-swapbytes/cmake_install.cmake")
  INCLUDE("/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-img2rr/cmake_install.cmake")
  INCLUDE("/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-tfw2ogeom/cmake_install.cmake")
  INCLUDE("/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-dem/cmake_install.cmake")
  INCLUDE("/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-modopt/cmake_install.cmake")
  INCLUDE("/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-chgkwval/cmake_install.cmake")
  INCLUDE("/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-dump-ocg/cmake_install.cmake")
  INCLUDE("/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-dms2deg/cmake_install.cmake")
  INCLUDE("/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-icp/cmake_install.cmake")
  INCLUDE("/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-img2md/cmake_install.cmake")
  INCLUDE("/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-rejout/cmake_install.cmake")
  INCLUDE("/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-computeSrtmStats/cmake_install.cmake")
  INCLUDE("/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-btoa/cmake_install.cmake")
  INCLUDE("/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-ws-cmp/cmake_install.cmake")
  INCLUDE("/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-extract-vertices/cmake_install.cmake")
  INCLUDE("/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-image-compare/cmake_install.cmake")
  INCLUDE("/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-band-merge/cmake_install.cmake")
  INCLUDE("/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-prune/cmake_install.cmake")
  INCLUDE("/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-igen/cmake_install.cmake")
  INCLUDE("/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-create-histo/cmake_install.cmake")
  INCLUDE("/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-applanix2ogeom/cmake_install.cmake")
  INCLUDE("/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-senint/cmake_install.cmake")
  INCLUDE("/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-rpf/cmake_install.cmake")
  INCLUDE("/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-info/cmake_install.cmake")
  INCLUDE("/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-deg2dms/cmake_install.cmake")
  INCLUDE("/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-create-cg/cmake_install.cmake")
  INCLUDE("/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-adrg-dump/cmake_install.cmake")
  INCLUDE("/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-ogeom2ogeom/cmake_install.cmake")
  INCLUDE("/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-mosaic/cmake_install.cmake")
  INCLUDE("/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-space-imaging/cmake_install.cmake")
  INCLUDE("/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-cmm/cmake_install.cmake")
  INCLUDE("/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-pixelflip/cmake_install.cmake")
  INCLUDE("/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-correl/cmake_install.cmake")
  INCLUDE("/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-orthoigen/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

