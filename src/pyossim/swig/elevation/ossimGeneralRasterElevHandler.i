/*-----------------------------------------------------------------------------
 * Filename        : ossimGeneralRasterElevHandler.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimGeneralRasterElevHandler
 * -----------------------------------------------------------------------------*/

%module pyossim

%{
        
#include <list>
#include <ossim/base/ossimIoStream.h>
#include <ossim/base/ossimString.h>
#include <ossim/base/ossimDatum.h>
#include <ossim/elevation/ossimElevCellHandler.h>
#include <ossim/elevation/ossimGeneralRasterElevHandler.h>
#include <ossim/imaging/ossimGeneralRasterInfo.h>
#include <ossim/imaging/ossimImageHandlerRegistry.h>
#include <ossim/imaging/ossimImageHandler.h>
#include <ossim/imaging/ossimImageSource.h>
#include <ossim/imaging/ossimImageGeometry.h>
#include <ossim/projection/ossimProjectionFactoryRegistry.h>
#include <ossim/projection/ossimMapProjection.h>
#include <ossim/projection/ossimImageViewTransform.h>
#include <ossim/base/ossimKeywordlist.h>
#include <ossim/base/ossimDpt.h>
#include <ossim/base/ossimGpt.h>
#include <OpenThreads/Mutex>
#include <OpenThreads/ScopedLock>

%}

/* Handling operators */
%rename(__set__) ossimGeneralRasterElevHandler::operator=;

/* Wrapping class ossimGeneralRasterElevHandler */
class ossimGeneralRasterElevHandler : public ossimElevCellHandler
{
        public:
                class GeneralRasterInfo
                {
                        public:
                                GeneralRasterInfo()
                                        :theWidth(0),
                                        theHeight(0),
                                        theNullHeightValue(ossim::nan()),
                                        theScalarType(OSSIM_SCALAR_UNKNOWN),
                                        theBytesPerRawLine(0),
                                        theDatum(0),
                                        theGeometry(0)
                        {
                        }
                                GeneralRasterInfo(const  ossimGeneralRasterElevHandler::GeneralRasterInfo& src)
                                        :theFilename(src.theFilename),
                                        theImageRect(src.theImageRect),
                                        theUl(src.theUl),
                                        theLr(src.theLr),
                                        theWidth(src.theWidth),
                                        theHeight(src.theHeight),
                                        theWgs84GroundRect(src.theWgs84GroundRect),
                                        theNullHeightValue(src.theNullHeightValue),
                                        theByteOrder(src.theByteOrder),
                                        theScalarType(src.theScalarType),
                                        theBytesPerRawLine(src.theBytesPerRawLine),
                                        theDatum(src.theDatum),
                                        theGeometry(src.theGeometry)
                        {
                        }
                                ossimFilename     theFilename;
                                ossimIrect        theImageRect;
                                ossimIpt          theUl;
                                ossimIpt          theLr;
                                ossim_uint32      theWidth;
                                ossim_uint32      theHeight;
                                ossimDrect        theWgs84GroundRect;
                                ossim_float64     theNullHeightValue;
                                ossimByteOrder    theByteOrder;
                                ossimScalarType   theScalarType;
                                ossim_uint32      theBytesPerRawLine;
                                const ossimDatum* theDatum;
                                ossimRefPtr<ossimImageGeometry> theGeometry;  //add by simbla
                };
                ossimGeneralRasterElevHandler(const ossimFilename& file="");
                ossimGeneralRasterElevHandler(const ossimGeneralRasterElevHandler::GeneralRasterInfo& generalRasterInfo);
                ossimGeneralRasterElevHandler(const ossimGeneralRasterElevHandler& rhs);
                const ossimGeneralRasterElevHandler& operator=(const ossimGeneralRasterElevHandler& rhs);

                virtual ~ossimGeneralRasterElevHandler();

                virtual ossimObject* dup()const;

                virtual double getHeightAboveMSL(const ossimGpt&);

                virtual ossimIpt getSizeOfElevCell() const;

                virtual double getPostValue(const ossimIpt& gridPt) const;

                virtual bool isOpen()const;

                bool open(const ossimFilename& file, bool memoryMapFlag=false);

                virtual void close();

                ossimDrect getBoundingRect()const;

                virtual bool pointHasCoverage(const ossimGpt& gpt) const;

                const ossimGeneralRasterElevHandler::GeneralRasterInfo& generalRasterInfo()const;

        private:
                template <class T>
                        double getHeightAboveMSLFileTemplate(T dummy,
                                        const ossimGeneralRasterElevHandler::GeneralRasterInfo& info,
                                        const ossimGpt& gpt);
                template <class T>
                        double getHeightAboveMSLMemoryTemplate(T dummy,
                                        const ossimGeneralRasterElevHandler::GeneralRasterInfo& info,
                                        const ossimGpt& gpt);

                virtual bool setFilename(const ossimFilename& file);

                ossimGeneralRasterElevHandler::GeneralRasterInfo theGeneralRasterInfo;
                mutable OpenThreads::Mutex m_inputStreamMutex;
                std::ifstream m_inputStream;

                /** @brief true if stream is open. */
                bool          m_streamOpen;

                std::vector<char> m_memoryMap;

                /* Ignoring Macro
                TYPE_DATA */
};
