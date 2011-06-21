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
with System;
with Interfaces.C.Extensions;
use Interfaces.C.Extensions;
package FilterResampler is

    type Object is tagged private;

    type OssimCFilterResamplerType is
            (ossimFilterResampler_NEAREST_NEIGHBOR,
            ossimFilterResampler_BOX,
            ossimFilterResampler_GAUSSIAN,
            ossimFilterResampler_CUBIC,
            ossimFilterResampler_HANNING,
            ossimFilterResampler_HAMMING,
            ossimFilterResampler_LANCZOS,
            ossimFilterResampler_MITCHELL,
            ossimFilterResampler_CATROM,
            ossimFilterResampler_BLACKMAN,
            ossimFilterResampler_BLACKMAN_SINC,
            ossimFilterResampler_BLACKMAN_BESSEL,
            ossimFilterResampler_QUADRATIC,
            ossimFilterResampler_TRIANGLE,
            ossimFilterResampler_HERMITE);
    for OssimCFilterResamplerType use (0, 1, 2, 3, 4, 5, 6, 7,
            8, 9, 10, 11, 12, 13, 14);
    for OssimCFilterResamplerType'size use 32;

    function Create(C_Object : Void_Ptr) return Object;

    function Create return Object;
    
    procedure Delete(Sampler : Object);
    
    procedure SetFilterType(
            Sampler		: Object;
            FilterType	: OssimCFilterResamplerType);

    function C_Object(The_Object : Object'class) return Void_Ptr;

private

    type Object is tagged 
    record
        OssimObject	: Void_Ptr;
    end record;

end FilterResampler;
