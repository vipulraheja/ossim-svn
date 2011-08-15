/*-----------------------------------------------------------------------------
 * Filename        : ossimTiffProjectionFactory.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimMapProjection
 * -----------------------------------------------------------------------------*/

%module pyossim

%{
#include <ossim/projection/ossimProjectionFactoryBase.h>
#include <ossim/projection/ossimTiffProjectionFactory.h>
%}

/* Wrapping the class */
%include "ossim/projection/ossimTiffProjectionFactory.h"
