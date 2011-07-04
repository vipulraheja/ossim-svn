/*-----------------------------------------------------------------------------
 * Filename        : ossimMapProjectionInfo.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimMapProjectionInfo
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimObject.h>
#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimGpt.h>
#include <ossim/base/ossimDpt.h>
#include <ossim/base/ossimDrect.h>
#include <ossim/base/ossimString.h>
#include <ossim/projection/ossimMapProjectionInfo.h>

%}

%import "ossim/projection/ossimMapProjection.h";
%import "ossim/imaging/ossimImageChain.h";

class ossimMapProjectionInfo : public ossimObject
{
        public:

                ossimMapProjectionInfo(const ossimMapProjection* proj,
                                const ossimDrect& output_rect);

                virtual ~ossimMapProjectionInfo();

                bool errorStatus() const;

                void getGeom(ossimKeywordlist& kwl, const char* prefix=0)const;

                ossimDpt getMetersPerPixel() const;

                ossimDpt getUsSurveyFeetPerPixel() const;

                ossimDpt getDecimalDegreesPerPixel() const;

                ossimDpt ulEastingNorthingPt() const;
                ossimDpt urEastingNorthingPt() const;
                ossimDpt lrEastingNorthingPt() const;
                ossimDpt llEastingNorthingPt() const;
                
                ossimDpt ulEastingNorthingPtInFt() const;
                ossimDpt urEastingNorthingPtInFt() const;
                ossimDpt lrEastingNorthingPtInFt() const;
                ossimDpt llEastingNorthingPtInFt() const;

                ossimGpt ulGroundPt() const;
                ossimGpt urGroundPt() const;
                ossimGpt lrGroundPt() const;
                ossimGpt llGroundPt() const;

                ossimGpt centerGroundPt() const;

                ossimDpt centerEastingNorthingPt() const;

                ossim_int32 linesPerImage() const;
                ossim_int32 pixelsPerLine() const;

                std::ostream& print(std::ostream& os) const;

                void setPixelType (ossimPixelType type);
                ossimPixelType  getPixelType () const;

                void setOutputFeetFlag (bool flag);

                bool unitsInFeet() const;

                ossimString getImageInfoString () const;
                void setImageInfoString (const ossimString& string);

                const ossimMapProjection* getProjection() const;

                static const char* README_IMAGE_STRING_KW;
                static const char* PIXEL_TYPE_KW;
                static const char* OUTPUT_US_FT_INFO_KW;

                virtual bool loadState(const ossimKeywordlist& kwl,
                                const char* prefix = 0);
                virtual bool saveState(ossimKeywordlist& kwl,
                                const char* prefix = 0) const;

        private:

                // Do not permit construction with void args.
                ossimMapProjectionInfo();
                ossimMapProjectionInfo& operator=(const ossimMapProjectionInfo&);

                void initializeMembers (const ossimDrect& output_rect);

                const ossimMapProjection* theProjection;
                mutable bool              theErrorStatus;
                int                       theLinesPerImage;
                int                       thePixelsPerLine;
                ossimGpt                  theCornerGroundPt[4];
                ossimDpt                  theCornerEastingNorthingPt[4];
                ossimGpt                  theCenterGroundPt;
                ossimDpt                  theCenterEastingNorthingPt;
                ossimDrect                theBoundingRect;

                ossimPixelType                 thePixelType;

                bool                      theOutputInfoInFeetFlag;

                ossimString               theImageInfoString;
};
