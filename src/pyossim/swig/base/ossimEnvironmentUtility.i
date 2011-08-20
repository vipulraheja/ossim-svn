/*-----------------------------------------------------------------------------
 * Filename        : ossimEnvironmentUtility.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimLsrRay
 * -----------------------------------------------------------------------------*/

%module pyossim

%{
#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimFilename.h>
#include <ossim/base/ossimEnvironmentUtility.h>
%}

/* Wrapping class ossimLsrRay */
%include "ossim/base/ossimConstants.h"
%include "ossim/base/ossimEnvironmentUtility.h"
