/*-----------------------------------------------------------------------------
Filename        : ossimGeneralRasterInfo.i
Author          : Vipul Raheja
License         : See top level LICENSE.txt file.
Description     : Contains SWIG-Python of class ossimGeneralRasterInfo
-----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/imaging/ossimGeneralRasterInfo.h>

#include <vector>

%}

/* Handling ossimGeneralRasterInfo assignment operator */
%rename(__set__) ossimGeneralRasterInfo::operator=;

/* Handling the reserved print function */
%rename(ossimGeneralRasterInfo_print) ossimGeneralRasterInfo::print;

/* Handling the std::vector for Python */
%include "std_vector.i"
namespace std
{
        %template(vectorOssimFileName) std::vector<ossimFilename>;
}

/* Wrapping the class ossimGeneralRasterInfo */
class ossimGeneralRasterInfo : public ossimObject,
        public ossimErrorStatusInterface
{
        public:

                enum ossimFillMode
                {
                        NONE,
                        ZEROES_TO_MIN,
                        ZEROES_TO_NULL_EDGES_ONLY
                };

                enum
                {
                        UNKNOWN = -1
                };

                ossimGeneralRasterInfo();

                ossimGeneralRasterInfo(const std::vector<ossimFilename>& imageFileList,
                                ossimScalarType      pixelType,
                                ossimInterleaveType  il_type,
                                ossim_uint32         numberOfBands,
                                ossim_uint32         lines,
                                ossim_uint32         samples,
                                ossim_uint32         headerSize,
                                ossimFillMode        nullsMode,
                                ossim_uint32         pixelsToChop);

                ossimGeneralRasterInfo(const ossimKeywordlist& kwl, const char* prefix=0);

                ~ossimGeneralRasterInfo ();

                ossimIrect imageRect()       const { return theImageRect;      }
                ossimIrect validImageRect()  const { return theValidImageRect; }
                ossimIrect rawImageRect()    const { return theRawImageRect;   }

                ossimIpt subImageOffset()  const { return theSubImageOffset; }

                ossim_uint32 headerSize()      const { return theHeaderSize;     }
                ossim_uint32 fillToNullsMode() const { return theSetNullsMode;   }

                void setFillToNullsMode(ossim_uint32 mode);

                void setMinPixelValue(ossim_uint32 band, double value)
                {
                        theMetaData.setMinPix(band, value);
                }
        
                double getMinPixelValue(ossim_uint32 band)const
                {
                        return theMetaData.getMinPix(band);
                }
                
                void setMaxPixelValue(ossim_uint32 band, double value)
                {
                        theMetaData.setMaxPix(band, value);
                }
                
                double getMaxPixelValue(ossim_uint32 band)const
                {
                        return theMetaData.getMaxPix(band);
                }
                
                void setNullPixelValue(ossim_uint32 band, double value)
                {
                        theMetaData.setNullPix(band, value);
                }
                
                double getNullPixelValue(ossim_uint32 band)const
                {
                        return theMetaData.getNullPix(band);
                }
                
                void setNumberOfBands(ossim_uint32 bands) { theMetaData.setNumberOfBands(bands); }

                ossim_uint32 pixelsToChop()   const { return thePixelsToChop;   } 
                ossim_uint32 numberOfBands()  const { return theMetaData.getNumberOfBands();  }

                ossimInterleaveType interleaveType() const { return theInterleaveType; }
                ossimScalarType getScalarType() const { return theMetaData.getScalarType(); }

                ossim_uint64 validLines()        const;
                ossim_uint64 rawLines()          const;
                ossim_uint64 bytesPerRawLine()   const;
                ossim_uint64 bytesPerValidLine() const;
                ossim_uint64 validSamples()      const;
                ossim_uint64 rawSamples()        const;
                ossim_uint64 offsetToFirstValidSample() const;

                std::vector<ossimFilename> getImageFileList() const { return theImageFileList; }

                void setImageFileList(const std::vector<ossimFilename>& list)
                {
                        theImageFileList = list; 
                }
                
                void setHeaderSize(ossim_uint32 headerSize) {theHeaderSize = headerSize;}
                
                void setInterleaveType(ossimInterleaveType il_type)
                {
                        theInterleaveType = il_type;
                }
                
                virtual std::ostream& print(std::ostream& out) const;
                void setImageRect(const ossimIrect& imageRect){theImageRect = imageRect;}
                
                void setValidImageRect(const ossimIrect &imageRect)
                {
                        theValidImageRect = imageRect;
                }
                
                void setRawImageRect(const ossimIrect &imageRect) {theRawImageRect=imageRect;}

                void setSubImageOffset(const ossimIpt& d) { theSubImageOffset = d; }

                ossim_uint32 bytesPerPixel(ossimScalarType type) const;
                ossim_uint32 bytesPerPixel() const;

                ossimByteOrder getImageDataByteOrder() const
                {
                        return theImageDataByteOrder; 
                }

                void setImageDataByteOrder(ossimByteOrder byteOrder);
                virtual bool saveState(ossimKeywordlist& kwl,
                                const char* prefix=0)const;

                virtual bool loadState(const ossimKeywordlist& kwl,
                                const char* prefix=0);


        private:
                ossimImageMetaData          theMetaData;
                std::vector<ossimFilename>  theImageFileList;
                ossimInterleaveType         theInterleaveType;
                ossim_uint32                theNumberOfBands;

                ossimIrect theRawImageRect;
                ossimIrect theValidImageRect;
                ossimIrect theImageRect;

                ossimIpt theSubImageOffset;

                ossim_uint32 theHeaderSize;
                ossimFillMode theSetNullsMode;
                ossim_uint32 thePixelsToChop;
                ossimByteOrder theImageDataByteOrder;

};


%inline %{

ossim_uint64 ossimGeneralRasterInfo::validLines() const
{
        return static_cast<ossim_uint64>(theValidImageRect.height());
}

ossim_uint64 ossimGeneralRasterInfo::rawLines() const
{
        return static_cast<ossim_uint64>(theRawImageRect.height());
}

ossim_uint64 ossimGeneralRasterInfo::bytesPerRawLine() const
{
        if (interleaveType() == OSSIM_BIP)
        {
                return rawSamples() * bytesPerPixel() * numberOfBands();
        }
        else
        {
                return rawSamples() * bytesPerPixel();
        }
}

ossim_uint64 ossimGeneralRasterInfo::bytesPerValidLine() const
{
        if (interleaveType() == OSSIM_BIP)
        {
                return validSamples() * bytesPerPixel() * numberOfBands();
        }
        else
        {
                return validSamples() * bytesPerPixel();
        }
}

ossim_uint64 ossimGeneralRasterInfo::validSamples() const
{
        return static_cast<ossim_uint64>(theValidImageRect.width());
}

ossim_uint64 ossimGeneralRasterInfo::rawSamples() const
{
        return static_cast<ossim_uint64>(theRawImageRect.width());
}

ossim_uint32 ossimGeneralRasterInfo::bytesPerPixel() const
{
        return bytesPerPixel((ossimScalarType)theMetaData.getScalarType());
}

ossim_uint64 ossimGeneralRasterInfo::offsetToFirstValidSample() const
{
        if (interleaveType() == OSSIM_BIP)
        {
                return headerSize() +
                        ( bytesPerRawLine() * validImageRect().ul().y ) +
                        ( validImageRect().ul().x * numberOfBands() * bytesPerPixel() );
        }
        else if (interleaveType() == OSSIM_BIL)
        {
                return headerSize() +
                        ( bytesPerRawLine() * validImageRect().ul().y * numberOfBands() ) +
                        ( validImageRect().ul().x * bytesPerPixel());
        }
        
        /* BSQ */
        else            
        {
                return headerSize() +
                        ( bytesPerRawLine() * validImageRect().ul().y ) +
                        ( validImageRect().ul().x * bytesPerPixel() );
        }
}

%}

