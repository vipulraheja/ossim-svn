/*
 *  ossimCGpt.cpp
 *  Ossim_Geo_Cutter
 *
 *  Created by jim hopper on Sat Aug 16 2003.
 *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
 *
 */

#include "ossimCGpt.h"
#include "base/data_types/ossimGpt.h"
#include "base/factory/ossimDatumFactory.h"

ossimGptH ossimCreateGpt(
		const double alat,  // degrees
		const double alon,  // degrees
		const double ahgt,
		const ossimDatum* aDatum)
{
	ossimGpt* result = (ossimGpt*) new ossimGpt(alat, alon, ahgt, aDatum);
	return result;
}

ossimGptH ossimCreateGptwgs84(
						 const double alat,  // degrees
						 const double alon,  // degrees
						 const double ahgt)

{
	ossimGpt* result = (ossimGpt*) new ossimGpt(
		alat, alon, ahgt, ossimDatumFactory::instance()->wgs84());
	return result;
}

double ossimGetGeoLat(ossimGptH pt)
{
	ossimGpt* point = (ossimGpt*)pt;
	return point->lat;
}

void ossimSetGeoLat(ossimGptH pt, double lat)
{
	ossimGpt* point = (ossimGpt*)pt;
	point->lat = lat;
}

double ossimGetGeoLong(ossimGptH pt)
{
	ossimGpt* point = (ossimGpt*)pt;
	return point->lon;
}

void ossimSetGeoLong(ossimGptH pt, double lon)
{
	ossimGpt* point = (ossimGpt*)pt;
	point->lon = lon;
}

double ossimGetGeoElev(ossimGptH pt)
{
	ossimGpt* point = (ossimGpt*)pt;
	return point->hgt;
}

void ossimSetGeoElev(ossimGptH pt, double elev)
{
	ossimGpt* point = (ossimGpt*)pt;
	point->hgt = elev;
}

void OssimFreeGpt(ossimGptH pt)
{
	delete (ossimGpt*)pt;
}
