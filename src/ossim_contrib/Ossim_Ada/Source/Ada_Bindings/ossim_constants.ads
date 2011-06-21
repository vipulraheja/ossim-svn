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
with Interfaces; use Interfaces;
with Interfaces.C; use Interfaces.C;
package Ossim_Constants is

    --
    --  we know that if this is defined all other types are defined
    --  since its included from ossimConfig.h
    --
    subtype Ossim_Int8 is Interfaces.Integer_8;
    subtype Ossim_UInt8 is Interfaces.Unsigned_8;
    subtype ossim_sint8 is Interfaces.Integer_8;

    subtype ossim_int16 is Interfaces.Integer_16;
    subtype ossim_uint16 is Interfaces.Unsigned_16;
    subtype ossim_sint16 is Interfaces.Integer_16;

    subtype ossim_int32 is Interfaces.Integer_32;
    subtype ossim_uint32 is Interfaces.Unsigned_32;
    subtype ossim_sint32 is Interfaces.Integer_32;

    subtype ossim_float32 is IEEE_Float_32;
    subtype ossim_float64 is IEEE_Float_64;

    subtype ossim_int64 is Interfaces.Integer_64;
    subtype ossim_uint64 is Interfaces.Unsigned_64;
    subtype ossim_sint64 is Interfaces.Integer_64;

    subtype ossimErrorCode is ossim_int32;

    --ossimVertexOrdering
    --

    type ossimVertexOrdering is (
        OSSIM_VERTEX_ORDER_UNKNOWN,
        OSSIM_CLOCKWISE_ORDER,
        OSSIM_COUNTERCLOCKWISE_ORDER);
    for ossimVertexOrdering'Size use 32;

    --
    -- Corner coordinates are relative to center (0) of pixel
    -- or relative to the upper left of pixel (1).
    --
    --ossimPixelType
    --
    type ossimPixelType is (
        OSSIM_PIXEL_IS_POINT,
        OSSIM_PIXEL_IS_AREA);
    for ossimPixelType'Size use 32;

    --
    -- Definitions for scalar type identification.
    --
    --ossimScalarType
    --

    type OssimScalarType is (
        OSSIM_SCALAR_UNKNOWN    ,
        OSSIM_UCHAR             ,   -- unsigned   char   8  bit
        OSSIM_USHORT16          ,   -- unsigned   short  16 bit
        OSSIM_SSHORT16          ,   -- signed     short  16 bit
        OSSIM_USHORT11          ,   -- unsigned   short  11 bit
        OSSIM_FLOAT             ,   -- floating   point  32 bit
        OSSIM_NORMALIZED_FLOAT  ,   -- normalized floating point  32 bit
        OSSIM_DOUBLE            ,   -- double 64 bit    
        OSSIM_NORMALIZED_DOUBLE);   -- Normalized double 64 bit);
    for OssimScalarType'Size use 32;

    function To_Unsigned_32 is new Unchecked_Conversion(
        OssimScalarType, Unsigned_32);

    --
    -- Definitions for interleave type identification.
    --
    --ossimInterleaveType
    --
    type ossimInterleaveType is (
        OSSIM_INTERLEAVE_UNKNOWN,
        OSSIM_BIL, -- band interleaved by line 
        OSSIM_BIP, -- band interleaved by pixel 
        OSSIM_BSQ,  -- band sequential 
        OSSIM_BSQ_MULTI_FILE -- band sequential in separate files 
            );
    for ossimInterleaveType'Size use 32;

    --
    -- Definitions for origin location.
    --
    --ossimOriginLocationType
    --
    type ossimOriginLocationType is (
        OSSIM_ORIGIN_LOCATION_UNKNOWN,
        OSSIM_CENTER,
        OSSIM_UPPER_LEFT,
        OSSIM_UPPER_LEFT_CENTER,
        OSSIM_LOWER_LEFT,
        OSSIM_LOWER_LEFT_CENTER);
    for ossimOriginLocationType'Size use 32;

    --
    -- Definitions for coordinate system type.
    --
    --ossimCoordinateSystemType
    --
    type ossimCoordinateSystemType is (
        OSSIM_COORDINATE_SYSTEM_UNKNOWN,
        OSSIM_IMAGE_SPACE,
        OSSIM_GEOGRAPHIC_SPACE,
        OSSIM_PROJECTED_SPACE,
        OSSIM_GEOCENTRIC_SPACE);
    for ossimCoordinateSystemType'Size use 32;

    --
    -- Definitions for coordinate system orientation mode .
    --
    --ossimCoordSysOrientMode
    --
    type ossimCoordSysOrientMode is (
        OSSIM_LEFT_HANDED,
        OSSIM_RIGHT_HANDED);
    for ossimCoordSysOrientMode'Size use 32;

    --
    -- Definitions for unit type.
    --
    --ossimUnitType
    --
    type ossimUnitType is (
        OSSIM_UNIT_UNKNOWN,
        OSSIM_METERS,
        OSSIM_FEET,
        OSSIM_US_SURVEY_FEET,
        OSSIM_DEGREES,
        OSSIM_RADIANS,
        OSSIM_NAUTICAL_MILES,
        OSSIM_SECONDS,
        OSSIM_MINUTES,
        OSSIM_PIXEL,
        OSSIM_MILES,
        OSSIM_MILLIMETERS);
    for ossimUnitType'Size use 32;

    --
    -- Definitions for data object status.
    --
    --ossimDataObjectStatus
    --
    type ossimDataObjectStatus is (
        OSSIM_STATUS_UNKNOWN,
        OSSIM_NULL,
        OSSIM_EMPTY,
        OSSIM_PARTIAL,
        OSSIM_FULL);
    for ossimDataObjectStatus'Size use 32;

    --
    -- Definitions for image type identification.
    --
    --ossimImageType
    --
    type ossimImageType is (
        OSSIM_IMAGE_TYPE_UNKOWN,
        OSSIM_TIFF_STRIP,
        OSSIM_TIFF_STRIP_BAND_SEPARATE,
        OSSIM_TIFF_TILED,
        OSSIM_TIFF_TILED_BAND_SEPARATE,
        OSSIM_GENERAL_RASTER_BIP,
        OSSIM_GENERAL_RASTER_BIL,
        OSSIM_GENERAL_RASTER_BSQ,
        OSSIM_JPEG);
    for ossimImageType'Size use 32;

    --**
    -- Definitions for metadata type identification.
    --
    --ossimMetadataType
    --
    type ossimMetadataType is (
        OSSIM_META_TFW,
        OSSIM_META_JGW,
        OSSIM_META_GEOM,
        OSSIM_META_README,
        OSSIM_META_EW,
        OSSIM_META_FGDC,
        OSSIM_META_ERMAPPER,
        OSSIM_META_ENVI);
    for ossimMetadataType'Size use 32;

    --ossimByteOrder
    --
    type ossimByteOrder is (
        OSSIM_LITTLE_ENDIAN,
        OSSIM_BIG_ENDIAN);
    for ossimByteOrder'Size use 32;

    M_Pi	: Constant ossim_float64 := 3.141592653589793238462643;
    TWO_PI	: Constant ossim_float64 := 2.0 * M_PI;
    DEG_PER_RAD	: Constant ossim_float64 := 180.0/M_PI;
    SEC_PER_RAD	: Constant ossim_float64 := 206264.8062471;
    RAD_PER_DEG	: Constant ossim_float64 := M_PI/180.0;
    MTRS_PER_FT	: Constant ossim_float64 := 0.3048;
    FT_PER_MTRS	: Constant ossim_float64 := 3.280839895013122;
    FT_PER_MILE	: Constant ossim_float64 := 5280.0;
    SQRT_TWO_PI	: Constant ossim_float64 := 2.50662827463100050242;
    SQRT_TWO_PI_DIV2	: Constant ossim_float64 := 7.07106781186547524401E-1;

    OSSIM_DEFAULT_TILE_HEIGHT 	: long_integer := 64;
    OSSIM_DEFAULT_TILE_WIDTH 	: Integer := 64; 

    --
    -- NOTE Reference for U.S. feet value:
    -- U.S.G.S. "Map Projections - A Working Manual"
    -- USGS Professional paper 1395 page 51
    US_METERS_PER_FT	: ossim_float64 := 0.3048006096;

    function convert is new Unchecked_Conversion(
        ossim_uint32, ossim_sint32);
    function convert is new Unchecked_Conversion(
        ossim_uint16, ossim_sint16);
    DBL_EPSILON 	: Constant ossim_float64 := 2.2204460492503131e-16;
    FLT_EPSILON		: Constant ossim_float32 := 1.19209290e-07;
    OSSIM_DBL_NAN 	: Constant ossim_float64 := -1.0/DBL_EPSILON;
    OSSIM_FLT_NAN    	: Constant ossim_float32 := -1.0/FLT_EPSILON;
    OSSIM_LONG_NAN   	: Constant ossim_sint32 := Convert(16#80000000#);
    OSSIM_INT_NAN   	: Constant ossim_sint32 := Convert(16#80000000#);
    OSSIM_ULONG_NAN  	: Constant ossim_uint32 := 16#FFFFFFFF#;
    OSSIM_UINT_NAN   	: Constant ossim_uint32 := 16#FFFFFFFF#;
    OSSIM_SSHORT_NAN 	: Constant ossim_sint16 := Convert(16#8000#);
    OSSIM_USHORT_NAN 	: Constant ossim_uint16 := 0;

    OSSIM_DEFAULT_MIN_PIX_UCHAR : Constant ossim_uint8 := 1;
    OSSIM_DEFAULT_MAX_PIX_UCHAR : Constant ossim_uint8 := 255;
    OSSIM_DEFAULT_MIN_PIX_SINT16 : Constant ossim_sint16 := Convert(16#8000#);
    OSSIM_DEFAULT_MAX_PIX_SINT16 : Constant ossim_sint16 := Convert(16#7FFF#);
    OSSIM_DEFAULT_MIN_PIX_UINT16 : Constant ossim_uint16 := 1;
    OSSIM_DEFAULT_MAX_PIX_UINT16 : Constant ossim_uint16 := 16#FFFF#;
    OSSIM_DEFAULT_MIN_PIX_UINT11 : Constant ossim_uint16 := 1;
    OSSIM_DEFAULT_MAX_PIX_UINT11 : Constant ossim_uint16 := 16#7FF#;

   OSSIM_DEFAULT_MIN_PIX_FLOAT : Constant ossim_float32 := (-1.0/FLT_EPSILON)+1.0;
   OSSIM_DEFAULT_MAX_PIX_FLOAT : Constant ossim_float32 := 1.0/FLT_EPSILON;
   OSSIM_DEFAULT_MIN_PIX_NORM_FLOAT : Constant ossim_float32 :=2.0*FLT_EPSILON;
   OSSIM_DEFAULT_MAX_PIX_NORM_FLOAT : Constant ossim_float32 := 1.0;
   OSSIM_DEFAULT_MIN_PIX_DOUBLE : Constant ossim_float64 := (-1.0/DBL_EPSILON)+1.0;
   OSSIM_DEFAULT_MAX_PIX_DOUBLE : Constant ossim_float64 := (1.0/DBL_EPSILON);
   OSSIM_DEFAULT_MIN_PIX_NORM_DOUBLE : Constant ossim_float64 := 2.0*DBL_EPSILON;
   OSSIM_DEFAULT_MAX_PIX_NORM_DOUBLE : Constant ossim_float64 := 1.0;

    -- *OSSIM Numerical Limits
    -- 
    --ifndef _OSSIM_LIMITS_
    --Const _OSSIM_LIMITS_ : Integer = 1;
    OSSIM_INFINITY 	: ossim_float64 := (1.0/DBL_EPSILON)-1.0;
    OSSIM_NAN 		: ossim_float64 := (1.0/DBL_EPSILON);
    OSSIM_EPSILON 	: ossim_float64 := DBL_EPSILON;

end Ossim_Constants;

