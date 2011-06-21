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
package body Ossim.Data is

    function Create(C_Object : Void_Ptr) return Object is
       the_Object : Object;
    begin
        the_Object.OssimObject:= C_Object;
        return the_Object; 
    end Create;

	function GetDataObjectStatus(Data : Object'class) return ossimDataObjectStatus is

		function GetDataObjectStatus(Data : Void_Ptr) return ossimDataObjectStatus;
		pragma import(C, GetDataObjectStatus, "getDataObjectStatus");

	begin
		return GetDataObjectStatus(ossim.C_Object(Data));
	end GetDataObjectStatus;
	
	procedure Free(Data : Object'class) is

		procedure Free(Data : Void_Ptr);
		pragma import(C, Free, "freeDataObjectStatus");

	begin
		Free(ossim.C_Object(Data));
	end Free;

end Ossim.Data;
