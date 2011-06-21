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
#include "ossimCIRect.h"
#include "base/data_types/ossimIrect.h"

void ossimFreeRect(ossimIrectH rect)
{
   if(rect)
   {
      delete ((ossimIrect*)rect);
   }
}

ossimIrectH ossimCreate4(int left, int top, int right, int bottom)
{
	return (ossimIrectH) new ossimIrect(left, top, right, bottom);
}

ossimIrectH ossimCreate(int width, int height)
{
	return (ossimIrectH) new ossimIrect(0, 0, width - 1, height - 1);
}

ossimIrectH ossimCreateIrectFromIrect(ossimIrectH rect)
{
   ossimIrect* result = new ossimIrect();
   result->makeNan();
   if(rect)
   {
      *result = *((ossimIrect*)rect);
   }
   
   return (ossimIrectH)result;
}

long int ossimGetIrectWidth(ossimIrectH rect)
{
   if(rect)
   {
      return ((ossimIrect*)rect)->width();
   }

   return 0;
}

long int ossimGetIrectHeight(ossimIrectH rect)
{
   if(rect)
   {
      return ((ossimIrect*)rect)->height();
   }
   return 0;
   
}

void ossimGetIrectWidthHeight(ossimIrectH rect,
                              long int* w,
                              long int* h)
{
   if(rect)
   {
      *w = ((ossimIrect*)rect)->width();
      *h = ((ossimIrect*)rect)->height();
   }
   else
   {
      *w = 0;
      *h = 0;
   }
}

ossimIrectH ossimIrectAddPt(ossimIrectH rect, ossimIptH point)
{
   ossimIrect* result = (ossimIrect*)rect;
   *result = *result + *(ossimIpt*)point;
   return result;
}

ossimIrectH ossimIrectSubPt(ossimIrectH rect, ossimIptH point)
{
   ossimIrect* result = (ossimIrect*)rect;
   *result = *result - *(ossimIpt*)point;
   return result;
}

void getBounds(ossimIrectH rect, ossim_int32& minx, ossim_int32& miny,
                  ossim_int32& maxx, ossim_int32& maxy)
{
	ossimIrect* r = (ossimIrect*)rect;
	r->getBounds(minx, miny, maxx, maxy);
}

ossimIptH ul(ossimIrectH rect)
{
	ossimIpt* pt = new ossimIpt();
	ossimIrect* r = (ossimIrect*)rect;
	*pt = r->ul();
	return (ossimIptH)pt;
}
ossimIptH ur(ossimIrectH rect)
{
	ossimIpt* pt = new ossimIpt();
	ossimIrect* r = (ossimIrect*)rect;
	*pt = r->ur();
	return (ossimIptH)pt;
}
ossimIptH lr(ossimIrectH rect)
{
	ossimIpt* pt = new ossimIpt();
	ossimIrect* r = (ossimIrect*)rect;
	*pt = r->lr();
	return (ossimIptH)pt;
}
ossimIptH ll(ossimIrectH rect)
{
	ossimIpt* pt = new ossimIpt();
	ossimIrect* r = (ossimIrect*)rect;
	*pt = r->ll();
	return (ossimIptH)pt;
}


/*!
* Sets the upper left corner to "pt".  Adjusts the remaining corners
* accordingly.
*/
void set_ul(ossimIrectH rect, const ossimIptH pt)
{
	ossimIpt* point = (ossimIpt*)pt;
	ossimIrect* r = (ossimIrect*)rect;
	r->set_ul(*point);
}

/*!
* Sets the upper right corner to "pt".  Adjusts the remaining corners
* accordingly.
*/
void set_ur(ossimIrectH rect, const ossimIptH pt)
{
	ossimIpt* point = (ossimIpt*)pt;
	ossimIrect* r = (ossimIrect*)rect;
	r->set_ur(*point);
}

/*!
* Sets the lower right corner to "pt".  Adjusts the remaining corners
* accordingly.
*/
void set_lr(ossimIrectH rect, const ossimIptH pt)
{
	ossimIpt* point = (ossimIpt*)pt;
	ossimIrect* r = (ossimIrect*)rect;
	r->set_lr(*point);
}

/*!
* Sets the lower left corner to "pt".  Adjusts the remaining corners
* accordingly.
*/
void set_ll(ossimIrectH rect, const ossimIptH pt)
{
	ossimIpt* point = (ossimIpt*)pt;
	ossimIrect* r = (ossimIrect*)rect;
	r->set_ll(*point);
}

/*!
* Sets the upper left x.  Adjusts the remaining corners accordingly.
*/
void set_ulx(ossimIrectH rect, ossim_int32 x)
{
	ossimIrect* r = (ossimIrect*)rect;
	r->set_ulx(x);
}

/*!
* Sets the upper left y.  Adjusts the remaining corners accordingly.
*/
void set_uly(ossimIrectH rect, ossim_int32 y)
{
	ossimIrect* r = (ossimIrect*)rect;
	r->set_uly(y);
}

/*!
* Sets the upper right x.  Adjusts the remaining corners accordingly.
*/
void set_urx(ossimIrectH rect, ossim_int32 x)
{
	ossimIrect* r = (ossimIrect*)rect;
	r->set_urx(x);
}

/*!
* Sets the upper right y.  Adjusts the remaining corners accordingly.
*/
void set_ury(ossimIrectH rect, ossim_int32 y)
{
	ossimIrect* r = (ossimIrect*)rect;
	r->set_ury(y);
}

/*!
* Sets the lower right x.  Adjusts the remaining corners accordingly.
*/
void set_lrx(ossimIrectH rect, ossim_int32 x)
{
	ossimIrect* r = (ossimIrect*)rect;
	r->set_lrx(x);
}

/*!
* Sets the lower right y.  Adjusts the remaining corners accordingly.
*/
void set_lry(ossimIrectH rect, ossim_int32 y)
{
	ossimIrect* r = (ossimIrect*)rect;
	r->set_lry(y);
}

/*!
* Sets the lower left x.  Adjusts the remaining corners accordingly.
*/
void set_llx(ossimIrectH rect, ossim_int32 x)
{
	ossimIrect* r = (ossimIrect*)rect;
	r->set_llx(x);
}

/*!
* Sets the lower left y.  Adjusts the remaining corners accordingly.
*/
void set_lly(ossimIrectH rect, ossim_int32 y)
{
	ossimIrect* r = (ossimIrect*)rect;
	r->set_lly(y);
}

