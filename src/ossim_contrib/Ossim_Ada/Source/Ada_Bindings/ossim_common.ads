--*******************************************************************
-- Copyright (C) 2000 ImageLinks Inc. 
--
-- OSSIM is free software; you can redistribute it and/or
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
-- Author: Ken Melero (kmelero@remotesensing.org)
-- Description: Common file for global functions.
--
--*************************************************************************
with Ossim_Constants;
 use Ossim_Constants;
package Ossim_Common is

    Common_H :  Short_Integer := 1;

    function  Cosd(X : Long_Float)  return  Long_Float;
    pragma Import(C, Cosd, "cosd");

    function  Sind(X : Long_Float)  return  Long_Float;
    pragma Import(C, Sind, "sind");

    function  Tand(X : Long_Float)  return  Long_Float;
    pragma Import(C, Tand, "tand");

    function  Acosd(X : Long_Float)  return  Long_Float;
    pragma Import(C, Acosd, "acosd");

    function  Asind(X : Long_Float)  return  Long_Float;
    pragma Import(C, Asind, "asind");

    function  Atand(X : Long_Float)  return  Long_Float;
    pragma Import(C, Atand, "atand");

    function  Atan2d(Y : Long_Float; X : Long_Float)  return  Long_Float;
    pragma Import(C, Atan2d, "atan2d");

    function  OssimIsNan(Val : Long_Float)  return  Boolean;

    function  ossimIsNan(Val : Float)  return  Boolean;

    function  ossimIsNan(Val :  Short_Integer)  return  Boolean;

    function  ossimIsNan(Val : Long_Integer)  return  Boolean;
    pragma Import(C, OssimIsNan, "ossimIsNan");
    
    function  Sinc(X : Long_Float)  return  Long_Float;
    pragma Import(C, Sinc, "sinc");

    function  OssimGetSign(Value : Long_Float)  return   Short_Integer;
    pragma Import(C, OssimGetSign, "ossimGetSign");

    function  Square(X : Long_Float)  return  Long_Float;

    function  Square(X : Long_Integer)  return  Long_Integer;
    pragma Import(C, Square, "square");

    function  Equals(X : Long_Float; Y : Long_Float)  return  Boolean;

    function  Equals(X : Float; Y : Float)  return  Boolean;
    pragma Import(C, Equals, "equals");

    function  Factorial(N :  Short_Integer)  return   Short_Integer;
    pragma Import(C, Factorial, "factorial");

    -- Round a Long_Float to an int correctly.
    --inline int irint(Long_Float d) { return int(floor(d + 0.5)); 
    function  Irint(D : Long_Float)  return   Short_Integer;

    -- Round a Long_Float to an int correctly.
    --inline long irlong(Long_Float d) { return long(floor(d + 0.5)); 
    function  Irlong(D : Long_Float)  return   Short_Integer;

    -- Round a Long_Float to an int correctly.
    --inline int irint(Long_Float d) { return int(floor(d + 0.5)); 
    function  Irint(D : Float)  return   Short_Integer;
    pragma Import(C, Irint, "irint");

    -- Round a Long_Float to an int correctly.
    --inline long irlong(Long_Float d) { return long(floor(d + 0.5)); 
    function  Irlong(D : Float)  return   Short_Integer;
    pragma Import(C, Irlong, "irlong");

    function  Gcd(M :  Short_Integer; N :  Short_Integer)  return
        Short_Integer;
    pragma Import(C, Gcd, "gcd");

    --***
    -- Common conversion functions
    --***
    function  Ft2mtrs(Feet : Long_Float)  return  Long_Float;
    pragma Import(C, Ft2mtrs, "ft2mtrs");

    function  Usft2mtrs(Feet : Long_Float)  return  Long_Float;
    pragma Import(C, Usft2mtrs, "usft2mtrs");

    function  Mtrs2ft(Meters : Long_Float)  return  Long_Float;
    pragma Import(C, Mtrs2ft, "mtrs2ft");

    function  Mtrs2usft(Meters : Long_Float)  return  Long_Float;
    pragma Import(C, Mtrs2usft, "mtrs2usft");

    function  ByteOrder  return  Ossim_Int32;
    pragma Import(C, ByteOrder, "byteOrder");

    function  OssimGetDefaultMin(ScalarType : 
        OssimScalarType)  return Long_Float;
    pragma Import(C, OssimGetDefaultMin, "ossimGetDefaultMin");

    function  OssimGetDefaultMax(ScalarType : 
        OssimScalarType)  return Long_Float;
    pragma Import(C, OssimGetDefaultMax, "ossimGetDefaultMax");

    function  OssimGetDefaultNull(ScalarType : 
        OssimScalarType)  return Long_Float;
    pragma Import(C, OssimGetDefaultNull, "ossimGetDefaultNull");

    function  OssimGetScalarSizeInBytes(ScalarType : 
            OssimScalarType)  return Ossim_Uint32;
    pragma Import(C, OssimGetScalarSizeInBytes,
        "GetScalarSizeInBytes");

        
end Ossim_Common;

