/*-----------------------------------------------------------------------------
 * Filename        : ossimElevationDatabaseRegistry.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimElevationDatabaseRegistry
 * -----------------------------------------------------------------------------*/

%module pyossim

%{
#include <ossim/elevation/ossimElevationDatabaseRegistry.h>
%}

%include "ossim/base/ossimConstants.h"

/* Wrapping class ossimElevationDatabaseRegistry */
%include "ossim/elevation/ossimElevationDatabaseRegistry.h"
