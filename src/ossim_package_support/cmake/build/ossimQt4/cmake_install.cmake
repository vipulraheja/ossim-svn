# Install script for directory: /home/vipul/ossim-svn/src/ossim_qt4

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
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libossimQt.so.1.8.12"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libossimQt.so.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libossimQt.so"
      )
    IF(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      FILE(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    ENDIF()
  ENDFOREACH()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/libossimQt.so.1.8.12"
    "/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/libossimQt.so.1"
    "/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/libossimQt.so"
    )
  FOREACH(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libossimQt.so.1.8.12"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libossimQt.so.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libossimQt.so"
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
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtPropertyDateItem.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtIgenDialog.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtIgenController.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtRoiAnnotator.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtPropertyStringListItem.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtPreferencesDialog.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtScrollingImageWidget.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtImageInfoDialog.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtMatrixPropertyController.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtViewDialogController.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtHsiRemapperDialog.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtEvent.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtImageWindowController.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtPropertyColorItem.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtInformationDialog.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQWidgetEditorFactory.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtDataManagerDialog.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtStringListPropertyController.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtDataManagerListBox.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtPropertyStringItem.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtIviewAboutDialog.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtImageChainEditorDialog.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtTopographicCorrectionDialog.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtAboutDialogBase.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtRLevelFilterDialog.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtGeometryBuilderDialogController.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtSingleImageWindow.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtProject.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtExport.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtHistogramController.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtAdjustableParameterDialogController.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtImageWindow.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQWidgetFactoryRegistry.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtAnnotatorBase.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtTopographicCorrectionDialogController.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtMainWindow.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtBandSelectorController.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtPreferencesDialogController.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtElevationManagerController.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtVectorEditorDialogController.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtPropertyItem.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtViewDialog.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtEditorWidgetManager.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtEventIds.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtPropertyFilenameItem.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtQuadProjectionController.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtPropertyDialog.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtGeometryBuilderDialog.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtApplicationUtility.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtPropertyFontItem.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtPropertyNumericItem.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtVectorEditorDialog.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtRoiRectAnnotator.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtBrightnessContrastDialog.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtCombinerEditorDialogController.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtStaticTileImageCache.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtPropertyDialogController.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtPositionQualityDialog.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtLayerEditor.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtCombinerEditorDialog.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtMatrixPropertyDialog.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtPropertyFactory.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtBandSelectorDialog.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtImageInfoController.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtIcpDialog.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtSliderTableItem.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtMainWindowWorkspace.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtLayerEditorController.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtQuadProjectionDialog.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtElevationManagerDialog.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtImageChainEditorController.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtUnitConverterDialog.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtImagelinkerAboutDialog.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtOverviewBuilderDialog.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtHistogramBuilderDialog.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtDatumConverterDialog.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtHsiRemapperController.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtDisplayUtility.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtScrollImgWidget.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtHistogramDialog.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtAdjustableParameterDialog.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtStringListPropertyDialog.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtHistogramWidget.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtMainWindowController.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtPropertyBooleanItem.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimDataManager.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtLayerChooser.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtPropertyListView.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtPropertyMatrixItem.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtPluginsDialog.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtPropertyContainerItem.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtImageWindowControllerEventFilter.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtSwipeScrollingImageWidget.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtPropertyTextItem.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQWidgetFactoryInterface.h"
    "/home/vipul/ossim-svn/src/ossim_qt4/include/ossimQt/ossimQtProgressDialog.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "ossim-dev")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "ossim")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/imagelinker" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/imagelinker")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/imagelinker"
         RPATH "")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/imagelinker")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/imagelinker" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/imagelinker")
    FILE(RPATH_REMOVE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/imagelinker")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/imagelinker")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "ossim")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "ossim")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/iview" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/iview")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/iview"
         RPATH "")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/vipul/ossim-svn/src/ossim_package_support/cmake/build/iview")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/iview" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/iview")
    FILE(RPATH_REMOVE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/iview")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/iview")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "ossim")

