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
#ifndef ossimCIrect_HEADER
#define ossimCIrect_HEADER

#include "ossimCIpt.h"
#include "base/common/ossimCommon.h"

typedef void* ossimIrectH;
typedef void* ossimIptH;

#ifdef __cplusplus
extern "C"
{
#endif

	void ossimFreeRect(ossimIrectH rect);
	ossimIrectH ossimCreate4(int left, int top, int right, int bottom);
	ossimIrectH ossimCreate(int width, int height);
	ossimIrectH ossimCreateIrectFromIrect(ossimIrectH rect);
	long int ossimGetIrectWidth(ossimIrectH rect);
	long int ossimGetIrectHeight(ossimIrectH rect);
	void ossimGetIrectWidthHeight(ossimIrectH rect,
                                 long int* w,
                                 long int* h);
	ossimIrectH ossimIrectAddPt(ossimIrectH rect, ossimIptH point);							 
	ossimIrectH ossimIrectSubPt(ossimIrectH rect, ossimIptH point);							 
	void getBounds(ossimIrectH rect, ossim_int32& minx, ossim_int32& miny,
                  ossim_int32& maxx, ossim_int32& maxy);
	ossimIptH ul(ossimIrectH rect);
	ossimIptH ur(ossimIrectH rect);
	ossimIptH lr(ossimIrectH rect);
	ossimIptH ll(ossimIrectH rect);

   /*!
    * Sets the upper left corner to "pt".  Adjusts the remaining corners
    * accordingly.
    */
   void set_ul(ossimIrectH rect, const ossimIptH pt);

   /*!
    * Sets the upper right corner to "pt".  Adjusts the remaining corners
    * accordingly.
    */
   void set_ur(ossimIrectH rect, const ossimIptH pt);

   /*!
    * Sets the lower right corner to "pt".  Adjusts the remaining corners
    * accordingly.
    */
   void set_lr(ossimIrectH rect, const ossimIptH pt);

   /*!
    * Sets the lower left corner to "pt".  Adjusts the remaining corners
    * accordingly.
    */
   void set_ll(ossimIrectH rect, const ossimIptH pt);

   /*!
    * Sets the upper left x.  Adjusts the remaining corners accordingly.
    */
   void set_ulx(ossimIrectH rect, ossim_int32 x);

   /*!
    * Sets the upper left y.  Adjusts the remaining corners accordingly.
    */
   void set_uly(ossimIrectH rect, ossim_int32 y);

   /*!
    * Sets the upper right x.  Adjusts the remaining corners accordingly.
    */
   void set_urx(ossimIrectH rect, ossim_int32 x);

   /*!
    * Sets the upper right y.  Adjusts the remaining corners accordingly.
    */
   void set_ury(ossimIrectH rect, ossim_int32 y);

   /*!
    * Sets the lower right x.  Adjusts the remaining corners accordingly.
    */
   void set_lrx(ossimIrectH rect, ossim_int32 x);

   /*!
    * Sets the lower right y.  Adjusts the remaining corners accordingly.
    */
   void set_lry(ossimIrectH rect, ossim_int32 y);

   /*!
    * Sets the lower left x.  Adjusts the remaining corners accordingly.
    */
   void set_llx(ossimIrectH rect, ossim_int32 x);

   /*!
    * Sets the lower left y.  Adjusts the remaining corners accordingly.
    */
   void set_lly(ossimIrectH rect, ossim_int32 y);

#ifdef __cplusplus
}
#endif

#endif
