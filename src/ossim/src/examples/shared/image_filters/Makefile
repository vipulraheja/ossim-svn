include /Users/Shared/Development/ossim/Makefile.common
include ../../../../makelib.mak

all: $(OBJS) ossimSharedRgbToGreyFilter.$(SO_VERSIONLESS_EXT)

ossimSharedRgbToGreyFilter.$(SO_VERSIONLESS_EXT): $(OBJS)
	$(CC) $(LD_SHARED) $(OBJS) $(OSSIM_APP_LINK) -o $@
