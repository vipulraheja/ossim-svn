//----------------------------------------------------------------------------
//
// License:  LGPL
// 
// See LICENSE.txt file in the top level directory for more details.
//
// Author:  David Burken
//
// Description: OSSIM Portable Network Graphics (PNG) reader (tile source).
//
//----------------------------------------------------------------------------
// $Id: ossimPngReader.cpp 19730 2011-06-06 21:46:30Z dburken $

#include <cstdlib>
#include <cstddef> /* for NULL */
#include <cmath>   /* for pow */

#include "ossimPngReader.h"
#include <ossim/imaging/ossimTiffTileSource.h>
#include <ossim/imaging/ossimImageDataFactory.h>
#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimIpt.h>
#include <ossim/base/ossimDpt.h>
#include <ossim/base/ossimEndian.h>
#include <ossim/base/ossimIrect.h>
#include <ossim/base/ossimFilename.h>
#include <ossim/base/ossimKeywordlist.h>
#include <ossim/imaging/ossimU8ImageData.h>
#include <ossim/base/ossimTrace.h>
#include <ossim/base/ossimNotifyContext.h>


RTTI_DEF1(ossimPngReader, "ossimPngReader", ossimImageHandler)

#ifdef OSSIM_ID_ENABLED
   static const char OSSIM_ID[] = "$Id: ossimPngReader.cpp 19730 2011-06-06 21:46:30Z dburken $";
#endif
   
static ossimTrace traceDebug("ossimPngReader:degug");  

ossimPngReader::ossimPngReader()
   :
      ossimImageHandler(),
      theTile(0),
      theCacheTile(0),
      theLineBuffer(0),
      theLineBufferSizeInBytes(0),
      theFilePtr(NULL),
      theBufferRect(0, 0, 0, 0),
      theImageRect(0, 0, 0, 0),
      theNumberOfInputBands(0),
      theNumberOfOutputBands(0),
      theBytePerPixelPerBand(1),
      theCacheSize	(0),
      theCacheId(-1),
      thePngPtr(0),
      theInfoPtr(0),
      thePngColorType(PNG_COLOR_TYPE_GRAY),
      theCurrentRow(0),
      theOutputScalarType(OSSIM_UINT8),
      theInterlacePasses(1),
      theBitDepth(8),
      theReadMode(ossimPngReadUnknown),
      theMaxPixelValue(),
      theSwapFlag(false)
{
   if (traceDebug())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << "ossimPngReader::ossimPngReader entered..." << std::endl;
      readPngVersionInfo();
#ifdef OSSIM_ID_ENABLED
      ossimNotify(ossimNotifyLevel_DEBUG)
         << "OSSIM_ID:  " << OSSIM_ID << endl;
#endif
   }
}

ossimPngReader::~ossimPngReader()
{
   if (isOpen())
   {
      close();
   }
}

void ossimPngReader::destroy()
{
   ossimAppFixedTileCache::instance()->deleteCache(theCacheId);

   // ossimRefPtrs so assign to 0(unreferencing) will handle memory.
   theTile      = 0;
   theCacheTile = 0;

   if (theLineBuffer)
   {
      delete [] theLineBuffer;
      theLineBuffer = 0;
   }

   if (thePngPtr)
   {
      png_destroy_read_struct(&thePngPtr, &theInfoPtr, NULL);
      thePngPtr = 0;
      theInfoPtr = 0;
   }
   if (theFilePtr)
   {
      fclose(theFilePtr);
      theFilePtr = NULL;
   }
}

void ossimPngReader::allocate()
{
   // Make the cache tile the height of one tile by the image width.
   ossim::defaultTileSize(theCacheSize);
   theCacheSize.x = theImageRect.width();
   
   ossimAppFixedTileCache::instance()->deleteCache(theCacheId);
   theCacheId = ossimAppFixedTileCache::instance()->
      newTileCache(theImageRect, theCacheSize);

   theTile = ossimImageDataFactory::instance()->create(this, this);
   theCacheTile = (ossimImageData*)theTile->dup();
   theTile->initialize();
   
   ossimIrect cache_rect(theImageRect.ul().x,
                         theImageRect.ul().y,
                         theImageRect.ul().x + (theCacheSize.x-1),
                         theImageRect.ul().y + (theCacheSize.y-1));
   
   theCacheTile->setImageRectangle(cache_rect);
   theCacheTile->initialize();

   if(theLineBuffer)
   {
      delete [] theLineBuffer;
   }
   theLineBuffer = new ossim_uint8[theLineBufferSizeInBytes];

   if (traceDebug())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << "ossimPngReader::allocate DEBUG:"
         << "\ntheCacheTile:\n" << *(theCacheTile.get())
         << "\ntheTile:\n"      << *(theTile.get())
         << "\ncache tile size:           " << theCacheSize
         << "\nimage width:               " << theImageRect.width()
         << "\nimage height:              " << theImageRect.height()
         << "\nnumber of bands:           " << theNumberOfOutputBands
         << "\nline buffer size:          " << theLineBufferSizeInBytes
         << endl;
   }
}

ossimRefPtr<ossimImageData> ossimPngReader::getTile(
   const ossimIrect& rect, ossim_uint32 resLevel)
{
   if (theTile.valid())
   {
      // Image rectangle must be set prior to calling getTile.
      theTile->setImageRectangle(rect);
      
      if ( getTile( theTile.get(), resLevel ) == false )
      {
         if (theTile->getDataObjectStatus() != OSSIM_NULL)
         {
            theTile->makeBlank();
         }
      }
   }
   
   return theTile;
}

bool ossimPngReader::getTile(ossimImageData* result,
                             ossim_uint32 resLevel)
{
   bool status = false;
   
   //---
   // Not open, this tile source bypassed, or invalid res level,
   // return a blank tile.
   //---
   if( isOpen() && isSourceEnabled() && isValidRLevel(resLevel) &&
       result && (result->getNumberOfBands() == getNumberOfOutputBands()) )
   {
      result->ref(); // Increment ref count.
      
      //---
      // Check for overview tile.  Some overviews can contain r0 so always
      // call even if resLevel is 0.  Method returns true on success, false
      // on error.
      //---
      status = getOverviewTile(resLevel, result);

      if (status)
      {
         if(theOutputScalarType == OSSIM_UINT16)
         {
            //---
            // Temp fix:
            // The overview handler could return a tile of OSSIM_USHORT11 if
            // the max sample value was not set to 2047.
            //
            // To prevent a scalar mismatch set 
            //---
            result->setScalarType(theOutputScalarType);
         }
      }
      
      if (!status) // Did not get an overview tile.
      {
         status = true;
         
         ossimIrect tile_rect = result->getImageRectangle();

         if ( ! tile_rect.completely_within(getImageRectangle(0)) )
         {
            // We won't fill totally so make blank first.
            theTile->makeBlank();
         }
         
         if (getImageRectangle(0).intersects(tile_rect))
         {
            // Make a clip rect.
            ossimIrect clip_rect = tile_rect.clipToRect(getImageRectangle(0));
            
            // This will validate the tile at the end.
            fillTile(clip_rect, result);
         }
      }

      result->unref();  // Decrement ref count.
   }

   return status;
}

void ossimPngReader::fillTile(const ossimIrect& clip_rect,
                              ossimImageData* tile)
{
   if (!tile || !theFilePtr) return;

   ossimIrect buffer_rect = clip_rect;
   buffer_rect.stretchToTileBoundary(theCacheSize);
   buffer_rect.set_ulx(0);
   buffer_rect.set_lrx(getImageRectangle(0).lr().x);

   ossim_int32 number_of_cache_tiles = buffer_rect.height()/theCacheSize.y;

#if 0
   if (traceDebug())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << "tiles high:  " << number_of_cache_tiles
         << endl;
   }
#endif

   ossimIpt origin = buffer_rect.ul();
   
   for (int tileIdx = 0; tileIdx < number_of_cache_tiles; ++tileIdx)
   {
      // See if it's in the cache already.
      ossimRefPtr<ossimImageData> tempTile;
      tempTile = ossimAppFixedTileCache::instance()->
         getTile(theCacheId, origin);
      if (tempTile.valid())
      {
         tile->loadTile(tempTile.get());
      }
      else
      {
         // Have to read from the png file.
         ossim_uint32 startLine = static_cast<ossim_uint32>(origin.y);
         ossim_uint32 stopLine  = 
            static_cast<ossim_uint32>( min(origin.y+theCacheSize.y-1,
                                           getImageRectangle().lr().y) );
         ossimIrect cache_rect(origin.x,
                               origin.y,
                               origin.x+theCacheSize.x-1,
                               origin.y+theCacheSize.y-1);
         
         theCacheTile->setImageRectangle(cache_rect);

         if ( !theCacheTile->getImageRectangle().
              completely_within(getImageRectangle()) )
         {
            theCacheTile->makeBlank();
         }

         if (startLine < theCurrentRow)
         {
            // Must restart the compression process again.
            restart();
         }

         // Gobble any not needed lines.
         while(theCurrentRow < startLine)
         {
            png_read_row(thePngPtr, theLineBuffer, NULL);
            ++theCurrentRow;
         }
            
         switch (theReadMode)
         {
            case ossimPngRead8:
               copyLines(ossim_uint8(0), stopLine);
               break;
            case ossimPngRead16:
               copyLines(ossim_uint16(0), stopLine);
               break;
            case ossimPngRead8a:
               copyLinesWithAlpha(ossim_uint8(0), stopLine);
               break;
            case ossimPngRead16a:
               copyLinesWithAlpha(ossim_uint16(0), stopLine);
               break;
            case ossimPngReadUnknown:
            default:
               break; // should never happen.
         }

         theCacheTile->validate();
         
         tile->loadTile(theCacheTile.get());
         
         // Add it to the cache for the next time.
         ossimAppFixedTileCache::instance()->addTile(theCacheId,
                                                     theCacheTile);
         
      } // End of reading for png file.
      
      origin.y += theCacheSize.y;
      
   } // for (int tile = 0; tile < number_of_cache_tiles; ++tile)
   
   tile->validate();
}

ossimIrect
ossimPngReader::getImageRectangle(ossim_uint32 reduced_res_level) const
{
   return ossimIrect(0,
                     0,
                     getNumberOfSamples(reduced_res_level) - 1,
                     getNumberOfLines(reduced_res_level)   - 1);
}

bool ossimPngReader::saveState(ossimKeywordlist& kwl,
                               const char* prefix) const
{
   return ossimImageHandler::saveState(kwl, prefix);
}

bool ossimPngReader::loadState(const ossimKeywordlist& kwl,
                               const char* prefix)
{
   if (ossimImageHandler::loadState(kwl, prefix))
   {
      return open();
   }

   return false;
}

bool ossimPngReader::open()
{
   static const char MODULE[] = "ossimPngReader::open";

   if (traceDebug())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << "ossimPngReader::open entered..."
         << "File:  " << theImageFile.c_str()
         << std::endl;
   }

   // Start with a clean slate.
   if (isOpen())
   {
      close();
   }

   // Check for empty filename.
   if (theImageFile.empty())
   {
      return false;
   }
   
   // Open Png file.
   if((theFilePtr = fopen(theImageFile.c_str(), "rb")) == NULL)
   {
      theErrorStatus = ossimErrorCodes::OSSIM_ERROR;

      if (traceDebug())
      {
         ossimNotify(ossimNotifyLevel_DEBUG)
            << MODULE << "\nERROR:\n"
            << "Could not open:  " << theImageFile.c_str()
            << endl;
      }
      
      return false;
   }

   if (readPngInit() == false)
   {
      destroy();
      return false;
   }
  
   completeOpen();

   // Allocate memory...
   allocate();

   return true;
}

ossim_uint32 ossimPngReader::getTileWidth() const
{
   return ( theTile.valid() ? theTile->getWidth() : 0 );
}

ossim_uint32 ossimPngReader::getTileHeight() const
{
   return ( theTile.valid() ? theTile->getHeight() : 0 );
}

ossim_uint32 ossimPngReader::getNumberOfLines(ossim_uint32 reduced_res_level) const
{
   if (reduced_res_level == 0)
   {
      return theImageRect.height();
   }
   else if ( theOverview.valid() )
   {
      return theOverview->getNumberOfLines(reduced_res_level);
   }

   return 0;
}

ossim_uint32 ossimPngReader::getNumberOfSamples(ossim_uint32 reduced_res_level) const
{
   if (reduced_res_level == 0)
   {
      return theImageRect.width();
   }
   else if ( theOverview.valid() )
   {
      return theOverview->getNumberOfSamples(reduced_res_level);
   }

   return 0;
}

ossim_uint32 ossimPngReader::getImageTileWidth() const
{
   return 0;
}

ossim_uint32 ossimPngReader::getImageTileHeight() const
{
   return 0;
}

ossimString ossimPngReader::getShortName()const
{
   return ossimString("ossim_png_reader");
}
   
ossimString ossimPngReader::getLongName()const
{
   return ossimString("ossim png reader");
}

ossimString  ossimPngReader::getClassName()const
{
   return ossimString("ossimPngReader");
}

ossim_uint32 ossimPngReader::getNumberOfInputBands() const
{
   //---
   // NOTE:  If there is an alpha channel the input band will be one more than
   // the output bands.  For library purposes the output bands and input bands
   // are the same.
   //---
   return theNumberOfOutputBands;
}

ossim_uint32 ossimPngReader::getNumberOfOutputBands()const
{
   return theNumberOfOutputBands;
}

ossimScalarType ossimPngReader::getOutputScalarType() const
{
   return theOutputScalarType;
}

bool ossimPngReader::isOpen()const
{
   return (theFilePtr != NULL);
}

double ossimPngReader::getMaxPixelValue(ossim_uint32 band)const
{
   //---
   // Note the size of theMaxPixelValue can be one greater than output bands
   // if there is an alpa channel.
   //---
   if (band < theNumberOfOutputBands)
   {
      return theMaxPixelValue[band];
   }
   return 255.0;
}

void ossimPngReader::close()
{
   destroy();
   ossimImageHandler::close();
}

void ossimPngReader::restart()
{
   // Destroy the existing memory associated with png structs.
   if (thePngPtr && theInfoPtr)
   {
      png_destroy_read_struct(&thePngPtr, &theInfoPtr, NULL);
   }

   thePngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
                                      NULL,
                                      NULL,
                                      NULL);
   theInfoPtr = png_create_info_struct(thePngPtr);

   if (setjmp (thePngPtr->jmpbuf))
   {
      ossimNotify(ossimNotifyLevel_WARN)
         << "Error while reading.  File corrupted?  "
         << theImageFile
         << std::endl;
      
      return;
   }

   // Reset the file pointer.
   fseek(theFilePtr, 0, SEEK_SET);

   // Store the file pointer in the thePngPtr struct.
   png_init_io(thePngPtr, theFilePtr);

   //---
   // Note we won't do png_set_sig_bytes(png_ptr, 8) here because we are not
   // rechecking for png signature.
   //---
   png_read_info(thePngPtr, theInfoPtr);

   //---
   // If png_set_expand used:
   // Expand data to 24-bit RGB, or 8-bit grayscale,
   // with alpha if available.
   //---
   bool expandFlag = false;

   if ( thePngColorType == PNG_COLOR_TYPE_PALETTE )
   {
      expandFlag = true;
   }
   if ( (thePngColorType == PNG_COLOR_TYPE_GRAY) && (theBitDepth < 8) )
   {
      expandFlag = true;
   }
   if ( png_get_valid(thePngPtr, theInfoPtr, PNG_INFO_tRNS) )
   {
      expandFlag = true;
   }

   //---
   // If png_set_packing used:
   // Use 1 byte per pixel in 1, 2, or 4-bit depth files. */
   //---
   bool packingFlag = false;

   if ( (theBitDepth < 8) && (thePngColorType == PNG_COLOR_TYPE_GRAY) )
   {
      packingFlag = true;
   }

   if (expandFlag)
   {
       png_set_expand(thePngPtr);
   }
   if (packingFlag)
   {
      png_set_packing(thePngPtr);
   }

   // Gamma correction.
   //    ossim_float64 gamma;
   //    if (png_get_gAMA(thePngPtr, theInfoPtr, &gamma))
   //    {
   //       png_set_gamma(thePngPtr, display_exponent, gamma);
   //    }

   //---
   // Turn on interlace handling... libpng returns just 1 (ie single pass)
   //  if the image is not interlaced
   //---
   png_set_interlace_handling (thePngPtr);

   //---
   // Update the info structures after the transformations take effect
   //---
   png_read_update_info (thePngPtr, theInfoPtr);

   // We're back on row 0 or first line.
   theCurrentRow = 0;
}

bool ossimPngReader::readPngInit()
{
   if (!theFilePtr)
   {
      return false;
   }

   //---
   // Verify the file is a png by checking the first eight bytes:
   // 0x 89 50 4e 47 0d 0a 1a 0a
   //---
   ossim_uint8 sig[8];
   int incount = (int) fread(sig, 1, 8, theFilePtr);

   if (incount < 8 ||(png_sig_cmp(sig, 0, 8)!=0))
   {
      if (traceDebug())
      {
         ossimNotify(ossimNotifyLevel_DEBUG)
            << "ossimPngReader::open NOTICE:\n"
            << "Not a png file..." << endl;
      }
      
      return false;
   }

   thePngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
                                      NULL,
                                      NULL,
                                      NULL);
   if (!thePngPtr)
   {
      return false; // out of memory...
   }
   
   theInfoPtr = png_create_info_struct(thePngPtr);
   
   if (!theInfoPtr)
   {
      png_destroy_read_struct(&thePngPtr, NULL, NULL);
      return false;   /* out of memory */
   }

   if (setjmp (thePngPtr->jmpbuf))
   {
      ossimNotify(ossimNotifyLevel_WARN)
         << "Error while reading.  File corrupted?  "
         << theImageFile
         << std::endl;
      return false;
   }

   png_init_io(thePngPtr, theFilePtr);
   png_set_sig_bytes(thePngPtr, 8);
   png_read_info(thePngPtr, theInfoPtr);
   

   ossim_uint32 height    = png_get_image_height(thePngPtr, theInfoPtr);
   ossim_uint32 width     = png_get_image_width(thePngPtr, theInfoPtr);
   theBitDepth            = png_get_bit_depth(thePngPtr, theInfoPtr);
   thePngColorType        = png_get_color_type(thePngPtr, theInfoPtr);
   
   theImageRect = ossimIrect(0, 0, width  - 1, height - 1);

   if (theBitDepth == 16)
   {
      // png_set_strip_16 (thePngPtr);
      theBytePerPixelPerBand = 2;
      theOutputScalarType = OSSIM_UINT16;
   }
   else
   {
      theBytePerPixelPerBand = 1;
   }

   // Set the read mode from scalar and color type.
   if (theOutputScalarType == OSSIM_UINT8)
   {
      if ( (thePngColorType == PNG_COLOR_TYPE_RGB_ALPHA) ||
           (thePngColorType == PNG_COLOR_TYPE_GRAY_ALPHA) )
      {
         theReadMode = ossimPngRead8a;
      }
      else
      {
         theReadMode = ossimPngRead8;
      }
   }
   else
   {
      if ( (thePngColorType == PNG_COLOR_TYPE_RGB_ALPHA) ||
           (thePngColorType == PNG_COLOR_TYPE_GRAY_ALPHA) )
      {
         theReadMode = ossimPngRead16a;
      }
      else
      {
         theReadMode = ossimPngRead16;
      }

      // Set the swap flag.  PNG stores data in network byte order(big endian).
      if(ossim::byteOrder() == OSSIM_LITTLE_ENDIAN)
      {
         theSwapFlag = true;
      }
   }

   //---
   // If png_set_expand used:
   // Expand data to 24-bit RGB, or 8-bit grayscale,
   // with alpha if available.
   //---
   bool expandFlag = false;

   if ( thePngColorType == PNG_COLOR_TYPE_PALETTE )
   {
      expandFlag = true;
   }
   if ( (thePngColorType == PNG_COLOR_TYPE_GRAY) && (theBitDepth < 8) )
   {
      expandFlag = true;
   }
   if ( png_get_valid(thePngPtr, theInfoPtr, PNG_INFO_tRNS) )
   {
      expandFlag = true;
   }

   //---
   // If png_set_packing used:
   // Use 1 byte per pixel in 1, 2, or 4-bit depth files. */
   //---
   bool packingFlag = false;

   if ( (theBitDepth < 8) && (thePngColorType == PNG_COLOR_TYPE_GRAY) )
   {
      packingFlag = true;
   }

   if (expandFlag)
   {
       png_set_expand(thePngPtr);
   }
   if (packingFlag)
   {
      png_set_packing(thePngPtr);
   }

   // Gamma correction.
   // ossim_float64 gamma;
   // if (png_get_gAMA(thePngPtr, theInfoPtr, &gamma))
   // {
   //    png_set_gamma(png_ptr, display_exponent, gamma);
   // }

   //---
   // Turn on interlace handling... libpng returns just 1 (ie single pass)
   //  if the image is not interlaced
   //---
   theInterlacePasses = png_set_interlace_handling (thePngPtr);

   //---
   // Update the info structures after the transformations take effect
   //---
   png_read_update_info (thePngPtr, theInfoPtr);

   // TODO:
   // Add check for image offsets.
   // Add check for resolution.
   // Add check for colormap.

   switch (thePngColorType)
   {
      case PNG_COLOR_TYPE_RGB:           /* RGB */
         theNumberOfInputBands  = 3;
         theNumberOfOutputBands = 3;
         break;
         
      case PNG_COLOR_TYPE_RGB_ALPHA:     /* RGBA */
         theNumberOfInputBands  = 4;
         theNumberOfOutputBands = 3;
         break;
         
      case PNG_COLOR_TYPE_GRAY:          /* Grayscale */
         theNumberOfInputBands = 1;
         theNumberOfOutputBands = 1;
         break;
         
      case PNG_COLOR_TYPE_GRAY_ALPHA:    /* Grayscale + alpha */
         theNumberOfInputBands = 2;
         theNumberOfOutputBands = 1;
        break;
        
     case PNG_COLOR_TYPE_PALETTE:       /* Indexed */
        theNumberOfInputBands  = 3;
        theNumberOfOutputBands = 3;
        break;
        
     default:                   /* Aie! Unknown type */
        return false;
   }

   theLineBufferSizeInBytes = png_get_rowbytes(thePngPtr, theInfoPtr);

   // Set the max pixel value.
   setMaxPixelValue();

   // Set to OSSIM_USHORT11 for use of specialized tile.
   if (theMaxPixelValue[0] == 2047.0)
   {
      theOutputScalarType = OSSIM_USHORT11;
   }

   if (traceDebug())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << "ossimPngReader::readPngInit DEBUG:"
         << "\ntheImageRect:                     " << theImageRect
         << "\ntheBitDepth:                      " << int(theBitDepth)
         << "\nthePngColorType:                  "
         <<  getPngColorTypeString().c_str()
         << "\ntheNumberOfInputBands:            " << theNumberOfInputBands
         << "\ntheNumberOfOutputBands:           " << theNumberOfOutputBands
         << "\ntheBytePerPixelPerBand:           " << theBytePerPixelPerBand
         << "\ntheLineBufferSizeInBytes:         " << theLineBufferSizeInBytes
         << "\ntheInterlacePasses:               " << theInterlacePasses
         << "\npalette expansion:                "
         << (expandFlag?"on":"off")
         << "\npacking (1,2,4 bit to one byte):  "
         << (packingFlag?"on":"off")
         << "\ntheReadMode:                      " << theReadMode
         << "\ntheSwapFlag:                      " << theSwapFlag
         << std::endl;

      for (ossim_uint32 band = 0; band < theNumberOfInputBands; ++band)
      {
         ossimNotify(ossimNotifyLevel_DEBUG)
            << "max[" << band << "]:  " << theMaxPixelValue[band]
            << std::endl;
      }
   }

   // We're on row 0 or first line.
   theCurrentRow = 0;

   return true;
}

void ossimPngReader::readPngVersionInfo()
{
   ossimNotify(ossimNotifyLevel_WARN)
      << "ossimPngReader::readPngVersionInfo\nCompiled with:"
      << "\nlibpng " << PNG_LIBPNG_VER_STRING
      << " using libpng " << PNG_LIBPNG_VER
      << "\nzlib " << ZLIB_VERSION " using zlib "
      << zlib_version << std::endl;
}

ossimString ossimPngReader::getPngColorTypeString() const
{
   ossimString result = "unknown";
   if (thePngColorType == PNG_COLOR_TYPE_GRAY)
   {
      return ossimString("PNG_COLOR_TYPE_GRAY");
   }
   else if (thePngColorType == PNG_COLOR_TYPE_PALETTE)
   {
      return ossimString("PNG_COLOR_TYPE_PALETTE");
   }
   else if (thePngColorType == PNG_COLOR_TYPE_RGB)
   {
      return ossimString("PNG_COLOR_TYPE_RGB");
   }
   else if (thePngColorType == PNG_COLOR_TYPE_RGB_ALPHA)
   {
      return ossimString("PNG_COLOR_TYPE_RGB_ALPHA");
   }
   else if (thePngColorType == PNG_COLOR_TYPE_GRAY_ALPHA)
   {
      return ossimString("PNG_COLOR_TYPE_GRAY_ALPHA");
   }

   return ossimString("unknown");
}

void ossimPngReader::setMaxPixelValue()
{
   ossim_uint32 band;
   theMaxPixelValue.resize(theNumberOfInputBands);
   for (band = 0; band < theNumberOfInputBands; ++band)
   {
      theMaxPixelValue[band] = 0.0;
   }
   
   if (png_get_valid(thePngPtr, theInfoPtr, PNG_INFO_sBIT ))
   {
      png_color_8p sig_bit;
      png_get_sBIT(thePngPtr, theInfoPtr, &sig_bit);
      if (traceDebug())
      {
         ossimNotify(ossimNotifyLevel_DEBUG)
            << "ossimPngReader::setMaxPixelValue DEBUG:"
            << "\nsig_bit->red:   " << int(sig_bit->red)
            << "\nsig_bit->green: " << int(sig_bit->green)
            << "\nsig_bit->blue:  " << int(sig_bit->blue)
            << "\nsig_bit->gray:  " << int(sig_bit->gray)            
            << "\nsig_bit->alpa:  " << int(sig_bit->alpha)
            << endl;
      }
      switch (thePngColorType)
      {
         case PNG_COLOR_TYPE_RGB:           /* RGB */
            theMaxPixelValue[0] = pow(2.0, double(sig_bit->red))-1.0;
            theMaxPixelValue[1] = pow(2.0, double(sig_bit->green))-1.0;
            theMaxPixelValue[2] = pow(2.0, double(sig_bit->blue))-1.0;
            break;
         case PNG_COLOR_TYPE_RGB_ALPHA:     /* RGBA */
            theMaxPixelValue[0] = pow(2.0, double(sig_bit->red))-1.0;
            theMaxPixelValue[1] = pow(2.0, double(sig_bit->green))-1.0;
            theMaxPixelValue[2] = pow(2.0, double(sig_bit->blue))-1.0;
            theMaxPixelValue[3] = pow(2.0, double(sig_bit->alpha))-1.0;
            break;
         case PNG_COLOR_TYPE_GRAY:          /* Grayscale */
            theMaxPixelValue[0] = pow(2.0, double(sig_bit->gray))-1.0;
            break;
         case PNG_COLOR_TYPE_GRAY_ALPHA:    /* Grayscale + alpha */            
            theMaxPixelValue[0] = pow(2.0, double(sig_bit->gray))-1.0;
            theMaxPixelValue[1] = pow(2.0, double(sig_bit->alpha))-1.0;
            break;
         case PNG_COLOR_TYPE_PALETTE:       /* Indexed */
            theMaxPixelValue[0] = 255.0;
            theMaxPixelValue[1] = 255.0;
            theMaxPixelValue[2] = 255.0;
            break;
         default:                   /* Aie! Unknown type */
            break;
      }
   }

   // Sanity check.
   for (ossim_uint32 band = 0; band < theNumberOfInputBands; ++band)
   {
      if (theMaxPixelValue[band] == 0.0)
      {
         if (theBitDepth <= 8)
         {
            theMaxPixelValue[band] = 255.0;
         }
         else
         {
            theMaxPixelValue[band] = 65535.0;
         }
      }
   }
}

template <class T>  void ossimPngReader::copyLines(
   T /*dummy*/,  ossim_uint32 stopLine)
{
   const ossim_uint32 SAMPLES = theImageRect.width();

   T* src = (T*)theLineBuffer;
   std::vector<T*> dst(theNumberOfOutputBands);

   ossim_uint32 band = 0;
   for (band = 0; band < theNumberOfOutputBands; ++band)
   {
      dst[band] = (T*) theCacheTile->getBuf(band);
   }
   
   ossim_int32 bufIdx = 0;
   
   while (theCurrentRow <= stopLine)
   {
      // Read a line from the jpeg file.
      png_read_row(thePngPtr, theLineBuffer, NULL);
      ++theCurrentRow;

      if(theSwapFlag)
      {
         ossimEndian endian;
         endian.swap(src, SAMPLES*theNumberOfInputBands);
      }

      //---
      // Copy the line which is band interleaved by pixel the the band
      // separate buffers.
      //---
      ossim_uint32 index = 0;
      for (ossim_uint32 sample = 0; sample < SAMPLES; ++sample)
      {
         for (band = 0; band < theNumberOfOutputBands; ++band)
         {
            dst[band][bufIdx] = src[index];
            ++index;
         }
         ++bufIdx;
      }
   }
}

template <class T> void ossimPngReader::copyLinesWithAlpha(
   T, ossim_uint32 stopLine)
{
   ossim_float64 denominator;
   if (theOutputScalarType == OSSIM_UINT8)
   {
      denominator = theMaxPixelValue[theNumberOfInputBands-1];
   }
   else
   {
      denominator = theMaxPixelValue[theNumberOfInputBands-1];
   }

   const ossim_uint32 SAMPLES = theImageRect.width();
   
   T* src = (T*) theLineBuffer;

   std::vector<T*> dst(theNumberOfOutputBands);
   std::vector<T> p(theNumberOfOutputBands);
   
   ossim_float64 alpha;

   const ossim_float64 MIN_PIX  = theCacheTile->getMinPix(0);
   const ossim_float64 MAX_PIX  = theCacheTile->getMaxPix(0);
   const ossim_float64 NULL_PIX = theCacheTile->getNullPix(0);
 
   ossim_uint32 band = 0;
   for (band = 0; band < theNumberOfOutputBands; ++band)
   {
      dst[band] = (T*)theCacheTile->getBuf(band);
   }

   ossim_int32 dstIdx = 0;
   
   while (theCurrentRow <= stopLine)
   {
      // Read a line from the jpeg file.
      png_read_row(thePngPtr, theLineBuffer, NULL);
      ++theCurrentRow;

      if(theSwapFlag)
      {
         ossimEndian endian;
         endian.swap(src, SAMPLES*theNumberOfInputBands);
      }
      
      //---
      // Copy the line which is band interleaved by pixel the the band
      // separate buffers.
      //---
      ossim_uint32 srcIdx = 0;
      for (ossim_uint32 sample = 0; sample < SAMPLES; ++sample)
      {
         // Copy the pixels.
         for (band = 0; band < theNumberOfOutputBands; ++band)
         {
            p[band] = src[srcIdx++];
         }
         
         // Get the alpha channel.
         alpha = src[srcIdx++];
         alpha = alpha / denominator;
         
         if (alpha == 1.0)
         {
            for (band = 0; band < theNumberOfOutputBands; ++band)
            {
               dst[band][dstIdx] = p[band];
            }
         }
         else if (alpha == 0.0)
         {
            for (band = 0; band < theNumberOfOutputBands; ++band)
            {
               dst[band][dstIdx] = static_cast<T>(NULL_PIX);
            }
         }
         else
         {
            for (band = 0; band < theNumberOfOutputBands; ++band)
            {
               ossim_float64 f = p[band];
               f = f * alpha;
               if (f != NULL_PIX)
               {
                  dst[band][dstIdx] =
                     static_cast<T>( (f>=MIN_PIX) ?
                                     ( (f<=MAX_PIX) ? f : MAX_PIX ) :
                                     MIN_PIX );
               }
               else
               {
                  dst[band][dstIdx] = static_cast<T>(NULL_PIX);
               }
            }
         }
         ++dstIdx; // next sample...
            
      } // End of sample loop.
      
   } // End of line loop.
}

