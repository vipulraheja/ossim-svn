/*-----------------------------------------------------------------------------
 * Filename        : ossimStringListProperty.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimStringListProperty
 * -----------------------------------------------------------------------------*/

%module pyossim

%{
#include <ossim/base/ossimStringListProperty.h>
%}

#ifndef TYPE_DATA
#define TYPE_DATA

/* Wrapping the class ossimStringListProperty */
%include "ossim/base/ossimConstants.h"
%include "ossim/base/ossimStringListProperty.h"

#endif
