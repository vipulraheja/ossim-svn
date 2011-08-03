/*-----------------------------------------------------------------------------
Filename        : ossimHistogramRemapper.i
Author          : Vipul Raheja
License         : See top level LICENSE.txt file.
Description     : Contains SWIG-Python of class ossimHistogramRemapper 
-----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/imaging/ossimTableRemapper.h>
#include <ossim/imaging/ossimHistogramRemapper.h>
#include <ossim/base/ossimMultiResLevelHistogram.h>

%}


/* Include the required header files */
%import "ossim/base/ossimConstants.h";

/* Handling ossimHistogramRemapper assignment operator */
%rename(__set__) ossimHistogramRemapper::operator=;
%rename(__lshift__) operator<<;

/* Handling the reserved function print */
%rename(ossimHistogramRemapper_print) ossimHistogramRemapper::print;

/* Handling the vector<> */
%include "std_vector.i"
namespace std
{
        %template(vectorossimFloat64) vector<ossim_float64>;
        %template(vectorossimUInt32) vector<ossim_uint32>;
};


/* Wrapping the class ossimHistogramRemapper */
class ossimHistogramRemapper : public ossimTableRemapper
{
        public:
                enum StretchMode
                {
                        LINEAR_ONE_PIECE      = 0,
                        LINEAR_1STD_FROM_MEAN = 1,
                        LINEAR_2STD_FROM_MEAN = 2,
                        LINEAR_3STD_FROM_MEAN = 3,
                        LINEAR_AUTO_MIN_MAX   = 4,
                        STRETCH_UNKNOWN = 5 // Alway last as used for number of modes method.
                };

                /** default constructor */
                ossimHistogramRemapper();


                virtual ossimString getLongName()  const;
                virtual ossimString getShortName() const;

                virtual ossimRefPtr<ossimImageData> getTile(const ossimIrect& tile_rect,
                                ossim_uint32 resLevel=0);

                virtual void initialize();

                void reset();

                void setStretchMode(StretchMode mode, bool rebuildTableFlag=false);

                void setStretchModeAsString(const ossimString& mode,
                                bool rebuildTableFlag=false);

                StretchMode   getStretchMode() const;

                ossimString getStretchModeString() const;

                ossim_uint32 getNumberOfStretchModes() const;

                ossimString getStretchModeString(ossim_uint32 index) const;

                void setLowNormalizedClipPoint(const ossim_float64& clip);

                void setLowNormalizedClipPoint(const ossim_float64& clip,
                                ossim_uint32 zero_based_band);

                void setHighNormalizedClipPoint(const ossim_float64& clip);

                void setHighNormalizedClipPoint(const ossim_float64& clip,
                                ossim_uint32 zero_based_band);
                void setLowClipPoint(const ossim_float64& clip);

                void setLowClipPoint(const ossim_float64& clip,
                                ossim_uint32 zero_based_band);

                void setHighClipPoint(const ossim_float64& clip);

                void setHighClipPoint(const ossim_float64& clip,
                                ossim_uint32 zero_based_band);

                void setMidPoint(const ossim_float64& value);

                void setMidPoint(const ossim_float64& value,
                                ossim_uint32 zero_based_band);

                void setMinOutputValue(const ossim_float64& value);

                void setMinOutputValue(const ossim_float64& value,
                                ossim_uint32 zero_based_band);

                void setMaxOutputValue(const ossim_float64& value);

                void setMaxOutputValue(const ossim_float64& value,
                                ossim_uint32 zero_based_band);

                ossim_float64 getLowNormalizedClipPoint(ossim_uint32 zero_based_band) const;

                ossim_float64 getLowNormalizedClipPoint() const;

                ossim_float64 getHighNormalizedClipPoint(ossim_uint32 zero_based_band) const;
                ossim_float64 getHighNormalizedClipPoint() const;

                ossim_float64 getLowClipPoint(ossim_uint32 zero_based_band) const;

                ossim_float64 getLowClipPoint() const;

                ossim_float64 getHighClipPoint(ossim_uint32 zero_based_band) const;

                ossim_float64 getHighClipPoint() const;

                ossim_float64 getMidPoint(ossim_uint32 zero_based_band) const;

                ossim_float64 getMidPoint() const;

                ossim_float64 getMinOutputValue(ossim_uint32 zero_based_band) const;

                ossim_float64 getMinOutputValue() const;

                ossim_float64 getMaxOutputValue(ossim_uint32 zero_based_band) const;

                ossim_float64 getMaxOutputValue() const;

                void setHistogram(ossimRefPtr<ossimMultiResLevelHistogram> histogram);

                ossimRefPtr<ossimHistogram> getHistogram(ossim_uint32 zero_based_band,
                                ossim_uint32 res_level=0) const;

                bool openHistogram(const ossimFilename& histogram_file);

                ossimFilename getHistogramFile() const;

                virtual bool saveState(ossimKeywordlist& kwl,
                                const char* prefix=0)const;

                void buildTable();
                virtual bool loadState(const ossimKeywordlist& kwl,
                                const char* prefix=0);


                virtual ostream& print(ostream& os) const;

                friend ostream& operator <<(ostream& os, const ossimHistogramRemapper& hr);
                virtual double getMinPixelValue(ossim_uint32 band=0)const;

                virtual double getMaxPixelValue(ossim_uint32 band=0)const;

                bool canConnectMyInputTo(ossim_int32 inputIndex,
                                const ossimConnectableObject* object)const;


        protected:
                /** virtual destructor */
                virtual ~ossimHistogramRemapper();

        private:
                // Do not allow copy constructor, operator=.
                ossimHistogramRemapper(const ossimHistogramRemapper& hr);
                ossimHistogramRemapper& operator=(const ossimHistogramRemapper& hr);

                void buildLinearTable();
                void buildAutoLinearMinMaxTable();
                template <class T> void buildLinearTable(T dummy);
                template <class T> void buildAutoLinearMinMaxTableTemplate(T dummy);

                void buildLinearTableStdFromMean();

                void initializeClips();

                void initializeClips(ossim_uint32 bands);

                void setNullCount();

                void setupTable();

                void verifyEnabled();

                ossim_uint32 getHistogramBand(ossim_uint32 input_band) const;

                void setBypassFlag(bool flag);


                StretchMode                   theStretchMode;
                bool                          theDirtyFlag;
                mutable ossimRefPtr<ossimMultiResLevelHistogram>  theHistogram;
                vector<ossim_float64>         theNormalizedLowClipPoint;
                vector<ossim_float64>         theNormalizedHighClipPoint;
                vector<ossim_float64>         theMidPoint;
                vector<ossim_float64>         theMinOutputValue;
                vector<ossim_float64>         theMaxOutputValue;

                vector<ossim_uint32>          theBandList;

                bool theBypassFlag;
                
                /* Ignored due to unclean parsing of MACROS     */
                /* TYPE_DATA                                    */
};
