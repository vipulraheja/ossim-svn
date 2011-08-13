/*-----------------------------------------------------------------------------
 * Filename        : ossimContainerProperty.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimProperty
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <vector>
#include <ossim/base/ossimRefPtr.h>
#include <ossim/base/ossimProperty.h>
#include <ossim/base/ossimContainerProperty.h>

%}

#ifndef TYPE_DATA
#define TYPE_DATA

/* Wrapping the class */
%include "ossim/base/ossimConstants.h"
%include "ossim/base/ossimContainerProperty.h"

#endif
