//----------------------------------------------------------------------------
//
// License:  See top level LICENSE.txt file
//
// Author:  David Burken
//
// Description: OSSIM Open JPEG (j2k) reader (tile source).
//
// http://www.openjpeg.org/
//
//----------------------------------------------------------------------------
// $Id: ossimOpenJpegReader.h 11438 2007-07-29 17:41:11Z dburken $
#ifndef ossimOpenJpegReader_HEADER
#define ossimOpenJpegReader_HEADER

#include <vector>

#include <ossim/imaging/ossimImageHandler.h>
#include <ossim/support_data/ossimJ2kSizRecord.h>

// Forward class declarations.
class ossimImageData;

class ossimOpenJpegReader : public ossimImageHandler
{
public:

   enum ossimOpenJpegReadMode
   {
      ossimOpenJpegReadUnknown = 0
   };

   /** default constructor */
   ossimOpenJpegReader();

   /** virtual destructor */
   virtual ~ossimOpenJpegReader();

   /** @return "png" */
   virtual ossimString getShortName() const;

   /** @return "ossim png" */
   virtual ossimString getLongName()  const;

   /** @return "ossimOpenJpegReader" */
   virtual ossimString getClassName()    const;

   /**
    *  Returns a pointer to a tile given an origin representing the upper
    *  left corner of the tile to grab from the image.
    *  Satisfies pure virtual from TileSource class.
    */
   virtual ossimRefPtr<ossimImageData> getTile(const  ossimIrect& tile_rect,
                                               ossim_uint32 resLevel=0);

    /**
     *  Returns the number of bands in the image.
     *  Satisfies pure virtual from ImageHandler class.
     */
   virtual ossim_uint32 getNumberOfInputBands() const;

   /**
    * Returns the number of bands in a tile returned from this TileSource.
    * Note: we are supporting sources that can have multiple data objects.
    * If you want to know the scalar type of an object you can pass in the
    */
   virtual ossim_uint32 getNumberOfOutputBands()const;

   /**
     *  Returns the number of lines in the image.
     *  Satisfies pure virtual from ImageHandler class.
     */
   virtual ossim_uint32 getNumberOfLines(ossim_uint32 reduced_res_level = 0) const;

   /**
    *  Returns the number of samples in the image.
    *  Satisfies pure virtual from ImageHandler class.
    */
   virtual ossim_uint32 getNumberOfSamples(ossim_uint32 reduced_res_level = 0) const;

   /**
    * Returns the zero based image rectangle for the reduced resolution data
    * set (rrds) passed in.  Note that rrds 0 is the highest resolution rrds.
    */
   virtual ossimIrect getImageRectangle(ossim_uint32 reduced_res_level = 0) const;

   /**
    * Method to save the state of an object to a keyword list.
    * Return true if ok or false on error.
    */
   virtual bool saveState(ossimKeywordlist& kwl,
                          const char* prefix=0)const;

   /**
    * Method to the load (recreate) the state of an object from a keyword
    * list.  Return true if ok or false on error.
    */
   virtual bool loadState(const ossimKeywordlist& kwl,
                          const char* prefix=0);

   /**
    * Returns the output pixel type of the tile source.
    */
   virtual ossimScalarType getOutputScalarType() const;

   /**
    * Returns the width of the output tile.
    */
   virtual ossim_uint32    getTileWidth() const;

   /**
    * Returns the height of the output tile.
    */
   virtual ossim_uint32    getTileHeight() const;

   /**
    * Returns the tile width of the image or 0 if the image is not tiled.
    * Note: this is not the same as the ossimImageSource::getTileWidth which
    * returns the output tile width which can be different than the internal
    * image tile width on disk.
    */
   virtual ossim_uint32 getImageTileWidth() const;

   /**
    * Returns the tile width of the image or 0 if the image is not tiled.
    * Note: this is not the same as the ossimImageSource::getTileWidth which
    * returns the output tile width which can be different than the internal
    * image tile width on disk.
    */
   virtual ossim_uint32 getImageTileHeight() const;

   virtual bool isOpen()const;

   virtual double getMaxPixelValue(ossim_uint32 band = 0)const;

   /** close method */
   virtual void close();

protected:

   // Cleans memory.  Called on close or destruct.
   void destroy();
   
   /**
    *  @brief open method.
    *  @return true on success, false on error.
    */
   virtual bool open();

   ossimJ2kSizRecord theSizRecord;
   
   ossimRefPtr<ossimImageData>  theTile;
   ossimRefPtr<ossimImageData>  theImage;

   
TYPE_DATA
};

#endif
