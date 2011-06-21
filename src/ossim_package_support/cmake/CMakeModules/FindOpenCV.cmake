# Locate OPENCV
# This module defines
# OPENCV_INCLUDE_DIR
# OPENCV_CXCORE_INCLUDE_DIR
# OPENCV_CVAUX_INCLUDE_DIR
# OPENCV_HIGHGUI_INCLUDE_DIR
# OPENCV_FOUND, 
# OPENCV_CXCORE_FOUND 
# OPENCV_CVAUX_FOUND 
# OPENCV_HIGHGUI_FOUND 
# OPENCV_INCLUDE_DIRS 
#
# OPENCV_LIBRARY
# OPENCV_CXCORE_LIBRARY
# OPENCV_CVAUX_LIBRARY
# OPENCV_HIGHGUI_LIBRARY
#
# OPENCV_LIBRARIES
# Created by Garrett Potts.

# Macro to find header and lib directories
# example: OPENCV_FIND(OPENCV cv cv.h)
MACRO(OPENCV_FIND varname shortname headername)
    FIND_PATH(${varname}_INCLUDE_DIR ${headername}
        PATHS
        $ENV{ProgramFiles}
        $ENV{SystemDrive}
        ~/Library/Frameworks
        /Library/Frameworks
        /usr/local/include
        /usr/include
        /sw/include # Fink
        /opt/local/include # DarwinPorts
        /opt/csw/include # Blastwave
        /opt/include
        /usr/freeware/include
        PATH_SUFFIXES 
        opencv
        OpenCV
        opencv/cv
        OpenCV/cv
        opencv/cv/include
        OpenCV/cv/include
        opencv/otherlibs/highgui
        OpenCV/otherlibs/highgui
        DOC "Location of OPENCV Headers"
    )

    FIND_LIBRARY(${varname}_LIBRARY
        NAMES ${shortname} cv210 cvaux210 cxcore210 highgui210.lib
        PATHS
        ~/Library/Frameworks
        /Library/Frameworks
        /usr/local/lib
         /usr/lib/postgresql
        /usr/local/lib64
        /usr/lib
        /usr/lib64
        /sw/lib
        /opt/local/lib
        /opt/csw/lib
        /opt/lib
        /usr/freeware/lib64
        $ENV{ProgramFiles}
        $ENV{SystemDrive} 
        PATH_SUFFIXES 
        OpenCV/lib
        
        DOC "Location of OPENCV Libraries"
    )

    SET(${varname}_FOUND "OFF")
    IF (${varname}_LIBRARY AND ${varname}_INCLUDE_DIR)
        SET(${varname}_FOUND "ON")
    ENDIF()

ENDMACRO(OPENCV_FIND)



OPENCV_FIND(OPENCV cv cv.h)
OPENCV_FIND(OPENCV_CXCORE  cxcore  cxcore.h)
OPENCV_FIND(OPENCV_CVAUX  cvaux  cvaux.h)
# OPENCV_FIND(OPENCV_CVXT  cxts  cxtypes.h)
OPENCV_FIND(OPENCV_HIGHGUI   highgui   highgui.h)
OPENCV_FIND(OPENCV_ML ml ml.h)

SET(OPENCV_ALL_FOUND "OFF")
SET(OPENCV_INCLUDE_DIRS "${OPENCV_INCLUDE_DIR}")
SET(OPENCV_LIBRARIES "${OPENCV_LIBRARY}")

IF(OPENCV_FOUND AND OPENCV_CXCORE_FOUND AND OPENCV_CVAUX_FOUND AND OPENCV_HIGHGUI_FOUND)
   SET(OPENCV_LIBRARIES 
        ${OPENCV_LIBRARY}
        ${OPENCV_CXCORE_LIBRARY}
        ${OPENCV_CVAUX_LIBRARY}
        ${OPENCV_HIGHGUI_LIBRARY}
        ${OPENCV_ML_LIBRARY}
      )
   SET(OPENCV_INCLUDE_DIRS 
        ${OPENCV_INCLUDE_DIR}
        ${OPENCV_CXCORE_INCLUDE_DIR}
        ${OPENCV_CVAUX_INCLUDE_DIR}
        ${OPENCV_HIGHGU_INCLUDE_DIR}
        ${OPENCV_ML_INCLUDE_DIR}
      )
   SET(OPENCV_ALL_FOUND "ON")
ELSE()
ENDIF()


