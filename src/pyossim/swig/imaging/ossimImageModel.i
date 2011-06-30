/*-----------------------------------------------------------------------------
Filename        : ossimImageModel.i
Author          : Vipul Raheja
License         : See top level LICENSE.txt file.
Description     : Contains SWIG-Python of class ossimImageModel 
-----------------------------------------------------------------------------*/

%module pyossim

%{

#include <vector>
#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimObject.h>
#include <ossim/base/ossimDpt.h>
#include <ossim/base/ossimRtti.h>
#include <ossim/imaging/ossimImageModel.h>

%}
        
%import "ossim/base/ossimDrect";
%import "ossim/imaging/ossimImageHandler";

/**
 * @brief Class to handle transforming image points, rectangles, and offsets
 * from one reduced resolution data set (rrds) level to another.
 *
 * Derived from ossimObject only so users can pass via the
 * ossimViewInterface::setView method.
 */
class ossimImageModel : public ossimObject
{
        public:
                ossimImageModel();

                virtual void initialize(const ossimImageHandler& ih);

                void rnToR0(ossim_uint32 rrds,
                                const ossimDpt& rnPt,
                                ossimDpt& r0Pt) const;
                void rnToR0(const ossimDpt& rnPt, ossimDpt& r0Pt) const;
                void r0ToRn(ossim_uint32 rrds,
                                const ossimDpt& r0Pt,
                                ossimDpt& rnPt) const;
                void r0ToRn(const ossimDpt& r0Pt,
                                ossimDpt& rnPt) const;

                void getSubImageOffset(ossim_uint32 rrds, ossimDpt& offset) const;

                void getImageRectangle(ossim_uint32 rrds, ossimDrect& rect) const; 

                void getBoundingRectangle(ossim_uint32 rrds, ossimDrect& rect) const;

                ossim_uint32 getNumberOfDecimationLevels()const;

                void setTargetRrds(ossim_uint32 rrds);

                ossim_uint32 getTargetRrds() const;


        protected:
                /** @brief virtual destructor */
                virtual ~ossimImageModel();

                /** Offset from the full image. */
                ossimDpt theSubImageOffset;

                /** Decimation factors for each rrds level. */
                std::vector<ossimDpt> theDecimationFactors;

                ossim_uint32 theLines;
                ossim_uint32 theSamples;
                ossim_uint32 theTargetRrds;

                TYPE_DATA
};
