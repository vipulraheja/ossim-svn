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
#include "ossimCGeoPolyCutter.h"
#include "imaging/tile_sources/ossimPolyCutter.h"
#include "imaging/tile_sources/ossimGeoPolyCutter.h"
#include "base/data_types/ossimGeoPolygon.h"
#include "imaging/formats/ossimImageHandler.h"
#include "projections/ossimProjection.h"
#include "base/data_types/ossimIrect.h"

ossimGeoPolyCutterH createOssimGeoPolyCutter()
{
	ossimGeoPolyCutter* cutter = new ossimGeoPolyCutter();
	return (ossimGeoPolyCutterH)cutter;
}

ossimGeoPolyCutterH createConnectedOssimGeoPolyCutter(ossimConnectableObjectH inputSource)
{
	ossimGeoPolyCutter* cutter = new ossimGeoPolyCutter();
	cutter->connectMyInputTo(PTR_CAST(ossimConnectableObject,
								   (ossimObject*)inputSource));
	return (ossimGeoPolyCutterH)cutter;
}

void deleteGeoPolyCutter(ossimGeoPolyCutterH cutter)
{
	if(cutter)
	delete (ossimGeoPolyCutter*)cutter;
}

/*!
* Will add the passed in polygon.
 */
void addGeoPolygon(ossimGeoPolyCutterH cutter, const ossimGeoPolygonH& polygon)
{
	ossimGeoPolyCutter *c = (ossimGeoPolyCutter*)cutter;
	c->addPolygon(*(ossimGeoPolygon*)polygon);
}

void setGeoCutType(ossimGeoPolyCutterH cutter, ossimCPolyCutterCutType cutType)
{
	ossimGeoPolyCutter *c = (ossimGeoPolyCutter*)cutter;
	c->setCutType(ossimPolyCutter::ossimPolyCutterCutType(cutType));
}

bool ossimGeoPolyCutterSetView(ossimGeoPolyCutterH cutter, ossimCMapProjectionH baseObject,
			 bool ownsTheView)
{
	ossimGeoPolyCutter *c = (ossimGeoPolyCutter*)cutter;
	return c->setView((ossimProjection*)baseObject, ownsTheView);
}

/*!
* The view projection used to project the ground coordinates.
*/
ossimCMapProjectionH geoPolyCutterGetView(ossimGeoPolyCutterH cutter)
{
	ossimGeoPolyCutter *c = (ossimGeoPolyCutter*)cutter;
	return (ossimCMapProjectionH)c->getView();
}

ossimIrectH geoPolyCutterGetBoundingRect(ossimGeoPolyCutterH cutter,
									  ossim_uint32 resLevel)
{
	ossimGeoPolyCutter *c = (ossimGeoPolyCutter*)cutter;
	ossimIrect* rect = new ossimIrect();
	*rect =  c->getBoundingRect(resLevel);
	return (ossimIrectH) rect;
}


