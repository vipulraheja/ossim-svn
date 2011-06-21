//----------------------------------------------------------------------------
//
// License:  See top level LICENSE.txt file
//
// Author:  David Burken
//
// Description: OSSIM Open JPEG (j2k) reader (tile source).
//
//----------------------------------------------------------------------------
// $Id: ossimOpenJpegReader.cpp 11439 2007-07-29 17:43:24Z dburken $

#include <fstream>

#include <ossimOpenJpegReader.h>
#include <ossimOpenJpegDecoder.h>

#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimCommon.h>
#include <ossim/base/ossimException.h>

#include <ossim/imaging/ossimTiffTileSource.h>
#include <ossim/imaging/ossimImageDataFactory.h>

#include <ossim/base/ossimIpt.h>
#include <ossim/base/ossimDpt.h>
#include <ossim/base/ossimEndian.h>
#include <ossim/base/ossimIrect.h>
#include <ossim/base/ossimFilename.h>
#include <ossim/base/ossimKeywordlist.h>
#include <ossim/imaging/ossimU8ImageData.h>
#include <ossim/base/ossimTrace.h>
#include <ossim/base/ossimNotifyContext.h>


RTTI_DEF1(ossimOpenJpegReader, "ossimOpenJpegReader", ossimImageHandler)

#ifdef OSSIM_ID_ENABLED
   static const char OSSIM_ID[] = "$Id: ossimOpenJpegReader.cpp 11439 2007-07-29 17:43:24Z dburken $";
#endif
   
static ossimTrace traceDebug(ossimString("ossimOpenJpegReader:degug"));

static const ossim_uint16 SOC_MARKER = 0xff4f; // start of codestream

ossimOpenJpegReader::ossimOpenJpegReader()
   :
   ossimImageHandler(),
   theTile(0),
   theImage(0)
{
   if (traceDebug())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << "ossimOpenJpegReader::ossimOpenJpegReader entered..." << std::endl;
#ifdef OSSIM_ID_ENABLED
      ossimNotify(ossimNotifyLevel_DEBUG)
         << "OSSIM_ID:  " << OSSIM_ID << endl;
#endif
   }
}

ossimOpenJpegReader::~ossimOpenJpegReader()
{
   destroy();
}

void ossimOpenJpegReader::destroy()
{
   theTile  = 0;  // ossimRefPtr
   theImage = 0;  // ossimRefPtr
}

ossimRefPtr<ossimImageData> ossimOpenJpegReader::getTile(
   const ossimIrect& tile_rect, ossim_uint32 resLevel)
{
   if(!isSourceEnabled()||!isOpen()||!isValidRLevel(resLevel))
   {
      return ossimRefPtr<ossimImageData>();
   }
   
   if (theOverview.valid() && resLevel)
   {
      ossimRefPtr<ossimImageData> t = theOverview->getTile(tile_rect,
                                                           resLevel);
      if ( t.valid() )
      {
         if(theImage->getScalarType() == OSSIM_UINT16)
         {
            //---
            // Temp fix:
            // The overview handler could return a tile of OSSIM_USHORT11 if
            // the max sample value was not set to 2047.
            //
            // To prevent a scalar mismatch set 
            //---
            t->setScalarType(theImage->getScalarType());
         }
         return t;
      }
   }
   
   if (!theTile.valid())
   {
      return ossimRefPtr<ossimImageData>();
   }

   theTile->setImageRectangle(tile_rect);

   ossimIrect imageRect = theImage->getImageRectangle();
   
   if ( ! tile_rect.completely_within(imageRect) )
   {
      // We won't fill totally so make blank first.
      theTile->makeBlank();
   }

   if ( tile_rect.intersects(imageRect) )
   {
      // Make a clip rect.
      ossimIrect clip_rect = tile_rect.clipToRect(imageRect);

      theTile->loadTile(theImage.get()->getBuf(),
                        imageRect,
                        clip_rect,
                        OSSIM_BSQ);
      theTile->validate();
   }

   return theTile;
}

ossimIrect
ossimOpenJpegReader::getImageRectangle(ossim_uint32 reduced_res_level) const
{
   return ossimIrect(0,
                     0,
                     getNumberOfSamples(reduced_res_level) - 1,
                     getNumberOfLines(reduced_res_level)   - 1);
}

bool ossimOpenJpegReader::saveState(ossimKeywordlist& kwl,
                               const char* prefix) const
{
   return ossimImageHandler::saveState(kwl, prefix);
}

bool ossimOpenJpegReader::loadState(const ossimKeywordlist& kwl,
                               const char* prefix)
{
   if (ossimImageHandler::loadState(kwl, prefix))
   {
      return open();
   }

   return false;
}

bool ossimOpenJpegReader::open()
{
   static const char MODULE[] = "ossimOpenJpegReader::open";

   if (traceDebug())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << MODULE << "entered..."
         << "\nFile:  " << theImageFile.c_str()
         << std::endl;
   }

   // Open the file.
   std::ifstream in(theImageFile.c_str(), std::ios::in|std::ios::binary);
   if (!in)
   {
      return false;
      
      // std::string errorMessage = "Could not open file ";
      // errorMessage += imageFile.c_str();
      // throw ossimException(errorMessage);
   }

   //---
   // Check for the Start Of Codestream (SOC) Marker required as first
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
      return false;
      
      // std::string errorMessage = "Magic number wrong.  Is this a j2k?";
      // throw ossimException(errorMessage);
   }

   theSizRecord.parseStream(in);
   if (traceDebug())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << "DEBUG:"
         << "\nSIZ marker segment"
         << theSizRecord
         << std::endl;
   }
    
   ossimOpenJpegDecoder decoder;
   try
   {
      // theImage = decoder.decode(theImageFile);
   }
   catch (const ossimException& e)
   {
      if (traceDebug())
      {
         ossimNotify(ossimNotifyLevel_DEBUG)
            << MODULE
            << "Caught exception: " << e.what()
            << std::endl;
      }
      return false;
   }
   
   theTile = ossimImageDataFactory::instance()->create(this, this);
   theTile->initialize();
   if (traceDebug())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << MODULE
         << "\ntheImage:\n" << *(theImage.get())
         << "\ntheTile:\n"  <<  *(theTile.get())
         << std::endl;
   }
   return true;
}

void ossimOpenJpegReader::close()
{
   destroy();
   ossimImageHandler::close();
   
}

ossim_uint32 ossimOpenJpegReader::getTileWidth() const
{
   return ( theTile.valid() ? theTile->getWidth() : 0 );
}

ossim_uint32 ossimOpenJpegReader::getTileHeight() const
{
   return ( theTile.valid() ? theTile->getHeight() : 0 );
}

ossim_uint32 ossimOpenJpegReader::getNumberOfLines(
   ossim_uint32 reduced_res_level) const
{
   if (reduced_res_level == 0)
   {
      return theSizRecord.theYsiz;
   }
   else if (theOverview.valid())
   {
      return theOverview->getNumberOfLines(reduced_res_level);
   }
   return 0;
}

ossim_uint32 ossimOpenJpegReader::getNumberOfSamples(
   ossim_uint32 reduced_res_level) const
{
   if (reduced_res_level == 0)
   {
      return theSizRecord.theXsiz;
   }
   else if (theOverview.valid())
   {
      return theOverview->getNumberOfSamples(reduced_res_level);
   }
   return 0;
}

ossim_uint32 ossimOpenJpegReader::getImageTileWidth() const
{
   return theSizRecord.theXTsiz;
}

ossim_uint32 ossimOpenJpegReader::getImageTileHeight() const
{
   return theSizRecord.theYTsiz;
}

ossimString ossimOpenJpegReader::getShortName()const
{
   return ossimString("ossim_openjpeg_reader");
}
   
ossimString ossimOpenJpegReader::getLongName()const
{
   return ossimString("ossim open jpeg reader");
}

ossimString  ossimOpenJpegReader::getClassName()const
{
   return ossimString("ossimOpenJpegReader");
}

ossim_uint32 ossimOpenJpegReader::getNumberOfInputBands() const
{
   return theSizRecord.theCsiz;
}

ossim_uint32 ossimOpenJpegReader::getNumberOfOutputBands()const
{
   return theSizRecord.theCsiz;
}

ossimScalarType ossimOpenJpegReader::getOutputScalarType() const
{
   return theSizRecord.getScalarType();
}

bool ossimOpenJpegReader::isOpen()const
{
   if (theImage.valid())
   {
      return true;
   }
   return false;
}

double ossimOpenJpegReader::getMaxPixelValue(ossim_uint32 band)const
{
   if (theImage.valid())
   {
      return theImage->getMaxPix(band);
   }
   return 255.0;
}
