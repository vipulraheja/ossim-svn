/*-----------------------------------------------------------------------------
 * Filename        : ossimElevationDatabase.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimElevationDatabase
 * -----------------------------------------------------------------------------*/

%module pyossim

%{
#include <ossim/elevation/ossimElevationDatabase.h>
%}

#ifndef TYPE_DATA
#define TYPE_DATA

/* Handling operators */
%rename(__set__) ossimElevationDatabase::operator=;
%rename(__set__) CellInfo::operator=;
%rename(__set__) ossimElevationCellDatabase::operator=;

%include "ossim/base/ossimConstants.h"

/* Wrapping class ossimElevationDatabase */    
%include "ossim/elevation/ossimElevationDatabase.h"

#endif
