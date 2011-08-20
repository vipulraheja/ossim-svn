/*-----------------------------------------------------------------------------
Filename        : ossimErrorStatusInterface.i
Author          : Vipul Raheja
License         : See top level LICENSE.txt file.
Description     : Contains SWIG-Python of class ossimObject
-----------------------------------------------------------------------------*/

%module pyossim

%{
#include <iosfwd>
#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimRtti.h>
#include <ossim/base/ossimErrorCodes.h>
#include <ossim/base/ossimErrorStatusInterface.h>
%}

#ifndef TYPE_DATA
#define TYPE_DATA

/* Handling operator */
%rename(__lshift__) operator<<;

/* Handling the reserved function print */
%rename(ossimErrorStatusInterface_print) ossimErrorStatusInterface::print;

/* Wrapping the class */
%include "ossim/base/ossimConstants.h"

/*!
 *  class ossimErrorStatusInterface
 *  Provides common interfaces for error handling.
 *
 *  Note: For error codes and associated strings use the ossimErrorCodes class.
 */
%include "ossim/base/ossimErrorStatusInterface.h"

#endif
