//----------------------------------------------------------------------------
//
// License:  See top level LICENSE.txt file
//
// Author:  David Burken
//
// Description: Factory for OSSIM Open JPEG writer.
//----------------------------------------------------------------------------
// $Id: ossimOpenJpegWriterFactory.cpp 11046 2007-05-25 18:03:03Z gpotts $

#include <cstddef>


#include "ossimOpenJpegWriterFactory.h"
#include "ossimOpenJpegWriter.h"
#include <ossim/base/ossimKeywordNames.h>
#include <ossim/imaging/ossimImageFileWriter.h>

ossimOpenJpegWriterFactory* ossimOpenJpegWriterFactory::theInstance = NULL;

RTTI_DEF1(ossimOpenJpegWriterFactory,
          "ossimOpenJpegWriterFactory",
          ossimImageWriterFactoryBase);

ossimOpenJpegWriterFactory::~ossimOpenJpegWriterFactory()
{
   theInstance = NULL;
}

ossimOpenJpegWriterFactory* ossimOpenJpegWriterFactory::instance()
{
   if(!theInstance)
   {
      theInstance = new ossimOpenJpegWriterFactory;
   }
   return theInstance;
}

ossimImageFileWriter *ossimOpenJpegWriterFactory::createWriterFromExtension(
   const ossimString& fileExtension)const
{
   ossimOpenJpegWriter* writer = NULL;
   if ( (fileExtension == "png") || (fileExtension == ".png") )
   {
      writer = new ossimOpenJpegWriter;
   }
   return writer;
}

ossimImageFileWriter* ossimOpenJpegWriterFactory::createWriter(
   const ossimKeywordlist& kwl, const char *prefix)const
{
   ossimRefPtr<ossimImageFileWriter> writer = 0;
   const char* type = kwl.find(prefix, ossimKeywordNames::TYPE_KW);
   if (type)
   {
      writer = createWriter(ossimString(type));
      if (writer.valid())
      {
         if (writer->loadState(kwl, prefix) == false)
         {
            writer = 0;
         }
      }
   }
   return writer.release();
}

ossimImageFileWriter* ossimOpenJpegWriterFactory::createWriter(
   const ossimString& typeName)const
{
   ossimRefPtr<ossimImageFileWriter> writer = 0;
   if (typeName == "ossimOpenJpegWriter")
   {
      writer = new ossimOpenJpegWriter;
   }
   else
   {
      // See if the type name is supported by the writer.
      writer = new ossimOpenJpegWriter;
      if ( writer->hasImageType(typeName) == false )
      {
         writer = 0;
      }
   }
   return writer.release();
}

ossimObject* ossimOpenJpegWriterFactory::createObject(
   const ossimKeywordlist& kwl, const char *prefix)const
{
   return createWriter(kwl, prefix);
}

ossimObject* ossimOpenJpegWriterFactory::createObject(
   const ossimString& typeName) const
{
   return createWriter(typeName);
}

void ossimOpenJpegWriterFactory::getExtensions(
   std::vector<ossimString>& result)const
{
   result.push_back("png");
}

void ossimOpenJpegWriterFactory::getTypeNameList(std::vector<ossimString>& typeList)const
{
   getImageTypeList(typeList);
}

void ossimOpenJpegWriterFactory::getImageTypeList(std::vector<ossimString>& imageTypeList)const
{
   ossimRefPtr<ossimOpenJpegWriter> writer = new ossimOpenJpegWriter;
   writer->getImageTypeList(imageTypeList);
}

ossimOpenJpegWriterFactory::ossimOpenJpegWriterFactory(){}

ossimOpenJpegWriterFactory::ossimOpenJpegWriterFactory(const ossimOpenJpegWriterFactory&){}

void ossimOpenJpegWriterFactory::operator=(const ossimOpenJpegWriterFactory&){}




