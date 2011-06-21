//*******************************************************************
// Copyright (C) 2005 David Burken, all rights reserved.
//
// License:  LGPL
// 
// See LICENSE.txt file in the top level directory for more details.
//
// Author:  David Burken
//*******************************************************************
//  $Id: ossimUnitTestPluginInit.cpp 9121 2006-06-14 20:23:26Z gpotts $
#include <gdal.h>
#include <ossim/plugin/ossimSharedObjectBridge.h>
#include <ossimPluginConstants.h>
#include <ossim/imaging/ossimImageHandlerRegistry.h>
#include <ossim/imaging/ossimImageSourceFactoryRegistry.h>
#include <ossim/imaging/ossimImageWriterFactoryRegistry.h>
#include <ossim/projection/ossimProjectionFactoryRegistry.h>
#include "ossimUnitTestImageSourceFactory.h"

static void setDescription(ossimString& description)
{
   description = "Unit test Plugin\n\n"
      "Tests parts of the OSSIM library.  This is mainly\n"
      "used for interactive GUI testing.  Components tested:\n"
      "ossimPolyCutter";
}


extern "C"
{
   ossimSharedObjectInfo  myInfo;
   ossimString theDescription;
   std::vector<ossimString> theObjList;
   const char* getDescription()
   {
      return theDescription.c_str();
   }
   int getNumberOfClassNames()
   {
      return (int)theObjList.size();
   }
   const char* getClassName(int idx)
   {
      if(idx < (int)theObjList.size())
      {
         return theObjList[0].c_str();
      }
      return (const char*)0;
   }

   /* Note symbols need to be exported on windoze... */ 
   OSSIM_PLUGINS_DLL void ossimSharedLibraryInitialize(
      ossimSharedObjectInfo** info)
   {
      myInfo.getDescription = getDescription;
      myInfo.getNumberOfClassNames = getNumberOfClassNames;
      myInfo.getClassName = getClassName;
      
      *info = &myInfo;

      /* Register the readers... */
      ossimImageSourceFactoryRegistry::instance()->
         registerFactory(ossimUnitTestImageSourceFactory::instance());
      
      setDescription(theDescription);
   }
   
   /* Note symbols need to be exported on windoze... */ 
   OSSIM_PLUGINS_DLL void ossimSharedLibraryFinalize()
   {
      ossimImageSourceFactoryRegistry::instance()->
         registerFactory(ossimUnitTestImageSourceFactory::instance());
      
   }
}
