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
with Interfaces.C.Extensions; use Interfaces.C.Extensions;
with OssimString.Filename;
package Ossim.Connectable.Source.MetaData.Writer.File.Geom is

    type Object is new Ossim.Connectable.Source.MetaData.Writer.File.Object with private;

    function Create(C_Object : Void_Ptr) return Object;

    function Create return Object;

    function Create(
            InputSource	: Ossim.Connectable.Object'class;
            Filename	: OssimString.Filename.Object) return Object;
            
    function Create(
            InputSource	: Ossim.Connectable.Object'class;
            Filename	: String) return Object;

    procedure Execute(Geom : Object);

    procedure Delete(geom : Object);

private

    type Object is new Ossim.Connectable.Source.MetaData.Writer.File.Object with
    record
        null;
    end record;
    
end Ossim.Connectable.Source.MetaData.Writer.File.Geom;
