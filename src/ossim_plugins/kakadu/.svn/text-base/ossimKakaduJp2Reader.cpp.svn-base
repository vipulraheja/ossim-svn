//----------------------------------------------------------------------------
//
// License:  LGPL
// 
// See LICENSE.txt file in the top level directory for more details.
//
// Description:  Class definition for JPEG2000 JP2 reader.
//
//----------------------------------------------------------------------------
// $Id$

#include "ossimKakaduJp2Reader.h"
#include "ossimKakaduCommon.h"
#include "ossimKakaduMessaging.h"
 
#include <ossim/base/ossimCommon.h>
#include <ossim/base/ossimDpt.h>
#include <ossim/base/ossimEndian.h>
#include <ossim/base/ossimException.h>
#include <ossim/base/ossimKeywordlist.h>
#include <ossim/base/ossimNotify.h>
#include <ossim/base/ossimPreferences.h>
#include <ossim/base/ossimScalarTypeLut.h>
#include <ossim/base/ossimTrace.h>
#include <ossim/base/ossimUnitConversionTool.h>
 
#include <ossim/imaging/ossimImageDataFactory.h>
#include <ossim/imaging/ossimImageGeometryRegistry.h>

#include <ossim/projection/ossimMapProjection.h>
#include <ossim/projection/ossimProjection.h>
#include <ossim/projection/ossimProjectionFactoryRegistry.h>

#include <ossim/support_data/ossimFgdcXmlDoc.h>
#include <ossim/support_data/ossimJ2kSizRecord.h>
#include <ossim/support_data/ossimJ2kSotRecord.h>
#include <ossim/support_data/ossimTiffInfo.h>
#include <ossim/support_data/ossimTiffWorld.h>

#include <jp2.h>
#include <kdu_compressed.h> 
#include <kdu_sample_processing.h>
#include <kdu_region_decompressor.h>

#include <fstream>
#include <iostream>
#include <string>

#ifdef OSSIM_ID_ENABLED
static const char OSSIM_ID[] = "$Id";
#endif
 
static ossimTrace traceDebug("ossimKakaduJp2Reader:debug");
static ossimTrace traceDump("ossimKakaduJp2Reader:dump");

static const ossim_uint16 SOC_MARKER = 0xff4f; // start of codestream marker
static const ossim_uint16 SIZ_MARKER = 0xff51; // size maker

RTTI_DEF1_INST(ossimKakaduJp2Reader,
               "ossimKakaduJp2Reader",
               ossimImageHandler)
 
ossimKakaduJp2Reader::ossimKakaduJp2Reader()
   : ossimImageHandler(),
     theJp2FamilySrc(0),
     theJp2Source(0),
     theChannels(0),
     theCodestream(),
     theThreadEnv(0),
     theOpenTileThreadQueue(0),
     theMinDwtLevels(0),
     theNumberOfBands(0),
     theCacheSize(0, 0),
     theScalarType(OSSIM_SCALAR_UNKNOWN),
     theImageRect(),
     theJp2Dims(0),
     theJp2TileDims(0),
     theTile(),
     theCacheTile(),
     theCacheId(-1)
{
   kdu_customize_warnings(&pretty_cout); // Deliver warnings to stdout.
   kdu_customize_errors(&pretty_cerr); // Deliver errors to stderr + throw exc
}

ossimKakaduJp2Reader::~ossimKakaduJp2Reader()
{
   closeEntry();
}

ossimString ossimKakaduJp2Reader::getShortName()const
{
   return ossimString("ossim_kakadu_jp2_reader");
}

ossimString ossimKakaduJp2Reader::getLongName()const
{
   return ossimString("ossim kakadu jp2 reader");
}

ossimString ossimKakaduJp2Reader::getClassName()const
{
   return ossimString("ossimKakaduJp2Reader");
}

ossim_uint32 ossimKakaduJp2Reader::getNumberOfDecimationLevels()const
{
   ossim_uint32 result = 1; // Add r0

   if (theMinDwtLevels)
   {
      //---
      // Add internal overviews.
      //---
      result += theMinDwtLevels;
   }

   if (theOverview.valid())
   {
      //---
      // Add external overviews.
      //---
      result += theOverview->getNumberOfDecimationLevels();
   }

   return result;
}

ossim_uint32 ossimKakaduJp2Reader::getNumberOfLines(
   ossim_uint32 resLevel) const
{
   ossim_uint32 result = 0;
   if ( isValidRLevel(resLevel) )
   {
      if (resLevel <= theMinDwtLevels)
      {
         result = theJp2Dims[resLevel].height();
      }
      else if (theOverview.valid())
      {
         result = theOverview->getNumberOfLines(resLevel);
      }
   }
   return result;
}

ossim_uint32 ossimKakaduJp2Reader::getNumberOfSamples(
   ossim_uint32 resLevel) const
{
   ossim_uint32 result = 0;
   if ( isValidRLevel(resLevel) )
   {
      if (resLevel <= theMinDwtLevels)
      {
         result = theJp2Dims[resLevel].width();
      }
      else if (theOverview.valid())
      {
         result = theOverview->getNumberOfSamples(resLevel);
      }
   }
   return result;
}

bool ossimKakaduJp2Reader::open()
{
   static const char MODULE[] = "ossimKakaduJp2Reader::open";

   if (traceDebug())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << MODULE << " entered...\n"
         << "image: " << theImageFile << "\n";
   }
   
   bool result = false;
   
   if(isOpen())
   {
      closeEntry();
   }

   if ( isJp2() )
   {
      result = openJp2File();

      if ( !result )
      {
         closeEntry();
      }
   }

   if (traceDebug())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << MODULE << " exit status = " << (result?"true":"false\n")
         << std::endl;
   }

   return result;
}

bool ossimKakaduJp2Reader::isJp2()
{
   bool result = true;

   std::ifstream str;
   str.open(theImageFile.chars(), ios::in | ios::binary);

   if ( str.is_open() )
   {
      const ossim_uint8 J2K_SIGNATURE_BOX[SIGNATURE_BOX_SIZE] = 
         {0x00,0x00,0x00,0x0c,0x6a,0x50,0x20,0x20,0x0d,0x0a,0x87,0x0a};
      
      ossim_uint8 box[SIGNATURE_BOX_SIZE];
      
      // Read in the box.
      str.read((char*)box, SIGNATURE_BOX_SIZE);
      
      for (ossim_uint32 i = 0; i < SIGNATURE_BOX_SIZE; ++i)
      {
         if (box[i] != J2K_SIGNATURE_BOX[i])
         {
            result = false;
            break;
         }
      }

      str.close();
   }
   else
   {
      result = false;
      
      if(traceDebug())
      {
         ossimNotify(ossimNotifyLevel_DEBUG)
            << "isJp2 ERROR:"
            << "\nCannot open:  " << theImageFile.chars() << endl;
      }
   }
   
   return result;
}

bool ossimKakaduJp2Reader::openJp2File()
{
   static const char MODULE[] = "ossimKakaduJp2Reader::openJp2File";
   
   if (traceDebug())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << MODULE << " entered...\n";
   }

   bool result = false;
   
   theJp2FamilySrc = new jp2_family_src();

   theJp2FamilySrc->open(theImageFile.chars(), true);

   if (theJp2FamilySrc->exists())
   {
      jp2_source* src = new jp2_source();
      theJp2Source = src;
      
      src->open(theJp2FamilySrc);

      src->read_header();

      if (traceDebug())
      {
         jp2_colour colour = src->access_colour();
         if ( colour.exists() )
         {
            ossimNotify(ossimNotifyLevel_DEBUG)
               << "jp2 color space: " << colour.get_space() << std::endl;
         }
      }

      theThreadEnv = new kdu_thread_env();
         
      theThreadEnv->create(); // Creates the single "owner" thread

      ossim_uint32 threads = 1;
      
      const char* lookup = ossimPreferences::instance()->findPreference("kakadu_threads");
      if ( lookup )
      {
         threads = ossimString::toUInt32(lookup);
         if ( threads > 1 )
         {
            for (ossim_uint32 nt=1; nt < threads; ++nt)
            {
               if ( !theThreadEnv->add_thread() )
               {
                  if (traceDebug())
                  {
                     ossimNotify(ossimNotifyLevel_WARN)
                        << "Unable to create thread!\n";
                  }
               }
            }
         }
      }

      theOpenTileThreadQueue =
         theThreadEnv->add_queue(NULL,NULL,"open_tile_q");
         
      theCodestream.create(theJp2Source, theThreadEnv);
         
      if ( theCodestream.exists() )
      {
         // This must be done before anything else...
         theCodestream.set_persistent();
         
         theCodestream.enable_restart(); // ????
         
         // Get the image and tile dimensions.
         if ( ossim::getCodestreamDimensions(theCodestream,
                                             theJp2Dims,
                                             theJp2TileDims) )
         {
            //---
            // Set the image size.
            //
            // NOTE:
            //
            // The geojp2 doqq's that I have all have an offset in them.  In
            // other words the "pos" from "get_dims" is not always 0,0.  I
            // think this was intended for mosaicing without any projection. I
            // do NOT think it was intended to be used as a sub image offset
            // into the projection picked up by the geotiff_box. If this were
            // so the current code here would not mosaic correctly.
            //
            // This may not be the case though with all data sets...  In which
            // case some kind of logic would have to be added to this code.
            //---
            theImageRect = ossimIrect( 0,
                                       0,
                                       theJp2Dims[0].width() -1,
                                       theJp2Dims[0].height()-1);
            
            // Number of internal dwl layers
            theMinDwtLevels = theCodestream.get_min_dwt_levels();

            // Get the number of bands.
            theNumberOfBands =
               static_cast<ossim_uint32>(theCodestream.
                                         get_num_components(true));
            
            //---
            // Set the cache tile size.  Use the internal j2k tile size if it's
            // reasonable else clamp to some max.  Some j2k writer make one
            // BIG tile so this must be done.
            //---
            const ossim_uint32 MAX_CACHE_TILE_DIMENSION = 1024;
            theCacheSize.x =
               static_cast<ossim_int32>(
                  (theJp2TileDims[0].width() <= MAX_CACHE_TILE_DIMENSION) ?
                  theJp2TileDims[0].width() : MAX_CACHE_TILE_DIMENSION );
            theCacheSize.y =
               static_cast<ossim_int32>(
                  (theJp2TileDims[0].height() <= MAX_CACHE_TILE_DIMENSION) ?
                  theJp2TileDims[0].height() : MAX_CACHE_TILE_DIMENSION );
            
            // Set the scalar:
            int bitDepth   = theCodestream.get_bit_depth(0, true);
            bool isSigned  = theCodestream.get_signed(0, true);

            switch (bitDepth)
            {
               case 8:
               {
                  theScalarType = OSSIM_UINT8;
                  break;
               }
               case 11:
               {
                  if (!isSigned)
                  {
                     theScalarType = OSSIM_USHORT11;
                  }
                  else
                  {
                     theScalarType = OSSIM_SINT16;
                  }
                  break;
               }
               case 16:
               {
                  if (!isSigned)
                  {
                     theScalarType = OSSIM_UINT16;
                  }
                  else
                  {
                     theScalarType = OSSIM_SINT16;
                  }
                  break;
               }
               default:
               {
                  theScalarType = OSSIM_SCALAR_UNKNOWN;
                  break;
               }
            }
            
            if (theScalarType != OSSIM_SCALAR_UNKNOWN)
            {
               // Initialize the cache.
               if (theCacheId != -1)
               {
                  ossimAppFixedTileCache::instance()->deleteCache(theCacheId);
                  theCacheId = -1;
               }
               
               ossimIrect fullImgRect = theImageRect;
               fullImgRect.stretchToTileBoundary(theCacheSize);

               theCacheId = ossimAppFixedTileCache::instance()->
                  newTileCache(fullImgRect, theCacheSize);
               
               // Initialize the tile we will return.
               initializeTile();
               
               // Call the base complete open to pick up overviews.
               completeOpen();

               // Set up channel mapping for copyRegionToTile if it makes sense.
               configureChannelMapping();

               // We should be good now so set the return result to true.
               result = true;
               
               if (traceDebug())
               {
                  ossim::print(ossimNotify(ossimNotifyLevel_DEBUG),
                               theCodestream);
                  ossimNotify(ossimNotifyLevel_DEBUG)
                     << "\ntheImageRect:      " << theImageRect
                     << "\nFull image rect:   " << fullImgRect
                     << "\ntheCacheSize:  " << theCacheSize
                     << "\nscalar type:       "
                     << ossimScalarTypeLut::instance()->
                     getEntryString(theScalarType)
                     << "\n";
                  
                  for (ossim_uint32 level=0;
                       level < theJp2Dims.size(); ++level)
                  {
                     ossimNotify(ossimNotifyLevel_DEBUG)
                        << "theJp2Dims[" << level << "]: "
                        << theJp2Dims[level]
                        << "\ntheJp2TileDims[" << level << "]: "
                        << theJp2TileDims[level] << "\n";
                  }
                  ossimNotify(ossimNotifyLevel_DEBUG)
                     << "threads: " << threads << endl;
               }
               
            } // if (theScalarType != OSSIM_SCALAR_UNKNOWN)

         } // matches: if ( ossim::getCodestreamDimensions
            
      } // matches: if ( theCodestream.exists() )
         
   } //  if (theJp2FamilySrc->exists())

   if (traceDebug())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << MODULE << " exit status = " << (result?"true":"false\n")
         << std::endl;
   }

   return result;      

   if (traceDebug())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << MODULE << " exit status = " << (result?"true":"false\n")
         << std::endl;
   }

   return result;
}

bool ossimKakaduJp2Reader::isOpen()const
{
   return theTile.get();
   
   // return theCodestream.exists()
      // return theFileStr.is_open();
}

void ossimKakaduJp2Reader::closeEntry()
{
   theTile = 0;
   theCacheTile = 0;

   if (theChannels)
   {
      theChannels->clear();
      delete theChannels;
      theChannels = 0;
   }
   if(theCodestream.exists())
   {
      theCodestream.destroy();
   }
   
   if (theJp2Source)
   {
      delete theJp2Source;
      theJp2Source = 0;
   }

   if (theJp2FamilySrc)
   {
      delete theJp2FamilySrc;
      theJp2FamilySrc = 0;
   }
   
   if (theThreadEnv)
   {
      theThreadEnv->terminate(theOpenTileThreadQueue, true);
      theThreadEnv->destroy();
      delete theThreadEnv;
      theThreadEnv = 0;
   }

   if (theOpenTileThreadQueue)
   {
      theOpenTileThreadQueue = 0;
   }

   if (theCacheId != -1)
   {
      ossimAppFixedTileCache::instance()->deleteCache(theCacheId);
      theCacheId = -1;
   }

   ossimImageHandler::close();
}

ossimRefPtr<ossimImageData> ossimKakaduJp2Reader::getTile(
   const ossimIrect& rect, ossim_uint32 resLevel)
{
   // This tile source bypassed, or invalid res level, return null tile.
   if(!isSourceEnabled() || !isOpen() || !isValidRLevel(resLevel))
   {
      return ossimRefPtr<ossimImageData>();
   }

   if (theTile.valid())
   {
      // Rectangle must be set prior to getOverviewTile call.
      theTile->setImageRectangle(rect);

      if (resLevel)
      {
         if ( getOverviewTile(resLevel, theTile.get()) == false )
         {
            theTile->makeBlank();
         }
      }
      else // r0
      {
         // NOTE:  Using cache for r0 tiles.

         //---
         // See if the whole tile is going to be filled, if not, start out with
         // a blank tile so data from a previous load gets wiped out.
         //---
         if ( !rect.completely_within(theImageRect) )
         {
            // Start with a blank tile.
            theTile->makeBlank();
         }
         
         //---
         // See if any point of the requested tile is in the image.
         //---
         if ( rect.intersects(theImageRect) )
         {
            ossimIrect clipRect = rect.clipToRect(theImageRect);

            ossimIrect expandedRect = clipRect;
            expandedRect.stretchToTileBoundary(theCacheSize);

            //---
            // Shift the upper left corner of the "clip_rect" to the an even
            // j2k tile boundry.  
            //---
            ossimIpt tileOrigin = expandedRect.ul();
            
            // Vertical tile loop.
            while (tileOrigin.y < expandedRect.lr().y)
            {
               // Horizontal tile loop.
               while (tileOrigin.x < expandedRect.lr().x)
               {
                  if ( loadTileFromCache(tileOrigin, clipRect) == false )
                  {
                     if ( loadTile(tileOrigin) )
                     {
                        //---
                        // Note: Clip the cache tile to the image clipRect
                        // since there are j2k tiles that go beyond the image
                        // dimensions, i.e., edge tiles.
                        //---    
                        ossimIrect cr =
                           theCacheTile->getImageRectangle().
                           clipToRect(clipRect);
                        
                        theTile->loadTile(theCacheTile->getBuf(),
                                          theCacheTile->getImageRectangle(),
                                          cr,
                                          OSSIM_BSQ);
                     }
                     
                  }
                  
                  tileOrigin.x += theCacheSize.x; // Go to next tile.

               } // End loop in x direction.
               
               // Go to next row of tiles.
               tileOrigin.x = expandedRect.ul().x;
               tileOrigin.y += theCacheSize.y;
               
            }  // End loop in y direction.

            // Set the tile status.
            theTile->validate();
            
         } // matches: if ( rect.intersects(theImageRect) )
         
      } // r0 block
      
   } // matches: if (theTile.valid())

   return theTile;
}

bool ossimKakaduJp2Reader::getOverviewTile(ossim_uint32 resLevel,
                                           ossimImageData* result)
{
   bool status = false;

   if ( (resLevel < getNumberOfDecimationLevels()) && result && 
        (result->getNumberOfBands() == getNumberOfOutputBands()) )
   {
      if (resLevel <= theMinDwtLevels)
      {
         // Using internal overviews.

         //---
         // NOTE:
         //
         // The geojp2 doqq's that I have all have an offset in them.  In
         // other words the "pos" from "get_dims" is not always 0,0.  I
         // think this was intended for mosaicing without any projection. I
         // do NOT think it was intended to be used as a sub image offset
         // into the projection picked up by the geotiff_box. If this were
         // so the current code here would not mosaic correctly.
         //
         // This may not be the case though with all data sets...  In which
         // case some kind of logic would have to be added to this code.
         //---
         ossimIrect originalTileRect = result->getImageRectangle();

         ossimIrect shiftedRect = originalTileRect + theJp2Dims[resLevel].ul();

         result->setImageRectangle(shiftedRect);
         
         try
         {
            if ( theChannels )
            {
               status = ossim::copyRegionToTile(theChannels,
                                                theCodestream,
                                                static_cast<int>(resLevel),
                                                theThreadEnv,
                                                theOpenTileThreadQueue,
                                                result);
            }
            else
            {
               status = ossim::copyRegionToTile(theCodestream,
                                                static_cast<int>(resLevel),
                                                theThreadEnv,
                                                theOpenTileThreadQueue,
                                                result);
            }     
         }
         catch(const ossimException& e)
         {
            ossimNotify(ossimNotifyLevel_WARN)
               << __FILE__ << " " << __LINE__ << " caught exception\n"
               << e.what();
            status = false;
         }
         
         // Set the rect back.
         result->setImageRectangle(originalTileRect);
         
      }  // matches:  if (resLevel <= theMinDwtLevels)
      else
      {
         // Using external overview.
         status = theOverview->getTile(result, resLevel);
      }
   }

   return status;
}

ossim_uint32 ossimKakaduJp2Reader::getNumberOfInputBands() const
{
   return theNumberOfBands;
}

ossim_uint32 ossimKakaduJp2Reader::getNumberOfOutputBands()const
{
   return theNumberOfBands;
}

ossim_uint32 ossimKakaduJp2Reader::getImageTileWidth() const
{
   ossim_uint32 result = 0;
   if ( theJp2TileDims.size() )
   {
      if ( theJp2TileDims[0].width() != theImageRect.width() )
      {
         // Not a single tile.
         result = theJp2TileDims[0].width();
      }
   }
   return result;
}

ossim_uint32 ossimKakaduJp2Reader::getImageTileHeight() const
{
   ossim_uint32 result = 0;
   if ( theJp2TileDims.size() )
   {
      if ( theJp2TileDims[0].height() != theImageRect.height() )
      {
         // Not a single tile.
         result = static_cast<ossim_uint32>(theJp2TileDims[0].height());
      }
   }
   return result;
}

ossimScalarType ossimKakaduJp2Reader::getOutputScalarType() const
{
   return theScalarType;
}
 
void ossimKakaduJp2Reader::initializeTile()
{
   ossim_uint32 width  = this->getImageTileWidth();
   ossim_uint32 height = this->getImageTileHeight();

   // Check for zero width, height and limit output tile sizes to 1024.
   if ( !width || !height || ( width > 1024) || (height > 1024) )
   {
      ossimIpt tileSize;
      ossim::defaultTileSize(tileSize);

      width  = tileSize.x;
      height = tileSize.y;
   }
   
   theTile = ossimImageDataFactory::instance()->
      create( this,
              this->getOutputScalarType(),
              this->getNumberOfOutputBands(),
              width,
              height);

   theTile->initialize();

   theCacheTile = ossimImageDataFactory::instance()->
      create( this,
              this->getOutputScalarType(),
              this->getNumberOfOutputBands(),
              theCacheSize.x,
              theCacheSize.y );
   
   theCacheTile->initialize();
}

bool ossimKakaduJp2Reader::loadTileFromCache(const ossimIpt& origin,
                                             const ossimIrect& clipRect)
{
   bool result = false;
   
   ossimRefPtr<ossimImageData> tempTile =
      ossimAppFixedTileCache::instance()->getTile(theCacheId, origin);
   if (tempTile.valid())
   {
      //---
      // Note: Clip the cache j2k tile to the image clipRect since
      // there are j2k tiles that go beyond the image dimensions, i.e.,
      // edge tiles.
      //---
      ossimIrect cr = tempTile->getImageRectangle().clipToRect(clipRect);

      theTile->loadTile(tempTile.get()->getBuf(),
                        tempTile->getImageRectangle(),
                        cr,
                        OSSIM_BSQ);
      result = true;
   }

   return result;
}

bool ossimKakaduJp2Reader::loadTile(const ossimIpt& origin)
{
   bool result = true;
   
   ossimIpt lr(origin.x + theCacheSize.x - 1,
               origin.y + theCacheSize.y - 1);

   // Set the cache rectangle to be an even j2k tile.
   theCacheTile->setImageRectangle(ossimIrect(origin, lr));

   // Let the getOverviewTile do the rest of the work.
   if ( getOverviewTile(0, theCacheTile.get()) )
   {
      // Add it to the cache for the next time.
      ossimAppFixedTileCache::instance()->addTile(theCacheId, theCacheTile);
   }
   else
   {
      ossimNotify(ossimNotifyLevel_WARN)
         << __FILE__ << __LINE__
         << " ossimKakaduJp2Reader::loadBlock failed!"
         << std::endl;
      result = false;
   }
   
   return result;
}

ossimRefPtr<ossimImageGeometry> ossimKakaduJp2Reader::getImageGeometry()
{
   if ( !theGeometry )
   {
      //---
      // Check for external geom - this is a file.geom not to be confused with
      // geometries picked up from dot.xml, dot.prj, dot.j2w and so on.  We
      // will check for that later if the getInternalImageGeometry fails.
      //---
      theGeometry = getExternalImageGeometry();
      
      if ( !theGeometry )
      {
         //---
         // Check for external files other than .geom, i.e. file.xml & j2w:
         //---
         theGeometry = getMetadataImageGeometry();

         if ( !theGeometry )
         {
            // Check the internal geometry first to avoid a factory call.
            theGeometry = getInternalImageGeometry();

            //---
            // WARNING:
            // Must create/set the geometry at this point or the next call to
            // ossimImageGeometryRegistry::extendGeometry will put us in an infinite loop
            // as it does a recursive call back to ossimImageHandler::getImageGeometry().
            //---
            if ( !theGeometry )
            {
               theGeometry = new ossimImageGeometry();
            }
            
            // Check for set projection.
            if ( !theGeometry->getProjection() )
            {
               // Last try factories for projection.
               ossimImageGeometryRegistry::instance()->extendGeometry(this);
            }
         }
      }

      // Set image things the geometry object should know about.
      initImageParameters( theGeometry.get() );
   }
   return theGeometry;
}

ossimRefPtr<ossimImageGeometry> ossimKakaduJp2Reader::getInternalImageGeometry() const
{
   static const char MODULE[] = "ossimKakaduJp2Reader::getInternalImageGeometry";
   if (traceDebug())
   {
      ossimNotify(ossimNotifyLevel_DEBUG) << MODULE << " entered...\n";
   }

   ossimRefPtr<ossimImageGeometry> geom = 0;

   // Look for the GeoTIFF Box
   std::ifstream str;
   str.open(theImageFile.chars(), ios::in | ios::binary);
   
   if ( str.is_open() )
   {
      // Position to start of code file.
      str.seekg(SIGNATURE_BOX_SIZE, std::ios_base::beg);

      // See if we need to byte swap.  JP2 boxes are big endian.
      ossimEndian* swapper = 0;
      if ( ossim::byteOrder() == OSSIM_LITTLE_ENDIAN )
      {
         swapper = new ossimEndian();
      }
      
      ossim_uint32 lbox  = 0;
      ossim_uint32 tbox  = 0;
      ossim_uint64 xlbox = 0;
      
      const ossim_uint32 UUID_TYPE = 0x75756964;

      const ossim_uint8 GEOTIFF_UUID[GEOTIFF_UUID_SIZE] = 
      {
         0xb1, 0x4b, 0xf8, 0xbd,
         0x08, 0x3d, 0x4b, 0x43,
         0xa5, 0xae, 0x8c, 0xd7,
         0xd5, 0xa6, 0xce, 0x03
      };

      while ( str.good() )
      {
         str.read((char*)&lbox, 4);
         str.read((char*)&tbox, 4);
         ossim_uint32 bytesRead = 8;
         if (swapper)
         {
            swapper->swap(lbox);
            swapper->swap(tbox);
         }

         if (tbox == UUID_TYPE)
         {
            // Check for GeoTIFF box.
            
            ossim_uint8 geotiffUuid[GEOTIFF_UUID_SIZE];
            
            // Read in the id.
            str.read((char*)geotiffUuid, GEOTIFF_UUID_SIZE);
            bytesRead += GEOTIFF_UUID_SIZE;
            
            bool foundIt = true;
            for (ossim_uint32 i = 0; i < GEOTIFF_UUID_SIZE; ++i)
            {
               if (geotiffUuid[i] != GEOTIFF_UUID[i])
               {
                  foundIt = false;
                  break;
               }
            }
            
            if ( foundIt )
            {
               //---
               // Feed the stream to the tiff info object to get a keyword
               // list with geometry/projection info.
               //---
               ossimTiffInfo info;

               //---
               // Have geotiff boxes with badly terminated geotiffs. So to keep
               // the tag parser from walking past the first image file directory
               // (IFD) into garbage we will set the process overview flag to false.
               //
               // Note if we ever get multiple entries we will need to take this out.
               //---
               info.setProcessOverviewFlag(false);
               
               ossim_uint32 entry = 0;
               ossimKeywordlist kwl; // Used to capture geometry data. 
               if ( info.getImageGeometry(str, kwl, entry) )
               {
                  //---
                  // The tiff embedded in the geojp2 only has one line
                  // and one sample by design so overwrite the lines and
                  // samples with the real value.
                  //---
                  ossimString pfx = "image";
                  pfx += ossimString::toString(entry);
                  pfx += ".";
                  
                  // Add the lines.
                  kwl.add(pfx.chars(), ossimKeywordNames::NUMBER_LINES_KW,
                          getNumberOfLines(0), true);
                  
                  // Add the samples.
                  kwl.add(pfx.chars(), ossimKeywordNames::NUMBER_SAMPLES_KW,
                          getNumberOfSamples(0), true);
                  
                  // Create the projection.
                  ossimRefPtr<ossimProjection> proj =
                     ossimProjectionFactoryRegistry::instance()->createProjection(kwl, pfx);
                  if ( proj.valid() )
                  {
                     // Create and assign projection to our ossimImageGeometry object.
                     geom = new ossimImageGeometry();
                     geom->setProjection( proj.get() );
                     if (traceDebug())
                     {
                        ossimNotify(ossimNotifyLevel_DEBUG) << "Found GeoTIFF box." << std::endl;
                     }
                  }
               }
               
               break; // Get out of while loop.
            }
         }
         else
         {
            str.read((char*)&xlbox, 8);
            bytesRead += 8;
            if (swapper)
            {
               swapper->swap(xlbox);
            }
         }

         if (lbox == 0) // last box?
         {
            break;
         }
         
         // Seek to the next box.  If xlbox is 1
         std::streamoff seekPos = 0;
         if (lbox == 1)
         {
            seekPos = static_cast<std::streamoff>(xlbox) - static_cast<std::streamoff>(bytesRead);
         }
         else
         {
            seekPos = static_cast<std::streamoff>(lbox) - static_cast<std::streamoff>(bytesRead);
         }
         str.seekg(seekPos,  std::ios_base::cur);

      } // matches: while ( str.good() )
      
      // cleanup
      if (swapper)
      {
         delete swapper; 
         swapper = 0;
      }
      
      // Close the stream.
      str.close();
      
   } // matches: if ( str.is_open() )

   if (traceDebug())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << MODULE << " exit status = " << (geom.valid()?"true":"false\n")
         << std::endl;
   }   
   
   return geom;
}

ossimRefPtr<ossimImageGeometry> ossimKakaduJp2Reader::getMetadataImageGeometry() const
{
   static const char M[] = "ossimKakaduJp2Reader::getMetadataImageGeometry";
   if ( traceDebug() )
   {
      ossimNotify(ossimNotifyLevel_DEBUG) << M << " entered...\n";
   }
   
   ossimRefPtr<ossimImageGeometry> geom = 0;
   ossimRefPtr<ossimProjection>    proj = 0;

   // See if we can pick up the projection from the FGDC file:
   ossimFilename fdgcFile = theImageFile;
   
   fdgcFile += ".xml"; // file.jp2.xml
   if ( fdgcFile.exists() == false ) 
   {
      fdgcFile = theImageFile;
      fdgcFile.setExtension(ossimString("xml")); // file.xml
   }
   
   if ( fdgcFile.exists() )
   {
      ossimFgdcXmlDoc fgdcDoc;
      if ( fgdcDoc.open(fdgcFile) )
      {
         try
         {
            proj = fgdcDoc.getGridCoordSysProjection();
         }
         catch (const ossimException& e)
         {
            ossimNotify(ossimNotifyLevel_WARN) << e.what() << std::endl;
         }

         if ( proj.valid() )
         {
            geom = new ossimImageGeometry();

            ossimMapProjection* mapProj = dynamic_cast<ossimMapProjection*>(proj.get());
            if ( mapProj )
            {
               // See if we have a world file.  Seems they have a more accurate tie point.
               ossimFilename worldFile = theImageFile;
               worldFile.setExtension(ossimString("j2w")); // file.j2w
               if ( worldFile.exists() )
               {
                  //---
                  // Note need a way to determine pixel type from fgdc doc.
                  // This can result in a half pixel shift.
                  //---
                  ossimPixelType pixelType = OSSIM_PIXEL_IS_POINT;
                  ossimUnitType  unitType  = fgdcDoc.getUnitType();
                  
                  ossimTiffWorld tfw;
                  if ( tfw.open(worldFile, pixelType, unitType) )
                  {
                     ossimDpt gsd = tfw.getScale();
                     gsd.y = std::fabs(gsd.y); // y positive up so negate.
                     ossimDpt tie = tfw.getTranslation();
                     
                     if ( unitType != OSSIM_METERS )
                     {
                        ossimUnitConversionTool uct;
                        
                        // GSD (scale):
                        uct.setValue(gsd.x, unitType);
                        gsd.x = uct.getValue(OSSIM_METERS);
                        uct.setValue(gsd.y, unitType);
                        gsd.y = uct.getValue(OSSIM_METERS);
                        
                        // Tie point:
                        uct.setValue(tie.x, unitType);
                        tie.x = uct.getValue(OSSIM_METERS);
                        uct.setValue(tie.y, unitType);
                        tie.y = uct.getValue(OSSIM_METERS);
                     }
                     
                     mapProj->setMetersPerPixel(gsd);
                     mapProj->setUlTiePoints(tie);
                  }
                  
                  if ( tfw.getRotation() != 0.0 )
                  {
                     ossimNotify(ossimNotifyLevel_WARN)
                        << M << " Unhandled rotation in tfw file." << std::endl;
                  }
               }
               
            } // if ( worldFile.exists() )
               
            geom->setProjection( proj.get() );
            
         }  // if ( proj.valid() )
         
      } // if ( fgdcDoc.open(fdgcFile) )
      
   } // if ( fdgcFile.exists() )

   if (traceDebug())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << M << " exit status = " << (geom.valid()?"true":"false\n")
         << std::endl;
   }   
   
   return geom;
}

bool ossimKakaduJp2Reader::loadState(const ossimKeywordlist& kwl,
                                     const char* prefix)
{
   bool result = false;
   if ( ossimImageHandler::loadState(kwl, prefix) )
   {
      result = open();
   }
   return result;
}

void ossimKakaduJp2Reader::configureChannelMapping()
{
   bool result = false;
   
   if ( theChannels )
   {
      theChannels->clear();
   }
   else
   {
      theChannels = new kdu_channel_mapping;
   }
            
   if ( theJp2Source )
   {
      // Currently ignoring alpha:
      result = theChannels->configure(static_cast<jp2_source*>(theJp2Source), false);
   }
   else
   {
      result = theChannels->configure(theCodestream);
   }
    
   if ( result )
   {
      // If we the mapping doesn't have all our bands we don't use it.
      if ( theChannels->get_num_colour_channels() !=  static_cast<int>(theNumberOfBands) )
      {
         result = false;
      }
   }

   if ( !result )
   {
      theChannels->clear();
      delete theChannels;
      theChannels = 0;
   }
}
