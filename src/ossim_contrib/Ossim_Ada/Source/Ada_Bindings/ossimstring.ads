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
with Interfaces.C.Extensions; use Interfaces.C.Extensions;
with Interfaces; use Interfaces;
with Ossim_Constants; use Ossim_Constants;
package OssimString is

    type Object is tagged private;
    subtype StringList is Void_Ptr;

    function Create(C_Object : Void_Ptr) return Object;

    function Create(AdaString : String) return Object'class;

    function Create(AdaString : Object'class) return Object'class;

    procedure Create(theObject : in out Object'class);

    function CreateStringList return StringList;
    pragma Import(C, CreateStringList, "ossimCreateStringVector");

    function GetNumberItems(TheList : StringList) return ossim_uint32;
    pragma Import(C, GetNumberItems, "ossimGetNumberOfStrings");

    procedure StringList_Free(List : StringList);
    pragma Import(C, StringList_Free, "ossimFreeStringVector");
 
    function GetossimString(
            TheList : StringList; 
            Index   : Ossim_Uint32) return Object;

    function GetossimString(
            TheList : StringList; 
            Index   : Ossim_Uint32) return String;
 
    function GetString(TheString : Object'class) return String;

    procedure Free(theObject : Object'class);
    
    function C_Object(The_Object : Object'class) return Void_Ptr;

private


    type Object is tagged
    record
        OssimObject	: Void_Ptr;
    end record;

end OssimString;

