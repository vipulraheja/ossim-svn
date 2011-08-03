/*-----------------------------------------------------------------------------
 * Filename        : ossimElevCellHandlerFactory.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimElevCellHandlerFactory
 * -----------------------------------------------------------------------------*/

%module pyossim

%{
#include <ossim/base/ossimString.h>
#include <ossim/elevation/ossimElevCellHandlerFactory.h>
%}

%include "ossim/base/ossimConstants.h"

/* Wrapping class ossimElevCellHandlerFactory */
%include "ossim/elevation/ossimElevCellHandlerFactory.h"
