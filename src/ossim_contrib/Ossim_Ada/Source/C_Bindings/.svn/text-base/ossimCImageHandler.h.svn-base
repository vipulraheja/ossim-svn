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
#ifndef ossimCImageHandler_HEADER
#define ossimCImageHandler_HEADER

#include "ossimCIRect.h"
#include "ossimCImageData.h"
#include "ossimCImageSourceInterface.h"
#include "ossimCObject.h"
#include "ossimCString.h"
#include "ossimCFilename.h"
#include "ossimCKeywordlist.h"

typedef void* ossimImageHandlerH;

#ifdef __cplusplus
extern "C"
{
#endif
	ossimObjectH castImageHandlerToObject(ossimImageHandlerH handler);
	ossimImageSourceInterfaceH castImageHandlerToImageSourceInterface(ossimImageHandlerH handler);
	ossimStringH ossimGetNewImageFilename(ossimImageHandlerH handler);
	int getNumberOfDecimationLevels(ossimImageHandlerH handler);
	ossimImageHandlerH ossimOpenImage(const char* filename);
	ossimImageHandlerH ossimOpenImageKey(ossimKeywordlistH kwl);
	ossimImageHandlerH ossimOpenHandler(ossimFilenameH& fileName);
	char* ossimGetClassName(ossimImageHandlerH handler);
  	int getNumberOfLines(ossimImageHandlerH handler,
	       int reduced_res_level);
  	int getNumberOfSamples(ossimImageHandlerH handler,
	       int reduced_res_level);
	ossimIrectH getBoundingRect(ossimImageHandlerH handler, int resLevel);
	
#ifdef __cplusplus
}
#endif

#endif
