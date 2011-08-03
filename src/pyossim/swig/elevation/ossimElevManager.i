/*-----------------------------------------------------------------------------
 * Filename        : ossimElevManager.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimElevManager
 * -----------------------------------------------------------------------------*/

%module pyossim

%{
#include <ossim/elevation/ossimElevManager.h>
%}

%include "ossim/base/ossimConstants.h"

/* Wrapping class ossimElevManager */
%include "ossim/elevation/ossimElevManager.h"
