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
with Unchecked_Conversion;
with System; use type System.Address;
package body Ossim.Data.Rectilinear.Image is

    function Create(C_Object : Void_Ptr) return Object is
       the_Object : Object;
    begin
        the_Object.OssimObject:= C_Object;
        return the_Object; 
    end Create;

	function Create(Source  : Ossim.Connectable.Source.Object'class;
					Scalar  : OssimScalarType;
					Bands   : ossim_uint32;
					Width   : ossim_uint32;
					Height  : ossim_uint32) return Object is

		function Create(Source  : Void_Ptr;
						Scalar  : OssimScalarType;
						Bands   : ossim_uint32;
						Width   : ossim_uint32;
						Height  : ossim_uint32) return Void_Ptr;
		pragma Import(C, Create, "createOssimImageData");
		
	begin
		return Create(Create(ossim.C_Object(Source), Scalar, Bands, Width, Height));
	end Create;

    function GetDataSizeInBytes(The_Object : Object) return ossim_uint32 is
    
        function GetDataSizeInBytes(The_Object : Void_Ptr) return ossim_uint32;
        pragma Import(C, GetDataSizeInBytes, "ossimGetImageDataSizeInBytes");
        
    begin
        return GetDataSizeInBytes(ossim.C_Object(The_Object));
    end GetDataSizeInBytes;

    function GetDataSizePerBandInBytes(The_Object : Object) return ossim_uint32 is
        function GetDataSizeInBytes(The_Object : Void_Ptr) return ossim_uint32;
        pragma Import(C, GetDataSizeInBytes,
            "ossimGetImageDataSizePerBandInBytes");
    begin
        return GetDataSizeInBytes(The_Object.OssimObject);
    end GetDataSizePerBandInBytes;

    function GetBuf(The_Object 	: Object;
                    Data_Size	: ossim_uint32;
                    Index		: Integer) return Void_Ptr is

        type Buffer is array(1..Data_Size) of ossim_uint8;
        type Buffer_Ptr is access Buffer;
        Data : Buffer_Ptr := new Buffer;

        function GetBuf(
            The_Object 	: Void_Ptr;
            Index		: Integer) return Buffer_Ptr;
        pragma Import(C, GetBuf, "ossimGetImageDataBuf");

        function Convert is new Unchecked_Conversion(
            Buffer_Ptr, Void_Ptr);

    begin
        Data.all := GetBuf(Ossim.C_Object(The_Object), Index).all;
        return Convert(Data);
    end GetBuf;

    function GetBuff_Band(
            The_Object 	: Object;
            Index		: Integer) return Buffer_Ptr is

        function GetBuf(
            The_Object 	: Void_Ptr;
            Index		: Integer) return Buffer_Ptr;
        pragma Import(C, GetBuf, "ossimGetImageDataBuf");

    begin
        return GetBuf(Ossim.C_Object(The_Object), Index);
    end GetBuff_Band;

    function GetBuff(The_Object : Object) return Buffer_Ptr is

        function GetBuf(The_Object 	: Void_Ptr) return Buffer_Ptr;
        pragma Import(C, GetBuf, "getBuf");

    begin
        return GetBuf(Ossim.C_Object(The_Object));
    end GetBuff;

	function Is_Null(The_Object : Object) return Boolean is
	begin
		return Ossim.C_Object(The_Object) = System.Null_Address;
	end Is_Null;
	
	function GetImageRectangle(The_Object : Object) return IRect.Object is
	
		function GetImageRectangle(The_Object : Void_Ptr) return Void_Ptr;
		pragma Import(C, GetImageRectangle, "getImageRectangle");
		
	begin
		return IRect.Create(GetImageRectangle(Ossim.C_Object(The_Object)));
	end GetImageRectangle;

	procedure SetImageRectangle(The_Object : Object;
								Rect	   : IRect.Object) is


		procedure SetImageRectangle(The_Object : Void_Ptr;
									Rect	   : Void_Ptr);
		pragma Import(C, SetImageRectangle, "setImageRectangle");
		
	begin
		SetImageRectangle(Ossim.C_Object(The_Object), IRect.C_Object(Rect));
	end SetImageRectangle;
	
	function GetNumberOfBands(The_Object : Object) return ossim_uint32 is

		function GetNumberOfBands(The_Object : Void_Ptr) return ossim_uint32;
		pragma Import(C, GetNumberOfBands, "getNumberOfBands");

	begin
		return GetNumberOfBands(Ossim.C_Object(The_Object));
	end GetNumberOfBands;
	
	function GetNullPix(The_Object  : Object;
						Band		: ossim_uint32) return ossim_float64 is

		function GetNullPix(The_Object  : Void_Ptr;
							Band		: ossim_uint32) return ossim_float64;
		pragma import(C, GetNullPix, "getNullPix");

	begin
		return GetNullPix(ossim.C_Object(The_Object), Band);
	end GetNullPix;
	
	function getMinPix(The_Object   : Object;
						Band		: ossim_uint32) return ossim_float64 is

		function getMinPix(The_Object   : Void_Ptr;
							Band		: ossim_uint32) return ossim_float64;
		pragma import(C, getMinPix, "getMinPix");

	begin
		return getMinPix(ossim.C_Object(The_Object), Band);
	end getMinPix;
	
	function GetMaxPix(The_Object   : Object;
						Band		: ossim_uint32) return ossim_float64 is

		function GetMaxPix(The_Object   : Void_Ptr;
							Band		: ossim_uint32) return ossim_float64;
		pragma import(C, GetMaxPix, "getMaxPix");

	begin
		return getMaxPix(ossim.C_Object(The_Object), Band);
	end GetMaxPix;
	
	function getMinNormalizedPix(The_Object  : Object) return ossim_float64 is

		function getMinNormalizedPix(The_Object  : Void_Ptr) return ossim_float64;
		pragma import(C, getMinNormalizedPix, "getMinNormalizedPix");

	begin
		return getMinNormalizedPix(ossim.C_Object(The_Object));
	end getMinNormalizedPix;

	function GetWidth(The_Object  : Object) return ossim_uint32 is

		function GetWidth(The_Object  : Void_Ptr) return ossim_uint32;
		pragma Import(C, GetWidth, "getWidth");

	begin
		return GetWidth(Ossim.C_Object(The_Object));
	end GetWidth;

	function GetHeight(The_Object  : Object) return ossim_uint32 is
	
		function GetHeight(The_Object  : Void_Ptr) return ossim_uint32;
		pragma Import(C, GetHeight, "getHeight");

	begin
		return GetHeight(Ossim.C_Object(The_Object));
	end GetHeight;

	procedure Initialize(The_Object 	: Object) is

		procedure Initialize(The_Object 	: Void_Ptr);
		pragma Import(C, Initialize, "initialize");
		
	begin
		Initialize(ossim.C_Object(The_Object));
	end Initialize;

	function IsInitialize(The_Object : Object) return Boolean is


		function IsInitialize(The_Object : Void_Ptr) return Boolean;
		pragma Import(C, IsInitialize, "isInitialize");

	begin
		return IsInitialize(Ossim.C_Object(The_Object));
	end IsInitialize;

	procedure LoadTile(The_Object   : Object;
					   Src			: Object) is
		procedure LoadTile(The_Object   : Void_Ptr;
						   Src			: Void_Ptr);
		pragma Import(C, LoadTile, "loadTile");
		
	begin
		LoadTile(Ossim.C_Object(The_Object), Ossim.C_Object(Src));
	end LoadTile;
	
	procedure LoadTile(The_Object	: Object;
					  Src			: Void_Ptr;
					  Src_Rect		: IRect.Object;
					  IL_Type		: ossimInterleaveType) is

		procedure LoadTile(The_Object	: Void_Ptr;
						  Src			: Void_Ptr;
						  Src_Rect		: Void_Ptr;
						  IL_Type		: ossimInterleaveType);
		pragma Import(C, LoadTile, "loadTileBoundRect");

	begin
		LoadTile(Ossim.C_Object(The_Object), Src, IRect.C_Object(Src_Rect), IL_Type);
	end LoadTile;

	procedure LoadTile(The_Object	: Object;
					  Src			: Void_Ptr;
					  Src_Rect		: IRect.Object;
					  Clip_Rect		: IRect.Object;
					  IL_Type		: ossimInterleaveType) is

		procedure LoadTile(The_Object	: Void_Ptr;
						  Src			: Void_Ptr;
						  Src_Rect		: Void_Ptr;
						  Clip_Rect		: Void_Ptr;
						  IL_Type		: ossimInterleaveType);
		pragma Import(C, LoadTile, "loadTileClipRect");

	begin
		LoadTile(Ossim.C_Object(The_Object), Src, IRect.C_Object(Src_Rect), 
			IRect.C_Object(Clip_Rect), IL_Type);
	end LoadTile;
	
	function IsValidBand(The_Object	: Object;
						 Band		: ossim_uint32) return Boolean is

		function IsValidBand(The_Object	: Void_Ptr;
							 Band		: ossim_uint32) return Boolean;
		pragma Import(C, IsValidBand, "isValidBand");

	begin
		return IsValidBand(Ossim.C_Object(The_Object), Band);
	end IsValidBand;
	
	function Validate(The_Object : Object) return ossimDataObjectStatus is

		function Validate(The_Object : Void_Ptr) return ossimDataObjectStatus;
		pragma Import(C, Validate, "validate");

	begin
		return Validate(ossim.C_Object(The_Object));
	end Validate;

	procedure LoadBand(The_Object	: Object;
					   Src			: Void_Ptr;
					   Src_Rect		: Irect.Object;
					   Band			: ossim_uint32) is

		procedure LoadBand(The_Object	: Void_Ptr;
						   Src			: Void_Ptr;
						   Src_Rect		: Void_Ptr;
						   Band			: ossim_uint32);
		pragma Import(C, LoadBand, "loadBand");

	begin
		LoadBand(Ossim.C_Object(The_Object), Src, IRect.C_Object(Src_Rect), Band);
	end LoadBand;
	
	function Dup(The_Object	: Object) return Object is

		function Dup(The_Object	: Void_Ptr) return Void_Ptr;
		pragma Import(C, Dup, "dupData");

	begin
		return Create(Dup(Ossim.C_Object(The_Object)));
	end Dup;

	procedure Free(The_Object	: Object) is
	
		procedure Free(The_Object	: Void_Ptr);
		pragma Import(C, Free, "freeOssimImageData");
	begin
		Free(Ossim.C_Object(The_Object));
	end Free;

end Ossim.Data.Rectilinear.Image;
