#ifndef ossimSharedRgbToGreyFilter_HEADER
#define ossimSharedRgbToGreyFilter_HEADER
#include "plugin/ossimSharedObjectBridge.h"
#include "base/data_types/ossimString.h"


#include "imaging/tile_sources/ossimImageSourceFilter.h"

class ossimSharedRgbToGreyFilter : public ossimImageSourceFilter
{
public:
   ossimSharedRgbToGreyFilter(ossimObject* owner=NULL);
   ossimSharedRgbToGreyFilter(ossimImageSource* inputSource,
                        double c1 = 1.0/3.0,
                        double c2 = 1.0/3.0,
                        double c3 = 1.0/3.0);
   ossimSharedRgbToGreyFilter(ossimObject* owner,
                        ossimImageSource* inputSource,
                        double c1 = 1.0/3.0,
                        double c2 = 1.0/3.0,
                        double c3 = 1.0/3.0);
   virtual ~ossimSharedRgbToGreyFilter();
   ossimString getShortName()const
      {
         return ossimString("grey");
      }
   
   ossimString getLongName()const
      {
         return ossimString("rgb to grey scale filter");
      }
   
   virtual ossimRefPtr<ossimImageData> getTile(const ossimIrect& tileRect, ossim_uint32 resLevel=0);
   
   virtual void initialize();
   
   virtual ossimScalarType getOutputScalarType() const;
   
   ossim_uint32 getNumberOfOutputBands() const;
 
   virtual bool saveState(ossimKeywordlist& kwl,
                          const char* prefix=0)const;
   
   /*!
    * Method to the load (recreate) the state of an object from a keyword
    * list.  Return true if ok or false on error.
    */
   virtual bool loadState(const ossimKeywordlist& kwl,
                          const char* prefix=0);

protected:
   ossimRefPtr<ossimImageData> theBlankTile;
   ossimRefPtr<ossimImageData> theTile;
   void runUcharTransformation(ossimImageData* tile);
   double theC1;
   double theC2;
   double theC3;

TYPE_DATA
};

#endif
