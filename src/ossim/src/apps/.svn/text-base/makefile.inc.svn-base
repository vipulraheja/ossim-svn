###
# $Id: makefile.vc 7049 2004-12-03 14:45:36Z dburken $
#
#  Include file for making windows executables using nmake.
###

OSSIM_ROOT	= ..\..\..
BIN_DIR     	= $(OSSIM_ROOT)\bin

!INCLUDE $(OSSIM_ROOT)\nmake.opt

###
# Note: EMBED_MANIFEST variable is set in nmake.opt so make sure it is included
# before this test.
###
!if "$(EMBED_MANIFEST)" == "1"
!include ..\..\makefile.inc
OSSIM_VC_MANIFEST_EMBED_EXE=$(_VC_MANIFEST_EMBED_EXE)
OSSIM_VC_MANIFEST_CLEAN=$(_VC_MANIFEST_CLEAN)
!else
OSSIM_VC_MANIFEST_EMBED_EXE=
OSSIM_VC_MANIFEST_CLEAN=
!endif

default:	$(PROGRAM).exe

all:	default

$(PROGRAM).exe:	$(PROGRAM).cpp
	$(CC) $(APP_CFLAGS) $(PROGRAM).cpp $(OSSIM_LINK)
	$(OSSIM_VC_MANIFEST_EMBED_EXE)

clean:
	$(RM) *.obj *.exe *.manifest *~
	$(OSSIM_VC_MANIFEST_EMBED_EXE)

install:	default
	$(CP) *.exe $(BIN_DIR)

!if "$(EMBED_MANIFEST)" == "1"
!include ..\..\makefile.targ.inc
!endif
