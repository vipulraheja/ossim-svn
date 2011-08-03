/*-----------------------------------------------------------------------------
 * Filename        : ossimDataObject.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimDataObject
 * -----------------------------------------------------------------------------*/

%module pyossim

%{
#include <ossim/base/ossimDataObject.h>
%}

#ifndef TYPE_DATA
#define TYPE_DATA

/* OPERATORS */
/* Handling operators */
%rename(__set__) ossimDataObject::operator=;
%rename(__cmp__) ossimDataObject::operator==;
%rename(__ne__) ossimDataObject::operator!=;
%rename(ossimDataObject_print) print;
  
/* Wrapping class ossimDataObject */
%include "ossim/base/ossimConstants.h"
%include "ossim/base/ossimDataObject.h"

#endif
