//*******************************************************************
//
// License:  LGPL
//
// See LICENSE.txt file in the top level directory for more details.
// 
// Author: Garrett Potts
// 
// Description: Rpf support class
// 
//********************************************************************
// $Id: ossimRpfTocEntry.h 18362 2010-11-01 15:20:47Z dburken $
#ifndef ossimRpfTocEntry_HEADER
#define ossimRpfTocEntry_HEADER

#include <ossim/support_data/ossimRpfBoundaryRectRecord.h>
#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimErrorContext.h>
#include <ossim/imaging/ossimImageGeometry.h>
#include <ossim/support_data/ossimRpfFrameEntry.h>

#include <vector>
#include <iosfwd>

class ossimIrect;

class OSSIM_DLL ossimRpfTocEntry
{
public:
   friend std::ostream& operator <<(std::ostream& out,
                                    const ossimRpfTocEntry& data);
   ossimRpfTocEntry();
   ossimErrorCode parseStream(std::istream &in, ossimByteOrder byteOrder);

   /**
    * @brief print method that outputs a key/value type format adding prefix
    * to keys.
    * @param out String to output to.
    * @param prefix This will be prepended to key.
    * e.g. Where prefix = "nitf." and key is "file_name" key becomes:
    * "nitf.file_name:"
    * @return output stream.
    */
   std::ostream& print(std::ostream& out,
                       const std::string& prefix=std::string()) const;
   
   void setEntry(const ossimRpfFrameEntry& entry,
                 long row,
                 long col);

   bool getEntry(long row,
                 long col,
                 ossimRpfFrameEntry& result)const;

   ossimString getProductType() const;
   
   /*!
    * returns how many subimges or frames exist in the horizontal
    * direction.
    */
   ossim_uint32 getNumberOfFramesHorizontal()const;

   /*!
    * returns how many subimges or frames exist in the vertical
    * direction.
    */
   ossim_uint32 getNumberOfFramesVertical()const;

   /** @return The number of lines (frames vertical * 1536). */
   ossim_uint32 getNumberOfLines() const;

   /** @return The number of samples (frames horizontal * 1536). */
   ossim_uint32 getNumberOfSamples() const;

   /** @return Number of bands. */
   ossim_uint32 getNumberOfBands() const;
   
   /**
    * @brief Get the bounding rect of entry.
    * @param rect Gets initialized with rect.
    */
   void getBoundingRect(ossimIrect& rect) const;
   
   const ossimRpfBoundaryRectRecord& getBoundaryInformation()const;

   /*!
    * If there is an entry and all the files don't exist we will return
    * true.
    */
   bool isEmpty()const;

   /**
    * Returns the image geometry object associated with this tile source or
    * NULL if non defined.  The geometry contains full-to-local image
    * transform as well as projection (image-to-world).
    */
   ossimRefPtr<ossimImageGeometry> getImageGeometry() const;

   /** @brief Get the scale in decimal degrees per pixel. */
   void getDecimalDegreesPerPixel(ossimDpt& scale) const;

   /** @brief Get the scale in meters per pixel. */
   void getMetersPerPixel(ossimDpt& scale) const;
   
private:
   void allocateFrameEntryArray();
   
   ossimRpfBoundaryRectRecord theBoundaryInformation;
   std::vector< std::vector<ossimRpfFrameEntry> > theFrameEntryArray;
};

#endif
