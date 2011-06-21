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
#include "ossimCImageHandler.h"
#include "imaging/formats/ossimImageHandler.h"
#include "imaging/factory/ossimImageHandlerRegistry.h"
#include "imaging/ossimImageSourceInterface.h"
#include "base/data_types/ossimIrect.h"

ossimObjectH castImageHandlerToObject(ossimImageHandlerH handler)
{
   ossimImageHandler* ih = (ossimImageHandler*)handler;
   return (ossimObjectH)PTR_CAST(ossimObject, ih);
}

ossimImageSourceInterfaceH castImageHandlerToImageSourceInterface(ossimImageHandlerH handler)
{
   ossimImageHandler* ih = (ossimImageHandler*)handler;
   return (ossimImageSourceInterfaceH)PTR_CAST(ossimImageSourceInterface, ih);
}

int getNumberOfDecimationLevels(ossimImageHandlerH handler)
{
	ossimImageHandler* ih = (ossimImageHandler*)handler;
	return ih->getNumberOfDecimationLevels();
}

ossimStringH ossimGetNewImageFilename(ossimImageHandlerH handler)
{
   ossimImageHandler* ih = (ossimImageHandler*)handler;
   return ossimCreateString(ih->getFilename().c_str());
}

ossimImageHandlerH ossimOpenImage(const char* filename)
{
	ossimImageHandlerH result = (ossimImageHandlerH)NULL;
   if(filename)
   {
      result = ossimImageHandlerRegistry::instance()->open(ossimFilename(filename));
   }
   
   return result;
}

ossimImageHandlerH ossimOpenImageKey(ossimKeywordlistH kwl)
{
	ossimImageHandlerH result = (ossimImageHandlerH)NULL;
	if(kwl)
	{
		result = ossimImageHandlerRegistry::instance()->open(*(ossimKeywordlist*)kwl);
	}
	return result;
}

ossimImageHandlerH ossimOpenHandler(ossimFilenameH& fileName)
{
	ossimImageHandler *handler =
         ossimImageHandlerRegistry::instance()->open(*(ossimFilename*) fileName);
	return (ossimImageHandlerH)handler;
}

char* ossimGetClassName(ossimImageHandlerH handler)
{
	ossimImageHandler* ih = (ossimImageHandler*)handler;
	ossimString Name = ih->getClassName();
	return (char*)ossimGetChars((ossimStringH)((const void*)Name));
}

int getNumberOfLines(ossimImageHandlerH handler,
	       int reduced_res_level)
{
	ossimImageHandler* ih = (ossimImageHandler*)handler;
	return ih->getNumberOfLines(reduced_res_level);
}

int getNumberOfSamples(ossimImageHandlerH handler,
	       int reduced_res_level)
{
	ossimImageHandler* ih = (ossimImageHandler*)handler;
	return ih->getNumberOfSamples(reduced_res_level);
}

ossimIrectH getBoundingRect(ossimImageHandlerH handler, int resLevel)
{
	ossimImageHandler* ih = (ossimImageHandler*)handler;
	ossimIrect* rect = new ossimIrect();
	*rect = ih->getBoundingRect(resLevel);
	return (ossimIrectH) rect;
}



