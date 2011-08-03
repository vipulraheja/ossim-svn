/*-----------------------------------------------------------------------------
 * Filename        : ossimConnectableObject.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimConnectableObject
 * -----------------------------------------------------------------------------*/

%module pyossim

%{
#include <ossim/base/ossimConnectableObject.h>
%}

#ifndef TYPE_DATA 
#define TYPE_DATA

/* Wrapping class ossimConnectableObject */
%include "ossim/base/ossimConstants.h"
%include "ossim/base/ossimConnectableObject.h"

#endif
