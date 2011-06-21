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
#include "ossimCFilterResampler.h"
#include "imaging/resample/ossimFilterResampler.h"

ossimCFilterResamplerH ossimCreateFilterResampler()
{
	ossimFilterResampler* Resampler = (ossimFilterResampler*) new ossimFilterResampler();
	return (ossimCFilterResamplerH)Resampler;
}

void ossimDeleteFilterResampler(ossimCFilterResamplerH resampler)
{
	if(resampler)
		delete (ossimFilterResampler*)resampler;
}

void ossimCFilterResamplerSetFilterType(
		ossimCFilterResamplerH resampler, ossimCFilterResamplerType filterType)
{
	ossimFilterResampler* sampler = (ossimFilterResampler*)resampler;
	sampler->setFilterType(ossimFilterResampler::ossimFilterResamplerType(filterType));
}
