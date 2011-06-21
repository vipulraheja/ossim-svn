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
package body Ossim.Projection.Map is

    function Create(C_Object : Void_Ptr) return Object is
        the_Object : Object;
    begin
        the_Object.OssimObject:= C_Object;
        return the_Object;
    end Create;
    
    procedure SetDecimalDegreesPerPixel(
                Projection 	: Ossim.Projection.Object'class;
                Point		: Dpt.Object) is
                            
        procedure SetDecimalDegreesPerPixel(
                        Projection 	: Void_Ptr;
                        Point		: Void_Ptr);
        pragma Import(C, SetDecimalDegreesPerPixel, "setDecimalDegreesPerPixel");
            
    begin
        SetDecimalDegreesPerPixel(Ossim.C_Object(Projection),Dpt.C_Object(Point));
    end SetDecimalDegreesPerPixel;
    
--    function C_Object(the_Object : Object'class) return Void_Ptr is
--    begin
--        return the_Object.OssimObject;
--    end C_Object;

end Ossim.Projection.Map;
