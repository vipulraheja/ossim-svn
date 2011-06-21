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
with IRect;
with Ossim.Projection;
with GeoPolygon;
package Ossim.Connectable.Source.Image.Filter.Polycutter.Geo is

    type Object is new Ossim.Connectable.Source.Image.Filter.Polycutter.Object with private;

    function Create(C_Object : Void_Ptr) return Object;

    function Create return Object;

    function Create(Source : Ossim.Connectable.Object'class) return Object;

    function Create(
            Source	: Ossim.Connectable.Object'class;
            Bounds	: Polygon.Object) return Object;

    procedure Delete(Cutter : Object);
    
    procedure AddPolygon(
            Cutter  : Object; 
            Polygon : GeoPolygon.Object); 
    
    procedure setCutType(
            PolyCut : Object'class;
            cutType : ossimPolyCutterCutType);
            
    -- The view projection used to project the ground coordinates.
    function GetView(Cutter : Object) return Ossim.Projection.Object;

    function setView(Cutter 	: Object;
                     BaseObject	: Ossim.Projection.Object;
                     OwnsTheView: Boolean := False) return Boolean;

    function GetBoundingRect(
            Polygon	: Object'class;
            ResLevel	: Interfaces.Unsigned_32 := 0) return IRect.Object;

private

    type Object is new Ossim.Connectable.Source.Image.Filter.Polycutter.Object with
    record
        null;
    end record;
    
end Ossim.Connectable.Source.Image.Filter.Polycutter.Geo;
