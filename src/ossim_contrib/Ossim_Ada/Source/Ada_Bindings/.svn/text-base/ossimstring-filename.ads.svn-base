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
with Interfaces.C.Extensions; use Interfaces.C.Extensions;
package Ossimstring.Filename is

    type Object is new OssimString.Object with private;

    type AccessModes is (
        OSSIM_EXIST,
        OSSIM_EXE,
        OSSIM_WRITE,
        OSSIM_READ,
        OSSIM_READ_WRITE);
    for AccessModes'Size use 32;
    for AccessModes use (0, 1, 2, 4, 6);

    function Create(C_Object : Void_Ptr) return Object;

    function Create(Filename : String) return Object;

    procedure Create(Filename : in out Object);

--    function Create(Filename : OssimString.Object'Class) return Object;

	procedure Free(Filename : in out Object);
	
    function CreateStringList return StringList;
    pragma Import(C, CreateStringList, "ossimCreateStringVector");

    function GetNumberItems(TheList : StringList) return Integer_32;
    pragma Import(C, GetNumberItems, "ossimGetNumberOfStrings");

    procedure StringList_Free(List : StringList);
    pragma Import(C, StringList_Free, "ossimFreeStringVector");

    function GetossimString(
        TheList : OssimString.StringList;
        Index 	: Ossim_Uint32) return OssimString.Object;

    procedure ConvertBackToForwardSlashes(Filename : in out String);
    procedure ConvertForwardToBackSlashes(Filename : in out String);

    -- Methods to test ossimFilename for various states.
    function Exists(Filename : Object) return Boolean;
    function IsFile(Filename : Object) return Boolean;
    function IsDir(Filename : Object) return Boolean;
    function IsReadable(Filename : Object) return Boolean;
    function IsWritable(Filename : Object) return Boolean;
    function IsExecutable(Filename : Object) return Boolean;
    function FileSize(Filename : Object) return Ossim_Int64;

    -- Methods to access parts of the ossimFilename.
    function Ext(Filename : Object) return OssimString.Object;
    function File(Filename : Object) return OssimString.Object;
    function Path(Filename : Object) return OssimString.Object;
    function Drive(Filename : Object) return OssimString.Object;
    function FileNoExtension(Filename : Object) return OssimString.Object;

    function SetExtension(
        Filename : Object;
        Ext	 : OssimString.Object) return Object;
    function SetPath(
        Filename : Object;
        Path	 : OssimString.Object) return Object;
    function SetFile(
        Filename : Object;
        File	 : OssimString.Object) return Object;

    procedure Split(
        Filename : Object;
        DrivePart: OssimString.Object;
        PathPart : OssimString.Object;
        FilePart : OssimString.Object;
        ExtPart  : OssimString.Object);

    procedure Merge(
        Filename : Object;
        DrivePart: OssimString.Object;
        PathPart : OssimString.Object;
        FilePart : OssimString.Object;
        ExtPart  : OssimString.Object);

    --
    -- Returns file appended onto this string. Path seperator is always placed
    -- between this and file.  Returns file if this string is empty.
    -- Given: this = /foo  and file  = bar output  = /foo/bar
    -- Given: this = /foo/ and file  = bar output  = /foo/bar
    --
    function DirCat(
        Pathname : Object;
        File	 : Object) return Object;

    function CreateDirectory(
        Filename 	: Object;
        RecurseFlag	: Boolean := True;
        Perm		: Integer := 0777) return Boolean;

    function GetossimString(
            TheList : StringList; 
            Index   : Ossim_Uint32) return Object;
    --
    -- Removes pathname from filesystem if supported by platform.
    -- Return true on success, false on error.
    -- If supported will set errno and output equivalent string if one occurs.
    --
    function Remove(Filename : Object;
        Pathname : System.Address) return Boolean;

    --
    -- since windows uses \ for path separation
    -- and unix / we need to be consistent.
    --
    ThePathSeparator : Character;
    pragma Import(C, ThePathSeparator, "thePathSeparator");

    procedure Free(Filename : Object'Class);

    function Get_Filename_String(Filename : Object) return String;

    function C_Object(The_Object : Object'class) return Void_Ptr;

private

    type Object is new OssimString.Object with
        record
        null;
    end record;

end Ossimstring.Filename;

