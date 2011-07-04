/*-----------------------------------------------------------------------------
 * Filename        : ossimImageViewTransform.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimImageViewTransform
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <iostream>

#include <ossim/base/ossimViewInterface.h>
#include <ossim/base/ossimObject.h>
#include <ossim/base/ossimDpt.h>
#include <ossim/base/ossimDrect.h>
#include <ossim/base/ossim2dTo2dTransform.h>
#include <ossim/projection/ossimImageViewTransform.h>

%}

class ossimImageViewTransform : public ossim2dTo2dTransform,
        public ossimViewInterface
{
        public:
                friend OSSIMDLLEXPORT ostream& operator<<(ostream& out,
                                const ossimImageViewTransform& data);

                ossimImageViewTransform();

                virtual void forward(const ossimDpt& input, ossimDpt& output) const;
                virtual void inverse(const ossimDpt& input, ossimDpt& output) const;

                virtual bool isIdentity()const=0;


                virtual bool isValid()const=0;
                virtual ossimDpt getInputMetersPerPixel()const=0;
                virtual ossimDpt getOutputMetersPerPixel()const=0;

                virtual void getImageToViewScale(ossimDpt& resultScale,
                                const ossimDpt& imagePoint,
                                const ossimDpt& deltaImagePointXY)const;

                virtual void getViewToImageScale(ossimDpt& resultScale,
                                const ossimDpt& imagePoint,
                                const ossimDpt& deltaImagePointXY)const;

                virtual void imageToView(const ossimDpt& imagePoint,
                                ossimDpt&       viewPoint)const;

                virtual void viewToImage(const ossimDpt& viewPoint,
                                ossimDpt&       imagePoint)const;

                virtual std::ostream& print(std::ostream& out) const;

                ossimDpt imageToView(const ossimDpt& imagePoint)const;

                ossimDpt viewToImage(const ossimDpt& viewPoint)const;

                virtual void getScaleChangeImageToView(ossimDpt& result,
                                const ossimDrect& imageRect);
                virtual void getScaleChangeViewToImage(ossimDpt& result,
                                const ossimDrect& viewRect);

                virtual void getRoundTripErrorView(ossimDpt& result,
                                const ossimDpt& viewPt)const;
                virtual void getRoundTripErrorImage(ossimDpt& result,
                                const ossimDpt& imagePt)const;
                virtual ossimDpt getRoundTripErrorView(const ossimDpt& viewPt)const;
                virtual ossimDpt getRoundTripErrorImage(const ossimDpt& imagePt)const;

                virtual ossimDrect getImageToViewBounds(const ossimDrect& imageRect)const;

                virtual bool loadState(const ossimKeywordlist& kwl,
                                const char* prefix =0);
                virtual bool saveState(ossimKeywordlist& kwl,
                                const char* prefix = 0)const;

                TYPE_DATA
};
