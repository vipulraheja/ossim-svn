/*-----------------------------------------------------------------------------
 * Filename        : ossimSensorModel.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimSensorModel
 * -----------------------------------------------------------------------------*/

%module pyossim

%{
#include <ossim/projection/ossimSensorModel.h>
%}        

#ifndef TYPE_DATA
#define TYPE_DATA

/* Handling operators */
%rename(__cmp__) ossimSensorModel::operator==;
%rename(ossimSensorModel_print) print;

%include "ossim/base/ossimConstants.h"

/* Wrapping class ossimSensorModel */    
%include "ossim/projection/ossimSensorModel.h"

#endif
