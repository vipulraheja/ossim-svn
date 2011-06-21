//----------------------------------------------------------------------------
//
// License:  See top level LICENSE.txt file
//
// Author:  David Burken
//
// Description: OSSIM Kakadu plugin initialization
// code.
//
//----------------------------------------------------------------------------
// $Id: ossimKakaduPluginInit.cpp 11046 2007-05-25 18:03:03Z gpotts $

#include <ossim/plugin/ossimSharedObjectBridge.h>
#include <ossimPluginConstants.h>
#include <ossimKakaduOverviewBuilderFactory.h>
#include <ossimKakaduReaderFactory.h>
#include <ossimKakaduWriterFactory.h>
#include <ossim/imaging/ossimImageHandlerRegistry.h>
#include <ossim/imaging/ossimImageWriterFactoryRegistry.h>
#include <ossim/imaging/ossimOverviewBuilderFactoryRegistry.h>

static void setDescription(ossimString& description)
{
   description = "Kakadu (j2k) reader / writer plugin\n\n";
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
                                                       ossimSharedObjectInfo** info, 
                                                       const char* options)
   {    
      myInfo.getDescription = getDescription;
      myInfo.getNumberOfClassNames = getNumberOfClassNames;
      myInfo.getClassName = getClassName;
      
      *info = &myInfo;
      ossimKeywordlist kwl;
      kwl.parseString(ossimString(options));
      if(ossimString(kwl.find("reader_factory.location")).downcase() == "front")
      {
         /* Register the readers... */
         ossimImageHandlerRegistry::instance()->
         registerFactoryToFront(ossimKakaduReaderFactory::instance());
      }
      else
      {
         /* Register the readers... */
         ossimImageHandlerRegistry::instance()->
         registerFactory(ossimKakaduReaderFactory::instance());
      }


      if(ossimString(kwl.find("overview_builder_factory.location")).downcase() == "front")
      {
         /* Register the overview buildeds. */
         ossimOverviewBuilderFactoryRegistry::instance()->
         registerFactoryToFront(ossimKakaduOverviewBuilderFactory::instance());
      }
      else 
      {
         /* Register the overview buildeds. */
         ossimOverviewBuilderFactoryRegistry::instance()->
         registerFactory(ossimKakaduOverviewBuilderFactory::instance(),
                         false);
      }
      
      if(ossimString(kwl.find("writer_factory.location")).downcase() == "front")
      {
         /* Register the writers... */
         ossimImageWriterFactoryRegistry::instance()->
         registerFactoryToFront(ossimKakaduWriterFactory::instance());
         
      }
      else 
      {
      
         /* Register the writers... */
         ossimImageWriterFactoryRegistry::instance()->
         registerFactory(ossimKakaduWriterFactory::instance());
         
      }
      
      setDescription(theDescription);
   }
   
   /* Note symbols need to be exported on windoze... */ 
   OSSIM_PLUGINS_DLL void ossimSharedLibraryFinalize()
   {
      ossimImageHandlerRegistry::instance()->
         unregisterFactory(ossimKakaduReaderFactory::instance());
      
      ossimOverviewBuilderFactoryRegistry::instance()->
         unregisterFactory(ossimKakaduOverviewBuilderFactory::instance());
      
      ossimImageWriterFactoryRegistry::instance()->
         unregisterFactory(ossimKakaduWriterFactory::instance());
   }
}
