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
#ifndef ossimCGpt_HEADER
#define ossimCGpt_HEADER

typedef void* ossimGptH;
typedef void* ossimDatumH;

#ifdef __cplusplus
extern "C"
{
#endif

// Constructor.  The values are assumed to be in DEGREES.

ossimGptH ossimCreateGpt(
		const double alat,  // degrees
		const double alon,  // degrees
		const double ahgt,
		const ossimDatumH* aDatum);

	ossimGptH ossimCreateGptwgs84(
						  const double alat,  // degrees
						  const double alon,  // degrees
						  const double ahgt);

	double ossimGetGeoLat(ossimGptH pt);
	void ossimSetGeoLat(ossimGptH pt, double lat);
	double ossimGetGeoLong(ossimGptH pt);
	void ossimSetGeoLong(ossimGptH pt, double lon);
	double ossimGetGeoElev(ossimGptH pt);
	void ossimSetGeoElev(ossimGptH pt, double elev);
	void OssimFreeGpt(ossimGptH pt);

#ifdef __cplusplus
}
#endif

#endif

