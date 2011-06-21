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
package body Ossim.MapProjectionInfo is

    function Create(C_Object : Void_Ptr) return Object is
       the_Object : Object;
    begin
        the_Object.OssimObject:= C_Object;
        return the_Object; 
    end Create;
    
   function Create(Projection : Ossim.Projection.Object'class;
                   Output_Rect: DRect.Object) return Object is

        function Create_Info(Projection 	: Void_Ptr;
                        Output_Rect	: Void_Ptr) return Void_Ptr;
        pragma import(C, Create_Info, "ossimCreateMapProjectionInfo");

    begin
        return Create(Create_Info(Ossim.C_Object(Projection), 
                DRect.C_Object(Output_Rect)));
    end Create;
    
    procedure Delete(Project_Info : Object) is

        procedure Delete(Projection : Void_Ptr);
        pragma import(C, Delete, "ossimDeleteMapProjectionInfo");
        
    begin
        Delete(Ossim.C_Object(Project_Info));
    end Delete;

    function Lines_Per_Image(Projection : Object'class) return ossim_int32 is
    
        function Lines_Per_Image(Projection : Void_Ptr) return ossim_int32;
        pragma import(C, Lines_Per_Image, "mapProjectionInfoLinesPerImage");
            
    begin
        return Lines_Per_Image(Ossim.C_Object(Projection));
    end Lines_Per_Image;
    
    function Pixels_Per_Line(Projection : Object'class) return ossim_int32 is

        function Pixels_Per_Line(Projection : Void_Ptr) return ossim_int32;
        pragma import(C, Pixels_Per_Line, "mapProjectionInfoPixelsPerLine");

    begin
        return Pixels_Per_Line(Ossim.C_Object(Projection));
    end Pixels_Per_Line;

end Ossim.MapProjectionInfo;
