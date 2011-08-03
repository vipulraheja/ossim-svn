/*-----------------------------------------------------------------------------
 * Filename        : ossim2dTo2dTransform.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossim2dTo2dTransform
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <map>

#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimConnectableObject.h>
#include <ossim/base/ossimConnectableObjectListener.h>
#include <ossim/base/ossimConnectableContainerInterface.h>
#include <ossim/base/ossimConnectableContainer.h>

%}

#ifndef TYPE_DATA
#define TYPE_DATA

/* Wrapping class ossimConnectableContainer */
%include "ossim/base/ossimConstants.h"
%include "ossim/base/ossimConnectableContainer.h" 

#endif
