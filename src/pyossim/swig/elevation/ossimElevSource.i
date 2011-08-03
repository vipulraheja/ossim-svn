/*-----------------------------------------------------------------------------
 * Filename        : ossimElevSource.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimElevSource
 * -----------------------------------------------------------------------------*/

%module pyossim

%{
#include <ossim/elevation/ossimElevSource.h>
%}

#ifndef TYPE_DATA
#define TYPE_DATA

/* Handling operators */
%rename(__set__) ossimElevSource::operator=;

%include "ossim/base/ossimConstants.h"

/* Wrapping class ossimElevSource */
%include "ossim/elevation/ossimElevSource.h"

#endif
