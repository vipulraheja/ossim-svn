//*******************************************************************
//
// License:  See top level LICENSE.txt file.
// 
// Author: Garrett Potts (gpotts@imagelinks)
// Description: A brief description of the contents of the file.
//
//*************************************************************************
// $Id: ossimSharedRgbToGreyFilter.cpp 15323 2009-09-01 19:19:48Z gpotts $
#include <base/common/ossimRefPtr.h>
#include "ossimSharedRgbToGreyFilter.h"
#include <imaging/ossimU8ImageData.h>
#include <base/common/ossimConstants.h>
#include <base/common/ossimCommon.h>
#include <base/data_types/ossimKeywordlist.h>
#include <base/common/ossimKeywordNames.h>
#include <imaging/factory/ossimImageSourceFactoryBase.h>
#include <imaging/factory/ossimImageSourceFactoryRegistry.h>
#include <base/common/ossimRefPtr.h>

RTTI_DEF1(ossimSharedRgbToGreyFilter, "ossimSharedRgbToGreyFilter", ossimImageSourceFilter)

ossimSharedRgbToGreyFilter::ossimSharedRgbToGreyFilter(ossimObject* owner)
   :ossimImageSourceFilter(owner),
    theTile(NULL),
    theC1(1.0/3.0),
    theC2(1.0/3.0),
    theC3(1.0/3.0)
{
}

ossimSharedRgbToGreyFilter::ossimSharedRgbToGreyFilter(ossimImageSource* inputSource,
                                           double c1,
                                           double c2,
                                           double c3)
   : ossimImageSourceFilter(NULL, inputSource),
     theTile(NULL),
     theC1(c1),
     theC2(c2),
     theC3(c3)
{
}

ossimSharedRgbToGreyFilter::ossimSharedRgbToGreyFilter(ossimObject* owner,
                                           ossimImageSource* inputSource,
                                           double c1,
                                           double c2,
                                           double c3)
   : ossimImageSourceFilter(owner, inputSource),
     theTile(NULL),
     theC1(c1),
     theC2(c2),
     theC3(c3)
{
}

ossimSharedRgbToGreyFilter::~ossimSharedRgbToGreyFilter()
{
}

ossimRefPtr<ossimImageData> ossimSharedRgbToGreyFilter::getTile(const ossimIrect& tileRect,
                                                                ossim_uint32 resLevel)
{
   if(!isSourceEnabled())
   {
      return ossimImageSourceFilter::getTile(tileRect,
                                             resLevel);
   }
   long w     = tileRect.width();
   long h     = tileRect.height();

   
   if(!theTile.valid()) initialize();
   if(!theTile.valid()) return 0;
   
   if(!theTile.valid()) return 0;
   
   ossimRefPtr<ossimImageData> data = 0;
   if(theInputConnection)
   {
      data  = theInputConnection->getTile(tileRect, resLevel);
   }
   else
   {
      return 0;
   }

   if(!data.valid()) return 0;
   if(data->getDataObjectStatus() == OSSIM_NULL ||
      data->getDataObjectStatus() == OSSIM_EMPTY)
   {
      return 0;
   }

   theTile->setImageRectangle(tileRect);
   theTile->makeBlank();
   
   theTile->setOrigin(tileRect.ul());
   runUcharTransformation(data.get());
   
   return theTile;
   
}

void ossimSharedRgbToGreyFilter::initialize()
{
   if(theInputConnection)
   {
      theTile = 0;
      
      theTile = new ossimU8ImageData(this,
                                     1,
                                     theInputConnection->getTileWidth(),
                                     theInputConnection->getTileHeight());  
      theTile->initialize();
   }
}

ossimScalarType ossimSharedRgbToGreyFilter::getOutputScalarType() const
{
   if(!isSourceEnabled())
   {
      return ossimImageSourceFilter::getOutputScalarType();
   }
   
   return OSSIM_UCHAR;
}

ossim_uint32 ossimSharedRgbToGreyFilter::getNumberOfOutputBands() const
{
   if(!isSourceEnabled())
   {
      return ossimImageSourceFilter::getNumberOfOutputBands();
   }
   return 1;
}

bool ossimSharedRgbToGreyFilter::saveState(ossimKeywordlist& kwl,
                                     const char* prefix)const
{
   ossimImageSourceFilter::saveState(kwl, prefix);

   kwl.add(prefix,
           "c1",
           theC1,
           true);
   kwl.add(prefix,
           "c2",
           theC2,
           true);
   kwl.add(prefix,
           "c3",
           theC3,
           true);
   
   return true;
}

bool ossimSharedRgbToGreyFilter::loadState(const ossimKeywordlist& kwl,
                                     const char* prefix)
{
   ossimImageSourceFilter::loadState(kwl, prefix);

   const char* lookup = kwl.find(prefix, "c1");
   if(lookup)
   {
      theC1 = ossimString(lookup).toDouble();
   }
   lookup = kwl.find(prefix, "c2");
   if(lookup)
   {
      theC2 = ossimString(lookup).toDouble();
   }
   lookup = kwl.find(prefix, "c3");
   if(lookup)
   {
      theC3 = ossimString(lookup).toDouble();
   }
   return true;
}

void ossimSharedRgbToGreyFilter::runUcharTransformation(ossimImageData* tile)
{   
   unsigned char* bandSrc[tile->getNumberOfBands()];
   unsigned char* bandDest;
   
   if(tile->getNumberOfBands() == 1)
   {
      bandSrc[0]  = static_cast<unsigned char*>(tile->getBuf(0));
      bandSrc[1]  = static_cast<unsigned char*>(tile->getBuf(0));
      bandSrc[2]  = static_cast<unsigned char*>(tile->getBuf(0));
   }
   else if(tile->getNumberOfBands() == 2)
   {
      bandSrc[0]  = static_cast<unsigned char*>(tile->getBuf(0));
      bandSrc[1]  = static_cast<unsigned char*>(tile->getBuf(1));
      bandSrc[2]  = static_cast<unsigned char*>(tile->getBuf(1));      
   }
   else if(tile->getNumberOfBands() == 3)
   {
      bandSrc[0]  = static_cast<unsigned char*>(tile->getBuf(0));
      bandSrc[1]  = static_cast<unsigned char*>(tile->getBuf(1));
      bandSrc[2]  = static_cast<unsigned char*>(tile->getBuf(2));      
   }
   
   bandDest = static_cast<unsigned char*>(theTile->getBuf());
   
   long offset;

   long upperBound = tile->getWidth()*tile->getHeight();
   for(offset = 0; offset < upperBound; ++offset)
   {
      long value;
      
      value = irint(theC1*(bandSrc[0][offset]) +
                    theC2*(bandSrc[1][offset]) +
                    theC3*(bandSrc[2][offset]));
      
      value = value<255?value:255;
      value = value>0?value:0;

      bandDest[offset] = value;
   }

   theTile->validate();
}

class ossimMyFactory : public ossimImageSourceFactoryBase
{
public:
   ossimMyFactory()
      {
      }
   virtual ~ossimMyFactory()
      {
         ossimImageSourceFactoryRegistry::instance()->unregisterFactory(instance());
         
      }
   
   static ossimMyFactory* instance();
   virtual ossimImageSource* createImageSource(const ossimString& name)const;
   virtual ossimImageSource* createImageSource(const ossimKeywordlist& kwl,
                                               const char* prefix=0)const;
   virtual void getTypeNameList(std::vector<ossimString>& typeList)const;
protected:
   static ossimMyFactory* theInstace;
   
TYPE_DATA
};

RTTI_DEF1(ossimMyFactory, "ossimMyFactory", ossimImageSourceFactoryBase);

ossimRefPtr<ossimMyFactory> ossimMyFactory::theInstance=0;

ossimMyFactory* ossimMyFactory::instance()
{
   if(!theInstance)
   {
      theinstace = new ossimMyFactory;
   }

   return theInstance;
}

ossimObject* ossimMyFactory::createObject(const ossimString& typeName)const
{
   if(typeName == STATIC_TYPE_NAME(ossimSharedRgbToGreyFilter))
   {
      return new ossimSharedRgbToGreyFilter;
   }

   return (ossimObject*)NULL;
}

ossimObject* ossimMyFactory::createObject(const ossimKeywordlist& kwl,
                                          const char* prefix)const
{
   const char* type = kwl.find(prefix, ossimKeywordNames::TYPE_KW);
   ossimObject* result = NULL;
   if(type)
   {
      result = createObject(ossimString(type));
      if(result)
      {
         result->loadState(kwl, prefix);
      }
   }

   return result;
}

void ossimMyFactory::getTypeNameList(std::vector<ossimString>& typeList)const
{
   typeList.push_back(STATIC_TYPE_NAME(ossimSharedRgbToGreyFilter));
}


extern "C"
{
   ossimSharedObjectInfo myInfo;
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
         return theObjList[idx].c_str();
      }
      return 0;
   }
   void ossimSharedLibraryInitialize(ossimSharedObjectInfo** info)
   {
      myInfo.getDescription        = getDescription;
      myInfo.getNumberOfClassNames = getNumberOfClassNames;
      myInfo.getClassName          = getClassName;
      *info = &myInfo;
      theDescription = ossimString("Shared library example\n\n")+ "RGB to grey filter\n\n";
      theObjList.push_back("ossimSharedRgbToGreyFilter");
      ossimImageSourceFactoryRegistry::instance()->registerFactory(ossimMyFactory::instance());
   }
   
   void ossimSharedLibraryFinalize()
   {
      ossimImageSourceFactoryRegistry::instance()->unregisterFactory(ossimMyFactory::instance());
   }
}
