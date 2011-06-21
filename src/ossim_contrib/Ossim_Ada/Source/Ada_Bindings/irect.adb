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
with System;
with Interfaces; use Interfaces;
with IPt; use IPt;
package body IRect is

    function Create(C_Object : Void_Ptr) return Object is
        TheObject : Object;
    begin
        TheObject.OssimObject:= C_Object;
        return TheObject;
    end Create;

    function Create(Left : ossim_int32; Top : ossim_int32; Right : ossim_int32; Bottom : ossim_int32) return Object is

        function Create(Left : ossim_int32; Top : ossim_int32; Right : ossim_int32; Bottom : ossim_int32) return Void_Ptr;
        pragma Import(C, Create, "ossimCreate4");

    begin
        return Create(Create(Left, Top, Right, Bottom));
    end Create;

    function Create(Width : ossim_int32; Height : ossim_int32) return Object is

        function Create(Width : ossim_int32; Height : ossim_int32) return Void_Ptr;
        pragma Import(C, Create, "ossimCreate");

    begin
        return Create(Create(Width, Height));
    end Create;

    function CreateIrectFromIrect(Rect : Object) return Object is
        function CreateIrectFromIrect(Rect : Void_Ptr) return Void_Ptr;
        pragma Import(C, CreateIrectFromIrect, "ossimCreateIrectFromIrect");
    begin
        return Create(CreateIrectFromIrect(C_Object(Rect)));
    end CreateIrectFromIrect;

	procedure GetBounds(rect	: in     IRect.Object;
						minx	:    out ossim_int32;
						miny	:    out  ossim_int32;
						maxx	:    out ossim_int32;
						maxy	:    out ossim_int32) is
		procedure GetBounds(
						rect	: in     Void_Ptr;
						minx	:    out ossim_int32;
						miny	:    out  ossim_int32;
						maxx	:    out ossim_int32;
						maxy	:    out ossim_int32) ;
        pragma Import(C, GetBounds, "getBounds");
	begin
		GetBounds(IRect.C_Object(Rect), minx, miny, maxx, maxy);
	end GetBounds;
	
	function UL(Rect : Irect.Object) return Ipt.Object is

		function UL(Rect : Void_Ptr) return Void_Ptr;
        pragma Import(C, UL, "ul");
		
	begin
		return Ipt.Create(UL(IRect.C_Object(Rect)));
	end UL;
	
	function UR(Rect : Irect.Object) return Ipt.Object is
		function UR(Rect : Void_Ptr) return Void_Ptr;
        pragma Import(C, UR, "ur");
		
	begin
		return Ipt.Create(UR(IRect.C_Object(Rect)));
	end UR;
	
	function LR(Rect : Irect.Object) return Ipt.Object is
		function LR(Rect : Void_Ptr) return Void_Ptr;
        pragma Import(C, LR, "lr");
		
	begin
		return Ipt.Create(LR(IRect.C_Object(Rect)));
	end LR;
	
	function LL(Rect : Irect.Object) return Ipt.Object is
		function LL(Rect : Void_Ptr) return Void_Ptr;
        pragma Import(C, LL, "ll");
		
	begin
		return Ipt.Create(LL(IRect.C_Object(Rect)));
	end LL;
	

    function Left(Rect : Object) return ossim_int32 is
		Point : Ipt.Object := UL(Rect);
	begin
		return IPt.GetX(Point);
	end Left;
	
    function Top(Rect : Object) return ossim_int32 is
		Point : Ipt.Object := UL(Rect);
	begin
		return IPt.GetY(Point);
	end Top;

    function Right(Rect : Object) return ossim_int32 is
		Point : Ipt.Object := LR(Rect);
	begin
		return IPt.GetX(Point);
	end Right;

    function Bottom(Rect : Object) return ossim_int32 is
		Point : Ipt.Object := LR(Rect);
	begin
		return IPt.GetX(Point);
	end Bottom;

    function Width(Rect : Object) return ossim_uint32 is
        function Width(Rect : Void_Ptr) return ossim_uint32;
        pragma Import(C, Width, "ossimGetIrectWidth");
    begin
        return Width(Rect.OssimObject);
    end Width;

    function Height(Rect : Object) return ossim_uint32 is
        function Height(Rect : Void_Ptr) return ossim_uint32;
        pragma Import(C, Height, "ossimGetIrectHeight");
    begin
        return Height(Rect.OssimObject);
    end Height;

    procedure WidthHeight(
			Rect 	: Object;
            Width 	:    out ossim_uint32;
            Height	:    out ossim_uint32) is
			
        procedure WidthHeight(
            Rect 	: Void_Ptr;
            Width	: System.Address;
            Height	: System.Address);
        pragma Import(C, WidthHeight, "ossimGetIrectWidthHeight");
		
    begin
        WidthHeight(C_Object(Rect), Width'Address, Height'Address);
    end WidthHeight;

    function "+"(Rect : Object; Point : Ipt.Object) return Object is

        function "+"(Rect : Void_Ptr; Point : Void_Ptr) return Void_Ptr;
        pragma Import(C, "+", "ossimIrectAddPt");

    begin
        return Create(C_Object(Rect) + Ipt.C_Object(Point));
    end "+";

    function "-"(Rect : Object; Point : Ipt.Object) return Object is

        function "-"(Rect : Void_Ptr; Point : Void_Ptr) return Void_Ptr;
        pragma Import(C, "-", "ossimIrectSubPt");

    begin
        return Create(C_Object(Rect) - Ipt.C_Object(Point));
    end "-";

	procedure Set_UL(Rect : Irect.Object; Point : Ipt.Object) is
				
        procedure Set_UL(
            Rect 	: Void_Ptr;
            Point	: Void_Ptr);
        pragma Import(C, Set_UL, "set_ul");
		
    begin
        Set_UL(C_Object(Rect), Ipt.C_Object(Point));
	end Set_UL;
	
	procedure Set_UR(Rect : Irect.Object; Point : Ipt.Object) is
				
        procedure Set_UR(
            Rect 	: Void_Ptr;
            Point	: Void_Ptr);
        pragma Import(C, Set_UR, "set_ur");
		
    begin
        Set_UR(C_Object(Rect), Ipt.C_Object(Point));
	end Set_UR;
	
	procedure Set_LR(Rect : Irect.Object; Point : Ipt.Object) is
				
        procedure Set_LR(
            Rect 	: Void_Ptr;
            Point	: Void_Ptr);
        pragma Import(C, Set_LR, "set_lr");
		
    begin
        Set_LR(C_Object(Rect), Ipt.C_Object(Point));
	end Set_LR;
	
	procedure Set_LL(Rect : Irect.Object; Point : Ipt.Object) is
				
        procedure Set_LL(
            Rect 	: Void_Ptr;
            Point	: Void_Ptr);
        pragma Import(C, Set_LL, "set_ll");
		
    begin
        Set_LL(C_Object(Rect), Ipt.C_Object(Point));
	end Set_LL;

	procedure Set_UL_X(Rect : Irect.Object; X : ossim_int32) is
				
        procedure Set_UL_X(
            Rect 	: Void_Ptr;
            X		: ossim_int32);
        pragma Import(C, Set_UL_X, "set_ulx");
		
    begin
        Set_UL_X(C_Object(Rect), X);
	end Set_UL_X;
	
	procedure Set_UR_X(Rect : Irect.Object; X : ossim_int32) is
				
        procedure Set_UR_X(
            Rect 	: Void_Ptr;
            X		: ossim_int32);
        pragma Import(C, Set_UR_X, "set_urx");
		
    begin
        Set_UR_X(C_Object(Rect), X);
	end Set_UR_X;
	
	procedure Set_LR_X(Rect : Irect.Object; X : ossim_int32) is
				
        procedure Set_LR_X(
            Rect 	: Void_Ptr;
            X		: ossim_int32);
        pragma Import(C, Set_LR_X, "set_lrx");
		
    begin
        Set_LR_X(C_Object(Rect), X);
	end Set_LR_X;
	
	procedure Set_LL_X(Rect : Irect.Object; X : ossim_int32) is
				
        procedure Set_LL_X(
            Rect 	: Void_Ptr;
            X		: ossim_int32);
        pragma Import(C, Set_LL_X, "set_llx");
		
    begin
        Set_LL_X(C_Object(Rect), X);
	end Set_LL_X;
	
	procedure Set_UL_Y(Rect : Irect.Object; Y : ossim_int32) is
				
        procedure Set_UL_Y(
            Rect 	: Void_Ptr;
            Y		: ossim_int32);
        pragma Import(C, Set_UL_Y, "set_uly");
		
    begin
        Set_UL_Y(C_Object(Rect), Y);
	end Set_UL_Y;
	
	procedure Set_UR_Y(Rect : Irect.Object; Y : ossim_int32) is
				
        procedure Set_UR_Y(
            Rect 	: Void_Ptr;
            Y		: ossim_int32);
        pragma Import(C, Set_UR_Y, "set_ury");
		
    begin
        Set_UR_Y(C_Object(Rect), Y);
	end Set_UR_Y;
	
	procedure Set_LR_Y(Rect : Irect.Object; Y : ossim_int32) is
				
        procedure Set_LR_Y(
            Rect 	: Void_Ptr;
            Y		: ossim_int32);
        pragma Import(C, Set_LR_Y, "set_lry");
		
    begin
        Set_LR_Y(C_Object(Rect), Y);
	end Set_LR_Y;
	
	procedure Set_LL_Y(Rect : Irect.Object; Y : ossim_int32) is
				
        procedure Set_LL_Y(
            Rect 	: Void_Ptr;
            Y		: ossim_int32);
        pragma Import(C, Set_LL_Y, "set_lly");
		
    begin
        Set_LL_Y(C_Object(Rect), Y);
	end Set_LL_Y;

	procedure Offset_Rect(
			Rect		: IRect.Object;
			Horizontal  : ossim_int32; 
			Vertical	: ossim_int32) is
			
		Point   : Ipt.Object;
		Offset  : Ipt.Object;
		
	begin
		Point := UL(Rect);
		Offset := Ipt.CreateIpt(Horizontal, Vertical);
		Point := Point + Offset;
		Set_UL(Rect, Point);
		Point := LR(Rect);
		Point := Point + Offset;
		Set_LR(Rect, Point);
	end Offset_Rect;

    procedure Free(Rect : Object) is
        procedure Free(Rect : Void_Ptr);
        pragma Import(C, Free, "ossimFreeRect");
    begin
        Free(Rect.OssimObject);
    end Free;

    function C_Object(Rect : Object) return Void_Ptr is
    begin
        return Rect.OssimObject;
    end C_Object;

end IRect;

