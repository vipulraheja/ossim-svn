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
package body Ossim.Connectable.Source.Image is

    function Create(C_Object : Void_Ptr) return Object is
       the_Object : Object;
    begin
        the_Object.OssimObject:= C_Object;
        return the_Object; 
    end Create;

    function GetOutputScalarType(
            Handler : Object'class) return OssimScalarType is

        function GetOutputScalarType(
            Handler : Void_Ptr) return OssimScalarType;
        pragma Import(C, GetOutputScalarType, "getOutputScalarType");

    begin
        return GetOutputScalarType(Ossim.C_Object(Handler));
    end GetOutputScalarType;

	function GetTile(
			Handler			: Object'class; 
			Bounding_Rect   : IRect.Object;
			ResLevel		: ossim_uint32 := 0) return Ossim.Data.Rectilinear.Image.Object is

		function GetTile(
				Handler			: Void_Ptr; 
				Bounding_Rect   : Void_Ptr;
				ResLevel		: ossim_uint32) return Void_Ptr;
		pragma Import(C, GetTile, "getTile");

	begin
		return Ossim.Data.Rectilinear.Image.Create(
			GetTile(Ossim.C_Object(Handler), IRect.C_Object(Bounding_Rect), ResLevel));
	end GetTile;
	
	procedure Free(Handler : Object'class) is
		procedure Free(Handler : Void_Ptr);
		pragma Import(C, Free, "freeOssimImageSource");
	begin
		Free(Ossim.C_Object(Handler));
	end Free;

end Ossim.Connectable.Source.Image;
