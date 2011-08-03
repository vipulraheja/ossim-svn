/*-----------------------------------------------------------------------------
 * Filename        : ossimEvent.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimEvent
 * -----------------------------------------------------------------------------*/

%module pyossim

%{
#include <ossim/base/ossimEvent.h>
%}

#ifndef TYPE_DATA
#define TYPE_DATA

/* Wrapping the class ossimEvent */
%include "ossim/base/ossimConstants.h"
%include "ossim/base/ossimEvent.h"

#endif
