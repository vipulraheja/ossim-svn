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
//
//*****************************************************************************

#include "ossimCMapProjectionInfo.h"
#include "ossimCMapProjection.h"
#include "projections/map_projections/ossimMapProjection.h"
#include "projections/map_projections/ossimMapProjectionInfo.h"
#include "base/data_types/ossimDrect.h"

	ossimCMapProjectionInfoH ossimCreateMapProjectionInfo(ossimCMapProjectionH proj,
                          ossimCDRectH output_rect)
	{
		ossimMapProjection* p = (ossimMapProjection*)proj;
		ossimDrect* rect = (ossimDrect*)output_rect;
		
		ossimMapProjectionInfo* projInfo = 
			(ossimMapProjectionInfo*) new ossimMapProjectionInfo(p, *rect);
		return (ossimCMapProjectionInfoH)projInfo;
	}

	void ossimDeleteMapProjectionInfo(ossimCMapProjectionInfoH proj)
	{
        if(proj)
			delete (ossimMapProjectionInfo*)proj;
	}

	ossim_int32 mapProjectionInfoLinesPerImage(ossimCMapProjectionInfoH proj)
	{
		ossimMapProjectionInfo* p = (ossimMapProjectionInfo*)proj;
		return p->linesPerImage();
	}
	
	ossim_int32 mapProjectionInfoPixelsPerLine(ossimCMapProjectionInfoH proj)
	{
		ossimMapProjectionInfo* p = (ossimMapProjectionInfo*)proj;
		return p->pixelsPerLine();
	}

