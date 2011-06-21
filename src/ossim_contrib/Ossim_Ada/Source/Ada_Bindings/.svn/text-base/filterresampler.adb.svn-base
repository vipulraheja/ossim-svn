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
package body FilterResampler is

    function Create(C_Object : Void_Ptr) return Object is
        TheObject : Object;
    begin
        TheObject.OssimObject:= C_Object;
        return TheObject;
    end Create;

    function Create return Object is

        function Create return Void_Ptr;
        pragma import(C, Create, "ossimCreateFilterResampler");

    begin
        return Create(Create);
    end Create;

    procedure Delete(Sampler : Object) is

        procedure Delete(Sampler : void_ptr);
        pragma import(C, Delete, "ossimDeleteFilterResampler");

    begin
        Delete(C_Object(Sampler));
    end Delete;

    procedure SetFilterType(
            Sampler		: Object;
            FilterType	: OssimCFilterResamplerType) is

        procedure SetFilterType(
                Sampler : void_ptr;
                FilterType	: OssimCFilterResamplerType);
        pragma Import(C, SetFilterType, "ossimCFilterResamplerSetFilterType");
    
    begin
        SetFilterType(C_Object(Sampler), FilterType);
    end SetFilterType;

    function C_Object(The_Object : Object'class) return Void_Ptr is
    begin
        return The_Object.OssimObject;
    end C_Object;

end FilterResampler;
