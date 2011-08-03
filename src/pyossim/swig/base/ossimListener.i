/*-----------------------------------------------------------------------------
 * Filename        : ossimListener.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimListener
 * -----------------------------------------------------------------------------*/

%module pyossim

%{
#include <ossim/base/ossimListener.h>
%}

#ifndef TYPE_DATA
#define TYPE_DATA

/* Wrapping class ossimListener */
%include "ossim/base/ossimConstants.h"
%include "ossim/base/ossimListener.h"

#endif
