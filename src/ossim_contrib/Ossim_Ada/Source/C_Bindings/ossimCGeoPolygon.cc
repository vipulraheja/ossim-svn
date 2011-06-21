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
#include "ossimCGeoPolygon.h"
#include "base/common/ossimConstants.h"
#include "base/data_types/ossimGeoPolygon.h"
#include "base/data_types/ossimGpt.h"

ossimGeoPolygonH createOssimGeoPolygon()
{
	ossimGeoPolygon* result = (ossimGeoPolygon*) new ossimGeoPolygon();
	return (ossimGeoPolygonH)result;
}

void deleteOssimGeoPolygon(ossimGeoPolygonH poly)
{
	if(poly)
		delete (ossimGeoPolygon*)poly;
}
void ossimGeoPolyAddPoint(ossimGeoPolygonH object, const ossimGptH& pt)
{
	ossimGeoPolygon *polygon = (ossimGeoPolygon*)object;
	const ossimGpt gPt = (const ossimGpt&)pt;
	polygon->addPoint(gPt);
}

void setOrdering(ossimGeoPolygonH object, ossimCVertexOrdering ordering)
{
	ossimGeoPolygon *polygon = (ossimGeoPolygon*)object;
	polygon->setOrdering(ossimVertexOrdering(ordering));
}
