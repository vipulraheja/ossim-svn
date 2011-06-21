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

#include "ossimCImageRenderer.h"
#include "imaging/tile_sources/ossimImageRenderer.h"

ossimCImageRendererH ossimCreateImageRenderer(ossimConnectableObjectH inputSource)
{
	ossimImageRenderer* render = new ossimImageRenderer();
	render->connectMyInputTo(PTR_CAST(ossimConnectableObject,
								   (ossimObject*)inputSource));
	return (ossimCImageRendererH)render;
}

void ossimDeleteRenderer(ossimCImageRendererH render)
{
	if(render)
		delete (ossimImageRenderer*) render;
}

ossimCFilterResamplerH getResampler(ossimCImageRendererH renderer)
{
	ossimImageRenderer* r = (ossimImageRenderer*) renderer;
	return (ossimCFilterResamplerH) r->getResampler();
}

ossimCMapProjectionH getView(ossimCImageRendererH renderer)
{
	ossimImageRenderer* r = (ossimImageRenderer*) renderer;
	return (ossimCMapProjectionH)r->getView();
}

bool ossimImageRendererSetView(ossimCImageRendererH renderer,
			 ossimCMapProjectionH baseObject,
			 bool ownsTheView) // default to false
{
	ossimImageRenderer* r = (ossimImageRenderer*) renderer;
	return r->setView((ossimObject*)baseObject, ownsTheView);
}

