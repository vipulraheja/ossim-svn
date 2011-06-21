//----------------------------------------------------------------------------
//
// License:  See top level LICENSE.txt file
//
// Author:  David Burken
//
// Description: OSSIM Open JPEG (j2k) tile.  This encapsulates decoding a
// jpeg image to an ossimImageData object using the openjpeg library.
//
// http://www.openjpeg.org/
//
//----------------------------------------------------------------------------
// $Id: ossimOpenJpegDecoder.h 11438 2007-07-29 17:41:11Z dburken $
#ifndef ossimOpenJpegDecoder_HEADER
#define ossimOpenJpegDecoder_HEADER

#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimRefPtr.h>

// Forward class / struct declarations.
class ossimFilename;
// class ossimImageData;
// struct opj_image;

class ossimOpenJpegDecoder
{
public:

   /** @brief default constructor */
   ossimOpenJpegDecoder();

   /** @brief destructor */
   ~ossimOpenJpegDecoder();

   ossimRefPtr<ossimImageData> decode(const ossimFilename& imageFile);

   ossimRefPtr<ossimImageData> decode(std::ifstream* in);
   


   

#if 0 
   /**
    * Decode file to ossimImageData object.
    *
    * @param file The file to decode.
    * 
    * @return ossimRefPtr<ossimImageData>.  Note that the internal pointer
    * will be null if file cannot be decoded so callers should check pointer.
    *
    * @note throws ossim exception on failure.
    */
   ossimRefPtr<ossimImageData> decode(const ossimFilename& imageFile);

   /**
    * Decode buffer to ossimImageData object.
    *
    * @param buffer The buffer to decode.
    *
    * @param bufferSize The buffer size in bytes.
    * 
    * @return ossimRefPtr<ossimImageData>.  Note that the internal pointer
    * will be null if file cannot be decoded so callers should check pointer.
    *
    * @note throws ossim exception on failure.
    */
   ossimRefPtr<ossimImageData> decodeBuffer(ossim_uint8* buffer,
                                            ossim_uint64 bufferSize);


   /**
    * Prints decode parameters.
    * 
    * @return std::ostream&
    */
   std::ostream& print(std::ostream& out) const;

   friend std::ostream& operator<<(std::ostream& out,
                                   const ossimOpenJpegDecoder& obj);
#endif

private:

#if 0
   /**
    * Load the decompressed image data to tile.
    */
   template <class T> void load(T scalar,
                                int mask,
                                const opj_image& image,
                                ossimRefPtr<ossimImageData> tile) const;

   
   /**
    * @return Returns the scalar type for image band.
    */
   ossimScalarType getScalarType(const opj_image& image,
                                 ossim_uint32 band) const;

#endif

   /** Callback method for errors. */
   static void error_callback(const char *msg, void *client_data);

   /** Callback method for warnings. */
   static void warning_callback(const char *msg, void *client_data);

   /** Callback method for info. */
   static void info_callback(const char *msg, void *client_data);

};

#endif /* #ifndef ossimOpenJpegDecoder_HEADER */
