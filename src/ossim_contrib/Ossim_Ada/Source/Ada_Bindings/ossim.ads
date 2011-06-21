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
with Interfaces.C.Extensions;
use Interfaces.C.Extensions;
with ossimRtti;
with ossimString;
with OssimKeywordlist;
package Ossim is

    type Object is tagged private;

    function Create(C_Object : Void_Ptr) return Object;

    function Create return Object'class;

    function Dup(TheObject : Object'class) return Object'class;
    function GetShortName(TheObject : Object'class) return String;
    function GetLongName(TheObject : Object'class) return String;
    function GetDescription(TheObject : Object'class) return String;
    function GetClassName(TheObject : Object'class) return String;
--    function GetClassName(TheObject : Object'class) return OssimString.Object;
	
    --
    -- Will return the type of this class in an RTTI format.
    --
    function GetType(theObject : Object'class) return ossimRtti.Object;
    function canCastTo(FromObject 	: Object'class;
                       ToObject		: Object'class) return Boolean;
    function canCastTo(FromObject 	: Object'class;
                       ToObject		: ossimRtti.Object'class) return Boolean;

    --
    -- Will use RTTI to search the derived classes to see if it derives from
    -- the passed in type.  If so then this object can be casted to the
    -- passed in class name.
    --
    function canCastTo(FromObject 	: Object'class;
                       parentClassName	: ossimString.Object'class) return Boolean;

    --
    -- Method to save the state of the object to a keyword list.
    -- Return true if ok or false on error.
    --
    function SaveState(theObject	: Object'class;
                       KeyWordList	: OssimKeywordlist.Object'class;
                       Prefix		: String := "") return Boolean;

    --
    -- Method to the load (recreate) the state of the object from a keyword
    -- list.  Return true if ok or false on error.
    --
    function loadState(theObject	: Object'class;
                       KeyWordList	: OssimKeywordlist.Object'class;
                       Prefix		: String := "") return Boolean;

    procedure Free(Obj	: Object'class);

    function C_Object(TheObject : Object'class) return Void_Ptr;

private

    type Object is tagged 
    record
        OssimObject	: Void_Ptr;
    end record;

end Ossim;

