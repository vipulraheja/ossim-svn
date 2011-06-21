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
with Ossim.Projection;
with DRect;
with Ossim_Constants;
 use Ossim_Constants;
package Ossim.MapProjectionInfo is

    type Object is new Ossim.Object with private;
	
    function Create(C_Object : Void_Ptr) return Object;

    function Create(Projection  : Ossim.Projection.Object'class;
                    Output_Rect	: DRect.Object) return Object;
                                    
    procedure Delete(Project_Info : Object);

    function Lines_Per_Image(Projection : Object'class) return ossim_int32;
    
    function Pixels_Per_Line(Projection : Object'class) return ossim_int32;

private
	
    type Object is new Ossim.Object with 
    record
        null;
    end record;
end Ossim.MapProjectionInfo;
