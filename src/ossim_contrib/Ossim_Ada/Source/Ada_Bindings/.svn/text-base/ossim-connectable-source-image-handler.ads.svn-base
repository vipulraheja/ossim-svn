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
with Interfaces; use Interfaces;
with Interfaces.C.Extensions;
 use Interfaces.C.Extensions;
with Ossim_Common; use Ossim_Common;
with IRect;
--with ossim.ImageData;
with ossim_Constants; use ossim_Constants;
with OssimString;
with OssimString.Filename;
with Ossim.Data.Rectilinear.Image;
with Ossim;
with OssimKeywordlist;
package Ossim.Connectable.Source.Image.Handler is

    type Object is new Ossim.Connectable.Source.Image.Object with private;

    function Create(C_Object : Void_Ptr) return Object;
	
    function Is_Null(Handler : Object) return Boolean;

    function getNumberOfDecimationLevels(handler : Object) return ossim_int32;

    function GetFilename(Handler : Object) return OssimString.Object;

    function getFilename(handler : Object) return String;

    function Open(Filename : OssimString.Filename.Object) return Object;

    function Open(Filename : String) return Object;

	function Open(Keywords : OssimKeywordlist.Object) return Object;

    function getOutputScalarType(handler : Object'class) return ossimScalarType;

    function getNumberOfLines(
            Handler				: Object;
            Reduced_Res_Level 	: ossim_int32:= 0) return ossim_int32;
            
    function getNumberOfSamples(
            Handler				: Object;
            Reduced_Res_Level 	: ossim_int32:= 0) return ossim_int32;

    function getBoundingRect(
            Handler				: Object;
            Reduced_Res_Level 	: ossim_int32:= 0) return IRect.Object;

    procedure Free(handler : Object);

private

    type Object is new Ossim.Connectable.Source.Image.Object with
    record
        null;
    end record;

end Ossim.Connectable.Source.Image.Handler;
