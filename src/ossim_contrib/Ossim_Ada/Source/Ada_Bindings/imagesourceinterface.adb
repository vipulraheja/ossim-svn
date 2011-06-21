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
package body ImageSourceInterface is

    function Create(C_Object : Void_Ptr) return Object is
        TheObject : Object;
    begin
        TheObject.OssimObject:= C_Object;
        return TheObject;
    end Create;
    
    procedure Free(handler : Object) is

        procedure Free(handler : void_ptr);
        pragma Import(C, Free, "ossimFreeObject");
            
    begin
        Free(Handler.ossimObject);
    end Free;

    function getBoundingRect(
            inter 	: Object;
            Res		: ossim_uint32:= 0) return IRect.Object is
                                                        
        function getBoundingRect(
                handler  : Void_Ptr;
                Res	 : ossim_uint32:= 0) return Void_Ptr;
        pragma Import(C, getBoundingRect, "getNewBoundingRect");
        
        Rect : Void_Ptr;
            
    begin
        Rect:= getBoundingRect(inter.ossimObject, Res);
        return IRect.Create(Rect);
    end getBoundingRect;

    function getTile(
            inter 		: Object; 
            Bounding_Rect 	: IRect.Object;
            Res 		: ossim_uint32:= 0) 
                return Ossim.Data.Rectilinear.Image.Object is
                
        function getTile(
                handler 	: void_ptr; 
                Bounding_Rect 	: Void_Ptr;
                Res		: ossim_uint32) return void_Ptr;
        pragma Import(C, getTile, "ossimGetTile");
            
    begin
        return Ossim.Data.Rectilinear.Image.Create(
            getTile(C_Object(inter), IRect.C_Object(Bounding_Rect), Res));
    end getTile;

    function C_Object(The_Object : Object'class) return Void_Ptr is
    begin
        return The_Object.OssimObject;
    end C_Object;
end ImageSourceInterface;
