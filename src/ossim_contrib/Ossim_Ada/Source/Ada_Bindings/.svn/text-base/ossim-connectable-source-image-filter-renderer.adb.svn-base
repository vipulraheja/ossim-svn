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
package body Ossim.Connectable.Source.Image.Filter.Renderer is

    function Create(C_Object : Void_Ptr) return Object is
        the_Object : Object;
    begin
        the_Object.OssimObject:= C_Object;
        return the_Object; 
    end Create;

    function Create(Source : Ossim.Connectable.Object'class) return Object is

        function Create_Renderer(Source : Void_Ptr) return Void_Ptr;
        pragma import(C, Create_Renderer, "ossimCreateImageRenderer");
		
		tmp : Void_Ptr := Create_Renderer(Ossim.C_Object(Source));

    begin
		if tmp = System.Null_Address then
			raise Can_Not_Create;
		end if;
        return Create(tmp);
    end Create;

    procedure Delete(Renderer : Object) is

        procedure Delete(Renderer : void_ptr);
        pragma import(C, Delete, "ossimDeleteRenderer");

    begin
        Delete(Ossim.C_Object(Renderer));
    end Delete;

    function GetResampler(Renderer : Object) return FilterResampler.Object is
            
        function GetResampler(Renderer : Void_Ptr) return Void_Ptr;
        pragma Import(C, GetResampler, "getResampler");
        
    begin
        return FilterResampler.Create(GetResampler(Ossim.C_Object(
                    Renderer)));
    end GetResampler;

    function GetView(Renderer : Object) return Ossim.Projection.Object is

        function GetView(Renderer : Void_Ptr) return Void_Ptr;
        pragma Import(C, GetView, "getView");

		tmp 	: Void_Ptr := Ossim.C_Object(Renderer);
		tmp1 	: Void_Ptr := GetView(tmp);
		theView : Ossim.Projection.Object;
    begin
		if tmp1 /= System.Null_Address then
			theView:=  Ossim.Projection.Create(tmp1);
			return theView;
		else
			raise No_View;
		end if;
    end GetView;

    function SetView(
			Renderer	: Object;
            BaseObject	: Ossim.Projection.Object;
            OwnsTheView	: Boolean := False) return Boolean is

        function SetView(
			Renderer 	: Void_Ptr;
            BaseObject	: Void_Ptr;
            OwnsTheView	: Boolean) return Boolean;
        pragma Import(C, SetView, "ossimImageRendererSetView");

    begin
        return SetView(
			Ossim.C_Object(Renderer), 
			Ossim.C_Object(BaseObject), OwnsTheView);
    end SetView;

end Ossim.Connectable.Source.Image.Filter.Renderer;
