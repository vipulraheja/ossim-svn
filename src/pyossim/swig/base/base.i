/*-----------------------------------------------------------------------------
Filename        : base.i
Author          : Vipul Raheja
License         : See top level LICENSE.txt file.
Description     : Contains SWIG-Python of class ossimInit which handles 
all aspects of initialization for OSSIM applications.
-----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimConnectableObject.h>
#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimDpt.h>
#include <ossim/base/ossimFilename.h>
#include <ossim/base/ossimGpt.h>
#include <ossim/base/ossimIpt.h>
#include <ossim/base/ossimIrect.h>
#include <ossim/base/ossimString.h>
#include <ossim/base/ossimKeywordlist.h>
#include <ossim/base/ossimObject.h>
#include <ossim/base/ossimObjectFactory.h>
#include <ossim/base/ossimProperty.h>
#include <ossim/base/ossimPropertyInterface.h>
#include <ossim/base/ossimRefPtr.h>
#include <ossim/base/ossimSource.h>
#include <ossim/base/ossimString.h>
#include <ossim/base/ossimRefPtr.h>
#include <vector>
#include <string>

%}



