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
package body Ossim.Connectable is

    function Create(C_Object : Void_Ptr) return Object is
        the_Object : Object;
    begin
        the_Object.OssimObject:= C_Object;
        return the_Object; 
    end Create;

	function CastToConnectableObject(theObject  : Object'class) return Object'class is

		function CastToConnectableObject(theObject  : Void_Ptr) return Void_Ptr;
        pragma Import(C, CastToConnectableObject, "castObjectToConnectableObject");

	begin
		return Create(CastToConnectableObject(Ossim.C_Object(theObject)));
	end CastToConnectableObject;

    procedure OssimConnectObjects(
            LeftObject	: Object;
            RightObject	: Object) is

        procedure ConnectObjects(
            LeftObject	: Void_Ptr;
            RightObject	: Void_Ptr);
        pragma Import(C, ConnectObjects, "ossimConnectObjects");

    begin
        ConnectObjects(Ossim.C_Object(LeftObject), Ossim.C_Object(RightObject));
    end OssimConnectObjects;

    procedure OssimConnectObject(
            LeftObject			: Object'class;
            RightObject			: Object'class;
            IdxRightObjectSlot	: Integer) is

        procedure OssimConnectObject(
            LeftObject			: Void_Ptr;
            RightObject			: Void_Ptr;
            IdxRightObjectSlot	: Integer);
        pragma Import(C, OssimConnectObject, "ossimConnectObject");

    begin
        OssimConnectObject(Ossim.C_Object(LeftObject), Ossim.C_Object(
                RightObject), IdxRightObjectSlot);
    end OssimConnectObject;

    function ConnectMyInputTo(
        LeftObject		: Object'class;
        RightObject		: Object'class;
        MakeOutputConnection	: Boolean := True;
        CreateEventFlag		: Boolean := True) return ossim_int32 is
        
        function ConnectMyInputTo(
            LeftObject		: void_Ptr;
            RightObject		: void_Ptr;
            MakeOutputConnection	: Boolean;
            CreateEventFlag		: Boolean) return ossim_int32;
        pragma import(c, ConnectMyInputTo,"connectMyInputTo");
    begin
        return ConnectMyInputTo(Ossim.C_Object(LeftObject), Ossim.C_Object(RightObject),
           MakeOutputConnection, CreateEventFlag);
    end ConnectMyInputTo;

end Ossim.Connectable;

