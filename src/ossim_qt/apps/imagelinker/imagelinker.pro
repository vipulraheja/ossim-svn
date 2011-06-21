###
# $Id: imagelinker.pro 13701 2008-10-10 21:30:28Z dburken $
#
# NOTE:  
# You should set environment variables for include paths and linking:
#
# "OSSIM_DEV_HOME" This should point to the top level directory where "ossim"
# and "ossim_qt" are compiled.
#
# Window build relies on "EARTH_PACKAGE" variable.
###

TEMPLATE	= app
LANGUAGE	= C++
CONFIG	+= qt warn_on release 

DEFINES	+= _FILE_OFFSET_BITS=64 _LARGE_FILES HAS_OPEN_THREADS=1 HAVE_CONFIG_H MPI_SETTING=0 GEOTIFF_ENABLED FREETYPE_SETTING=1

TARGET = imagelinker
DESTDIR = $$(OSSIM_DEV_HOME)/ossim_qt/bin

###
# For make install target.
###
include(../../makedefs.pri)
target.path = $$INSTALL_PREFIX/bin
INSTALLS += target

INCLUDEPATH	+= ../../src ../../src/.ui ../../src/.moc

SOURCES	= main.cpp

win32 {
  QMAKE_CLEAN += imagelinker.e* imagelinker.l* ..\..\bin\imagelinker.*  
  DEFINES += NOMINMAX OSSIMUSINGDLL
  QMAKE_CXXFLAGS = -EHsc

  ###
  # Uncomment out for visual express 2008 (vs9).
  # QMAKE_LFAGS = NODEFAULTLIB:MSVCP90
  ###

  LIBS = -L$(OSSIM_DEV_HOME)/ossim/lib -L$(OSSIM_DEV_HOME)/ossim_qt/lib ../../lib/ossim_qt.lib -lossim -lopengl32 -lglu32 -lopengl32 -lglu32

  target.path = $(OSSIM_DEV_HOME)\ossim_qt\bin
  DEPENDPATH += $(OSSIM_DEV_HOME)\ossim_qt\src $(OSSIM_DEV_HOME)\ossim\include
  INCLUDEPATH += $(OSSIM_DEV_HOME)\ossim\include $(OSSIM_DEV_HOME)\3rd-party\include
}

else:macx {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
  QMAKE_CLEAN += imagelinker ../../bin/imagelinker
   LIBS = -bind_at_load -L$$(OSSIM_DEV_HOME)/ossim_qt/lib -L$$(OSSIM_DEV_HOME)/ossim/lib/ossim -L/opt/local/lib -lossim_qt -lossim
  INCLUDEPATH += $(OSSIM_DEV_HOME)/ossim/include /opt/local/include
  target.path = $(OSSIM_DEV_HOME)/ossim_qt/bin
  DEPENDPATH += $(OSSIM_DEV_HOME)/ossim_qt/src $(OSSIM_DEV_HOME)/ossim/include
  INCLUDEPATH	+= $(OSSIM_DEV_HOME)/ossim/include
  target.path = $(OSSIM_DEV_HOME)/ossim_qt/bin
}

else:unix {
###
# Relies upon OSSIM_DEV_HOME environment variable being set.
# LOCAL_ROOT is set in top level makedefs.pri file.  
# OpenThread and geotiff should be installed in $LOCAL_ROOT
# Take out/edit as necessary.
###

QMAKE_CLEAN += imagelinker ../../bin/imagelinker
UI_DIR = .ui
MOC_DIR = .moc
OBJECTS_DIR = .obj

LIBS = -L$$(OSSIM_DEV_HOME)/ossim_qt/lib -L$$(OSSIM_DEV_HOME)/ossim/lib -L$$LOCAL_ROOT/lib -lossim_qt -lossim -lOpenThreads -lgeotiff -ltiff

DEFINES += OSSIMQT_USE_WINDOWS_STYLE=1

DEPENDPATH += $$(OSSIM_DEV_HOME)/ossim_qt/src $$(OSSIM_DEV_HOME)/ossim/include

INCLUDEPATH	+= $$(OSSIM_DEV_HOME)/ossim/include $$LOCAL_ROOT/include
}
