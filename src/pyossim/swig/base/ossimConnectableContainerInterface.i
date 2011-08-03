/*-----------------------------------------------------------------------------
 * Filename        : ossimConnectableContainerInterface.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimConnectableContainerInterface
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimRtti.h>
#include <ossim/base/ossimId.h>
#include <ossim/base/ossimConnectableObject.h>
#include <ossim/base/ossimConnectableContainerInterface.h>
#include <vector>

%}

#ifndef TYPE_DATA
#define TYPE_DATA

/* Wrapping class ossimConnectableContainerInterface */
%include "ossim/base/ossimConstants.h"
%include "ossim/base/ossimConnectableContainerInterface.h"

#endif
