###
# $Id: src.pro 16847 2010-03-09 12:19:39Z gpotts $
#
# NOTE:  
# You should set environment variables for include paths and linking:
#
# "OSSIM_DEV_HOME" This should point to the top level directory where "ossim"
# and "ossim_qt" are compiled.
#
# Window build relies on "EARTH_PACKAGE" variable.
#
###

TEMPLATE	= lib
LANGUAGE	= C++

CONFIG	+= qt warn_on release

DEFINES	+= _FILE_OFFSET_BITS=64 _LARGE_FILES

HEADERS	+= ossimQtBrightnessContrastDialog.h \
	ossimQtScrollingImageWidget.h \
	ossimQtElevationManagerController.h \
	ossimQtGeometryBuilderDialogController.h \
	ossimDataManager.h \
	ossimQtDataManagerListBox.h \
	ossimQtInformationDialog.h \
	ossimQtMainWindowController.h \
	ossimQtImageWindowController.h \
	ossimQtBandSelectorController.h \
	ossimQtViewDialogController.h \
	ossimQtMainWindowWorkspace.h \
	ossimQtEvent.h \
	ossimQtImageWindowControllerEventFilter.h \
	ossimQtDisplayUtility.h \
	ossimQtHsiRemapperController.h \
	ossimQtSwipeScrollingImageWidget.h \
	ossimQtHistogramWidget.h \
	ossimQListBox.h \
	ossimQtCombinerEditorDialogController.h \
	ossimQtProject.h \
	ossimQtHistogramController.h \
	ossimQtLayerEditorController.h \
	ossimQtTopographicCorrectionDialogController.h \
	ossimQtAdjustableParameterDialogController.h \
	ossimQtSliderTableItem.h \
	ossimQtIgenController.h \
	ossimQtVectorEditorDialogController.h \
	ossimQtImageChainEditorController.h \
	ossimQWidgetFactoryInterface.h \
	ossimQWidgetEditorFactory.h \
	ossimQWidgetFactoryRegistry.h \
	ossimQtPositionQualityDialog.h \
	vce/ossimQtVceWindowController.h \
	vce/ossimQtVceComponentView.h \
	vce/ossimQtVceComponentDialogController.h \
	vce/ossimQtVceCanvasWidget.h \
	vce/ossimQtVceConnectableObject.h \
	vce/ossimQtVceConnectionObject.h \
	vce/ossimQtVceImageDisplayObject.h \
	vce/ossimQtVceImageSourceObject.h \
	vce/ossimQtVceShape.h \
	vce/ossimQtVceShapeRect.h \
	vce/ossimQtVceImageHandlerObject.h \
	vce/ossimQtVceCanvasContainerUtility.h \
	property/ossimQtPropertyDialogController.h \
	property/ossimQtPropertyTextItem.h \
	property/ossimQtPropertyListView.h \
	property/ossimQtPropertyBooleanItem.h \
	property/ossimQtPropertyFactory.h \
	property/ossimQtPropertyContainerItem.h \
	property/ossimQtPropertyItem.h \
	property/ossimQtPropertyStringItem.h \
	property/ossimQtPropertyNumericItem.h \
	property/ossimQtPropertyColorItem.h \
	property/ossimQtPropertyFontItem.h \
	property/ossimQtPropertyFilenameItem.h \
	property/ossimQtMatrixPropertyController.h \
	property/ossimQtPropertyMatrixItem.h \
	property/ossimQtStringListPropertyController.h \
	property/ossimQtPropertyStringListItem.h \
	property/ossimQtPropertyDateItem.h \
	ossimQtPreferencesDialogController.h \
	ossimQtStaticTileImageCache.h \
	ossimQtImageInfoController.h \
	ossimQtQuadProjectionController.h \
	ossimQtSingleImageWindow.h \
	ossimQtAnnotatorBase.h \
	ossimQtRoiAnnotator.h \
	ossimQtRoiRectAnnotator.h \
	ossimQtProgressDialog.h \
	ossimQtRLevelFilterDialog.h \
	ossimQtEditorWidgetManager.h \
	ossimQtHistogramBuilderDialog.h \
	ossimQtIcpDialog.h \
	ossimQtOverviewBuilderDialog.h \
	ossimQtAboutDialogBase.h \
	ossimQtImagelinkerAboutDialog.h \
	ossimQtIviewAboutDialog.h

SOURCES	+= ossimQtBrightnessContrastDialog.cpp \
	ossimQtScrollingImageWidget.cpp \
	ossimQtElevationManagerController.cpp \
	ossimQtInformationDialog.cpp \
	ossimQtGeometryBuilderDialogController.cpp \
	ossimDataManager.cpp \
	ossimQtDataManagerListBox.cpp \
	ossimQtMainWindowController.cpp \
	ossimQtImageWindowController.cpp \
	ossimQtBandSelectorController.cpp \
	ossimQtViewDialogController.cpp \
	ossimQtEvent.cpp \
	ossimQtMainWindowWorkspace.cpp \
	ossimQtApplicationUtility.cpp \
	ossimQtImageWindowControllerEventFilter.cpp \
	ossimQtDisplayUtility.cpp \
	ossimQtHsiRemapperController.cpp \
	ossimQtSwipeScrollingImageWidget.cpp \
	ossimQtHistogramWidget.cpp \
	ossimQListBox.cpp \
	ossimQtCombinerEditorDialogController.cpp \
	ossimQtProject.cpp \
	ossimQtHistogramController.cpp \
	ossimQtLayerEditorController.cpp \
	ossimQtTopographicCorrectionDialogController.cpp \
	ossimQtAdjustableParameterDialogController.cpp \
	ossimQtSliderTableItem.cpp \
	ossimQtIgenController.cpp \
	ossimQtVectorEditorDialogController.cpp \
	ossimQtImageChainEditorController.cpp \
	ossimQWidgetFactoryInterface.cpp \
	ossimQWidgetEditorFactory.cpp \
	ossimQWidgetFactoryRegistry.cpp \
	ossimQtPositionQualityDialog.cpp \
	vce/ossimQtVceWindowController.cpp \
	vce/ossimQtVceComponentView.cpp \
	vce/ossimQtVceComponentDialogController.cpp \
	vce/ossimQtVceCanvasWidget.cpp \
	vce/ossimQtVceConnectableObject.cpp \
	vce/ossimQtVceConnectionObject.cpp \
	vce/ossimQtVceImageDisplayObject.cpp \
	vce/ossimQtVceImageSourceObject.cpp \
	vce/ossimQtVceShape.cpp \
	vce/ossimQtVceShapeRect.cpp \
	vce/ossimQtVceImageHandlerObject.cpp \
	vce/ossimQtVceCanvasContainerUtility.cpp \
	property/ossimQtPropertyDialogController.cpp \
	property/ossimQtPropertyTextItem.cpp \
	property/ossimQtPropertyListView.cpp \
	property/ossimQtPropertyBooleanItem.cpp \
	property/ossimQtPropertyFactory.cpp \
	property/ossimQtPropertyContainerItem.cpp \
	property/ossimQtPropertyItem.cpp \
	property/ossimQtPropertyStringItem.cpp \
	property/ossimQtPropertyNumericItem.cpp \
	property/ossimQtPropertyColorItem.cpp \
	property/ossimQtPropertyFontItem.cpp \
	property/ossimQtPropertyFilenameItem.cpp \
	property/ossimQtMatrixPropertyController.cpp \
	property/ossimQtPropertyMatrixItem.cpp \
	property/ossimQtStringListPropertyController.cpp \
	property/ossimQtPropertyStringListItem.cpp \
	property/ossimQtPropertyDateItem.cpp \
	ossimQtPreferencesDialogController.cpp \
	ossimQtStaticTileImageCache.cpp \
	ossimQtImageInfoController.cpp \
	ossimQtQuadProjectionController.cpp \
	ossimQtSingleImageWindow.cpp \
	ossimQtAnnotatorBase.cpp \
	ossimQtRoiAnnotator.cpp \
	ossimQtRoiRectAnnotator.cpp \
	ossimQtProgressDialog.cpp \
	ossimQtRLevelFilterDialog.cpp \
	ossimQtEditorWidgetManager.cpp \
	ossimQtHistogramBuilderDialog.cpp \
	ossimQtIcpDialog.cpp \
	ossimQtOverviewBuilderDialog.cpp \
	ossimQtAboutDialogBase.cpp \
	ossimQtImagelinkerAboutDialog.cpp \
	ossimQtIviewAboutDialog.cpp

FORMS	= ossimQtMainWindow.ui \
	ossimQtImageWindow.ui \
	ossimQtElevationManagerDialog.ui \
	ossimQtDatumConverterDialog.ui \
	ossimQtUnitConverterDialog.ui \
	ossimQtDataManagerDialog.ui \
	ossimQtBandSelectorDialog.ui \
	ossimQtViewDialog.ui \
	ossimQtGeometryBuilderDialog.ui \
	ossimQtHsiRemapperDialog.ui \
	ossimQtLayerChooser.ui \
	ossimQtHistogramDialog.ui \
	ossimQtLayerEditor.ui \
	ossimQtCombinerEditorDialog.ui \
	ossimQtTopographicCorrectionDialog.ui \
	ossimQtAdjustableParameterDialog.ui \
	ossimQtIgenDialog.ui \
	ossimQtVectorEditorDialog.ui \
	vce/ossimQtVceWindow.ui \
	vce/ossimQtVceComponentDialog.ui \
	property/ossimQtPropertyDialog.ui \
	property/ossimQtMatrixPropertyDialog.ui \
	property/ossimQtStringListPropertyDialog.ui \
	ossimQtPreferencesDialog.ui \
	ossimQtImageChainEditorDialog.ui \
	ossimQtImageInfoDialog.ui \
	ossimQtQuadProjectionDialog.ui

IMAGES	= ../images/filenew \
	../images/fileopen \
	../images/filesave \
	../images/print \
	../images/undo \
	../images/redo \
	../images/editcut \
	../images/editcopy \
	../images/editpaste \
	../images/searchfind \
	../images/display \
	../images/datastore \
	../images/fingerup \
	../images/dataextract \
	../images/alignbottom \
	../images/alignleft \
	../images/alignright \
	../images/aligntop \
	../images/tilecascade \
	../images/connection \
	../images/resetproperty \
	../images/ImageLinkerSplash \
	../images/iviewsplash

UI_DIR = .ui
MOC_DIR = .moc
OBJECTS_DIR = .obj
VERSION = 1.8.4
TARGET = ossim_qt
DESTDIR = $$(OSSIM_DEV_HOME)/ossim_qt/lib

###
# For make install target.
###
include(../makedefs.pri)
target.path = $$INSTALL_PREFIX/lib
INSTALLS += target


win32 {
  DEFINES += NOMINMAX OSSIMUSINGDLL
  QMAKE_CXXFLAGS = -EHsc -GR
  LIBS	= -L$(OSSIM_DEV_HOME)\lib -lossim 
  INCLUDEPATH += $(OSSIM_DEV_HOME)\ossim\include $(OSSIM_DEV_HOME)\3rd-party\include
  DESTDIR = $(OSSIM_DEV_HOME)\ossim_qt\lib
  DEPENDPATH += $(OSSIM_DEV_HOME)\ossim\include

  ###
  # DO NOT delete in svn!
  ###
  # DEFINES += NOMINMAX OSSIMUSINGDLL
  # QMAKE_CXXFLAGS = -EHsc -GR
  # LIBS	+= -L$(OSSIM_DEV_HOME)\ossim\lib -lossim 
  # INCLUDEPATH += $(OSSIM_DEV_HOME)\ossim\include C:\sw\vs9\3rdparty\include C:\sw\vs9\3rdparty\include\freetype2
  # DESTDIR = $(OSSIM_DEV_HOME)\ossim_qt\lib
  # DEPENDPATH += $(OSSIM_DEV_HOME)\ossim\include
}

else:macx {
  DEFINES += MACOSX
  LIBS += -L$(OSSIM_DEV_HOME)/ossim/lib/ossim -lossim -flat_namespace -undefined suppress
  INCLUDEPATH += $(OSSIM_DEV_HOME)/ossim/include /opt/local/include 
  DESTDIR = $(OSSIM_DEV_HOME)/ossim_qt/lib
  DEPENDPATH += $(OSSIM_DEV_HOME)/ossim/include
}

else:unix {
  ###
  # Relies upon OSSIM_DEV_HOME environment variable being set.
  # LOCAL_ROOT is set in top level makedefs.pri file.  
  # OpenThread and geotiff should be installed in $$LOCAL_ROOT
  # Take out/edit as necessary.
  ###

  INCLUDEPATH += $$(OSSIM_DEV_HOME)/ossim/include $$LOCAL_ROOT/include

  LIBS += -L$$(OSSIM_DEV_HOME)/ossim/lib -L$$LOCAL_ROOT/lib -lossim -lOpenThreads -lgeotiff -ltiff

  DESTDIR = $$(OSSIM_DEV_HOME)/ossim_qt/lib

  DEPENDPATH += $$(OSSIM_DEV_HOME)/ossim/include
}

