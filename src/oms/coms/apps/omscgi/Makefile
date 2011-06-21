####
# $Id: Makefile 9377 2006-08-03 18:32:03Z dburken $
####

###
# Use ../../make.opt to set things.
###
include ../../make.opt

include $(OSSIM_DEV_HOME)/ossim/Makefile.common

CPPSRCS=$(wildcard *.cpp)
CPPOBJS=$(patsubst %.cpp,%.o,$(CPPSRCS))
OBJS=$(CPPOBJS) $(COBJS) 

DEPENDS_FILES=$(wildcard *.d)

INCLUDES := -I../../include $(BASE_INCLUDES)
OSSIM_APP_LINK := $(OSSIM_APP_LINK) $(OMS_LIB_PATH)/liboms.so

BASE_DEFINES += $(OMS_DLL_IMPORT_DEFINE)

all: 	$(OBJS)
	$(CXX) $(CXXFLAGS) $(CDEBUGFLAGS) $(BASE_DEFINES) $(LDFLAGS_APP) $(OBJS) $(OSSIM_APP_LINK) -o omscgi


install:
	$(INSTALL_PROGRAM) omscgi $(OSM_CGI_INSTALL_DIR)

uninstall:
	$(RM_CMD) $(OSM_CGI_INSTALL_DIR)/omscgi

clean:
	$(RM_CMD) omscgi

depends: 	$(CPPSRCS:.cpp=.d)

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
