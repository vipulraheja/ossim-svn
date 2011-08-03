/*-----------------------------------------------------------------------------
 * Filename        : ossimStringProperty.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimStringProperty
 * -----------------------------------------------------------------------------*/

%module pyossim

%{
#include <ossim/base/ossimStringProperty.h>
%}

#ifndef TYPE_DATA
#define TYPE_DATA

/* Wrapping the class ossimStringProperty */
%include "ossim/base/ossimConstants.h"
%include "ossim/base/ossimStringProperty.h"

#endif
