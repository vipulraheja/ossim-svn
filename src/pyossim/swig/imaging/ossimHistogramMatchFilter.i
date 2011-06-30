/*-----------------------------------------------------------------------------
 * Filename        : ossimHistogramMatchFilter.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimHistogramMatchFilter
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/imaging/ossimImageSourceFilter.h>
#include <ossim/imaging/ossimHistogramEqualization.h>
#include <ossim/imaging/ossimHistogramMatchFilter.h>

%}

/**
 * class ossimHistogramMatchFilter
 *
 * <pre>
 *
 * This class owns two ossimHistogramEqualization filters and will chain them together.  It will
 * make the left most filter the forward transform by transforming the input input to an equalized
 * space defined by the input histogram.  The right filter is the target histogram to match.  It will
 * take the equalized space and invert it to a target histogram.
 *
 * There is an auto load input histogram flag that if set true will always try to search for an input handler
 * and get the input handlers histogram file. and set it.  If this is enabled then the only other field that
 * is required is to specify the target histogram.  If a target histogram is not specified then the output
 *
 * will be an equalized image without the target applied.
 *
 * </pre>
 */ 
class ossimHistogramMatchFilter : public ossimImageSourceFilter
{
        public:
                ossimHistogramMatchFilter();

                virtual ossimRefPtr<ossimImageData> getTile(const ossimIrect& tileRect,
                                ossim_uint32 resLevel=0);
                virtual void initialize();

                void setInputHistogram(const ossimFilename& inputHistogram);

                void setTargetHistogram(const ossimFilename& targetHistogram);

                virtual void connectInputEvent(ossimConnectionEvent& event);
                virtual void disconnectInputEvent(ossimConnectionEvent& event);

                virtual void setProperty(ossimRefPtr<ossimProperty> property);

                virtual ossimRefPtr<ossimProperty> getProperty(const ossimString& name)const;

                virtual void getPropertyNames(std::vector<ossimString>& propertyNames)const;

                virtual bool loadState(const ossimKeywordlist& kwl,
                                const char* prefix=NULL);

                virtual bool saveState(ossimKeywordlist& kwl,
                                const char* prefix=NULL)const;

        protected:
                void autoLoadInputHistogram();

                ossimRefPtr<ossimHistogramEqualization> theInputHistogramEqualizer;
                ossimRefPtr<ossimHistogramEqualization> theTargetHistogramEqualizer;
                ossimFilename theInputHistogramFilename;
                ossimFilename theTargetHistogramFilename;

                bool          theAutoLoadInputHistogramFlag;

                TYPE_DATA   
};
