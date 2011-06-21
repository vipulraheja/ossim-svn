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
generic

    type Object is tagged private;
    with function Create(C_Object : Void_Ptr) return Object; 
    with function C_Object(theObject : Object'class) return void_Ptr; 
    
package ProcessInterface is

   type ossimProcessStatus is (
        PROCESS_STATUS_UNKNOWN,
        PROCESS_STATUS_EXECUTING,
        PROCESS_STATUS_ABORTED,
        PROCESS_STATUS_ABORT_REQUEST,
        PROCESS_STATUS_NOT_EXECUTING);
    for ossimProcessStatus'size use 32;

    function Execute(theObject : Object) return Boolean;

end ProcessInterface;
