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
package body ossimRtti is

    function Create(C_Object : Void_Ptr) return Object is
        TheObject : Object;
    begin
        TheObject.OssimObject:= C_Object;
        return TheObject;
    end Create;

    function Create return Object is
    
        function Create return Void_Ptr;
        pragma Import(C, Create, "ossimCreateObject");
        
    begin
        return Create(Create);
    end Create;

    procedure OssimFreeObject(Obj	: Object) is
        procedure OssimFreeObject(Obj : Void_Ptr);
        pragma Import(C, OssimFreeObject, "ossimFreeObject");
    begin
        OssimFreeObject(C_Object(Obj));
    end OssimFreeObject;

    function C_Object(theObject : Object) return Void_Ptr is
    begin
        return theObject.OssimObject;
    end C_Object;

end ossimRtti;
