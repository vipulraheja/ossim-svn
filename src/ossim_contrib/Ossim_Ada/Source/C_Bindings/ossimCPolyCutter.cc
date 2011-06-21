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
#include "ossimCPolyCutter.h"
#include "imaging/tile_sources/ossimPolyCutter.h"
#include "base/data_types/ossimPolygon.h"
#include "imaging/formats/ossimImageHandler.h"

ossimPolyCutterH createOssimPolyCutter()
{
	ossimPolyCutter* cutter = new ossimPolyCutter();
	return (ossimPolyCutterH)cutter;
}

ossimPolyCutterH ossimCreatePolyCutter(
	ossimConnectableObjectH inputSource, ossimPolygonH polygon)
{
	ossimImageSource *ih = (ossimImageSource*)inputSource;
	ossimPolygon *bounds = (ossimPolygon*)polygon;
	ossimPolyCutter* Cutter = (ossimPolyCutter*) new ossimPolyCutter(ih, *bounds);
	return (ossimPolyCutterH)Cutter;
}

void deletePolyCutter(ossimPolyCutterH cutter)
{
	if(cutter)
		delete (ossimPolyCutter*)cutter;
}

void setCutType(ossimPolyCutterH cutter, ossimCPolyCutterCutType cutType)
{
	ossimPolyCutter *c = (ossimPolyCutter*)cutter;
	c->setCutType(ossimPolyCutter::ossimPolyCutterCutType(cutType));
}

ossimIrectH polyCutterGetBoundingRect(ossimPolyCutterH cutter,
										 ossim_uint32 resLevel)
{
	ossimPolyCutter *c = (ossimPolyCutter*)cutter;
	ossimIrect* rect = new ossimIrect();
	*rect =  c->getBoundingRect(resLevel);
	return (ossimIrectH) rect;
}

