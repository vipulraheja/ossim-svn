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
with Ada.Text_IO;
with OssimString;
with OssimKeywordlist;
package body Ossim.Factory.Imagewriter is

    function Create(C_Object : Void_Ptr) return Object is
       the_Object : Object;
    begin
        the_Object.OssimObject:= C_Object;
        return the_Object; 
    end Create;

    function CreateWriter(
            Kwl 	: OssimKeywordlist.Object'class;
            Prefix	: String := "") 
            return Ossim.Connectable.Source.Output.Imagewriter.File.Object is

        function CreateImageFileWriterFromKwl(
            Kwl 	: Void_Ptr;
            Prefix	: System.Address := System.Null_Address) return Void_Ptr;
        pragma Import(C, CreateImageFileWriterFromKwl, "createWriterKeyword");

        Prefix_Null : String(Prefix'First..Prefix'Last + 1) :=
            Prefix & ASCII.Nul;

    begin
        if Prefix /= "" then
            return Ossim.Connectable.Source.Output.Imagewriter.File.Create(
                CreateImageFileWriterFromKwl(
                OssimKeywordlist.C_Object(Kwl), Prefix_Null'address));
        else
            return Ossim.Connectable.Source.Output.Imagewriter.File.Create(
                CreateImageFileWriterFromKwl(
                OssimKeywordlist.C_Object(Kwl), System.Null_Address));
        end if;
    end CreateWriter;

    function CreateWriter(TypeName : OssimString.Object'class) 
            return Ossim.Connectable.Source.Output.Imagewriter.File.Object is
    
        function CreateWriter(Filetype : System.Address) return Void_Ptr;
        pragma Import(C, CreateWriter, "createWriter");
        
    begin
        return Ossim.Connectable.Source.Output.Imagewriter.File.Create(
            CreateWriter(OssimString.C_Object(TypeName)'Address));
    end CreateWriter;

    function GetImageTypeList return OssimString.StringList is

		procedure GetImageTypeList(List : OssimString.StringList);
        pragma Import(C, GetImageTypeList, "getImageTypeList");

        OutputType : OssimString.StringList:= OssimString.CreateStringList;

    begin
        GetImageTypeList(OutputType);
        return OutputType;
    end GetImageTypeList;

    function CreateWriter(Filetype : String) 
        return Ossim.Connectable.Source.Output.Imagewriter.File.Object is
	
        function CreateWriter(Filetype : System.Address) return Void_Ptr;
        pragma Import(C, CreateWriter, "createWriter");
		
        File 	  : String(Filetype'first..Filetype'last + 1) := Filetype & ASCII.Nul;
        File_Type : OssimString.Object'class := OssimString.Create(File);
        
        temp : Void_Ptr;
        
    begin
        temp:= CreateWriter(OssimString.C_Object(File_Type)'address);
        return Ossim.Connectable.Source.Output.Imagewriter.File.Create(temp);
    end CreateWriter;

end Ossim.Factory.Imagewriter;
