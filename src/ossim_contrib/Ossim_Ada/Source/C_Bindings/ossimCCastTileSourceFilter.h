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
#ifndef ossimCCastTileSourceFilter_HEADER
#define ossimCCastTileSourceFilter_HEADER

#include "ossimCConnectableObject.h"

typedef void* ossimCastTileSourceFilterH;
enum ossimCScalarType
{
   OSSIM_CSCALAR_UNKNOWN    =  0,   
   OSSIM_CUCHAR             =  1,   /* unsigned   char   8  bit */
   OSSIM_CUSHORT16          =  2,   /* unsigned   short  16 bit */
   OSSIM_CSSHORT16          =  3,   /* signed     short  16 bit */
   OSSIM_CUSHORT11          =  4,   /* unsigned   short  11 bit */
   OSSIM_CFLOAT             =  5,   /* floating   point  32 bit */
   OSSIM_CNORMALIZED_FLOAT  =  6,   /* normalized floating point  32 bit */
   OSSIM_CDOUBLE            =  7,   /* double 64 bit    */
   OSSIM_CNORMALIZED_DOUBLE =  8    /* Normalized double 64 bit */
};

#ifdef __cplusplus
extern "C"
{
#endif

	ossimCastTileSourceFilterH ossimCreateCastTileSourceFilter(
		ossimConnectableObjectH inputSource,
		ossimCScalarType scalarType); // default to Null, OSSIM_UCHAR);
	void ossimDeleteCastTileSourceFilter(ossimCastTileSourceFilterH cast);
	
#ifdef __cplusplus
}
#endif

#endif

