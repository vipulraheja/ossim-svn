#ifndef omsImageModel_HEADER
#define omsImageModel_HEADER
#include <oms/Constants.h>
#include <ossim/base/ossimReferenced.h>
#include <ossim/base/ossimDpt.h>
#include <ossim/base/ossimGpt.h>
#include <ossim/base/ossimDrect.h>
#include <string>
namespace oms
{
class OMSDLL ImageModel
{
public:
   
   ImageModel();
   virtual ~ImageModel();
   bool setModelFromFile(const std::string& filename,
                         unsigned int entry=0);
   void centerToGround(ossimGpt& gpt)const;
   void imageToGround(const ossimDpt& imagePoint,
                      ossimGpt&  gpt,
                      unsigned int resolution = 0)const;
   
   void groundToImage(const ossimGpt& gpt,
                      ossimDpt& imagePoint,
                      unsigned int resolutionLevel=0)const;
   
protected:
   class PrivateData;
   PrivateData* thePrivateData;
};
}
#endif
