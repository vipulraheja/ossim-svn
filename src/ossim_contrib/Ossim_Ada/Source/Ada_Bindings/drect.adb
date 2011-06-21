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
package body DRect is

    function Create(C_Object : Void_Ptr) return Object is
        TheObject : Object;
    begin
        TheObject.OssimObject:= C_Object;
        return TheObject;
    end Create;

    function Create return Object is

        function Create return Void_Ptr;
        pragma Import(C, Create, "ossimCreateDrect");

    begin
        return Create(Create);
    end Create;

    function Create(
            Ul_Corner 	: DPt.Object;
            Lr_Corner	: DPt.Object;
            Mode	: ossimCoordSysOrientMode := OSSIM_LEFT_HANDED) return Object is

        function Create(
            Ul_Corner 	: Void_Ptr;
            Lr_Corner	: Void_Ptr;
            Mode	: ossimCoordSysOrientMode := OSSIM_LEFT_HANDED) return
            Void_Ptr;
        pragma Import(C, Create, "ossimCreateCornerDrect");

    begin
        return Create(Create(DPt.C_Object(Ul_Corner),
                DPt.C_Object(Ul_Corner), Mode));
    end Create;

    function Create(
            Ul_Corner_X 	: Long_Float;
            Ul_Corner_Y 	: Long_Float;
            Lr_Corner_X 	: Long_Float;
            Lr_Corner_Y 	: Long_Float;
            Mode		: ossimCoordSysOrientMode := OSSIM_LEFT_HANDED) return Object is

        function Create(
            Ul_Corner_X 	: Long_Float;
            Ul_Corner_Y 	: Long_Float;
            Lr_Corner_X 	: Long_Float;
            Lr_Corner_Y 	: Long_Float;
            Mode		: ossimCoordSysOrientMode := OSSIM_LEFT_HANDED) return
            Void_Ptr;
        pragma Import(C, Create, "ossimCreatePointsDrect");

    begin
        return Create(Create(Ul_Corner_X, Ul_Corner_Y,
                Lr_Corner_X, Lr_Corner_Y, Mode));
    end Create;

    function CreateDRect(Rect : Object) return Object is

        function Create(Rect : Void_Ptr) return Void_Ptr;
        pragma Import(C, Create, "ossimCreateDRDrect");

    begin
        return Create(Create(C_Object(Rect)));
    end CreateDRect;

    function Create(Rect : IRect.Object) return Object is

        function Create(Rect : Void_Ptr) return Void_Ptr;
        pragma Import(C, Create, "ossimCreateIRDrect");

    begin
        return Create(Create(IRect.C_Object(Rect)));
    end Create;

    procedure Free(Rect : Object) is
        procedure Free(Rect : Void_Ptr);
        pragma Import(C, Free, "ossimDeleteDrect");
    begin
        Free(Rect.OssimObject);
    end Free;

    function C_Object(Rect : Object) return Void_Ptr is
    begin
        return Rect.OssimObject;
    end C_Object;

end DRect;

