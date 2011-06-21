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
package body Init is

    function Create(C_Object : Void_Ptr) return Object is
        TheObject : Object;
    begin
        TheObject.OssimObject:= C_Object;
        return TheObject;
    end Create;

    procedure Initialize is

        Gnat_Argc : aliased Integer;
        Gnat_Argv : System.Address;
        pragma Import (C, Gnat_Argc);
        pragma Import (C, Gnat_Argv);

        procedure Initialize(
            Gnat_Argc : Integer;
            Gnat_Argv : System.Address);
        pragma Import(C, Initialize, "ossimInitialize");

    begin

        Initialize(Gnat_Argc, Gnat_Argv);

    end Initialize;

end Init;

