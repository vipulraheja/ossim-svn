/*-----------------------------------------------------------------------------
 * Filename        : ossimGeoid.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimDtedHandler
 * -----------------------------------------------------------------------------*/

%module pyossim

%{
#include <ossim/base/ossimObject.h>
#include <ossim/base/ossimGeoid.h>
#include <ossim/base/ossimErrorStatusInterface.h>
%}

#ifndef TYPE_DATA
#define TYPE_DATA

%include "ossim/base/ossimConstants.h"

/* Handling class ossimGeoid */
%include "ossim/base/ossimGeoid.h"

#endif
