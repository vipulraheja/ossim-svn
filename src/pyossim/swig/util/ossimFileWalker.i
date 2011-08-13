/*-----------------------------------------------------------------------------
 * Filename        : ossimFileWalker.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossim2dTo2dTransform
 * -----------------------------------------------------------------------------*/


%module pyossim

%{

#include <string>
#include <vector>
#include <ossim/base/ossimCallback2wRet.h>
#include <ossim/base/ossimConstants.h>
#include <ossim/util/ossimFileWalker.h>

%}

/* Wrapping class ossimFileWalker */
%include "ossim/base/ossimConstants.h"
%include "ossim/util/ossimFileWalker.h"
