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
with Ossim.Connectable.Source;
with Ossim.Connectable.Source.Image;
with Ossim.Data.Rectilinear.Image;
package OssimImageDataFactory is

    type Object is tagged private;

    function Create(C_Object : Void_Ptr) return Object;

-- future      
--	function Create(Owner : Ossim.Connectable.Source;
--					Input_Source : ossimImageSourceInterface) return Ossim.Data.Rectilinear.Image.Object;

	function Create(
		Owner			: Ossim.Connectable.Source.Object'class;
		Input_Source	: Ossim.Connectable.Source.Image.Object'class) return 
											Ossim.Data.Rectilinear.Image.Object;

    function C_Object(theObject : Object'class) return Void_Ptr;

private

    type Object is tagged
    record
        OssimObject	: Void_Ptr;
    end record;

end OssimImageDataFactory;
