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
#include "ossimCImageSource.h"
#include "imaging/ossimImageSource.h"

/*!
* Each band has a null pixel associated with it.  The null pixel 
* represents an invalid value.
*/ 
double getNullPixelValue(ossimImageSourceH data, ossim_uint32 band)
{
	ossimImageSource* d = (ossimImageSource*)data;
	return d->getNullPixelValue(band);
}


/*!
* Returns the min pixel of the band.
*/
double getMinPixelValue(ossimImageSourceH data, ossim_uint32 band)
{
	ossimImageSource* d = (ossimImageSource*)data;
	return d->getMinPixelValue(band);
}

/*!
* Returns the max pixel of the band.
*/
double getMaxPixelValue(ossimImageSourceH data, ossim_uint32 band)
{
	ossimImageSource* d = (ossimImageSource*)data;
	return d->getMaxPixelValue(band);
}

ossimImageDataH getTile(ossimImageSourceH handler, 
						ossimIrectH boundingRect,
						ossim_uint32 resLevel)
{
	ossimImageSource* h = (ossimImageSource*)handler;
	return h->getTile(*(ossimIrect*)boundingRect, resLevel);
}

int getOutputScalarType(ossimImageSourceH handler, 
		unsigned int dataObject)
{
	ossimImageSource* ih = (ossimImageSource*)handler;
	return ih->getOutputScalarType();
}

void freeOssimImageSource(ossimImageSourceH handler)
{
	if(handler)
		delete (ossimImageSource*)handler;
}
