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
#ifndef ossimCGeoPolygon_HEADER
#define ossimCGeoPolygon_HEADER
#include "ossimCGpt.h"

typedef void* ossimGeoPolygonH;

#ifdef __cplusplus
extern "C"
{
#endif

enum ossimCVertexOrdering
{
	OSSIM_CVERTEX_ORDER_UNKNOWN    = 0,
	OSSIM_CCLOCKWISE_ORDER         = 1,
	OSSIM_CCOUNTERCLOCKWISE_ORDER  = 2
};

ossimGeoPolygonH createOssimGeoPolygon();
void deleteOssimGeoPolygon(ossimGeoPolygonH poly);
void ossimGeoPolyAddPoint(ossimGeoPolygonH object, const ossimGptH& pt);
void setOrdering(ossimGeoPolygonH object, ossimCVertexOrdering ordering);
	
#ifdef __cplusplus
}
#endif

#endif
