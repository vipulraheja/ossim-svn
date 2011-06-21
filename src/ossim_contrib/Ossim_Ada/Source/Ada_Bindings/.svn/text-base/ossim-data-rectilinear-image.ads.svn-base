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
with IRect;
with Ossim.Connectable.Source;
with Ossim_Constants; use Ossim_Constants;
package Ossim.Data.Rectilinear.Image is

    type Object is new Ossim.Data.Rectilinear.Object with private;

    function Create(C_Object : Void_Ptr) return Object;

	function Create(Source  : Ossim.Connectable.Source.Object'class;
					Scalar  : OssimScalarType;
					bands   : ossim_uint32;
					width   : ossim_uint32;
					height  : ossim_uint32) return Object;

    function GetDataSizeInBytes(The_Object : Object) return ossim_uint32;

    function GetDataSizePerBandInBytes(The_Object : Object) return ossim_uint32;

    function GetBuf(
        The_Object 	: Object;
        Data_Size	: ossim_uint32;
        Index		: Integer) return Void_Ptr;
		
	function Is_Null(The_Object : Object) return Boolean;
	
	function GetImageRectangle(The_Object : Object) return IRect.Object;
	procedure SetImageRectangle(The_Object : Object;
								Rect	   : IRect.Object);

	function GetNumberOfBands(The_Object : Object) return ossim_uint32;

	function GetNullPix(The_Object  : Object;
						Band		: ossim_uint32) return ossim_float64;
	function getMinPix(The_Object   : Object;
						Band		: ossim_uint32) return ossim_float64;
	function getMaxPix(The_Object   : Object;
						Band		: ossim_uint32) return ossim_float64;
	function getMinNormalizedPix(The_Object  : Object) return ossim_float64;

	function GetWidth(The_Object  : Object) return ossim_uint32;

	function GetHeight(The_Object  : Object) return ossim_uint32;

    generic
        type Buffer_Ptr is private;
    function GetBuff_Band(
        The_Object 	: Object;
        Index		: Integer) return Buffer_Ptr;

    generic
        type Buffer_Ptr is private;
    function GetBuff(
        The_Object 	: Object) return Buffer_Ptr;

	--
    --  Initialize the data buffer.
    --
	procedure Initialize(The_Object 	: Object);

	--
    -- This is to be overriden in the derived classes so they can check
    -- If their data is null.
    --
	function IsInitialize(The_Object : Object) return Boolean;

	-- Will load a tile of different types.  If they
	-- are the same then it will call loadTile(void*...)
	-- method.  Note if they are of different types we
	-- will have to go through a much slower assign
	-- process by normalizing the right side and then
	-- unnormalizing to the destination type. For this
	-- method to work they both must have the same
	-- number of bands.
	procedure LoadTile(The_Object   : Object;
					   Src			: Object);

	procedure LoadTile(The_Object	: Object;
					  Src			: Void_Ptr;
					  Src_Rect		: IRect.Object;
					  IL_Type		: ossimInterleaveType);

	procedure LoadTile(The_Object	: Object;
					  Src			: Void_Ptr;
					  Src_Rect		: IRect.Object;
					  Clip_Rect		: IRect.Object;
					  IL_Type		: ossimInterleaveType);
					  
	function IsValidBand(The_Object	: Object;
						 Band		: ossim_uint32) return Boolean;

	function Validate(The_Object	: Object) return ossimDataObjectStatus;

	procedure LoadBand(The_Object	: Object;
					   Src			: Void_Ptr;
					   Src_Rect		: Irect.Object;
					   Band			: ossim_uint32);

	function Dup(The_Object	: Object) return Object;
	
	procedure Free(The_Object	: Object);

private

    type Object is new Ossim.Data.Rectilinear.Object with
    record
        null;
    end record;


end Ossim.Data.Rectilinear.Image;
