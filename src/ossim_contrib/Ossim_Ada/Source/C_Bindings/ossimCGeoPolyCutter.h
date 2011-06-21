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
#ifndef ossimCGeoPolyCutter_HEADER
#define ossimCGeoPolyCutter_HEADER

#include "base/common/ossimConstants.h"
#include "ossimCGeoPolygon.h"
#include "ossimCPolyCutter.h"
#include "ossimCMapProjection.h"

typedef void* ossimGeoPolyCutterH;

#ifdef __cplusplus
extern "C"
{
#endif

	ossimGeoPolyCutterH createOssimGeoPolyCutter();

	ossimGeoPolyCutterH createConnectedOssimGeoPolyCutter(ossimConnectableObjectH inputSource);

	void deleteGeoPolyCutter(ossimGeoPolyCutterH cutter);
	
	/*!
    * Will add the passed in polygon.
	 */
	void addGeoPolygon(ossimGeoPolyCutterH cutter, const ossimGeoPolygonH& polygon);
	void setGeoCutType(ossimGeoPolyCutterH cutter, ossimCPolyCutterCutType cutType);
	bool ossimGeoPolyCutterSetView(ossimGeoPolyCutterH cutter, ossimCMapProjectionH baseObject,
					  bool ownsTheView); // default to false
  /*!
    * The view projection used to project the ground coordinates.
    */
   ossimCMapProjectionH geoPolyCutterGetView(ossimGeoPolyCutterH cutter);

   ossimIrectH geoPolyCutterGetBoundingRect(ossimGeoPolyCutterH cutter,
											ossim_uint32 resLevel); // default = 0

#ifdef __cplusplus
}
#endif

#endif
