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
with System; use type System.Address;
with ListenerManager;
--pragma Elaborate_All(ListenerManager);
with ProcessInterface;
--pragma Elaborate_All(ProcessInterface);
package body Ossim.Connectable.Source.Output.Imagewriter.File is

    function C_Object(the_Object : Object'class) return Void_Ptr;
    package WriteListener is new ListenerManager(Object, Create, C_Object);
        
    function Create(C_Object : Void_Ptr) return Object is
        the_Object : Object;
    begin
        the_Object.OssimObject:= C_Object;
        return the_Object;
    end Create;

    procedure SetFilename(Writer	: Object;
                          Filename 	: OssimString.Filename.Object) is
 
		procedure SetFilename(Writer	: Void_Ptr;
                                      Filename 	: Void_Ptr);
        pragma Import(C, SetFilename, "ossimSetFilename");

    begin
        SetFilename(Ossim.C_Object(Writer), ossimString.Filename.C_Object(Filename));
    end SetFilename;

    procedure SetFilename(  Writer 		: Object;
                            Filename 	: String) is

        procedure SetFilename(Writer	: Void_Ptr;
                              Filename 	: Void_Ptr);
        pragma Import(C, SetFilename, "ossimSetFilename");
		
        File 	  : String(Filename'first..Filename'last + 1) := Filename & ASCII.Nul;
        File_Name : OssimString.Object'class := OssimString.Create(File);
        
    begin
        SetFilename(Ossim.C_Object(Writer), OssimString.C_Object(File_Name));
    end SetFilename;

    function Is_Null(Writer : Object) return Boolean is
    begin
        return Ossim.C_Object(Writer) = System.Null_Address;
    end Is_Null;

    procedure Execute(Writer : Object) is

		procedure Execute(Writer : Void_Ptr);
		pragma import(C, Execute, "ossimExecuteImageFileWriter");
		
    begin
        Execute(Ossim.C_Object(Writer));
    end Execute;

    function AddListener(
            Writer		: Object;
            theListener : Listener.Process.StdOutProgress.Object) return Boolean is

    begin
        return WriteListener.AddListener(Writer, theListener);
    end AddListener;

    function AddListener(
            Writer 		: Object;
            theListener 	: Listener.Process.ProgressPercent.Object) return Boolean is

    begin
        return WriteListener.AddListener(Writer, theListener);
    end AddListener;

    function RemoveListener(
            Writer 		: Object;
            theListener 	: Listener.Process.StdOutProgress.Object) return Boolean is
    begin
        return WriteListener.RemoveListener(Writer, theListener);
    end RemoveListener;

    function RemoveListener(
            Writer 		: Object;
            theListener 	: Listener.Process.ProgressPercent.Object) return Boolean is
    begin
        return WriteListener.RemoveListener(Writer, theListener);
    end RemoveListener;

    function GetNumberImageType(TheList : OssimString.StringList) return ossim_uint32 is
    begin
        return OssimString.GetNumberItems(TheList);
    end GetNumberImageType;

    function GetImageType(TheList : OssimString.StringList;
            Index : ossim_uint32) return String is
    begin
        return OssimString.GetossimString(TheList, Index);
    end GetImageType;

    procedure SetOutputName(
            Writer 	: Object;
            OutputName	: String) is

        procedure SetOutputName(
            Writer 	: Void_Ptr;
            OutputName	: System.Address);
        pragma Import(C, SetOutputName, "setOutputName");

        OutputName_Null : String(OutputName'First..OutputName'Last + 1) :=
            OutputName & ASCII.Nul;

    begin
        SetOutputName(Ossim.C_Object(Writer), OutputName_Null'Address);
    end SetOutputName;

	procedure Writer_Abort(Writer : Object) is
	
		procedure Writer_Abort(Writer : Void_Ptr);
        pragma Import(C, Writer_Abort, "ossimFileWrighterAbort");
		
	begin
		Writer_Abort(Ossim.C_Object(Writer));
	end Writer_Abort;

    procedure Free(Handler : Object) is

        procedure Free(Handler : Void_Ptr);
        pragma Import(C, Free, "ossimFreeObject");

    begin
        Free(Handler.OssimObject);
    end Free;

    function C_Object(the_Object : Object'class) return Void_Ptr is
    begin
        return the_Object.OssimObject;
    end C_Object;

end Ossim.Connectable.Source.Output.Imagewriter.File;
