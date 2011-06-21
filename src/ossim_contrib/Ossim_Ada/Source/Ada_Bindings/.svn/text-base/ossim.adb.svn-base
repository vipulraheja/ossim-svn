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
package body Ossim is

    function Create(C_Object : Void_Ptr) return Object is
        TheObject : Object;
    begin
        TheObject.OssimObject:= C_Object;
        return TheObject;
    end Create;

    function Create return Object'class is
    
        function Create return Void_Ptr;
        pragma Import(C, Create, "ossimCreateObject");
        
    begin
        return Create(Create);
    end Create;

    function Dup(TheObject : Object'class) return Object'class is
        function Dup(
            TheObject : Void_Ptr) return Void_Ptr;
        pragma Import(C, Dup, "dupC");
    begin
        return Create(Dup(C_Object(TheObject)));
    end Dup;
    
    function GetShortName(TheObject : Object'class) return String is
	
        function GetShortName(
            Handler : Void_Ptr) return Chars_Ptr;
        pragma Import(C, GetShortName, "getShortNameC");

        Name : Chars_Ptr;

    begin
        Name:= GetShortName(TheObject.OssimObject);
        return Value(Name, (Strlen(Name)));
    end GetShortName;

    function GetLongName(TheObject : Object'class) return String is
        function GetLongName(
            Handler : Void_Ptr) return Chars_Ptr;
        pragma Import(C, GetLongName, "getLongNameC");

        Name : Chars_Ptr;

    begin
        Name:= GetLongName(TheObject.OssimObject);
        return Value(Name, (Strlen(Name)));
    end GetLongName;

    function GetDescription(TheObject : Object'class) return String is

        function GetDescription(
            Handler : Void_Ptr) return Chars_Ptr;
        pragma Import(C, GetDescription, "getDescriptionC");

        Description : Chars_Ptr;

    begin
        Description:= GetDescription(TheObject.OssimObject);
        return Value(Description, (Strlen(Description)));
    end GetDescription;

    function GetClassName(TheObject : Object'class) return OssimString.Object is

        function GetClassName(Handler : Void_Ptr) return Void_Ptr;
        pragma Import(C, GetClassName, "getClassNameC");

    begin
        return OssimString.Create(GetClassName(TheObject.OssimObject));
	end GetClassName;

    function GetClassName(TheObject : Object'class) return String is

        function GetClassName(Handler : Void_Ptr) return Void_Ptr;
        pragma Import(C, GetClassName, "getClassNameC");

        Classname : OssimString.Object;

    begin
        Classname:= OssimString.Create(GetClassName(TheObject.OssimObject));
        return OssimString.GetString(Classname);
	end GetClassName;
    
    function GetType(theObject : Object'class) return ossimRtti.Object is
        function GetType(
            theObject : Void_Ptr) return void_Ptr;
        pragma Import(C, GetType, "getType");
    begin
        return ossimRtti.Create(GetType(C_Object(theObject)));
    end GetType;
    
    function canCastTo(FromObject 	: Object'class;
                       ToObject		: Object'class) return Boolean is
					   
        function canCastTo(FromObject 	: Void_Ptr;
                       ToObject			: Void_Ptr) return Boolean;
        pragma Import(C, canCastTo, "canCastTo");
		
    begin
        return canCastTo(C_Object(FromObject), C_Object(ToObject));
    end canCastTo;

    function canCastTo(FromObject 	: Object'class;
                       ToObject		: ossimRtti.Object'class) return Boolean is
					   
        function canCastTo(FromObject 	: Void_Ptr;
                       ToObject			: Void_Ptr) return Boolean;
        pragma Import(C, canCastTo, "canCastToRtti");
		
    begin
        return canCastTo(C_Object(FromObject), ossimRtti.C_Object(ToObject));
    end canCastTo;

    function canCastTo(FromObject		: Object'class;
                       parentClassName	: ossimString.Object'class) return Boolean is
					   
        function canCastTo(FromObject 		: Void_Ptr;
                           parentClassName	: Void_Ptr) return Boolean;
        pragma Import(C, canCastTo, "canCastToClassName");
		
    begin
        return canCastTo(C_Object(FromObject), ossimString.C_Object(parentClassName));
    end canCastTo;

    function SaveState(theObject	: Object'class;
                       KeyWordList	: OssimKeywordlist.Object'class;
                       Prefix		: String := "") return Boolean is
					   
        function SaveState(FromObject 	: Void_Ptr;
                           KeyWordList	: Void_Ptr;
                           Prefix	: System.Address) return Boolean;
        pragma Import(C, SaveState, "saveState");
		

    begin
        return SaveState(C_Object(theObject), OssimKeywordlist.C_Object(KeyWordList),
            Prefix'address);
    end SaveState;

    function loadState(theObject	: Object'class;
                       KeyWordList	: OssimKeywordlist.Object'class;
                       Prefix		: String := "") return Boolean is
        function loadState(FromObject 	: Void_Ptr;
                           KeyWordList	: Void_Ptr;
                           Prefix	: System.Address) return Boolean;
        pragma Import(C, loadState, "loadState");

    begin
        return loadState(C_Object(theObject), OssimKeywordlist.C_Object(KeyWordList),
            Prefix'address);
    end LoadState;

    procedure Free(Obj	: Object'class) is
        procedure Free(Obj : Void_Ptr);
        pragma Import(C, Free, "ossimFreeObject");
    begin
        Free(C_Object(Obj));
    end Free;

    function C_Object(theObject : Object'class) return Void_Ptr is
    begin
        return theObject.OssimObject;
    end C_Object;

end Ossim;

