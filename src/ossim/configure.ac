dnl ---
dnl $Id: configure.ac 16665 2010-02-24 19:01:26Z gpotts $
dnl ---

dnl Required initialization macro
AC_INIT([ossim],[1.8.4],[http://bugzilla.remotesensing.org])

dnl Configure include/ossim/ossimConfig.h from include/ossim/ossimConfig.h.in
AC_CONFIG_HEADER(include/ossim/ossimConfig.h)

OSSIM_TOP=`pwd`
TOP=${OSSIM_TOP}
top_builddir=${TOP}

AC_CONFIG_AUX_DIR(${OSSIM_TOP})

OSSIM_MAJOR_VERSION_NUMBER=1
OSSIM_MINOR_VERSION_NUMBER=8
OSSIM_RELEASE_NUMBER=4


OSSIM_VERSION=${OSSIM_MAJOR_VERSION_NUMBER}.${OSSIM_MINOR_VERSION_NUMBER}.${OSSIM_RELEASE_NUMBER}

AC_DEFINE_UNQUOTED(OSSIM_MAJOR_VERSION_NUMBER, ${OSSIM_MAJOR_VERSION_NUMBER} )
AC_DEFINE_UNQUOTED(OSSIM_MINOR_VERSION_NUMBER, ${OSSIM_MINOR_VERSION_NUMBER} )
AC_DEFINE_UNQUOTED(OSSIM_RELEASE_NUMBER, ${OSSIM_RELEASE_NUMBER} )
AC_DEFINE_UNQUOTED(OSSIM_VERSION, "${OSSIM_VERSION}" )

dnl ---
dnl 1) Check for programs section...
dnl ---

dnl Set the "INSTALL" variable.
AC_PROG_INSTALL

dnl Set the "RANLIB" varaible.
AC_PROG_RANLIB

dnl Start with blank compiler flags and base defines.
CFLAGS=""
CXXFLAGS=""
BASE_DEFINES=""

dnl Set the "CC" variable.
AC_PROG_CC(xlc gcc cl cc egcs)

dnl Set the "CXX" variable.
AC_PROG_CXX(xlC g++ cl CC cxx c++ cc++ aCC egcs)

dnl Set the "CPP" variable.
AC_PROG_CPP

dnl Set the "CXXCPP" variable.  This will also set GXX to yes if using gnu.
AC_PROG_CXXCPP

dnl Set the "EXEEXT" or executable extension.
AC_EXEEXT

dnl Set the "OBJEXT" or object extension.
AC_OBJEXT

AC_CHECK_PROG(AR, ar, ar, ar)
AC_CHECK_PROG(ECHO, echo, echo, echo)
AC_CHECK_PROG(RM, rm, rm, rm)
AC_CHECK_PROG(STRIP, strip, strip, strip)
AC_CHECK_PROG(DIRNAME, dirname, dirname)
AC_CHECK_PROG(SED, sed, sed)
AC_CHECK_PROG(CHMOD, chmod, chmod)

dnl ----
dnl AC_CHECK_LIB will define a standard system lib variable "$(LIB)"
dnl that will check all standard libraries
dnl ---

dnl This library may be required by Python 2.0
AC_CHECK_LIB(util, openpty)
AC_CHECK_LIB(dl, dlopen)
AC_CHECK_LIB(m, sin)
AC_CHECK_LIB(z, main)

AC_CHECK_LIB(pthread, pthread_attr_init)
dnl Now check the Size support

AC_CHECK_SIZEOF(float, 4)
AC_CHECK_SIZEOF(double, 8)
AC_CHECK_SIZEOF(long long, 8)
AC_CHECK_SIZEOF(long int, 4)
AC_CHECK_SIZEOF(int, 4)
AC_CHECK_SIZEOF(short int, 2)

dnl ---
dnl Compute the canonical host-system type variable, host, and its three 
dnl individual parts host_cpu, host_vendor, and host_os.
dnl host can be set with `--host` option.
dnl ---
AC_CANONICAL_HOST
echo "Host type:  ${host}"

dnl ---
dnl 2) Check for headers section.
dnl ---

dnl Defines "STDC_HEADERS"
AC_HEADER_STDC

dnl If you want to check for functions (currently no checks) it would go here.
dnl Like:  AC_CHECK_FUNCS(strchr memcpy)


AC_CHECK_HEADERS(fcntl.h unistd.h dbmalloc.h dlfcn.h malloc.h getopt.h dirent.h libtar.h)
AC_CHECK_HEADER(zlib.h, [AC_DEFINE(OSSIM_HAS_LIBZ)])

echo "HAVE ZLIB ===================================== ${HAVE_ZLIB_H}"

dnl ---
dnl 3) Check for libraries section.
dnl ---

dnl Check for libtiff support (required)...
OSSIM_CHECK_LIBTIFF

dnl Check for jpeg support (required)...
OSSIM_CHECK_JPEG

dnl Check for geotiff support (required)...
OSSIM_CHECK_GEOTIFF

dnl Check for the mpi package (not required)...
OSSIM_CHECK_MPI

dnl Check for OpenThreads (required)...
OSSIM_CHECK_OPEN_THREADS

dnl Check for freetype package (not required)...
OSSIM_CHECK_FREETYPE

dnl Check for program prefix for apps, like prefix = ossim_ , igen = ossim_igen
OSSIM_CHECK_PROGRAM_PREFIX

BASE_DEFINES="${BASE_DEFINES} ${GEOTIFF_DEFINES}"

OSSIM_USE_UNIX=0
OSSIM_USE_WIN32=0
OSSIM_USE_MAC=0

OSSIM_USE_CYGWIN=0
OSSIM_USE_LINUX=0
OSSIM_USE_SGI=
OSSIM_USE_HPUX=
OSSIM_USE_SYSV=
OSSIM_USE_SVR4=
OSSIM_USE_AIX=
OSSIM_USE_SUN=
OSSIM_USE_SOLARIS=
OSSIM_USE_SUNOS=
OSSIM_USE_ALPHA=
OSSIM_USE_OSF=
OSSIM_USE_BSD=
OSSIM_USE_DARWIN=
OSSIM_USE_MAC=
OSSIM_USE_FREEBSD=
OSSIM_USE_OPENBSD=
OSSIM_USE_NETBSD=
OSSIM_USE_VMS=
OSSIM_USE_ULTRIX=
TOOLKIT_VERSION=
WIDGET_SET=
HOST_RESULT=linux
lib_unicode_suffix=
lib_debug_suffix=
OSSIM_HOST_INCLUDE=
OSSIM_HOST_LIB=
CARBON=
LDFLAGS_EXE=
LDFLAGS_APP=

dnl ---
dnl Shared library variables:
dnl Defaulted to linux behavior, override switch on host.
dnl ---
ossimBuildSharedLibraries="no"
OSSIM_ARG_ENABLE(sharedOssimLibraries,   [  --enable-sharedOssimLibraries build shared ossim libraries(default=no)], ossimBuildSharedLibraries)
                                                                              
ossimBuildStaticLibraries="no"
OSSIM_ARG_ENABLE(staticOssimLibraries,   [  --enable-staticOssimLibraries build static ossim libraries(default=no)], ossimBuildStaticLibraries)

ossimBuildSingleSharedLibrary="yes"
OSSIM_ARG_ENABLE(singleSharedOssimLibrary,   [  --enable-singleSharedOssimLibrary build single shared ossim library(default=yes)], ossimBuildSingleSharedLibrary)
                                                                              
ossimBuildSingleStaticLibrary="no"
OSSIM_ARG_ENABLE(singleStaticOssimLibrary,   [  --enable-singleStaticOssimLibrary build single static ossim librarie(default=no)], ossimBuildSingleStaticLibrary)

ossimLinkApplicationsStatic="no"
OSSIM_ARG_ENABLE(staticOssimApps,   [  --enable-staticOssimApps build static ossim apps(default=no)], ossimLinkApplicationsStatic)

BUILD_SHARED_OBJS="no"
BUILD_STATIC_OBJS="no"
BUILD_SHARED_LIBS=${ossimBuildSharedLibraries}
BUILD_STATIC_LIBS=${ossimBuildStaticLibraries}
BUILD_SINGLE_SHARED_LIBS=${ossimBuildSingleSharedLibrary}
BUILD_SINGLE_STATIC_LIBS=${ossimBuildSingleStaticLibrary}
BUILD_STATIC_APPS=${ossimLinkApplicationsStatic}


dnl --- 
dnl Do some sanity checks...  You have to build at least one library.
dnl ---
if test "$BUILD_STATIC_LIBS"        = "no" && \
   test "$BUILD_SHARED_LIBS"        = "no" && \
   test "$BUILD_SINGLE_STATIC_LIBS" = "no" && \
   test "$BUILD_SINGLE_SHARED_LIBS" = "no" ; then \
   AC_MSG_ERROR("ERROR:  Both build static and shared library disabled!") ; 
fi


dnl ---
dnl Enable / disable object builds.
dnl ---
if test "$BUILD_STATIC_LIBS"        = "yes" || \
   test "$BUILD_SINGLE_STATIC_LIBS" = "yes" ; then \
   BUILD_STATIC_OBJS="yes" ;
fi
if test "$BUILD_SHARED_LIBS"        = "yes" || \
   test "$BUILD_SINGLE_SHARED_LIBS" = "yes" ; then \
   BUILD_SHARED_OBJS="yes" ;
fi

dnl ---
dnl Check for trying to link static without static library.
dnl---
if test "$BUILD_STATIC_APPS" = "yes" && test "$BUILD_STATIC_OBJS" = "no" ; then AC_MSG_ERROR("ERROR:  Cannot link apps statically if static library build is turned off!") ; fi

if test "$BUILD_STATIC_APPS" = "yes" && test "$BUILD_STATIC_LIBS" = "no" && test "$BUILD_SINGLE_STATIC_LIBS" = "no" ; then AC_MSG_ERROR("ERROR:  Cannot link apps statically if static library build is turned off!") ; fi

dnl ---
dnl Set the LDFLAG for application link.
dnl ---
if test "$BUILD_STATIC_APPS" = "yes" ; then 
  LDFLAGS_APP="-static"
  AC_DEFINE(OSSIM_DYNAMIC_ENABLED, 0)
fi

SHARED_OBJ_DIR=".shared_obj"
STATIC_OBJ_DIR=".static_obj"

SO_VERSIONLESS_EXT="so"
SO_SONAME_EXT="${SO_VERSIONLESS_EXT}.${OSSIM_MAJOR_VERSION_NUMBER}"
SO_REALNAME_EXT="${SO_VERSIONLESS_EXT}.${OSSIM_VERSION}"
LD_SHARED="${CXX} -shared -Wl,-soname,\$(SHARED_LIB_SONAME)"

LDFLAGS=""
PIC_FLAG="-fPIC"
AR_FLAGS="cru"


dnl --------------------------------------------------------------------------
dnl HOST specific stuff goes here...
dnl To support a new system, you need to add its canonical name (as determined
dnl by config.sub or specified by the configure command line) to this "case"
dnl and also define the shared library flags below - search for
dnl SHARED_LIB_SETUP to find the exact place
dnl --------------------------------------------------------------------------

SPECIALIZED_MAKEFILE_DIR="unx"
case "${host}" in
  *-hp-hpux* )
    OSSIM_USE_HPUX=1
    NEEDS_D_REENTRANT_FOR_R_FUNCS=1
    SO_VERSIONLESS_EXT=sl
    AC_DEFINE(__OSSIM_HPUX__)
    HOST_RESULT=hpux
    SO_VERSIONLESS_EXT=sl
  ;;
  *-*-linux* )
    OSSIM_USE_LINUX=1
    AC_DEFINE(__OSSIM_LINUX__)
    TMP=`uname -m`
    if test "x$TMP" = "xalpha"; then
      OSSIM_USE_ALPHA=1
      AC_DEFINE(__OSSIM_ALPHA__)
    fi
    HOST_RESULT=linux
  ;;
  *-*-irix5* | *-*-irix6* )
    OSSIM_USE_SGI=1
    OSSIM_USE_SVR4=1
    AC_DEFINE(__OSSIM_SGI__)
    AC_DEFINE(__OSSIM_SVR4__)
    HOST_RESULT=irix
  ;;
  *-*-solaris2* )
    OSSIM_USE_SUN=1
    OSSIM_USE_SOLARIS=1
    OSSIM_USE_SVR4=1
    AC_DEFINE(__OSSIM_SUN__)
    AC_DEFINE(__OSSIM_SOLARIS__)
    AC_DEFINE(__OSSIM_SVR4__)
    NEEDS_D_REENTRANT_FOR_R_FUNCS=1
    HOST_RESULT=solaris
    SPECIALIZED_MAKEFILE_DIR="solaris"
  ;;
  *-*-sunos4* )
    OSSIM_USE_SUN=1
    OSSIM_USE_SUNOS=1
    OSSIM_USE_BSD=1
    AC_DEFINE(__OSSIM_SUN__)
    AC_DEFINE(__OSSIM_SUNOS__)
    AC_DEFINE(__OSSIM_BSD__)
    HOST_RESULT=sunos
  ;;
  *-*-freebsd*)
    OSSIM_USE_BSD=1
    OSSIM_USE_FREEBSD=1
    AC_DEFINE(__OSSIM_FREEBSD__)
    AC_DEFINE(__OSSIM_BSD__)
    HOST_RESULT=freebsd
  ;;
  *-*-openbsd*)
    OSSIM_USE_BSD=1
    OSSIM_USE_OPENBSD=1
    AC_DEFINE(__OSSIM_FREEBSD__)
    AC_DEFINE(__OSSIM_OPENBSD__)
    HOST_RESULT=openbsd
  ;;
  *-*-netbsd*)
    OSSIM_USE_BSD=1
    OSSIM_USE_NETBSD=1
    AC_DEFINE(__OSSIM_FREEBSD__)
    AC_DEFINE(__OSSIM_NETBSD__)
    HOST_RESULT=netbsd
  ;;
  *-*-osf* )
    OSSIM_USE_ALPHA=1
    OSSIM_USE_OSF=1
    AC_DEFINE(__OSSIM_ALPHA__)
    AC_DEFINE(__OSSIM_OSF__)
    NEEDS_D_REENTRANT_FOR_R_FUNCS=1
    HOST_RESULT=osf
  ;;
  *-*-dgux5* )
    OSSIM_USE_ALPHA=1
    OSSIM_USE_SVR4=1
    AC_DEFINE(__OSSIM_ALPHA__)
    AC_DEFINE(__OSSIM_SVR4__)
    HOST_RESULT=dgux5
  ;;
  *-*-sysv5* )
    OSSIM_USE_SYSV=1
    OSSIM_USE_SVR4=1
    AC_DEFINE(__OSSIM_SYSV__)
    AC_DEFINE(__OSSIM_SVR4__)
    HOST_RESULT=sysv5
  ;;
  *-*-aix* )
    OSSIM_USE_AIX=1
    OSSIM_USE_SYSV=1
    OSSIM_USE_SVR4=1
    dnl Irvin Probst <irvin.probst@fr.thalesgroup.com> reports that the shared
    dnl libraries under AIX have the same suffix as the normal ones
    SO_VERSIONLESS_EXT=a
    AC_DEFINE(__OSSIM_AIX__)
    AC_DEFINE(__OSSIM_SYSV__)
    AC_DEFINE(__OSSIM_SVR4__)
    HOST_RESULT=aix
  ;;

  *-*-cygwin* )
    SO_VERSIONLESS_EXT=dll
    PROGRAM_EXT=".exe"
    RESCOMP=windres
    AC_DEFINE(__OSSIM_CYGWIN__)
    OSSIM_USE_CYGWIN=1
    HOST_RESULT=cygwin
    PIC_FLAG=""
    SPECIALIZED_MAKEFILE_DIR="cygwin"
  ;;
  
  *-*-mingw32* )
    SO_VERSIONLESS_EXT=dll
    PROGRAM_EXT=".exe"
    RESCOMP=windres
    AC_DEFINE(__OSSIM_CYGWIN__)
    OSSIM_USE_CYGWIN=1
    HOST_RESULT=mingw32
    LDFLAGS="$LDFLAGS -Wl,--subsystem,windows -mwindows -mthreads"
    CFLAGS="${CFLAGS} -mthreads"
    CXXFLAGS="${CXXFLAGS} -mthreads"
    PIC_FLAG="-DPIC"
    SPECIALIZED_MAKEFILE_DIR="mingw"
    LIBS="$LIBS -ljpeg"
  ;;

  *-pc-msdosdjgpp )
    OSSIM_USE_UNIX=0
    OSSIM_USE_DOS=1
    AC_DEFINE(__OSSIM_DOS__)
    PROGRAM_EXT=".exe"
    dnl DJGPP needs explicit -lstdc++ for some reason (VS: mayb some versions only?)
    LIBS="$LIBS -lstdc++"
    HOST_RESULT=msdosdjgpp
  ;;

  *-pc-os2_emx | *-pc-os2-emx )
    AC_DEFINE(__OSSIM_EMX__)
    PROGRAM_EXT=".exe"
    LIBS="$LIBS -lstdcpp"
    HOST_RESULT=os2_emx
  ;;

  *-darwin* )
    dnl PowerPC Darwin based distributions (including Mac OS X)
    SO_VERSIONLESS_EXT="dylib"
    SO_SONAME_EXT="${OSSIM_MAJOR_VERSION_NUMBER}.${SO_VERSIONLESS_EXT}"
    SO_REALNAME_EXT="${OSSIM_VERSION}.${SO_VERSIONLESS_EXT}"
    OSSIM_USE_BSD=1
    OSSIM_USE_DARWIN=1
    OSSIM_USE_MAC=1
    TOOLKIT=MAC
    SO_VERSIONLESS_EXT=dylib
    AC_DEFINE(__OSSIM_BSD__)
    AC_DEFINE(__OSSIM_DARWIN__)
    AC_DEFINE(__OSSIM_POWERPC__)
    CARBON="-DCARBON"
    CFLAGS="${CFLAGS} -Wno-long-double -DDARWIN -DMACOSX -no-cpp-precomp"
    CXXFLAGS="${CXXFLAGS} -Wno-long-double -DDARWIN -DMACOSX -no-cpp-precomp"
    OSSIM_HOST_INCLUDE="${OSSIM_HOST_INCLUDE} -I/sw/include"
    OSSIM_HOST_LIB="${OSSIM_HOST_LIB} -L/sw/lib"
    LD_FLAGS="-dynamiclib -compatibility_version ${OSSIM_MAJOR_VERSION_NUMBER}.${OSSIM_MINOR_VERSION_NUMBER} -current_version ${OSSIM_VERSION} -install_name ${INSTALL_NAME} -single_module -undefined dynamic_lookup "
    dnl SO_VERSIONLESS_EXT="dylib"
    HOST_RESULT=darwin
    SPECIALIZED_MAKEFILE_DIR="macosx"
  ;;

  *-*-beos* )
    dnl leave OSSIM_USE_UNIX on - BeOS is sufficiently Unix-like for this
    OSSIM_USE_BEOS=1
    AC_DEFINE(__OSSIM_BEOS__)
    HOST_RESULT=beos
  ;;

  *)
    AC_MSG_ERROR(unknown system type ${host}.)
esac

TOOLKIT_DIR=`echo ${TOOLKIT} | tr "[[A-Z]]" "[[a-z]]"`

if test "$ac_cv_sizeof_float" = "4" ; then
	AC_DEFINE(OSSIM_SIZEOF_FLOAT, 4)
else
	echo "WARNING: float is not 4 bytes setting to 0 bytes"
	AC_DEFINE(OSSIM_SIZEOF_FLOAT, 0)
fi

if test "$ac_cv_sizeof_double" = "8" ; then
	AC_DEFINE(OSSIM_SIZEOF_DOUBLE, 8)
else
	echo "WARNING: double is not 8 bytes setting to 0 bytes"
	AC_DEFINE(OSSIM_SIZEOF_DOUBLE, 0)
fi


if test "$ac_cv_sizeof_long_int" = "4" ; then
	AC_DEFINE(OSSIM_SIZEOF_LONG_INT, 4)
elif test "$ac_cv_sizeof_long_int" = "8" ; then
	AC_DEFINE(OSSIM_SIZEOF_LONG_INT, 8)
else
	echo "WARNING: long int  is not 4 or 8  bytes setting to 0 bytes"
	AC_DEFINE(OSSIM_SIZEOF_DOUBLE, 0)
fi

if test "$ac_cv_sizeof_long_long" = "4" ; then
	AC_DEFINE(OSSIM_SIZEOF_LONG_LONG, 4)
elif test "$ac_cv_sizeof_long_long" = "8" ; then
	AC_DEFINE(OSSIM_SIZEOF_LONG_LONG, 8)
else 
	echo "WARNING: long long  is not 4 or 8  bytes setting to 0 bytes"
	AC_DEFINE(OSSIM_SIZEOF_DOUBLE, 0)
fi

if test "$ac_cv_sizeof_short_int" = "2" ; then
	AC_DEFINE(OSSIM_SIZEOF_SHORT_INT, 2)
else
	echo "WARNING: long int  is not 4 or 8  bytes setting to 0 bytes"
	AC_DEFINE(OSSIM_SIZEOF_SHORT_INT, 0)
fi

if test "$ac_cv_sizeof_int" = "4" ; then
	AC_DEFINE(OSSIM_SIZEOF_INT, 4)
else
	echo "WARNING: int is not 4 bytes setting to 0 bytes"
	AC_DEFINE(OSSIM_SIZEOF_INT, 0)
fi



dnl We really need a relatively recent libtiff, at least a 3.5.x version.
dnl AC_CHECK_LIB(tiff, TIFFReadRGBATile)

dnl Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T

AC_SYS_LARGEFILE

if test "x$ossim_largefile" = "xyes"; then
    if test "x$ac_cv_sys_file_offset_bits" = "x64"; then
        OSSIM_LARGEFILE_FLAGS="-D_FILE_OFFSET_BITS=64 -D_LARGE_FILES"
    else
         OSSIM_LARGEFILE_FLAGS="-D_LARGE_FILES"
     fi
 
     dnl Added to base defines.
     BASE_DEFINES="${BASE_DEFINES} ${OSSIM_LARGEFILE_FLAGS}"
fi

dnl CXXFLAG getting wiped slick up above somewhere so set this again...
if test "$OSSIM_USE_AIX" = "1"; then
    CXXFLAGS="${CXXFLAGS}"
    dnl Use the native compiler over gcc...
    CXX="xlC"
    CC="xlc"
fi

ossimSHARED_LIBRARY="yes"
ossimDEBUG_FLAG="no"
ossimOPTIMIZATION_FLAG="yes"
ossimWARN_ALL_FLAG="yes"

OSSIM_ARG_ENABLE(debug,       [  --enable-debug          add debug flag], ossimDEBUG_FLAG)

dnl If debug is set above default the ossimOPTIMIZATION_FLAG to no...
dnl They can still turn optimization on with the next line.
if test "$ossimDEBUG_FLAG" = "yes" ; then
	ossimOPTIMIZATION_FLAG="no"
fi

OSSIM_ARG_ENABLE(optimization,[  --enable-optimization   add optimization], ossimOPTIMIZATION_FLAG)
OSSIM_ARG_ENABLE(warn_all,    [  --enable-warn_all       enable -Wall compiler option], ossimWARN_ALL_FLAG)

DEBUG_FLAG=""
OPTIMIZATION_FLAG=""
WARN_OPTION=""

if test "$ossimDEBUG_FLAG" = "yes" ; then
	DEBUG_FLAG="-g"
else
	DEBUG_FLAG=""
fi

dnl -------------------------
dnl NOTE:
dnl The -O3 flag has given us grief with the templates on older gcc compilers
dnl (3.2 in particular); hence, back to -O2...
dnl 
dnl You can override at make time with: "make CDEBUGFLAGS=-O3"
dnl -------------------------
if test "$ossimOPTIMIZATION_FLAG" = "yes"  ; then
	OPTIMIZATION_FLAG="-O2"
	case "${host}" in
		*-darwin* )
#			had to comment out since creates internal compile error for file
#			vpftidx.c in vpf_util directory
#			OPTIMIZATION_FLAG="-fast"
			OPTIMIZATION_FLAG="-O2"
		;;
	      *-*-mingw32* | *-*-cygwin* )
			OPTIMIZATION_FLAG="-O2"
		;;
	esac

else
	OPTIMIZATION_FLAG=""
fi

if test "$ossimWARN_ALL_FLAG" = "yes"  ; then
	WARN_OPTION="-Wall"
fi

CFLAGS="${CFLAGS} ${WARN_OPTION} -pipe"
CXXFLAGS="${CXXFLAGS} ${WARN_OPTION} -pipe"
CDEBUGFLAGS="${DEBUG_FLAG} ${OPTIMIZATION_FLAG}"

dnl OSSIM_CONFIGURE_PACKAGES

cd ${OSSIM_TOP}

echo "Host:  ${host}"

if test "$ossimSHARED_LIBRARY" = "yes" ; then

   BUILD_SHARED=yes
   SHARED_OBJ_DIR=.shared_obj

   case "${host}" in
      *-hp-hpux* )
      ;;
      *-*-linux* )
      ;;
      *-*-solaris2* )
	LD_SHARED="${CXX} -shared "
      ;;
      *-*-sunos4* )
	LD_SHARED="${CXX} -shared "
      ;;
      *-*-darwin* )
	LD_SHARED="${CXX} -dynamiclib  -single_module -flat_namespace -undefined suppress"
      ;;
      *-*-aix* )
      ;;
      *-*-mingw32* | *-*-cygwin* )
         LD_SHARED="dllwrap.exe --output-def \$(OSSIM_DLL_DEF) --implib \$(OSSIM_IMP_LIB) --export-all --driver-name=\$(CXX)"
         PIC_FLAG="-DPIC"
      ;;
      *-*-beos* )
         LD_SHARED="${LD} -shared"
      ;;
      *-*-freebsd* | *-*-openbsd* | *-*-netbsd* | \
                     *-*-sunos4* | \
                     *-*-irix5* | *-*-irix6* | \
                     *-*-osf* | \
                     *-*-dgux5* | \
                     *-*-sysv5* )
			dnl defaults are ok
      ;;
      *)
         AC_MSG_ERROR(unknown system type $host.)
   esac
	
fi

dnl ---
dnl Add pthread needed by static build right now.  
dnl We should add a test for this perhaps(drb).
dnl ---
LIBS="${LIBS}"

echo "BASE_DEFINES from configure:  ${BASE_DEFINES}"
echo "LIBS from configure:  ${LIBS}"

CFLAGS="${CFLAGS} ${DEFS}"
CXXFLAGS="${CXXFLAGS} ${DEFS}"

dnl
dnl  Now setup the ossim-config file for install locations
dnl  

if test "$OSSIM_USE_CYGWIN" = "1" ; then
 ADDITIONAL_GUI_LIBS="-lrpcrt4 -loleaut32 -lole32 -luuid -lwinspool -lwinmm -lshell32 -lcomctl32 -lctl3d32 -ladvapi32 -lwsock32 -lkernel32 -luser32 -lgdi32 -lcomdlg32"
fi

INCLUDE_COMMON="include ${TOP}/Makefile.common"

dnl _____________________ START DOING SOME SUBSTITUTIONS _________________
dnl
dnl

AC_SUBST(OSSIM_TOP, $OSSIM_TOP)
AC_SUBST(top_builddir, $top_builddir)
AC_SUBST(OSSIM_MAJOR_VERSION_NUMBER, $OSSIM_MAJOR_VERSION_NUMBER)
AC_SUBST(OSSIM_MINOR_VERSION_NUMBER, $OSSIM_MINOR_VERSION_NUMBER)
AC_SUBST(OSSIM_RELEASE_NUMBER, $OSSIM_RELEASE_NUMBER)
AC_SUBST(OSSIM_VERSION, $OSSIM_VERSION)
AC_SUBST(BUILD_SHARED_OBJS, $BUILD_SHARED_OBJS)
AC_SUBST(BUILD_STATIC_OBJS, $BUILD_STATIC_OBJS)
AC_SUBST(BUILD_SHARED_LIBS, $BUILD_SHARED_LIBS)
AC_SUBST(BUILD_STATIC_LIBS, $BUILD_STATIC_LIBS)
AC_SUBST(BUILD_SINGLE_SHARED_LIBS, $BUILD_SINGLE_SHARED_LIBS)
AC_SUBST(BUILD_SINGLE_STATIC_LIBS, $BUILD_SINGLE_STATIC_LIBS)
AC_SUBST(BUILD_STATIC_APPS, $BUILD_STATIC_APPS)
AC_SUBST(SHARED_OBJ_DIR)
AC_SUBST(STATIC_OBJ_DIR)
AC_SUBST(SO_VERSIONLESS_EXT, $SO_VERSIONLESS_EXT)
AC_SUBST(SO_SONAME_EXT, $SO_SONAME_EXT)
AC_SUBST(SO_REALNAME_EXT, $SO_REALNAME_EXT)
AC_SUBST(SHARED_LIB_FLAG, $SHARED_LIB_FLAG)
AC_SUBST(PIC_FLAG, $PIC_FLAG)
AC_SUBST(RESCOMP)
AC_SUBST(RESFLAGS)
AC_SUBST(MACOSX_BUNDLE)
AC_SUBST(TOOLKIT_DIR)
AC_SUBST(LIBOSSIMMACRES)
AC_SUBST(LIBOSSIMMACRESCOMP)
AC_SUBST(OSSIM_RESOURCES_MACOSX_DATA)
AC_SUBST(OSSIM_RESOURCES_MACOSX_TEXT)
AC_SUBST(CFLAGS, $CFLAGS)
AC_SUBST(CXXFLAGS, $CXXFLAGS)
AC_SUBST(CDEBUGFLAGS, $CDEBUGFLAGS)
AC_SUBST(BASE_DEFINES, $BASE_DEFINES)
AC_SUBST(AR_FLAGS, $AR_FLAGS)
AC_SUBST(HOST_RESULT, $HOST_RESULT )
AC_SUBST(CARBON)
AC_SUBST(OPTIMIZATION_FLAG, $OPTIMIZATION_FLAG)
AC_SUBST(LD_SHARED, $LD_SHARED)
AC_SUBST(LDFLAGS, $LDFLAGS)
AC_SUBST(LDFLAGS_GL, $LDFLAGS_GL)
AC_SUBST(LDFLAGS_VERSIONING, LDFLAGS_VERSIONING)
AC_SUBST(LDFLAGS_EXE, $LDFLAGS_EXE)
AC_SUBST(LDFLAGS_APP, $LDFLAGS_APP)
AC_SUBST(OSSIM_CFLAGS)
AC_SUBST(OSSIM_CPP_FLAGS)
AC_SUBST(OSSIM_LIBS)
AC_SUBST(OSSIM_INCLUDES)
AC_SUBST(OSSIM_PREFIX)
AC_SUBST(INCLUDE_COMMON)

dnl ---
dnl Required output macro.
dnl ---
AC_OUTPUT(
ossim.spec
Makefile.common 
Makefile:makefiles/${SPECIALIZED_MAKEFILE_DIR}/makeroot
makelib.mak:makefiles/${SPECIALIZED_MAKEFILE_DIR}/makelib
makeprog.mak:makefiles/${SPECIALIZED_MAKEFILE_DIR}/makeprog
src/apps/Makefile:makefiles/unx/makeapps.unx
src/Makefile:makefiles/unx/makesrc.unx
src/ossim/Makefile:makefiles/${SPECIALIZED_MAKEFILE_DIR}/makelibcore
src/ossim/base/Makefile:makefiles/unx/makelibbase.unx
src/ossim/elevation/Makefile:makefiles/unx/makelibelevation.unx
src/ossim/font/Makefile:makefiles/unx/makelibfont.unx
src/ossim/imaging/Makefile:makefiles/unx/makelibimaging.unx
src/ossim/init/Makefile:makefiles/unx/makelibinit.unx
src/ossim/kbool/Makefile:makefiles/unx/makelibkbool.unx
src/ossim/matrix/Makefile:makefiles/unx/makelibmatrix.unx
src/ossim/parallel/Makefile:makefiles/unx/makelibparallel.unx
src/ossim/plugin/Makefile:makefiles/unx/makelibplugin.unx
src/ossim/projection/Makefile:makefiles/unx/makelibprojection.unx
src/ossim/support_data/Makefile:makefiles/unx/makelibsupportdata.unx
src/ossim/vec/Makefile:makefiles/unx/makelibvec.unx
src/ossim/vpfutil/Makefile:makefiles/unx/makelibvpfutil.unx
)

echo "  OSSIM configured settings:"
echo "  host:                           ${host}"
echo "  OSSIM_TOP:                      ${OSSIM_TOP}"
echo "  top_builddir:                   ${top_builddir}"
echo "  OSSIM_MAJOR_VERSION_NUMBER:     ${OSSIM_MAJOR_VERSION_NUMBER}"
echo "  OSSIM_MINOR_VERSION_NUMBER:     ${OSSIM_MINOR_VERSION_NUMBER}"
echo "  OSSIM_RELEASE_NUMBER:           ${OSSIM_RELEASE_NUMBER}"
echo "  OSSIM_VERSION:                  ${OSSIM_VERSION}"
echo "  BUILD_SHARED_OBJS:              ${BUILD_SHARED_OBJS}"
echo "  BUILD_STATIC_OBJS:              ${BUILD_STATIC_OBJS}"
echo "  BUILD_SHARED_LIBS:              ${BUILD_SHARED_LIBS}"
echo "  BUILD_STATIC_LIBS:              ${BUILD_STATIC_LIBS}"
echo "  BUILD_SINGLE_SHARED_LIBS:       ${BUILD_SINGLE_SHARED_LIBS}"
echo "  BUILD_SINGLE_STATIC_LIBS:       ${BUILD_SINGLE_STATIC_LIBS}"
echo "  BUILD_STATIC_APPS:              ${BUILD_STATIC_APPS}"
echo "  SHARED_OBJ_DIR:                 ${SHARED_OBJ_DIR}"
echo "  STATIC_OBJ_DIR:                 ${STATIC_OBJ_DIR}"
echo "  SO_VERSIONLESS_EXT:             ${SO_VERSIONLESS_EXT}"
echo "  SO_SONAME_EXT:                  ${SO_SONAME_EXT}"
echo "  SO_REALNAME_EXT:                ${SO_REALNAME_EXT}"
echo "  SHARED_APP_FLAG:                ${SHARED_APP_FLAG}"
echo "  PIC_FLAG:                       ${PIC_FLAG}"
echo "  RESCOMP:                        ${RESCOMP}"
echo "  RESFLAGS:                       ${RESFLAGS}"
echo "  MACOSX_BUNDLE:                  ${MACOSX_BUNDLE}"
echo "  TOOLKIT_DIR:                    ${TOOLKIT_DIR}"
echo "  LIBOSSIMMACRES:                 ${LIBOSSIMMACRES}"
echo "  LIBOSSIMMACRESCOMP:             ${LIBOSSIMMACRESCOMP}"
echo "  OSSIM_RESOURCES_MACOSX_DATA:    ${OSSIM_RESOURCES_MACOSX_DATA}"
echo "  OSSIM_RESOURCES_MACOSX_TEXT:    ${OSSIM_RESOURCES_MACOSX_TEXT}"
echo "  CFLAGS:                         ${CFLAGS}"
echo "  CXXFLAGS:                       ${CXXFLAGS}"
echo "  CDEBUGFLAGS:                    ${CDEBUGFLAGS}"
echo "  BASE_DEFINES:                   ${BASE_DEFINES}"
echo "  AR_FLAGS:                       ${AR_FLAGS}"
echo "  HOST_RESULT:                    ${HOST_RESULT}"
echo "  CARBON:                         ${CARBON}"
echo "  OPTIMIZATION_FLAG:              ${OPTIMIZATION_FLAG}"
echo "  LD_SHARED:                      ${LD_SHARED}"
echo "  LDFLAGS:                        ${LDFLAGS}"
echo "  LDFLAGS_GL:                     ${LDFLAGS_GL}"
echo "  LDFLAGS_VERSIONING:             ${LDFLAGS_VERSIONING}"
echo "  LDFLAGS_EXE:                    ${LDFLAGS_EXE}"
echo "  LDFLAGS_APP:                    ${LDFLAGS_APP}"
echo "  INSTALL:                        ${INSTALL}"
echo "  OSSIM_VERSION:                  ${OSSIM_VERSION}"
echo "  INCLUDE_COMMON:                 ${INCLUDE_COMMON}"
echo "  -------------- INSTALL LOCATIONS ----------------"
echo "  prefix(to change use --prefix):           ${prefix}"
echo "  exec_prefix(to change use --exec_prefix): ${exec_prefix}"
echo "  bindir(to change use --bindir):           ${bindir}"
echo "  includedir(to change use --includedir:    ${includedir}"
echo "  libdir(to change use --libdir):           ${libdir}"
