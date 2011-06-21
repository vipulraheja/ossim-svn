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
with Interfaces.C.Extensions;
use Interfaces.C.Extensions;
with Interfaces; use Interfaces;
with Ossim_Common; use Ossim_Common;
with Ossim_Constants; 
 use Ossim_Constants;
with DPt;
with IRect;
package DRect is

    UPPER_LEFT  : constant Integer := 1;
    LOWER_LEFT 	: constant Integer := 2;
    LOWER_RIGHT	: constant Integer := 4;
    UPPER_RIGHT	: constant Integer := 8;

    type Object is tagged private;

    function Create(C_Object : Void_Ptr) return Object;

    function Create return Object;
    
    function Create(
        Ul_Corner 	: DPt.Object;
        Lr_Corner	: DPt.Object;
        Mode		: ossimCoordSysOrientMode := OSSIM_LEFT_HANDED) return Object;
        
    function Create(
        Ul_Corner_X 	: Long_Float;
        Ul_Corner_Y 	: Long_Float;
        Lr_Corner_X 	: Long_Float;
        Lr_Corner_Y 	: Long_Float;
        Mode			: ossimCoordSysOrientMode := OSSIM_LEFT_HANDED) return Object;
        
    function CreateDRect(Rect : Object) return Object;
    
    function Create(Rect : IRect.Object) return Object;

    procedure Free(Rect : Object);

    function C_Object(Rect : Object) return Void_Ptr;

private

    type Object is tagged
    record
        OssimObject	: Void_Ptr;
    end record;

end DRect;

