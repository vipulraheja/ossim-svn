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
package body Ossim.Connectable.Source.Image.Handler.TiffTileSource is

    function Create(C_Object : Void_Ptr) return Object is
        the_Object : Object;
    begin
        the_Object.OssimObject := C_Object;
        return the_Object;
    end Create;

    procedure setApplyColorPaletteFlag(
		Instance	: Object;
		Flag		: Boolean) is
		
        procedure setApplyColorPaletteFlag(
				instance	: Void_Ptr;
				flag		: Boolean);
        pragma Import(C, setApplyColorPaletteFlag, "setApplyColorPaletteFlag");

    begin
        setApplyColorPaletteFlag(C_Object(Instance), Flag);
    end setApplyColorPaletteFlag;

    procedure setApplyColorPaletteFlag(
		Instance	: Ossim.Connectable.Source.Image.Handler.Object;
		Flag		: Boolean) is
		
        procedure setApplyColorPaletteFlag(
				instance	: Void_Ptr;
				flag		: Boolean);
        pragma Import(C, setApplyColorPaletteFlag, "setApplyColorPaletteFlag");

    begin
        setApplyColorPaletteFlag(C_Object(Instance), Flag);
    end setApplyColorPaletteFlag;


	function getApplyColorPaletteFlag(Instance	: Object) return Boolean is
	
        function getApplyColorPaletteFlag(instance : Void_Ptr) return boolean;
        pragma Import(C, getApplyColorPaletteFlag, "getApplyColorPaletteFlag");

	begin
		return getApplyColorPaletteFlag(C_Object(Instance));
	end getApplyColorPaletteFlag;

end Ossim.Connectable.Source.Image.Handler.TiffTileSource;



