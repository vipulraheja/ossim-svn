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
with Interfaces.C.Strings; use Interfaces.C.Strings;
package body OssimString is

    function Create(C_Object : Void_Ptr) return Object is
        TheObject : Object;
    begin
        TheObject.OssimObject:= C_Object;
        return TheObject;
    end Create;

    function Create(AdaString : String) return Object'class is

        function OssimString(AString : System.Address) return Void_Ptr;
        pragma Import(C, OssimString, "ossimCreateString");

        TheObject : Object;
        AdaString_Null : String(AdaString'First..AdaString'Last + 1) :=
            AdaString & ASCII.Nul;

    begin
        TheObject.OssimObject:= OssimString(AdaString_Null'Address);
        return TheObject;
    end Create;

    function Create(AdaString : Object'class) return Object'class is
    begin
        return Create(GetString(AdaString));
    end Create;

    procedure Create(theObject : in out Object'class) is
    begin
        theObject:= Create(GetString(theObject));
    end Create;

    function GetossimString(
        TheList 	: StringList; 
        Index 	: Ossim_Uint32) return Object is

        function GetString(Index : Ossim_Uint32; TheList : StringList) return
            Void_Ptr;
        pragma Import(C, GetString, "ossimGetString");

    begin
        return Create(GetString(Index, TheList));
    end GetossimString;

    function GetString(TheString : Object'class) return String is

        function GetString(TheString : Void_Ptr) return Chars_Ptr;
        pragma Import(C, GetString, "ossimGetChars");

        C_String	: Chars_Ptr:= GetString(TheString.OssimObject);

    begin
        return Value(C_String, (Strlen(C_String)));
    end GetString;

    function GetossimString(TheList : StringList; Index : Ossim_Uint32) return
            String is

        function GetString(Index : Ossim_Uint32; TheList : StringList) return
            Void_Ptr;
        pragma Import(C, GetString, "ossimGetString");

        function GetChars(TheString : Void_Ptr) return Chars_Ptr;
        pragma Import(C, GetChars, "ossimGetChars");

        C_String	: Chars_Ptr:= GetChars(GetString(Index, TheList));

    begin
        return Value(C_String, (Strlen(C_String)));
    end GetossimString;

    procedure Free(theObject : Object'class) is

        procedure Free(theObject : Void_Ptr);
        pragma Import(C, Free, "ossimFreeObject");

    begin
        Free(theObject.OssimObject);
    end Free;

    function C_Object(The_Object : Object'class) return Void_Ptr is
    begin
        return The_Object.OssimObject;
    end C_Object;

end OssimString;

