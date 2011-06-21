--*****************************************************************************
-- Copyright (C) 2003 James E. Hopper. 
--
-- This is free software; you can redistribute it and/or
-- modify it under the terms of the GNU General Public License
-- as published by the Free Software Foundation.
--
-- This software is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
--
-- You should have received a copy of the GNU General Public License
-- along with this software. If not, write to the Free Software
-- Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-
-- 1307, USA.
--
-- See the GPL in the COPYING.GPL file for more details.
--
-- AUTHOR: James E. Hopper (hopperj@macconnect.com)
--
--*****************************************************************************
with Interfaces.C.Extensions;
use Interfaces.C.Extensions;
with Interfaces; use Interfaces;
with Ossim_Common; use Ossim_Common;
with Ossim_Constants; 
 use Ossim_Constants;
with Ipt;
package IRect is

    type Object is tagged private;

    function Create(C_Object : Void_Ptr) return Object;

    function Create(Left : ossim_int32; Top : ossim_int32; Right : ossim_int32; Bottom : ossim_int32) return Object;
	
    function Create(Width : ossim_int32; Height : ossim_int32) return Object;

    function CreateIRectFromIRect(Rect : Object) return Object;

    procedure Free(Rect : Object);

    function Width(Rect : Object) return ossim_uint32;

    function Height(Rect : Object) return ossim_uint32;

	procedure GetBounds(rect	: in     IRect.Object;
						minx	:    out ossim_int32;
						miny	:    out ossim_int32;
						maxx	:    out ossim_int32;
						maxy	:    out ossim_int32);
	function UL(Rect : Irect.Object) return Ipt.Object;
	function UR(Rect : Irect.Object) return Ipt.Object;
	function LR(Rect : Irect.Object) return Ipt.Object;
	function LL(Rect : Irect.Object) return Ipt.Object;

	procedure Set_UL(Rect : Irect.Object; Point : Ipt.Object);
	procedure Set_UR(Rect : Irect.Object; Point : Ipt.Object);
	procedure Set_LR(Rect : Irect.Object; Point : Ipt.Object);
	procedure Set_LL(Rect : Irect.Object; Point : Ipt.Object);

	procedure Set_UL_X(Rect : Irect.Object; X : ossim_int32);
	procedure Set_UR_X(Rect : Irect.Object; X : ossim_int32);
	procedure Set_LR_X(Rect : Irect.Object; X : ossim_int32);
	procedure Set_LL_X(Rect : Irect.Object; X : ossim_int32);
	procedure Set_UL_Y(Rect : Irect.Object; Y : ossim_int32);
	procedure Set_UR_Y(Rect : Irect.Object; Y : ossim_int32);
	procedure Set_LR_Y(Rect : Irect.Object; Y : ossim_int32);
	procedure Set_LL_Y(Rect : Irect.Object; Y : ossim_int32);

	procedure Offset_Rect(
			Rect		: IRect.Object; 
			Horizontal  : ossim_int32; 
			Vertical	: ossim_int32);
			
    function Left(Rect : Object) return ossim_int32;
    function Top(Rect : Object) return ossim_int32;
    function Right(Rect : Object) return ossim_int32;
    function Bottom(Rect : Object) return ossim_int32;

    procedure WidthHeight(
        Rect 	: in     Object;
        Width 	:    out ossim_uint32;
        Height	:    out ossim_uint32);

    function "+"(Rect : Object; Point : Ipt.Object) return Object;
    function "-"(Rect : Object; Point : Ipt.Object) return Object;

    function C_Object(Rect : Object) return Void_Ptr;

private

    type Object is tagged
    record
        OssimObject	: Void_Ptr;
    end record;

end IRect;

