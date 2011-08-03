/*-----------------------------------------------------------------------------
 * Filename        : ossimDtedHandler.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimDtedHandler
 * -----------------------------------------------------------------------------*/

%module pyossim

%{
#include <ossim/elevation/ossimDtedHandler.h>
%}

#ifndef TYPE_DATA
#define TYPE_DATA

/* Handling operators */
%rename(__set__) ossimDtedHandler::operator=;

%include "ossim/base/ossimConstants.h"

/* Handling class ossimDtedHandler */
%include "ossim/elevation/ossimDtedHandler.h"

#endif
