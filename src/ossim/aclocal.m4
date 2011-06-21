dnl ---
dnl $Id: aclocal.m4 16903 2010-03-22 20:13:11Z dburken $
dnl
dnl If you modify this code run "autoconf" in this same directory with no 
dnl arguments to regenerate the configure script to pick up your changes 
dnl in OSSIM.
dnl 
dnl ---


dnl ---
dnl User defined functions start here...
dnl ---

dnl ---
dnl Function to set program prefix.  If set all applications (programs)
dnl will be prefixed with the prefix picked up here.
dnl Like: prefix=ossim_ 
dnl The program igen will be named ossim_igen
dnl ---
AC_DEFUN([OSSIM_CHECK_PROGRAM_PREFIX],
   [AC_ARG_WITH([program_prefix],
      AS_HELP_STRING([--with-program_prefix=prefix],
         [add prefix to applications (default is no prefix)]),
      [app_prefix=$withval], [app_prefix=])

   echo "Program prefix = $app_prefix"
   AC_SUBST(PROGRAM_PREFIX, $app_prefix)
])
dnl End of program prefix function.


dnl JPEG support
AC_DEFUN(OSSIM_CHECK_JPEG,
[
  AC_ARG_WITH(jpeg,[  --with-jpeg[=ARG]         Include JPEG support (ARG=no or full_path_to_jpeg)],,)

  JPEG_TOP=
  JPEG_INCLUDE_PATH=
  JPEG_LIB_PATH=
  JPEG_LIBS=

  if test "$with_jpeg" = "no" ; then
    dnl Required support.
    echo "ERROR: no is not an option as jpeg is required!"
    AC_MSG_ERROR([jpeg support required!])
  elif test "$with_jpeg" = "" ; then
    dnl No args, look in standard intall locations as default.
    if test -f "$OSSIM_TOP/../jpeg/jpeglib.h" ; then
        JPEG_TOP="$OSSIM_TOP/../jpeg"
    elif test -f "$OSSIM_TOP/../jpeg-8a/jpeglib.h" ; then
      JPEG_TOP="$OSSIM_TOP/../jpeg-8a"
    elif test -f "$OSSIM_TOP/../jpeg-6b/jpeglib.h" ; then
      JPEG_TOP="$OSSIM_TOP/../jpeg-6b"
    elif test -f "/usr/include/jpeglib.h" ; then
      JPEG_TOP="/usr"
    elif test -f "/usr/local/include/jpeglib.h" ; then
      JPEG_TOP="/usr/local"
    elif test -f "/opt/local/include/jpeglib.h" ; then
      JPEG_TOP="/opt/local"
    elif test -f "/sw/include/jpeglib.h" ; then
      JPEG_TOP="/sw"
    else
      dnl Required support.
      echo "ERROR: JPEG_TOP not found!"
      AC_MSG_ERROR([jpeg support required!])
    fi
  else
    dnl User passed in path to jpeg top.
    JPEG_TOP=$with_jpeg
  fi
	
  echo "JPEG_TOP:  $JPEG_TOP"

  if test -d "$JPEG_TOP" ; then
    dnl Set the include path.
    if test -f "$JPEG_TOP/include/jpeglib.h" ; then
      JPEG_INCLUDE_PATH="-I$JPEG_TOP/include"
    elif test -f "$JPEG_TOP/jpeglib.h" ; then
      JPEG_INCLUDE_PATH="-I$JPEG_TOP"
    else
      dnl Required support.
      echo "ERROR: jpeglib.h not found!"
      AC_MSG_ERROR([jpeg support required!])
    fi

    dnl Standard location.
    if test "$JPEG_INCLUDE_PATH" = "-I/usr/include" ; then
      JPEG_INCLUDE_PATH=""
    fi

    dnl Set the lib path
    if test -f "$JPEG_TOP/lib/libjpeg.a" ; then
	JPEG_LIB_PATH="-L$JPEG_TOP/lib"
    elif test -f "$JPEG_TOP/lib/libjpeg.dll.a" ; then
	JPEG_LIB_PATH="-L$JPEG_TOP/lib"
    elif test -f "$JPEG_TOP/lib/libjpeg.lib" ; then
	JPEG_LIB_PATH="-L$JPEG_TOP/lib"
    elif test -f "$JPEG_TOP/lib64/libjpeg.a" ; then
	JPEG_LIB_PATH="-L$JPEG_TOP/lib64" 
    elif test -f "$JPEG_TOP/lib/libjpeg.so" ; then
	JPEG_LIB_PATH="-L$JPEG_TOP/lib"
    elif test -f "$JPEG_TOP/.libs/libjpeg.so" ; then
	JPEG_LIB_PATH="-L$JPEG_TOP/lib"
    elif test -f "$JPEG_TOP/libjpeg.a" ; then
	JPEG_LIB_PATH="-L$JPEG_TOP"
    elif test -f "$JPEG_TOP/libjpeg.lib" ; then
	JPEG_LIB_PATH="-L$JPEG_TOP"
    elif test -f "$JPEG_TOP/libjpeg.so" ; then
	JPEG_LIB_PATH="-L$JPEG_TOP"
    elif test -f "$JPEG_TOP/lib64/libjpeg.so" ; then
	JPEG_LIB_PATH="-L$JPEG_TOP/lib64" 
    else
      dnl Required support.
      echo "ERROR: libjpeg not found!"
      AC_MSG_ERROR([jpeg support required!])
    fi
    JPEG_LIBS=-ljpeg

    dnl ---
    dnl Standard location. Do not add to link line in case someone has an
    dnl LD_LIBRARY_PATH set to avoid picking up the wrong library at run
    dnl time.
    dnl ---
    if test "$JPEG_LIB_PATH" = "-L/usr/lib" ; then
      JPEG_LIB_PATH=""
    elif test "$JPEG_LIB_PATH" = "-L/usr/lib64" ; then
      JPEG_LIB_PATH=""
    fi

    echo "JPEG_INCLUDE_PATH	= $JPEG_INCLUDE_PATH"
    echo "JPEG_LIB_PATH	        = $JPEG_LIB_PATH"
    echo "JPEG_LIBS	        = $JPEG_LIBS"
  else
    echo "JPEG_TOP not determined!"
    AC_MSG_ERROR([jpeg support required!])
  fi

  AC_SUBST(JPEG_INCLUDE_PATH, $JPEG_INCLUDE_PATH)
  AC_SUBST(JPEG_LIB_PATH,     $JPEG_LIB_PATH)
  AC_SUBST(JPEG_LIBS,         $JPEG_LIBS)
])
dnl End of JPEG support...

###
# Usage for AC_ARG_WITH:
# AC_ARG_WITH (package, help-string, [action-if-given], [action-if-not-given])
###

dnl Check for mpi package.
AC_DEFUN(OSSIM_CHECK_MPI,
[
  AC_ARG_WITH(mpi,[  --with-mpi=[ARG]          Include mpi support (ARG=yes or no or directory to install location)],,)

  AC_ARG_WITH(mpi-inc,[--with-mpi-inc=[DIR]  MPI include path (ARG=/path/to/mpi/includes in non standard location)],[mpi_include_path="$withval"],[mpi_include_path=""])


  AC_ARG_WITH(mpi-lib,[--with-mpi-lib[=DIR] MPI lib path (ARG=/path/to/mpi/libs in none standard location)],[mpi_lib_path="$withval"],[mpi_lib_path=""])

  AC_ARG_WITH(openmpi-flag,[--with-openmpi-flag[=ARG] OpenMPi flag(ARG=1 if openmpi, 0 if not)],[openmpi_flag="$withval"],[openmpi_flag=""])

  MPI_TOP= 
  MPI_INCLUDE_PATH=
  MPI_INCLUDES= 
  MPI_LIBS= 
  MPI_LIB_PATH=
  MPI_ENABLED="0"
  OPENMPI_FOUND="0"

  # Check for include path.
  if test -n "$mpi_include_path" ; then
    MPI_INCLUDE_PATH="$mpi_include_path"
  fi

  # Check for lib path.
  if test -n "$mpi_lib_path" ; then
    MPI_LIB_PATH="-L$mpi_lib_path"
  fi

  # Check for openmpi flag
  if test -n "$openmpi_flag" ; then
    OPENMPI_FOUND="$openmpi_flag"
  fi

  # New section for include and path in non standard place.
  if test -n "$MPI_INCLUDE_PATH" && test -n "$MPI_LIB_PATH" ; then
    MPI_ENABLED="1"
    if test "$OPENMPI_FOUND" = "1" ; then
      MPI_INCLUDES="-I$MPI_INCLUDE_PATH"
      MPI_LIBS="-lmpi_cxx -lmpi"
    else
      MPI_INCLUDES="-I$MPI_INCLUDE_PATH"
      MPI_LIBS=-llammpi++ -lmpi -llam -llammpio
    fi
  else
    if test "$with_mpi" = "yes" -o "$with_mpi" = ""; then
      if test -f "/usr/bin/lamboot" ; then
	MPI_TOP=/usr
      elif test -f "/usr/local/bin/lamboot" ; then
        MPI_TOP=/usr/local
      elif test -f "/usr/local/ossim/bin/lamboot" ; then
        MPI_TOP=/usr/local/ossim
      elif test -f "/opt/local/bin/lamboot" ; then
        MPI_TOP=/opt/local
      elif test -f "/sw/local/bin/lamboot" ; then
        MPI_TOP=/sw/local
      elif test -f "/usr/local/bin/mpirun" ; then
        MPI_TOP=/usr/local
        OPENMPI_FOUND="1"
    fi
    elif test "$with_mpi" != "no" ; then
      if test -f "$with_mpi/bin/lamboot" ; then
        MPI_TOP="$with_mpi"
      fi
    fi

    if test "$OPENMPI_FOUND" = "1" ; then
      MPI_LIBS="-lmpi_cxx -lmpi"
      MPI_ENABLED="1"
    elif test "$MPI_TOP" = "/usr" ; then
      MPI_INCLUDES=
      MPI_LIB_PATH=
      if test -f "/usr/include/lam/mpi.h" ; then
        if test -f "/usr/include/lam/32/lam_config.h" ; then
          MPI_INCLUDES="-I/usr/include/lam -I/usr/include/lam/32"
        else
          MPI_INCLUDES="-I/usr/include/lam"
        fi
      fi
      if test -e "/usr/lib/lam/libmpi.so" ; then
        MPI_LIB_PATH="-L/usr/lib/lam"
      fi
      MPI_LIBS="-llammpi++ -lmpi -llam -llammpio"
      MPI_ENABLED="1"
    elif test "$MPI_TOP" != "" ; then
      dnl library path for linking
      MPI_LIB_PATH="-L$MPI_TOP/lib"
      dnl libraries to link with
      MPI_LIBS="-llammpi++ -lmpi -llam -llammpio"
      dnl enable for starters.
      MPI_ENABLED="1"
      dnl Find includes.  These seem to vary by different packagers.
      if test -f "$MPI_TOP/include/mpi.h" ; then
	MPI_INCLUDES="-I$MPI_TOP/include"
      elif test -f "$MPI_TOP/include/lammpi/mpi.h" ; then
	MPI_INCLUDES="-I$MPI_TOP/include/lammpi"
      else
        dnl No mpi.h found
        echo "MPI include mpi.h not found, disabled..."
        MPI_ENABLED="0"
      fi
    fi
  fi

  if test "$MPI_ENABLED" = "1" ; then
    dnl ---
    dnl Standard location. Do not add to link line in case someone has an
    dnl LD_LIBRARY_PATH set to avoid picking up the wrong library at run
    dnl time.
    dnl ---
    if test "$MPI_LIB_PATH" = "-L/usr/lib" ; then
      MPI_LIB_PATH=""
    elif test "$MPI_LIB_PATH" = "-L/usr/lib64" ; then
      MPI_LIB_PATH=""
    fi
  fi

dnl If an mpi directory was not specified try looking parallel to 
dnl the ossim (this) package.
  echo "OPENMPI_FOUND           = $OPENMPI_FOUND"
  echo "MPI_INCLUDE_PATH        = $MPI_INCLUDE_PATH"
  echo "MPI_INCLUDES		= $MPI_INCLUDES"
  echo "MPI_LIB_PATH		= $MPI_LIB_PATH"
  echo "MPI_LIBS		= $MPI_LIBS"
  echo "MPI_ENABLED		= $MPI_ENABLED"

  AC_SUBST(MPI_INCLUDES,   $MPI_INCLUDES)
  AC_SUBST(MPI_LIB_PATH,   $MPI_LIB_PATH)
  AC_SUBST(MPI_LIBS,       $MPI_LIBS)
  
  if test "$MPI_ENABLED" = "1" ; then
    AC_DEFINE(OSSIM_HAS_MPI, 1)
  fi

])
dnl End of MPI package...

dnl Check for OpenThreads package.
AC_DEFUN(OSSIM_CHECK_OPEN_THREADS,
[
  AC_ARG_WITH(openthreads,       [  --with-openthreads[=ARG]  Open threads support , ARG=yes or no or directory to install location],,)

  OPEN_THREADS_TOP=
  OPEN_THREADS_INCLUDES=
  OPEN_THREADS_LIBS= 
  OPEN_THREADS_LIB_PATH=
  OPEN_THREADS_ENABLED="0"
  OPEN_THREADS_FRAMEWORK="no"
  if test "$with_openthreads" = "no" ; then
    dnl Required support.
    echo "ERROR: no is not an option as openthreads is required!"
    AC_MSG_ERROR([openthreads support required!])
  elif test "$with_openthreads" = "" ; then
    dnl Look in all the standard places.
    if test -d "/Library/Frameworks/OpenThreads.framework" ; then
	OPEN_THREADS_TOP="/Library/Frameworks/"
	OPEN_THREADS_FRAMEWORK="yes"
    elif test -d "$HOME/Library/Frameworks/OpenThreads.framework" ; then
	OPEN_THREADS_TOP="$HOME/Library/Frameworks/"
	OPEN_THREADS_FRAMEWORK="yes"
    elif test -f "/usr/local/include/OpenThreads/Mutex" ; then
	OPEN_THREADS_TOP="/usr/local"
    elif test -f "/opt/local/include/OpenThreads/Mutex" ; then
	OPEN_THREADS_TOP="/opt/local"
    elif test -f "/sw/local/include/OpenThreads/Mutex" ; then
	OPEN_THREADS_TOP="/sw/local"
    elif test -f "/usr/include/OpenThreads/Mutex" ; then
	OPEN_THREADS_TOP="/usr"
    elif test -f "$OSSIM_TOP/../OpenThreads/include/OpenThreads/Mutex" ; then
        OPEN_THREADS_TOP="$OSSIM_TOP/../OpenThreads"
    fi
  else
    dnl User passed in OpenThreads top.
    if test -d "$with_openthreads/OpenThreads.framework" ; then
	OPEN_THREADS_TOP="$with_openthreads"
	OPEN_THREADS_FRAMEWORK="yes"
    else
    	OPEN_THREADS_TOP=$with_openthreads
	OPEN_THREADS_INCLUDES=-I$with_openthreads    
    fi	
  fi
   
  if test "$OPEN_THREADS_FRAMEWORK" = "yes" ; then
	OPEN_THREADS_INCLUDES="-F$OPEN_THREADS_TOP"
	OPEN_THREADS_ENABLED="1"
	OPEN_THREADS_LIBS="-F$OPEN_THREADS_TOP -framework OpenThreads"
  elif test -d "$OPEN_THREADS_TOP" ; then
    OPEN_THREADS_INCLUDES="-I$OPEN_THREADS_TOP/include"
    OPEN_THREADS_LIBS="-lOpenThreads"

    dnl Set the lib path.
    if test -f "$OPEN_THREADS_TOP/lib/Linux32/libOpenThreads.so" ; then
      OPEN_THREADS_LIB_PATH="-L$OPEN_THREADS_TOP/lib/Linux32"
    elif test -f "$OPEN_THREADS_TOP/lib64/libOpenThreads.so" ; then
      OPEN_THREADS_LIB_PATH="-L$OPEN_THREADS_TOP/lib64"
    elif test -f "$OPEN_THREADS_TOP/lib/libOpenThreads.so" ; then
      OPEN_THREADS_LIB_PATH="-L$OPEN_THREADS_TOP/lib"
    elif test -f "$OPEN_THREADS_TOP/lib/libOpenThreads.a" ; then
      OPEN_THREADS_LIB_PATH="-L$OPEN_THREADS_TOP/lib"
    elif test -f "$OPEN_THREADS_TOP/lib/OpenThreads.lib" ; then
      OPEN_THREADS_LIB_PATH="-L$OPEN_THREADS_TOP/lib"
    elif test -f "$OPEN_THREADS_TOP/lib/libOpenThreads.dll.a" ; then
      OPEN_THREADS_LIB_PATH="-L$OPEN_THREADS_TOP/lib"
    else
      dnl Required support.
      echo "ERROR: libOpenThreads not found!"
      AC_MSG_ERROR([OpenThreads support required!])
    fi

    dnl ---
    dnl Standard location. Do not add to link line in case someone has an
    dnl LD_LIBRARY_PATH set to avoid picking up the wrong library at run
    dnl time.
    dnl ---
    if test "$OPEN_THREADS_LIB_PATH" = "-L/usr/lib" ; then
      OPEN_THREADS_LIB_PATH=""
    elif test "$OPEN_THREADS_LIB_PATH" = "-L/usr/lib64" ; then
      OPEN_THREADS_LIB_PATH=""
    fi

    OPEN_THREADS_ENABLED="1"
  else
    echo "OPEN_THREADS_TOP not determined!"
    AC_MSG_ERROR([OpenThreads support required!])
  fi

  echo "OPEN_THREADS_INCLUDES   = $OPEN_THREADS_INCLUDES"
  echo "OPEN_THREADS_LIBS       = $OPEN_THREADS_LIBS"
  echo "OPEN_THREADS_LIB_PATH   = $OPEN_THREADS_LIB_PATH"
  echo "OPEN_THREADS_ENABLED    = $OPEN_THREADS_ENABLED"

  AC_SUBST(OPEN_THREADS_INCLUDES,   $OPEN_THREADS_INCLUDES)
  AC_SUBST(OPEN_THREADS_LIBS,       $OPEN_THREADS_LIBS)
  AC_SUBST(OPEN_THREADS_LIB_PATH,   $OPEN_THREADS_LIB_PATH)

  if test "$OPEN_THREADS_ENABLED" = "1" ; then
    AC_DEFINE(OSSIM_HAS_OPEN_THREADS, 1)
  fi

])
dnl End of OpenThread package...


dnl Check for freetype package.
AC_DEFUN(OSSIM_CHECK_FREETYPE,
[
  AC_ARG_WITH(freetype,[  --with-freetype[=ARG]     Include freetype support (ARG=no or full_path_to_free)],,)

  FREETYPE_TOP=""
  FREETYPE_INCLUDES= 
  FREETYPE_LIBS= 
  FREETYPE_LIB_PATH=
  FREETYPE_ENABLED="0"

  if test "$with_freetype" = "" ; then
    if test -f "/usr/bin/freetype-config" ; then
	FREETYPE_CONFIG_FOUND=1
	FREETYPE_INCLUDES=`freetype-config --cflags`
	FREETYPE_LIBS=`freetype-config --libs`
	FREETYPE_LIB_PATH=-L`freetype-config --prefix`/lib
        FREETYPE_ENABLED="1"
    elif test -d "/usr/include/freetype2" ; then
        FREETYPE_TOP="/usr"
    elif test -d "/usr/local/include/freetype2" ; then
        FREETYPE_TOP="/usr/local"
    elif test -d "/usr/X11R6/include/freetype2" ; then
        FREETYPE_TOP="/usr/X11R6"
    fi
  else 
    FREETYPE_TOP=$with_freetype
  fi

  if test "$FREETYPE_TOP" != "" ; then
    if test -d "$FREETYPE_TOP/include/freetype2" ; then
      FREETYPE_INCLUDES="-I$FREETYPE_TOP/include -I$FREETYPE_TOP/include/freetype2 -I$FREETYPE_TOP/include/freetype2/freetype"
      FREETYPE_LIB_PATH="-L$FREETYPE_TOP/lib"
      FREETYPE_LIBS="-lfreetype"
      FREETYPE_ENABLED="1"
    fi
  fi

  dnl ---
  dnl Standard location. Do not add to link line in case someone has an
  dnl LD_LIBRARY_PATH set to avoid picking up the wrong library at run
  dnl time.
  dnl ---
  if test "$FREETYPE_LIB_PATH" = "-L/usr/lib" ; then
    FREETYPE_LIB_PATH=""
  elif test "$FREETYPE_LIB_PATH" = "-L/usr/lib64" ; then
    FREETYPE_LIB_PATH=""
  fi

  echo "FREETYPE_INCLUDES	= $FREETYPE_INCLUDES"
  echo "FREETYPE_LIB_PATH	= $FREETYPE_LIB_PATH"
  echo "FREETYPE_LIBS		= $FREETYPE_LIBS"
  echo "FREETYPE_ENABLED 	= $FREETYPE_ENABLED"

  AC_SUBST(FREETYPE_INCLUDES,   $FREETYPE_INCLUDES)
  AC_SUBST(FREETYPE_LIB_PATH,   $FREETYPE_LIB_PATH)
  AC_SUBST(FREETYPE_LIBS,       $FREETYPE_LIBS)

  if test "$FREETYPE_ENABLED" = "1" ; then
    AC_DEFINE(OSSIM_HAS_FREETYPE, 1)
  fi

])

dnl Check for geotif package.
AC_DEFUN(OSSIM_CHECK_GEOTIFF,
[
  AC_ARG_WITH(geotiff,[  --with-geotiff[=ARG]      Include geotiff support (ARG=no or full_path_to_geotiff)],,)

  GEOTIFF_TOP=
  GEOTIFF_INCLUDE_PATH=
  GEOTIFF_LIB_PATH=
  GEOTIFF_LIBS=
  GEOTIFF_ENABLED="0"

  if test "$with_geotiff" = "no" ; then
    dnl User does not want to use geotiff so do nothing...
    echo "Geotiff support option = no"
  elif test "$with_geotiff" = "" ; then
    dnl No args, look in standard intall location as default.
    dnl Look in parallel directory.
    if test -d "$OSSIM_TOP/../geotiff" ; then
      if test -f "$OSSIM_TOP/../geotiff/include/geotiff.h" ; then
        dnl User did a make install to top.
        GEOTIFF_TOP="$OSSIM_TOP/../geotiff"
      else
        GEOTIFF_TOP="$OSSIM_TOP/../geotiff/libgeotiff"
      fi
    elif test -f "/usr/local/include/geotiff.h" ; then
	GEOTIFF_TOP="/usr/local"
    elif test -f "/usr/include/geotiff.h" ; then
	GEOTIFF_TOP="/usr"
    elif test -f "/usr/include/libgeotiff/geotiff.h" ; then
	GEOTIFF_TOP="/usr"
    elif test -f "/usr/include/geotiff/geotiff.h" ; then
	GEOTIFF_TOP="/usr"
    elif test -f "/opt/local/include/geotiff.h" ; then
	GEOTIFF_TOP="/opt/local"
    fi
  else
    dnl User passed in geotiff top.
    GEOTIFF_TOP=$with_geotiff
  fi
  
  if test -d $GEOTIFF_TOP && test "$GEOTIFF_TOP" != ""; then
    dnl Set the include path.
    if test -f "$GEOTIFF_TOP/include/geotiff.h" ; then
      GEOTIFF_INCLUDE_PATH="-I$GEOTIFF_TOP/include"
    elif test -f "$GEOTIFF_TOP/include/libgeotiff/geotiff.h" ; then
      GEOTIFF_INCLUDE_PATH="-I$GEOTIFF_TOP/include/libgeotiff"
    elif test -f "$GEOTIFF_TOP/include/geotiff/geotiff.h" ; then
      GEOTIFF_INCLUDE_PATH="-I$GEOTIFF_TOP/include/geotiff"
    else
      GEOTIFF_INCLUDE_PATH="-I$GEOTIFF_TOP"
    fi
    dnl Set the lib path.
    if test -d "$GEOTIFF_TOP/lib" ; then
      GEOTIFF_LIB_PATH="-L$GEOTIFF_TOP/lib"
    elif test -d "$GEOTIFF_TOP/lib64" ; then
	GEOTIFF_LIB_PATH="-L$GEOTIFF_TOP/lib64"
    else
      GEOTIFF_LIB_PATH="-L$GEOTIFF_TOP"
    fi

    dnl ---
    dnl Standard location. Do not add to link line in case someone has an
    dnl LD_LIBRARY_PATH set to avoid picking up the wrong library at run
    dnl time.
    dnl ---
    if test "$GEOTIFF_LIB_PATH" = "-L/usr/lib" ; then
      GEOTIFF_LIB_PATH=""
    elif test "$GEOTIFF_LIB_PATH" = "-L/usr/lib64" ; then
      GEOTIFF_LIB_PATH=""
    fi

    GEOTIFF_LIBS=-lgeotiff
    GEOTIFF_ENABLED="1"
  else
    dnl Required support.
    echo "ERROR: GEOTIFF_TOP not found!"
    AC_MSG_ERROR([geotiff support required!])
  fi

  echo "GEOTIFF_INCLUDE_PATH	= $GEOTIFF_INCLUDE_PATH"
  echo "GEOTIFF_LIB_PATH	= $GEOTIFF_LIB_PATH"
  echo "GEOTIFF_LIBS	        = $GEOTIFF_LIBS"
  echo "GEOTIFF_ENABLED         = $GEOTIFF_ENABLED"

  AC_SUBST(GEOTIFF_INCLUDE_PATH, $GEOTIFF_INCLUDE_PATH)
  AC_SUBST(GEOTIFF_LIB_PATH,     $GEOTIFF_LIB_PATH)
  AC_SUBST(GEOTIFF_LIBS,         $GEOTIFF_LIBS)

  if test "$GEOTIFF_ENABLED" = "1" ; then
    AC_DEFINE(OSSIM_HAS_GEOTIFF, 1)
  fi

])
dnl End of Geotiff package...


dnl Check for libtiff package.
AC_DEFUN(OSSIM_CHECK_LIBTIFF,
[
  AC_ARG_WITH(libtiff,[  --with-libtiff[=ARG]      Include libtiff support (ARG=no or full_path_to_libtiff)],,)

  LIBTIFF_TOP=
  LIBTIFF_INCLUDE_PATH=
  LIBTIFF_LIB_PATH=
  LIBTIFF_LIBS=

  if test "$with_libtiff" = "no" ; then
    dnl User does not want to use libtiff so do nothing...
    AC_MSG_ERROR([libtiff support required!])
  elif test "$with_libtiff" = "" ; then
    dnl No args, look in standard intall location as default.
    if test -d "$OSSIM_TOP/../libtiff" ; then
        LIBTIFF_TOP="$OSSIM_TOP/../libtiff"
    elif test -f "/usr/local/include/tiff.h" ; then
	LIBTIFF_TOP="/usr/local"
    elif test -f "/usr/include/tiff.h" ; then
	LIBTIFF_TOP="/usr"
    elif test -f "/opt/local/include/tiff.h" ; then
	LIBTIFF_TOP="/opt/local"
    else
      echo "Libtiff support disabled."
    fi
  else
    dnl User passed in libtiff top.
    LIBTIFF_TOP=$with_libtiff
  fi
  
  if test -d "$LIBTIFF_TOP" ; then
    dnl Set the include path.
    if test -f "$LIBTIFF_TOP/include/tiff.h" ; then
	LIBTIFF_INCLUDE_PATH="-I$LIBTIFF_TOP/include"
    elif test -f "$LIBTIFF_TOP/libtiff/tiff.h" ; then
	LIBTIFF_INCLUDE_PATH="-I$LIBTIFF_TOP/libtiff"
    else
	LIBTIFF_INCLUDE_PATH="-I$LIBTIFF_TOP"
    fi
    dnl Set the lib path
    if test -f "$LIBTIFF_TOP/lib/libtiff.a" ; then
	LIBTIFF_LIB_PATH="-L$LIBTIFF_TOP/lib"
    elif test -f "$LIBTIFF_TOP/lib/libtiff.so" ; then
	LIBTIFF_LIB_PATH="-L$LIBTIFF_TOP/lib"
    elif test -f "$LIBTIFF_TOP/lib64/libtiff.a" ; then
	LIBTIFF_LIB_PATH="-L$LIBTIFF_TOP/lib64"
    elif test -f "$LIBTIFF_TOP/lib64/libtiff.so" ; then
	LIBTIFF_LIB_PATH="-L$LIBTIFF_TOP/lib64"
    elif test -f "$LIBTIFF_TOP/libtiff/libtiff.a" ; then
	LIBTIFF_LIB_PATH="-L$LIBTIFF_TOP/libtiff"
    elif test -f "$LIBTIFF_TOP/libtiff/libtiff.so" ; then
	LIBTIFF_LIB_PATH="-L$LIBTIFF_TOP/libtiff"
    elif test -f "$LIBTIFF_TOP/libtiff/.libs/libtiff.a" ; then
	LIBTIFF_LIB_PATH="-L$LIBTIFF_TOP/libtiff/.libs"
    elif test -f "$LIBTIFF_TOP/libtiff/.libs/libtiff.so" ; then
	LIBTIFF_LIB_PATH="-L$LIBTIFF_TOP/libtiff/.libs"
    elif test -f "$LIBTIFF_TOP/.libs/libtiff.a" ; then
	LIBTIFF_LIB_PATH="-L$LIBTIFF_TOP/.libs"
    elif test -f "$LIBTIFF_TOP/.libs/libtiff.so" ; then
	LIBTIFF_LIB_PATH="-L$LIBTIFF_TOP/.libs"
    else
	LIBTIFF_LIB_PATH=-L$LIBTIFF_TOP
    fi

    dnl ---
    dnl Standard location. Do not add to link line in case someone has an
    dnl LD_LIBRARY_PATH set to avoid picking up the wrong library at run
    dnl time.
    dnl ---
    if test "$LIBTIFF_LIB_PATH" = "-L/usr/lib" ; then
      LIBTIFF_LIB_PATH=""
    elif test "$LIBTIFF_LIB_PATH" = "-L/usr/lib64" ; then
      LIBTIFF_LIB_PATH=""
    fi

    LIBTIFF_LIBS=-ltiff
    echo "LIBTIFF_INCLUDE_PATH	= $LIBTIFF_INCLUDE_PATH"
    echo "LIBTIFF_LIB_PATH	= $LIBTIFF_LIB_PATH"
    echo "LIBTIFF_LIBS	        = $LIBTIFF_LIBS"
  else
    AC_MSG_ERROR([libtiff support required!])
  fi

  AC_SUBST(LIBTIFF_INCLUDE_PATH, $LIBTIFF_INCLUDE_PATH)
  AC_SUBST(LIBTIFF_LIB_PATH,     $LIBTIFF_LIB_PATH)
  AC_SUBST(LIBTIFF_LIBS,         $LIBTIFF_LIBS)

])
dnl End of Libtiff package...



dnl this macro checks for a command line argument and caches the result
dnl usage: OSSIM_ARG_WITH(option, helpmessage, variable-name)
AC_DEFUN([OSSIM_ARG_WITH],
        [
          AC_MSG_CHECKING([for --with-$1])
          no_cache=0
          AC_ARG_WITH($1, [$2],
                      [
                        if test "$withval" = yes; then
                          ac_cv_use_$1='$3=yes'
                        elif test "$withval" = "" ; then
                          ac_cv_use_$1='$3=no'
			else
                          ac_cv_use_$1='$3=$withval'
                        fi
                      ],
                      [
				ac_cv_use_$1='$3=no'
dnl                        LINE=`grep "$3" ${wx_arg_cache_file}`
dnl                        if test "x$LINE" != x ; then
dnl                          eval "DEFAULT_$LINE"
dnl                        else
dnl                          no_cache=1
dnl                        fi

dnl                        ac_cv_use_$1='$3='$DEFAULT_$3
                      ])

          eval "$ac_cv_use_$1"
dnl          if test "$no_cache" != 1; then
dnl            echo $ac_cv_use_$1 >> ${wx_arg_cache_file}.tmp
dnl          fi

          if test "$$3" = yes; then
            AC_MSG_RESULT(yes)
          else
            AC_MSG_RESULT(no)
          fi
        ]
)

dnl like OSSIM_ARG_WITH but uses AC_ARG_ENABLE instead of AC_ARG_WITH
dnl usage: OSSIM_ARG_ENABLE(option, helpmessage, variable-name, enablestring)
dnl
dnl enablestring is a hack and allows to show "checking for --disable-foo"
dnl message when running configure instead of the default "checking for
dnl --enable-foo" one whih is useful for the options enabled by default
AC_DEFUN([OSSIM_ARG_ENABLE],   
         [
   	  enablestring=$4
          AC_MSG_CHECKING([for --${enablestring:-enable}-$1])
          no_cache=0
          AC_ARG_ENABLE($1, [$2],
                        [
                          if test "$enableval" = yes; then
                            ac_cv_use_$1='$3=yes'
                           else
                            ac_cv_use_$1='$3=no'
                          fi
                        ],
                        [
                          ac_cv_use_$1='$3=$$3'
dnl                          LINE=`grep "$3" ${wx_arg_cache_file}`
dnl                          if test "x$LINE" != x ; then
dnl                            eval "DEFAULT_$LINE"
dnl                          else
dnl                            no_cache=1
dnl                          fi

dnl                          ac_cv_use_$1='$3='$DEFAULT_$3
                        ])

          eval "$ac_cv_use_$1"
dnl          if test "$no_cache" != 1; then
dnl          echo $ac_cv_use_$1 >> ${wx_arg_cache_file}.tmp
dnl      fi

          if test "$$3" = yes; then
            AC_MSG_RESULT(yes)
          else
            AC_MSG_RESULT(no)
          fi
        ]
)

define(OSSIM_SYS_LARGEFILE_TEST,
[typedef struct {
    unsigned int field: sizeof(off_t) == 8;
} wxlf;
])

OSSIM_SYS_LARGEFILE_MACRO_VALUE(C-MACRO, VALUE, CACHE-VAR)
define(OSSIM_SYS_LARGEFILE_MACRO_VALUE,
[
    AC_CACHE_CHECK([for $1 value needed for large files], [$3],
        [
          AC_TRY_COMPILE([#define $1 $2
                          #include <sys/types.h>],
                         OSSIM_SYS_LARGEFILE_TEST,
                         [$3=$2],
                         [$3=no])
        ]
    )

    if test "$$3" != no; then
        ossim_largefile=yes
        AC_DEFINE_UNQUOTED([$1], [$$3])
    fi
])

dnl AC_SYS_LARGEFILE
dnl ----------------
dnl By default, many hosts won't let programs access large files;
dnl one must use special compiler options to get large-file access to work.
dnl For more details about this brain damage please see:
dnl http://www.sas.com/standards/large.file/x_open.20Mar96.html
AC_DEFUN([AC_SYS_LARGEFILE],
[AC_ARG_ENABLE(largefile,
               [  --disable-largefile     omit support for large files])
if test "$enable_largefile" != no; then
    dnl _FILE_OFFSET_BITS==64 is needed for Linux, Solaris, ...
    dnl _LARGE_FILES -- for AIX
    ossim_largefile=no
    OSSIM_SYS_LARGEFILE_MACRO_VALUE(_FILE_OFFSET_BITS, 64, ac_cv_sys_file_offset_bits)
    if test "x$ossim_largefile" != "xyes"; then
        OSSIM_SYS_LARGEFILE_MACRO_VALUE(_LARGE_FILES, 1, ac_cv_sys_large_files)
    fi

    AC_MSG_CHECKING(if large file support is available)
    if test "x$ossim_largefile" = "xyes"; then
        AC_DEFINE(HAVE_LARGEFILE_SUPPORT)
    fi
    AC_MSG_RESULT($ossim_largefile)
fi
])
