/*-----------------------------------------------------------------------------
 * Filename        : ossimObjectFactory.i  
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimObjectFactory 
 * -----------------------------------------------------------------------------*/

%module pyossim

%{
#include <ossim/base/ossimObjectFactory.h>
%}

#ifndef TYPE_DATA
#define TYPE_DATA

%include "ossim/base/ossimConstants.h"
%include "ossim/base/ossimObjectFactory.h"

#endif
