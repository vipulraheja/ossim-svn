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
#ifndef ossimCDRect_HEADER
#define ossimCDRect_HEADER

#include "ossimCIRect.h"
#include "ossimCDpt.h"
#include "ossimCCommon.h"

typedef void* ossimCDRectH;

#ifdef __cplusplus
extern "C"
{
#endif

   enum
   {
      CUPPER_LEFT  = 1,
      CLOWER_LEFT  = 2,
      CLOWER_RIGHT = 4,
      CUPPER_RIGHT = 8
   };
   
   ossimCDRectH ossimCreateDrect();
   
   ossimCDRectH ossimCreateCornerDrect(
				ossimCDptH   ul_corner,
				ossimCDptH   lr_corner,
				ossimCCoordSysOrientMode mode); //default = OSSIMC_LEFT_HANDED
				
   ossimCDRectH ossimCreatePointsDrect(
				const double& ul_corner_x,
				const double& ul_corner_y,
				const double& lr_corner_x,
				const double& lr_corner_y,
				ossimCCoordSysOrientMode mode); // default = OSSIMC_LEFT_HANDED
				
   ossimCDRectH ossimCreateDRDrect(const ossimCDRectH rect);
   ossimCDRectH ossimCreateIRDrect(const ossimIrectH rect);
   
	void ossimDeleteDrect(ossimCDRectH rect);
   
#ifdef __cplusplus
}
#endif

#endif



