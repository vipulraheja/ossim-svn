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
with Interfaces; use Interfaces;
with Interfaces.C.Extensions; use Interfaces.C.Extensions;
with Ossim_Constants;
 use Ossim_Constants;
with OssimString.Filename;
with Listener.Process.StdOutProgress;
with Listener.Process.ProgressPercent;
with OssimString;
with ossimKeywordlist;
package Ossim.Connectable.Source.Output.Imagewriter.File is

    Pragma Elaborate_Body;

    type Object is new Ossim.Connectable.Source.Output.Imagewriter.Object with private;

    function Create(C_Object : Void_Ptr) return Object;

    function Is_Null(Writer : Object) return Boolean;

    procedure SetFilename(  Writer	: Object;
                            Filename 	: ossimString.Filename.Object);

    procedure SetFilename(  Writer	: Object;
                            Filename : String);

    procedure Execute(Writer : Object);

    function AddListener(
        Writer 		: Object;
        theListener	: Listener.Process.StdOutProgress.Object) return Boolean;

    function AddListener(
        Writer 		: Object;
        theListener	: Listener.Process.ProgressPercent.Object) return Boolean;

    function RemoveListener(
        Writer 		: Object;
        theListener 	: Listener.Process.StdOutProgress.Object) return Boolean;

    function RemoveListener(
        Writer 		: Object;
        theListener 	: Listener.Process.ProgressPercent.Object) return Boolean;

    function GetNumberImageType(
        TheList : OssimString.StringList) return ossim_uint32;

    function GetImageType(
        TheList : OssimString.StringList;
        Index : ossim_uint32) return String;

    procedure SetOutputName(
        Writer 		: Object;
        OutputName	: String);

	procedure Writer_Abort(Writer : Object);

    procedure Free(handler : Object);

private

    type Object is new  Ossim.Connectable.Source.Output.Imagewriter.Object with
    record
        null;
    end record;

end Ossim.Connectable.Source.Output.Imagewriter.File;
