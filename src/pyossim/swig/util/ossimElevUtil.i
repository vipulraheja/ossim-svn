/*-----------------------------------------------------------------------------
 * Filename        : ossimElevUtil.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossim2dTo2dTransform
 * -----------------------------------------------------------------------------*/

%module pyossim
%{

#include <map>
#include <vector>

#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimReferenced.h>
#include <ossim/base/ossimRefPtr.h>
#include <ossim/imaging/ossimImageSource.h>
#include <ossim/imaging/ossimSingleImageChain.h>
#include <ossim/projection/ossimMapProjection.h>
#include <ossim/util/ossimElevUtil.h>

%}

/* Wrapping class ossimElevUtil */
%include "ossim/base/ossimConstants.h"
%include "ossim/util/ossimElevUtil.h"
