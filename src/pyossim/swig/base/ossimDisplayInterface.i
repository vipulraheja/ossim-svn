/*-----------------------------------------------------------------------------
 * Filename        : ossimDisplayInterface.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimProperty
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimRtti.h>
#include <ossim/base/ossimString.h>
#include <ossim/base/ossimDisplayInterface.h>

%}

#ifndef TYPE_DATA
#define TYPE_DATA

/* Wrapping class ossimDisplayInterface */
%include "ossim/base/ossimConstants.h"
%include "ossim/base/ossimDisplayInterface.h"

#endif
