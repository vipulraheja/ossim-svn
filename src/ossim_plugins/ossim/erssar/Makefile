###
# $Id: Makefile 10406 2007-01-30 21:55:38Z dburken $
###

###
# Use ../make.opt to set png includes, libs, install path.
###
include ../../make.opt

###
# You must have the variable OSSIM_HOME set.
# 
# This can be put in the ../make.opt file or be an environment variable.
###
include $(OSSIM_HOME)/Makefile.common

###
# Pick up platform specific overrides.
###
include ../../make_platform.opt

BASE_INCLUDES := -I.. -I. $(PNG_INCLUDES) $(BASE_INCLUDES)

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

SHARED_OBJECT_FILES=*.$(OBJEXT)
DOT_D_FILES=*.d

# ---
# all target:
# 1) Make all objects.
# ---
all:    depends $(OBJS)

# ---
# clean target:
# ---
clean:
	$(RM_NOPROMPT) $(DOT_D_FILES) $(SHARED_OBJECT_FILES) *~

# ---
# depends target (for .d files):
# ---
depends: $(CPPSRCS:.cpp=.d)

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
