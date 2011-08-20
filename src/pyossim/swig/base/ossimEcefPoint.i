/*-----------------------------------------------------------------------------
 * Filename        : ossimEcefPoint.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimLsrRay
 * -----------------------------------------------------------------------------*/

%module pyossim

%{
#include <iosfwd>
#include <ossim/base/ossimCommon.h>
#include <ossim/base/ossimColumnVector3d.h>
#include <ossim/base/ossimNotify.h>
#include <ossim/base/ossimString.h>
#include <ossim/base/ossimEcefPoint.h>
#include <ossim/base/ossimEcefVector.h>
%}

/* Handling operators */
%rename(__add__) ossimEcefPoint::operator+;
%rename(__sub__) ossimEcefPoint::operator-;
%rename(__set__) ossimEcefPoint::operator=;
%rename(__cmp__) ossimEcefPoint::operator==;
%rename(__ne__) ossimEcefPoint::operator!=;
%rename(__lshift__) operator<<;
%rename(ossimEcefPoint_print) print;
%rename(__getitem__) ossimEcefPoint::operator[];

/* Wrapping class */
%include "ossim/base/ossimConstants.h"
%include "ossim/base/ossimEcefPoint.h"
