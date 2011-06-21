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
with ProcessInterface;
pragma Elaborate_All(ProcessInterface);
package body Ossim.Connectable.Source.MetaData.Writer.File.Geom is

    function Create(C_Object : Void_Ptr) return Object is
       the_Object : Object;
    begin
        the_Object.OssimObject:= C_Object;
        return the_Object; 
    end Create;

    function Create return Object  is
    
        function CreateGeom return Void_Ptr;
        pragma import(C, CreateGeom, "createOssimGeomFileWriter");

    begin
        return Create(CreateGeom);
    end Create;

    function Create(
            InputSource	: Ossim.Connectable.Object'class;
            Filename	: OssimString.Filename.Object) return Object is

        function CreateGeom(
                Source	: Void_Ptr;
                Filename	: Void_Ptr) return Void_Ptr;
        pragma import(C, CreateGeom, "createConnectedOssimGeomFileWriter");

    begin
        return Create(CreateGeom(ossim.C_Object(InputSource),
                OssimString.C_Object(Filename)));
    end Create;
            
    function Create(
            InputSource	: Ossim.Connectable.Object'class;
            Filename	: String) return Object is

        function CreateGeom(
                Source	: Void_Ptr;
                Filename	: Void_Ptr) return Void_Ptr;
        pragma import(C, CreateGeom, "createConnectedOssimGeomFileWriterS");
        
        File_Null : String(Filename'First..Filename'last + 1) :=
                Filename & Ascii.Nul;

    begin
        return Create(CreateGeom(Ossim.C_Object(InputSource), File_Null'address));
    end Create;

    procedure Execute(Geom : Object) is

		procedure Execute(Writer : Void_Ptr);
		pragma import(C, Execute, "ossimExecuteGeomFileWriter");
		
    begin
        Execute(Ossim.C_Object(Geom));
    end Execute;


    procedure Delete(Geom : Object) is

        procedure Delete(Readme : Void_Ptr);
        pragma Import(C, Delete, "deleteOssimGeomFileWriter");

    begin
        Delete(Ossim.C_Object(Geom));
    end Delete;
            
end Ossim.Connectable.Source.MetaData.Writer.File.Geom;
