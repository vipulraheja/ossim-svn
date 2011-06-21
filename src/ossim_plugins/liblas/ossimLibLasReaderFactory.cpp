//----------------------------------------------------------------------------
//
// File: ossimLibLasReaderFactory.cpp
// 
// License:  See top level LICENSE.txt file
//
// Author:  David Burken
//
// Description: Reader factory for OSSIM libLAS plugin.
//----------------------------------------------------------------------------
// $Id: ossimLibLasReaderFactory.cpp 2645 2011-05-26 15:21:34Z oscar.kramer $

#include "ossimLibLasReaderFactory.h"
#include "ossimLibLasReader.h"
#include <ossim/base/ossimKeywordlist.h>
#include <ossim/base/ossimRefPtr.h>
#include <ossim/base/ossimString.h>
#include <ossim/imaging/ossimImageHandler.h>
#include <ossim/base/ossimTrace.h>
#include <ossim/base/ossimKeywordNames.h>

static const ossimTrace traceDebug("ossimLibLasReaderFactory:debug");

RTTI_DEF1(ossimLibLasReaderFactory,
          "ossimLibLasReaderFactory",
          ossimImageHandlerFactoryBase);

ossimLibLasReaderFactory* ossimLibLasReaderFactory::theInstance = 0;

ossimLibLasReaderFactory::~ossimLibLasReaderFactory()
{
   theInstance = 0;
}

ossimLibLasReaderFactory* ossimLibLasReaderFactory::instance()
{
   if(!theInstance)
   {
      theInstance = new ossimLibLasReaderFactory;
   }
   return theInstance;
}
   
ossimImageHandler* ossimLibLasReaderFactory::open(
   const ossimFilename& fileName, bool openOverview)const
{
   if(traceDebug())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << "ossimLibLasReaderFactory::open(filename) DEBUG: entered..."
         << "\ntrying ossimLibLasReader"
         << std::endl;
   }
   
   ossimRefPtr<ossimImageHandler> reader = 0;

   reader = new ossimLibLasReader;
   reader->setOpenOverviewFlag(openOverview);
   if(reader->open(fileName) == false)
   {
      reader = 0;
   }
   
   if(traceDebug())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << "ossimLibLasReaderFactory::open(filename) DEBUG: leaving..."
         << std::endl;
   }
   
   return reader.release();
}

ossimImageHandler* ossimLibLasReaderFactory::open(const ossimKeywordlist& kwl,
                                               const char* prefix)const
{
   if(traceDebug())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << "ossimLibLasReaderFactory::open(kwl, prefix) DEBUG: entered..."
         << "Trying ossimLibLasReader"
         << std::endl;
   }

   ossimRefPtr<ossimImageHandler> reader = new ossimLibLasReader;
   if(reader->loadState(kwl, prefix) == false)
   {
      reader = 0;
   }
   
   if(traceDebug())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << "ossimLibLasReaderFactory::open(kwl, prefix) DEBUG: leaving..."
         << std::endl;
   }
   
   return reader.release();
}

ossimObject* ossimLibLasReaderFactory::createObject(
   const ossimString& typeName)const
{
   ossimRefPtr<ossimObject> result = 0;
   if(typeName == "ossimLibLasReader")
   {
      // result = new ossimLibLasReader;
   }
   return result.release();
}

ossimObject* ossimLibLasReaderFactory::createObject(const ossimKeywordlist& kwl,
                                                 const char* prefix)const
{
   return this->open(kwl, prefix);
}
 
void ossimLibLasReaderFactory::getTypeNameList(std::vector<ossimString>& typeList)const
{
   typeList.push_back(ossimString("ossimLibLasReader"));
}

void ossimLibLasReaderFactory::getSupportedExtensions(
   ossimImageHandlerFactoryBase::UniqueStringList& extensionList)const
{
   extensionList.push_back(ossimString("las"));
}

ossimLibLasReaderFactory::ossimLibLasReaderFactory(){}

ossimLibLasReaderFactory::ossimLibLasReaderFactory(const ossimLibLasReaderFactory&){}

void ossimLibLasReaderFactory::operator=(const ossimLibLasReaderFactory&){}
