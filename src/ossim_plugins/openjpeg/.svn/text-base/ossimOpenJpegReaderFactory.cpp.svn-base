//----------------------------------------------------------------------------
//
// License:  See top level LICENSE.txt file
//
// Author:  David Burken
//
// Description: Factory for J2k image readers OpenJPEG library.
//----------------------------------------------------------------------------
// $Id: ossimOpenJpegReaderFactory.cpp 11046 2007-05-25 18:03:03Z gpotts $

#include <ossimOpenJpegReaderFactory.h>
#include <ossimOpenJpegReader.h>
#include <ossimOpenJpegNitfReader.h>
#include <ossim/base/ossimKeywordlist.h>
#include <ossim/base/ossimString.h>
#include <ossim/imaging/ossimImageHandler.h>
#include <ossim/base/ossimTrace.h>
#include <ossim/base/ossimKeywordNames.h>

static const ossimTrace traceDebug("ossimOpenJpegReaderFactory:debug");

RTTI_DEF1(ossimOpenJpegReaderFactory,
          "ossimOpenJpegReaderFactory",
          ossimImageHandlerFactoryBase);

ossimOpenJpegReaderFactory* ossimOpenJpegReaderFactory::theInstance = 0;

ossimOpenJpegReaderFactory::~ossimOpenJpegReaderFactory()
{
   theInstance = 0;
}

ossimOpenJpegReaderFactory* ossimOpenJpegReaderFactory::instance()
{
   if(!theInstance)
   {
      theInstance = new ossimOpenJpegReaderFactory;
   }
   return theInstance;
}
   
ossimImageHandler* ossimOpenJpegReaderFactory::open(
   const ossimFilename& fileName, bool openOverview)const
{
   if(traceDebug())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << "ossimOpenJpegReaderFactory::open(filename) DEBUG: entered..."
         << "\ntrying ossimOpenJpegReader"
         << std::endl;
   }
   
   ossimRefPtr<ossimImageHandler> reader = new ossimOpenJpegReader;
   reader->setOpenOverviewFlag(openOverview);
   if(reader->open(fileName) == false)
   {
      // Try the nitf reader.
      if(traceDebug())
      {
         ossimNotify(ossimNotifyLevel_DEBUG)
            << "ossimOpenJpegReaderFactory::open(filename) DEBUG: entered..."
            << "\ntrying ossimOpenJpegNitfReader"
            << std::endl;
      }
      reader = new ossimOpenJpegNitfReader;
      if(reader->open(fileName) == false)
      {
         reader = 0;
      }
   }
   
   if(traceDebug())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << "ossimOpenJpegReaderFactory::open(filename) DEBUG: leaving..."
         << std::endl;
   }
   
   return reader.release();
}

ossimImageHandler* ossimOpenJpegReaderFactory::open(
   const ossimKeywordlist& kwl, const char* prefix)const
{
   if(traceDebug())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << "ossimOpenJpegReaderFactory::open(kwl, prefix) DEBUG: entered..."
         << "Trying ossimOpenJpegReader"
         << std::endl;
   }

   ossimRefPtr<ossimImageHandler> reader = new ossimOpenJpegReader;
   if(reader->loadState(kwl, prefix) == false)
   {
      // Try the nitf reader.
      reader = new ossimOpenJpegNitfReader;
      if(reader->loadState(kwl, prefix) == false)
      {
         reader = 0;
      }
   }
   
   if(traceDebug())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << "ossimOpenJpegReaderFactory::open(kwl, prefix) DEBUG: leaving..."
         << std::endl;
   }
   
   return reader.release();
}

ossimObject* ossimOpenJpegReaderFactory::createObject(
   const ossimString& typeName)const
{
   if(typeName == "ossimOpenJpegReader")
   {
      return new ossimOpenJpegReader;
   }
   else if(typeName == "ossimOpenJpegNitfReader")
   {
      return new ossimOpenJpegNitfReader;
   }
   return 0;
}

ossimObject* ossimOpenJpegReaderFactory::createObject(
   const ossimKeywordlist& kwl,
   const char* prefix)const
{
   return this->open(kwl, prefix);
}
 
void ossimOpenJpegReaderFactory::getTypeNameList(
   std::vector<ossimString>& typeList)const
{
   typeList.push_back(ossimString("ossimOpenJpegReader"));
   typeList.push_back(ossimString("ossimOpenJpegNitfReader"));
}

void ossimOpenJpegReaderFactory::getSupportedExtensions(
   ossimImageHandlerFactoryBase::UniqueStringList& extensionList)const
{
   extensionList.push_back(ossimString("j2k"));
}

ossimOpenJpegReaderFactory::ossimOpenJpegReaderFactory(){}

ossimOpenJpegReaderFactory::ossimOpenJpegReaderFactory(const ossimOpenJpegReaderFactory&){}

void ossimOpenJpegReaderFactory::operator=(const ossimOpenJpegReaderFactory&){}
