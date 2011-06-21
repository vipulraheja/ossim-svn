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
package body Ipt is

    function Create(C_Object : Void_Ptr) return Object is
        TheObject : Object;
    begin
        TheObject.OssimObject:= C_Object;
        return TheObject;
    end Create;

    function CreateIpt( X	: ossim_int32;
						Y	: ossim_int32) return Object is

        function CreateIpt( X	: ossim_int32;
							Y	: ossim_int32) return Void_Ptr;
        pragma Import(C, CreateIpt, "ossimCreateIpt");

    begin
        return Create(CreateIpt(X, Y));
    end CreateIpt;

    procedure SetX(Point : Object; X : ossim_int32) is

        procedure SetX(Point : Void_Ptr; X : ossim_int32);
        pragma Import(C, SetX, "ossimSetX");

    begin
        SetX(C_Object(Point), X);
    end SetX;

    function GetX(Point : Object) return ossim_int32 is

        function GetX(Point : Void_Ptr) return ossim_int32;
        pragma Import(C, GetX, "ossimGetX");

    begin
        return GetX(C_Object(Point));
    end GetX;

    procedure SetY(Point : Object; Y : ossim_int32) is
        procedure SetY(Point : Void_Ptr; Y : ossim_int32);
        pragma Import(C, SetY, "ossimSetY");

    begin
        SetY(C_Object(Point), Y);
    end SetY;

    function GetY(Point : Object) return ossim_int32 is

        function GetY(Point : Void_Ptr) return ossim_int32;
        pragma Import(C, GetY, "ossimGetY");

    begin
        return GetY(C_Object(Point));
    end GetY;

    function "+"(Point : Object; offset : Object) return Object is
	begin
		return CreateIpt(GetX(Point) + GetX(Offset), GetY(Point) + GetY(Offset));
	end "+";
	
    function "-"(Point : Object; offset : Object) return Object is
	begin
		return CreateIpt(GetX(Point) - GetX(Offset), GetY(Point) - GetY(Offset));
	end "-";
	
	procedure Free(Point : Object) is

        procedure Free(Point : Void_Ptr);
        pragma Import(C, Free, "ossimFreeCIpt");

	begin
		Free(C_Object(Point));
	end Free;


    function C_Object(Point : Object) return Void_Ptr is
    begin
        return Point.OssimObject;
    end C_Object;


end Ipt;

