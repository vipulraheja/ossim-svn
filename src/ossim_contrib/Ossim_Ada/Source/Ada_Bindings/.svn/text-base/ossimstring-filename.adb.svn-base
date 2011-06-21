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
with Interfaces.C.Strings; use Interfaces.C.Strings;
package body Ossimstring.Filename is

    function Create(C_Object : Void_Ptr) return Object is
        the_Object : Object;
     begin
        the_Object.OSSIMObject := C_Object;
        return the_Object; 
    end Create;

    function Create(Filename : String) return Object is
    
        function Create(Filename : System.Address) return Void_Ptr;
        pragma Import(C, Create, "ossimCreateString");

        TheObject : Object;
        AdaString_Null : String(Filename'First..Filename'Last + 1) := Filename & ASCII.Nul;

    begin
        TheObject.OssimObject:= Create(AdaString_Null'Address);
        return TheObject;
    end Create;

    procedure Create(Filename : in out Object) is
    begin
        OssimString.Create(Filename);
    end Create;

--    function Create(Filename : OssimString.Object'Class) return Object is
--    begin
--        return Create(Filename);
--    end Create;

	procedure Free(Filename : in out Object) is
        procedure Free(Filename : Void_Ptr);
        pragma Import(C, Free, "ossimFreeFilename");
	begin
		Free(OssimString.Filename.C_Object(Filename));
	end Free;

    function GetossimString(
            TheList : StringList;
            Index   : Ossim_Uint32) return OssimString.Object is

    begin
        return OssimString.GetossimString(TheList, Index);
    end GetossimString;

    function Get_Filename_String(Filename : Object) return String is

    begin
        return OssimString.GetString(Filename);
    end Get_Filename_String;

    procedure ConvertBackToForwardSlashes(Filename : in out String) is

        procedure ConvertBackToForwardSlashes(Filename : System.Address);
        pragma Import(C, ConvertBackToForwardSlashes,
            "convertBackToForwardSlashesC");

    begin
        ConvertBackToForwardSlashes(Filename'Address);
    end ConvertBackToForwardSlashes;

    procedure ConvertForwardToBackSlashes(Filename : in out String) is

        procedure ConvertForwardToBackSlashes(Filename : System.Address);
        pragma Import(C, ConvertForwardToBackSlashes,
            "convertForwardToBackSlashesC");

    begin
        ConvertForwardToBackSlashes(Filename'Address);
    end ConvertForwardToBackSlashes;

    function Exists(Filename : Object) return Boolean is

        function Exists(Filename : Void_Ptr) return Boolean;
        pragma Import(C, Exists, "existsC");

    begin
        return Exists(OssimString.C_Object(Filename));
    end Exists;

    function IsFile(Filename : Object) return Boolean is

        function IsFile(Filename : Void_Ptr) return Boolean;
        pragma Import(C, IsFile, "isFileC");

    begin
        return IsFile(OssimString.C_Object(Filename));
    end IsFile;

    function IsDir(Filename : Object) return Boolean is

        function IsDir(Filename : Void_Ptr) return Boolean;
        pragma Import(C, IsDir, "isDirC");

    begin
        return IsDir(OssimString.C_Object(Filename));
    end IsDir;

    function IsReadable(Filename : Object) return Boolean is

        function IsReadable(Filename : Void_Ptr) return Boolean;
        pragma Import(C, IsReadable, "isReadableC");

    begin
        return IsReadable(OssimString.C_Object(Filename));
    end IsReadable;

    function IsWritable(Filename : Object) return Boolean is

        function IsWritable(Filename : Void_Ptr) return Boolean;
        pragma Import(C, IsWritable, "isWritableC");

    begin
        return IsWritable(OssimString.C_Object(Filename));
    end IsWritable;

    function IsExecutable(Filename : Object) return Boolean is

        function IsExecutable(Filename : Void_Ptr) return Boolean;
        pragma Import(C, IsExecutable, "isExecutableC");

    begin
        return IsExecutable(OssimString.C_Object(Filename));
    end IsExecutable;

    function FileSize(Filename : Object) return Ossim_Int64 is

        function FileSize(Filename : Void_Ptr) return Ossim_Int64;
        pragma Import(C, FileSize, "fileSizeC");

    begin
        return FileSize(OssimString.C_Object(Filename));
    end FileSize;

    function Ext(Filename : Object) return OssimString.Object is

        function Ext(Filename : Void_Ptr) return Void_Ptr;
        pragma Import(C, Ext, "ext");

    begin
        return OssimString.Create(Ext(OssimString.C_Object(Filename)));
    end Ext;

    function File(Filename : Object) return OssimString.Object is

        function File(Filename : Void_Ptr) return Void_Ptr;
        pragma Import(C, File, "file");

    begin
        return OssimString.Create(File(OssimString.C_Object(Filename)));
    end File;

    function Path(Filename : Object) return OssimString.Object is

        function Path(Filename : Void_Ptr) return Void_Ptr;
        pragma Import(C, Path, "path");

    begin
        return OssimString.Create(Path(OssimString.C_Object(Filename)));
    end Path;

    function Drive(Filename : Object) return OssimString.Object is

        function Drive(Filename : Void_Ptr) return Void_Ptr;
        pragma Import(C, Drive, "drive");

    begin
        return OssimString.Create(Drive(OssimString.C_Object(Filename)));
    end Drive;

    function FileNoExtension(Filename : Object) return OssimString.Object is

        function FileNoExtension(Filename : Void_Ptr) return Void_Ptr;
        pragma Import(C, FileNoExtension, "fileNoExtension");

    begin
        return OssimString.Create(FileNoExtension(OssimString.C_Object(Filename)));
    end FileNoExtension;

    function SetExtension(
            Filename : Object;
            Ext		 : OssimString.Object) return Object is

        function SetExtension(
            Filename : in Void_Ptr;
            Ext		 : in Void_Ptr) return Void_Ptr;
        pragma Import(C, SetExtension, "setExtension");

    begin
        return Create(SetExtension(OssimString.C_Object(Filename), 
            OssimString.C_Object(Ext)));
    end SetExtension;

    function SetPath(
            Filename : Object;
            Path     :OssimString.Object) return Object is

        function SetPath(
            Filename : in Void_Ptr;
            Ext		 : in Void_Ptr) return Void_Ptr;
        pragma Import(C, SetPath, "setPath");

    begin
        return Create(SetPath(OssimString.C_Object(Filename), 
            OssimString.C_Object(Path)));
    end SetPath;

    function SetFile(
            Filename : Object;
            File	 : OssimString.Object) return Object is

        function SetFile(
            Filename : in Void_Ptr;
            Ext		 : in Void_Ptr) return Void_Ptr;
        pragma Import(C, SetFile, "setFile");

    begin
        return Create(SetFile(OssimString.C_Object(Filename), 
            OssimString.C_Object(File)));
    end SetFile;

    procedure Split(
            Filename : Object;
            DrivePart: OssimString.Object;
            PathPart : OssimString.Object;
            FilePart : OssimString.Object;
            ExtPart  : OssimString.Object) is

        procedure Split(
            Filename : Void_Ptr;
            DrivePart: Void_Ptr;
            PathPart : Void_Ptr;
            FilePart : Void_Ptr;
            ExtPart  : Void_Ptr);
        pragma Import(C, Split, "split");

    begin
        Split(OssimString.C_Object(Filename), OssimString.C_Object(DrivePart),
            OssimString.C_Object(PathPart), OssimString.C_Object(FilePart),
            OssimString.C_Object(ExtPart));
    end Split;

    procedure Merge(
            Filename : Object;
            DrivePart: OssimString.Object;
            PathPart : OssimString.Object;
            FilePart : OssimString.Object;
            ExtPart  : OssimString.Object) is

        procedure Merge(
            Filename : Void_Ptr;
            DrivePart: Void_Ptr;
            PathPart : Void_Ptr;
            FilePart : Void_Ptr;
            ExtPart  : Void_Ptr);
        pragma Import(C, Merge, "merge");

    begin
        Merge(OssimString.C_Object(Filename), OssimString.C_Object(DrivePart),
            OssimString.C_Object(PathPart), OssimString.C_Object(FilePart),
            OssimString.C_Object(ExtPart));
    end Merge;

    function DirCat(Pathname : Object;
            File	 : Object) return Object is

        function DirCat(Pathname : Void_Ptr;
            File	 : Void_Ptr) return Void_Ptr;
        pragma Import(C, DirCat, "dirCat");

    begin
        return Create(DirCat(OssimString.C_Object(Pathname), 
            OssimString.C_Object(File)));
    end DirCat;

    function CreateDirectory(
            Filename 	: Object;
            RecurseFlag	: Boolean := True;
            Perm		: Integer := 0777) return Boolean is

        function CreateDirectory(
            Filename 	: Void_Ptr;
            RecurseFlag	: Boolean;
            Perm		: Integer) return Boolean;
        pragma Import(C, CreateDirectory, "createDirectory");

    begin
        return CreateDirectory(OssimString.C_Object(Filename), RecurseFlag, Perm);
    end CreateDirectory;

    function GetossimString(
            TheList : StringList; 
            Index   : Ossim_Uint32) return Object is
        the_Object : Object;
    begin
        return The_Object;
    end GetossimString;

    --
    -- Removes pathname from filesystem if supported by platform.
    -- Return true on success, false on error.
    -- If supported will set errno and output equivalent string if one occurs.
    --
    function Remove(Filename : Object;
            Pathname : System.Address) return Boolean is

        function Remove(Filename : Void_Ptr;
            Pathname : System.Address) return Boolean;
        pragma Import(C, Remove, "removePathnameC");

    begin
        return Remove(OssimString.C_Object(Filename), Pathname'Address);
    end Remove;

    procedure Free(Filename : Object'Class) is

    begin
        OssimString.Free(Filename);
    end Free;

    function C_Object(The_Object : Object'class) return Void_Ptr is

    begin
        return the_Object.OssimObject;
    end C_Object;

end Ossimstring.Filename;

