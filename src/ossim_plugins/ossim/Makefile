###
# $Id: Makefile 10406 2007-01-30 21:55:38Z dburken $
###

###
# Use ../make.opt to set gdal includes, gdal libs, install path.
###
include ../make.opt

###
# You must have the variable OSSIM_HOME set.
# 
# This can be put in the ../make.opt file or be an environment variable.
###
include $(OSSIM_HOME)/Makefile.common

###
# Pick up platform specific overrides.
###
include ../make_platform.opt

BASE_INCLUDES := -I.. -I. -Iotb -Ierssar $(BASE_INCLUDES)

###
# For pattern rule to make objects.
###
CPPSRCS=$(wildcard *.cpp)
CPPOBJS=$(patsubst %.cpp,%.o,$(CPPSRCS))
OBJS=$(CPPOBJS)

###
# For pattern rule to make .d files.
###
DEPENDS_FILES=$(wildcard *.d)


PLUGIN_LIB=libossim_plugin
SHARED_LIB_VERSIONLESS=$(PLUGIN_LIB).$(SO_VERSIONLESS_EXT)
SHARED_LIB_DIR=../lib
SHARED_LIB_TARGET=$(SHARED_LIB_DIR)/$(SHARED_LIB_VERSIONLESS)
SHARED_OBJ_DIR=`pwd`/$(SHARED_OBJ_DIR)

# ---
# Objects to link:
# ---
OBJECT_FILES=*.$(OBJEXT)
ALOS_PALSAR_OBJECT_FILES=AlosPalsar/*.$(OBJEXT)
ENVISAT_ASA_OBJECT_FILES=EnvisatAsar/*.$(OBJEXT)
ERS_OBJECT_FILES=erssar/*.$(OBJEXT)
OTB_OBJECT_FILES=otb/*.$(OBJEXT)
RADARSAT_OBJECT_FILES=RadarSat/*.$(OBJEXT)
RADARSAT_DATA_OBJECT_FILES=RadarSat/Data/*.$(OBJEXT)
RADARSAT_LEADER_OBJECT_FILES=RadarSat/Leader/*.$(OBJEXT)
SHARED_OBJECT_FILES=$(OBJECT_FILES) $(ALOS_PALSAR_OBJECT_FILES) $(ENVISAT_ASA_OBJECT_FILES) $(ERS_OBJECT_FILES) $(OTB_OBJECT_FILES) $(RADARSAT_OBJECT_FILES) $(RADARSAT_DATA_OBJECT_FILES) $(RADARSAT_LEADER_OBJECT_FILES)

DOT_D_FILES=*.d
INSTALL_LIB_TARGET=$(OSSIM_PLUGINS_INSTAL_LIB_DIR)/$(SHARED_LIB_VERSIONLESS)

# ---
# all target:
# 1) Make all objects.
# 2) link objects to library.
# ---
all:    depends $(OBJS)
	cd AlosPalsar; $(MAKE) all;
	cd EnvisatAsar; $(MAKE) all;
	cd erssar; $(MAKE) all;
	cd otb; $(MAKE) all;
	cd RadarSat; $(MAKE) all;

	$(LD_SHARED) -o $(SHARED_LIB_TARGET) $(SHARED_OBJECT_FILES) $(OSSIM_APP_LINK) 

# ---
# install target:
# ---
install: 
	if test "$(OSSIM_PLUGINS_INSTAL_LIB_DIR)" != "$(SHARED_LIB_DIR)" ; then $(INSTALL) -d $(OSSIM_PLUGINS_INSTAL_LIB_DIR) ; $(INSTALL_PROGRAM) $(SHARED_LIB_TARGET) $(INSTALL_LIB_TARGET) ; fi

# ---
# clean target:
# ---
clean:
	cd AlosPalsar; $(MAKE) clean;
	cd EnvisatAsar; $(MAKE) clean;
	cd erssar; $(MAKE) clean;
	cd otb; $(MAKE) clean;
	cd RadarSat; $(MAKE) clean;
	$(RM_NOPROMPT) $(DOT_D_FILES) $(SHARED_OBJECT_FILES) $(SHARED_LIB_TARGET) *~

# ---
# uninstall target:
# ---
uninstall:
	if test -f "$(INSTALL_LIB_TARGET)" ; then $(RM_NOPROMPT) $(INSTALL_LIB_TARGET) ; fi

# ---
# depends target (for .d files):
# ---
depends: $(CPPSRCS:.cpp=.d)
	cd AlosPalsar; $(MAKE) depends;
	cd EnvisatAsar; $(MAKE) depends;
	cd erssar; $(MAKE) depends;
	cd otb; $(MAKE) depends;
	cd RadarSat; $(MAKE) depends;

# ---
# Pattern rule for objects from .cpp files.
# ---
%.$(OBJEXT): %.cpp
	$(CXX) $(CXXFLAGS) $(PIC_FLAG) $(CDEBUGFLAGS) $(BASE_DEFINES) $(BASE_INCLUDES) -c $< -o $@

###
# Pattern rule for .d dependency file from .cpp files.
###
%.d: %.cpp
	$(SHELL) -ec '$(CXX) -MM $(CXXFLAGS) $(CDEBUGFLAGS) $(BASE_DEFINES) $(BASE_INCLUDES) $< >> $@;'

ifneq ( $(DEPENDS_FILES),)
-include $(DEPENDS_FILES) 
endif
