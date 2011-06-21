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

#include "ossimCIpt.h"
#include "base/data_types/ossimIpt.h"

ossimIptH ossimCreateIpt(int anX, int aY)
{
   ossimIpt* result = (ossimIpt*) new ossimIpt(anX, aY);
   return result;
}

void ossimSetX(ossimIptH pt, int anX)
{
	ossimIpt* point = (ossimIpt*)pt;
	point->x = anX;
}

int	ossimGetX(ossimIptH pt)
{
	ossimIpt* point = (ossimIpt*)pt;
	return point->x;
}

void ossimSetY(ossimIptH pt, int aY)
{
	ossimIpt* point = (ossimIpt*)pt;
	point->y = aY;
}

int	ossimGetY(ossimIptH pt)
{
	ossimIpt* point = (ossimIpt*)pt;
	return point->y;
}

void ossimFreeCIpt(ossimIptH pt)
{
	delete (ossimIpt*)pt;
}
