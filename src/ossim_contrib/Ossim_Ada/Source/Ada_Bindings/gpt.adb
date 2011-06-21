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
package body Gpt is

    function Create(C_Object : Void_Ptr) return Object is
        TheObject : Object;
    begin
        TheObject.OssimObject:= C_Object;
        return TheObject;
    end Create;

    function CreateGpt(
            Latitude	: IEEE_Float_64;
            Longitude	: IEEE_Float_64;
            Elevation	: IEEE_Float_64 ) return Object is

        function CreateGpt(
            Latitude	: IEEE_Float_64;
            Longitude	: IEEE_Float_64;
            Elevation	: IEEE_Float_64 ) return Void_Ptr;
        pragma Import(C, CreateGpt, "ossimCreateGptwgs84");

    begin
        return Create(CreateGpt(Latitude, Longitude, Elevation));
    end CreateGpt;

    function Get_Lat(Point : Object) return IEEE_Float_64 is

        function Get_Lat(Point : Void_Ptr) return IEEE_Float_64;
        pragma Import(C, Get_Lat, "ossimGetGeoLat");

    begin
        return Get_Lat(C_Object(Point));
    end Get_Lat;

    procedure Set_Lat(Point : Object; Delta_Lat : IEEE_Float_64) is

        procedure Set_Lat(Point : Void_Ptr; Delta_Lat : IEEE_Float_64);
        pragma Import(C, Set_Lat, "ossimSetGeoLat");

    begin
        Set_Lat(C_Object(Point), Delta_Lat);
    end Set_Lat;

    function Get_Long(Point : Object) return IEEE_Float_64 is

        function Get_Long(Point : Void_Ptr) return IEEE_Float_64;
        pragma Import(C, Get_Long, "ossimGetGeoLong");

    begin
        return Get_Long(C_Object(Point));
    end Get_Long;

    procedure Set_Long(Point : Object; Delta_Long : IEEE_Float_64) is

        procedure Set_Long(Point : Void_Ptr; Delta_Long : IEEE_Float_64);
        pragma Import(C, Set_Long, "ossimSetGeoLong");

    begin
        Set_Long(C_Object(Point), Delta_Long);
    end Set_Long;

    function Get_Elev(Point : Object) return IEEE_Float_64 is

        function Get_Elev(Point : Void_Ptr) return IEEE_Float_64;
        pragma Import(C, Get_Elev, "ossimGetGeoElev");

    begin
        return Get_Elev(C_Object(Point));
    end Get_Elev;

    procedure Set_Elev(Point : Object; Delta_Elev : IEEE_Float_64) is

        procedure Set_Elev(Point : Void_Ptr; Delta_Elev : IEEE_Float_64);
        pragma Import(C, Set_Elev, "ossimSetGeoElev");

    begin
        Set_Elev(C_Object(Point), Delta_Elev);
    end Set_Elev;

    procedure Add_Lat(Point : Object; Delta_Lat : IEEE_Float_64) is

        Latitude : IEEE_Float_64:= Get_Lat(Point) + Delta_Lat;

    begin
        Set_Lat(Point, Latitude);
    end Add_Lat;

    procedure Add_Long(Point : Object; Delta_Lon : IEEE_Float_64) is

        Longitude : IEEE_Float_64:= Get_Long(Point) + Delta_Lon;

    begin
        Set_Long(Point, Longitude);
    end Add_Long;

    procedure Add_Elev(Point : Object; Delta_Elev : IEEE_Float_64) is

        Elevation : IEEE_Float_64:= Get_Elev(Point) + Delta_Elev;

    begin
        Set_Elev(Point, Elevation);
    end Add_Elev;
	
	procedure Free(Point : Object) is
        procedure Free(Point : Void_Ptr);
        pragma Import(C, Free, "OssimFreeGpt");
	begin
		Free(C_Object(Point));
	end Free;

    function C_Object(Point : Object) return Void_Ptr is
    begin
        return Point.OssimObject;
    end C_Object;

end Gpt;

