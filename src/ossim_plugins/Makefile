###
# $Id: Makefile 14588 2009-05-20 23:45:15Z dburken $
###

###
# all target:
###
all: depends
	if test -d "gdal" ; then cd gdal; $(MAKE) all; fi
	if test -d "kakadu" ; then cd kakadu; $(MAKE) all; fi
	if test -d "ndf" ; then cd ndf; $(MAKE) all; fi
	if test -d "nitro" ; then cd nitro; $(MAKE) all; fi
	if test -d "nui" ; then cd nui; $(MAKE) all; fi
	if test -d "openjpeg" ; then cd openjpeg; $(MAKE) all; fi
	if test -d "ossim" ; then cd ossim; $(MAKE) all; fi
	if test -d "png" ; then cd png; $(MAKE) all; fi
	if test -d "registration" ; then cd registration; $(MAKE) all; fi
	if test -d "worldwind" ; then cd worldwind; $(MAKE) all; fi

###
# install target:
###
install: all
	if test -d "gdal" ; then cd gdal; $(MAKE) install; fi
	if test -d "kakadu" ; then cd kakadu; $(MAKE) install; fi
	if test -d "ndf" ; then cd ndf; $(MAKE) install; fi
	if test -d "nitro" ; then cd nitro; $(MAKE) install; fi
	if test -d "nui" ; then cd nui; $(MAKE) install; fi
	if test -d "openjpeg" ; then cd openjpeg; $(MAKE) install; fi
	if test -d "ossim" ; then cd ossim; $(MAKE) install; fi
	if test -d "png" ; then cd png; $(MAKE) install; fi
	if test -d "registration" ; then cd registration; $(MAKE) install; fi
	if test -d "worldwind" ; then cd worldwind; $(MAKE) install; fi


###
# clean target:
###
clean: make_options
	if test -d "gdal" ; then cd gdal; $(MAKE) clean; fi
	if test -d "kakadu" ; then cd kakadu; $(MAKE) clean; fi
	if test -d "ndf" ; then cd ndf; $(MAKE) clean; fi
	if test -d "nitro" ; then cd nitro; $(MAKE) clean; fi
	if test -d "nui" ; then cd nui; $(MAKE) clean; fi
	if test -d "openjpeg" ; then cd openjpeg; $(MAKE) clean; fi
	if test -d "ossim" ; then cd ossim; $(MAKE) clean; fi
	if test -d "png" ; then cd png; $(MAKE) clean; fi
	if test -d "registration" ; then cd registration; $(MAKE) clean; fi
	if test -d "worldwind" ; then cd worldwind; $(MAKE) clean; fi


####
# uninstall target:
####
uninstall: make_options
	if test -d "gdal" ; then cd gdal; $(MAKE) uninstall; fi
	if test -d "kakadu" ; then cd kakadu; $(MAKE) uninstall; fi
	if test -d "ndf" ; then cd ndf; $(MAKE) uninstall; fi
	if test -d "nitro" ; then cd nitro; $(MAKE) uninstall; fi
	if test -d "nui" ; then cd nui; $(MAKE) uninstall; fi
	if test -d "openjpeg" ; then cd openjpeg; $(MAKE) uninstall; fi
	if test -d "ossim" ; then cd ossim; $(MAKE) uninstall; fi
	if test -d "png" ; then cd png; $(MAKE) uninstall; fi
	if test -d "registration" ; then cd registration; $(MAKE) uninstall; fi
	if test -d "worldwind" ; then cd worldwind; $(MAKE) uninstall; fi


# ---
# depends target (for .d files):
# ---
depends: make_options
	if test -d "gdal" ; then cd gdal; $(MAKE) depends; fi
	if test -d "kakadu" ; then cd kakadu; $(MAKE) depends; fi
	if test -d "ndf" ; then cd ndf; $(MAKE) depends; fi
	if test -d "nitro" ; then cd nitro; $(MAKE) depends; fi
	if test -d "nui" ; then cd nui; $(MAKE) depends; fi
	if test -d "openjpeg" ; then cd openjpeg; $(MAKE) depends; fi
	if test -d "ossim" ; then cd ossim; $(MAKE) depends; fi
	if test -d "png" ; then cd png; $(MAKE) depends; fi
	if test -d "registration" ; then cd registration; $(MAKE) depends; fi
	if test -d "worldwind" ; then cd worldwind; $(MAKE) depends; fi


make_options:
	if test ! -f "make.opt" ; then \
		cp make.opt.in make.opt ; \
	fi
	if test ! -f "make_platform.opt" ; then \
		cp make_platform.opt.in make_platform.opt ; \
	fi
