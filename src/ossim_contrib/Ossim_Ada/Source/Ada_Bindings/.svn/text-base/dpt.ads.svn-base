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
with Interfaces;
use Interfaces;

package Dpt is

    type Object is tagged private;

    function Create(C_Object : Void_Ptr) return Object;

    function Create(X, Y : IEEE_Float_64) return Object;
	
	procedure Free(Point : Object);

    function C_Object(Point : Object) return Void_Ptr;

private

    type Object is tagged
    record
        OssimObject	: Void_Ptr;
    end record;

end Dpt;

