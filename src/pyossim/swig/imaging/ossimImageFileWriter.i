/*-----------------------------------------------------------------------------
 * Filename        : ossimImageData.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimImageData 
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <fstream>
#include <ossim/base/ossimIoStream.h>
#include <ossim/imaging/ossimImageWriter.h>
#include <ossim/base/ossimFilename.h>
#include <ossim/base/ossimConnectableObjectListener.h>
#include <ossim/base/ossimProcessInterface.h>
#include <ossim/base/ossimObjectEvents.h>
#include <ossim/base/ossimProcessProgressEvent.h>
#include <ossim/base/ossimViewController.h>
#include <ossim/imaging/ossimImageFileWriter.h>

%}

/**
 * Pure virtual base class for image file writers.
 *
 * There is normally one subclass of this class for each format supported
 * for writing.  This class roughly corresponds to the ImageHandler class
 * used for reading images.  Format specific ossimImageWriter's are normally
 * instantiated by the ossimImageWriterFactory::createWriterInstance() method.
 * ossimImageWriters should not be directly instantiated by application code.
 */
class ossimImageFileWriter : public ossimImageWriter,
        public ossimProcessInterface,
        public ossimConnectableObjectListener
{
        public:

                ossimImageFileWriter(const ossimFilename& filename = ossimFilename(),
                                ossimImageSource* inputSource=0,
                                ossimObject* owner=0);

                virtual ~ossimImageFileWriter();

                virtual ossimObject* getObject();
                virtual const ossimObject* getObject() const;

                virtual void getImageTypeList(std::vector<ossimString>& imageTypeList)const=0;

                virtual ossimString getExtension() const;

                virtual bool getOutputHasInternalOverviews( void ) const;

                virtual bool hasImageType(const ossimString& imageType) const;

                virtual void setTileSize(const ossimIpt& tileSize);

                virtual bool writeEnviHeaderFile() ;

                virtual bool writeErsHeaderFile() ;

                virtual bool writeExternalGeometryFile() ;

                virtual bool writeFgdcFile() ;

                virtual bool writeHistogramFile() ;

                virtual bool writeJpegWorldFile() ;

                virtual bool writeOverviewFile(ossim_uint16 tiff_compress_type = 1,
                                ossim_int32 jpeg_compress_quality = 75,
                                bool includeR0 = false );

                virtual bool writeReadmeFile() ;

                virtual bool writeTiffWorldFile() ;

                virtual bool writeWorldFile() ;

                virtual bool writeMetaDataFiles() ;

                virtual void setAreaOfInterest(const ossimIrect& inputRect);

                virtual void changeSequencer(ossimImageSourceSequencer* sequencer);

                virtual ossimImageSourceSequencer* getSequencer();

                virtual void initialize();

                virtual bool execute();

                virtual bool writeStream();

                virtual bool setOutputStream(ossimRefPtr<ossimOStream> stream);

                /** tmp drb */
                virtual bool setOutputStream(std::ostream& str);

                virtual ossimRefPtr<ossimOStream> getOutputStream() const;

                virtual void setPercentComplete(double percentComplete);

                virtual void  setOutputImageType(ossim_int32 type);
                virtual void  setOutputImageType(const ossimString& type);
                virtual ossim_int32 getOutputImageType() const;
                virtual ossimString getOutputImageTypeString() const;

                virtual void setOutputName(const ossimString& outputName);

                virtual void setFilename(const ossimFilename& file);

                virtual const ossimFilename& getFilename()const;

                virtual bool saveState(ossimKeywordlist& kwl,
                                const char* prefix=0)const;

                virtual bool loadState(const ossimKeywordlist& kwl,
                                const char* prefix=0);


                virtual bool canConnectMyInputTo(ossim_int32 inputIndex,
                                const ossimConnectableObject* object)const;

                virtual void disconnectInputEvent(ossimConnectionEvent& event);
                virtual void connectInputEvent(ossimConnectionEvent& event);
                virtual void propertyEvent(ossimPropertyEvent& event);

                /**
                 * Control flags...
                 */

                virtual bool         getWriteImageFlag()            const;
                virtual bool         getWriteHistogramFlag()        const;
                virtual bool         getWriteOverviewFlag()         const;
                virtual bool         getScaleToEightBitFlag()       const;

                virtual bool         getWriteEnviHeaderFlag()       const;
                virtual bool         getWriteErsHeaderFlag()        const;   
                virtual bool         getWriteExternalGeometryFlag() const;
                virtual bool         getWriteFgdcFlag()             const;
                virtual bool         getWriteJpegWorldFileFlag()    const;
                virtual bool         getWriteReadmeFlag()           const;
                virtual bool         getWriteTiffWorldFileFlag()    const;
                virtual bool         getWriteWorldFileFlag()        const;

                virtual void         setWriteImageFlag(bool flag);
                virtual void         setWriteOverviewFlag(bool flag);
                virtual void         setWriteHistogramFlag(bool flag);
                virtual void         setScaleToEightBitFlag(bool flag);

                virtual void         setWriteEnviHeaderFlag(bool flag);
                virtual void         setWriteErsHeaderFlag(bool flag); 
                virtual void         setWriteExternalGeometryFlag(bool flag);
                virtual void         setWriteFgdcFlag(bool flag);
                virtual void         setWriteJpegWorldFile(bool flag);
                virtual void         setWriteReadme(bool flag);
                virtual void         setWriteTiffWorldFile(bool flag);
                virtual void         setWriteWorldFile(bool flag);

                virtual ossim_uint16 getOverviewCompressType() const;
                virtual ossim_int32  getOverviewJpegCompressQuality() const;

                virtual void         setOverviewCompressType(ossim_uint16 type);
                virtual void         setOverviewJpegCompressQuality(ossim_int32 quality);


                virtual void setProperty(ossimRefPtr<ossimProperty> property);
                virtual ossimRefPtr<ossimProperty> getProperty(const ossimString& name)const;
                virtual void getPropertyNames(std::vector<ossimString>& propertyNames)const;

                virtual bool addListener(ossimListener* listener);

                virtual bool removeListener(ossimListener* listener);

                virtual void setPixelType(ossimPixelType type);

                virtual void setPixelType(const ossimString& type);

                virtual ossimPixelType getPixelType() const;

                virtual void getPixelTypeString(ossimString& type) const;

        protected:

                bool writeWorldFile(const ossimFilename& file);

                virtual bool writeFile() = 0;

                ossimRefPtr<ossimImageSourceSequencer> theInputConnection;
                ossimRefPtr<ossimViewController>       theViewController;
                ossimListener*             theProgressListener;
                ossimFilename              theFilename;
                ossimString                theOutputImageType;
                bool                       theWriteImageFlag;
                bool                       theWriteOverviewFlag;
                bool                       theWriteHistogramFlag;
                bool                       theScaleToEightBitFlag;
                ossim_uint16               theOverviewCompressType;
                ossim_int32                theOverviewJpegCompressQuality;

                /**
                 * External meta data writer flags.  Not really part of an image writer, put
                 * here for convenience.  If true the writer will do the connection work
                 * for you.
                 */
                bool                       theWriteEnviHeaderFlag;
                bool                       theWriteErsHeaderFlag; 
                bool                       theWriteExternalGeometryFlag;
                bool                       theWriteFgdcFlag;
                bool                       theWriteJpegWorldFileFlag;
                bool                       theWriteReadmeFlag;
                bool                       theWriteTiffWorldFileFlag;
                bool                       theWriteWorldFileFlag;


                ossimUnitType              theLinearUnits;

                /** OSSIM_PIXEL_IS_POINT = 0, OSSIM_PIXEL_IS_AREA  = 1 */
                ossimPixelType             thePixelType;

                TYPE_DATA
};
