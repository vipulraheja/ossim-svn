/*-----------------------------------------------------------------------------
 * Filename        : ossimImageHandlerRegistry.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimImageHandlerRegistry
 * -----------------------------------------------------------------------------*/

#ifndef TYPE_DATA
#define TYPE_DATA 

%module pyossim

%{
#include <ossim/imaging/ossimImageHandlerRegistry.h>
%}
     
%rename(__set__) ossimImageHandlerRegistry::operator=;

%include "ossim/imaging/ossimConstants.h"

/* Wrapping class ossimImageHandlerRegistry */
%include "ossim/imaging/ossimImageHandlerRegistry.h"

#endif
