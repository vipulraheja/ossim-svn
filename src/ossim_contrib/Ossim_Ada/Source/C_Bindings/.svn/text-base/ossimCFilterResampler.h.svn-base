//*****************************************************************************
// Copyright (C) 2003 James E. Hopper & ImageLinks Inc.
//
// This is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation.
//
// This software is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// You should have received a copy of the GNU General Public License
// along with this software. If not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-
// 1307, USA.
//
// See the GPL in the COPYING.GPL file for more details.
//
// AUTHOR: James E. Hopper (hopperj@macconnect.com)
//
//*****************************************************************************
#ifndef ossimCFilterResampler_HEADER
#define ossimCFilterResampler_HEADER

typedef void* ossimCFilterResamplerH;

#ifdef __cplusplus
extern "C"
{
#endif
	
enum ossimCFilterResamplerType
{
	ossimFilterResampler_NEAREST_NEIGHBOR = 0,
	ossimFilterResampler_BOX              = 1,
	ossimFilterResampler_GAUSSIAN         = 2,
	ossimFilterResampler_CUBIC            = 3,
	ossimFilterResampler_HANNING          = 4,
	ossimFilterResampler_HAMMING          = 5,
	ossimFilterResampler_LANCZOS          = 6,
	ossimFilterResampler_MITCHELL         = 7,
	ossimFilterResampler_CATROM           = 8,
	ossimFilterResampler_BLACKMAN         = 9,
	ossimFilterResampler_BLACKMAN_SINC    = 10,
	ossimFilterResampler_BLACKMAN_BESSEL  = 11,
	ossimFilterResampler_QUADRATIC        = 12,
	ossimFilterResampler_TRIANGLE         = 13,
	ossimFilterResampler_HERMITE          = 14
};

ossimCFilterResamplerH ossimCreateFilterResampler();
void ossimDeleteFilterResampler(ossimCFilterResamplerH resampler);
void ossimCFilterResamplerSetFilterType(
	ossimCFilterResamplerH resampler, ossimCFilterResamplerType filterType);

#ifdef __cplusplus
}
#endif

#endif

