/*-----------------------------------------------------------------------------
Filename        : ossimImageHandler.i
Author          : Vipul Raheja
License         : See top level LICENSE.txt file.
Description     : Contains SWIG-Python of class ossimImageHandler 
-----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/imaging/ossimImageSource.h>
#include <ossim/imaging/ossimImageMetaData.h>
#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimNBandLutDataObject.h>
#include <ossim/base/ossimIrect.h>
#include <ossim/base/ossimFilename.h>
#include <ossim/base/ossimRefPtr.h>
#include <ossim/imaging/ossimFilterResampler.h>
#include <ossim/imaging/ossimImageHandler.h>

#include <vector>

%}

/* Include the required header files */
%import "ossim/base/ossimConstants.h"

/* Handling the std::exception */
%include "exception.i"
%exception
{
        try
        {
                $action
        }
        catch(const std::exception& e)
        {
                SWIG_exception(SWIG_RuntimeError, e.what());
        }
}

/* Handling the vectors */
%include "std_vector.i"
namespace std
{
        %template(vectorossimIpt) vector<ossimIpt>;
        %template(vectorossimDpt) vector<ossimDpt>;
        %template(vectorossimUInt32) vector<ossim_uint32>;
        %template(vectorossimString) vector<ossimString>;
};


/**
 *  This class defines an abstract Handler which all image handlers(loaders)
 *  should derive from.
 */
class ossimImageHandler : public ossimImageSource
{
        public:

                enum ossimImageHandlerOverviewCompressionType
                {
                        OSSIM_OVERVIEW_COMPRESSION_NONE= 0,
                        OSSIM_OVERVIEW_COMPRESSION_JPEG,
                        OSSIM_OVERVIEW_COMPRESSION_LZW,
                        OSSIM_OVERVIEW_COMPRESSION_DEFLATE,
                        OSSIM_OVERVIEW_COMPRESSION_PACKBITS
                };

                ossimImageHandler();

                virtual ~ossimImageHandler();

                virtual void initialize();
                
                virtual bool openOverview();
                virtual bool openOverview(const ossimFilename& overview_file);
                virtual void closeOverview();

                virtual const ossimImageHandler* getOverview() const;

                virtual bool hasOverviews() const;

                virtual ossimFilename createDefaultOverviewFilename() const;
                virtual ossimFilename createDefaultGeometryFilename() const;
                virtual ossimFilename createDefaultMetadataFilename() const;
                virtual ossimFilename createDefaultHistogramFilename() const;
                virtual ossimFilename createDefaultValidVerticesFilename() const;

                virtual bool writeValidImageVertices(const std::vector<ossimIpt>& vertices, 
                                const ossimFilename& file=ossimFilename(""));

                virtual bool openValidVertices(const ossimFilename& vertices_file);
                virtual bool openValidVertices();

                virtual bool open() = 0;
                virtual bool open(const ossimFilename& imageFile,
                                ossim_uint32 entryIndex);
                virtual bool open(const ossimFilename& imageFile);

                virtual void close();

                virtual bool isOpen()const=0;

                virtual bool buildHistogram(int numberOfRLevels=0);
                virtual bool buildAllHistograms(int numberOfRLevels=0);

                virtual bool buildOverview(ossimImageHandlerOverviewCompressionType compressionType = OSSIM_OVERVIEW_COMPRESSION_NONE,
                                ossim_uint32 quality = 75,
                                ossimFilterResampler::ossimFilterResamplerType resampleType = ossimFilterResampler::ossimFilterResampler_BOX,
                                bool includeFullResFlag=false);

                virtual bool buildAllOverviews(ossimImageHandlerOverviewCompressionType compressionType = OSSIM_OVERVIEW_COMPRESSION_NONE,
                                ossim_uint32 quality = 75,
                                ossimFilterResampler::ossimFilterResamplerType resampleType = ossimFilterResampler::ossimFilterResampler_BOX,
                                bool includeFullResFlag=false);

                virtual bool buildOverview(const ossimFilename& filename,
                                ossimImageHandlerOverviewCompressionType compressionType = OSSIM_OVERVIEW_COMPRESSION_NONE,
                                ossim_uint32 quality = 75,
                                ossimFilterResampler::ossimFilterResamplerType resampleType = ossimFilterResampler::ossimFilterResampler_BOX,
                                bool includeFullResFlag=false);

                virtual ossimRefPtr<ossimImageGeometry> getImageGeometry();

                virtual void setImageGeometry(ossimImageGeometry* geom);

                virtual void saveImageGeometry() const;

                virtual void saveImageGeometry(const ossimFilename& geometry_file) const;   

                virtual ossim_uint32 getNumberOfLines(ossim_uint32 resLevel = 0) const = 0;
                virtual ossim_uint32 getNumberOfSamples(ossim_uint32 resLevel = 0) const = 0;

                virtual ossimIrect getImageRectangle(ossim_uint32 resLevel = 0) const; 
                virtual ossimIrect getBoundingRect(ossim_uint32 resLevel = 0) const;

                virtual void getDecimationFactor(ossim_uint32 resLevel, ossimDpt& result) const;
                virtual void getDecimationFactors(vector<ossimDpt>& decimations) const;

                virtual ossim_uint32 getNumberOfDecimationLevels() const;
                virtual ossim_uint32 getNumberOfReducedResSets()const;

                virtual void setFilename(const ossimFilename& filename);
                virtual const ossimFilename& getFilename()const;

                virtual bool saveState(ossimKeywordlist& kwl,
                                const char* prefix=0)const;
                virtual bool loadState(const ossimKeywordlist& kwl,
                                const char* prefix=0);

                virtual bool isValidRLevel(ossim_uint32 resLevel) const;

                bool canConnectMyInputTo(ossim_int32 inputIndex,
                                const ossimConnectableObject* object) const;

                virtual void getValidImageVertices(vector<ossimIpt>& validVertices,
                                ossimVertexOrdering ordering=OSSIM_CLOCKWISE_ORDER,
                                ossim_uint32 resLevel=0)const;

                virtual bool isBandSelector() const;

                virtual bool setOutputBandList(const std::vector<ossim_uint32>& band_list);

                virtual bool isImageTiled() const;

                virtual ossim_uint32 getImageTileWidth() const = 0;
                virtual ossim_uint32 getImageTileHeight() const = 0;

                virtual bool hasMetaData() const;

                virtual ossimRefPtr<ossimNBandLutDataObject> getLut()const;

                virtual bool hasLut() const;

                virtual void loadMetaData();

                virtual double getMinPixelValue(ossim_uint32 band=0)const;
                virtual double getMaxPixelValue(ossim_uint32 band=0)const;
                virtual double getNullPixelValue(ossim_uint32 band=0)const;

                virtual void setMinPixelValue(ossim_uint32 band, const ossim_float64& pix);
                virtual void setMaxPixelValue(ossim_uint32 band, const ossim_float64& pix);
                virtual void setNullPixelValue(ossim_uint32 band, const ossim_float64& pix);

                virtual ossim_uint32 getCurrentEntry()const;
                virtual ossim_uint32 getNumberOfEntries()const;

                virtual void getEntryList(std::vector<ossim_uint32>& entryList) const;
                virtual void getEntryStringList(
                                std::vector<ossimString>& entryStringList) const;

                ossimFilename getOverviewFile()const;

                virtual bool setCurrentEntry(ossim_uint32 entryIdx);

                virtual void setProperty(ossimRefPtr<ossimProperty> property);
                virtual ossimRefPtr<ossimProperty> getProperty(const ossimString& name)const;
                virtual void getPropertyNames(std::vector<ossimString>& propertyNames)const;

                ossimFilename getFilenameWithThisExtension(const ossimString& ext,
                                bool set_e0_prefix=false) const;

                ossim_uint32 getStartingResLevel() const;

                void setStartingResLevel(ossim_uint32 level);

                bool getOpenOverviewFlag() const;

                void setOpenOverviewFlag(bool flag);

                virtual void setSupplementaryDirectory(const ossimFilename& dir);

                virtual const ossimFilename& getSupplementaryDirectory()const;

                const ossimString& getImageID() const { return theImageID; }

                void setImageID(const ossimString&  id) { theImageID = id; }

        protected:

                virtual ossimRefPtr<ossimImageGeometry> getExternalImageGeometry() const;
                virtual ossimRefPtr<ossimImageGeometry> getInternalImageGeometry() const;

                virtual bool getOverviewTile(ossim_uint32 resLevel, ossimImageData* result);  

                bool initVertices(const char* file);

                virtual void completeOpen();

                void initImageParameters(ossimImageGeometry* geom) const;

                virtual void establishDecimationFactors();

                ossimFilename theImageFile;
                ossimFilename theOverviewFile;
                ossimFilename theSupplementaryDirectory;
      
                ossimRefPtr<ossimImageHandler> theOverview;
                
                vector<ossimIpt> theValidImageVertices;
                
                ossimImageMetaData theMetaData;
                
                mutable ossimRefPtr<ossimImageGeometry> theGeometry;
                
                ossimRefPtr<ossimNBandLutDataObject> theLut;
                
                std::vector<ossimDpt> theDecimationFactors;
                
                ossimString theImageID;

                ossim_uint32 theStartingResLevel; // 0 being full or highest res.

                bool theOpenOverviewFlag;

                //TYPE_DATA
};
