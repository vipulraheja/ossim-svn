/*-----------------------------------------------------------------------------
Filename        : ossimProjectionFactoryRegistry.i
Author          : Vipul Raheja
License         : See top level LICENSE.txt file.
-----------------------------------------------------------------------------*/

%module pyossim

%{
#include <ossim/projection/ossimProjectionFactoryRegistry.h>
%}

/* Handling assignment operator */
%rename(__set__) ossimProjectionFactoryRegistry::operator=;

%include "ossim/base/ossimConstants.h"

/* Wrapping class ossimProjectionFactoryRegistry */
%include "ossim/projection/ossimProjectionFactoryRegistry.h"
