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
package body Ossim.Connectable.Source.Image.Filter.Polycutter is

    function Create(C_Object : Void_Ptr) return Object is
       the_Object : Object;
    begin
        the_Object.OssimObject:= C_Object;
        return the_Object; 
    end Create;

    function Create return Object is
    
        function CreateCutter return Void_Ptr;
        pragma import(C, CreateCutter, "createOssimPolyCutter");

    begin
        return Create(CreateCutter);
    end Create;

    function Create(
            Source	: Ossim.Connectable.Object'class;
            Bounds	: Polygon.Object) return Object is

        function Create(Source : Void_Ptr;
						Bounds : Void_Ptr) return Void_Ptr;
        pragma import(C, Create, "ossimCreatePolyCutter");

    begin
        return Create(Create(Ossim.C_Object(Source), Polygon.C_Object(Bounds)));
    end Create;

    procedure setCutType(
            PolyCut : Object'class;
            cutType : ossimPolyCutterCutType) is

        procedure SetCutType(
                PolyCut : void_ptr;
                cutType	: ossimPolyCutterCutType);
        pragma Import(C, setCutType, "setCutType");
    
    begin
        SetCutType(Ossim.C_Object(PolyCut), CutType);
    end setCutType;

    function GetBoundingRect(
            Polygon	: Object'class;
            ResLevel	: Interfaces.Unsigned_32 := 0) return IRect.Object is

        function GetBoundingRect(
                Polygon		: Void_Ptr;
                ResLevel	: Interfaces.Unsigned_32 := 0) return Void_Ptr;
        pragma Import(C, GetBoundingRect, "polyCutterGetBoundingRect");
                    
    begin
        return IRect.Create(GetBoundingRect(Ossim.C_Object(Polygon), ResLevel));
    end GetBoundingRect;

end Ossim.Connectable.Source.Image.Filter.Polycutter;
