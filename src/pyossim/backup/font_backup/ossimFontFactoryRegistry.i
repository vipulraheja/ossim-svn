/*-----------------------------------------------------------------------------
 * Filename        : ossimFontFactoryRegistry.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimFontFactoryRegistry
 * -----------------------------------------------------------------------------*/

%module pyossim

%{
#include <ossim/font/ossimFontFactoryRegistry.h>
%}

%include "ossim/base/ossimConstants.h"

/* Handling operators */
%rename(__set__) ossimFontFactoryRegistry::operator=;

/* Wrapping class ossimFontFactoryRegistry */
%include "ossim/font/ossimFontFactoryRegistry.h"
