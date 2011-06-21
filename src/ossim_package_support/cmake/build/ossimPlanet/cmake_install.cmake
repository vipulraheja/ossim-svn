# Install script for directory: /home/vipul/ossim-svn/src/ossimPlanet

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
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libossimPlanet.so.1.8.12"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libossimPlanet.so.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libossimPlanet.so"
      )
    IF(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      FILE(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    ENDIF()
  ENDFOREACH()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/libossimPlanet.so.1.8.12"
    "/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/libossimPlanet.so.1"
    "/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/libossimPlanet.so"
    )
  FOREACH(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libossimPlanet.so.1.8.12"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libossimPlanet.so.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libossimPlanet.so"
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
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ossimPlanet" TYPE FILE FILES
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetNodeFactory.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetShaderProgramSetup.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/netMessage.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetTexture2D.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetKml.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetAnimatedPointModel.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetThreadImp.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetGrid.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetIdolBridge.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetUtility.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetExport.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetTerrainTileId.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetYahooGeocoder.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanet.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetElevationDatabaseGroup.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetServerMessageHandler.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetIo.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetViewMatrixBuilder.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetLayer.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetSetup.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetManipulator.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetServerThread.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetAction.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetDistanceAccumulator.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetLayerFactoryBase.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetWmsImageLayer.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetTerrainTile.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetAnimationPath.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetPagedRequestNode.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/mkUtils.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetPlaneGrid.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetReentrantMutex.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetKmlLayer.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetCloudLayer.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetTileRequest.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/unzip.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetLandNormalType.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetXmlAction.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetTextureLayerGroup.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetLandReaderWriter.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetTerrainGeometryTechnique.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetLandCache.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetElevationRegistry.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetKmlScreenOverlayNode.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/zip.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/sg_socket.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetNode.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetLookAt.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetDatabasePager.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetGeoRefModel.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetTextureLayer.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetNetworkConnection.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetKmlPlacemarkNode.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetBillboardIcon.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetLayerFactory.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetViewer.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetGridUtility.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetLabelGeom.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ulRTTI.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetAnnotationLayerNode.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetApi.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/sg_file.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetVideoLayer.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetIoThread.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/netBuffer.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetElevationFactory.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetThreadPool.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetTerrainTechnique.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetTextureLayerRegistry.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetTerrainLayer.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetClientThread.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetKmlReaderWriter.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ulLocal.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetPagedLandLodRefreshType.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetCache.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetCompass.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/netChat.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetIoMessageHandler.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ioapi.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetTextureLayerFactory.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetNodeFactoryBase.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/netSocket.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetCacheTextureLayer.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetGeocoder.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/sg_socket_udp.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetPrimaryBody.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetEphemeris.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetOssimImage.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetSousaLayer.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetWmsClient.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetTerrain.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetElevationGrid.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetIntersectUserData.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetKmlLayerNode.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetIoSocket.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetLsrSpaceTransform.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetOperation.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetInputDevice.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetVideoLayerNode.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetDepthPartitionNode.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetOrthoFlatLandNode.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/netMonitor.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetSocketNetworkConnection.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetLandNode.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetIdManager.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetCallback.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetThread.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/netChannel.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetOssimElevationDatabase.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetActionRouter.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetNavigator.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetIdolLayer.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetLandTreeNode.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetLand.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetArchiveMapping.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetExtents.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetSceneView.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetBoundingBox.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetSrtmElevationDatabase.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/compiler.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetDestinationCommandAction.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetPagedLandLod.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetImage.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetIconGeom.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetInteractionController.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetIoRoutableMessageHandler.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetLatLonHud.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetId.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetActionReceiver.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetArchive.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetJpegImage.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetRefBlock.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetDtedElevationDatabase.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetVisitors.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetPointModel.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetLandCullCallback.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetNodeRegistry.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetCubeGrid.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetGeneralRasterElevationDatabase.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetKmlNetworkLinkNode.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetOssimImageLayer.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetMessage.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetPredatorVideoLayerNode.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetFadeText.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ul.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetLayerRegistry.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetIoSocketServerChannel.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/net.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetElevationDatabase.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetStandardTextureLayerFactory.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetAnnotationLayer.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/iowin32.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetConstants.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/ossimPlanetLandTextureRequest.h"
    "/home/vipul/ossim-svn/src/ossimPlanet/include/ossimPlanet/iochannel.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "ossim-dev")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "ossim")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ossimplanetviewer" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ossimplanetviewer")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ossimplanetviewer"
         RPATH "")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossimplanetviewer")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ossimplanetviewer" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ossimplanetviewer")
    FILE(RPATH_REMOVE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ossimplanetviewer")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ossimplanetviewer")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "ossim")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "ossim")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ossimplanettest" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ossimplanettest")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ossimplanettest"
         RPATH "")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossimplanettest")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ossimplanettest" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ossimplanettest")
    FILE(RPATH_REMOVE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ossimplanettest")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ossimplanettest")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "ossim")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "ossim")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ossimplanetklv" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ossimplanetklv")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ossimplanetklv"
         RPATH "")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossimplanetklv")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ossimplanetklv" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ossimplanetklv")
    FILE(RPATH_REMOVE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ossimplanetklv")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ossimplanetklv")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "ossim")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "ossim")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ossimplanet-chip" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ossimplanet-chip")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ossimplanet-chip"
         RPATH "")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossimplanet-chip")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ossimplanet-chip" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ossimplanet-chip")
    FILE(RPATH_REMOVE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ossimplanet-chip")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ossimplanet-chip")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "ossim")

