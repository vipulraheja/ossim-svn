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
with Ossim_Constants;
 use Ossim_Constants;
package Ossim.Connectable is

    type Object is new Ossim.Object with private;

    type OssimConnectableObjectDirectionType is (
        CONNECTABLE_DIRECTION_NONE,
        CONNECTABLE_DIRECTION_INPUT,
        CONNECTABLE_DIRECTION_OUTPUT);
    for OssimConnectableObjectDirectionType'Size use 32;

    function Create(C_Object : Void_Ptr) return Object;
	
	function CastToConnectableObject(theObject  : Object'class) return Object'class;

    procedure OssimConnectObjects(
        LeftObject	: Object;
        RightObject	:Object);

    procedure OssimConnectObject(
        LeftObject		: Object'class;
        RightObject		: Object'class;
        IdxRightObjectSlot	: Integer);

    --
    -- Will try to connect this objects input to the passed in object.
    -- It will return a valid index >= 0 if successful.  Will use the
    -- getMyInputIndexToConnectTo method to implement the connection
    --
    function ConnectMyInputTo(
        LeftObject				: Object'class;
        RightObject				: Object'class;
        MakeOutputConnection	: Boolean := True;
        CreateEventFlag			: Boolean := True) return ossim_int32;

private

    type Object is new Ossim.Object with
    record
        null;
    end record;

end Ossim.Connectable;

