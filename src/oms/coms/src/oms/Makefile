####
# $Id: Makefile 13544 2008-09-08 14:09:48Z gpotts $
####

###
# Use ../make.opt to set things.
#
# REQUIRES OSSIM_DEV_HOME environment variable.
###
include ../../make.opt

include $(OSSIM_DEV_HOME)/ossim/Makefile.common

###
# INSTALL DIRECTORY:
# NOTE you can override at make time like this:
# make prefix=/usr/local
###
# prefix=$(OMS_HOME)
prefix=$(OMS_INSTALL_ROOT)

INCLUDES := $(OMS_INCLUDES) $(BASE_INCLUDES) -I$(FFMPEG_INSTALL)/include -I$(FFMPEG_INSTALL)/include/ffmpeg

BASE_DEFINES += $(PREDATOR_DEFINE) $(OMS_DLL_EXPORT_DEFINE)

DEPENDS_FILES=$(wildcard *.d)

CPPSRCS=$(wildcard *.cpp)
CPPOBJS=$(patsubst %.cpp,%.o,$(CPPSRCS))
OBJS=$(CPPOBJS) $(COBJS)

INSTALLED_DIRS = $(OMS_INST_INC) $(OMS_INST_LIB)
INCLUDE_FILES=$(wildcard $(OMS_INCLUDE_PATH)/oms/*.h)


libdir=$(prefix)/lib
includedir=$(prefix)/include/oms

SHARED_LIB=liboms.$(SO_VERSIONLESS_EXT)
SHARED_LIB_TARGET= $(OMS_LIB_PATH)/$(SHARED_LIB)
LINK_SHARED_OBJECT_FILES=*.$(OBJEXT)

# linux stuff #
ifeq ($(HOST_RESULT),linux)
# Override for linux to just do a straight link. 
LD_SHARED=$(CXX) -shared 
endif

all: depends $(OBJS)
	$(LD_SHARED) -o $(SHARED_LIB_TARGET) \
	$(LINK_SHARED_OBJECT_FILES) -L$(OSSIM_HOME)/lib/ossim -lossim $(OSSIM_LIB_LINK) -L/usr/local/lib $(PREDATOR_LIB) 


clean:
	$(RM) -f $(SHARED_LIB_TARGET)
	$(RM_CMD)

depends: 	$(CPPSRCS:.cpp=.d)

install: all
	if test "$(prefix)" != "$(OMS_HOME)" ; then \
		$(INSTALL) -d $(libdir); \
		$(INSTALL) -d $(includedir); \
		$(INSTALL) $(SHARED_LIB_TARGET) $(libdir)/$(SHARED_LIB) ; \
		( cd $(OMS_INCLUDE_PATH) ; \
			for h in `find . -name "*.h"` ; do \
				$(INSTALL) -m 664 $$h $(includedir)/$$h; \
			done ; \
		) \
	fi

uninstall:
	if test "$(prefix)" != "$(OMS_HOME)" ; then \
		$(RM) -f $(libdir)/$(SHARED_LIB) ; \
		( cd $(OMS_INCLUDE_PATH) ; \
			for h in `find . -name "*.h"` ; do \
				$(RM) -f $(includedir)/$$h; \
			done ; \
		) \
	fi

###
# Pattern rule for objects from .cpp files.
###
%.$(OBJEXT): %.cpp
	$(CXX) $(CXXFLAGS) $(PIC_FLAG) $(CDEBUGFLAGS) $(BASE_DEFINES) $(INCLUDES) -c $< -o $@

###
# Pattern rule for .d dependency file from .cpp files.
###
%.d: %.cpp
	$(SHELL) -ec '$(CXX) -MM $(PIC_FLAG) $(CXXFLAGS) $(CDEBUGFLAGS) $(BASE_DEFINES) $(INCLUDES) $< >> $@;'

ifneq ( $(DEPENDS_FILES),)
-include $(DEPENDS_FILES) 
endif
