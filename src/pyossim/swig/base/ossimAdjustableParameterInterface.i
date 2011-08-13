/*-----------------------------------------------------------------------------
 * Filename        : ossimAdjustableParameterInterface.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimProperty
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimRtti.h>
#include <vector>
#include <ossim/base/ossimAdjustmentInfo.h>
#include <ossim/base/ossimKeywordlist.h>
#include <ossim/base/ossimObject.h>
#include <ossim/base/ossimAdjustableParameterInterface.h>

%}

#ifndef TYPE_DATA
#define TYPE_DATA

/* Handling assignment operator */
%rename(__set__) ossimAdjustableParameterInterface::operator=;

/* Wrapping class ossimAdjustableParameterInterface */
%include "ossim/base/ossimConstants.h"
%include "ossim/base/ossimAdjustableParameterInterface.h"

#endif
