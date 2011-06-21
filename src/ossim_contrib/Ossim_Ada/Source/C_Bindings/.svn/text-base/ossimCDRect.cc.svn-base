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
#include "ossimCDRect.h"
#include "ossimCDpt.h"
#include "base/common/ossimCommon.h"
#include "base/data_types/ossimDrect.h"
#include "base/data_types/ossimDpt.h"
	
	ossimCDRectH ossimCreateDrect()
	{
	ossimDrect* rect = new ossimDrect();
	return (ossimCDptH)rect;
	}
	
	ossimCDRectH ossimCreateCornerDrect(
				ossimCDptH   ul_corner,
				ossimCDptH   lr_corner,
				ossimCCoordSysOrientMode mode) //default = OSSIMC_LEFT_HANDED
	{
		ossimDpt* ul = (ossimDpt*) ul_corner;
		ossimDpt* lr = (ossimDpt*) lr_corner;
		ossimCoordSysOrientMode CoordMode = (ossimCoordSysOrientMode)mode;
		ossimDrect* rect = new ossimDrect(*ul, *lr, CoordMode);
		return (ossimCDRectH)rect;
	}
				
	ossimCDRectH ossimCreatePointsDrect(
				const double& ul_corner_x,
				const double& ul_corner_y,
				const double& lr_corner_x,
				const double& lr_corner_y,
				ossimCCoordSysOrientMode mode) // default = OSSIMC_LEFT_HANDED
	{
		ossimCoordSysOrientMode CoordMode = (ossimCoordSysOrientMode)mode;
		ossimDrect* rect = new ossimDrect(ul_corner_x, ul_corner_y, 
			lr_corner_x, lr_corner_y, CoordMode);
		return rect;
	}
				
	ossimCDRectH ossimCreateDRDrect(const ossimCDRectH rect)
	{
	return (ossimCDRectH) new ossimDrect(*(ossimDrect*)rect);
	}
	
	ossimCDRectH ossimCreateIRDrect(const ossimIrectH rect)
	{
	return (ossimCDRectH) new ossimDrect(*(ossimIrect*)rect);
	}

	void ossimDeleteDrect(ossimCDRectH rect)
	{
		if(rect)
			delete (ossimDrect*)rect;
	}	
	
