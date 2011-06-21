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
package body Ossim.Connectable.Source.MetaData.Writer.File.Readme is

    function Create(C_Object : Void_Ptr) return Object is
       the_Object : Object;
    begin
        the_Object.OssimObject:= C_Object;
        return the_Object; 
    end Create;
    
    function Create return Object is
    
        function CreateReadme return Void_Ptr;
        pragma import(C, CreateReadme, "createOssimReadmeFileWriter");

    begin
        return Create(CreateReadme);
    end Create;

    function Create(
            InputObject : Ossim.Connectable.Object'class;
            Filename	: OssimString.Filename.Object) return Object is

        function CreateReadme(
                Source		: Void_Ptr;
                Filename	: Void_Ptr) return Void_Ptr;
        pragma import(C, CreateReadme, "createConnectedOssimReadmeFileWriter");

    begin
        return Create(CreateReadme(Ossim.C_Object(InputObject), 
                    OssimString.C_Object(Filename)));
    end Create;
            
    function Create(
            InputObject : Ossim.Connectable.Object'class;
            Filename	: String) return Object is

        function CreateReadme(
                Source		: Void_Ptr;
                Filename	: Void_Ptr) return Void_Ptr;
        pragma import(C, CreateReadme, "createConnectedOssimReadmeFileWriterS");
        
        File_Null : String(Filename'First..Filename'last + 1) :=
                Filename & Ascii.Nul;

    begin
        return Create(CreateReadme(Ossim.C_Object(InputObject), File_Null'address));
    end Create;

    procedure Execute(Writer : Object) is

		procedure Execute(Writer : Void_Ptr);
		pragma import(C, Execute, "ossimExecuteReadmeFileWriter");
		
    begin
        Execute(Ossim.C_Object(Writer));
    end Execute;

    procedure Delete(Readme : Object) is

        procedure Delete(Readme : Void_Ptr);
        pragma Import(C, Delete, "deleteOssimReadmeFileWriter");

    begin
        Delete(Ossim.C_Object(Readme));
    end Delete;
            
end Ossim.Connectable.Source.MetaData.Writer.File.Readme;
