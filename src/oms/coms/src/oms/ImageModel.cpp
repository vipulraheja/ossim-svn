#include <oms/ImageModel.h>
#include <ossim/imaging/ossimImageHandlerRegistry.h>
#include <ossim/imaging/ossimImageHandler.h>
#include <ossim/projection/ossimProjection.h>
#include <ossim/projection/ossimProjectionFactoryRegistry.h>

class oms::ImageModel::PrivateData
{
public:
   ossimRefPtr<ossimImageHandler> theImageHandler;
   ossimRefPtr<ossimImageGeometry> theImageGeometry;
   ossimDrect theBoundingRect;
};
oms::ImageModel::ImageModel()
:thePrivateData(new PrivateData())
{
}
oms::ImageModel::~ImageModel()
{
   if(thePrivateData)
   {
      delete thePrivateData;
      thePrivateData = 0;
   }
}

bool oms::ImageModel::setModelFromFile(const std::string& file,
                                       unsigned int entry)
{
   bool result = false;
   thePrivateData->theImageHandler = ossimImageHandlerRegistry::instance()->open(ossimFilename(file));
   if(thePrivateData->theImageHandler.valid())
   {
      if(thePrivateData->theImageHandler->setCurrentEntry(entry))
      {
         ossimKeywordlist kwl;
         thePrivateData->theImageGeometry = thePrivateData->theImageHandler->getImageGeometry();
         thePrivateData->theBoundingRect = thePrivateData->theImageHandler->getBoundingRect();
         
         if(thePrivateData->theImageGeometry.valid()&&
            thePrivateData->theImageGeometry->getProjection())
         {
            result = false;
         }
      }
   }
   if(!result)
   {
      thePrivateData->theImageHandler  = 0;
      thePrivateData->theImageGeometry = 0;
   }
   return result;
}

void oms::ImageModel::centerToGround(ossimGpt& gpt)const
{
   if(thePrivateData->theImageHandler.valid())
   {
      imageToGround(ossimDpt(thePrivateData->theBoundingRect.width()/2.0,
                             thePrivateData->theBoundingRect.height()/2.0),
                    gpt);
   }
}

void oms::ImageModel::imageToGround(const ossimDpt& imagePoint,
                                    ossimGpt&  gpt,
                                    unsigned int resolution)const
{
   if(resolution)
   {
      ossimDpt inputPt = imagePoint;
      double scale = 1<<resolution;
      inputPt.x*=scale;
      inputPt.y*=scale;
      
      imageToGround(inputPt,
                    gpt);
   }
   else
   {
      imageToGround(imagePoint,
                    gpt);
   }
}

void oms::ImageModel::groundToImage(const ossimGpt& gpt,
                                    ossimDpt& imagePoint,
                                    unsigned int resolutionLevel)const
{
   if(thePrivateData->theImageGeometry.valid()&&thePrivateData->theImageGeometry->getProjection())
   {
      thePrivateData->theImageGeometry->worldToRn(gpt, resolutionLevel, imagePoint);
   }
}
