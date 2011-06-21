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
with Ossim_Constants; use Ossim_Constants;
package Ipt is

    type Object is tagged private;

    function Create(C_Object : Void_Ptr) return Object;

    function CreateIpt(
        X	: ossim_int32;
        Y	: ossim_int32) return Object;

    procedure SetX(Point : Object; X : ossim_int32);

    function GetX(Point : Object) return ossim_int32;

    procedure SetY(Point : Object; Y : ossim_int32);

    function GetY(Point : Object) return ossim_int32;

    function C_Object(Point : Object) return Void_Ptr;

    function "+"(Point : Object; offset : Object) return Object;
    function "-"(Point : Object; offset : Object) return Object;
	
	procedure Free(Point : Object);

private

    type Object is tagged
    record
        OssimObject	: Void_Ptr;
    end record;

end Ipt;

