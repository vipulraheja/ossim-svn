/*-----------------------------------------------------------------------------
 * Filename        : ossimHistogramThreshholdFilter.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimHistogramThreshholdFilter
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/imaging/ossimImageSourceHistogramFilter.h>
#include <ossim/imaging/ossimHistogramThreshholdFilter.h>

%}

class ossimHistogramThreshholdFilter : public ossimImageSourceHistogramFilter
{
        public:
                ossimHistogramThreshholdFilter();
                ossimHistogramThreshholdFilter(double minValuePercent,
                                double maxValuePercent,
                                ossimImageSource* inputSource,
                                ossimMultiResLevelHistogram* histogram);
                virtual ossimRefPtr<ossimImageData> getTile(const ossimIrect& tileRect,
                                ossim_uint32 resLevel=0);

                virtual void setMinValuePercent(double minValue);
                virtual void setMaxValuePercent(double maxValue);

                virtual double getMinValuePercent()const;
                virtual double getMaxValuePercent()const;

                virtual void initialize();
                virtual bool loadState(const ossimKeywordlist& kwl,
                                const char* prefix=0);
                virtual bool saveState(ossimKeywordlist& kwl,
                                const char* prefix=0)const;

        protected:
                virtual ~ossimHistogramThreshholdFilter();

                double theMinValuePercent;
                double theMaxValuePercent;
                template <class T>
                        ossimRefPtr<ossimImageData> runThreshholdStretchAlgorithm(
                                        T dummyVariable,
                                        ossimRefPtr<ossimImageData>& tile);

                TYPE_DATA
};
