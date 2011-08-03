/*-----------------------------------------------------------------------------
 * Filename        : ossimMapProjectionFactory.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimMapProjectionFactory
 * -----------------------------------------------------------------------------*/

%module pyossim

%{
#include <ossim/projection/ossimMapProjectionFactory.h>
%}

%include "ossim/base/ossimConstants.h"

/* Wrapping the class ossimMapProjectionFactory */
%include "ossim/projection/ossimMapProjectionFactory.h"
