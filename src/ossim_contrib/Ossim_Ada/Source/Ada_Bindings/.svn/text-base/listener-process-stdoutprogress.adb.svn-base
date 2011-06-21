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
package body Listener.Process.StdOutProgress is

    function Create(C_Object : Void_Ptr) return Object is
        TheObject : Object;
    begin
        TheObject.OssimObject:= C_Object;
        return TheObject;
    end Create;

    function Create(Precision	: Long_Integer:= 0;
                    flushStream : Boolean := False) return Object is
                    
        function createOssimStdOutProgress(
                Precision	: Long_Integer;
                flushStream : Boolean) return Void_Ptr;
        pragma Import(C, createOssimStdOutProgress, "ossimCreateStdOutProgress");
        
    begin
        return Create(createOssimStdOutProgress(Precision, FlushStream));
    end Create;

	procedure Free(Instance : Object) is
        procedure Free(Instance : Void_Ptr);
        pragma Import(C, Free, "ossimFreeStdOutProgress");
	begin
		Free(Listener.C_Object(Instance));
	end Free;

end Listener.Process.StdOutProgress;
