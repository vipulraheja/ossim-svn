/*-----------------------------------------------------------------------------
Filename        : ossimImageData.i
Author          : Vipul Raheja
License         : See top level LICENSE.txt file.
Description     : Contains SWIG-Python of class ossimImageData 
-----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimCommon.h>
#include <ossim/base/ossimIrect.h>
#include <ossim/base/ossimIpt.h>
#include <ossim/base/ossimRectilinearDataObject.h>
#include <ossim/base/ossimRefPtr.h>

#include <ossim/imaging/ossimImageData.h>

#include <vector>
#include <string>
#include <iosfwd>

%}

/* Handling the std::exception  */
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


/* Handling the vector<ossimDpt>  */
%include "std_vector.i"
namespace std
{
        %template(vectorFloat64) vector<ossim_float64>;
        %template(vectorUInt8) vector<ossim_uint8>;
};


/* Handling void ponters */
%typemap(in) void* 
{
        if (!PyCapsule_CheckExact($input)) 
        {
                %argument_fail(SWIG_ERROR, "$type", $symname, $argnum);
        }
        
        $1 = PyCapsule_GetPointer($input, NULL);
}

%typemap(out) void* 
{
        $result = PyCapsule_New($1, NULL, NULL);
}


/* Handling basic primitives */
/* Typemaps to convert values from Python to C++ */
%typemap(in) ossimjni_int8
{
        $1 = PyString_AsString($input);
}

%typemap(in) ossimjni_int32
{
        $1 = PyInt_AsLong($input);
}

%typemap(in) ossimjni_int64
{
        $1 = PyLong_AsLongLong($input);
}

%typemap(in) ossimjni_uint64
{
        $1 = PyLong_AsUnsignedLongLong
}

%typemap(in) ossimjni_float64
{
        $1 = PyFloat_AsDouble($input);
}


/* Typemaps to convert from C++ to Python */
%typemap(out) ossimjni_int32
{
        $result = PyInt_FromLong((long) $1);
}

%typemap(out) ossimjni_int64
{
        $result = PyLong_FromLongLong($1);
}

%typemap(out) ossimjni_uint64
{
        $result = PyLong_FromUnsignedLongLong($1);
}

%typemap(out) ossimjni_float64
{
        $result = PyFloat_FromDouble($1);
}


/* Applying the typemaps to other basic primitives */
%apply ossimjni_int8 { ossimjni_sint8, ossimjni_uint8 };
%apply ossimjni_int32 { ossimjni_int16, ossimjni_uint16, ossimjni_uint16, ossimjni_uint32, ossimjni_sint32 };
%apply ossimjni_int64 { ossimjni_sint64 };
%apply ossimjni_float64 { ossimjni_float32 };


/* Handling ossimImageData Assignment operator */
%rename(__setattr__) ossimImageData::operator=;


/* Handling ossimImageData Assignment operator */
%rename(ossimImageData_print) ossimImageData::print;


/* Wrapping the ossimImageData class */
class ossimImageData : public ossimRectilinearDataObject
{
        public:

                ossimImageData(const ossimImageData &rhs);

                ossimImageData(ossimSource* source,
                                ossimScalarType scalar,
                                ossim_uint32 bands = 1);

                ossimImageData(ossimSource* source,
                                ossimScalarType scalar,
                                ossim_uint32 bands,
                                ossim_uint32 width,
                                ossim_uint32 height);

                virtual ~ossimImageData();

                virtual const ossimImageData& operator=(const ossimImageData &rhs);

                virtual ossim_uint32 getWidth()const;

                virtual ossim_uint32 getHeight()const;

                virtual ossimIrect getImageRectangle() const;

                virtual void getWidthHeight(ossim_uint32& w, ossim_uint32& h);

                virtual void setWidth(ossim_uint32 width);

                virtual void setHeight(ossim_uint32 height);

                virtual void setWidthHeight(ossim_uint32 w, ossim_uint32 h);

                virtual void setImageRectangleAndBands(const ossimIrect& rect,
                                ossim_uint32 numberOfBands);

                virtual void setImageRectangle(const ossimIrect& rect);

                virtual void setOrigin(const ossimIpt& origin);   


                virtual void assign(const ossimDataObject* data);
                virtual void assign(const ossimImageData* data);
                virtual void assignBand(const ossimImageData* data,
                                ossim_uint32 source_band,
                                ossim_uint32 output_band);

                virtual ossimObject* dup() const;

                virtual ossim_uint32 getHashId()const;

                virtual void setNullPix(ossim_float64 null_pix);
                virtual void setNullPix(ossim_float64 null_pix, ossim_uint32 band);
                virtual void setNullPix(const ossim_float64* nullPixArray,
                                ossim_uint32 numberOfValues);
                virtual void setMinPix(ossim_float64 min_pix);
                virtual void setMinPix(ossim_float64 min_pix, ossim_uint32 band);
                virtual void setMinPix(const ossim_float64* minPixArray,
                                ossim_uint32 numberOfValues);
                virtual void setMaxPix(ossim_float64 max_pix);
                virtual void setMaxPix(ossim_float64 max_pix, ossim_uint32 band);
                virtual void setMaxPix(const ossim_float64* maxPixArray,
                                ossim_uint32 numberOfValues);

                virtual const ossimIpt& getOrigin()const{return m_origin;}

                virtual void computeMinMaxPix(std::vector<ossim_float64>& minBands,
                                std::vector<ossim_float64>& maxBands) const;

                virtual void computeMinMaxNulPix(
                                std::vector<ossim_float64>& minBands,
                                std::vector<ossim_float64>& maxBands,
                                std::vector<ossim_float64>& nulBands) const;

                virtual const ossim_float64* getNullPix()const;
                virtual const ossim_float64* getMinPix()const;
                virtual const ossim_float64* getMaxPix()const;
                virtual ossim_float64        getNullPix(ossim_uint32 band) const;
                virtual ossim_float64        getMinPix(ossim_uint32 band)  const;
                virtual ossim_float64        getMaxPix(ossim_uint32 band)  const;

                virtual ossim_float64   getMinNormalizedPix() const;

                virtual ossimString     getScalarTypeAsString()const;

                virtual ossim_uint32    getNumberOfBands() const;

                virtual void            setNumberOfBands(ossim_uint32 bands,
                                bool reallocate=false);

                virtual ossim_float64 getPix(const ossimIpt& position,
                                ossim_uint32 band=0) const;
                virtual ossim_float64 getPix(ossim_uint32 offset,
                                ossim_uint32 band = 0) const;

                void fill(ossim_uint32 band, ossim_float64 value);
                void fill(ossim_float64 value);

                bool isNull(ossim_uint32 offset)const;
                bool isNull(ossim_uint32 offset, ossim_uint32 band)const;

                void setNull(ossim_uint32 offset);
                void setNull(ossim_uint32 offset, ossim_uint32 band);

                bool isNull(const ossimIpt& pt)const;
                void setNull(const ossimIpt& pt);
                bool isNull(const ossimIpt& pt, ossim_uint32 band)const;
                void setNull(const ossimIpt& pt, ossim_uint32 band);


                virtual bool   isValidBand(ossim_uint32 band) const;

                virtual ossimDataObjectStatus validate() const;

                virtual ossimRefPtr<ossimImageData> newNormalizedFloat()const;


                virtual void getNormalizedFloat(ossim_uint32 offset,
                                ossim_uint32 bandNumber,
                                ossim_float32& result)const;
                virtual void setNormalizedFloat(ossim_uint32 offset,
                                ossim_uint32 bandNumber,
                                ossim_float32 input);

                virtual void convertToNormalizedFloat(ossimImageData* result)const;

                virtual ossimImageData* newNormalizedDouble()const;

                virtual void convertToNormalizedDouble(ossimImageData* result)const;

                virtual void unnormalizeInput(ossimImageData* normalizedInput);

                virtual ossim_float64 computeAverageBandValue(
                                ossim_uint32 bandNumber = 0) const;

                virtual ossim_float64 computeMeanSquaredError(
                                ossim_float64 meanValue,
                                ossim_uint32 bandNumber = 0) const;


                virtual void populateHistogram(ossimRefPtr<ossimMultiBandHistogram> histo);

                virtual bool hasAlpha() const;

                virtual const ossim_uint8* getAlphaBuf() const;

                virtual ossim_uint8* getAlphaBuf();

                virtual const void* getBuf() const;

                virtual const ossim_uint8*    getUcharBuf()  const;

                virtual const ossim_uint16*   getUshortBuf() const;

                virtual const ossim_sint16*   getSshortBuf() const;

                virtual const ossim_float32*  getFloatBuf()  const;

                virtual const ossim_float64*  getDoubleBuf() const;

                virtual void* getBuf();

                virtual ossim_uint8*    getUcharBuf();

                virtual ossim_uint16*   getUshortBuf();

                virtual ossim_sint16*   getSshortBuf();

                virtual ossim_float32*  getFloatBuf();

                virtual ossim_float64*  getDoubleBuf();

                virtual const void*           getBuf(ossim_uint32 band) const;

                virtual const ossim_uint8*    getUcharBuf(ossim_uint32 band) const;

                virtual const ossim_uint16*   getUshortBuf(ossim_uint32 band) const;

                virtual const ossim_sint16*   getSshortBuf(ossim_uint32 band) const;

                virtual const ossim_float32*  getFloatBuf(ossim_uint32 band) const;

                virtual const ossim_float64*  getDoubleBuf(ossim_uint32 band) const;

                virtual void*           getBuf(ossim_uint32 band);

                virtual ossim_uint8*    getUcharBuf(ossim_uint32 band);

                virtual ossim_uint16*   getUshortBuf(ossim_uint32 band);

                virtual ossim_sint16*   getSshortBuf(ossim_uint32 band);

                virtual ossim_float32*  getFloatBuf(ossim_uint32 band);

                virtual ossim_float64*  getDoubleBuf(ossim_uint32 band);

                virtual ossim_uint32 getSize() const;

                virtual ossim_uint32 getSizePerBand()const;

                virtual ossim_uint32 getSizePerBandInBytes() const;

                virtual ossim_uint32 getDataSizeInBytes()const;

                virtual ossim_uint32  getSizeInBytes() const;

                virtual void makeBlank();

                virtual void initialize(); 

                virtual bool write(const ossimFilename& f) const;


                virtual void copyTileToNormalizedBuffer(ossim_float64* buf) const;

                virtual void copyTileToNormalizedBuffer(ossim_float32* buf)const;


                virtual void copyTileBandToNormalizedBuffer(ossim_uint32 band,
                                ossim_float64* buf) const;

                virtual void copyTileBandToNormalizedBuffer(ossim_uint32 band,
                                ossim_float32* buf)const;


                virtual void copyNormalizedBufferToTile(ossim_float64* buf);
                virtual void copyNormalizedBufferToTile(ossim_float32* buf);


                virtual void copyNormalizedBufferToTile(ossim_uint32 band,
                                ossim_float64* buf);
                virtual void copyNormalizedBufferToTile(ossim_uint32 band,
                                ossim_float32* buf);


                virtual bool isWithin(ossim_int32 x, ossim_int32 y);
                virtual void setValue(ossim_int32 x, ossim_int32 y, ossim_float64 color);


                virtual void loadBand(const void* src,
                                const ossimIrect& src_rect,
                                ossim_uint32 band);

                virtual void loadBand(const void* src,
                                const ossimIrect& src_rect,
                                const ossimIrect& clip_rect,
                                ossim_uint32 band);


                virtual void loadTile(const void* src,
                                const ossimIrect& src_rect,
                                ossimInterleaveType il_type);

                virtual void loadTile(const void* src,
                                const ossimIrect& src_rect,
                                const ossimIrect& clip_rect,                         
                                ossimInterleaveType il_type);


                virtual void nullTileAlpha(const ossim_uint8* src,
                                const ossimIrect& src_rect,
                                bool mutliplyAlphaFlag=false);
                virtual void nullTileAlpha(const ossim_uint8* src,
                                const ossimIrect& src_rect,
                                const ossimIrect& clip_rect,
                                bool multiplyAlphaFlag=false);


                virtual void loadTile(const ossimImageData* src);

                virtual void loadTileFrom1Band(const ossimImageData* data);

                virtual void loadTileFrom1Band(const void* src,
                                const ossimIrect& src_rect);


                virtual void loadShortBand(const void* src,
                                const ossimIrect& src_rect,
                                ossim_uint32 band,
                                bool swap_bytes=false);


                virtual void unloadBand( void* dest,
                                ossim_uint32 src_band,
                                ossim_uint32 dest_band,
                                const ossimIrect& dest_rect,
                                ossimInterleaveType il_type=OSSIM_BSQ,
                                OverwriteBandRule ow_type=NULL_RULE ) const;

                virtual void unloadBand( void* dest,
                                ossim_uint32 src_band,
                                ossim_uint32 dest_band,
                                const ossimIrect& dest_rect,
                                const ossimIrect& clip_rect,
                                ossimInterleaveType il_type=OSSIM_BSQ,
                                OverwriteBandRule ow_type=NULL_RULE ) const;

                virtual void unloadBand(void* dest,
                                const ossimIrect& dest_rect,
                                ossim_uint32 src_band) const;

                virtual void unloadBand(void* dest,
                                const ossimIrect& dest_rect,
                                const ossimIrect& clip_rect,
                                ossim_uint32 src_band) const;


                virtual void unloadTile(void* dest,
                                const ossimIrect& dest_rect,
                                ossimInterleaveType il_type ) const;

                virtual void unloadTile(void* dest,
                                const ossimIrect& dest_rect,
                                const ossimIrect& clip_rect,
                                ossimInterleaveType il_type) const;


                virtual void unloadTileToBipAlpha(void* dest,
                                const ossimIrect& dest_rect,
                                const ossimIrect& clip_rect) const;

                virtual bool isPointWithin(const ossimIpt& point)const;
                virtual bool isPointWithin(ossim_int32 x,
                                ossim_int32 y)const;


                virtual std::ostream& print(std::ostream& out) const;

                virtual void stretchMinMax();

                virtual void computeAlphaChannel();

                virtual void copyLine(const void* src,
                                ossim_int32 lineNumber,
                                ossim_int32 lineStartSample,
                                ossim_int32 lineStopSample,
                                ossimInterleaveType lineInterleave);

                void setIndexedFlag(bool flag);

                bool getIndexedFlag() const;


        protected:

                ossimImageData();

                template <class T> void copyLineTemplate(T dummyTemplate,
                                const void* src,
                                ossim_int32 lineNumber,
                                ossim_int32 lineStartSample,
                                ossim_int32 lineStopSample,
                                ossimInterleaveType lineInterleave);

                template <class T> void stretchMinMax(T dummyTemplate);

                template <class T> void computeAlphaChannel(T dummyTemplate);   

                template <class T> ossimDataObjectStatus validate(T dummyTemplate) const;

                template <class T> void makeBlank(T dummyTemplate);

                template <class T>
                        ossim_float64 computeMeanSquaredError(T dummyTemplate,
                                        ossim_float64 meanValue,
                                        ossim_uint32 bandNumber) const;

                template <class T>
                        ossim_float64 computeAverageBandValue(T dummyTemplate,
                                        ossim_uint32 bandNumber) const;

                void loadTileFromBip(const void* src, const ossimIrect& src_rect);
                void loadTileFromBil(const void* src, const ossimIrect& src_rect);
                void loadTileFromBsq(const void* src, const ossimIrect& src_rect);

                void loadTileFromBip(const void* src,
                                const ossimIrect& src_rect,
                                const ossimIrect& clip_rect);
                void loadTileFromBil(const void* src,
                                const ossimIrect& src_rect,
                                const ossimIrect& clip_rect);
                void loadTileFromBsq(const void* src,
                                const ossimIrect& src_rect,
                                const ossimIrect& clip_rect);

                void unloadTileToBip(void* dest,
                                const ossimIrect& dest_rect,
                                const ossimIrect& clip_rect) const;
                void unloadTileToBil(void* dest,
                                const ossimIrect& dest_rect,
                                const ossimIrect& clip_rect) const;
                void unloadTileToBsq(void* dest,
                                const ossimIrect& dest_rect,
                                const ossimIrect& clip_rect) const;

                virtual void unloadBandToBsq( void* dest,
                                ossim_uint32 src_band,
                                ossim_uint32 dest_band,
                                const ossimIrect& dest_rect,
                                const ossimIrect& clip_rect,
                                OverwriteBandRule ow_type=NULL_RULE ) const;

                template <class T>
                        void copyTileToNormalizedBuffer(T dummyTemplate,
                                        ossim_float64* buf) const;
                template <class T>
                        void copyTileToNormalizedBuffer(T dummyTemplate,
                                        ossim_float32* buf)const;

                template <class T>
                        void copyTileToNormalizedBuffer(T dummyTemplate,
                                        ossim_uint32 band, ossim_float64* buf) const;
                template <class T>
                        void copyTileToNormalizedBuffer(T dummyTemplate,
                                        ossim_uint32 band, ossim_float32* buf)const;

                template <class T>
                        void copyNormalizedBufferToTile(T dummyTemplate,
                                        ossim_float64* buf);
                template <class T>
                        void copyNormalizedBufferToTile(T dummyTemplate,
                                        ossim_float32* buf);
                template <class T>
                        void copyNormalizedBufferToTile(T dummyTemplate,
                                        ossim_uint32 band,
                                        ossim_float64* buf);
                template <class T>
                        void copyNormalizedBufferToTile(T dummyTemplate,
                                        ossim_uint32 band,
                                        ossim_float32* buf);


                template <class T>
                        void computeMinMaxPix(T dummyValue,
                                        std::vector<ossim_float64>& minBands,
                                        std::vector<ossim_float64>& maxBands) const;

                template <class T>
                        void computeMinMaxNulPix(T dummyValue,
                                        std::vector<ossim_float64>& minBands,
                                        std::vector<ossim_float64>& maxBands,
                                        std::vector<ossim_float64>& nulBands) const;

                template <class T> void loadBandTemplate(T, // dummy template variable
                                const void* src,
                                const ossimIrect& src_rect,
                                ossim_uint32 band);

                template <class T> void loadBandTemplate(T, // dummy template variable
                                const void* src,
                                const ossimIrect& src_rect,
                                const ossimIrect& clip_rect,
                                ossim_uint32 band);

                template <class T> void nullTileAlphaTemplate(T,
                                const ossim_uint8* src,
                                const ossimIrect& src_rect,
                                const ossimIrect& clip_rect,
                                bool multiplyAlphaFlag=false);

                template <class T> void loadTileFromBipTemplate(T, // dummy template variable
                                const void* src,
                                const ossimIrect& src_rect);

                template <class T> void loadTileFromBipTemplate(T, // dummy template variable
                                const void* src,
                                const ossimIrect& src_rect,
                                const ossimIrect& clip_rect);

                template <class T> void loadTileFromBilTemplate(T, // dummy template variable
                                const void* src,
                                const ossimIrect& src_rect);

                template <class T> void loadTileFromBilTemplate(T, // dummy template variable
                                const void* src,
                                const ossimIrect& src_rect,
                                const ossimIrect& clip_rect);

                template <class T> void loadTileFromBsqTemplate(T, // dummy template variable
                                const void* src,
                                const ossimIrect& src_rect);

                template <class T> void loadTileFromBsqTemplate(T, // dummy template variable
                                const void* src,
                                const ossimIrect& src_rect,
                                const ossimIrect& clip_rect);

                template <class T> void unloadTileToBipTemplate(T, // dummy template variable
                                void* dest,
                                const ossimIrect& dest_rect,
                                const ossimIrect& clip_rect) const;

                template <class T> void unloadTileToBipAlphaTemplate(T, // dummy template variable
                                void* dest,
                                const ossimIrect& dest_rect,
                                const ossimIrect& clip_rect) const;

                template <class T> void unloadTileToBilTemplate(T, // dummy template variable
                                void* dest,
                                const ossimIrect& dest_rect,
                                const ossimIrect& clip_rect) const;

                template <class T> void unloadTileToBsqTemplate(T, // dummy template variable
                                void* dest,
                                const ossimIrect& dest_rect,
                                const ossimIrect& clip_rect) const;

                template <class T> void unloadBandTemplate(T, // dummy template variable
                                void* dest,
                                const ossimIrect& dest_rect,
                                const ossimIrect& clip_rect,
                                ossim_uint32 band) const;

                template <class T> void unloadBandToBsqTemplate(T, // dummy template variable
                                void* dest,
                                ossim_uint32 src_band,
                                ossim_uint32 dest_band,
                                const ossimIrect& dest_rect,
                                const ossimIrect& clip_rect,
                                OverwriteBandRule ow_type=NULL_RULE) const;

                virtual void initializeDefaults();

                virtual void initializeMinDefault();

                virtual void initializeMaxDefault();

                virtual void initializeNullDefault();

                virtual bool isEqualTo(const ossimDataObject& rhs,
                                bool deepTest=false)const;

                bool hasSameDimensionsAs(ossimImageData* data)const
                {
                        bool result = false;
                        if(data)
                        {
                                result = ((m_spatialExtents.size() ==
                                                        data->m_spatialExtents.size())&&
                                                (m_spatialExtents[0] == data->m_spatialExtents[0])&&
                                                (m_spatialExtents[1] == data->m_spatialExtents[1])&&
                                                (m_scalarType == data->m_scalarType));
                        }
                        return result;
                }

                std::vector<ossim_float64> m_nullPixelValue;

                std::vector<ossim_float64> m_minPixelValue;

                std::vector<ossim_float64> m_maxPixelValue;

                std::vector<ossim_uint8> m_alpha;

                ossimIpt m_origin;

                bool m_indexedFlag;


        private:
                /* Ignored due to unclean parsing of MACROS     */                
                /* TYPE_DATA */
};

%inline 

%{

        bool ossimImageData::hasAlpha() const
        {
                return (m_alpha.size()?true:false);
        }

        ossimIrect ossimImageData::getImageRectangle() const
        {
                ossimIpt lr(m_origin.x + getWidth()  - 1,
                                m_origin.y + getHeight() - 1);

                return ossimIrect(m_origin, lr);
        }

        const ossim_float64* ossimImageData::getNullPix()const
        {
                return ( m_nullPixelValue.size() > 0 ? &m_nullPixelValue.front() : 0 );
        }

        const ossim_float64* ossimImageData::getMinPix()const
        {
                return ( m_minPixelValue.size() > 0 ? &m_minPixelValue.front() : 0 );
        }

        const ossim_float64* ossimImageData::getMaxPix()const
        {
                return ( m_maxPixelValue.size() > 0 ? &m_maxPixelValue.front() : 0 );
        }

        ossim_float64 ossimImageData::getNullPix(ossim_uint32 band) const
        {
                return ( band < m_nullPixelValue.size() ? m_nullPixelValue[band] :
                                ossim::defaultNull( getScalarType() ) );
        }

        ossim_float64 ossimImageData::getMinPix(ossim_uint32 band) const
        {
                return ( band < m_minPixelValue.size() ? m_minPixelValue[band] :
                                ossim::defaultMin( getScalarType() ) );
        }

        ossim_float64 ossimImageData::getMaxPix(ossim_uint32 band) const
        {
                return ( band < m_maxPixelValue.size() ? m_maxPixelValue[band] :
                                ossim::defaultMax( getScalarType() ) );
        }

        ossim_uint32 ossimImageData::getHashId()const
        {
                const unsigned char *bufx = (unsigned char*)(&m_origin.x);
                const unsigned char *bufy = (unsigned char*)(&m_origin.y);
                return (ossim_uint32)(bufx[0]*101 + bufx[1]*103 +
                                bufx[2]*107 + bufx[3]*109 +
                                bufy[0]*139 + bufy[1]*149 +
                                bufy[2]*151 + bufy[3]*157);
        }

%}
