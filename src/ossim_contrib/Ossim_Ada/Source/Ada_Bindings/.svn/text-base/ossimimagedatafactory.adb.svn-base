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
package body OssimImageDataFactory is

    function Create(C_Object : Void_Ptr) return Object is
       the_Object : Object;
    begin
        the_Object.OssimObject:= C_Object;
        return the_Object; 
    end Create;

	function Create(
		Owner			: Ossim.Connectable.Source.object'class;
		Input_Source	: Ossim.Connectable.Source.Image.object'class) return 
											Ossim.Data.Rectilinear.Image.Object is

		function Create(
			Owner			: Void_Ptr;
			Input_Source	: Void_Ptr) return Void_Ptr;
		pragma Import(C, Create, "ossimCImageDataFactoryCreate");

	begin
		return Ossim.Data.Rectilinear.Image.Create(
			Create(Ossim.C_Object(Owner), Ossim.C_Object(Input_Source)));
	end Create;

    function C_Object(theObject : Object'class) return Void_Ptr is
    begin
        return theObject.OssimObject;
    end C_Object;

end OssimImageDataFactory;
