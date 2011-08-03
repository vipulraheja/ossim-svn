/*-----------------------------------------------------------------------------
 * Filename        : ossimHistogramEqualization.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimHistogramEqualization
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/imaging/ossimImageSourceHistogramFilter.h>
#include <ossim/imaging/ossimHistogramEqualization.h>

#include <vector>

%}

/* Handling the vector<ossim_uint32> */
%include "std_vector.i"
namespace std
{
        %template(vectorossimUInt32) vector<ossim_uint32>;
};

/* Handling the reserved function print */
%rename(ossimHistogramEqualization_print) ossimHistogramEqualization::print;


/* Wrapping the class ossimHistogramEqualization */
class ossimHistogramEqualization : public ossimImageSourceHistogramFilter
{
        public:
                ossimHistogramEqualization();
                ossimHistogramEqualization(ossimImageSource* inputSource,
                                ossimRefPtr<ossimMultiResLevelHistogram> histogram);
                ossimHistogramEqualization(ossimImageSource* inputSource,
                                ossimRefPtr<ossimMultiResLevelHistogram> histogram,
                                bool inverseFlag);
                virtual ossimRefPtr<ossimImageData> getTile(const ossimIrect& tileRect,
                                ossim_uint32 resLevel=0);

                virtual void setHistogram(ossimRefPtr<ossimMultiResLevelHistogram> histogram);
                virtual bool setHistogram(const ossimFilename& filename);

                virtual bool getInverseFlag()const;
                virtual void initialize();
                virtual void setInverseFlag(bool inverseFlag);

                virtual bool loadState(const ossimKeywordlist& kwl,
                                const char* prefix=NULL);
                virtual bool saveState(ossimKeywordlist& kwl,
                                const char* prefix=NULL)const;

                virtual std::ostream& print(std::ostream& out) const;


        protected:
                virtual ~ossimHistogramEqualization();

                void allocate();

                ossimRefPtr<ossimImageData> theTile;
                ossimRefPtr<ossimMultiResLevelHistogram> theAccumulationHistogram;

                bool theInverseFlag;
                vector<double*> theForwardLut;

                vector<double*> theInverseLut;


                std::vector<ossim_uint32> theBandList;
                virtual void computeAccumulationHistogram();

                template<class T>
                        ossimRefPtr<ossimImageData> runEqualizationAlgorithm(T dummyVariable,
                                        ossimRefPtr<ossimImageData> tile);

                virtual void initializeLuts();
                virtual void deleteLuts();
                
                /* Ignored due to unclean parsing of MACROS     */
                /* TYPE_DATA                                    */
};
