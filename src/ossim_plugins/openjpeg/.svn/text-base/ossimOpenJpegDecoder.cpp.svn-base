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
// $Id$

/* #define USE_OPJ_DEPRECATED */ /* fix (drb) */


#if 0

#include <cstdlib> /* for malloc */
#include <cstdio>  /* for stderr */
#include <cstddef> /* for NULL macro */
#include <cstring> /* for memset */
#include <fstream>

#include <openjpeg-2.0/openjpeg.h>

#include <ossimOpenJpegDecoder.h>
#include <ossimOpenJpegCommon.h>
#include <ossim/support_data/ossimJ2kSizRecord.h>

#include <ossim/base/ossimEndian.h>
#include <ossim/base/ossimException.h>
#include <ossim/base/ossimIrect.h>
#include <ossim/base/ossimTrace.h>

#include <ossim/imaging/ossimImageData.h>
#include <ossim/imaging/ossimU8ImageData.h>
#include <ossim/imaging/ossimImageDataFactory.h>

static const ossim_uint16 SOC_MARKER = 0xff4f; // Start of codestream marker.

static ossimTrace traceDebug(ossimString("ossimOpenJpegDecoder:degug"));

ossimOpenJpegDecoder::ossimOpenJpegDecoder()
{
}

ossimOpenJpegDecoder::~ossimOpenJpegDecoder()
{
}

ossimRefPtr<ossimImageData> ossimOpenJpegDecoder::decode(
   const ossimFilename& imageFile)
{
   ossimRefPtr<ossimImageData> result = 0;
   
   // Open the file.
   std::ifstream* in = new std::ifstream(imageFile.c_str(), std::ios::in|std::ios::binary);
   if (in->bad())
   {
      std::string errorMessage = "Could not open file ";
      errorMessage += imageFile.c_str();
      throw ossimException(errorMessage);
   }

   result = decode(in);

   in->close();
   delete in;
   in = 0;
   
   return in;
}

ossimRefPtr<ossimImageData> decode(std::ifstream* in)
{
   ossimRefPtr<ossimImageData> result = 0;

   if ( in && in->good() )
   {
      //---
      // Check for the start of codestream (soc) Marker required as first
      // field in main header.
      //---
      ossim_uint16 soc;
      in->read((char*)&soc,  2);
      if (ossim::byteOrder() == OSSIM_LITTLE_ENDIAN)
      {
         ossimEndian().swap(soc);
      }
      
      if (soc != SOC_MARKER)
      {
         std::string errorMessage = "Magic number wrong.  Is this a j2k?";
         throw ossimException(errorMessage);
      }

      // Get the size.
      ossimJ2kSizRecord siz;
      siz.parseStream(*in);

      


      

   }
   
   return result;
}

#if 1
ossimRefPtr<ossimImageData> ossimOpenJpegDecoder::decode(
   const ossimFilename& imageFile)
{
   // Open the file.
   std::ifstream in(imageFile.c_str(), std::ios::in|std::ios::binary);
   if (!in)
   {
      std::string errorMessage = "Could not open file ";
      errorMessage += imageFile.c_str();
      throw ossimException(errorMessage);
   }

   //---
   // Check for the start of codestream (soc) Marker required as first
   // field in main header.
   //---
   ossim_uint16 soc;
   in.read((char*)&soc,  2);
   if (ossim::byteOrder() == OSSIM_LITTLE_ENDIAN)
   {
      ossimEndian().swap(soc);
   }

   if (soc != SOC_MARKER)
   {
      std::string errorMessage = "Magic number wrong.  Is this a j2k?";
      throw ossimException(errorMessage);
   }

   if (traceDebug())
   {
      ossimJ2kSizRecord siz;
      siz.parseStream(in);
      ossimNotify(ossimNotifyLevel_DEBUG) << siz << std::endl;
   }

   //---
   // Read the file into memory.  Check for exception since this could
   // potentially run us out of memory.
   //---
   ossim_uint8* buffer = 0;
   ossim_int64 fileSize = imageFile.fileSize();
   try
   {
      buffer = new ossim_uint8[fileSize];
   }
   //Catch all standard exceptions. 
   catch (const std::exception& e)
   {
      if (buffer)
      {
         delete [] buffer;
         buffer = 0;
         throw ossimException(std::string(e.what()));
      }
   }

   in.seekg(0, ios::beg);
   in.read((char*)buffer, fileSize);

   // Finished with stream.
   in.close();

   // Decode to tile.
   ossimRefPtr<ossimImageData> result = 0;
   try
   {
      result = decodeBuffer(buffer, fileSize);
   }
   catch (const ossimException& e)
   {
      if (buffer)
      {
         delete [] buffer;
         buffer = 0;
         throw e;
      }
   }

   delete [] buffer;
   buffer = 0;

   return result;
}
#endif

#if 0
ossimRefPtr<ossimImageData> ossimOpenJpegDecoder::decodeBuffer(
   ossim_uint8* buffer, ossim_uint64 bufferSize)
{
   static const char MODULE[] = "ossimOpenJpegDecoder::decodeBuffer";
#if 0  
   opj_dparameters_t     parameters;
   opj_codestream_info_t cstr_info;
   
   // JPEG-2000 codestream

   // set decoding parameters to default values
   opj_set_default_decoder_parameters(&parameters);

   parameters.decod_format = 0;
   parameters.cod_format = -1;
   
   // get a decoder handle
   opj_codec_t* codec = opj_create_decompress(CODEC_J2K);
   if ( !codec )
   {
      std::string errMsg = MODULE;
      errMsg += " ERROR: opj_create_decompress failed!";
      throw ossimException(errMsg);
   }

   // catch events using our callbacks and give a local context
   opj_set_info_handler   (codec, &ossimOpenJpegDecoder::info_callback,   0);
   opj_set_warning_handler(codec, &ossimOpenJpegDecoder::warning_callback,0);
   opj_set_error_handler  (codec, &ossimOpenJpegDecoder::info_callback,   0);

   // setup the decoder decoding parameters using user parameters
   if ( opj_setup_decoder(codec, &parameters) == false )
   {
      std::string errMsg = MODULE;
      errMsg += " ERROR: opj_decode_with_info failed!";
      throw ossimException(errMsg);
   }

   // open a byte stream
   opj_cio_t* cio = opj_cio_open((opj_common_ptr)dinfo,
                                 static_cast<unsigned char*>(buffer),
                                 static_cast<int>(bufferSize));

   // decode the stream and fill the image structure
   // opj_image_t* image = opj_decode_with_info(dinfo, cio, theCodeStreamInfo);
   opj_image_t* image = opj_decode_with_info(dinfo, cio, &cstr_info);
   if(!image)
   {
      opj_destroy_decompress(dinfo);
      opj_destroy_cstr_info(&cstr_info);
      opj_cio_close(cio);
      std::string errMsg = MODULE;
      errMsg += " ERROR: opj_decode_with_info failed!";
      throw ossimException(errMsg);
   }
   
   if (traceDebug())
   {
      ossim::print(ossimNotify(ossimNotifyLevel_DEBUG), cstr_info);
      ossim::print(ossimNotify(ossimNotifyLevel_DEBUG), parameters);
      ossim::print(ossimNotify(ossimNotifyLevel_DEBUG), *image);
   }

   // close the byte stream
   opj_cio_close(cio);

   //---
   // We will assume all components or bands have the same scalar type for now.
   //---
   ossimScalarType scalar = getScalarType(*image, 0);
   if (scalar == OSSIM_SCALAR_UNKNOWN)
   {
      // free remaining structures
      if(dinfo)
      {
         opj_destroy_decompress(dinfo);
         dinfo = NULL;
      }
      opj_destroy_cstr_info(&cstr_info);
   
      // free codestream information structure */
      // opj_destroy_cstr_info(&cstr_info);

      // free image data structure
      opj_image_destroy(image);

      std::string errorMessage = "ERROR -> Unhandled scalar type: ";
      errorMessage += ossimString::toString(scalar).c_str();

      throw ossimException(errorMessage);
   }
   

   
   // Create a tile.
   ossimRefPtr<ossimImageData> result = 0;
   result = ossimImageDataFactory::instance()->
      create(0, // owner
             scalar,
             static_cast<ossim_uint32>(image->numcomps), // bands
             static_cast<ossim_uint32>(image->x1), // width
             static_cast<ossim_uint32>(image->y1)); // height
   
   // Allocate the tile buffer.
   result->initialize();

   
   // Load the image data to the tile.
   switch(scalar)
   {
      case OSSIM_UINT8:
      {
         load(ossim_uint8(0), 0, *image, result);
         break;
      }
      case OSSIM_SINT8:
      {
         int mask = image->comps[0].prec - 1; 
         load(ossim_sint8(0), mask, *image, result);
         break;
      }
      case OSSIM_UINT16:
      {
         load(ossim_uint16(0), 0, *image, result);
         break;
      }
      case OSSIM_SINT16:
      {
         int mask = image->comps[0].prec - 1;
         load(ossim_sint16(0), mask, *image, result);
         break;
      }
      default:
         break;
   }

   // free remaining structures
   if(dinfo)
   {
      opj_destroy_decompress(dinfo);
   }
   
   // free codestream information structure */
   opj_destroy_cstr_info(&cstr_info);

   // free image data structure
   opj_image_destroy(image);

   return result;
   #endif
   return 0;
}
#endif

std::ostream& ossimOpenJpegDecoder::print(std::ostream& out) const
{
   return out;
}

std::ostream& operator<<(std::ostream& out, const ossimOpenJpegDecoder& obj)
{
   return obj.print(out);
}

template <class T> void ossimOpenJpegDecoder::load(
   T /* scalar */,
   int mask,
   const opj_image& image,
   ossimRefPtr<ossimImageData> tile) const
{
   ossim_uint32 bands = static_cast<ossim_uint32>(image.numcomps);

   ossimEndian swapper;
   
   for(ossim_uint32 compno = 0; compno < bands; ++compno)
   {
      int* src   = image.comps[compno].data;        // source
      T*   dst   = (T*) tile->getBuf(compno);       // destination
      int  w     = image.comps[compno].w;
      int  h     = image.comps[compno].h;
      int  index = 0;
      
      for (int row = 0; row < h; ++row)
      {
         for(int col = 0; col < w; ++col)
         {
            int p = src[index];
            if (mask)
            {
               p += mask;
            }
            dst[index] = static_cast<T>(p);
            ++index;
         }
      }
   }

   // Validate status (empty, partial or full).
   tile->validate();
}

ossimScalarType ossimOpenJpegDecoder::getScalarType(
   const opj_image& image, ossim_uint32 band) const
{
   ossimScalarType result = OSSIM_SCALAR_UNKNOWN;

   if(image.comps[band].prec <= 8)
   {
      if(image.comps[band].sgnd == 0)
      {
         result = OSSIM_UINT8;
      }
      else if(image.comps[band].sgnd == 1)
      {
         result = OSSIM_SINT8;
      }
   }
   else if(image.comps[band].prec <= 16)
   {
      if(image.comps[band].sgnd == 0)
      {
         result = OSSIM_UINT16;
      }
      else if(image.comps[band].sgnd == 1)
      {
         result = OSSIM_SINT16;
      }
   }
   return result;
}

void ossimOpenJpegDecoder::error_callback(const char* msg,
                                          void* /* client_data */)
{
   ossimNotify(ossimNotifyLevel_WARN) << msg << std::endl;
}

void ossimOpenJpegDecoder::warning_callback(const char* msg,
                                            void* /* client_data */ )
{
   ossimNotify(ossimNotifyLevel_WARN) << msg << std::endl;
}

void ossimOpenJpegDecoder::info_callback(const char* msg,
                                         void* /* client_data */)
{
   ossimNotify(ossimNotifyLevel_WARN) << msg << std::endl;
}

#endif
