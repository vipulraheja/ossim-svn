CXX           = g++
CXXFLAGS      =  -DOSSIM_USE_WX_GUI=1 -D_FILE_OFFSET_BITS=64 -D_LARGE_FILES  -DHAVE_CONFIG_H -fPIC  -DMPI_SETTING=0 -DGDAL_SETTING=1 -DGEOTIFF_ENABLED -DFREETYPE_SETTING=1
CFLAGS        =  -DOSSIM_USE_WX_GUI=1 -D_FILE_OFFSET_BITS=64 -D_LARGE_FILES  -DHAVE_CONFIG_H -fPIC  -DMPI_SETTING=0 -DGDAL_SETTING=1 -DGEOTIFF_ENABLED -DFREETYPE_SETTING=1

INCLUDES=-I/usr/local/include/ossim #-I/usr/include/g++-3/
CCSRCS=$(wildcard *.cc)
CCOBJS=$(patsubst %.cc,%.o,$(CCSRCS))
OBJS=$(CCOBJS)
OSSIM_CORE_LIBS    =  -lossim /home/hopper/ossim/src/packages/package_install/lib/libtiff.a
LIBRARY   = $(CORE_LIBS)
DEPLIBS	  = $(OSSIM_CORE_LIBS:-l/usr/local/lib/ossim/lib%.a)

.cc.o:
	$(CXX) $(CFLAGS) $(INCLUDES) -c $< 


%.d: %.cc
	$(SHELL) -ec '$(CXX) -MM $(CFLAGS) $(INCLUDES) $< >> $@;'

all: $(OBJS) lib

lib: $(OBJS) $(DEPLIBS)
	ar -r ../../libossimbindings.a *.o
	ranlib ../../libossimbindings.a