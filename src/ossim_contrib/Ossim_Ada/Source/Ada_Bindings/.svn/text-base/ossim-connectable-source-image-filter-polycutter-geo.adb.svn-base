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
package body Ossim.Connectable.Source.Image.Filter.Polycutter.Geo is

    function Create(C_Object : Void_Ptr) return Object is
        the_Object : Object;
    begin
        the_Object.OssimObject:= C_Object;
        return the_Object; 
    end Create;
    
    function Create return Object is
    
        function CreateCutter return Void_Ptr;
        pragma import(C, CreateCutter, "createOssimGeoPolyCutter");

    begin
        return Create(CreateCutter);
    end Create;

    function Create(Source : Ossim.Connectable.Object'class) return Object is
    
        function CreateCutter(Source : Void_Ptr) return Void_Ptr;
        pragma import(C, CreateCutter, "createConnectedOssimGeoPolyCutter");

    begin
        return Create(CreateCutter(Ossim.C_Object(Source)));
    end Create;

    function Create(
            Source	: Ossim.Connectable.Object'class;
            Bounds	: Polygon.Object) return Object is
    begin
        return Create(Source);
    end Create;
    
    procedure Delete(Cutter : Object) is

        procedure Delete(cutter : void_ptr);
        pragma import(C, Delete, "deleteGeoPolyCutter");

    begin
        Delete(Ossim.C_Object(Cutter));
    end Delete;
    
    procedure AddPolygon(Cutter  : Object; 
                         Polygon : GeoPolygon.Object) is

        procedure AddPolygon(cutter : void_ptr; 
							polygon : System.Address);
        pragma import(C, AddPolygon, "addGeoPolygon");

    begin
        AddPolygon(Ossim.C_Object(Cutter), GeoPolygon.C_Object(Polygon)'address);
    end AddPolygon;

    procedure setCutType(
            PolyCut : Object'class;
            cutType : OssimPolyCutterCutType) is

        procedure SetCutType(
                PolyCut : void_ptr;
                cutType	: ossimPolyCutterCutType);
        pragma Import(C, setCutType, "setCutType");
    
    begin
        SetCutType(Ossim.C_Object(PolyCut), CutType);
    end setCutType;

    function SetView(Cutter	: Object;
                     BaseObject	: Ossim.Projection.Object;
                     OwnsTheView: Boolean := False) return Boolean is
                                        
        function SetView(Cutter	: Void_Ptr;
                            BaseObject	: Void_Ptr;
                            OwnsTheView: Boolean := False) return Boolean;
        pragma Import(C, SetView, "ossimGeoPolyCutterSetView");

    begin
        return SetView(Ossim.C_Object(Cutter), Ossim.C_Object(BaseObject),
                OwnsTheView);
    end SetView;
    
    -- The view projection used to project the ground coordinates.
    function GetView(Cutter : Object) return Ossim.Projection.Object is

        function GetView(Cutter		: Void_Ptr) return Void_Ptr;
        pragma Import(C, GetView, "geoPolyCutterGetView");
            
    begin
        return Ossim.Projection.Create(GetView(Ossim.C_Object(Cutter)));
    end GetView;

    function GetBoundingRect(
            Polygon	: Object'class;
            ResLevel	: Interfaces.Unsigned_32 := 0) return IRect.Object is

    begin
        return GetBoundingRect(
            Ossim.Connectable.Source.Image.Filter.Polycutter.Object(Polygon), ResLevel);
    end GetBoundingRect;

end Ossim.Connectable.Source.Image.Filter.Polycutter.Geo;
