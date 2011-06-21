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
package body Ossim.Connectable.Source.Image.Filter.CacheTileSource is

    function Create(C_Object : Void_Ptr) return Object is
        the_Object : Object;
    begin
        the_Object.OssimObject:= C_Object;
        return the_Object;
    end Create;

    function Create return Object is

        function CreateCache return Void_Ptr;
        pragma import(C, CreateCache, "ossimCreateCacheTileSource");

    begin
        return Create(CreateCache);
    end Create;

    function Create(inputObject : Ossim.Connectable.Object'class) return Object is

		function CreateCache(Source : Void_Ptr) return Void_Ptr;
		pragma import(C, CreateCache, "ossimCreateCacheTileSourceConnect");

	begin
		return Create(CreateCache(Ossim.C_Object(inputObject)));
    end Create;

    procedure SetCachingEnabledFlag(Cache 	: Object;
                                    Flag 	: Boolean) is

        procedure SetCachingEnabledFlag(Cache 	: void_ptr;
                                        Flag 	: Boolean);
        pragma import(C, SetCachingEnabledFlag, "setCachingEnabledFlag");

    begin
        SetCachingEnabledFlag(Ossim.C_Object(Cache), Flag);
    end SetCachingEnabledFlag;

    procedure Delete(Cache : Object) is

        procedure Delete(Cache : void_ptr);
        pragma import(C, Delete, "ossimDeleteCacheTileSource");

    begin
        Delete(Ossim.C_Object(Cache));
    end Delete;

end Ossim.Connectable.Source.Image.Filter.CacheTileSource;
