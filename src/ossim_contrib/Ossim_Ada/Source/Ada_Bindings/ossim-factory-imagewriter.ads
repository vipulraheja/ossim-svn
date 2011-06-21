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
with System;
with OssimKeywordlist;
with OssimString;
with OssimString.Filename;
with Ossim.Connectable.Source.Output.Imagewriter.File;
pragma Elaborate_All(Ossim.Connectable.Source.Output.Imagewriter.File);
package Ossim.Factory.Imagewriter is

    type Object is new Ossim.Factory.Object with private;

    function Create(C_Object : Void_Ptr) return Object;

    function CreateWriter(
            kwl 	: OssimKeywordlist.Object'class;
            Prefix	: String := "") 
            return Ossim.Connectable.Source.Output.Imagewriter.File.Object;

    function CreateWriter( typeName : OssimString.Object'class) 
        return Ossim.Connectable.Source.Output.Imagewriter.File.Object;

    function CreateWriter(Filetype : String) 
        return Ossim.Connectable.Source.Output.Imagewriter.File.Object;
    --
    -- getImageTypeList.  This is the actual image type name.  So for
    -- example, ossimTiffWriter has several image types.  Some of these
    -- include TIFF_TILED, TIFF_TILED_BAND_SEPARATE ... etc.  The ossimGdalWriter
    -- may include GDAL_IMAGINE_HFA, GDAL_RGB_NITF, GDAL_JPEG20000, ... etc
    -- A writer should be able to be instantiated by this name as well as a class name
    --
    function GetImageTypeList return OssimString.StringList;

private

    type Object is new Ossim.Factory.Object with
    record
        null;
    end record;

end Ossim.Factory.Imagewriter;
