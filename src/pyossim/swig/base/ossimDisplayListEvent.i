/*-----------------------------------------------------------------------------
 * Filename        : ossimDisplayListEvent.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimProperty
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimEvent.h>
#include <ossim/base/ossimDisplayListEvent.h>
#include <map>

%}

#ifndef TYPE_DATA
#define TYPE_DATA

/* Wrapping class */
%include "ossim/base/ossimConstants.h"
%include "ossim/base/ossimDisplayListEvent.h"

#endif
