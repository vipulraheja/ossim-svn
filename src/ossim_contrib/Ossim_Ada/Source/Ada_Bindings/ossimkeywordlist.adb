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
with Unchecked_Deallocation;
package body OssimKeywordlist is

    function Create(C_Object : Void_Ptr) return Object is
        TheObject : Object;
    begin
        TheObject.OssimObject:= C_Object;
        return TheObject;
    end Create;

    function CreateKeywordlist return Object is

        function CreateKeywordlist return Void_Ptr;
        pragma Import(C, CreateKeywordlist, "ossimCreateKeywordlist");
    begin
        return Create(CreateKeywordlist);
    end CreateKeywordlist;

    function CreateKeywordlistNewDelimeter(Delimiter : Character) return
            Object is

        function CreateKeywordlistNewDelimeter(Delimiter : Character) return
            Void_Ptr;
        pragma Import(C, CreateKeywordlistNewDelimeter,
            "ossimCreateKeywordlistNewDelimeter");

    begin
        return Create(CreateKeywordlistNewDelimeter(Delimiter));
    end CreateKeywordlistNewDelimeter;

    procedure FreeKeywordlist(KeyList : Object) is

        procedure FreeKeywordlist(KeyList :    Void_Ptr);
        pragma Import(C, FreeKeywordlist, "ossimFreeKeywordlist");

    begin
        FreeKeywordlist(C_Object(KeyList));
    end FreeKeywordlist;

    procedure AddKeywordAndPrefixString(
            Kwl		: Object;
            Prefix	: String;
            Key		: String;
            Value	: String;
            Replace : Boolean) is

        procedure AddKeywordAndPrefixString(
            Kwl		: Void_Ptr;
            Prefix	: System.Address;
            Key		: System.Address;
            Value	: System.Address;
            Replace : Boolean);
        pragma Import(C, AddKeywordAndPrefixString,
            "ossimAddKeywordAndPrefixString");

        Prefix_Null : String(Prefix'First..Prefix'Last + 1) := Prefix &
            ASCII.Nul;
        Key_Null : String(Key'First..Key'Last + 1) := Key & ASCII.Nul;
        Value_Null : String(Value'First..Value'Last + 1) := Value & ASCII.
            Nul;

    begin
        AddKeywordAndPrefixString(C_Object(Kwl),Prefix_Null'Address,
            Key_Null'Address, Value_Null'Address, Replace);
    end AddKeywordAndPrefixString;

    procedure AddKeywordString(
            Kwl		: Object;
            Key		: String;
            Value	: String;
            Replace	: Boolean) is

        procedure AddKeywordString(
            Kwl		: Void_Ptr;
            Key		: System.Address;
            Value	: System.Address;
            Replace	: Boolean);
        pragma Import(C, AddKeywordString, "ossimAddKeywordString");

        Key_Null : String(Key'First..Key'Last + 1) := Key & ASCII.Nul;
        Value_Null : String(Value'First..Value'Last + 1) := Value & ASCII.
            Nul;

    begin
        AddKeywordString(C_Object(Kwl), Key_Null'Address,
            Value_Null'Address, Replace);
    end AddKeywordString;

    function LoadKeywordlistFromFile(
            Kwl		: Object;
            Filename: String) return Boolean is

        function LoadKeywordlistFromFile(
            Kwl		: Void_Ptr;
            Filename: System.Address) return Boolean;
        pragma Import(C, LoadKeywordlistFromFile,
            "loadKeywordlistFromFile");

        Filename_Null : String(Filename'First..Filename'Last + 1) :=
            Filename & ASCII.Nul;

    begin
        return LoadKeywordlistFromFile(C_Object(Kwl), Filename_Null'
            Address);
    end LoadKeywordlistFromFile;

    function C_Object(Filename : Object) return Void_Ptr is
    begin
        return Filename.OssimObject;
    end C_Object;

end OssimKeywordlist;

