/*-----------------------------------------------------------------------------
 * Filename        : ossimHistoMatchRemapper.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimHistoMatchRemapper
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <vector>
#include <ossim/imaging/ossimImageSourceFilter.h>
#include <ossim/imaging/ossimHistoMatchRemapper.h>

%}

class ossimHistoMatchRemapper : public ossimImageSourceFilter
{
        public:
                ossimHistoMatchRemapper();
                ossimHistoMatchRemapper(ossimImageSource* inputSource,
                                const vector<double>& targetMeanPerBand  = vector<double>(),
                                const vector<double>& targetSigmaPerBand = vector<double>(),
                                const vector<double>& inputMeanPerBand   = vector<double>(),
                                const vector<double>& inputSigmaPerBand  = vector<double>()
                                );

                virtual ossimRefPtr<ossimImageData> getTile(const ossimIrect& tileRect,
                                ossim_uint32 resLevel=0);
                virtual void initialize();

                const vector<double>& getInputMeanValues()const;
                const vector<double>& getInputSigmaValues()const;
                const vector<double>& getTargetMeanValues()const;
                const vector<double>& getTargetSigmaValues()const;

                void setInputMeanValues(const vector<double>& newValues);
                void setInputSigmaValues(const vector<double>& newValues);
                void setTargetMeanValues(const vector<double>& newValues);
                void setTargetSigmaValues(const vector<double>& newValues);


                virtual bool loadState(const ossimKeywordlist& kwl,
                                const char* prefix=NULL);
                virtual bool saveState(ossimKeywordlist& kwl,
                                const char* prefix=NULL);

        protected:
                virtual ~ossimHistoMatchRemapper();

                ossimRefPtr<ossimImageData> theBlankTile;

                vector<double> theTargetMeanPerBand;
                vector<double> theTargetSigmaPerBand;
                vector<double> theInputMeanPerBand;
                vector<double> theInputSigmaPerBand;

                double transLean(double vIn,
                                double vBias,
                                double vTarget,
                                double vMin,
                                double vMax);

                double transLeanStretch(double vIn,
                                double vBias,
                                double vBiasStretch,
                                double vTarget,
                                double vTargetStretch,
                                double vMin,
                                double vMax);

};
