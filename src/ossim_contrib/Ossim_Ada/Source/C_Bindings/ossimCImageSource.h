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
#ifndef ossimCImageSource_HEADER
#define ossimCImageSource_HEADER
typedef void* ossimImageSourceH;
typedef void* ossimIrectH;
typedef void* ossimImageDataH;

#include "base/common/ossimConstants.h"

#ifdef __cplusplus
extern "C"
{
#endif

	/*!
	* Each band has a null pixel associated with it.  The null pixel 
	* represents an invalid value.
	*/ 
	double getNullPixelValue(ossimImageSourceH data, ossim_uint32 band);


	/*!
	* Returns the min pixel of the band.
	*/
	double getMinPixelValue(ossimImageSourceH data, ossim_uint32 band);

	/*!
	* Returns the max pixel of the band.
	*/
	double getMaxPixelValue(ossimImageSourceH data, ossim_uint32 band);

	//
	// Returns the requested region of interest
	//
	ossimImageDataH getTile(ossimImageSourceH handler, 
									ossimIrectH boundingRect,
									ossim_uint32 resLevel=0);

	int getOutputScalarType(ossimImageSourceH handler, 
								unsigned int dataObject);
	
	void freeOssimImageSource(ossimImageSourceH handler);

#ifdef __cplusplus
}
#endif

#endif
