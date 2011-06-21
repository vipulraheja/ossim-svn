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
with Polygon;
with IRect;
package Ossim.Connectable.Source.Image.Filter.Polycutter is

    type Object is new Ossim.Connectable.Source.Image.Filter.Object with private;

    type ossimPolyCutterCutType is (
                OSSIM_POLY_NULL_INSIDE, 
                OSSIM_POLY_NULL_OUTSIDE);
    for ossimPolyCutterCutType use (0, 1);
    for ossimPolyCutterCutType'size use 32;

    function Create(C_Object : Void_Ptr) return Object;

    function Create return Object;

    function Create(
            Source	: Ossim.Connectable.Object'class;
            Bounds	: Polygon.Object) return Object;
    
    procedure setCutType(
            PolyCut : Object'class;
            cutType : ossimPolyCutterCutType);

    function GetBoundingRect(
            Polygon	: Object'class;
            ResLevel	: Interfaces.Unsigned_32 := 0) return IRect.Object;

private

    type Object is new Ossim.Connectable.Source.Image.Filter.Object with
    record
        null;
    end record;

end Ossim.Connectable.Source.Image.Filter.Polycutter;
