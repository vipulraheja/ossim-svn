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
#include "ossimCImageData.h"
#include "imaging/ossimImageData.h"
#include "base/data_types/ossimIrect.h"
#include "base/common/ossimConstants.h"

ossimImageDataH createOssimImageData(
                  ossimSourceH source,
                  ossimScalarType scalar,
                  ossim_uint32 bands,
                  ossim_uint32 width,
                  ossim_uint32 height)
{
	ossimSource* src = (ossimSource*)source;
	return (ossimImageDataH) new ossimImageData(src, scalar, bands, width, height);
}

unsigned long int ossimGetImageDataSizeInBytes(ossimImageDataH data)
{
   if(data)
   {
      return ((ossimImageData*)data)->getSizeInBytes();
   }

   return 0;
}

unsigned long int ossimGetImageDataSizePerBandInBytes(ossimImageDataH data)
{
   if(data)
   {
      return ((ossimImageData*)data)->getSizePerBandInBytes();
   }

   return 0;
   
}

void* ossimGetImageDataBuf(ossimImageDataH data, int idx)
{
   if(data)
   {
      return ((ossimImageData*)data)->getBuf(idx);
   }

   return (void*)NULL;
   
}

void* getBuf(ossimImageDataH data)
{
   if(data)
   {
      return ((ossimImageData*)data)->getBuf();
   }

   return (void*)NULL;
}

ossimIrectH getImageRectangle(ossimImageDataH data)
{
	if(data)
	{
		ossimIrect* r = new ossimIrect();
		*r = ((ossimImageData*)data)->getImageRectangle();
		return (ossimIrectH)r;
	}

	return (void*)NULL;
}

void setImageRectangle(ossimImageDataH data, const ossimIrectH rect)
{
	ossimImageData* d = (ossimImageData*)data;
	ossimIrect* r = new ossimIrect();
	r = (ossimIrect*)rect;
	d->setImageRectangle(*r);
}


ossim_uint32 getNumberOfBands(ossimImageDataH data)
{
	ossimImageData* d = (ossimImageData*)data;
	return d->getNumberOfBands();
}

ossim_float64 getNullPix(ossimImageDataH data, ossim_uint32 band)
{
	ossimImageData* d = (ossimImageData*)data;
	return d->getNullPix(band);
}

ossim_float64 getMinPix(ossimImageDataH data, ossim_uint32 band)
{
	ossimImageData* d = (ossimImageData*)data;
	return d->getMinPix(band);
}

ossim_float64 getMaxPix(ossimImageDataH data, ossim_uint32 band)
{
	ossimImageData* d = (ossimImageData*)data;
	return d->getMaxPix(band);
}

ossim_float64 getMinNormalizedPix(ossimImageDataH data)
{
	ossimImageData* d = (ossimImageData*)data;
	return d->getMinNormalizedPix();
}

ossim_uint32 getWidth(ossimImageDataH data)
{
	ossimImageData* d = (ossimImageData*)data;
	return d->getWidth();
}

ossim_uint32 getHeight(ossimImageDataH data)
{
	ossimImageData* d = (ossimImageData*)data;
	return d->getHeight();
}

void initialize(ossimImageDataH data)
{
	ossimImageData* d = (ossimImageData*)data;
	d->initialize();
}

bool isInitialize(ossimImageDataH data)
{
	ossimImageData* d = (ossimImageData*)data;
	return d->isInitialize();
}

void loadTile(ossimImageDataH data, const ossimImageDataH src)
{
	ossimImageData* d = (ossimImageData*)data;
	d->loadTile((ossimImageData*)src);
}

void loadTileBoundRect(      
                       ossimImageDataH data,
				 const void* src,
				 const ossimIrectH src_rect,
					   ossimInterleaveType il_type)
{
	ossimImageData* d = (ossimImageData*)data;
	d->loadTile(src, *(ossimIrect*)src_rect, il_type);
}

void loadTileClipRect(      
					   ossimImageDataH data,
				 const void* src,
                 const ossimIrectH src_rect,
                 const ossimIrectH clip_rect,                         
                 ossimInterleaveType il_type)
{
	ossimImageData* d = (ossimImageData*)data;
	d->loadTile(src, *(ossimIrect*)src_rect, *(ossimIrect*)clip_rect, il_type);
}

bool   isValidBand(ossimImageDataH data, ossim_uint32 band)
{
	ossimImageData* d = (ossimImageData*)data;
	return d->isValidBand(band);
}

ossimDataObjectStatus validate(ossimImageDataH data)
{
	ossimImageData* d = (ossimImageData*)data;
	return d->validate();
}

void loadBand(       ossimImageDataH data,
		       const void* src,
			   const ossimIrectH src_rect,
					  ossim_uint32 band)
{
	ossimImageData* d = (ossimImageData*)data;
	d->loadBand(src, *(ossimIrect*)src_rect, band);
}

ossimObjectH dupData(ossimImageDataH data)
{
	ossimImageData* d = (ossimImageData*)data;
	return d->dup();
}

void freeOssimImageData(ossimImageDataH data)
{
	if(data)
		delete (ossimImageData*)data;
}

