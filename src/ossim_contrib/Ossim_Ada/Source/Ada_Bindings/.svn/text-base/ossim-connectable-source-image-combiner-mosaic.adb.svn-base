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
with Ossim.Connectable;
package body Ossim.Connectable.Source.Image.Combiner.Mosaic is

    function Create(C_Object : Void_Ptr) return Object is
       the_Object : Object;
    begin
        the_Object.OssimObject:= C_Object;
        return the_Object; 
    end Create;

    function Create return object is

        function Create_Mosaic_C return Void_Ptr;
        pragma Import(C, Create_Mosaic_C, "ossimCreateImageMosaic");

    begin
        return Create(Create_Mosaic_C);
    end Create;

    function Create(inputObject : Object'class) return Object is

        Mosaic_Object	: Object := Create;
        index		: ossim_int32;
    begin
        index:= ConnectMyInputTo(inputObject, Mosaic_Object);
        return Mosaic_Object;
    end Create;
	
    procedure Free(Mosaic : Object'class) is

        procedure Delete(Mosaic : Void_Ptr);
        pragma Import(C, Delete, "ossimDeleteImageMosaic");

    begin
        Delete(Ossim.C_Object(Mosaic));
    end Free;

end Ossim.Connectable.Source.Image.Combiner.Mosaic;

