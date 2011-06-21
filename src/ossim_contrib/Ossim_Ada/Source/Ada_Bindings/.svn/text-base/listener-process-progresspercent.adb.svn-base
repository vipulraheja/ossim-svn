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
package body Listener.Process.ProgressPercent is

    function Create(C_Object : Void_Ptr) return Object is
        TheObject : Object;
    begin
        TheObject.OssimObject:= C_Object;
        return TheObject;
    end Create;

    function Create( Precision	 : Long_Integer:= 0;
                     flushStream : Boolean := False) return Object is
                    
        function createOssimStdOutProgress(
                Precision	: Long_Integer;
                flushStream : Boolean) return Void_Ptr;
        pragma Import(C, createOssimStdOutProgress, "ossimCreateProgressPercent");
        
    begin
        return Create(createOssimStdOutProgress(Precision, FlushStream));
    end Create;

    function Get_Percent_Complete(Progress : Object) return Long_Float is
    
        function Get_Percent_Complete(Progress : Void_Ptr) return Long_Float;
        pragma Import(C, Get_Percent_Complete, "Get_Percent_Complete");

    begin
        return Get_Percent_Complete(Listener.C_Object(Progress));
    end Get_Percent_Complete;
	
	procedure Free(Progress : Object) is
        procedure Free(Progress : Void_Ptr);
        pragma Import(C, Free, "ossimFreeProgressPercent");
	begin
		Free(Listener.C_Object(Progress));
	end Free;

end Listener.Process.ProgressPercent;
