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
with System; use System;
package body Ossim.Projection is

    function Create(C_Object : Void_Ptr) return Object is
        the_Object : Object;
    begin
        the_Object.OssimObject:= C_Object;
        return the_Object;
    end Create;

    function Is_Null(Projection : Object) return Boolean is
    begin
        return Projection.OssimObject = System.Null_Address;
    end Is_Null;

--    function C_Object(the_Object : Object'class) return Void_Ptr is
--    begin
--        return the_Object.OssimObject;
--    end C_Object;

end Ossim.Projection;

