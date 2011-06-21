//*******************************************************************
// Copyright (C) 2003 ImageLinks Inc.
//
// OSSIM is free software; you can redistribute it and/or
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
// Author: Garrett Potts (gpotts@imagelinks)
//         James E. Hopper
//
//*************************************************************************

#ifndef ossimProgressPercent_HEADER
#define ossimProgressPercent_HEADER
#include <iostream>
#include "base/common/events/ossimProcessListener.h"
#include "base/common/events/ossimProcessProgressEvent.h"


class OSSIMDLLEXPORT ossimProgressPercent : public ossimProcessListener
{
public:

ossimProgressPercent()
:	ossimProcessListener()

{
}
	
virtual void processProgressEvent(ossimProcessProgressEvent& event)
{	
	percent_complete = event.getPercentComplete();
}

virtual double Get_Percent_Complete()
{
	return percent_complete;
}

protected:
double percent_complete;
TYPE_DATA
};
extern ossimProgressPercent theossimProgressPercent;
#endif
