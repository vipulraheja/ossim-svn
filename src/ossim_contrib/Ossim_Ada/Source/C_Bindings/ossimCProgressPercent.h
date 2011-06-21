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
#ifndef ossimCProgressPercent_HEADER
#define ossimCProgressPercent_HEADER

typedef void* ossimProgressPercentH;

#ifdef __cplusplus
extern "C"
{
#endif

	extern "C" {

		ossimProgressPercentH ossimCreateProgressPercent();
		double Get_Percent_Complete(ossimProgressPercentH obj);
		void ossimFreeProgressPercent(ossimProgressPercentH obj);
	}

#ifdef __cplusplus
}
#endif

#endif
