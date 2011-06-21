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
with System; use type System.Address;
with Interfaces.C; use Interfaces.C;
with Interfaces.C.Strings; use Interfaces.C.Strings;
with Ossim_Constants; use Ossim_Constants;
with ProcessInterface;

package body Ossim.Connectable.Source.Image.Handler is

    function Create(C_Object : Void_Ptr) return Object is
        the_Object : Object;
    begin
        the_Object.OssimObject := C_Object;
        return the_Object;
    end Create;

    function Is_Null(Handler : Object) return Boolean is
    begin
        return Handler.OssimObject = System.Null_Address;
    end Is_Null;

    function GetNumberOfDecimationLevels(Handler : Object) return
            Integer_32 is

        function GetNumberOfDecimationLevels(Handler : Void_Ptr) return Integer_32;
        pragma Import(C, GetNumberOfDecimationLevels, "getNumberOfDecimationLevels");

    begin
        return GetNumberOfDecimationLevels(C_Object(Handler));
    end GetNumberOfDecimationLevels;

    function GetOutputScalarType(Handler : Object'class) return OssimScalarType is

    begin
        return Ossim.Connectable.Source.Image.GetOutputScalarType(Handler);
    end GetOutputScalarType;

    function GetFilename(Handler : Object) return OssimString.Object is

        function GetFilename(Handler : Void_Ptr) return Void_ptr;
        pragma Import(C, GetFilename, "ossimGetNewImageFilename");

    begin
        return OssimString.Create(GetFilename(C_Object(Handler)));
    end GetFilename;

    function GetFilename(Handler : Object) return String is

        function GetFilename(Handler : Void_Ptr) return Void_ptr;
        pragma Import(C, GetFilename, "ossimGetNewImageFilename");

        Filename : OssimString.Object;

    begin
        Filename:= OssimString.Create(GetFilename(C_Object(Handler)));
        return OssimString.GetString(Filename);
    end GetFilename;

    function Open(Filename : OssimString.Filename.Object) return Object is

        function Open_File(Filename : System.Address) return Void_Ptr;
        pragma Import(C, Open_File, "ossimOpenHandler");

    begin
        return Create(Open_File(OssimString.C_Object(Filename)'Address));
    end Open;
    
    function Open(Filename : String) return Object is

        function Open(Filename : System.Address) return Void_Ptr;
        pragma Import(C, Open, "ossimOpenImage");

        Filename_Null : String(Filename'First..Filename'Last + 1) :=
                    Filename & ASCII.Nul;

    begin
        return Create(Open(Filename_Null'Address));
    end Open;

    function Open(Keywords : OssimKeywordlist.Object) return Object is

        function Open(Keywords : Void_Ptr) return Void_Ptr;
        pragma Import(C, Open, "ossimOpenImageKey");

     begin
        return Create(Open(OssimKeywordlist.C_Object(Keywords)));
    end Open;

    function GetNumberOfLines(
            Handler				: Object;
            Reduced_Res_Level 	: ossim_int32:= 0) return ossim_int32 is

        function GetNumberOfLines(
            Handler				: Void_Ptr;
            Reduced_Res_Level 	: ossim_int32) return ossim_int32;
        pragma Import(C, GetNumberOfLines, "getNumberOfLines");
        
    begin
        return GetNumberOfLines(Ossim.C_Object(Handler),Reduced_Res_Level);
    end GetNumberOfLines;

    function GetNumberOfSamples(
            Handler 			: Object;
            Reduced_Res_Level 	: ossim_int32:= 0) return ossim_int32 is
        function GetNumberOfSamples(
            Handler 			: Void_Ptr;
            Reduced_Res_Level 	: ossim_int32) return ossim_int32;
        pragma Import(C, GetNumberOfSamples, "getNumberOfSamples");
    begin
        return GetNumberOfSamples(Ossim.C_Object(Handler),Reduced_Res_Level);
    end GetNumberOfSamples;

    function GetBoundingRect(
            Handler 			: Object;
            Reduced_Res_Level 	: ossim_int32:= 0) return IRect.Object is

        function GetBoundingRect(
            Handler 			: Void_Ptr;
            Reduced_Res_Level 	: ossim_int32:= 0) return Void_Ptr;
        pragma Import(C, GetBoundingRect, "getBoundingRect");

    begin
        return IRect.Create(GetBoundingRect(Ossim.C_Object(Handler),
                Reduced_Res_Level));
    end GetBoundingRect;

    procedure Free(Handler : Object) is

        procedure Free(Handler : Void_Ptr);
        pragma Import(C, Free, "ossimFreeObject");

    begin
        Free(Handler.OssimObject);
    end Free;

end Ossim.Connectable.Source.Image.Handler;

