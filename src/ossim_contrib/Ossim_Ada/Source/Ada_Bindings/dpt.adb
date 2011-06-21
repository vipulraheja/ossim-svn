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
with Interfaces.C.Strings; use Interfaces.C.Strings;
package body Dpt is

    function Create(C_Object : Void_Ptr) return Object is
        TheObject : Object;
    begin
        TheObject.OssimObject:= C_Object;
        return TheObject;
    end Create;

    function Create(X, Y : IEEE_Float_64) return Object is

        function Create(X, Y : IEEE_Float_64) return Void_Ptr;
        pragma Import(C, Create, "ossimCreateDpt");

    begin
        return Create(Create(X, Y));
    end Create;

	procedure Free(Point : Object) is
        procedure Free(Point : Void_Ptr);
        pragma Import(C, Free, "ossimCFreeDpt");
	begin
		Free(C_Object(Point));
	end Free;

    function C_Object(Point : Object) return Void_Ptr is
    begin
        return Point.OssimObject;
    end C_Object;

end Dpt;

