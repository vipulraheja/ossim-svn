//*****************************************************************************
// Copyright (C) 2003 James E. Hopper & ImageLinks Inc. 
//
// This is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation.
//
// This software is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// You should have received a copy of the GNU General Public License
// along with this software. If not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-
// 1307, USA.
//
// See the GPL in the COPYING.GPL file for more details.
//
// AUTHOR: James E. Hopper (hopperj@macconnect.com)
//         Garrett Potts (gpotts@imagelinks)
//
//*****************************************************************************
#ifndef ossimCImageData_HEADER
#define ossimCImageData_HEADER
typedef void* ossimImageDataH;
typedef void* ossimSourceH;
typedef void* ossimObjectH;

#include "ossimCIRect.h"
#include "base/common/ossimConstants.h"

#ifdef __cplusplus
extern "C"
{
#endif

   ossimImageDataH createOssimImageData(
                  ossimSourceH source,
                  ossimScalarType scalar,
                  ossim_uint32 bands = 1,
                  ossim_uint32 width = 128,
                  ossim_uint32 height= 128);

	unsigned long int ossimGetImageDataSizeInBytes(ossimImageDataH data);
	unsigned long int ossimGetImageDataSizePerBandInBytes(ossimImageDataH data);
	void* ossimGetImageDataBuf(ossimImageDataH data, int idx);
	void* getBuf(ossimImageDataH data);
   /*!
    * Returns the image rectangle relative to origin, height and width.
    */
	ossimIrectH getImageRectangle(ossimImageDataH data);
	void setImageRectangle(ossimImageDataH data, const ossimIrectH rect);

	ossim_uint32 getNumberOfBands(ossimImageDataH data);
	/*!
	* Each band has a null pixel associated with it.  The null pixel 
	* represents an invalid value.
	*/ 
	double getNullPixelValue(ossimImageDataH data, ossim_uint32 band);


	/*!
	* Returns the min pixel of the band.
	*/
	double getMinPixelValue(ossimImageDataH data, ossim_uint32 band);

	/*!
	* Returns the max pixel of the band.
	*/
	double getMaxPixelValue(ossimImageDataH data, ossim_uint32 band);
	
	ossim_float64 getNullPix(ossimImageDataH data, ossim_uint32 band);
	ossim_float64 getMinPix(ossimImageDataH data, ossim_uint32 band);
	ossim_float64 getMaxPix(ossimImageDataH data, ossim_uint32 band);
	ossim_float64 getMinNormalizedPix(ossimImageDataH data);

   ossim_uint32 getWidth(ossimImageDataH data);
   ossim_uint32 getHeight(ossimImageDataH data);

   /*!
    *  Initialize the data buffer.
    */
   void initialize(ossimImageDataH data);
   
      /*!
    * This is to be overriden in the derived classes so they can check
    * If their data is null.
    */
   bool isInitialize(ossimImageDataH data);

   /*!
    * Will load a tile of different types.  If they
    * are the same then it will call loadTile(void*...)
    * method.  Note if they are of different types we
    * will have to go through a much slower assign
    * process by normalizing the right side and then
    * unnormalizing to the destination type. For this
    * method to work they both must have the same
    * number of bands.
    */
   void loadTile(ossimImageDataH data, const ossimImageDataH src);

   void loadTileBoundRect(      
                       ossimImageDataH data,
				 const void* src,
				 const ossimIrectH src_rect,
					   ossimInterleaveType il_type);

   void loadTileClipRect(      
					   ossimImageDataH data,
				 const void* src,
                 const ossimIrectH src_rect,
                 const ossimIrectH clip_rect,                         
                 ossimInterleaveType il_type);

   bool   isValidBand(ossimImageDataH data, ossim_uint32 band);

   ossimDataObjectStatus validate(ossimImageDataH data);

   void loadBand(      ossimImageDataH data,
				 const void* src,
                 const ossimIrectH src_rect,
					   ossim_uint32 band);

	ossimObjectH dupData(ossimImageDataH data);
	
	void freeOssimImageData(ossimImageDataH data);
	
#ifdef __cplusplus
}
#endif

#endif
