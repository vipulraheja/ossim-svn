/*-----------------------------------------------------------------------------
 * Filename        : ossimNitfProjectionFactory.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimMapProjection
 * -----------------------------------------------------------------------------*/

%module pyossim

%{
#include <vector>
#include <ossim/projection/ossimProjectionFactoryBase.h>
#include <ossim/projection/ossimNitfProjectionFactory.h>
%}       

%include "ossim/base/ossimConstants.h"

/* Wrapping the class */
%include "ossim/projection/ossimNitfProjectionFactory.h"
