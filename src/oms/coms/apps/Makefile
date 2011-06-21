###
# $Id: Makefile 10395 2007-01-29 19:43:49Z dburken $
###

include ../make.opt

include $(OSSIM_DEV_HOME)/ossim/Makefile.common

INCLUDES := -I../include $(BASE_INCLUDES)

OSSIM_APP_LINK := $(OSSIM_APP_LINK) -L$(OMS_LIB_PATH) -loms

prefix=$(OMS_INSTALL_ROOT)
bindir=$(prefix)/bin

all:
	$(CXX) $(CXXFLAGS) $(CDEBUGFLAGS) $(BASE_DEFINES) $(INCLUDES) -c oms-image-info.cpp -o oms-image-info.o
	$(CXX) $(CXXFLAGS) $(CDEBUGFLAGS) $(BASE_DEFINES) $(INCLUDES) oms-image-info.o $(OSSIM_APP_LINK) -o oms-image-info 


clean:
	$(RM) -f *.o *~ oms-image-info *.d

depends:
	$(SHELL) -ec '$(CXX) -MM $(CXXFLAGS) $(CDEBUGFLAGS) $(BASE_DEFINES) $(INCLUDES) oms-image-info.cpp >> oms-image-info.d;'

install:
	if test "$(prefix)" != "$(OMS_HOME)" ; then \
		$(INSTALL) -d $(bindir); \
	fi
	$(INSTALL_PROGRAM) oms-image-info $(bindir)/oms-image-info


uninstall:
	$(RM) -f $(bindir)/oms-image-info

